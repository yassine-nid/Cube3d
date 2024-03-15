/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:15:04 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/15 21:19:15 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief draws the player color
static void	draw_player(t_game *game, int x, int y)
{
	if (x - MMAP_PLAYER_SIZE > MMAP_WIDTH / 2)
		return ;
	if (x + MMAP_PLAYER_SIZE < MMAP_WIDTH / 2)
		return ;
	if (y - MMAP_PLAYER_SIZE > MMAP_HEIGHT / 2)
		return ;
	if (y + MMAP_PLAYER_SIZE < MMAP_HEIGHT / 2)
		return ;
	mlx_put_pixel(game->minimap_img, x, y, MMAP_PLAYER_COLOR);
}

/// @brief draws map elemets near the player
static void	draw_map_elemets(t_game *game, t_map *map, int x, int y)
{
	double	current_x;
	double	current_y;

	current_x = ((double)x - (double)MMAP_EDGE) / MMAP_GRID;
	current_y = ((double)y - (double)MMAP_EDGE) / MMAP_GRID;
	current_x = floor(current_x + (game->player_position.x - 2.5));
	current_y = floor(current_y + (game->player_position.y - 2.5));
	if (current_x >= map->longest_line || current_y >= map->map_size)
		return ;
	if (current_x < 0 || current_y < 0)
		return ;
	if (map->map[(int)current_y][(int)current_x] == WALL)
		mlx_put_pixel(game->minimap_img, x, y, MMAP_WALL_COLOR);
	if (map->map[(int)current_y][(int)current_x] == map->start_location_type)
		mlx_put_pixel(game->minimap_img, x, y, MMAP_SPAWN_POINT_COLOR);
}

/// @brief draw minimap
void	do_draw_mini_map(t_cub *cub, t_game *game, t_map *map)
{
	int		x;
	int		y;

	(void)cub;
	y = MMAP_EDGE;
	while (y < MMAP_HEIGHT - MMAP_EDGE)
	{
		x = MMAP_EDGE;
		while (x < MMAP_WIDTH - MMAP_EDGE)
		{
			mlx_put_pixel(game->minimap_img, x, y, MMAP_BACKGROUND_COLOR);
			draw_map_elemets(game, map, x, y);
			draw_player(game, x, y);
			x++;
		}
		y++;
	}
}
