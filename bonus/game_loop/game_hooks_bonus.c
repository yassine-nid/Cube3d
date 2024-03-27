/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:52:39 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/27 22:49:00 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/// @brief MLX event for when a key is pressed
static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub		*cub;
	t_game		*game;
	t_inputs	*inputs;

	(void) keydata;
	cub = (t_cub *)param;
	game = cub->game;
	inputs = &game->m_inputs;
	inputs->key_forward = mlx_is_key_down(game->mlx, MLX_KEY_W);
	inputs->key_backward = mlx_is_key_down(game->mlx, MLX_KEY_S);
	inputs->key_left = mlx_is_key_down(game->mlx, MLX_KEY_A);
	inputs->key_right = mlx_is_key_down(game->mlx, MLX_KEY_D);
	inputs->key_turn_left = mlx_is_key_down(game->mlx, MLX_KEY_LEFT);
	inputs->key_turn_right = mlx_is_key_down(game->mlx, MLX_KEY_RIGHT);
	inputs->key_close_game = mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE);
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))
		on_interact_clicked(cub);
}

/// @brief MLX event for when the cursor is moved
static void	cursor_hook(double xpos, double ypos, void *param)
{
	t_cub		*cub;
	t_inputs	*inputs;

	(void)ypos;
	cub = (t_cub *)param;
	inputs = &cub->game->m_inputs;
	inputs->change_x += (inputs->old_x - xpos);
	if (inputs->old_x == -1)
		inputs->change_x = 0;
	inputs->old_x = xpos;
}

long long	get_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL);
}

/// @brief MLX event for the window update loop
static void	loop_hook(void *param)
{
	t_cub	*cub;
	t_game	*game;

	cub = (t_cub *)param;
	game = cub->game;
	game->preveus_time = game->current_time;
	game->current_time = get_time();
	game->frame_time = (game->current_time - game->preveus_time) / 1000.0;
	game->frame_rate = 1.0 / game->frame_time;
	do_handle_keys(cub, game);
	do_draw_game(cub, game, cub->map_data);
	do_draw_mini_map(cub, game, cub->map_data);
	if (game->stop)
	{
		sleep(3);
		cleanup(cub);
		exit(0);
	}
	if (game->win)
		win(cub);
	if (game->loose)
		loose(cub);
}

/// @brief listen to relavent events
void	register_events(t_cub *cub)
{
	mlx_key_hook(cub->game->mlx, key_hook, cub);
	mlx_cursor_hook(cub->game->mlx, cursor_hook, cub);
	mlx_loop_hook(cub->game->mlx, loop_hook, cub);
}
