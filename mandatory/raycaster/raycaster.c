/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:59:28 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 01:56:17 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief checks done after the raycast to validate the new point
static bool	post_checks(t_cub *cub, t_vector2 *pos, t_rayhit *hit, char target)
{
	int	x;
	int	y;

	x = (int)ceil(pos->x);
	y = (int)ceil(pos->y);
	if (x >= cub->map_data->longest_line || x < 0)
		return (false);
	if (y >= cub->map_data->map_size || y < 0)
		return (false);
	if (cub->map_data->map[y][x] == target)
	{
		hit->did_hit_target = true;
		return (false);
	}
	return (true);
}

/// @brief calculate the next grid edge distance
/// in the given direction using an angle
static double	distance(bool is_v, t_vector2 *r_move, double ang)
{
	double	ray_distance;
	double	fmod_xy;

	if (is_v)
	{
		fmod_xy = fmod(r_move->x, 1);
		if (ang > 270 || ang < 90)
			ray_distance = (1 - fmod_xy) / cos(ang_to_rad(360 - ang));
		else
			ray_distance = (fmod_xy) / cos(ang_to_rad(180 - ang));
		return (ray_distance);
	}
	fmod_xy = fmod(r_move->y, 1);
	ray_distance = (1 - fmod_xy) / cos(ang_to_rad(90 + ang));
	if (ang >= 0 && ang <= 180)
		ray_distance = fmod_xy / cos(ang_to_rad(90 - ang));
	return (ray_distance);
}

/// @brief prevent staying in the preveus grid that the hit happend in
static void	get_correct_grid(t_vector2 *res_move, bool is_vert, double angle)
{
	double	error_tolerance;

	error_tolerance = 0.001;
	if (is_vert)
	{
		if (angle > 270 || angle < 90)
		{
			res_move->x = res_move->x + error_tolerance;
		}
		else
		{
			res_move->x = res_move->x - error_tolerance;
		}
		return ;
	}
	if (angle >= 0 && angle <= 180)
		res_move->y = res_move->y - error_tolerance;
	else
		res_move->y = res_move->y + error_tolerance;
}

/// @brief shoots a single ray horizontaly or verticaly
static t_rayhit	single_ray(t_cub *cub, double angle, bool is_ver, char target)
{
	t_rayhit	rayhit;
	double		ray_distance;
	t_vector2	result_move;
	int			fov;

	fov = 0;
	result_move.x = cub->game->player_position.x;
	result_move.y = cub->game->player_position.y;
	rayhit.did_hit_target = false;
	rayhit.hit_distance = 0;
	rayhit.is_vertical = is_ver;
	while (++fov < /*MAX_FOV*/10)
	{
		ray_distance = distance(is_ver, &result_move, angle);
		result_move = calc_direction(result_move, ray_distance, angle);
		get_correct_grid(&result_move, is_ver, angle);
		rayhit.hit_distance += ray_distance;
		if (!post_checks(cub, &result_move, &rayhit, target))
			break ;
	}
	rayhit.target = target;
	rayhit.point = result_move;
	return (rayhit);
}

/// @brief shoots a ray in the a direction calculated by the angle
/// ,and returns the first point to intersect with the given symbol
t_rayhit	ray_cast(t_cub *cub, double angle, char target)
{
	t_rayhit	horizontal_ray;
	t_rayhit	vertical_ray;

	horizontal_ray = single_ray(cub, angle, false, target);
	vertical_ray = single_ray(cub, angle, true, target);
	if (horizontal_ray.did_hit_target && !vertical_ray.did_hit_target)
		return (horizontal_ray);
	else if (!horizontal_ray.did_hit_target && vertical_ray.did_hit_target)
		return (vertical_ray);
	else if (horizontal_ray.hit_distance <= vertical_ray.hit_distance)
		return (horizontal_ray);
	return (vertical_ray);
}
