/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_map_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:28:37 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:55:00 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/// @brief claculates the distance and the height of the wall/texture
static void	distance_and_height(t_game *game, double ang, t_stripe_data *data)
{
	data->hit->hit_distance = data->hit->hit_distance * 112;
	data->hit->hit_distance *= cos(ang_to_rad(ang - game->angle));
	data->height = 64 * 1000;
	if (data->hit->hit_distance > 1)
		data->height /= data->hit->hit_distance;
	data->height_y = data->height;
	if (data->height > game->game_img->height / 2)
		data->height_y = game->game_img->height / 2;
}

/// @brief returns the direction of the current face
static char	get_direction(t_rayhit *hit, double angle)
{
	if (hit->is_vertical)
	{
		if (angle > 90 && angle < 270)
			return (WEST);
		else
			return (EAST);
	}
	if (angle > 180)
		return (SOUTH);
	else
		return (NORTH);
}

/// @brief performce a wall & door hit and returns which one is valid
t_rayhit	get_valid_hit(t_cub *cub, double angle)
{
	t_rayhit	wall_hit;
	t_rayhit	door_hit;
	t_door		*door;

	wall_hit = ray_cast(cub, angle, WALL);
	door_hit = ray_cast(cub, angle, DOOR);
	if (!door_hit.did_hit_target)
		return (wall_hit);
	if (door_hit.hit_distance >= wall_hit.hit_distance)
		return (wall_hit);
	door = get_door_data(cub, door_hit);
	if (!door)
		return (wall_hit);
	return (door_hit);
}

/// @brief calls draw stripe after calculating the direction
static void	do_draw(t_cub *cub, double ang, t_stripe_data *data, t_rayhit *hit)
{
	distance_and_height(cub->game, ang, data);
	data->direction = get_direction(hit, ang);
	draw_stripe(*data, cub);
}

/// @brief draw the map
void	do_draw_map(t_cub *cub, t_game *game, int ray_count, double stripe_siz)
{
	t_rayhit		hit;
	t_stripe_data	data;
	double			angle;
	int				index;

	angle = clamp_angle(cub->game->angle + 30);
	index = -1;
	while (++index < ray_count - 1)
	{
		data.start_x_pos = index * stripe_siz;
		data.end_x_pos = data.start_x_pos + stripe_siz;
		data.img = game->game_img;
		data.hit = &hit;
		hit = get_valid_hit(cub, angle);
		if (hit.did_hit_target)
			do_draw(cub, angle, &data, &hit);
		angle = clamp_angle(angle - ((double)60 / (double)ray_count));
	}
}
