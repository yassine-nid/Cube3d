/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:06:11 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/25 03:00:51 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	angle_diff(double ang1, double ang2)
{
	double	diff;

	diff = ang1 - ang2;
	if (diff < -180)
		diff = 360 + diff;
	else if (diff > 180)
	{
		diff = 360 - diff;
		if (ang1 > ang2)
			diff = -diff;
	}
	return (diff);
}

t_sprite	sprite_init(double x, double y, t_cub *cub)
{
	t_sprite	sprite;
	t_vector2	dis;

	sprite.position.x = x;
	sprite.position.y = y;
	dis.x = cub->game->player_position.x - sprite.position.x;
	dis.y = cub->game->player_position.y - sprite.position.y;
	sprite.distance = sqrtf(dis.x * dis.x + dis.y * dis.y);
	sprite.angle = asin(fabs(dis.y) / sprite.distance);
	sprite.angle = sprite.angle * (double)(180 / PI);
	if (dis.y > 0 && dis.x > 0)
		sprite.angle = 180 - sprite.angle;
	else if (dis.y < 0 && dis.x < 0)
		sprite.angle = 360 - sprite.angle;
	else if (dis.y < 0 && dis.x > 0)
		sprite.angle += 180;
	sprite.height = (640) / sprite.distance;
	sprite.width = (640) / sprite.distance;
	sprite.txt = cub->game->e_txt;
	sprite.start_x = (double)(cub->game->game_img->width / 2) * \
		(1 + (angle_diff(cub->game->angle, sprite.angle)) / 30);
	sprite.start_x -= sprite.width / 2;
	sprite.start_y = cub->game->game_img->height / 2;
	return (sprite);
}

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
		ray = ray_cast(cub, angle, WALL);
		if (ray.hit_distance < sprite->distance)
			continue ;
		draw_sprite_strip(x, y, sprite, cub);
	}
	printf("angle: %f distance: %f\n", sprite->angle, sprite->distance);
	printf("px: %f py: %f game_angle: %f\n", cub->game->player_position.x, cub->game->player_position.y, cub->game->angle);
}
