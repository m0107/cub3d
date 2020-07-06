/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:46:18 by mgupta            #+#    #+#             */
/*   Updated: 2019/10/31 03:14:41 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkstr(const char *h, const char *ndle, int len, int tem)
{
	int i;

	i = 0;
	while (h[i] == ndle[i] && (tem + i) < len)
	{
		i++;
		if (ndle[i] == '\0')
			return (1);
	}
	return (0);
}

char		*ft_strnstr(const char *h, const char *ndle, unsigned int len)
{
	unsigned int i;

	i = 0;
	if (!*ndle)
		return ((char *)h);
	while (*h && i < len)
	{
		if (*h == ndle[0])
		{
			if (checkstr(h, ndle, len, i))
				return (char *)h;
		}
		h++;
		i++;
	}
	return (NULL);
}
