/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:52:26 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/24 22:37:14 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief draws the sky and floot
static void	do_draw_sky_and_floor(t_game *game, t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (int)game->game_img->height)
	{
		x = -1;
		while (++x < (int)game->game_img->width)
		{
			if (y < (int)game->game_img->height / 2)
				mlx_put_pixel(game->game_img, x, y, map->c_int_color);
			else
				mlx_put_pixel(game->game_img, x, y, map->f_int_color);
		}
	}
}

/// @brief draws the map as in 3D
void	do_draw_game(t_cub *cub, t_game *game, t_map *map)
{
	int		ray_count;
	double	stripe_size;

	ray_count = (int)game->game_img->width / GAME_QUALITY;
	stripe_size = (double)game->game_img->width / (double)ray_count;
	do_draw_sky_and_floor(game, map);
	do_draw_map(cub, game, ray_count, stripe_size);
}
