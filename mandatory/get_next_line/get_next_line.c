/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 02:29:05 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/27 12:51:38 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*clean_buffer(char *buffer)
{
	int	start_n;
	int	end_n;

	start_n = 0;
	while (buffer[start_n] != '\0' && buffer[start_n] != '\n')
		start_n++;
	if (buffer[start_n] == '\0' || buffer[start_n + 1] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	start_n++;
	end_n = start_n;
	while (buffer[end_n])
		end_n++;
	end_n = 0;
	while (buffer[start_n] != '\0')
		buffer[end_n++] = buffer[start_n++];
	buffer[end_n] = '\0';
	return (buffer);
}

char	*restore_from_buffer(char *buffer, int *is_nln)
{
	char	*restored;
	int		i;

	*is_nln = 0;
	if (str_len(buffer, NULL) <= 0)
		return (NULL);
	restored = malloc((sizeof * restored) * (str_len(buffer, NULL) + 1));
	if (restored == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0')
	{
		restored[i] = buffer[i];
		if (buffer[i] == '\n')
		{
			*is_nln = 1;
			i++;
			break ;
		}
		i++;
	}
	restored[i] = '\0';
	return (restored);
}

int	do_read(int *is_nln, int fd, char *buff, char **return_v)
{
	char	*temp;
	int		read_value;

	read_value = 0;
	temp = NULL;
	while (*is_nln == 0)
	{
		read_value = read(fd, buff, BUFFER_SIZE);
		if (read_value <= 0)
			return (1);
		buff[read_value] = '\0';
		temp = append(buff, *return_v, is_nln);
		if (temp == NULL)
			return (-1);
		*return_v = temp;
	}
	return (1);
}

char	*buffer_malloc(char *buff)
{
	buff = malloc((sizeof * buff) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	buff[0] = '\0';
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*return_v;
	int			is_nln;

	return_v = NULL;
	is_nln = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(buff), buff = NULL);
	if (buff != NULL)
	{
		return_v = restore_from_buffer(buff, &is_nln);
		if (return_v == NULL)
			return (free(buff), buff = NULL);
	}
	if (buff == NULL && is_nln == 0)
	{
		buff = buffer_malloc(buff);
		if (buff == NULL)
			return (free(return_v), NULL);
	}
	if (do_read(&is_nln, fd, buff, &return_v) == -1)
		return (free(return_v), free(buff), buff = NULL);
	if (buff != NULL)
		buff = clean_buffer(buff);
	return (return_v);
}
