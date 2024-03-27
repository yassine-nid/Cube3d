/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exits_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:32:11 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 22:06:06 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	cleanup_map(t_map *map)
{
	int	index;

	index = -1;
	while (++index < map->map_size)
		free(map->map[index]);
	free(map->map);
	free(map->tx_north);
	free(map->tx_south);
	free(map->tx_west);
	free(map->tx_east);
	free(map->flor_color);
	free(map->ceiling_color);
}

static void	log_error(char *error)
{
	ft_putstr_fd("Error\n", 2);
	if (!error)
	{
		perror("cub3D");
		return ;
	}
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	cleanup(t_cub *cub)
{
	cleanup_map(cub->map_data);
	cleanup_game(cub->game);
	if (cub->fd != -1)
		close(cub->fd);
}

void	cleanup_exit(t_cub *cub, char *msg)
{
	cleanup(cub);
	if (msg)
		ft_putstr_fd(msg, 1);
	exit(0);
}

void	clean_exit(t_cub *cub, char *error, int code)
{
	cleanup(cub);
	log_error(error);
	exit(code);
}
