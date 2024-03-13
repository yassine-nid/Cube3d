/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:55:13 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/10 10:30:45 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	ang_to_rad(double angle)
{
	return ((angle * PI) / 180);
}

/// @brief returns a point (Distance)away
/// from the (start_pos)position using the angle
/// @param start_pos the position which will be used as a starting point
/// @param result a vector containing the calculated point
/// @param dis how many pixels away the point is
void	calc_direction(const t_ve2 *st_pos, t_ve2 *res, double dis, double angle)
{
	res->x = (dis * cos(ang_to_rad(360 - angle))) + st_pos->x;
	res->y = (dis * sin(ang_to_rad(360 - angle))) + st_pos->y;
}

/// @brief makes sure the angle is between 0 and 359
double	clamp_angle(double angle)
{
	if (angle >= 0)
		angle = fmod(angle, 360);
	else
		angle = fmod(angle, 360) + 360;
	return (angle);
}

/// @brief for debugging only
void	draw_line(t_ve2 start, double len, int color, int line_size, double angle, mlx_image_t *img)
{
	t_ve2	result;

	for (double line_len = 0; line_len <= len; line_len++)
	{
		calc_direction(&start, &result, line_len, angle);
		if (result.x < 0 || result.y < 0)
			break ;
		if (result.x >= img->width || result.y >= img->height)
			break ;
		for (int extra_width = -(line_size / 2); extra_width < line_size / 2; extra_width++)
		{
			int x_wid = result.x + extra_width;
			mlx_put_pixel(img, x_wid, result.y, color);
		}
	}
}
