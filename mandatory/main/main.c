/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:48:47 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 20:08:49 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief initialize map varriables
static void	init_map(t_map *map)
{
	map->map = NULL;
	map->tx_north = NULL;
	map->tx_south = NULL;
	map->tx_west = NULL;
	map->tx_east = NULL;
	map->flor_color = NULL;
	map->f_int_color = 0;
	map->ceiling_color = NULL;
	map->c_int_color = 0;
	map->map_start_index = 0;
	map->longest_line = 0;
	map->map_size = 0;
	map->start_location_type = '\0';
}

/// @brief initialize game varriables
static void	init_game(t_game *game)
{
	game->game_img = NULL;
	game->e_txt = NULL;
	game->n_txt = NULL;
	game->s_txt = NULL;
	game->w_txt = NULL;
	game->mlx = NULL;
	game->m_inputs.key_backward = false;
	game->m_inputs.key_forward = false;
	game->m_inputs.key_left = false;
	game->m_inputs.key_right = false;
	game->m_inputs.key_turn_left = false;
	game->m_inputs.key_turn_right = false;
	game->m_inputs.key_close_game = false;
	game->current_time = 0;
	game->preveus_time = 0;
	game->frame_time = 0;
	game->frame_rate = 0;
}

static void	init(t_cub *cub, t_map *map, t_game *game)
{
	init_map(map);
	init_game(game);
	cub->fd = -1;
	cub->map_data = map;
	cub->game = game;
}

int	main(int argc, char *argv[])
{
	t_cub	cub;
	t_map	map;
	t_game	game;

	srand(time(NULL));
	init(&cub, &map, &game);
	do_parse(&cub, argc, argv);
	do_game(&cub);
	cleanup(&cub);
	return (EXIT_SUCCESS);
}
