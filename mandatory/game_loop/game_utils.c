/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 00:23:54 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 01:48:14 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief angle to radian
double	ang_to_rad(double angle)
{
	return ((angle * PI) / 180);
}

/// @brief returns a point (Distance)away
/// from the (start_pos)position using the angle
/// @param start_pos the position which will be used as a starting point
/// @param dis how many pixels away the point is
t_vector2	calc_direction(t_vector2 start_position, double dis, double angle)
{
	t_vector2	result;

	result.x = (dis * cos(ang_to_rad(360 - angle))) + start_position.x;
	result.y = (dis * sin(ang_to_rad(360 - angle))) + start_position.y;
	return (result);
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

/// @brief draws a line in the image, a line which has a height
/// and a width that starts from  and ends at x_end
void	draw_stripe(t_stripe_data *data)
{
	uint32_t	y;

	if (data->start_x_pos < 0 || data->end_x_pos < 0)
		return ;
	if (data->height > (data->img->height / 2))
		return ;
	if (data->start_x_pos > data->img->width)
		return ;
	if (data->end_x_pos > data->img->width)
		data->end_x_pos = data->img->width;
	while (data->start_x_pos <= data->end_x_pos)
	{
		y = (data->img->height / 2) - data->height;
		while (y < ((data->img->height / 2) + data->height))
		{
			mlx_put_pixel(data->img, data->start_x_pos, y, data->color);
			y++;
		}
		data->start_x_pos = data->start_x_pos + 1;
	}
}
