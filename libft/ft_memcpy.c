/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 02:27:52 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/07 15:33:34 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict d, const void *restrict s, size_t n)
{
	char *dst;
	char *src;

	if (d == NULL && s == NULL)
		return (NULL);
	dst = (char *)d;
	src = (char *)s;
	while (n--)
		*dst++ = *src++;
	return (d);
}
