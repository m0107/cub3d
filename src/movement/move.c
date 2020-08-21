/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 06:19:59 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 06:20:03 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	move_up(t_game *g, double mvspd)
{
	int x_map;
	int	y_map;

	x_map = (int)((g->pl.posx + g->pl.dirx * mvspd));
	y_map = (int)(g->pl.posy);
	if (g->map.data[x_map][y_map] == '0')
		g->pl.posx += g->pl.dirx * mvspd;
	if (g->map.data[(int)(g->pl.posx)]
		[(int)((g->pl.posy + g->pl.diry * mvspd))] == '0')
		g->pl.posy += g->pl.diry * mvspd;
	render(g);
}

void	move_down(t_game *g, double mvspd)
{
	if (g->map.data[(int)(g->pl.posx - g->pl.dirx * mvspd)]
		[(int)g->pl.posy] == '0')
		g->pl.posx -= g->pl.dirx * mvspd;
	if (g->map.data[(int)g->pl.posx]
		[(int)(g->pl.posy - g->pl.diry * mvspd)] == '0')
		g->pl.posy -= g->pl.diry * mvspd;
	render(g);
}

void	move_right(t_game *g, double mvspd)
{
	double rtspd;
	double old_dir_x;
	double tempx;
	double tempy;

	rtspd = 1.5708;
	old_dir_x = g->pl.dirx;
	tempx = g->pl.dirx * cos(-rtspd) - g->pl.diry * sin(-rtspd);
	tempy = old_dir_x * sin(-rtspd) + g->pl.diry * cos(-rtspd);
	if (g->map.data[(int)(g->pl.posx + tempx * mvspd)]
		[(int)g->pl.posy] == '0')
		g->pl.posx += tempx * mvspd;
	if (g->map.data[(int)g->pl.posx]
		[(int)(g->pl.posy + tempy * mvspd)] == '0')
		g->pl.posy += tempy * mvspd;
	render(g);
}

void	move_left(t_game *g, double mvspd)
{
	double rtspd;
	double old_dir_x;
	double tempx;
	double tempy;

	rtspd = -1.5708;
	old_dir_x = g->pl.dirx;
	tempx = g->pl.dirx * cos(rtspd) - g->pl.diry * sin(rtspd);
	tempy = old_dir_x * sin(rtspd) + g->pl.diry * cos(rtspd);
	if (g->map.data[(int)(g->pl.posx - tempx * mvspd)]
		[(int)g->pl.posy] == '0')
		g->pl.posx -= tempx * mvspd;
	if (g->map.data[(int)g->pl.posx]
		[(int)(g->pl.posy - tempy * mvspd)] == '0')
		g->pl.posy -= tempy * mvspd;
	render(g);
}
