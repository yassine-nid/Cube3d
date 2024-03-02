/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:48:10 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/01 13:54:56 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief Counts the map size, and length of the longest map line
static void	count_map_size(t_cub *cub, t_map *map, char *argv[])
{
	char	*line;
	int		index;

	index = 0;
	map->map_size = 0;
	open_map_file(cub, argv);
	while (1)
	{
		line = get_next_line(cub->fd);
		if (!line)
			break ;
		index++;
		if (index >= map->map_start_index)
		{
			map->map_size++;
			if (map->longest_line < str_len_no_endspace(line))
				map->longest_line = str_len_no_endspace(line);
		}
		free(line);
	}
	close_map_file(cub);
}

/// @brief Saves the map into a pointer to an array of strings
static void	save_map(t_cub *cub, t_map *map, char *argv[])
{
	int		index;
	char	*line;

	open_map_file(cub, argv);
	read_x_lines(cub->fd, map->map_start_index - 1);
	index = 0;
	while (1)
	{
		line = get_next_line(cub->fd);
		if (!line)
			break ;
		remove_new_line(line);
		save_line(cub, map, &line, index);
		index++;
	}
	close_map_file(cub);
}

/// @brief validates the symbols in the map and there quantity
static void	validate_map_symbols(t_cub *cub, t_map *map, int x, int y)
{
	y = -1;
	while (++y < map->map_size)
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (ft_isspace(map->map[y][x]) || map->map[y][x] == WALL)
				continue ;
			if (map->map[y][x] == EMPTY)
				continue ;
			if (map->map[y][x] == NORTH || map->map[y][x] == SOUTH
				|| map->map[y][x] == EAST || map->map[y][x] == WEST)
			{
				if (map->start_location_type)
					clean_exit(cub, "Multiple start positions", 1);
				map->start_location_type = map->map[y][x];
				continue ;
			}
			clean_exit(cub, "Invalid Map symbol", 1);
		}
	}
	if (!map->start_location_type)
		clean_exit(cub, "there is no player start position", 1);
}

/// @brief Validates if the map is surrounded by walls
static void	validate_map_walls(t_cub *cub, t_map *map)
{
	int	y;
	int	x;

	if (map->map_size <= 2)
		clean_exit(cub, INVALID_MAP_CHECK, 1);
	y = -1;
	while (++y < map->map_size)
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (ft_isspace(map->map[y][x]) || map->map[y][x] == WALL)
				continue ;
			if (!check_x(map->map, map->longest_line, x, y))
				clean_exit(cub, "Invalid map walls", 1);
			if (!check_y(map->map, map->map_size, x, y))
				clean_exit(cub, "Invalid map walls", 1);
			if (!check_angles(map, x, y))
				clean_exit(cub, "Invalid map walls", 1);
		}
	}
}

/// @brief takes a map from a file and puts it in a pointer to an array of strs
void	map_parse(t_cub *cub, t_map *map, char *argv[])
{
	count_map_size(cub, map, argv);
	alloc_init_map(cub, map);
	save_map(cub, map, argv);
	validate_map_walls(cub, map);
	validate_map_symbols(cub, map, 0, 0);
}
