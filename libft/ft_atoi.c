/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:21:57 by mgupta            #+#    #+#             */
/*   Updated: 2019/11/05 04:44:20 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	checkno(long ans, int sign)
{
	if (sign > 0 && ans > 2147483647)
		return (-1);
	else if (sign < 0 && ans > 2147483648)
		return (0);
	return (ans * sign);
}

int	ft_atoi(const char *str)
{
	long	sign;
	long	ans;

	ans = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		ans = ans * 10 + (*str - 48);
		if (ans > 21474836470)
			break ;
		str++;
	}
	return (checkno(ans, sign));
}
