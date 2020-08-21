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
#include "math.h"
#include "../gnl/get_next_line.h"

void		get_pixel_color(t_texture texture, int x, int y,
		unsigned char *result)
{

	int index;
	int i;

	if (x >= texture.width || y >= texture.height)
		return ;
	if (x < 0 || y < 0)
		return ;
	index = (x + y * texture.width) * 4;
	i = -1;
	while (++i < 4)
	{
		result[i] = (int)texture.data[index + i];
		
	}
	
}


void            my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
    char    *dst;

    dst = vars->img.addr + (y * vars->img.line_length + x * (vars->img.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_pixel(t_vars *vars, unsigned int x, unsigned int y,
	unsigned char color[4])
{
	int index;
	int	i;

	if (x >= vars->screenwidth || y >= vars->screenheight)
		return ;
	index = x * 4 + (y * vars->img.line_length);
	i = -1;
	while (++i < 4)
		vars->img.addr[index + i] = color[i];
}

int             ft_close(int keycode, t_game *game)
{

	//speed modifiers
	double moveSpeed = 0.15; //the constant value is in squares/second
	double rotSpeed = 0.0872665;
	//double rotSpeed = 0.0872665; //the constant value is in radians/second
	//printf("pos x: %f | y: %f\n", game->player.posX, game->player.posY);
	printf("keycode: %d******\n\n\n", keycode);
	//forward
	if(keycode == KEY_W)
	{		
		int xMap = (int)((game->player.posX + game->player.dirX * moveSpeed));
		int yMap = (int)(game->player.posY);
		if(game->map.data[xMap][yMap] == '0')
			game->player.posX += game->player.dirX * moveSpeed;
		if(game->map.data[(int)(game->player.posX)][(int)((game->player.posY + game->player.dirY * moveSpeed))] == '0')
			game->player.posY += game->player.dirY * moveSpeed;
		render(game);
	}
	//back
	if(keycode == KEY_S)
	{
		if(game->map.data[(int)(game->player.posX - game->player.dirX * moveSpeed)][(int)game->player.posY] == '0')
			game->player.posX -= game->player.dirX * moveSpeed;
		if(game->map.data[(int)game->player.posX][(int)(game->player.posY - game->player.dirY * moveSpeed)] == '0')
			game->player.posY -= game->player.dirY * moveSpeed;
			printf("****game.player.posX:|%f|\n", game->player.posX);
			printf("****game.player.posY:|%f|\n", game->player.posY);
		render(game);
	}
	//ritgh
	if (keycode == KEY_D)
	{  	rotSpeed = 1.5708;
		double oldDirX = game->player.dirX;
		double tempx = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
      	double tempy = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);

		if(game->map.data[(int)(game->player.posX + tempx * moveSpeed)][(int)game->player.posY] == '0')
			game->player.posX += tempx * moveSpeed;
		if(game->map.data[(int)game->player.posX][(int)(game->player.posY + tempy * moveSpeed)] == '0')
			game->player.posY += tempy * moveSpeed;
		render(game);
	}

	if(keycode == KEY_A)
	{	
		rotSpeed = -1.5708;
		double oldDirX = game->player.dirX;
		double tempx  = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
      	double tempy  = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);

		if(game->map.data[(int)(game->player.posX - tempx * moveSpeed)][(int)game->player.posY] == '0') game->player.posX -= tempx * moveSpeed;
		if(game->map.data[(int)game->player.posX][(int)(game->player.posY - tempy * moveSpeed)] == '0') game->player.posY -= tempy * moveSpeed;
		render(game);
	}
	//turn right
	if(keycode == KEY_RIGHT)
    {
      double oldDirX = game->player.dirX;
      game->player.dirX = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
      game->player.dirY = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);
      double oldPlaneX = game->player.planeX;
      game->player.planeX = game->player.planeX * cos(-rotSpeed) - game->player.planeY * sin(-rotSpeed);
      game->player.planeY = oldPlaneX * sin(-rotSpeed) + game->player.planeY * cos(-rotSpeed);
	  render(game);
    }
    //rotate to the left
    if(keycode == KEY_LEFT)
    {
      double oldDirX = game->player.dirX;
      game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
      game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
      double oldPlaneX = game->player.planeX;
      game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
      game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
	  render(game);
    }

	if(keycode == KEY_ESC)
	{	
		mlx_destroy_window(game->vars.mlx, game->vars.win);
		printf("map size: %d", game->map.size);
		for(int i=0;i<game->map.size;i++)
		{
			free(game->map.data[i]);
		}
		free(game->map.data);
		free(game->sprite.pos);
		free(game->render.ZBuffer);
		printf("map freed\n\n");
		exit(0);
		
	}
	return (1);
}


int             main(int argc, char *argv[])
{
	t_game		game; 
	
	game.vars.mlx = mlx_init();
	main_parser(&game, argv[1]);
	
	
	game.vars.win = mlx_new_window(game.vars.mlx, game.vars.screenwidth, game.vars.screenheight, "Hello world!");
	//mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    game.vars.img.img = mlx_new_image(game.vars.mlx, 1920, 1080);
    game.vars.img.addr = mlx_get_data_addr(game.vars.img.img, &game.vars.img.bits_per_pixel, &game.vars.img.line_length,
                                 &game.vars.img.endian);
	//print_line(vars);	
		printf("startig renDering\n");
		render(&game);
		mlx_hook(game.vars.win, 2, 1L<<0, ft_close, &game);
		//mlx_key_hook(game.vars.win,ft_close, &game);
		mlx_loop(game.vars.mlx);
	return 0;
}