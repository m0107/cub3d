/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 23:17:28 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/09 23:17:30 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int		is_direction(char c)
{
	if ( c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	check_input_map_error(char c)
{
	if (!(c == '1' || c == '2' || c == '0' || c == ' '
	|| is_direction(c)))
		printf_error("Invalid map entry.\n");
}

void	set_player_pos(t_game *game, char c, int y)
{
	game->player.posX = (double)game->map.size + 0.5;
	game->player.posY = (double)y + 0.5;
	
}

void	map_parser(t_game *game,char *line)
{
	char	**temp_map;
	int		j;

	
	if (!(temp_map = (char **)malloc((game->map.size+1) * sizeof(char *))))
		printf_error("malloc map failed.\n");
	j = -1;
	
	printf("mohit 1\n\n");
	printf("J value: %d\n", j);
	printf("game->map.size:%d\n",game->map.size);
	while (++j < game->map.size)
		temp_map[j] = game->map.data[j];
	printf("mohit 1.5\n\n");
	if (game->map.size > 0)
		free(game->map.data);
	printf("mohit 2\n\n");
	game->map.data = temp_map;
	j = 0;
	printf("mohit\n\n");
	while (line[j] != '\0')
	{
		if (is_direction(line[j]))
		{
			line[j] = '0';
			set_player_pos(game, line[j], j);
		}
		check_input_map_error(line[j++]);
	}
	char *str = ft_strdup(line);
	game->map.data[game->map.size] = str;
	game->map.size++;
}
