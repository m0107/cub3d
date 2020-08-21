/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_start_init(t_game *g)
{
	g->r.lineheight = (int)(g->vars.scn_h / g->r.pwd);
	g->r.drawstart = -g->r.lineheight / 2 + g->vars.scn_h / 2;
	if (g->r.drawstart < 0)
		g->r.drawstart = 0;
	g->r.drawend = g->r.lineheight / 2 + g->vars.scn_h / 2;
	if (g->r.drawend >= g->vars.scn_h)
		g->r.drawend = g->vars.scn_h - 1;
	if (g->r.side == 0)
		g->r.wallx = g->pl.posy + g->r.pwd * g->r.raydiry;
	else
		g->r.wallx = g->pl.posx + g->r.pwd * g->r.raydirx;
	g->r.wallx -= floor((g->r.wallx));
	g->r.texx = (int)(g->r.wallx * (double)(TEX_WIDTH));
	if (g->r.side == 0 && g->r.raydirx > 0)
		g->r.texx = TEX_WIDTH - g->r.texx - 1;
	if (g->r.side == 1 && g->r.raydiry < 0)
		g->r.texx = TEX_WIDTH - g->r.texx - 1;
	g->r.step = 1.0 * TEX_HEIGHT / g->r.lineheight;
	g->r.texpos = (g->r.drawstart - g->vars.scn_h / 2 +
		g->r.lineheight / 2) * g->r.step;
}

void	render_start(t_game *g, int x)
{
	render_start_init(g);
	render_ceiling(g, x);
	render_wall(g, x);
	render_floor(g, x);
	g->r.zbuffer[x] = g->r.pwd;
}

void	render(t_game *g)
{
	int x;

	x = -1;
	while (++x < g->vars.scn_w)
	{
		render_init(g, x);
		dda(g);
		if (g->r.pwd <= 0.0000001f)
			return ;
		render_start(g, x);
	}
	render_sprites(g);
	mlx_put_image_to_window(g->vars.mlx, g->vars.win,
		g->vars.img.img, 0, 0);
}
