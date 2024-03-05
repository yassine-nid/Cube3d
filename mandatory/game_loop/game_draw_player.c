/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:18:22 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/05 15:59:37 by yzirri           ###   ########.fr       */
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


static void	draw_sky_and_floor(t_cub *cub, t_map *map)
{
	// sky
	for (int y = 0; y < WIN_HEIGHT / 2; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			mlx_put_pixel(cub->img, x, y, map->c_int_color);
	
	// floor
	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			mlx_put_pixel(cub->img, x, y, map->f_int_color);
}


void	draw_player(t_cub *cub, t_map *map)
{
	draw_sky_and_floor(cub, map);
	
	if (0)
		do_draw_player(cub, map, cub->game);

	

	double angle = cub->game->angle;
	int pixel_per_ray = WIN_WIDTH / 60;

	angle -= 30;
	angle = clamp_angle(angle);
	int x_tss = 0;

	for (int i = 0; i < 60; i++)
	{
		t_rayhit hit = ray_cast(cub, angle, WALL);

		int y_start = 0;
		int	y_max = WIN_HEIGHT;
		
		int remover = hit.hit_distance / 10;
		if (remover <= 0)
			remover = 0;
		if (remover > 1300)
			remover = 1300;
		remover += 100;
		
		y_start += remover;
		y_max -= remover;
		
		
		for (int y = y_start; y < y_max; y++)
		{
			for (int x = 0; x < pixel_per_ray; x++)
			{
				if (hit.hit_target)
					mlx_put_pixel(cub->img, x + x_tss, y, 0x1C80F2);
				else
					mlx_put_pixel(cub->img, x + x_tss, y, 0xFFFFFF);
			}
		}
		x_tss += pixel_per_ray;
		
		
		


		
		// int color = 0xF34D8A;
		// draw_line(cub, *cub->game->player_pos, ray_to_draw.hit_distance, color, 5, angle);




		
		angle++;
		angle = clamp_angle(angle);
	}
	
}
