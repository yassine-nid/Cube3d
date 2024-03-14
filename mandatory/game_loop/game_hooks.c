/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:10:19 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/14 01:13:48 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_cub	*cub;
	t_game	*game;
	double		move_amount;
	(void)keydata;

	cub = (t_cub *)param;;
	game = cub->game;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		clean_exit(cub, "Game closed", 0);
	move_amount = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_amount += 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_amount -= 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->angle += 3;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->angle  -= 3;
	game->angle = clamp_angle(game->angle);
	
	game->player_position = calc_direction(game->player_position, move_amount, game->angle);
}

static void	loop_hook(void* param)
{
	t_cub *cub = (t_cub *)param;

	do_draw_game(cub, cub->game, cub->map_data);
}

void	register_events(t_cub *cub)
{
	mlx_key_hook(cub->game->mlx, key_hook, cub);
	mlx_loop_hook(cub->game->mlx, loop_hook, cub);
}
