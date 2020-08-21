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

void	resize_map(t_game *g)
{
	char	**temp_map;
	int		j;

	if (!(temp_map = (char **)malloc((g->map.size + 1) * sizeof(char *))))
		printf_error("malloc map failed.\n", g);
	j = -1;
	while (++j < g->map.size)
		temp_map[j] = g->map.data[j];
	if (g->map.size > 0)
	{
		free(g->map.data);
		g->map.data = NULL;
	}
	g->map.data = temp_map;
}

void	map_parser(t_game *g, char *line)
{
	int	j;

	j = -1;
	resize_map(g);
	while (line[++j] != '\0')
	{
		check_input_map_error(line[j], g);
		if (is_direction(line[j]))
		{
			set_player_pos(g, line[j], j);
			line[j] = '0';
		}
		else if (line[j] >= '2' && line[j] <= '4')
		{
			set_sprite_pos(g, line[j], j, g->sp.size);
			g->sp.size++;
		}
	}
	g->map.data[g->map.size] = ft_strdup(line);
	g->map.size++;
}
