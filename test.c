#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "libft/libft.h"


#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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
    void        *mlx;
    void        *win;
	t_data 		img;
}               t_vars;

typedef struct  s_game {
    t_player	player;
	t_vars		vars;
}               t_game;

typedef struct	s_texture
{
	int				width;
	int				height;
	char			*filename;
	void			*ptr;
	char			*data;
}				t_texture;

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

void	load_texture(void *mlx_ptr, char *filename, t_texture *res)
{
	
	int			config[3];
	
	res->ptr = mlx_xpm_file_to_image(mlx_ptr, filename,
			&(res->width), &(res->height));
	if (res->ptr == 0){
		printf("Not able to read");
	}
	config[0] = 32;
	config[1] = res->width * 4;
	config[2] = 0;
	res->data = mlx_get_data_addr(res->ptr,
			&config[0], &config[1], &config[2]);
	if(res->data == 0)
	{
		printf("reading failed");
	}
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
void	draw_pixel(t_data *data, unsigned int x, unsigned int y,
	unsigned char color[4])
{
	int index;
	int	i;

	if (x >= screenWidth || y >= screenHeight)
		return ;
	index = x * 4 + (y * data->line_length);
	i = -1;
	while (++i < 4)
		data->addr[index + i] = color[i];
}

void render(t_game game)
{
	for(int x = 0; x < screenWidth; x++) {
			//calculate ray position and direction
			double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
			double rayDirX = game.player.dirX + game.player.planeX * cameraX;
			double rayDirY = game.player.dirY + game.player.planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)game.player.posX;
			int mapY = (int)game.player.posY;

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
				sideDistX = (game.player.posX - mapX) * deltaDistX;
			}else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - game.player.posX) * deltaDistX;
			}
			if(rayDirY < 0) {
				stepY = -1;
				sideDistY = (game.player.posY - mapY) * deltaDistY;
			}else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - game.player.posY) * deltaDistY;
			}
			//perform DDA
			while (hit == 0) {
				//jump to next map square, OR in x-direction, OR in y-direction
				if(sideDistX < sideDistY) {
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}else {
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if(worldMap[mapX][mapY] > 0) hit = 1;
			}
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if(side == 0) perpWallDist = (mapX - game.player.posX + (1 - stepX) / 2) / rayDirX;
			else          perpWallDist = (mapY - game.player.posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(screenHeight / perpWallDist);
			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;


			

			//calculate value of wallX
			double wallX; //where exactly the wall was hit
			if (side == 0) wallX = game.player.posY + perpWallDist * rayDirY;
			else           wallX = game.player.posX + perpWallDist * rayDirX;
			wallX -= floor((wallX));

			//x coordinate on the texture
			int texX = (int)(wallX * (double)(texWidth));
			if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
			if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

			t_texture temp_tex;
			
			load_texture(game.vars.mlx, "./pics/wall1.xpm", &temp_tex);
			
			// How much to increase the texture coordinate per screen pixel
			double step = 1.0 * texHeight / lineHeight;
			// Starting texture coordinate
			double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
			int i;
			for(i = 0; i < drawStart; i++)
			{
				my_mlx_pixel_put(&game.vars.img, x, i, 11793663);
			}
			for(i = drawStart; i < drawEnd; i++)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				unsigned char color[4];
				get_pixel_color(temp_tex, texX, texY, color);
				
					draw_pixel(&game.vars.img, x, i, color);
		
				//printf("pos x: %d | i: %d\n",x, i);
		
				//my_mlx_pixel_put(&game.vars.img, x, i, 0x00ff0000);
			}
			for(i = drawEnd; i < screenHeight; i++)
			{
				my_mlx_pixel_put(&game.vars.img, x, i, 0x009B7653);
			}

			//printf(" value of i in end : %d\n", i);
			//print_line(game.vars, x, drawStart, drawEnd, color);
		}
		mlx_put_image_to_window(game.vars.mlx, game.vars.win, game.vars.img.img, 0, 0);	
}

int             ft_close(int keycode, t_game *game)
{

		

		//speed modifiers
		double moveSpeed = 0.1; //the constant value is in squares/second
		double rotSpeed = 0.3; //the constant value is in radians/second
		//printf("pos x: %f | y: %f\n", game->player.posX, game->player.posY);
		
		
		
	
     // if(worldMap[(int)(game->player.posX + game->player.dirX * 0.1)][(int)game->player.posY] == 0) game->player.posX += game->player.dirX * moveSpeed;
      //if(worldMap[(int)game->player.posX][(int)(game->player.posY + game->player.dirY * moveSpeed)] == 0) game->player.posY += game->player.dirY * moveSpeed;
    
	if(keycode == 13)
	{		
		if(worldMap[(int)(game->player.posX + game->player.dirX * moveSpeed)][(int)game->player.posY] == 0) game->player.posX += game->player.dirX * moveSpeed;
		if(worldMap[(int)game->player.posX][(int)(game->player.posY + game->player.dirY * moveSpeed)] == 0) game->player.posY += game->player.dirY * moveSpeed;
		render(*game);
	}

	if(keycode == 1)
	{
		if(worldMap[(int)(game->player.posX - game->player.dirX * moveSpeed)][(int)game->player.posY] == 0) game->player.posX -= game->player.dirX * moveSpeed;
		if(worldMap[(int)game->player.posX][(int)(game->player.posY - game->player.dirY * moveSpeed)] == 0) game->player.posY -= game->player.dirY * moveSpeed;
		render(*game);
	//	if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //  if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	if (keycode == 2)
	{  	rotSpeed = 1.5708;
		double oldDirX = game->player.dirX;
		double tempx = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
      	double tempy = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);

		if(worldMap[(int)(game->player.posX + tempx * moveSpeed)][(int)game->player.posY] == 0) game->player.posX += tempx * moveSpeed;
		if(worldMap[(int)game->player.posX][(int)(game->player.posY + tempy * moveSpeed)] == 0) game->player.posY += tempy * moveSpeed;
		render(*game);
	}

	if(keycode == 0)
	{	
		rotSpeed = -1.5708;
		double oldDirX = game->player.dirX;
		double tempx  = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
      	double tempy  = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);

		if(worldMap[(int)(game->player.posX - tempx * moveSpeed)][(int)game->player.posY] == 0) game->player.posX -= tempx * moveSpeed;
		if(worldMap[(int)game->player.posX][(int)(game->player.posY - tempy * moveSpeed)] == 0) game->player.posY -= tempy * moveSpeed;
		render(*game);
	//	if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //  if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	//turn right
	if(keycode == 124)
    {
      //both camera direction and camera plane must be rotated
	  
      double oldDirX = game->player.dirX;
      game->player.dirX = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
      game->player.dirY = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);
      double oldPlaneX = game->player.planeX;
      game->player.planeX = game->player.planeX * cos(-rotSpeed) - game->player.planeY * sin(-rotSpeed);
      game->player.planeY = oldPlaneX * sin(-rotSpeed) + game->player.planeY * cos(-rotSpeed);
	  render(*game);
    }
    //rotate to the left
    if(keycode == 123)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = game->player.dirX;
      game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
      game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
      double oldPlaneX = game->player.planeX;
      game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
      game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
	  render(*game);
    }

	if(keycode == 53)
	{	
		mlx_destroy_window(game->vars.mlx, game->vars.win);
		exit(1);
	}
	return (1);
}


int             main(void)
{
	t_game		game;
	game.player.posX = 22;
	game.player.posY = 12;  //x and y start position
	game.player.dirX = -1; 
	game.player.dirY = 0; //initial direction vector
	game.player.planeX = 0; 
	game.player.planeY = 0.66; //the 2d raycaster version of camera plane


	game.vars.mlx = mlx_init();
    game.vars.win = mlx_new_window(game.vars.mlx, screenWidth, screenHeight, "Hello world!");
    //mlx = mlx_init();

	
    //mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    game.vars.img.img = mlx_new_image(game.vars.mlx, 1920, 1080);
    game.vars.img.addr = mlx_get_data_addr(game.vars.img.img, &game.vars.img.bits_per_pixel, &game.vars.img.line_length,
                                 &game.vars.img.endian);

	//print_line(vars);	
	int temp = 0;
	while(temp == 0) {
		render(game);
		mlx_hook(game.vars.win, 2, 1L<<0, ft_close, &game);
		mlx_loop(game.vars.mlx);
  	}
}



