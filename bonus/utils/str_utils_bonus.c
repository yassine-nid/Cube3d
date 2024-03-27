/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:33:48 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:56:02 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	ft_putstr_fd(char *s, int fd)
{
	char	c;
	int		return_val;

	if (s == NULL)
		return (write(fd, "", 0));
	return_val = 0;
	while (*s)
	{
		c = *s;
		return_val += write(fd, &c, 1);
		s++;
	}
	return (return_val);
}

bool	is_valid_extention(const char *src, const char *ne)
{
	size_t	i;
	size_t	j;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i])
	{
		j = 0;
		while (src[j + i] == ne[j] && ne[j] && src[i + j])
			j++;
		if (ne[j] == '\0' && src[j + i] == '\0')
			return (true);
		i++;
	}
	return (false);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*s1_cpy;

	s1_cpy = malloc (sizeof * s1_cpy * (ft_strlen(s1) + 1));
	if (s1_cpy == NULL)
		return (NULL);
	ft_memcpy(s1_cpy, s1, ft_strlen(s1) + 1);
	return (s1_cpy);
}
