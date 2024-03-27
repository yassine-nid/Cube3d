/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:02:22 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:55:41 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/// @brief checks if there is only one map and nothing after it
static void	map_shape_validation(t_cub *cub, t_map *map, char *argv[])
{
	char	*line;

	open_map_file(cub, argv);
	read_x_lines(cub->fd, map->map_start_index - 1);
	while (1)
	{
		line = get_next_line(cub->fd);
		if (!line)
			break ;
		if (!*line || *line == '\n')
		{
			free(line);
			clean_exit(cub, "Map content has to be the last element", 1);
		}
		free(line);
	}
	close_map_file(cub);
}

/// @brief open file descriptor fd pointed in the cub struct
void	open_map_file(t_cub *cub, char *argv[])
{
	cub->fd = open(argv[1], O_RDONLY);
	if (cub->fd == -1)
		clean_exit(cub, NULL, errno);
}

/// @brief close file descriptor fd pointed in the cub struct and assigns it -1
void	close_map_file(t_cub *cub)
{
	close(cub->fd);
	cub->fd = -1;
}

/// @brief parse everything in the given file into a map struct
void	do_parse(t_cub *cub, int argc, char *argv[])
{
	if (argc != 2)
		clean_exit(cub, "Invalid argument count", 1);
	if (!is_valid_extention(argv[1], ".cub"))
		clean_exit(cub, "Invalid map file extention", 1);
	varriables_parse(cub, cub->map_data, NULL, argv);
	map_parse(cub, cub->map_data, argv);
	map_shape_validation(cub, cub->map_data, argv);
	colors_parse(cub, cub->map_data);
}
