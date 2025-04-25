/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:02:02 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:03:04 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;

	tmp = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		new_lst = ft_lstnew((*f)(lst->content));
		if (!new_lst)
		{
			while (tmp)
			{
				new_lst = tmp->next;
				(*del)(tmp->content);
				free(tmp);
				tmp = new_lst;
			}
			return (NULL);
		}
		ft_lstadd_back(&tmp, new_lst);
		lst = lst->next;
	}
	return (tmp);
}
