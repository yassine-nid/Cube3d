/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:52:48 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/05 11:52:31 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_grid(t_cub *cub, int x, int y, int color)
{
	int	grid_x;
	int	drig_y;
	int	m_x;
	int	m_y;

	grid_x = 0;
	while (grid_x < GRID_SIZE)
	{
		drig_y = 0;
		while (drig_y < GRID_SIZE)
		{
			m_x = (x * GRID_SIZE) + grid_x;
			m_y = (y * GRID_SIZE) + drig_y;
			mlx_put_pixel(cub->img, m_x, m_y, color);
			if (drig_y < 2 || grid_x < 2)
				mlx_put_pixel(cub->img, m_x, m_y, 0x524747);
			drig_y++;
		}
		grid_x++;
	}
}

/// @brief draws the map gicing each node a grid size
void	draw_map(t_cub *cub, t_map *map)
{
	int	y;
	int	x;
	int	color;

	y = -1;
	while (++y < map->map_size)
	{
		x = -1;
		while (++x < map->longest_line)
		{
			color = 0x509C7E;
			if (map->map[y][x] == WALL)
				color = 0x56B7EF;
			if (map->map[y][x] == ' ')
				color = 0xB5CA00;
			draw_grid(cub, x, y, color);
		}
	}
}
