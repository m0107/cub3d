/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void render_init(t_game *game, int x)
{
	game->render.cameraX = 2 * x / (double)game->vars.screenwidth - 1; //x-coordinate in camera space
	game->render.rayDirX = game->player.dirX + game->player.planeX * game->render.cameraX;
	game->render.rayDirY = game->player.dirY + game->player.planeY * game->render.cameraX;
	//which box of the map we're in
	game->render.mapX = (int)(game->player.posX);
	game->render.mapY = (int)(game->player.posY);


	//length of ray from one x or y-side to next x or y-side
	game->render.deltaDistX = fabs(1 / game->render.rayDirX);
	game->render.deltaDistY = fabs(1 / game->render.rayDirY);

	game->render.hit = 0; //was there a wall hit?
	if(game->render.rayDirX < 0) {
		game->render.stepX = -1;
		game->render.sideDistX = (game->player.posX - game->render.mapX) * game->render.deltaDistX;
	}else {
		game->render.stepX = 1;
		game->render.sideDistX = (game->render.mapX + 1.0 - game->player.posX) * game->render.deltaDistX;
	}
	if(game->render.rayDirY < 0) {
		game->render.stepY = -1;
		game->render.sideDistY = (game->player.posY - game->render.mapY) * game->render.deltaDistY;
	}else {
		game->render.stepY = 1;
		game->render.sideDistY = (game->render.mapY + 1.0 - game->player.posY) * game->render.deltaDistY;
	}
}

void	dda(t_game *game)
{
	while (game->render.hit == 0) 
	{
		if (game->render.sideDistX < game->render.sideDistY) {
			game->render.sideDistX += game->render.deltaDistX;
			game->render.mapX += game->render.stepX;
			game->render.side = 0;
		} else {
			game->render.sideDistY += game->render.deltaDistY;
			game->render.mapY += game->render.stepY;
			game->render.side = 1;
		}
		//Check if ray has hit a wall
		if(game->map.data[game->render.mapX][game->render.mapY] == '1')
			game->render.hit = 1;
		
	}
	if(game->render.side == 0) game->render.perpWallDist = (game->render.mapX - game->player.posX + (1 - game->render.stepX) / 2) / game->render.rayDirX;
	else          game->render.perpWallDist = (game->render.mapY - game->player.posY + (1 - game->render.stepY) / 2) / game->render.rayDirY;
}