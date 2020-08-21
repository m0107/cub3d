/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 00:24:11 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/16 00:24:15 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	convert_map(t_game *g, char to_change, char new_char)
{
	int i;
	int j;

	i = -1;
	while (++i < g->map.size)
	{
		j = -1;
		while (g->map.data[i][++j] != '\0')
		{
			if (g->map.data[i][j] == to_change)
				g->map.data[i][j] = new_char;
		}
	}
}

int		is_boundary(t_game *g, int i, int j)
{
	if (i == 0 || i == g->map.size - 1 ||
		g->map.data[i][j + 1] == '\0')
		return (1);
	else if (g->map.data[i + 1][j] == ' ' || g->map.data[i][j + 1] == ' ' ||
		g->map.data[i - 1][j] == ' ' || g->map.data[i][j - 1] == ' ')
		return (1);
	return (0);
}

void	check(t_game *g, int i, int j)
{
	if (g->map.data[i][j] == '1' || g->map.data[i][j] == '8'
		|| g->map.data[i][j] == '9')
		return ;
	else if (is_boundary(g, i, j))
		printf_error("Map is not closed.", g);
	if (g->map.data[i][j] == '2')
		g->map.data[i][j] = '9';
	if (g->map.data[i][j] == '0')
		g->map.data[i][j] = '8';
	check(g, i + 1, j);
	check(g, i, j + 1);
	check(g, i - 1, j);
	check(g, i, j - 1);
}

void	check_map(t_game *g)
{
	check(g, (int)g->pl.posx + 0.5, (int)g->pl.posy + 0.5);
	convert_map(g, '8', '0');
	convert_map(g, '9', '2');
}
