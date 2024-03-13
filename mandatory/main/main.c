/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:48:47 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/13 20:14:52 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static void	init(t_cub *cub, t_map *map)
{
	init_map(map);
	cub->fd = -1;
	cub->map_data = map;
}

void	leak_detector(void)
{
	system("leaks cub3D");
}

int	main(int argc, char *argv[])
{
	t_cub	cub;
	t_map	map;

	atexit(leak_detector);
	init(&cub, &map);
	do_parse(&cub, argc, argv);
	printf("<NO>: [%s]\n", map.tx_north);
	printf("<SO>: [%s]\n", map.tx_south);
	printf("<WE>: [%s]\n", map.tx_west);
	printf("<EA>: [%s]\n", map.tx_east);
	printf("<F>: [%s]\n", map.flor_color);
	printf("<C>: [%s]\n", map.ceiling_color);
	printf("<First Line>: [%d]\n", map.map_start_index);
	cleanup(&cub);
	return (EXIT_SUCCESS);
}
