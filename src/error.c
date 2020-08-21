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

void	ft_destroy(t_game *g)
{
	int i;

	i = -1;
	if (g->pars_check[1] == 0)
		mlx_destroy_image(g->vars.mlx, g->txs[0].ptr);
	if (g->pars_check[2] == 0)
		mlx_destroy_image(g->vars.mlx, g->txs[1].ptr);
	if (g->pars_check[3] == 0)
		mlx_destroy_image(g->vars.mlx, g->txs[2].ptr);
	if (g->pars_check[4] == 0)
		mlx_destroy_image(g->vars.mlx, g->txs[3].ptr);
	if (g->pars_check[5] == 0)
		mlx_destroy_image(g->vars.mlx, g->txs[4].ptr);
	if (g->pars_check[8] == 0)
	{
		while (++i < g->map.size)
			free(g->map.data[i]);
		free(g->map.data);
		if (g->sp.size > 0)
			free(g->sp.pos);
	}
}

void	printf_error(char *error, t_game *g)
{
	perror("Error\n");
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(error, 1);
	ft_destroy(g);
	exit(1);
}
