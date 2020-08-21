/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    render_start_init(t_game *game)
{

	game->render.lineHeight = (int)(game->vars.screenheight / game->render.perpWallDist);
	game->render.drawStart = -game->render.lineHeight / 2 + game->vars.screenheight / 2;
	if(game->render.drawStart < 0)
		game->render.drawStart = 0;
	game->render.drawEnd = game->render.lineHeight / 2 + game->vars.screenheight / 2;
	if(game->render.drawEnd >= game->vars.screenheight)
		game->render.drawEnd = game->vars.screenheight - 1;
	if (game->render.side == 0) game->render.wallX = game->player.posY + game->render.perpWallDist * game->render.rayDirY;
	else          game->render. wallX = game->player.posX + game->render.perpWallDist * game->render.rayDirX;
	game->render.wallX -= floor((game->render.wallX));

	//x coordinate on the texture
	game->render.texX = (int)(game->render.wallX * (double)(texWidth));
	if(game->render.side == 0 && game->render.rayDirX > 0)
        game->render.texX = texWidth - game->render.texX - 1;
	if(game->render.side == 1 && game->render.rayDirY < 0)
        game->render.texX = texWidth - game->render.texX - 1;
	game->render.step = 1.0 * texHeight / game->render.lineHeight;
	game->render.texPos = (game->render.drawStart - game->vars.screenheight / 2 + game->render.lineHeight / 2) * game->render.step;
	
}

void	render_start(t_game *game, int x)
{
    
    render_start_init(game);
    render_ceiling(game, x);
    render_wall(game, x);
	render_floor(game, x);
    game->render.ZBuffer[x] = game->render.perpWallDist; //perpendicular distance is used
}

void	render(t_game *game)
{
	int x;

	x = -1;
	while (++x < game->vars.screenwidth) 
	{
		render_init(game, x);
		dda(game);
        if (game->render.perpWallDist <= 0.0000001f)
		    return;
		render_start(game, x);
	}
	render_sprites(game);
    printf("drawing finished\n\n");
	int e;
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->vars.img.img, 0, 0);
	
	printf("rendering done\n\n");
}