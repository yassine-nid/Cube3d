/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:06:11 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/27 01:04:46 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_sprite_strip(int x, int y, t_sprite *sprite, t_cub *cub)
{
	int	xx;
	int	yy;
	int	color;

	while (y < sprite->start_y + (int) sprite->height
		&& y < (int) cub->game->game_img->height)
	{
		yy = (((double)(y - sprite->start_y)
					/ (double)(sprite->height)) * (double)sprite->txt->height);
		xx = (((double)(x - sprite->start_x)
					/ (double)(sprite->width)) * (double) sprite->txt->width);
		color = *(((int *)(sprite->txt->pixels + yy
						* 4 * sprite->txt->width + xx * 4)));
		if (color)
			color = (color << 8) | (int)255;
		else
		{
			y++;
			continue ;
		}
		mlx_put_pixel(cub->game->game_img, x, y, color);
		y++;
	}
}

void	draw_sprite(t_cub *cub, t_sprite *sprite)
{
	int			x;
	int			y;
	double		angle;
	t_rayhit	ray;

	if (fabs(angle_diff(cub->game->angle, sprite->angle)) > 40)
		return ;
	x = sprite->start_x - 1;
	while (++x < sprite->start_x + (int) sprite->width
		&& x < (int) cub->game->game_img->width)
	{
		if (x < 0)
			continue ;
		y = sprite->start_y;
		angle = cub->game->angle + ((((double) cub->game->game_img->width
						/ 2 - x) / ((double)cub->game->game_img->width / 2))
				* 30);
		ray = get_valid_hit(cub, clamp_angle(angle));
		if (ray.hit_distance < sprite->distance)
			continue ;
		draw_sprite_strip(x, y, sprite, cub);
	}
}
