/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:10:19 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 04:15:49 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;
	t_game	*game;

	(void) keydata;
	cub = (t_cub *)param;
	game = cub->game;
	game->key_forward = mlx_is_key_down(game->mlx, MLX_KEY_W);
	game->key_backward = mlx_is_key_down(game->mlx, MLX_KEY_S);
	game->key_left = mlx_is_key_down(game->mlx, MLX_KEY_A);
	game->key_right = mlx_is_key_down(game->mlx, MLX_KEY_D);
	game->key_turn_left = mlx_is_key_down(game->mlx, MLX_KEY_LEFT);
	game->key_turn_right = mlx_is_key_down(game->mlx, MLX_KEY_RIGHT);
	game->key_close_game = mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE);
}

static void	cursor_hookm(double xpos, double ypos, void *param)
{
	t_cub *cub = (t_cub *)param;
	(void)ypos;

	cub->game->change_x += (cub->game->old_x - xpos);
	cub->game->old_x = xpos;
}

static void	loop_hook(void *param)
{
	t_cub *cub = (t_cub *)param;

	do_handle_keys(cub, cub->game, cub->map_data);
	do_draw_game(cub, cub->game, cub->map_data);
}

void	register_events(t_cub *cub)
{
	mlx_key_hook(cub->game->mlx, key_hook, cub);
	mlx_cursor_hook(cub->game->mlx, cursor_hookm, cub);
	mlx_loop_hook(cub->game->mlx, loop_hook, cub);
}
