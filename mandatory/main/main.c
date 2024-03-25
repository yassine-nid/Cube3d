/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:48:47 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/22 19:59:56 by yzirri           ###   ########.fr       */
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
	game->mimimap_texture = NULL;
	game->minimap_img = NULL;
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
	game->m_inputs.key_close_game= false;
	game->m_inputs.change_x = 0;
	game->m_inputs.old_x = -1;

	game->doors = NULL;
	game->door_texts = NULL;

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

void	leak_detector(void)
{
	//system("leaks cub3D");
}

int	main(int argc, char *argv[])
{
	t_cub	cub;
	t_map	map;
	t_game	game;

	atexit(leak_detector);
	init(&cub, &map, &game);
	do_parse(&cub, argc, argv);
	do_game(&cub);
	// printf("<NO>: [%s]\n", map.tx_north);
	// printf("<SO>: [%s]\n", map.tx_south);
	// printf("<WE>: [%s]\n", map.tx_west);
	// printf("<EA>: [%s]\n", map.tx_east);
	// printf("<F>: [%s]\n", map.flor_color);
	// printf("<C>: [%s]\n", map.ceiling_color);
	// printf("<First Line>: [%d]\n", map.map_start_index);
	cleanup(&cub);
	return (EXIT_SUCCESS);
}
