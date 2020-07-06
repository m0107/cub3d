/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 23:36:47 by mgupta            #+#    #+#             */
/*   Updated: 2019/10/31 02:07:49 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t len)
{
	char *dst;
	char *src;

	dst = (char *)d;
	src = (char *)s;
	if (dst == src)
		return (dst);
	if (src < dst && (src + len) > dst)
	{
		src += len;
		dst += len;
		while (len--)
			*--dst = *--src;
	}
	else
	{
		while (len--)
			*dst++ = *src++;
	}
	return (d);
}
