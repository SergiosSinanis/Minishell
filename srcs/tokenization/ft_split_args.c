/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:37:08 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/08 15:14:23 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	ft_count_words(char *str, char *charset)
{
	int		i;
	int		count;
	char	*flag;

	flag = ft_set_flags(str, charset);
	if (!flag)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (flag[i] == '0' && str[i])
			i++;
		if (flag[i] == '1' && str[i++])
			count++;
		while (flag[i] == '1' && str[i])
			i++;
		if (flag[i] == '2' && str[i++])
			count++;
		while (flag[i] == '2' && str[i])
			i++;
	}
	free(flag);
	return (count);
}

char	*ft_str_cpy_i(char *dest, const char *src, int index, int *len)
{
	int	i;

	i = 0;
	dest = malloc((*len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < *len)
	{
		dest[i] = src[index + i];
		i++;
	}
	dest[i] = '\0';
	*len = 0;
	return (dest);
}

char	**ft_add_words(char **res, char *str, char *charset, char *flag)
{
	int	i;
	int	j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (j < ft_count_words(str, charset))
	{
		while (flag[i] == '0' && str[i])
			i++;
		while (flag[i] == '1' && str[i++])
			k++;
		if (k != 0)
		{
			res[j] = ft_str_cpy_i(res[j], str, i - k, &k);
			j++;
		}
		while (flag[i] == '2' && str[i++])
			k++;
		if (k != 0)
		{
			res[j] = ft_str_cpy_i(res[j], str, i - k, &k);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split_args(char *str, char *charset)
{
	char		**res;
	char		*flags;

	flags = ft_set_flags(str, charset);
	if (ft_strncmp(flags, "error", 5) == 0)
	{
		free(flags);
		ft_putstr_fd("minishell: missing quote\n", 2);
		return (ft_calloc(1, sizeof(char *)));
	}
	res = malloc((ft_count_words(str, charset) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_add_words(res, str, charset, flags);
	free(flags);
	return (res);
}
