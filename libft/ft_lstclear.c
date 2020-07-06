/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:19:21 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/07 16:38:57 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;

	if (!del)
		return ;
	while (*lst != NULL)
	{
		temp = *lst;
		del((*lst)->content);
		(*lst) = (*lst)->next;
		free(temp);
	}
}
