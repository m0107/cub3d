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

void	sprite_parser(t_game *game, char *line)
{
	
	if (game->map.size > 0)
		printf_error("Input order incorrect.\n", game);

	line = line + 1;
	load_texture(game->vars.mlx, remove_space(line), &game->sprite.texture, game);
	game->parsCheck[5]++;
}

