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

void 	check_map_borders(t_game *game)
{
	int k;

	k = -1;
	while(game->map.data[0][++k] != '\0')
	{
		if(game->map.data[0][k] == '0')
			printf_error("Map not closed.\n", game);
	}
	k = -1;
	while(game->map.data[game->map.size - 1][++k] != '\0')
	{
		if(game->map.data[game->map.size - 1][k] == '0')
			printf_error("Map not closed.\n", game);
	}
	k = -1;
	while(++k < game->map.size)
	{
		if(game->map.data[k][0] == '0')
			printf_error("Map not closed.\n", game);
	}	
}

int		check_map_input(t_map map, int i, int j)
{
	if (map.data[i][j] == '0')
	{
	

	}
	return(0);
}	

void	check_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	check_map_borders(game);
	while (++i < game->map.size - 1)
	{
		j = 1;
		while (game->map.data[i][j] != '\0')
		{
			if(check_map_input(game->map, i, j))
				printf_error("Map not closed. :err1\n", game);
			j++;
		}
		printf("\n");
	}
	// exit(0);
}