/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:16:03 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/16 02:16:05 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_pos_north(t_game *game)
{
	game->player.dirX = -1; 
	game->player.dirY = 0; //initial direction vector
	game->player.planeX = 0; 
	game->player.planeY = 0.66; //the 2d raycaster version of camera plane
}

void	set_pos_south(t_game *game)
{
	game->player.dirX = 1; 
	game->player.dirY = 0; //initial direction vector
	game->player.planeX = 0; 
	game->player.planeY = -0.66; //the 2d raycaster version of camera plane		
}

void	set_pos_east(t_game *game)
{

	game->player.dirX = 0; 
	game->player.dirY = 1; //initial direction vector
	game->player.planeX = 0.66; 
	game->player.planeY = 0; //the 2d raycaster version of camera plane		
}

void	set_pos_west(t_game *game)
{
	game->player.dirX = 0; 
	game->player.dirY = -1; //initial direction vector
	game->player.planeX = -0.66; 
	game->player.planeY = 0; //the 2d raycaster version of camera plane		
}