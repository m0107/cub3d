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

	if (x >= vars->screenWidth || y >= vars->screenHeight)
		return ;
	index = x * 4 + (y * vars->img.line_length);
	i = -1;
	while (++i < 4)
		vars->img.addr[index + i] = color[i];
}

void render(t_game *game)
{
	printf("inside rendering function\n\n");
	for(int x = 0; x < game->vars.screenWidth; x++) {
			//calculate ray position and direction
			double cameraX = 2 * x / (double)game->vars.screenWidth - 1; //x-coordinate in camera space
			double rayDirX = game->player.dirX + game->player.planeX * cameraX;
			double rayDirY = game->player.dirY + game->player.planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)(game->player.posX);
			int mapY = (int)(game->player.posY);

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
			if(rayDirX < 0) {
				stepX = -1;
				sideDistX = (game->player.posX - mapX) * deltaDistX;
			}else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
			}
			if(rayDirY < 0) {
				stepY = -1;
				sideDistY = (game->player.posY - mapY) * deltaDistY;
			}else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
			}
			// printf("Starting dda\n\n");
			// perform DDA
			while (hit == 0) {
				
			
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY) {
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				} else {
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if(game->map[mapX][mapY] != '0')
				{ 
					hit = 1;
					printf("hit at mapx: %d, mapY:%d\n", mapX, mapY);
					printf("side: %d\n", side);
					int trmp;
				
				}
				
			}
			//  printf("game.player.posX:|%f|\n", game->player.posX);
			//  printf("game.player.posY:|%f|\n", game->player.posY);
			
			//  printf("stepX:|%d|\n", stepX);
			//  printf("stepY:|%d|\n", stepY);


			// printf("rayDirX:|%f|\n", rayDirX);
			// printf("rayDirY:|%f|\n", rayDirY);
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if(side == 0) perpWallDist = (mapX - game->player.posX + (1 - stepX) / 2) / rayDirX;
			else          perpWallDist = (mapY - game->player.posY + (1 - stepY) / 2) / rayDirY;
		//	 printf("prepWallDist: %f\n\n", perpWallDist);
			 if (perpWallDist <= 0.0000001f){
				 printf("*******returning\n\n");
				 printf("game.player.posX:|%f|\n", game->player.posX);
				printf("game.player.posY:|%f|\n", game->player.posY);
			
			 	return;
			 }
		//	 printf("Calculate height of line to draw on screen\n\n");
			//Calculate height of line to draw on screen
			int lineHeight = (int)(game->vars.screenHeight / perpWallDist);
		//	printf("line height: %d\n\n", lineHeight);
			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + game->vars.screenHeight / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + game->vars.screenHeight / 2;
			// printf("drawend: %d\n", drawEnd);
		
			if(drawEnd >= game->vars.screenHeight)drawEnd = game->vars.screenHeight - 1;


	

			//calculate value of wallX
			double wallX; //where exactly the wall was hit
			if (side == 0) wallX = game->player.posY + perpWallDist * rayDirY;
			else           wallX = game->player.posX + perpWallDist * rayDirX;
			wallX -= floor((wallX));

			//x coordinate on the texture
			int texX = (int)(wallX * (double)(texWidth));
			if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
			if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
			double step = 1.0 * texHeight / lineHeight;
			// Starting texture coordinate
			double texPos = (drawStart - game->vars.screenHeight / 2 + lineHeight / 2) * step;
			int i;
			for(i = 0; i < drawStart; i++)
			{
				my_mlx_pixel_put(&game->vars, x, i, game->vars.ceiling_color);
			}
		//	printf("starting drawing 1\n\n");
		//	printf("drawend: %d\n", drawEnd);
		
			for(i = drawStart; i < drawEnd; i++)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				unsigned char color[4];
				if (side == 0 && rayDirX < 0)
				{	//north
					get_pixel_color(game->textures[0], texX, texY, color);
					draw_pixel(&game->vars, x, i, color);
				}
				else if (side == 0 && rayDirX >= 0)
				{
					get_pixel_color(game->textures[1], texX, texY, color);
					draw_pixel(&game->vars, x, i, color);
				}
				else if (side == 1 && rayDirY < 0)
				{
					get_pixel_color(game->textures[2], texX, texY, color);
					draw_pixel(&game->vars, x, i, color);
				}
				else 
				{
					get_pixel_color(game->textures[3], texX, texY, color);
					draw_pixel(&game->vars, x, i, color);
				}
			}
			for(i = drawEnd; i < game->vars.screenHeight; i++)
			{
				my_mlx_pixel_put(&game->vars, x, i, game->vars.floor_color);
			}
		}
		// printf("drawing finished\n\n");
		mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->vars.img.img, 0, 0);	
		// printf("rendering done\n\n");
}

int             ft_close(int keycode, t_game *game)
{

	//speed modifiers
	double moveSpeed = 0.1; //the constant value is in squares/second
	double rotSpeed = 0.0872665;
	//double rotSpeed = 0.0872665; //the constant value is in radians/second
	printf("pos x: %f | y: %f\n", game->player.posX, game->player.posY);
	printf("keycode: %d******\n\n\n", keycode);
	if(keycode == 13)
	{		
		int xMap = (int)((game->player.posX + game->player.dirX * moveSpeed));
		int yMap = (int)(game->player.posY);
		printf("xMap: %d | yMap: %d\n\n", xMap, yMap);
		if(game->map[xMap][yMap] == '0')
			game->player.posX += game->player.dirX * moveSpeed;
		if(game->map[(int)ceil(game->player.posX)][(int)(ceil(game->player.posY + game->player.dirY * moveSpeed))] == '0')
			game->player.posY += game->player.dirY * moveSpeed;
		render(game);
	}

	if(keycode == 1)
	{
		if(game->map[(int)(game->player.posX - game->player.dirX * moveSpeed)][(int)game->player.posY] == '0')
			game->player.posX -= game->player.dirX * moveSpeed;
		if(game->map[(int)game->player.posX][(int)(game->player.posY - game->player.dirY * moveSpeed)] == '0')
			game->player.posY -= game->player.dirY * moveSpeed;
			 printf("****game.player.posX:|%f|\n", game->player.posX);
				printf("****game.player.posY:|%f|\n", game->player.posY);
		render(game);
	}
	if (keycode == 2)
	{  	rotSpeed = 1.5708;
		double oldDirX = game->player.dirX;
		double tempx = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
      	double tempy = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);

		if(game->map[(int)(game->player.posX + tempx * moveSpeed)][(int)game->player.posY] == '0')
			game->player.posX += tempx * moveSpeed;
		if(game->map[(int)game->player.posX][(int)(game->player.posY + tempy * moveSpeed)] == '0')
			game->player.posY += tempy * moveSpeed;
		render(game);
	}

	if(keycode == 0)
	{	
		rotSpeed = -1.5708;
		double oldDirX = game->player.dirX;
		double tempx  = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
      	double tempy  = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);

		if(game->map[(int)(game->player.posX - tempx * moveSpeed)][(int)game->player.posY] == '0') game->player.posX -= tempx * moveSpeed;
		if(game->map[(int)game->player.posX][(int)(game->player.posY - tempy * moveSpeed)] == '0') game->player.posY -= tempy * moveSpeed;
		render(game);
	}
	//turn right
	if(keycode == 124)
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
    if(keycode == 123)
    {
      double oldDirX = game->player.dirX;
      game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
      game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
      double oldPlaneX = game->player.planeX;
      game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
      game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
	  render(game);
    }

	if(keycode == 53)
	{	
		mlx_destroy_window(game->vars.mlx, game->vars.win);
		for(int i=0;i<4;i++)
		{
			free(game->map[i]);
		}
		printf("map freed\n\n");
		
	}
	return (1);
}


int             main(int argc, char *argv[])
{
	t_game		game; 
	game.player.posX = 6.5; //row no, starting from 0
	game.player.posY = 4.5;  //Column no starting from 0
	game.player.dirX = 1; 
	game.player.dirY = 0; //initial direction vector
	
	// plane according to intial direction vector
	game.player.planeX = 0; 
	game.player.planeY = -0.66; //the 2d raycaster version of camera plane
	
	game.vars.mlx = mlx_init();
	main_parser(&game, argv[1]);
	
	game.vars.win = mlx_new_window(game.vars.mlx, game.vars.screenWidth, game.vars.screenHeight, "Hello world!");
	//mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    game.vars.img.img = mlx_new_image(game.vars.mlx, 1920, 1080);
    game.vars.img.addr = mlx_get_data_addr(game.vars.img.img, &game.vars.img.bits_per_pixel, &game.vars.img.line_length,
                                 &game.vars.img.endian);
	//print_line(vars);	
		render(&game);
		mlx_hook(game.vars.win, 2, 1L<<0, ft_close, &game);
		mlx_loop(game.vars.mlx);
	return 0;
}