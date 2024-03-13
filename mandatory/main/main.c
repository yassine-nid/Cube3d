/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:48:47 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/10 13:52:30 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_vars(t_cub *cub, t_map *map)
{
	cub->fd = -1;
	cub->map_data = map;
	map->ceiling_color = NULL;
	map->f_int_color = 0;
	map->c_int_color = 0;
	map->flor_color = NULL;
	map->tx_east = NULL;
	map->tx_north = NULL;
	map->tx_south = NULL;
	map->tx_west = NULL;
	map->map_start_index = 0;
	map->longest_line = 0;
	map->map = NULL;
	map->map_size = 0;
	map->start_location_type = '\0';
	cub->game = NULL;
	cub->game_img = NULL;
	cub->mlx = NULL;
}

void	leak_detector()
{
	system("leaks cub3D");
}

int	main(int argc, char *argv[])
{
	t_cub	cub;
	t_map	map;

	// atexit(leak_detector);
	init_vars(&cub, &map);
	do_parse(&cub, argc, argv);

	// printf("<NO>: [%s\n", map.tx_north);
	// printf("<SO>: [%s\n", map.tx_south);
	// printf("<WE>: [%s\n", map.tx_west);
	// printf("<EA>: [%s\n", map.tx_east);
	// printf("<F>: [%s\n", map.flor_color);
	// printf("<C>: [%s\n", map.ceiling_color);
	// printf("<First Line>: [%d]\n", map.map_start_index);

	// int index = 0;
	// while (index < map.map_size)
	// {
	// 	printf("%s", map.map[index]);
	// 	printf(".\n");
	// 	index++;
	// }
	
	
	
	// for (int i = 0; i < width; i++)
	// {
	// 	for (int j = 0; j < height; j++)
	// 	{
	// 		mlx_put_pixel(img_c, i, j, map.c_int_color);
	// 	}
	// }
	
	// mlx_texture_t texture = texture
	// mlx_texture_to_image(ptr, )
	

	start_game(&cub, &map);
	cleanup(&cub);
	return 0;
}