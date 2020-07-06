/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:39:30 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/06 16:52:42 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		ans;
	t_list	*temp;

	temp = lst;
	ans = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		ans++;
	}
	return (ans);
}
