/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:32:11 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/10 13:52:50 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	free(cub->map_data->ceiling_color);
	free(cub->map_data->flor_color);
	free(cub->map_data->tx_east);
	free(cub->map_data->tx_north);
	free(cub->map_data->tx_south);
	free(cub->map_data->tx_west);
	if (cub->fd != -1)
		close(cub->fd);
	
	int index = -1;
	while (++index < cub->map_data->map_size)
		free(cub->map_data->map[index]);
	free(cub->map_data->map);
	
	if (cub->game_img)
		mlx_delete_image(cub->mlx, cub->game_img);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
}

void	clean_exit(t_cub *cub, char *error, int code)
{
	cleanup(cub);
	log_error(error);
	exit(code);
}
