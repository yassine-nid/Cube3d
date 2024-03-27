/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 00:23:54 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/20 23:21:45 by yzirri           ###   ########.fr       */
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

/// @brief attempts to laod a texture, exits when it fails
mlx_texture_t	*load_texture(t_cub *cub, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	return (texture);
}

/// @brief converts a texture into a image, exits when it fails
mlx_image_t	*texture_to_image(t_cub *cub, mlx_texture_t *texture)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(cub->game->mlx, texture);
	if (!img)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	return (img);
}
