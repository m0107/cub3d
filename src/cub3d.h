/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 00:56:09 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 01:00:39 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

#define texWidth 64
#define texHeight 64

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include "../libft/libft.h"
#include "../gnl/get_next_line.h"

typedef struct  s_player {
	// double posX = 22, posY = 12;  //x and y start position
	// double dirX = -1, dirY = 0; //initial direction vector
	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
    double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
}               t_player;


typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_vars {
	int			screenWidth;
	int			screenHeight;
	int			floor_color;
	int			ceiling_color;
	void        *mlx;
	void        *win;
	t_data 		img;
}               t_vars;

typedef struct	s_texture
{
	int				width;
	int				height;
	char			*filename;
	void			*ptr;
	char			*data;
}				t_texture;

typedef struct	s_map {
	char 		**data;
	int			size;
	int			read; // 0:not started 1:reading 2:done
}				t_map;

typedef struct  s_game {
    t_player	player;
	t_texture	textures[4];
	t_vars		vars;
	t_map		map;
}               t_game;

void	main_parser(t_game *game, char *filename);

char	**map_parser(char *line, int *i, char **map);
int		res_parser(t_game *game, char *line);
int		check_n_set_res(t_game *game,int screenWidth, int screenHeight);

int		tex_parser(t_game *game, char *line);
int		load_texture(void *mlx_ptr, char *filename, t_texture *res);

int		color_parser(t_game *game, char *line);


int		checkno_cub(long ans, int sign);
int		ft_atoi_cub(char **str);
char	*remove_space(char *line);

#endif