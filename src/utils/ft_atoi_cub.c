/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 02:52:57 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 02:53:03 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	checkno_cub(long ans, int sign)
{
	if (sign > 0 && ans > 2147483647)
		return (-942514);
	else if (sign < 0 && ans > 2147483648)
		return (0);
	return (ans * sign);
}

int	ft_atoi_cub(char **str)
{
	long	sign;
	long	ans;

	ans = -1;
	sign = 1;
	while (**str == '\t' || **str == '\n' || **str == '\v'
			|| **str == '\f' || **str == '\r' || **str == ' ')
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	if (**str >= '0' && **str <= '9')
		ans = 0;
	while (**str >= '0' && **str <= '9')
	{
		ans = ans * 10 + (**str - 48);
		if (ans > 21474836470)
			break ;
		(*str)++;
	}
	return (checkno_cub(ans, sign));
}
