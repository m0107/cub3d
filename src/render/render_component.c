/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_component.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ceiling(t_game *g, int x)
{
	int i;

	i = -1;
	while (++i < g->r.drawstart)
		my_mlx_pixel_put(&g->vars, x, i, g->vars.ceiling_color);
}

void	render_floor(t_game *g, int x)
{
	int i;

	i = g->r.drawend - 1;
	while (++i < g->vars.scn_h)
		my_mlx_pixel_put(&g->vars, x, i, g->vars.floor_color);
}

void	render_wall_helper(t_game *g, int tex_i, int i, int x)
{
	unsigned char color[4];

	get_pixel_color(g->txs[tex_i], g->r.texx, g->r.texy, color);
	draw_pixel(&g->vars, x, i, color);
}

void	render_wall(t_game *g, int x)
{
	int i;

	i = g->r.drawstart - 1;
	while (++i < g->r.drawend)
	{
		g->r.texy = (int)g->r.texpos & (TEX_HEIGHT - 1);
		g->r.texpos += g->r.step;
		if (g->r.side == 0 && g->r.raydirx < 0)
			render_wall_helper(g, 0, i, x);
		else if (g->r.side == 0 && g->r.raydirx >= 0)
			render_wall_helper(g, 1, i, x);
		else if (g->r.side == 1 && g->r.raydiry < 0)
			render_wall_helper(g, 2, i, x);
		else
			render_wall_helper(g, 3, i, x);
	}
}
