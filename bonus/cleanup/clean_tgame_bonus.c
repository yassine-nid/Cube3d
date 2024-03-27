/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tgame_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:57:03 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 23:05:33 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	clean_doors(t_game *game)
{
	int	index;

	index = -1;
	if (game->door_text)
		mlx_delete_texture(game->door_text);
	index = -1;
	while (game->doors && game->doors[++index])
		free(game->doors[index]);
	free(game->doors);
}

static void	clear_enemies(t_game *game)
{
	int	index;

	index = -1;
	while (game->enemies && game->enemies[++index])
		free(game->enemies[index]);
	free(game->enemies);
	index = -1;
	while (game->enemy_sprites && game->enemy_sprites[++index])
		mlx_delete_texture(game->enemy_sprites[index]);
	free(game->enemy_sprites);
}

void	cleanup_game(t_game *game)
{
	clean_doors(game);
	clear_enemies(game);
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
	if (game->win_txt)
		mlx_delete_texture(game->win_txt);
	if (game->loose_txt)
		mlx_delete_texture(game->loose_txt);
	if (game->trophy_sprite.txt)
		mlx_delete_texture(game->trophy_sprite.txt);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
