#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

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

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void print_line(t_vars vars, int x, int drawStart, int drawEnd, int color)
{
	//printf("x: %d,  drawStart: %d,   drawEnd: %d color:%d\n", x, drawStart, drawEnd, color);
	int i,j;
	for(i = 0; i < drawStart; i++)
	{
		my_mlx_pixel_put(&vars.img, x, i, 0x00000000);
	}
	for ( i = drawStart; i <= drawEnd; i++)
	{
		
			my_mlx_pixel_put(&vars.img, x, i, color);
	}

	for(i = drawEnd; i < screenHeight; i++)
	{
		my_mlx_pixel_put(&vars.img, x, i, 0x00000000);
	}
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

			//choose wall color
			int color;
			switch(worldMap[mapX][mapY])
			{
				case 1:  color = 0x00FF0000;    break; //red
				case 2:  color = 0x0000FF00;  break; //green
				case 3:  color = 0x000000FF;   break; //blue
				case 4:  color = 0X00FFFFFF;  break; //white
				default: color = 0x00CCCC00; break; //yellow
			}

			//give x and y sides different brightness
			if(side == 1) {color = color / 2;}

			//draw the pixels of the stripe as a vertical line
			//verLine(x, drawStart, drawEnd, color);
			//printf("MOhit");
			print_line(game.vars, x, drawStart, drawEnd, color);
		}
		mlx_put_image_to_window(game.vars.mlx, game.vars.win, game.vars.img.img, 0, 0);	
}

int             close(int keycode, t_game *game)
{

		

		//speed modifiers
		double moveSpeed = 0.1; //the constant value is in squares/second
		
		printf("pos x: %f | y: %f\n", game->player.posX, game->player.posY);
		
		
		
	
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
	{
		if(worldMap[(int)game->player.posX][(int)(game->player.posY + moveSpeed)] == 0) game->player.posY +=  moveSpeed;
		render(*game);
	}

	if(keycode == 0)
	{
		if(worldMap[(int)game->player.posX][(int)(game->player.posY - moveSpeed)] == 0) game->player.posY -=  moveSpeed;
		render(*game);
	//	if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //  if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
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
    game.vars.win = mlx_new_window(game.vars.mlx, screenWidth, screenWidth, "Hello world!");
    //mlx = mlx_init();


    //mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    game.vars.img.img = mlx_new_image(game.vars.mlx, 1920, 1080);
    game.vars.img.addr = mlx_get_data_addr(game.vars.img.img, &game.vars.img.bits_per_pixel, &game.vars.img.line_length,
                                 &game.vars.img.endian);

	//print_line(vars);	
	int temp = 0;
	while(temp == 0) {
		render(game);
		mlx_hook(game.vars.win, 2, 1L<<0, close, &game);	
		mlx_loop(game.vars.mlx);
  	}
}



