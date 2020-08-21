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

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

// if Aplple
// #include "./keys/keys_darwin.h"

// if linux
#include "./keys/keys_linux.h"

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
	int			screenwidth;
	int			screenheight;
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
}				t_map;

typedef struct s_sp_pos {
	double	x;
	double	y;
	int		texture;
}				t_sp_pos;

typedef struct s_sprite {
	t_sp_pos	*pos;
	int			size;
}				t_sprite;


typedef struct s_render {
	int		*ZBuffer;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	int		texX;
	int		texY;
	double	step;
	double	texPos;
}				t_render;

typedef struct  s_rndr_sprite {
    int		*spriteOrder;
	double	*spriteDistance;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double transformX;
	double transformY;
	int spriteScreenX;
	int spriteHeight;
	int spriteWidth;
	int drawStartY;
	int drawEndY;
	int drawStartX;
	int drawEndX;


}               t_rndr_sprite;



typedef struct  s_game {
	int			parsCheck[9];
    t_player	player;
	t_texture	textures[7];
	t_vars		vars;
	t_map		map;
	t_sprite	sprite;
	t_render	render;
}               t_game;

typedef struct	s_p_order {
	double	first;
	int		second;
}				t_p_order;

void	main_parser(t_game *game, char *filename);

void	map_parser(t_game *game, char *line);
void	res_parser(t_game *game, char *line);
void	check_n_set_res(t_game *game,int screenWidth, int screenHeight);

void	tex_parser(t_game *game, char *line);
void	load_texture(void *mlx_ptr, char *filename, t_texture *res, t_game *game);

void	color_parser(t_game *game, char *line);
void	sprite_parser(t_game *game, char *line);


int		checkno_cub(long ans, int sign);
int		ft_atoi_cub(char **str);

char	*remove_space(char *line);

void	check_map(t_game *game);
void	printf_error(char *error, t_game *game);

void	set_pos_north(t_game *game);
void	set_pos_south(t_game *game);
void	set_pos_east(t_game *game);
void	set_pos_west(t_game *game);

void	render(t_game *game);
void	render_start(t_game *game, int x);
void    render_start_init(t_game *game);
void	render_init(t_game *game, int x);
void	dda(t_game *game);
void    render_ceiling(t_game *game, int x);
void    render_floor(t_game *game, int x);
void	render_wall(t_game *game, int x);
void	render_sprites(t_game *game);
void	render_sprites_helper(t_game *game, t_rndr_sprite *rndr_sprites);




void	draw_pixel(t_vars *vars, unsigned int x, unsigned int y, unsigned char color[4]);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	get_pixel_color(t_texture texture, int x, int y, unsigned char *result);

#endif