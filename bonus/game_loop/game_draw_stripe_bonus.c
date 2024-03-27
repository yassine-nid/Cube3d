/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_stripe_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:01:48 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:55:06 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/// @brief returns the correct texture for the given data
static mlx_texture_t	*get_texture(t_stripe_data *data, t_cub *cub)
{
	t_door	*door;

	if (data->hit->target == DOOR)
	{
		door = get_door_data(cub, *data->hit);
		if (door && !door->is_open)
			return (cub->game->door_text);
	}
	if (data->direction == NORTH)
		return (cub->game->n_txt);
	else if (data->direction == SOUTH)
		return (cub->game->s_txt);
	else if (data->direction == EAST)
		return (cub->game->e_txt);
	else
		return (cub->game->w_txt);
}

/// @brief returns the color for the given pixel
static int	get_pix_color(t_stripe_data *data, uint32_t y_strip, t_cub *cub)
{
	int				x_txt;
	int				y_txt;
	mlx_texture_t	*txt;

	txt = get_texture(data, cub);
	y_txt = y_strip - (data->img->height / 2) + data->height;
	y_txt = ((double)y_txt / (double)(data->height * 2)) * (double)txt->height;
	if (!data->hit->is_vertical)
		x_txt = (fmod(data->hit->point.x, 1) * (double)txt->width);
	else
		x_txt = (fmod(data->hit->point.y, 1) * (double)txt->width);
	x_txt = x_txt % txt->width;
	y_txt = y_txt % txt->height;
	return (*(((int *)(txt->pixels + y_txt * txt->width * 4 + x_txt * 4))));
}

/// @brief Draws a vertical stripe on the screen
/// @param data all the data needed to draw the stripe
void	draw_stripe(t_stripe_data data, t_cub *cub)
{
	uint32_t	y;
	int			color;

	if (data.start_x_pos < 0 || data.end_x_pos < 0)
		return ;
	if (data.start_x_pos > data.img->width)
		return ;
	if (data.end_x_pos > data.img->width)
		data.end_x_pos = data.img->width;
	while (data.start_x_pos <= data.end_x_pos)
	{
		y = (data.img->height / 2) - data.height_y;
		while (y < ((data.img->height / 2) + data.height_y))
		{
			color = get_pix_color(&data, y, cub);
			if (data.hit->is_vertical && color)
				color = (color << 8) | (int)200;
			else if (color)
				color = (color << 8) | (int)255;
			if (color)
				mlx_put_pixel(data.img, data.start_x_pos, y, color);
			y++;
		}
		data.start_x_pos = data.start_x_pos + 1;
	}
}
