/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    helper(t_game *game, t_rndr_sprite *r_sp, int i)
{
    r_sp->spriteX = game->sprite.pos[r_sp->spriteOrder[i]].x - game->player.posX;
    r_sp->spriteY = game->sprite.pos[r_sp->spriteOrder[i]].y - game->player.posY;
    r_sp->invDet = 1.0 / (game->player.planeX * game->player.dirY - game->player.dirX * game->player.planeY); //required for correct matrix multiplication
    r_sp->transformX = r_sp->invDet * (game->player.dirY * r_sp->spriteX - game->player.dirX * r_sp->spriteY);
    r_sp->transformY = r_sp->invDet * (-game->player.planeY * r_sp->spriteX + game->player.planeX * r_sp->spriteY); //this is actually the depth inside the screen, that what Z is in 3D
    r_sp->spriteScreenX = (int)((game->vars.screenwidth / 2) * (1 + r_sp->transformX / r_sp->transformY));
    r_sp->spriteHeight = abs((int)(game->vars.screenheight / (r_sp->transformY))); //using 'transformY' instead of the real distance prevents fisheye
    r_sp->drawStartY = -r_sp->spriteHeight / 2 + game->vars.screenheight / 2;
    if(r_sp->drawStartY < 0)
        r_sp->drawStartY = 0;
    r_sp->drawEndY = r_sp->spriteHeight / 2 + game->vars.screenheight / 2;
    if(r_sp->drawEndY >= game->vars.screenheight)
        r_sp->drawEndY = game->vars.screenheight - 1;

    r_sp->spriteWidth = abs( (int)(game->vars.screenheight / (r_sp->transformY)));
    r_sp->drawStartX = -r_sp->spriteWidth / 2 + r_sp->spriteScreenX;
    if(r_sp->drawStartX < 0)
        r_sp->drawStartX = 0;
    r_sp->drawEndX = r_sp->spriteWidth / 2 + r_sp->spriteScreenX;
    if(r_sp->drawEndX >= game->vars.screenwidth)
        r_sp->drawEndX = game->vars.screenwidth - 1;
}

void    helper_1(t_game *game, t_rndr_sprite *r_sp, int stripe, int i)
{
    int texX;
    int y;
    int d;
    int texY;
    int sp_order_tmp;
    unsigned char color[4];

    texX = (int)(256 * (stripe - (-r_sp->spriteWidth / 2 + r_sp->spriteScreenX)) * texWidth / r_sp->spriteWidth) / 256;
    if(r_sp->transformY > 0 && stripe > 0 && stripe < game->vars.screenwidth 
        && r_sp->transformY < (double)game->render.ZBuffer[stripe] + 0.6)
    {
        y = r_sp->drawStartY -1;            
        while (++y < r_sp->drawEndY) //for every pixel of the current stripe
        {
            d = (y) * 256 - game->vars.screenheight * 128 + r_sp->spriteHeight * 128; //256 and 128 factors to avoid floats
            texY = ((d * texHeight) / r_sp->spriteHeight) / 256;
            sp_order_tmp = game->sprite.pos[r_sp->spriteOrder[i]].texture;
            get_pixel_color(game->textures[sp_order_tmp], texX, texY, color);
            if ( color[1] != 0 ||  color[2] != 0 ||  color[3] != 0 )
                draw_pixel(&game->vars, stripe, y, color);
        }
}
}

void    render_sprites_helper(t_game *game, t_rndr_sprite *r_sp)
{
    int i;
    int st;
    
    i = -1;
    while (++i < game->sprite.size)
    {
	    helper(game, r_sp, i);
        st = r_sp->drawStartX -1;
        while(++st < r_sp->drawEndX)
        {
           helper_1(game, r_sp, st, i);
        }        
	}
}