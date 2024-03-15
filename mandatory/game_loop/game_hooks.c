/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:10:19 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 20:16:33 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
}

static void	cursor_hookm(double xpos, double ypos, void *param)
{
	t_cub *cub = (t_cub *)param;
	t_inputs *inputs = &cub->game->m_inputs;
	(void)ypos;

	inputs->change_x += (inputs->old_x - xpos);
	if (inputs->old_x == -1)
		inputs->change_x = 0;
	inputs->old_x = xpos;
}

static void	loop_hook(void *param)
{
	t_cub *cub = (t_cub *)param;

	do_handle_keys(cub, cub->game, cub->map_data);
	do_draw_game(cub, cub->game, cub->map_data);
	do_draw_mini_map(cub, cub->game, cub->map_data);
}

void	register_events(t_cub *cub)
{
	mlx_key_hook(cub->game->mlx, key_hook, cub);
	mlx_cursor_hook(cub->game->mlx, cursor_hookm, cub);
	mlx_loop_hook(cub->game->mlx, loop_hook, cub);
}
