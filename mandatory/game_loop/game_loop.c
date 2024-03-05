/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:25:02 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/05 15:09:26 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief convert player start position from array x, y into image pixel location
static void	load_player_start_position(t_map *map, t_ve2 *player_pos)
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
				player_pos->x = (x * GRID_SIZE) + (GRID_SIZE / 2);
				player_pos->y = (y * GRID_SIZE) + (GRID_SIZE / 2);
				break ;
			}
		}
	}
}

/// @brief setup and initialize game variables
static void	init_game_vars(t_cub *cub, t_map *map, t_game *game, t_ve2 *player_pos)
{
	load_player_start_position(map, player_pos);
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
static void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", false);
	if (!cub->mlx)
		clean_exit(cub, NULL, errno);
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->img)
		clean_exit(cub, NULL, errno);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

void	start_game(t_cub *cub, t_map *map)
{
	t_game	game;
	t_ve2	player_pos;

	init_game_vars(cub, map, &game, &player_pos);
	init_mlx(cub);
	register_events(cub);
	mlx_loop(cub->mlx);
}