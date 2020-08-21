/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 23:17:28 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/09 23:17:30 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		is_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	check_input_map_error(char c, t_game *g)
{
	if (!(c == '1' || c == '2' || c == '0' || c == ' '
	|| is_direction(c)))
	{
		printf("char: |%c|\n", c);
		printf_error("Invalid map entry.\n", g);
	}
}

void	set_player_pos(t_game *g, char c, int y)
{
	if (g->pl.posx != -1 || g->pl.posx != -1)
		printf_error("Player position invalid", g);
	g->pl.posx = (double)g->map.size + 0.5;
	g->pl.posy = (double)y + 0.5;
	if (c == 'N')
		set_pos_north(g);
	else if (c == 'S')
		set_pos_south(g);
	else if (c == 'E')
		set_pos_east(g);
	else if (c == 'W')
		set_pos_west(g);
}

void	set_sprite_pos(t_game *g, char c, int y, int i)
{
	t_sp_pos	*p;
	int			j;

	if (!(p = (t_sp_pos *)malloc((i + 1) * sizeof(t_sp_pos))))
		printf_error("malloc sprite failed.\n", g);
	j = -1;
	while (++j < i)
		p[j] = g->sp.pos[j];
	if (i > 0)
		free(g->sp.pos);
	g->sp.pos = p;
	g->sp.pos[i].x = (double)(g->map.size + 0.5);
	g->sp.pos[i].y = (double)y + 0.5;
	g->sp.pos[i].texture = ((int)c - 46);
}
