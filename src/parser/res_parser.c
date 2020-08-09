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

// Return 0 if resolution is fine, otherwise Error no;
int check_n_set_res(t_game *game,int screenWidth, int screenHeight)
{
	if(screenWidth > 2560)	screenWidth = 2560;
	if(screenHeight > 1440) screenHeight = 1440;
	if(screenHeight <= 0 || screenHeight <= 0) 
		return (-1);
	game->vars.screenHeight = screenHeight;
	game->vars.screenWidth = screenWidth;
	return (0);
}

// Resolution parser Return 0 if resolution is fine, otherwise Error no;
int	res_parser(t_game *game, char *line)
{
	int	screenWidth;
	int	screenHeight;
	int	loop_len;

	line = line + 2;
	screenWidth = ft_atoi_cub(&line);
	screenHeight = ft_atoi_cub(&line);
	return (check_n_set_res(game, screenWidth, screenHeight));
}
