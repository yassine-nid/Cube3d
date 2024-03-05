/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:18:22 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/05 15:09:06 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	do_draw_player(t_cub *cub, t_map *map, t_game *game)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;

	y = -(PLAYER_SIZE / 2) - 1;
	while (++y < (PLAYER_SIZE / 2))
	{
		x = -(PLAYER_SIZE / 2) - 1;
		while (++x < (PLAYER_SIZE / 2))
		{
			draw_x = game->player_pos->x + x;
			draw_y = game->player_pos->y + y;
			mlx_put_pixel(cub->img, draw_x, draw_y, map->c_int_color);
		}
	}
}

void	draw_player(t_cub *cub, t_map *map)
{
	do_draw_player(cub, map, cub->game);

	
	double angle = cub->game->angle;
	
	angle -= 30;
	angle = clamp_angle(angle);

	for (int i = 0; i < 60; i++)
	{
		t_rayhit ray_to_draw = ray_cast(cub, angle, WALL);
		
		int color = 0xF34D8A;
		draw_line(cub, *cub->game->player_pos, ray_to_draw.hit_distance, color, 5, angle);

		angle++;
		angle = clamp_angle(angle);
	}
	
}
