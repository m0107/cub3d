/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_component.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    render_ceiling(t_game *game, int x)
{
    int i;

    i = -1;
    while (++i < game->render.drawStart)
		my_mlx_pixel_put(&game->vars, x, i, game->vars.ceiling_color);

}

void    render_floor(t_game *game, int x)
{   
    int i;

    i = game->render.drawEnd - 1;
    while (++i < game->vars.screenheight)
		my_mlx_pixel_put(&game->vars, x, i, game->vars.floor_color);
	
}

void render_wall_helper(t_game *game, int tex_i, int i, int x)
{
    unsigned char color[4];

    get_pixel_color(game->textures[tex_i], game->render.texX, game->render.texY, color);
    draw_pixel(&game->vars, x, i, color);
}

void render_wall(t_game *game, int x)
{
    int i;

    i = game->render.drawStart - 1;
	while (++i < game->render.drawEnd)
	{
		game->render.texY = (int)game->render.texPos & (texHeight - 1);
		game->render.texPos += game->render.step;
		
		if (game->render.side == 0 && game->render.rayDirX < 0)
	        render_wall_helper(game, 0, i, x);
		else if (game->render.side == 0 && game->render.rayDirX >= 0)
            render_wall_helper(game, 1, i, x);
		else if (game->render.side == 1 && game->render.rayDirY < 0)
            render_wall_helper(game, 2, i, x);
		else 
            render_wall_helper(game, 3, i, x);
	}
}