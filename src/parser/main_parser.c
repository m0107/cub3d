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

void	mp_helpr(char *line, t_game *g)
{
	char	*temp;

	temp = line;
	line = remove_space(line);
	if (*line == 'R')
		res_parser(g, line);
	else if (*line == 'N' || (*line == 'S' && *(line + 1) == 'O')
		|| *line == 'W' || *line == 'E')
		tex_parser(g, line);
	else if (*line == 'F' || *line == 'C')
		color_parser(g, line);
	else if (*line == 'S')
		sprite_parser(g, line);
	else if (*line != '\n' && *line != '\0')
		map_parser(g, temp);
	else if (g->map.size > 0 && *temp != ' ')
		printf_error("Empty line in Map.\n", g);
	free(temp);
}

void	init_pars_check(t_game *g)
{
	int i;

	i = -1;
	while (++i < 9)
	{
		g->pars_check[i] = -1;
	}
	g->map.size = 0;
	g->pl.posx = -1;
	g->pl.posy = -1;
	g->sp.size = 0;
}

void	pars_check_result(t_game *g)
{
	if (g->pars_check[0] != 0)
		printf_error("Error in input, Resolution missing or double.\n", g);
	if (g->pars_check[1] != 0)
		printf_error("Error in input, North Texture missing or double.\n", g);
	if (g->pars_check[2] != 0)
		printf_error("Error in input, South Texture missing or double.\n", g);
	if (g->pars_check[3] != 0)
		printf_error("Error in input, West Texture missing or double.\n", g);
	if (g->pars_check[4] != 0)
		printf_error("Error in input, East Texture missing or double.\n", g);
	if (g->pars_check[5] != 0)
		printf_error("Error in input, Sprite missing or double.\n", g);
	if (g->pars_check[6] != 0)
		printf_error("Error in input, Floor color missing or double.\n", g);
	if (g->pars_check[7] != 0)
		printf_error("Error in input, Ceiling color missing or double.\n", g);
	if (g->pars_check[8] != 0)
		printf_error("Error in input, Map data missing or double.\n", g);
	if (g->pl.posy < 0 || g->pl.posx < 0)
		printf_error("Error in input, Player position not set.\n", g);
}

void	main_parser(t_game *g, char *filename)
{
	int		fd;
	int		t;
	char	*line;
	char	**map;

	init_pars_check(g);
	if ((fd = open(filename, O_RDONLY)) < 1)
		printf_error("invalid filepath\n", g);
	while ((t = get_next_line(fd, &line)) == 1)
		mp_helpr(line, g);
	if (t < 0)
		printf_error("get_next_line failed.\n", g);
	mp_helpr(line, g);
	g->pars_check[8]++;
	pars_check_result(g);
	check_map(g);
	close(fd);
}
