/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 01:50:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/14 01:51:07 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void sort(t_p_order *sprites, int amount)
{
    int i;
    int j; 
	double	tempx;
    int	tempy;


    i = -1;
    while (++i < amount-1) 
	{
        j = -1;
        while (++j < amount-i-1)  
        {
				if (sprites[j].first > sprites[j+1].first) 
				{			
					tempx = sprites[j].first;
					sprites[j].first = sprites[j + 1].first;
					sprites[j +1].first = tempx;
					tempy = sprites[j].second;
					sprites[j].second= sprites[j + 1].second;
					sprites[j +1].second= tempy;
				}
		}
	}
}

void sortSprites(t_game *game, t_rndr_sprite *rndr_sprites)
{
    t_p_order   *sprites;
    int         i;
	int         j;

    sprites = (t_p_order *)malloc((game->sprite.size) * sizeof(t_p_order));
    i = -1;
    while (++i < game->sprite.size)
    {
        sprites[i].first = rndr_sprites->spriteDistance[i];
        sprites[i].second = rndr_sprites->spriteOrder[i];
    }
    sort(sprites, game->sprite.size);
	for(int i = 0; i < game->sprite.size; i++) {
        rndr_sprites->spriteDistance[i] = sprites[game->sprite.size - i - 1].first;
        rndr_sprites->spriteOrder[i] = sprites[game->sprite.size - i - 1].second;
    }
    free(sprites);
}

void    render_sprites(t_game *game)
{
    int i;
    t_rndr_sprite rndr_sprites;

	if (!(rndr_sprites.spriteOrder = (int *)malloc((game->sprite.size) * sizeof(int))))
		printf_error("malloc spriteOrder failed.\n", game);
	if (!(rndr_sprites.spriteDistance = (double *)malloc((game->sprite.size) * sizeof(double))))
		printf_error("malloc spriteOrder failed.\n", game);
	i = -1;
    while (++i < game->sprite.size)
    {
      rndr_sprites.spriteOrder[i] = i;
      rndr_sprites.spriteDistance[i] = sqrt(((game->player.posX - game->sprite.pos[i].x) * (game->player.posX - game->sprite.pos[i].x) + (game->player.posY - game->sprite.pos[i].y) * (game->player.posY - game->sprite.pos[i].y))); //sqrt not taken, unneeded
    }
    sortSprites(game, &rndr_sprites);
    render_sprites_helper(game, &rndr_sprites);
	free(rndr_sprites.spriteOrder);
	free(rndr_sprites.spriteDistance);	
}