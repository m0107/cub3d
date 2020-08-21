/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 03:27:56 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/16 03:27:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_parser(t_game *g, char *line)
{
	int i;

	if (g->map.size > 0)
		printf_error("Input order incorrect:sprite_parser.\n", g);
	if (*line == 'S')
	{
		i = 4;
		g->pars_check[5]++;
	}
	else
		printf_error("Invalid texture file", g);
	line = line + 1;
	load_texture(g->vars.mlx, remove_space(line), &g->txs[i], g);
}
