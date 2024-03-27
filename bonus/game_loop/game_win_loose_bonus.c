/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_win_loose_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:45:36 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/27 22:49:30 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	loose(t_cub *cub)
{
	mlx_image_t	*img;
	int			x;
	int			y;

	x = cub->game->game_img->width / 2;
	y = cub->game->game_img->height / 2;
	x -= cub->game->loose_txt->width / 2;
	y -= cub->game->loose_txt->height / 2;
	img = mlx_texture_to_image(cub->game->mlx, cub->game->loose_txt);
	mlx_image_to_window(cub->game->mlx, img, x, y);
	ft_putstr_fd("GameOver\n", 1);
	cub->game->stop = 1;
}

void	win(t_cub *cub)
{
	mlx_image_t	*img;
	int			x;
	int			y;

	x = cub->game->game_img->width / 2;
	y = cub->game->game_img->height / 2;
	x -= cub->game->win_txt->width / 2;
	y -= cub->game->win_txt->height / 2;
	img = mlx_texture_to_image(cub->game->mlx, cub->game->win_txt);
	mlx_image_to_window(cub->game->mlx, img, x, y);
	ft_putstr_fd("You Win\n", 1);
	cub->game->stop = 1;
}
