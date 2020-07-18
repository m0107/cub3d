/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 05:51:57 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 05:51:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// F 220,100,0

#include "../cub3d.h"
// Return 0 if resolution is fine, otherwise Error no;

int		create_trgb(int t, int r, int g, int b)
{
	printf("Debug:  r: %d g: %d b: %d\n\n", r,g,b);
	return(t << 24 | r << 16 | g << 8 | b);
}


int		color_parser(t_game *game, char *line)
{
	
	int r;
	int g;
	int b;
	int loop_len;

	if(*line++ == 'F')
	{
		r = ft_atoi_cub(&line);
		line++;
		g = ft_atoi_cub(&line);
		line++;
		b = ft_atoi_cub(&line);
		game->vars.floor_color = create_trgb(0,r,g,b);
		printf("FLOOR color R:%d G:%d B:%d \n\n", r,g,b);
	}else
	{
		r = ft_atoi_cub(&line);
		line++;
		g = ft_atoi_cub(&line);
		line++;
		b = ft_atoi_cub(&line);
		game->vars.ceiling_color = create_trgb(0,r,g,b);
		printf("Ceiling color R:%d G:%d B:%d \n\n", r,g,b);
	}
	return (0);
}