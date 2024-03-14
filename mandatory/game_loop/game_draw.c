/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 00:12:02 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 02:05:33 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_sky_and_floor(t_game *game, t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (int)game->game_img->height)
	{
		x = -1;
		while (++x < (int)game->game_img->width)
		{
			if (y < (int)game->game_img->height / 2)
				mlx_put_pixel(game->game_img, x, y, map->c_int_color);
			else
				mlx_put_pixel(game->game_img, x, y, map->f_int_color);
		}
	}
}

static void	draw_map(t_cub *cub, t_game *game)
{
	double angle = cub->game->angle;
	int	ray_count = (int)game->game_img->width;
	
	angle += 30;
	angle = clamp_angle(angle);
	uint32_t len = 100;
	double stripe_size = game->game_img->width / ray_count;
	int color = 0;
	
	// draw strips
	for (int i = 0; i <= ray_count; i++)
	{
		t_rayhit hit = ray_cast(cub, angle, WALL);
		
		double rrrrang = clamp_angle(angle - cub->game->angle);
		hit.hit_distance = hit.hit_distance * 112;
		hit.hit_distance = hit.hit_distance * cos(ang_to_rad(rrrrang));
		if (hit.did_hit_target == true)
		{
			color = 0xFFFFFF;
			if (!hit.is_vertical)
				color = 0xFFFFD0;
			if (hit.hit_distance > 0)
			{
				len /= (hit.hit_distance * 0.03);
				len = (64 * 320) / hit.hit_distance;
				if (len >= game->game_img->height / 2)
					len = game->game_img->height / 2;
				if (len < 0)
					len = 0;
			}
		}
		else
		{
			color = 0;
			len = 0;
		}
		int	stripe_start_pos = i * stripe_size;
		
		t_stripe_data data;
		data.color = color;
		data.start_x_pos = stripe_start_pos;
		data.end_x_pos = stripe_start_pos + stripe_size;
		data.height = len;
		data.img = game->game_img;
		draw_stripe(&data);
		angle -= ((double)60 / (double)ray_count);
		angle = clamp_angle(angle);
	}
}

void	do_draw_game(t_cub *cub, t_game *game, t_map *map)
{
	(void)cub;
	draw_sky_and_floor(game, map);
	draw_map(cub, game);
}