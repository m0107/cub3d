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

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "../gnl/get_next_line.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "./keys/keys_linux.h"

typedef struct	s_player
{
	double posx;
	double posy;
	double dirx;
	double diry;
	double plnx;
	double plny;
}				t_player;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars
{
	int		scn_w;
	int		scn_h;
	int		floor_color;
	int		ceiling_color;
	void	*mlx;
	void	*win;
	t_data	img;
}				t_vars;

typedef struct	s_texture
{
	int				width;
	int				height;
	char			*filename;
	void			*ptr;
	char			*data;
}				t_texture;

typedef struct	s_map
{
	char	**data;
	int		size;
}				t_map;

typedef struct	s_sp_pos
{
	double	x;
	double	y;
	int		texture;
}				t_sp_pos;

typedef struct	s_sprite
{
	t_sp_pos	*pos;
	int			size;
}				t_sprite;

typedef struct	s_render
{
	int		*zbuffer;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	pwd;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
}				t_render;

typedef struct	s_rndr_sprite
{
	int		*spriteorder;
	double	*sp_dist;
	double	spritex;
	double	spritey;
	double	t;
	double	t_x;
	double	t_y;
	int		sp_scn_x;
	int		sp_height;
	int		sp_width;
	int		drawstarty;
	int		drawendy;
	int		drawstartx;
	int		drawendx;
	int		texx;
	int		texy;
}				t_rndr_sprite;

typedef struct	s_game
{
	int			pars_check[9];
	t_player	pl;
	t_texture	txs[5];
	t_vars		vars;
	t_map		map;
	t_sprite	sp;
	t_render	r;
}				t_game;

typedef struct	s_p_order {
	double	first;
	int		second;
}				t_p_order;

void			main_parser(t_game *g, char *filename);
void			map_parser(t_game *g, char *line);
void			res_parser(t_game *g, char *line);
void			check_n_set_res(t_game *g, int scn_w, int scn_h);
void			tex_parser(t_game *g, char *line);
void			load_texture(void *mlx_ptr, char *filename,
	t_texture *res, t_game *g);
void			color_parser(t_game *g, char *line);
void			sprite_parser(t_game *g, char *line);
int				checkno_cub(long ans, int sign);
int				ft_atoi_cub(char **str);
char			*remove_space(char *line);
void			check_map(t_game *g);
void			printf_error(char *error, t_game *g);
void			ft_destroy(t_game *g);
void			set_player_pos(t_game *g, char c, int y);
void			set_pos_north(t_game *g);
void			set_pos_south(t_game *g);
void			set_pos_east(t_game *g);
void			set_pos_west(t_game *g);
void			set_sprite_pos(t_game *g, char c, int y, int i);
int				is_direction(char c);
void			check_input_map_error(char c, t_game *g);
void			render(t_game *g);
void			render_start(t_game *g, int x);
void			render_start_init(t_game *g);
void			render_init(t_game *g, int x);
void			dda(t_game *g);
void			render_ceiling(t_game *g, int x);
void			render_floor(t_game *g, int x);
void			render_wall(t_game *g, int x);
void			render_sprites(t_game *g);
void			render_sprites_helper(t_game *g, t_rndr_sprite *rndr_sprites);
int				keys_hook(int keycode, t_game *g);
void			move_up(t_game *g, double mvspd);
void			move_down(t_game *g, double mvspd);
void			move_left(t_game *g, double mvspd);
void			move_right(t_game *g, double mvspd);
void			rotate_right(t_game *g, double mvspd, double rtspd);
void			exit_game(t_game *g);
void			rotate_left(t_game *g, double mvspd, double rtspd);
void			draw_pixel(t_vars *vars, unsigned int x, unsigned int y,
	unsigned char color[4]);
void			my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void			get_pixel_color(t_texture texture, int x,
	int y, unsigned char *result);

#endif
