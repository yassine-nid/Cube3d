/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:31:42 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:55:47 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/// @brief saves the line in the map, matching its size to the longest line size
void	save_line(t_cub *cub, t_map *map, char **line, int map_index)
{
	int		line_len;
	char	*new_char;
	int		index;

	line_len = str_len_no_endspace(*line);
	if (line_len >= map->longest_line)
		return (map->map[map_index] = *line, (void) NULL);
	new_char = malloc(sizeof * new_char * (map->longest_line + 1));
	if (!new_char)
		return (free(*line), clean_exit(cub, NULL, errno));
	index = -1;
	while ((*line)[++index])
		new_char[index] = (*line)[index];
	while (index < map->longest_line)
		new_char[index++] = ' ';
	new_char[index] = '\0';
	return (free(*line), map->map[map_index] = new_char, (void) NULL);
}

/// @brief allocates and inits the map to null entries
void	alloc_init_map(t_cub *cub, t_map *map)
{
	int	index;

	index = 0;
	map->map = malloc ((sizeof * map->map) * map->map_size);
	if (!map->map)
		clean_exit(cub, NULL, errno);
	while (index < map->map_size)
		map->map[index++] = NULL;
}

/// @brief checks left and right of a node to make sure it has a valid type
bool	check_x(char **map, int len, int x, int y)
{
	int	tmp_x;

	tmp_x = x;
	while (tmp_x >= 0 && map[y][tmp_x] != WALL && !ft_isspace(map[y][tmp_x]))
		tmp_x--;
	if (tmp_x < 0 || map[y][tmp_x] != WALL)
		return (false);
	tmp_x = x;
	while (tmp_x < len && map[y][tmp_x] != WALL && !ft_isspace(map[y][tmp_x]))
		tmp_x++;
	if (tmp_x >= len || map[y][tmp_x] != WALL)
		return (false);
	return (true);
}

/// @brief checks up and down on the Y axis to make sure it has a valid type
bool	check_y(char **map, int len, int x, int y)
{
	int	tmp_y;

	tmp_y = y;
	while (tmp_y >= 0 && map[tmp_y][x] != WALL && !ft_isspace(map[tmp_y][x]))
		tmp_y--;
	if (tmp_y < 0 || map[tmp_y][x] != WALL)
		return (false);
	tmp_y = y;
	while (tmp_y < len && map[tmp_y][x] != WALL && !ft_isspace(map[tmp_y][x]))
		tmp_y++;
	if (tmp_y >= len || map[tmp_y][x] != WALL)
		return (false);
	return (true);
}
