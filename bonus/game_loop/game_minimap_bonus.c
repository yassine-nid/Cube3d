/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:15:04 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:55:19 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	if (map->map[(int)current_y][(int)current_x] == DOOR)
		mlx_put_pixel(game->minimap_img, x, y, MMAP_DOOR_COLOR);
	if (map->map[(int)current_y][(int)current_x] == map->start_location_type)
		mlx_put_pixel(game->minimap_img, x, y, MMAP_SPAWN_POINT_COLOR);
}

/// @brief keep drawing direction line pixel by pixel
static void	loop_and_draw_line(t_game *g, t_line_data data)
{
	while (1)
	{
		mlx_put_pixel(g->minimap_img, data.p0_x, data.p0_y, MMAP_PLAYER_COLOR);
		if (data.p0_x == data.p1_x && data.p0_y == data.p1_y)
			break ;
		data.temp_err = data.err;
		if (data.temp_err > -data.diffrence_x)
		{
			data.err -= data.diffrence_y;
			data.p0_x += data.direction_x;
		}
		if (data.temp_err < data.diffrence_y)
		{
			data.err += data.diffrence_x;
			data.p0_y += data.direction_y;
		}
	}
}

/// @brief prepare varriable to draw direction line
static void	draw_mmap_direction(t_game *game, t_vector2 center, t_vector2 dire)
{
	// understand how this works or delete
	t_line_data	line_data;

	line_data.p0_x = center.x;
	line_data.p0_y = center.y;
	line_data.p1_x = dire.x;
	line_data.p1_y = dire.y;
	line_data.diffrence_x = abs(line_data.p1_x - line_data.p0_x);
	line_data.diffrence_y = abs(line_data.p1_y - line_data.p0_y);
	line_data.direction_x = -1;
	line_data.direction_y = -1;
	if (line_data.p0_x < line_data.p1_x)
		line_data.direction_x = 1;
	if (line_data.p0_y < line_data.p1_y)
		line_data.direction_y = 1;
	line_data.err = -line_data.diffrence_y / 2;
	if (line_data.diffrence_x > line_data.diffrence_y)
		line_data.err = line_data.diffrence_x / 2;
	loop_and_draw_line(game, line_data);
}

/// @brief draw minimap
void	do_draw_mini_map(t_cub *cub, t_game *game, t_map *map)
{
	t_vector2	current_dire;
	t_vector2	center;
	int			y;
	int			x;

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
	center.x = MMAP_WIDTH / 2;
	center.y = MMAP_HEIGHT / 2;
	current_dire = calc_direction(center, MMAP_DIRECTION_LENGTH, game->angle);
	draw_mmap_direction(game, center, current_dire);
}
