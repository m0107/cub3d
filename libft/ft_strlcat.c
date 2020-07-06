/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:38:01 by mgupta            #+#    #+#             */
/*   Updated: 2019/10/30 21:09:48 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	int n;
	int i;
	int j;

	i = 0;
	while (dst[i] != '\0')
		i++;
	n = size - i - 1;
	j = -1;
	while (++j < n && src[j] != '\0')
	{
		dst[i + j] = src[j];
	}
	dst[i + j] = '\0';
	return ((size_t)(ft_min((int)size, i) + ft_strlen(src)));
}
