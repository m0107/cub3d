/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putchar_fd(char c, int fd)
{
	int i;

	i = write(fd, &c, 1);
	
}


void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
void	printf_error(char *error, t_game *game)
{
	perror("Error\n");
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(error, 1);
	exit(0);
}
