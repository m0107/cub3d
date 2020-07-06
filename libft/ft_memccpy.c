/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 02:34:25 by mgupta            #+#    #+#             */
/*   Updated: 2019/10/31 02:45:12 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict d, const void *restrict s, int c, size_t len)
{
	char *dst;
	char *src;

	dst = (char *)d;
	src = (char *)s;
	while (len--)
	{
		if (*(unsigned char *)src == (unsigned char)c)
		{
			*dst++ = *src++;
			return (dst);
		}
		else
			*dst++ = *src++;
	}
	return (NULL);
}
