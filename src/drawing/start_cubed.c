#include "../../include/cubed.h"

static void	position_mini_map(t_cubed *cubed)
{
	double	distanceX;
	double	distanceY;
	
	distanceX = - (cubed->posX - (cubed->mini_map_size / 2));
	distanceY = - (cubed->posY - (cubed->mini_map_size / 2));
	cubed->image->instances[0].x = distanceX * cubed->grid_width;
	cubed->image->instances[0].y = distanceY * cubed->grid_height;
	// mlx_set_instance_depth(cubed->image->instances, 1);
	// mlx_set_instance_depth(cubed->image_game->instances, 2);
}

void draw_screen(t_cubed *cubed)
{
	mini_map(cubed);
	raycasting(cubed);
	position_mini_map(cubed);
	clean_screen(cubed);
	draw_player_mini_map(cubed);
}

void	reset_settings(t_cubed *cubed)
{
	position_mini_map(cubed);
	clean_screen(cubed);
	raycasting(cubed);
	draw_player_mini_map(cubed);

}

static bool	initialize_cubed(t_cubed *cubed)
{
	// screen variables
	cubed->screen_width = 800;
	cubed->screen_height = 800;
	printf("%i = cubed->max_column\n", cubed->max_column);
	printf("%i = cubed->total_row\n", cubed->total_row);
	cubed->map_width = cubed->max_column;// misschien omdraaien
	cubed->map_height = cubed->total_row;
	cubed->grid_width = 40;
	cubed->grid_height = 40;
	printf("%f grid width\n", cubed->grid_width);
	cubed->mini_map_width = cubed->max_column  * cubed->grid_width;
	printf("%f = mini_map_width\n", cubed->mini_map_width);
	cubed->mini_map_height = cubed->total_row * cubed->grid_height; // misschien omdraaien
	cubed->mini_map_start_y = cubed->screen_height - cubed->mini_map_height;
	cubed->mini_map_size = 6;
	cubed->mini_map_middle = cubed->mini_map_size * cubed->grid_width / 2;
	cubed->draw_screen = true;
	cubed->stepXctrlA = 0;
	cubed->stepYctrlA = 0;
	cubed->stepXctrlD = 0;
	cubed->stepYctrlD = 0;

	// player variables
	printf("%i = start x\n", cubed->start_pos[X]);
	printf("%i = start y\n", cubed->start_pos[Y]);
	cubed->posX = cubed->start_pos[X];
	cubed->posY = cubed->start_pos[Y];
	cubed->mapX = 0;
	cubed->mapY = 0;
	cubed->dirX = 0.0;
	cubed->dirY = 0.0;
	cubed->pa = 0;
	cubed->fov = 0;
	cubed->stepX = 0;
	cubed->stepY = 0;
	cubed->raycasting_is_done = false;
	cubed->x_ray_length = 0;
	cubed->y_ray_length = 0;
	cubed->shortest_ray_length = 1000;
	cubed->side = false;
	cubed->player_to_grid_x = 5;
	cubed->player_to_grid_y = 5;
	cubed->mapX = (int)cubed->posX;
	cubed->mapY = (int)cubed->posY;
	return (true);
}

int32_t start_cubed(t_cubed *cubed)
{
	if (!initialize_cubed(cubed))
		return (1);
	if (!(cubed->mlx = mlx_init((int32_t)cubed->screen_width, (int32_t)cubed->screen_height, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(cubed->image = mlx_new_image(cubed->mlx, (int32_t)cubed->mini_map_width, (int32_t)cubed->mini_map_height)))
	{
		mlx_close_window(cubed->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(cubed->image_game = mlx_new_image(cubed->mlx, (int32_t)cubed->screen_width, (int32_t)cubed->screen_height)))
	{
		mlx_close_window(cubed->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(cubed->mlx, cubed->image, 0, 0) == -1)
	{
		mlx_close_window(cubed->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(cubed->mlx, cubed->image_game, 0, 0) == -1)
	{
		mlx_close_window(cubed->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	draw_screen(cubed);
	mlx_loop_hook(cubed->mlx, hooks, cubed);
	mlx_loop(cubed->mlx);
	mlx_terminate(cubed->mlx);
	return (EXIT_SUCCESS);
}
