/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	helper(t_game *g, t_rndr_sprite *r_sp, int i)
{
	r_sp->spritex = g->sp.pos[r_sp->spriteorder[i]].x - g->pl.posx;
	r_sp->spritey = g->sp.pos[r_sp->spriteorder[i]].y - g->pl.posy;
	r_sp->t = 1.0 /
		(g->pl.plnx * g->pl.diry - g->pl.dirx * g->pl.plny);
	r_sp->t_x = r_sp->t *
		(g->pl.diry * r_sp->spritex - g->pl.dirx * r_sp->spritey);
	r_sp->t_y = r_sp->t *
		(-g->pl.plny * r_sp->spritex + g->pl.plnx * r_sp->spritey);
	r_sp->sp_scn_x = (int)
		((g->vars.scn_w / 2) * (1 + r_sp->t_x / r_sp->t_y));
	r_sp->sp_height = abs((int)(g->vars.scn_h / (r_sp->t_y)));
	r_sp->drawstarty = -r_sp->sp_height / 2 + g->vars.scn_h / 2;
	if (r_sp->drawstarty < 0)
		r_sp->drawstarty = 0;
	r_sp->drawendy = r_sp->sp_height / 2 + g->vars.scn_h / 2;
	if (r_sp->drawendy >= g->vars.scn_h)
		r_sp->drawendy = g->vars.scn_h - 1;
	r_sp->sp_width = abs((int)(g->vars.scn_h / (r_sp->t_y)));
	r_sp->drawstartx = -r_sp->sp_width / 2 + r_sp->sp_scn_x;
	if (r_sp->drawstartx < 0)
		r_sp->drawstartx = 0;
	r_sp->drawendx = r_sp->sp_width / 2 + r_sp->sp_scn_x;
	if (r_sp->drawendx >= g->vars.scn_w)
		r_sp->drawendx = g->vars.scn_w - 1;
}

void	helper_1(t_game *g, t_rndr_sprite *r_sp, int stripe, int i)
{
	int				y;
	int				d;
	int				sp_order_tmp;
	unsigned char	color[4];

	r_sp->texx = (int)(256 * (stripe - (-r_sp->sp_width / 2 + r_sp->sp_scn_x))
		* TEX_WIDTH / r_sp->sp_width) / 256;
	if (r_sp->t_y > 0 && stripe > 0 && stripe < g->vars.scn_w
		&& r_sp->t_y < (double)g->r.zbuffer[stripe] + 0.6)
	{
		y = r_sp->drawstarty - 1;
		while (++y < r_sp->drawendy)
		{
			d = (y) * 256 - g->vars.scn_h * 128 + r_sp->sp_height * 128;
			r_sp->texy = ((d * TEX_HEIGHT) / r_sp->sp_height) / 256;
			sp_order_tmp = g->sp.pos[r_sp->spriteorder[i]].texture;
			get_pixel_color(g->txs[sp_order_tmp],
				r_sp->texx, r_sp->texy, color);
			if (color[1] != 0 || color[2] != 0 || color[3] != 0)
				draw_pixel(&g->vars, stripe, y, color);
		}
	}
}

void	render_sprites_helper(t_game *g, t_rndr_sprite *r_sp)
{
	int i;
	int st;

	i = -1;
	while (++i < g->sp.size)
	{
		helper(g, r_sp, i);
		st = r_sp->drawstartx - 1;
		while (++st < r_sp->drawendx)
		{
			helper_1(g, r_sp, st, i);
		}
	}
}
