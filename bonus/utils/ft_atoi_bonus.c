/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:13:29 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:55:58 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	ft_protect(long old, long new, int *isnegative)
{
	if (new < old && *isnegative < 0)
		return (1);
	else if (new < old && *isnegative > 0)
		return (2);
	else
		return (0);
}

static int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		isnegative;
	long	nb;

	nb = 0;
	isnegative = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		isnegative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		if (ft_protect(nb, nb * 10 + *str - '0', &isnegative) == 1)
			return (10000);
		else if (ft_protect(nb, nb * 10 + *str - '0', &isnegative) == 2)
			return (10000);
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * isnegative);
}
