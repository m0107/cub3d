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

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


int             close1(int keycode, char *vars)
{
	printf("close1 called");
	printf("%d\n",keycode);
	printf("*********%s\n", (vars));

	return (1);
}

int             close(int keycode, t_vars *vars)
{

	printf("close called");
	printf("%d\n",keycode);
	(void)vars;
	if(keycode == 53)
	{	
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	return (1);
}

void print_line(t_vars vars, int x, int drawStart, int drawEnd, int color)
{
	printf("x: %d,  drawStart: %d,   drawEnd: %d color:%d\n", x, drawStart, drawEnd, color);
	int i,j;
	for ( i = drawStart; i <= drawEnd+5; i++)
	{
		
			my_mlx_pixel_put(&vars.img, x, i, color);
	}
}


void render(t_player player, t_vars vars)
{
	for(int x = 0; x < screenWidth; x++) {
			//calculate ray position and direction
			double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
			double rayDirX = player.dirX + player.planeX * cameraX;
			double rayDirY = player.dirY + player.planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)player.posX;
			int mapY = (int)player.posY;

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
				sideDistX = (player.posX - mapX) * deltaDistX;
			}else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - player.posX) * deltaDistX;
			}
			if(rayDirY < 0) {
				stepY = -1;
				sideDistY = (player.posY - mapY) * deltaDistY;
			}else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - player.posY) * deltaDistY;
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
			if(side == 0) perpWallDist = (mapX - player.posX + (1 - stepX) / 2) / rayDirX;
			else          perpWallDist = (mapY - player.posY + (1 - stepY) / 2) / rayDirY;

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
			print_line(vars, x, drawStart, drawEnd, color);
		}
		mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);	
}



int             main(void)
{

	t_player	player;
	player.posX = 22;
	player.posY = 12;  //x and y start position
	player.dirX = -1; 
	player.dirY = 0; //initial direction vector
	player.planeX = 0; 
	player.planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	t_vars      vars;

	vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, screenWidth, screenWidth, "Hello world!");
    //mlx = mlx_init();


    //mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
                                 &vars.img.endian);

	//print_line(vars);	
	int temp = 0;
	while(temp == 0) {
		render(player, vars);
		printf("Mohit");
		//timing for input and FPS counter
		oldTime = time;
		//time = getTicks();
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		//print(1.0 / frameTime); //FPS counter
		//redraw();
		//cls();

		//speed modifiers
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
		mlx_hook(vars.win, 2, 1L<<0, close, &vars);
		char  *c = "MOhit";
		printf("%s", c);
		//mlx_hook(vars.win, 2, 1L<<0, close1, c);
		
		mlx_loop(vars.mlx);
  	}
}



