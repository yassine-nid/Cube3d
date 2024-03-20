/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 00:23:54 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/20 00:49:49 by ynidkouc         ###   ########.fr       */
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

mlx_texture_t	*get_texture(t_stripe_data *data, t_cub *cub)
{
	if (data->direction == NORTH)
		return (cub->game->n_txt);
	else if (data->direction == SOUTH)
		return (cub->game->s_txt);
	else if (data->direction == EAST)
		return (cub->game->e_txt);
	else
		return (cub->game->w_txt);	
}

int	get_pix_color(t_rayhit hit, t_stripe_data *data, uint32_t y, t_cub *cub)
{
	int				xx;
	int				yy;
	mlx_texture_t	*txt;

	txt = get_texture(data, cub);
	yy = y - (data->img->height / 2) + data->height;
	yy = (((double) yy / (double) (data->height * 2)) * (double) txt->height);
	if (!hit.is_vertical)
		xx = (fmod(hit.point.x, 1) * (double) txt->width);
	else
		xx = (fmod(hit.point.y, 1) * (double) txt->width);
	xx = xx % txt->width;
	yy = yy % txt->height;
	return (*(((int *)(txt->pixels + yy * txt->width * 4 + xx * 4))));
}


void	draw_stripe(t_stripe_data *data, t_rayhit hit, t_cub *cub)
{
	uint32_t	y;
	int			color;

	if (data->start_x_pos < 0 || data->end_x_pos < 0)
		return ;
	if (data->start_x_pos > data->img->width)
		return ;
	if (data->end_x_pos > data->img->width)
		data->end_x_pos = data->img->width;
	while (data->start_x_pos <= data->end_x_pos)
	{
		y = (data->img->height / 2) - data->height_y;
		while (y < ((data->img->height / 2) + data->height_y))
		{
			color = get_pix_color(hit, data, y, cub);
			color = hit.is_vertical ? (color << 8) | (int)200 : (color << 8) | (int)255;
			mlx_put_pixel(data->img, data->start_x_pos, y, color);
			y++;
		}
		data->start_x_pos = data->start_x_pos + 1;
	}
}
