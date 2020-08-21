/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 05:51:57 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 05:51:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	tex_parser(t_game *game, char *line)
{
	int i;
	printf("line: %s\n", line);
	printf("line _c: |%c|\n", *line);
	
	i = 0;
	if (game->map.size > 0)
		printf_error("Input order incorrect: tex_parser\n", game);
	if (*line == 'N')
		i = 0;
	else if (*line == 'S')
		i = 1;
	else if (*line == 'W')
		i = 2;
	else if (*line == 'E')
		i = 3;
	else
		printf_error("Invalid texture file", game);
	line = line + 2;
	load_texture(game->vars.mlx, remove_space(line), &game->textures[i], game);
	game->parsCheck[i + 1]++;
}

void	load_texture(void *mlx_ptr, char *filename, t_texture *res, t_game *game)
{
	int	config[3];
	res->ptr = mlx_xpm_file_to_image(mlx_ptr, filename,
			&(res->width), &(res->height));
	if (res->ptr == 0)
		printf_error("Not able to read Texture\n", game);
	config[0] = 32;
	config[1] = res->width * 4;
	config[2] = 0;
	res->data = mlx_get_data_addr(res->ptr,
			&config[0], &config[1], &config[2]);
	if (res->data == 0)
		printf_error(" Texture reading failed\n", game);
}
