/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:58:04 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:53:03 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_env_variable(const char *var_name, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

char	*ft_append_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = ft_realloc(str, len + 1, len + 2, 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

void	ft_update_quote_flags(char c, int *flag_single, int *flag_double)
{
	if (c == '\'' && *flag_double == 0)
	{
		if (*flag_single == 0)
			*flag_single = 1;
		else
			*flag_single = 0;
	}
	else if (c == '\"' && *flag_single == 0)
	{
		if (*flag_double == 0)
			*flag_double = 1;
		else
			*flag_double = 0;
	}
}

char	*ft_dollar(char *str, int *i, t_expand_context *context)
{
	char	*value;
	char	*var_name;

	if (str[++(*i)] == '?')
		return (ft_question_mark(context->new_str, context->exit_status));
	var_name = ft_strdup("");
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name = ft_append_char(var_name, str[(*i)++]);
	(*i)--;
	value = ft_get_env_variable(var_name, context->env);
	if (ft_strlen(var_name) > 0 && value)
	{
		context->new_str = ft_realloc(context->new_str,
				ft_strlen(context->new_str) + 1,
				ft_strlen(context->new_str) + ft_strlen(value) + 1, 1);
		ft_strlcat(context->new_str, value,
			ft_strlen(context->new_str) + ft_strlen(value) + 1);
		free(value);
	}
	free(var_name);
	return (context->new_str);
}

char	*ft_expand(char *str, char **env, int exit_status)
{
	int						i;
	int						flag_single_quote;
	int						flag_double_quote;
	t_expand_context		context;

	i = 0;
	flag_single_quote = 0;
	flag_double_quote = 0;
	context.env = env;
	context.exit_status = exit_status;
	context.new_str = ft_strdup("");
	while (str[i])
	{
		ft_update_quote_flags(str[i], &flag_single_quote, &flag_double_quote);
		if (str[i + 1] && !ft_isalnum(str[i + 1]) && str[i + 1] != '?')
			context.new_str = ft_append_char(context.new_str, str[i]);
		else if (!str[i + 1])
			context.new_str = ft_append_char(context.new_str, str[i]);
		else if (str[i] == '$' && !flag_single_quote)
			context.new_str = ft_dollar(str, &i, &context);
		else
			context.new_str = ft_append_char(context.new_str, str[i]);
		i++;
	}
	return (context.new_str);
}
