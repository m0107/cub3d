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

int compare(const void * a, const void * b) 
{ 
	t_sprites *a_sprite = (t_sprites *) a;
	t_sprites *b_sprite = (t_sprites *) b;
    return ( a_sprite->first - b_sprite->first ); 
} 

//sort the sprites based on distance
void sortSprites(int* order, double* dist, int amount, t_game *game)
{
  //std::vector<std::pair<double, int>> sprites(amount);
	t_sprites *sprites;
	printf("amount: %d\n", amount);
	if (!(sprites = (t_sprites *)malloc((amount) * sizeof(t_sprites))))
		printf_error("malloc spriteOrder failed.\n", game);

  for(int i = 0; i < amount; i++) {
    sprites[i].first = dist[i];
    sprites[i].second = order[i];
  }
   for(int i = 0; i < amount; i++) {
    printf("dist[%d]: %f\n", i, dist[i]);
	printf("order[%d]: %d\n\n\n", i, order[i]);
  }
  // std::sort(sprites.begin(), sprites.end());
  qsort(sprites, amount, sizeof(t_sprites), compare); 
  // restore in reverse order to go from farthest to nearest
  for(int i = 0; i < amount; i++) {
    dist[i] = sprites[amount - i - 1].first;
    order[i] = sprites[amount - i - 1].second;
  }
  for(int i = 0; i < amount; i++) {
    printf("dist[%d]: %f\n", i, dist[i]);
	printf("order[%d]: %d\n", i, order[i]);
  }
  //exit(0);
}


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

void render(t_game *game)
{
	int   ZBuffer[500];
	//printf("inside rendering function\n\n");
	for(int x = 0; x < game->vars.screenwidth; x++) 
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)game->vars.screenwidth - 1; //x-coordinate in camera space
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
			if(game->map.data[mapX][mapY] == '1')
				hit = 1;
			
		}
		//   printf("game.player.posX:|%f|\n", game->player.posX);
		//   printf("game.player.posY:|%f|\n", game->player.posY);
		
		//   printf("stepX:|%d|\n", stepX);
		//   printf("stepY:|%d|\n", stepY);


		//  printf("rayDirX:|%f|\n", rayDirX);
		//  printf("rayDirY:|%f|\n", rayDirY);
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - game->player.posX + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - game->player.posY + (1 - stepY) / 2) / rayDirY;
			//printf("prepWallDist: %f\n\n", perpWallDist);
			if (perpWallDist <= 0.0000001f){
			//  printf("*******returning\n\n");
			//  printf("game.player.posX:|%f|\n", game->player.posX);
			// printf("game.player.posY:|%f|\n", game->player.posY);
		
			return;
			}
		
		//  printf("Calculate height of line to draw on screen\n\n");
		//Calculate height of line to draw on screen
		int lineHeight = (int)(game->vars.screenheight / perpWallDist);
		// printf("line height: %d\n\n", lineHeight);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game->vars.screenheight / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + game->vars.screenheight / 2;
		//  printf("drawend: %d\n", drawEnd);
	
		if(drawEnd >= game->vars.screenheight)drawEnd = game->vars.screenheight - 1;




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
		double texPos = (drawStart - game->vars.screenheight / 2 + lineHeight / 2) * step;
		int i;
		for(i = 0; i < drawStart; i++)
		{
			my_mlx_pixel_put(&game->vars, x, i, game->vars.ceiling_color);
		}

	
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
		for(i = drawEnd; i < game->vars.screenheight; i++)
			{
				my_mlx_pixel_put(&game->vars, x, i, game->vars.floor_color);
			}
			ZBuffer[x] = perpWallDist; //perpendicular distance is used
	}
	//SPRITE CASTING
    //sort sprites from far to close
	int *spriteOrder;
	double *spriteDistance;

	if (!(spriteOrder = (int *)malloc((game->map.size) * sizeof(int))))
		printf_error("malloc spriteOrder failed.\n", game);

	if (!(spriteDistance = (double *)malloc((game->map.size) * sizeof(double))))
		printf_error("malloc spriteOrder failed.\n", game);


	for(int i = 0; i < game->sprite.size; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = sqrt(((game->player.posX - game->sprite.pos[i].x) * (game->player.posX - game->sprite.pos[i].x) + (game->player.posY - game->sprite.pos[i].y) * (game->player.posY - game->sprite.pos[i].y))); //sqrt not taken, unneeded
    }
	printf("startig sorting\n\n");
	sortSprites(spriteOrder, spriteDistance, game->sprite.size, game);
	printf("startig done\n\n");
	for(int i = 0; i < game->sprite.size; i++)
    {
	double spriteX = game->sprite.pos[spriteOrder[i]].x - game->player.posX;
	double spriteY = game->sprite.pos[spriteOrder[i]].y - game->player.posY;

	double invDet = 1.0 / (game->player.planeX * game->player.dirY - game->player.dirX * game->player.planeY); //required for correct matrix multiplication

	double transformX = invDet * (game->player.dirY * spriteX - game->player.dirX * spriteY);
	double transformY = invDet * (-game->player.planeY * spriteX + game->player.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

	int spriteScreenX = (int)((game->vars.screenwidth / 2) * (1 + transformX / transformY));

	//calculate height of the sprite on screen
	int spriteHeight = abs((int)(game->vars.screenheight / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	int drawStartY = -spriteHeight / 2 + game->vars.screenheight / 2;
	if(drawStartY < 0) drawStartY = 0;
	int drawEndY = spriteHeight / 2 + game->vars.screenheight / 2;
	if(drawEndY >= game->vars.screenheight) drawEndY = game->vars.screenheight - 1;

	//calculate width of the sprite
	int spriteWidth = abs( (int)(game->vars.screenheight / (transformY)));
	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if(drawStartX < 0) drawStartX = 0;
	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if(drawEndX >= game->vars.screenwidth) drawEndX = game->vars.screenwidth - 1;
	unsigned char color[4];
	//loop through every vertical stripe of the sprite on screen
	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if(transformY > 0 && stripe > 0 && stripe < game->vars.screenwidth && transformY < ZBuffer[stripe] + 0.5)
		{
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y) * 256 - game->vars.screenheight * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * texHeight) / spriteHeight) / 256;
				get_pixel_color(game->sprite.texture, texX, texY, color);
				if(color[3] ==  0)
				{
					
				}
				if ( color[3] != 255)
					draw_pixel(&game->vars, stripe, y, color);
			}
		}
	}
	
	
	}
	free(spriteOrder);
	free(spriteDistance);
	//printf("drawing finished\n\n");

	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->vars.img.img, 0, 0);	
	//printf("rendering done\n\n");
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
		free(game->sprite.pos);
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