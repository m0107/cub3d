/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 23:14:34 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/05 04:43:09 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		charcount(char const *s, char c)
{
	int ans;

	ans = 0;
	while (*s)
	{
		if (*s == c)
			ans++;
		s++;
	}
	return (ans);
}

char	**returnans(char **ans, int i)
{
	ans[i] = NULL;
	return (ans);
}

char	**ft_split(char const *s, char c)
{
	char	**ans;
	int		count;
	int		i;
	int		j;

	i = 0;
	if (!(ans = (char **)malloc(sizeof(char *) * (charcount(s, c) + 2))))
		return (NULL);
	while (*s)
	{
		count = 0;
		j = 0;
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		while (*s != '\0' && *s != c && s++)
			count++;
		if (!(ans[i] = (char *)malloc(count + 1)))
			return (NULL);
		while (count > 0)
			ans[i][j++] = *(s - count--);
		ans[i++][j] = '\0';
	}
	return (returnans(ans, i));
}
