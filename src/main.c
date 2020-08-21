/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 06:19:59 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 06:20:03 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pixel_color(t_texture texture, int x, int y, unsigned char *result)
{
	int	index;
	int	i;

	if (x >= texture.width || y >= texture.height)
		return ;
	if (x < 0 || y < 0)
		return ;
	index = (x + y * texture.width) * 4;
	i = -1;
	while (++i < 4)
		result[i] = (int)texture.data[index + i];
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img.addr +
		(y * vars->img.line_length +
		x * (vars->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_pixel(t_vars *vars, unsigned int x,
	unsigned int y, unsigned char color[4])
{
	int	index;
	int	i;

	if (x >= vars->scn_w || y >= vars->scn_h)
		return ;
	index = x * 4 + (y * vars->img.line_length);
	i = -1;
	while (++i < 4)
		vars->img.addr[index + i] = color[i];
}

int		main(int argc, char *argv[])
{
	t_game	g;

	g.vars.mlx = mlx_init();
	main_parser(&g, argv[1]);
	g.vars.win = mlx_new_window(g.vars.mlx,
		g.vars.scn_w, g.vars.scn_h, "Cub3d");
	g.vars.img.img = mlx_new_image(g.vars.mlx, 1920, 1080);
	g.vars.img.addr = mlx_get_data_addr(g.vars.img.img,
		&g.vars.img.bits_per_pixel, &g.vars.img.line_length,
		&g.vars.img.endian);
	render(&g);
	mlx_hook(g.vars.win, 2, 1L << 0, keys_hook, &g);
	mlx_loop(g.vars.mlx);
	return (0);
}
