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
	int i;

	if (game->map.size > 0)
		printf_error("Input order incorrect:sprite_parser.\n", game);
	if (*line == 'S')
	{
		i = 4;
		game->parsCheck[5]++;
	}
	else if (*line == 'D')
		i = 5;
	
	else if (*line == 'L')
		i = 6;
	else
		printf_error("Invalid texture file", game);
	line = line + 1;
	load_texture(game->vars.mlx, remove_space(line), &game->textures[i], game);
}

