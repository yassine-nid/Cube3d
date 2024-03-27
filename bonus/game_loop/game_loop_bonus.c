/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:52:50 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/27 03:55:16 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/// @brief sets up and starts the game loop
void	do_game(t_cub *cub)
{
	do_init_game(cub, cub->game, cub->map_data);
	register_events(cub);
	mlx_loop(cub->game->mlx);
}
