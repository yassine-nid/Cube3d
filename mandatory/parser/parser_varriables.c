/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_varriables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:50:06 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/13 20:00:31 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief removes the var name at the start of the line and any extra spaces
static void	trim_assign_var(t_cub *cub, char *line, char **var)
{
	int	index;

	index = 0;
	while (line[index] && !ft_isspace(line[index]))
		index++;
	while (line[index] && ft_isspace(line[index]))
		index++;
	*var = ft_strdup(line + index);
	free(line);
	if (!*var)
		return (clean_exit(cub, NULL, errno));
	index = -1;
	while ((*var)[++index])
	{
		if ((*var)[index] == '\n' && !(*var)[index + 1])
		{
			(*var)[index] = '\0';
			break ;
		}
	}
}

/// @brief checks if the line starts with (cmp), and puts it in in the var
static bool	assign_var(t_cub *cub, char *line, char **var, char *cmp)
{
	if (!*line || !*cmp || *line != *cmp)
		return (false);
	if (line[1] && cmp[1])
	{
		if (line[1] != cmp[1])
			return (false);
		if (!ft_isspace(line[2]))
			return (false);
	}
	if (line[1] && !cmp[1] && !ft_isspace(line[1]))
		return (false);
	if (*var != NULL)
	{
		free(line);
		clean_exit(cub, INVALID_MAP_CONTENT, 10);
	}
	trim_assign_var(cub, line, var);
	return (true);
}

static void	post_arg_validation(t_cub *cub, t_map *map)
{
	close_map_file(cub);
	if (!map->tx_north || !map->tx_south || !map->tx_west || !map->tx_east
		|| !map->flor_color || !map->ceiling_color)
		clean_exit(cub, INVALID_MAP_VARRIABLES, 1);
}

/// @brief takes varriables (NO/SO/...) from a file and saves them in a struct
void	varriables_parse(t_cub *cub, t_map *map, char *line, char *argv[])
{
	open_map_file(cub, argv);
	while (1)
	{
		line = get_next_line(cub->fd);
		if (!line)
			return ;
		map->map_start_index++;
		if (*line && assign_var(cub, line, &map->tx_north, "NO"))
			continue ;
		else if (*line && assign_var(cub, line, &map->tx_south, "SO"))
			continue ;
		else if (*line && assign_var(cub, line, &map->tx_west, "WE"))
			continue ;
		else if (*line && assign_var(cub, line, &map->tx_east, "EA"))
			continue ;
		else if (*line && assign_var(cub, line, &map->flor_color, "F"))
			continue ;
		else if (*line && assign_var(cub, line, &map->ceiling_color, "C"))
			continue ;
		else if (*line && *line != '\n')
			return (free(line), post_arg_validation(cub, map));
		free(line);
	}
	post_arg_validation(cub, map);
}
