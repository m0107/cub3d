/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sort(t_p_order *sprites, int amount)
{
	int		i;
	int		j;
	double	tempx;
	int		tempy;

	i = -1;
	while (++i < amount - 1)
	{
		j = -1;
		while (++j < amount - i - 1)
		{
			if (sprites[j].first > sprites[j + 1].first)
			{
				tempx = sprites[j].first;
				sprites[j].first = sprites[j + 1].first;
				sprites[j + 1].first = tempx;
				tempy = sprites[j].second;
				sprites[j].second = sprites[j + 1].second;
				sprites[j + 1].second = tempy;
			}
		}
	}
}

void	sort_sprites(t_game *g, t_rndr_sprite *rndr_sprites)
{
	t_p_order	*sprites;
	int			i;
	int			j;

	sprites = (t_p_order *)malloc((g->sp.size) * sizeof(t_p_order));
	i = -1;
	while (++i < g->sp.size)
	{
		sprites[i].first = rndr_sprites->sp_dist[i];
		sprites[i].second = rndr_sprites->spriteorder[i];
	}
	sort(sprites, g->sp.size);
	i = -1;
	while (++i < g->sp.size)
	{
		rndr_sprites->sp_dist[i] =
			sprites[g->sp.size - i - 1].first;
		rndr_sprites->spriteorder[i] =
			sprites[g->sp.size - i - 1].second;
	}
	free(sprites);
}

void	render_sprites(t_game *g)
{
	int				i;
	t_rndr_sprite	r_sp;

	if (!(r_sp.spriteorder = (int *)malloc((g->sp.size) * sizeof(int))))
		printf_error("malloc spriteorder failed.\n", g);
	if (!(r_sp.sp_dist = (double *)malloc((g->sp.size) * sizeof(double))))
		printf_error("malloc spriteorder failed.\n", g);
	i = -1;
	while (++i < g->sp.size)
	{
		r_sp.spriteorder[i] = i;
		r_sp.sp_dist[i] = ((g->pl.posx - g->sp.pos[i].x)
			* (g->pl.posx - g->sp.pos[i].x)
			+ (g->pl.posy - g->sp.pos[i].y)
			* (g->pl.posy - g->sp.pos[i].y));
	}
	sort_sprites(g, &r_sp);
	render_sprites_helper(g, &r_sp);
	free(r_sp.spriteorder);
	free(r_sp.sp_dist);
}
