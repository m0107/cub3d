/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 06:19:59 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 06:20:03 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	rotate_left(t_game *g, double mvspd, double rtspd)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = g->pl.dirx;
	g->pl.dirx = g->pl.dirx * cos(rtspd) - g->pl.diry * sin(rtspd);
	g->pl.diry = old_dir_x * sin(rtspd) + g->pl.diry * cos(rtspd);
	old_plane_x = g->pl.plnx;
	g->pl.plnx = g->pl.plnx * cos(rtspd) - g->pl.plny * sin(rtspd);
	g->pl.plny = old_plane_x * sin(rtspd) + g->pl.plny * cos(rtspd);
	render(g);
}

void	rotate_right(t_game *g, double mvspd, double rtspd)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = g->pl.dirx;
	g->pl.dirx = g->pl.dirx * cos(-rtspd) - g->pl.diry * sin(-rtspd);
	g->pl.diry = old_dir_x * sin(-rtspd) + g->pl.diry * cos(-rtspd);
	old_plane_x = g->pl.plnx;
	g->pl.plnx = g->pl.plnx * cos(-rtspd) - g->pl.plny * sin(-rtspd);
	g->pl.plny = old_plane_x * sin(-rtspd) + g->pl.plny * cos(-rtspd);
	render(g);
}

void	exit_game(t_game *g)
{
	mlx_destroy_window(g->vars.mlx, g->vars.win);
	ft_destroy(g);
	free(g->r.zbuffer);
	printf("map freed\n\n");
	exit(0);
}
