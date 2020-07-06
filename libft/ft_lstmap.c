/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:44:47 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/06 20:07:24 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ans;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	if (!(temp = ft_lstnew(f(lst->content))))
		return (NULL);
	ans = temp;
	lst = lst->next;
	while (lst != NULL)
	{
		if (!(temp->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&ans, del);
			return (NULL);
		}
		lst = lst->next;
		temp = temp->next;
	}
	return (ans);
}
