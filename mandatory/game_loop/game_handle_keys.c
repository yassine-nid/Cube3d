/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handle_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:52:33 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/22 20:27:12 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief get the angle the next move is to be performed at
static double	get_move_angle(t_inputs *inputs, double angle)
{
	double	new_angle;

	new_angle = angle;
	if (inputs->key_right)
	{
		if (inputs->key_forward)
			new_angle = angle - 45;
		else if (inputs->key_backward)
			new_angle = angle - 135;
		else
			new_angle = angle - 90;
	}
	else if (inputs->key_left)
	{
		if (inputs->key_forward)
			new_angle = angle + 45;
		else if (inputs->key_backward)
			new_angle = angle + 135;
		else
			new_angle = angle + 90;
	}
	else if (inputs->key_backward)
		new_angle = angle + 180;
	return (clamp_angle(new_angle));
}

/// @brief returns if any movement key is clicked
static bool	is_movement_key_down(t_game *game)
{
	if (game->m_inputs.key_forward || game->m_inputs.key_backward)
		return (true);
	if (game->m_inputs.key_left || game->m_inputs.key_right)
		return (true);
	return (false);
}

/// @brief move the player if its a valid move
static void	do_move(t_cub *cub, t_game *game)
{
	t_rayhit	hit;
	double		move_ang;
	t_vector2	new_pos;
	double		move_speed;

	if (is_movement_key_down(game))
	{
		move_ang = get_move_angle(&game->m_inputs, game->angle);
		hit = get_valid_hit(cub, move_ang);
		if (hit.did_hit_target && hit.hit_distance <= 0.3)
			return ;
		move_speed = MOVE_SPEED * game->frame_time;
		new_pos = calc_direction(game->player_position, move_speed, move_ang);
		game->player_position = new_pos;
	}
}

/// @brief process buffered inputs
void	do_handle_keys(t_cub *cub, t_game *game)
{
	double		tmp_angle;
	t_inputs	*inputs;
	double		rotate_speed;

	inputs = &game->m_inputs;
	if (inputs->key_close_game)
		clean_exit(cub, "Game closed", EXIT_SUCCESS);
	rotate_speed = ROTATE_SPEED * game->frame_time;
	if (inputs->key_turn_left)
		game->angle = clamp_angle(game->angle + rotate_speed);
	if (inputs->key_turn_right)
		game->angle = clamp_angle(game->angle - rotate_speed);
	if (inputs->change_x != 0)
	{
		rotate_speed = MOUSE_ROTATE_SPEED * game->frame_time;
		tmp_angle = game->angle + (inputs->change_x * rotate_speed);
		game->angle = clamp_angle(tmp_angle);
		inputs->change_x = 0;
	}
	do_move(cub, game);
}
