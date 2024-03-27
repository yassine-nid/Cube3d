/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:56:58 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:56:00 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	container_size_calc(char const *s, char c, int *con_size)
{
	int	i;
	int	matched_characters;

	*con_size = 0;
	i = 0;
	while (1)
	{
		matched_characters = 0;
		while (s[i] != '\0' && s[i] != c)
		{
			i++;
			matched_characters++;
		}
		if (matched_characters > 0)
			*con_size = *con_size + 1;
		if (s[i] == '\0')
			break ;
		i++;
	}
}

static int	calculate_segments(char const *s, char c)
{
	int	segment_size;

	segment_size = 0;
	while (s[segment_size] != '\0' && s[segment_size] != c)
		segment_size++;
	return (segment_size);
}

static int	allocate_segment(char **container, int i, int segment_size)
{
	int	clean;

	container[i] = malloc(sizeof(char) * (segment_size + 1));
	if (container[i] == NULL)
	{
		clean = 0;
		while (clean < i)
		{
			free(container[clean]);
			clean++;
		}
		free(container);
		return (1);
	}
	return (0);
}

static void	populate_segment(const char *s, char c, char **container, int *i)
{
	int	segment_size;

	segment_size = 0;
	while (s[segment_size] != '\0' && s[segment_size] != c)
	{
		container[*i][segment_size] = s[segment_size];
		segment_size++;
	}
	container[*i][segment_size] = '\0';
	*i = *i + 1;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		container_size;
	char	**container;

	i = 0;
	if (s == NULL)
		return (NULL);
	container_size_calc(s, c, &container_size);
	container = malloc(sizeof * container * (container_size + 1));
	if (container == NULL)
		return (NULL);
	while (i < container_size)
	{
		if (calculate_segments(s, c) > 0)
		{
			if (allocate_segment(container, i, calculate_segments(s, c)) != 0)
				return (NULL);
			populate_segment(s, c, container, &i);
		}
		if (s[calculate_segments(s, c)] == '\0')
			break ;
		s = s + calculate_segments(s, c) + 1;
	}
	container[i] = NULL;
	return (container);
}
