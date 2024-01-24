#include "../../include/cubed.h"

static int worldMap[column][row]=
{
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1}
};

static void	draw_visor(int x, int y, t_cubed *cubed)
{
	uint32_t	colorYellow = ft_pixel(255, 165, 0, 0xFF);
	double		pa;
	int	line;
	
	pa = cubed->pa;
	line = 15;
	while (line > 0)
	{
		mlx_put_pixel(cubed->image, x + cos(pa) * line, y + sin(pa) * line, colorYellow);
		line--;
	}
}

static void	player(t_cubed *cubed)
{
	uint32_t colorYellow = ft_pixel(255, 165, 0, 0xFF);
	double	player_size;
	double	visor_thickness;

	player_size = 4;
	visor_thickness = 1.5;
	int	y = 0;
	while (y < cubed->mini_map_height && cubed->posY > 0 && cubed->posY < cubed->mini_map_height)
	{
		int x = 0;
		while (x < cubed->mini_map_width && cubed->posX > 0 && cubed->posX < cubed->mini_map_width)
		{
			if ((x > cubed->posX - player_size && x < cubed->posX + player_size)
					&& (y > cubed->posY - player_size && y < cubed->posY + player_size))
			{
				mlx_put_pixel(cubed->image, x, y + cubed->mini_map_start_y, colorYellow);
				if ((x > cubed->posX - visor_thickness && x < cubed->posX + visor_thickness)
					&& (y > cubed->posY - visor_thickness && y < cubed->posY + visor_thickness))
					draw_visor(x, y + cubed->mini_map_start_y, cubed);
			}
			x++;
		}
		y++;
	}
}

// TO DO: does not work perfectly on all maps
void mini_map(t_cubed *cubed)
{
	uint32_t colorBlack = ft_pixel(0, 0, 0, 0xFF);
	uint32_t colorWhite = ft_pixel(255, 255, 255, 0xFF);
	int	y;
	int	border;

	y = 0;
	border = 1;

	double	stepY = cubed->mini_map_height / column;
	double stepX = cubed->mini_map_width / row;
	double	startY = cubed->screen_height - cubed->mini_map_height;
	double	endY = startY + stepY;

	// printf("startY: %f\n", startY);

	while (y < (int)column)
	{
		int	startX = 0;
		int endX = stepX;
		int x = 0;
		while (x < (int)row)
		{
			if (worldMap[y][x] == 0)
			{
				draw_color_stripe((int) startX, (int) endX, (int) startY, (int) endY, colorBlack, cubed);
			}
			else if (worldMap[y][x] == 1)
			{
				draw_color_stripe((int) startX + border, (int) endX - border, (int) startY + border, 
					(int) endY - border, colorWhite, cubed);
			}
			startX = endX;
			endX += stepX;
			x++;
		}
		startY = endY;
		endY += stepY;
		y++;
	}
	player(cubed);
}