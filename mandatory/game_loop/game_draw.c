/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 00:12:02 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 19:17:20 by yzirri           ###   ########.fr       */
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

static void	on_wall_hit(t_game *game, t_rayhit *hit, double angle, t_stripe_data *data)
{
	angle = clamp_angle(angle - game->angle);
	hit->hit_distance = hit->hit_distance * 112;
	hit->hit_distance = hit->hit_distance * cos(ang_to_rad(angle));
	
	data->color = 0xFFFFFF;
	if (!hit->is_vertical)
		data->color = 0xFFFFD0;
	data->height = game->game_img->height / 2;
	if (hit->hit_distance > 0)
	{
		data->height = (64 * 320) / hit->hit_distance;
		if (data->height >= game->game_img->height / 2)
			data->height = game->game_img->height / 2;
		if (data->height < 0)
			data->height = 0;
	}
}

static void	draw_map(t_cub *cub, t_game *game, int ray_count, double stripe_size)
{
	t_rayhit		hit;
	t_stripe_data	data;
	double			angle;
	int				index;

	angle = clamp_angle(cub->game->angle + 30);
	index = -1;
	while (++index < ray_count - 1)
	{
		hit = ray_cast(cub, angle, WALL);
		data.color = 0;
		data.height = 0;
		data.start_x_pos = index * stripe_size;
		data.end_x_pos = data.start_x_pos + stripe_size;
		data.img = game->game_img;
		if (hit.did_hit_target)
			on_wall_hit(game, &hit, angle, &data);
		draw_stripe(&data);
		angle = clamp_angle(angle - ((double)60 / (double)ray_count));
	}
}

void	do_draw_game(t_cub *cub, t_game *game, t_map *map)
{
	int		ray_count;
	double	stripe_size;

	ray_count = (int)game->game_img->width;
	stripe_size = game->game_img->width / ray_count;
	draw_sky_and_floor(game, map);
	draw_map(cub, game, ray_count, stripe_size);
}
