/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:06:28 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/01 17:45:57 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief combines the provided Red, Green, Blue channels into a single color
static unsigned int	combine_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return ((int)r << 24 | (int)g << 16 |  (int)b << 8 | (int)255);
}

static void	clean_splitted(char **splitted)
{
	int	index;

	index = -1;
	while (splitted[++index])
		free(splitted[index]);
	free(splitted);
}

/// @brief checks if the given str only contains digits between optional spaces
static void	validate_color_str(t_cub *cub, char *str, char **splitted)
{
	if (!str)
		return ;
	while (ft_isspace(*str))
		str++;
	while (*str <= '9' && *str >= '0')
		str++;
	while (ft_isspace(*str))
		str++;
	if (*str && *str != '\n')
	{
		clean_splitted(splitted);
		clean_exit(cub, "Colors format R,G,B colors in range [0,255]", 1);
	}
}

/// @brief splits the line into seperate R, G, B, and returnes them combined
static unsigned int	get_color(t_cub *cub, char *line)
{
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
	char				**splitted_line;
	int					index;

	splitted_line = ft_split(line, ',');
	if (!splitted_line)
		clean_exit(cub, NULL, errno);
	index = -1;
	while (splitted_line[++index])
	{
		validate_color_str(cub, splitted_line[index], splitted_line);
		if (index == 0)
			r = ft_atoi(splitted_line[index]);
		if (index == 1)
			g = ft_atoi(splitted_line[index]);
		if (index == 2)
			b = ft_atoi(splitted_line[index]);
	}
	clean_splitted(splitted_line);
	if (r > 255 || g > 255 || b > 255)
		clean_exit(cub, "Colors format R,G,B colors in range [0,255]", 1);
	return (combine_rgb(r, g, b));
}

/// @brief transforms the parsed colors from a str to an int
void	colors_parse(t_cub *cub, t_map *map)
{
	map->c_int_color = get_color(cub, map->ceiling_color);
	map->f_int_color = get_color(cub, map->flor_color);
}
