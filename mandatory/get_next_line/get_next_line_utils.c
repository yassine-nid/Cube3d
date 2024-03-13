/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 02:29:28 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/27 12:51:37 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	str_len(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1 != NULL && str1[i] != '\0' && str1[i] != '\n')
		i++;
	if (str1 != NULL && str1[i] == '\n')
		i++;
	while (str2 != NULL && str2[j] != '\0' && str2[j] != '\n')
		j++;
	if (str2 != NULL && str2[j] == '\n')
		j++;
	return (i + j);
}

char	*prepare_dst(char *dst, char *src, int *len)
{
	char	*temp;

	*len = 0;
	if (dst == NULL)
	{
		dst = malloc((sizeof * dst) * (str_len(src, NULL) + 1));
		if (dst == NULL)
			return (NULL);
	}
	else
	{
		temp = malloc((sizeof * temp) * (str_len(src, dst) + 1));
		if (temp == NULL)
			return (NULL);
		while (dst[*len] != '\0')
		{
			temp[*len] = dst[*len];
			*len = *len + 1;
		}
		temp[*len] = '\0';
		free(dst);
		return (temp);
	}
	return (dst);
}

char	*append(char *src, char *dst, int *new_l)
{
	int		dst_len;
	int		i;

	*new_l = 0;
	dst_len = 0;
	dst = prepare_dst(dst, src, &dst_len);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i + dst_len] = src[i];
		i++;
		if (src[i - 1] == '\n')
		{
			*new_l = 1;
			break ;
		}
	}
	dst[i + dst_len] = '\0';
	return (dst);
}
