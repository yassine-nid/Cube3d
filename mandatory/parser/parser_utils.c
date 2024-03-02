/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:06:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/01 13:26:08 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief Returns the length of a string, ignoring the spaces at the end
int	str_len_no_endspace(char *line)
{
	int	index;
	int	temp_index;

	index = 0;
	while (line)
	{
		while (line[index] && !ft_isspace(line[index]))
			index++;
		temp_index = index;
		while (line[temp_index] && ft_isspace(line[temp_index]))
			temp_index++;
		if (!line[temp_index] || line[temp_index] == '\n')
			break ;
		index = temp_index;
	}
	return (index);
}

/// @brief remove the \\n at the end of a line if it exists
void	remove_new_line(char *line)
{
	int	line_len;

	if (!line)
		return ;
	line_len = ft_strlen(line);
	if (line_len >= 1 && line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
}

/// @brief Reads count amount of lines from a file descriptor, file must be open
void	read_x_lines(int fd, int count)
{
	int		index;
	char	*line;

	index = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		index++;
		free(line);
		if (index >= count)
			break ;
	}
}
