/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:14:14 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/15 22:02:56 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief sets up and starts the game loop
void	do_game(t_cub *cub)
{
	do_init_game(cub, cub->game, cub->map_data);
	register_events(cub);
	mlx_loop(cub->game->mlx);
}