/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:16:03 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/16 02:16:05 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_pos_north(t_game *g)
{
	g->pl.dirx = -1;
	g->pl.diry = 0;
	g->pl.plnx = 0;
	g->pl.plny = 0.66;
}

void	set_pos_south(t_game *g)
{
	g->pl.dirx = 1;
	g->pl.diry = 0;
	g->pl.plnx = 0;
	g->pl.plny = -0.66;
}

void	set_pos_east(t_game *g)
{
	g->pl.dirx = 0;
	g->pl.diry = 1;
	g->pl.plnx = 0.66;
	g->pl.plny = 0;
}

void	set_pos_west(t_game *g)
{
	g->pl.dirx = 0;
	g->pl.diry = -1;
	g->pl.plnx = -0.66;
	g->pl.plny = 0;
}
