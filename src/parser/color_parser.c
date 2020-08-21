/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 05:51:57 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 05:51:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		create_trgb(int t, int color[], t_game *game)
{
	if (color[0] > 255 || color[1] > 255 || color[2] > 255
	|| color[0] < 0 || color[1] < 0 || color[2] <0)
		printf_error("color range should be between 0 and 255\n", game);
	return (t << 24 | color[0] << 16 | color[1] << 8 | color[2]);
}

char	*check_comma(char *line, t_game *game)
{
	line = remove_space(line);
	if (*line != ',')
		printf_error("Color should be seperated by comma.\n", game);
	line++;
	return (line);
}

void	cp_helpr(char *line, t_game *game, int isfloor)
{
	int color[3];

	color[0] = ft_atoi_cub(&line);
	line = check_comma(line, game);
	color[1] = ft_atoi_cub(&line);
	line = check_comma(line, game);
	color[2] = ft_atoi_cub(&line);
	if (isfloor)
		game->vars.floor_color = create_trgb(0, color, game);
	else
		game->vars.ceiling_color = create_trgb(0, color, game);
	while (*line != '\0' && *line != 0)
	{
		if(*line++ != ' ')
			printf_error("Extra input in colors\n", game);
	}
}

void	check_color_line(char *line, t_game *game)
{
	int i;
	int comma;

	i = 0;
	comma = 0;
	while (line[++i] != '\0')
	{
		if (line[i] < '0' || line[i] > '9')
		{
			if (line[i] == ',')
				comma++;
			else if (line[i] != ' ')
				printf_error("Invalid color format.\n", game);
		}
	}
	if (comma != 2)
		printf_error("Invlaid no of commas in color.\n", game);
}

void	color_parser(t_game *game, char *line)
{
	check_color_line(line, game);
	if (game->map.size > 0)
		printf_error("Input order incorrect:color_parser.\n", game);
	if (*line++ == 'F')
	{
		cp_helpr(line, game, 1);
		game->parsCheck[6]++;
	}
	else
	{
		cp_helpr(line, game, 0);
		game->parsCheck[7]++;
	}
	
}
