/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:25:02 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/13 03:18:07 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief convert player start position from array x, y into image pixel location
static void	load_player_start_position(t_cub *cub, t_map *map, t_ve2 *player_pos)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->map_size)
	{
		x = -1;
		while (++x < map->longest_line)
		{
			if (map->map[y][x] == map->start_location_type)
			{
				player_pos->x = (x * cub->grid_x) + (cub->grid_x / 2);
				player_pos->y = (y * cub->grid_y) + (cub->grid_y / 2);
				break ;
			}
		}
	}
}

/// @brief setup and initialize game variables
static void	init_game_vars(t_cub *cub, t_map *map, t_game *game, t_ve2 *player_pos)
{
	load_player_start_position(cub, map, player_pos);
	game->angle = 90;
	if (map->start_location_type == EAST)
		game->angle = 0;
	if (map->start_location_type == SOUTH)
		game->angle = 270;
	if (map->start_location_type == WEST)
		game->angle = 180;
	game->player_pos = player_pos;
	cub->game = game;
}

/// @brief creates mlx_ptr and the image to be used for drawing
static void	init_mlx(t_cub *cub, int m_y, int m_x)
{
	cub->win_height = ceil((double)1000 / (double)m_y) * m_y;
	cub->win_width = ceil((double)1780 / (double)m_x) * m_x;

	cub->grid_x = cub->win_width / cub->map_data->longest_line;
	cub->grid_y = cub->win_height / cub->map_data->map_size;

	cub->mlx = mlx_init(cub->win_width, cub->win_height, "cub3D", false);
	if (!cub->mlx)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);

	cub->game_img = mlx_new_image(cub->mlx, cub->win_width , cub->win_height);
	if (!cub->game_img)
		clean_exit(cub, NULL, errno);
	if (mlx_image_to_window(cub->mlx, cub->game_img, 0, 0) < 0)
        clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);


	cub->test_texture = mlx_load_png("./test_png.png");
	if (!cub->test_texture)
		clean_exit(cub, NULL, errno);
	
	
}

void	start_game(t_cub *cub, t_map *map)
{
	t_game	game;
	t_ve2	player_pos;

	init_mlx(cub, cub->map_data->map_size, cub->map_data->longest_line);
	init_game_vars(cub, map, &game, &player_pos);
	register_events(cub);
	mlx_loop(cub->mlx);
}