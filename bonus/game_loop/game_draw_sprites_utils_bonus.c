/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_sprites_utils_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:33:30 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 04:05:23 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/// @brief calculate the differece between two angles
double	angle_diff(double ang1, double ang2)
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

void	sprite_init(t_cub *cub, t_sprite *sprite)
{
	t_vector2	dis;
	double		dis_y;

	dis.x = cub->game->player_position.x - sprite->position.x;
	dis.y = cub->game->player_position.y - sprite->position.y;
	sprite->distance = sqrtf(dis.x * dis.x + dis.y * dis.y);
	dis_y = fabs(dis.y) / sprite->distance;
	if (dis_y > 1)
		dis_y = 1;
	else if (dis_y < -1)
		dis_y = -1;
	sprite->angle = asin(dis_y);
	sprite->angle = sprite->angle * (double)(180 / PI);
	if (dis.y > 0 && dis.x > 0)
		sprite->angle = 180 - sprite->angle;
	else if (dis.y < 0 && dis.x < 0)
		sprite->angle = 360 - sprite->angle;
	else if (dis.y < 0 && dis.x > 0)
		sprite->angle += 180;
	sprite->height = (640) / sprite->distance;
	sprite->width = (640) / sprite->distance;
	sprite->start_x = (double)(cub->game->game_img->width / 2) * \
		(1 + (angle_diff(cub->game->angle, sprite->angle)) / 30);
	sprite->start_x -= sprite->width / 2;
	sprite->start_y = cub->game->game_img->height / 2;
}
