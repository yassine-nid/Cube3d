/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:19:03 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/13 03:51:47 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_cub	*cub;
	t_game	*game;
	int		move_amount;
	(void)keydata;

	cub = (t_cub *)param;;
	game = cub->game;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		clean_exit(cub, "Game closed", 0);
	move_amount = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		move_amount += MOVE_SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		move_amount -= MOVE_SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		game->angle += ROTATE_SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		game->angle  -= ROTATE_SPEED;
	game->angle = clamp_angle(game->angle);
	
	calc_direction(game->player_pos, game->player_pos, move_amount, game->angle);
}

static void	loop_hook(void* param)
{
	t_cub *cub = (t_cub *)param;
	t_map *map = cub->map_data;

	draw_player(cub, map);
}

void	register_events(t_cub *cub)
{
	mlx_key_hook(cub->mlx, key_hook, cub);
	mlx_loop_hook(cub->mlx, loop_hook, cub);
}