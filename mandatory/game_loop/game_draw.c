/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:52:26 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/27 02:53:27 by yzirri           ###   ########.fr       */
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

/// @brief initialize all sprites
static void	init_sprites(t_cub *cub, t_enemy **enemies, t_game *game)
{
	int			index;
	t_enemy		*enemy;

	index = -1;
	while (enemies && enemies[++index])
	{
		enemy = enemies[index];
		enemy->sprite_data.position = enemy->position;
		enemy->sprite_data.txt = cub->game->enemy_sprites[enemy->sprite_index];
		sprite_init(cub, &enemy->sprite_data);
	}
	if (game->trophy_sprite.txt)
		sprite_init(cub, &game->trophy_sprite);
}

static void	sort_enemies(t_enemy **enemies)
{
	int			index;
	t_sprite	*current_sprite;
	t_sprite	*next_sprite;
	t_enemy		*tmp_enemy;

	index = -1;
	while (enemies && enemies[++index])
	{
		if (enemies[index + 1] == NULL)
			break ;
		current_sprite = &enemies[index]->sprite_data;
		next_sprite = &enemies[index + 1]->sprite_data;
		if (current_sprite->distance < next_sprite->distance)
		{
			tmp_enemy = enemies[index];
			enemies[index] = enemies[index + 1];
			enemies[index + 1] = tmp_enemy;
			index = -1;
		}
	}
}

static void	draw_sprites(t_cub *cub, t_enemy **enemies, t_sprite *throphy)
{
	int			index;
	bool		done;
	t_sprite	*sprite ;

	done = false;
	index = -1;
	while (enemies && enemies[++index])
	{
		sprite = &enemies[index]->sprite_data;
		if (throphy->txt && !done && throphy->distance >= sprite->distance)
		{
			draw_sprite(cub, throphy);
			done = true;
		}
		draw_sprite(cub, sprite);
	}
	if (throphy->txt && !done)
		draw_sprite(cub, throphy);
}

/// @brief draws the map as in 3D
void	do_draw_game(t_cub *cub, t_game *game, t_map *map)
{
	int		ray_count;
	double	stripe_size;

	update_enemies(cub, game);
	init_sprites(cub, game->enemies, game);
	sort_enemies(game->enemies);
	ray_count = (int)game->game_img->width / GAME_QUALITY;
	stripe_size = (double)game->game_img->width / (double)ray_count;
	do_draw_sky_and_floor(game, map);
	do_draw_map(cub, game, ray_count, stripe_size);
	draw_sprites(cub, game->enemies, &game->trophy_sprite);
}
