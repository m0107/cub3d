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

void	check_input_map_error(char c, t_game *game)
{
	printf("Invalid entry: %c\n", c);
	if (!(c == '1' || c == '2' || c == '0' || c == ' '
	|| is_direction(c)))
		printf_error("Invalid map entry.\n", game);
}

void	set_player_pos(t_game *game, char c, int y)
{
	if (game->player.posX != -1 || game->player.posX != -1)
		printf_error("Player position invalid", game);
	game->player.posX = (double)game->map.size + 0.5;
	game->player.posY = (double)y + 0.5;
	if (c == 'N')
		set_pos_north(game);
	else if (c =='S')
		set_pos_south(game);
	else if (c =='E')
		set_pos_east(game);
	else if (c =='W')
		set_pos_west(game);

	
}
void	set_sprite_pos(t_game *game, char c, int y, int i)
{
	t_sp_pos *temp_sp_pos;
	int j;
	printf("set_sprite_pos\n");
	if (!(temp_sp_pos = (t_sp_pos *)malloc((i+1) * sizeof(temp_sp_pos))))
		printf_error("malloc sprite failed.\n", game);
	j = -1;	
	while (++j < i)
		temp_sp_pos[j] = game->sprite.pos[j];
	
	if (i > 0)
		free(game->sprite.pos);
	
	game->sprite.pos = temp_sp_pos;
	game->sprite.pos[i].x = (double)(game->map.size)+0.5;
	game->sprite.pos[i].y = (double)(y)+0.5;	
	j = -1;
	while (++j <= i) {
		printf(" game->sprite.pos[%d].x :%f\n", j, game->sprite.pos[j].x);
		printf(" game->sprite.pos[%d].y :%f\n", j, game->sprite.pos[j].y);	
	}
}

void	map_parser(t_game *game,char *line)
{
	char	**temp_map;
	int		j;
	
	printf("line: %s\n", line);
	if (!(temp_map = (char **)malloc((game->map.size+1) * sizeof(char *))))
		printf_error("malloc map failed.\n", game);
	j = -1;	
	while (++j < game->map.size)
		temp_map[j] = game->map.data[j];
	if (game->map.size > 0)
		free(game->map.data);
	game->map.data = temp_map;
	j = -1;

	while (line[++j] != '\0')
	{
		check_input_map_error(line[j], game);
		if (is_direction(line[j]))
		{
			set_player_pos(game, line[j], j);
			line[j] = '0';
		}
		else if (line[j] == '2')
		{
			printf("2 detected.\n");
			set_sprite_pos(game, line[j],j, game->sprite.size );
			line[j] = '2';
			game->sprite.size++;
		}
	}
	printf("game->sprite.size  : %d\n", game->sprite.size );
	char *str = ft_strdup(line);
	game->map.data[game->map.size] = str;
	game->map.size++;
}
