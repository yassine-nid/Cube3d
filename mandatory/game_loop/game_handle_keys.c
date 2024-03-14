/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handle_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:48:07 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 04:18:58 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_can_move(t_game *game, double *move_angle)
{
	*move_angle = game->angle;
	if (game->key_right)
	{
		if (game->key_forward)
			*move_angle = *move_angle - 45;
		else if (game->key_backward)
			*move_angle = *move_angle - 135;
		else
			*move_angle = *move_angle - 90;
	}
	else if (game->key_left)
	{
		if (game->key_forward)
			*move_angle = *move_angle + 45;
		else if (game->key_backward)
			*move_angle = *move_angle + 135;
		else
			*move_angle = *move_angle + 90;
	}
	else if (game->key_backward)
		*move_angle = *move_angle + 180;
	return (game->key_forward || game->key_backward
		|| game->key_left || game->key_right);
}

void	do_handle_keys(t_cub *cub, t_game *game, t_map *map)
{
	(void)cub;
	(void)map;
	double 		speed;
	double 		rotate_speed;
	double		move_angle;
	t_rayhit	hit;

	speed = 0.01;
	rotate_speed = 2;
	double mouse_rotate_speed = 0.1;
	if (game->key_close_game)
		clean_exit(cub, "Game closed", 0);
	if (game->key_turn_left)
		game->angle = clamp_angle(game->angle + rotate_speed);
	if (game->key_turn_right)
		game->angle = clamp_angle(game->angle - rotate_speed);
	if (game->change_x != 0)
	{
		game->angle = clamp_angle(game->angle + (game->change_x * mouse_rotate_speed));
		game->change_x = 0;
	}
	if (is_can_move(game, &move_angle))
	{
		move_angle = clamp_angle(move_angle);
		hit = ray_cast(cub, move_angle, WALL);
		if (!hit.did_hit_target || hit.hit_distance > 0.2)
			game->player_position = calc_direction(game->player_position, speed, move_angle);
	}
}