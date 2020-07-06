/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 05:16:30 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/05 08:52:48 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int temp)
{
	int		ans;
	long	n;

	ans = 0;
	n = temp;
	if (n < 0)
	{
		n = -n;
		ans++;
	}
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		ans++;
	}
	return (ans);
}

static char	*handleintmin(char *ans)
{
	ans[0] = '-';
	ans[1] = '2';
	ans[2] = '1';
	ans[3] = '4';
	ans[4] = '7';
	ans[5] = '4';
	ans[6] = '8';
	ans[7] = '3';
	ans[8] = '6';
	ans[9] = '4';
	ans[10] = '8';
	ans[11] = '\0';
	return (ans);
}

char		*ft_itoa(int n)
{
	char	*ans;
	int		i;
	int		len;
	int		temp;

	temp = 0;
	i = 0;
	len = numlen(n);
	if (!(ans = (char *)malloc(len + 1 * sizeof(char))))
		return (NULL);
	if (n < 0)
	{
		if (n == -2147483648)
			return (handleintmin(ans));
		ans[i] = '-';
		n = -n;
		temp = -1;
	}
	while (i < (len + temp))
	{
		ans[len - ++i] = (n % 10) + 48;
		n = n / 10;
	}
	ans[len] = '\0';
	return (ans);
}
