/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:59:28 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/06 07:39:42 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief checks done after the raycast to validate the new point
static bool	post_ray_check(t_map *map, t_ve2 *pos, t_rayhit *hit, char target)
{
	int	x;
	int	y;

	x = (int)(pos->x / GRID_SIZE);
	y = (int)(pos->y / GRID_SIZE);
	if (x >= map->longest_line || x < 0)
		return (false);
	if (y >= map->map_size || y < 0)
		return (false);
	if (map->map[y][x] == target)
	{
		hit->hit_target = true;
		return (false);
	}
	return (true);
}

/// @brief calculate the next grid edge distance
/// in the given direction using an angle
static double	get_ray_distance(bool is_verti, t_ve2 *res_move, double angle)
{
	double	ray_distance;
	double	fmod_xy;

	if (is_verti)
	{
		fmod_xy = fmod(res_move->x, GRID_SIZE);
		if (angle > 270 || angle < 90)
			ray_distance = (GRID_SIZE - fmod_xy) / cos(ang_to_rad(360 - angle));
		else
			ray_distance = (fmod_xy) / cos(ang_to_rad(180 - angle));
		return (ray_distance);
	}
	fmod_xy = fmod(res_move->y, GRID_SIZE);
	ray_distance = (GRID_SIZE - fmod_xy) / cos(ang_to_rad(90 + angle));
	if (angle >= 0 && angle <= 180)
		ray_distance = fmod_xy / cos(ang_to_rad(90 - angle));
	return (ray_distance);
}

/// @brief prevent staying in the preveus grid that the hit happend in
static void	get_correct_grid(t_ve2 *res_move, bool is_vert, double angle)
{
	if (is_vert)
	{
		if (angle > 270 || angle < 90)
			res_move->x = res_move->x + 0.01;
		else
			res_move->x = res_move->x - 0.01;
		return ;
	}
	if (angle >= 0 && angle <= 180)
		res_move->y = res_move->y - 0.01;
	else
		res_move->y = res_move->y + 0.01;
}

/// @brief shoots a single ray horizontaly or verticaly
static t_rayhit	single_ray(t_cub *cub, double angle, bool is_ver, char target)
{
	t_rayhit	rayhit;
	double		ray_distance;
	t_ve2		result_move;
	int			fov;

	fov = 0;
	result_move.x = cub->game->player_pos->x;
	result_move.y = cub->game->player_pos->y;
	rayhit.hit_target = false;
	rayhit.hit_distance = 0;
	while (++fov < MAX_FOV)
	{
		ray_distance = get_ray_distance(is_ver, &result_move, angle);
		calc_direction(&result_move, &result_move, ray_distance, angle);
		get_correct_grid(&result_move, is_ver, angle);
		rayhit.hit_distance += ray_distance;
		if (!post_ray_check(cub->map_data, &result_move, &rayhit, target))
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
	if (horizontal_ray.hit_target && !vertical_ray.hit_target)
		return (horizontal_ray);
	else if (!horizontal_ray.hit_target && vertical_ray.hit_target)
		return (vertical_ray);
	else if (horizontal_ray.hit_distance <= vertical_ray.hit_distance)
		return (horizontal_ray);
	return (vertical_ray);
}
