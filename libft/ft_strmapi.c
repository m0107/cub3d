/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:08:42 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/06 15:31:48 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*ans;
	int		i;

	if (s == NULL)
		return (NULL);
	i = -1;
	len = ft_strlen(s) + 1;
	if (!(ans = (char *)malloc(len * sizeof(char))))
		return (NULL);
	while (s[++i] != '\0')
		ans[i] = f(i, s[i]);
	ans[i] = '\0';
	return (ans);
}
