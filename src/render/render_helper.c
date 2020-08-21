/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_init_helper(t_game *g)
{
	if (g->r.raydirx < 0)
	{
		g->r.stepx = -1;
		g->r.sidedistx = (g->pl.posx - g->r.mapx) * g->r.deltadistx;
	}
	else
	{
		g->r.stepx = 1;
		g->r.sidedistx = (g->r.mapx + 1.0 - g->pl.posx) * g->r.deltadistx;
	}
	if (g->r.raydiry < 0)
	{
		g->r.stepy = -1;
		g->r.sidedisty = (g->pl.posy - g->r.mapy) * g->r.deltadisty;
	}
	else
	{
		g->r.stepy = 1;
		g->r.sidedisty = (g->r.mapy + 1.0 - g->pl.posy) * g->r.deltadisty;
	}
}

void	render_init(t_game *g, int x)
{
	g->r.camerax = 2 * x / (double)g->vars.scn_w - 1;
	g->r.raydirx = g->pl.dirx + g->pl.plnx * g->r.camerax;
	g->r.raydiry = g->pl.diry + g->pl.plny * g->r.camerax;
	g->r.mapx = (int)(g->pl.posx);
	g->r.mapy = (int)(g->pl.posy);
	g->r.deltadistx = fabs(1 / g->r.raydirx);
	g->r.deltadisty = fabs(1 / g->r.raydiry);
	g->r.hit = 0;
	render_init_helper(g);
}

void	dda(t_game *g)
{
	while (g->r.hit == 0)
	{
		if (g->r.sidedistx < g->r.sidedisty)
		{
			g->r.sidedistx += g->r.deltadistx;
			g->r.mapx += g->r.stepx;
			g->r.side = 0;
		}
		else
		{
			g->r.sidedisty += g->r.deltadisty;
			g->r.mapy += g->r.stepy;
			g->r.side = 1;
		}
		if (g->map.data[g->r.mapx][g->r.mapy] == '1')
			g->r.hit = 1;
	}
	if (g->r.side == 0)
		g->r.pwd = (g->r.mapx - g->pl.posx +
			(1 - g->r.stepx) / 2) / g->r.raydirx;
	else
		g->r.pwd = (g->r.mapy - g->pl.posy +
			(1 - g->r.stepy) / 2) / g->r.raydiry;
}
