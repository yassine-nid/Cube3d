/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handle_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:48:07 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/15 21:25:26 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_can_move(t_game *game, t_inputs *inputs, double *move_angle)
{
	*move_angle = game->angle;
	if (inputs->key_right)
	{
		if (inputs->key_forward)
			*move_angle = *move_angle - 45;
		else if (inputs->key_backward)
			*move_angle = *move_angle - 135;
		else
			*move_angle = *move_angle - 90;
	}
	else if (inputs->key_left)
	{
		if (inputs->key_forward)
			*move_angle = *move_angle + 45;
		else if (inputs->key_backward)
			*move_angle = *move_angle + 135;
		else
			*move_angle = *move_angle + 90;
	}
	else if (inputs->key_backward)
		*move_angle = *move_angle + 180;
	return (inputs->key_forward || inputs->key_backward
		|| inputs->key_left || inputs->key_right);
}

void	do_handle_keys(t_cub *cub, t_game *game, t_map *map)
{
	(void)map;
	double 		speed;
	double 		rotate_speed;
	double		move_angle;
	t_rayhit	hit;

	speed = 0.01;
	rotate_speed = 2;
	double mouse_rotate_speed = 0.1;
	if (game->m_inputs.key_close_game)
		clean_exit(cub, "Game closed", 0);
	if (game->m_inputs.key_turn_left)
		game->angle = clamp_angle(game->angle + rotate_speed);
	if (game->m_inputs.key_turn_right)
		game->angle = clamp_angle(game->angle - rotate_speed);
	if (game->m_inputs.change_x != 0)
	{
		game->angle = clamp_angle(game->angle + (game->m_inputs.change_x * mouse_rotate_speed));
		game->m_inputs.change_x = 0;
	}
	if (is_can_move(game, &game->m_inputs, &move_angle))
	{
		move_angle = clamp_angle(move_angle);
		hit = ray_cast(cub, move_angle, WALL);
		if (!hit.did_hit_target || hit.hit_distance > 0.03)
			game->player_position = calc_direction(game->player_position, speed, move_angle);
	}
}