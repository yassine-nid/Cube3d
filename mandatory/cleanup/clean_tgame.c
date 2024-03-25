/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tgame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:57:03 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/25 01:58:58 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	clean_doors(t_game *game)
{
	int	index;

	index = -1;
	while (game->door_texts && game->door_texts[++index])
		mlx_delete_texture(game->door_texts[index]);
	free(game->door_texts);
	index = -1;
	while (game->doors && game->doors[++index])
		free(game->doors[index]);
	free(game->doors);
}

void	cleanup_game(t_game *game)
{
	clean_doors(game);
	if (game->n_txt)
		mlx_delete_texture(game->n_txt);
	if (game->w_txt)
		mlx_delete_texture(game->w_txt);
	if (game->e_txt)
		mlx_delete_texture(game->e_txt);
	if (game->s_txt)
		mlx_delete_texture(game->s_txt);
	if (game->minimap_img)
		mlx_delete_image(game->mlx, game->minimap_img);
	if (game->game_img)
		mlx_delete_image(game->mlx, game->game_img);
	if (game->mimimap_texture)
		mlx_delete_texture(game->mimimap_texture);
	mlx_terminate(game->mlx);
}
