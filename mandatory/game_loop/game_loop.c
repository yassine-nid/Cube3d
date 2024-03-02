/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:25:02 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/02 07:58:44 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	grid_size = 30;
int	player_x;
int player_y;

static void	draw_map(t_cub *cub, t_map *map)
{
	
	for (int y = 0; y < map->map_size; y++)
	{
		for (int x = 0; x < map->longest_line; x++)
		{
			int color = 0x509C7E;
			if (map->map[y][x] == WALL)
				color = 0x56B7EF;
			if (map->map[y][x] == ' ')
				color = 0xB5CA00;
			int index_x = 0;
			while (index_x < grid_size)
			{
				int index_y = 0;
				while (index_y < grid_size)
				{
					mlx_put_pixel(cub->img, (x * grid_size) + index_x
						, (y * grid_size) + index_y, color);
					index_y++;
				}
				index_x++;
			}

			mlx_put_pixel(cub->img, x, y, 0x509C7E);
		}
	}
}



static void	draw_player(t_cub *cub, t_map *map)
{
	int player_size = 10;
	
	// int index_x = 0;
	// while (index_x < grid_size / 2)
	// {
	// 	int index_y = 0;
	// 	while (index_y < grid_size / 2)
	// 	{
	// 		mlx_put_pixel(cub->img, (player_x * grid_size) + index_x
	// 			, (player_y * grid_size) + index_y, map->c_int_color);
	// 		index_y++;
	// 	}
	// 	index_x++;
	// }

	for (int y = grid_size - player_size; y < player_size; y++)
	{
		for (int x = grid_size - player_size; x < player_size; x++)
		{
			int draw_x = (player_x * grid_size) + x;
			int draw_y = (player_y * grid_size) + y;
			mlx_put_pixel(cub->img, draw_x, draw_y, map->c_int_color);
		}
	}
	return ;
	mlx_put_pixel(cub->img, player_x, player_y, map->c_int_color);

}

void	loop_hook(void* param)
{
	t_cub *cub = (t_cub *)param;
	t_map *map = cub->map_data;

	draw_map(cub, map);
	draw_player(cub, map);
}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_cub *cub = (t_cub *)param;
	
	(void)keydata;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		clean_exit(cub, "Closed", 0);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		player_y--;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		player_y++;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		player_x--;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		player_x++;
}

void	start_game(t_cub *cub, t_map *map)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", false);
	if (!cub->mlx)
		clean_exit(cub, NULL, errno);
	
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->img)
		clean_exit(cub, NULL, errno);
	
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);

	//draw_map(cub, map);

	for (int y = 0; y < map->map_size; y++)
	{
		for (int x = 0; x < map->longest_line; x++)
		{
			if (map->map[y][x] == EAST || map->map[y][x] == WEST
				|| map->map[y][x] == SOUTH || map->map[y][x] == NORTH)
			{
				player_x = x;
				player_y = y;
			}
		}
	}

	mlx_key_hook(cub->mlx, key_hook, cub);
	mlx_loop_hook(cub->mlx, loop_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}