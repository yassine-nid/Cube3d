/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:22:38 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 01:36:25 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief convert player start position from array[y][x] into image pixel location
static t_vector2	load_player_start_position(t_map *map)
{
	t_vector2	result;
	int			x;
	int			y;

	y = -1;
	while (++y < map->map_size)
	{
		x = -1;
		while (++x < map->longest_line)
		{
			if (map->map[y][x] == map->start_location_type)
			{
				result.x = x;
				result.y = y;
				if (result.x > 0)
					result.x -= 0.5;
				if (result.x > 0)
					result.y -= 0.5;
				break ;
			}
		}
	}
	return (result);
}

/// @brief setup and initialize game variables
static void	init_game_vars(t_map *map, t_game *game)
{
	game->player_position = load_player_start_position(map);
	game->angle = 90;
	if (map->start_location_type == EAST)
		game->angle = 0;
	if (map->start_location_type == SOUTH)
		game->angle = 270;
	if (map->start_location_type == WEST)
		game->angle = 180;
}

/// @brief creates mlx_ptr and the image to be used for drawing
static void	init_mlx(t_cub *cub, t_game *game)
{
	uint32_t	win_height;
	uint32_t	win_width;

	win_height = 1000;
	win_width = 1780;
	game->mlx = mlx_init(win_width, win_height, "cub3D", false);
	if (!game->mlx )
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	game->game_img = mlx_new_image(game->mlx, win_width, win_height);
	if (!game->game_img)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->game_img , 0, 0) < 0)
        clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
}

void	do_init_game(t_cub *cub, t_game *game, t_map *map)
{
	init_mlx(cub, game);
	init_game_vars(map, game);
}