/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 05:51:57 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 05:51:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	mp_helpr(char * line, t_game *game)
{

		char	*temp;
		temp = line;
		line  = remove_space(line);
		if (*line == 'R')
			res_parser(game,line);
		else if (*line == 'N'|| (*line == 'S' && *(line+1) == 'O') || *line == 'W' || *line == 'E')
			tex_parser(game, line);
		else if (*line == 'F' || *line == 'C')
			color_parser(game,line);
		else if (*line == 'S')
			sprite_parser(game,line);
		else if (*line != '\n' && *line !='\0')
			map_parser(game, temp);
		else if(game->map.size > 0 && *temp != ' ')
			printf_error("Empty line in Map.\n", game);
		free(temp);
	
}

void	init_pars_check(t_game *game)
{
	int i;

	i = -1;
	while (++i < 9)
	{
		game->parsCheck[i] = -1;
	}
	game->map.size = 0;
	game->player.posX = -1;
	game->player.posY = -1;
}

void pars_check_result(t_game *game)
{

	if (game->parsCheck[0] != 0)
		printf_error("Error in input, Resolution missing or double.\n", game);
	if (game->parsCheck[1] != 0)
		printf_error("Error in input, North Texture missing or double.\n", game);
	if (game->parsCheck[2] != 0)
		printf_error("Error in input, South Texture missing or double.\n", game);
	if (game->parsCheck[3] != 0)
		printf_error("Error in input, West Texture missing or double.\n", game);
	if (game->parsCheck[4] != 0)
		printf_error("Error in input, East Texture missing or double.\n", game);
	if (game->parsCheck[5] != 0)
		printf_error("Error in input, Sprite missing or double.\n", game);
	if (game->parsCheck[6] != 0)
		printf_error("Error in input, Floor color missing or double.\n", game);
	if (game->parsCheck[7] != 0)
		printf_error("Error in input, Ceiling color missing or double.\n", game);
	if (game->parsCheck[8] != 0)
		printf_error("Error in input, Map data missing or double.\n", game);
	if (game->player.posY < 0 || game->player.posX < 0 )
			printf_error("Error in input, Player position not set.\n", game);
}

void	main_parser(t_game *game, char *filename)
{
	int		fd;
	int		t;
	char	*line;
	char	**map;

	printf("parsing starting\n");
	init_pars_check(game);
	if ((fd = open(filename, O_RDONLY)) < 1)
		printf_error("invalid filepath\n", game);
	while ((t = get_next_line(fd, &line)) == 1)
		mp_helpr(line, game);
	if	(t < 0)
		printf_error("get_next_line failed.\n", game);
	mp_helpr(line, game);
	printf("parsing done\n");
	game->parsCheck[8]++;
	pars_check_result(game);
	printf("res %d\n\n", game->vars.screenheight);
	printf("res %d\n\n", game->vars.screenwidth);
	printf("map.sprite x :%f\n\n", game->sprite.x);
	printf("map.sprite y :%f\n\n", game->sprite.y);
	check_map(game);
//	exit(0);
	close(fd);
}