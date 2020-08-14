/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 05:51:57 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 05:51:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_n_set_res(t_game *game, int screenwidth, int screenheight)
{
	if (screenwidth > 2560 || screenwidth == -942514)
		screenwidth = 2560;
	if (screenheight > 1440 || screenheight == -942514)
		screenheight = 1440;
	
	if(screenwidth <= 0 || screenheight <= -1)
		printf_error("Invalid Resolution\n");
	
	game->vars.screenheight = screenheight;
	game->vars.screenwidth = screenwidth;
}

void	res_parser(t_game *game, char *line)
{
	int	screenwidth;
	int	screenheight;
	int	loop_len;

	if (game->map.size > 0)
		printf_error("Input order incorrect.\n");
	line = line + 2;
	screenwidth = ft_atoi_cub(&line);
	screenheight = ft_atoi_cub(&line);
	while (*line != '\0' && *line != 0 )
	{
		if(*line != ' ')
			printf_error("Extra input in resolution\n");
		line++;
	}
	check_n_set_res(game, screenwidth, screenheight);
	game->parsCheck[0]++;
}
