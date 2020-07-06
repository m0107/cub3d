/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 03:22:49 by mgupta            #+#    #+#             */
/*   Updated: 2019/10/31 05:47:08 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *ans;

	ans = NULL;
	if (!(ans = malloc(size * count)))
		return (NULL);
	ft_bzero(ans, (size * count));
	return (ans);
}
