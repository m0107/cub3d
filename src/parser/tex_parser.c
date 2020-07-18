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
// Return 0 if resolution is fine, otherwise Error no;
int	tex_parser(t_game *game, char *line)
{
	int i;
	
	i = 0;
	if(*line == 'N')
		i = 0;
	else if(*line == 'S')
		i = 1;
	else if(*line == 'W')
		i = 2;
	else if(*line == 'E')
		i = 3;
	else
		return (-2);
	line = line + 2;
	return(load_texture(game->vars.mlx, remove_space(line), &game->textures[i]));
}

// Return 0 if resolution is fine, otherwise Error no;
int	load_texture(void *mlx_ptr, char *filename, t_texture *res)
{
	printf("filename: %s\n", filename);
	int			config[3];
	
	res->ptr = mlx_xpm_file_to_image(mlx_ptr, filename,
			&(res->width), &(res->height));
	if (res->ptr == 0){
		printf("Not able to read\n");
		return (-2);
	}
	config[0] = 32;
	config[1] = res->width * 4;
	config[2] = 0;
	res->data = mlx_get_data_addr(res->ptr,
			&config[0], &config[1], &config[2]);
	if (res->data == 0){
		printf("reading failed\n");
		return (-2);
	}
	return 0;
}
