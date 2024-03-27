/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 00:47:10 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 01:40:43 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief updates all enemies varriables
void	update_enemies(t_cub *cub, t_game *game)
{
	int		index;
	t_enemy	*enemy;
	double	delta_time;

	(void)cub;
	index = -1;
	while (game->enemies[++index])
	{
		enemy = game->enemies[index];
		delta_time = ((float)rand() / RAND_MAX) * 20;
		delta_time += ENEMY_ANIM_SPEED;
		enemy->sprite_index_time += delta_time * game->frame_time;
		if (enemy->sprite_index_time >= 100)
		{
			enemy->sprite_index_time = 0;
			enemy->sprite_index++;
			if (!game->enemy_sprites[enemy->sprite_index])
				enemy->sprite_index = 0;
		}
	}
}

/// @brief allocate all enemies sprites
static void	allocate_enemy_sprites(t_cub *cub, t_game *game)
{
	char	path[37];
	int		index;
	size_t	alloc_size;

	alloc_size = sizeof * game->enemy_sprites * (S_ENEMY_COUNT + 1);
	game->enemy_sprites = malloc(alloc_size);
	if (!game->enemy_sprites)
		clean_exit(cub, NULL, errno);
	index = -1;
	while (++index <= S_ENEMY_COUNT)
		game->enemy_sprites[index] = NULL;
	ft_strcpy(path, "./assets/sprites/enemy_texture_A.png");
	index = -1;
	while (++index < S_ENEMY_COUNT)
	{
		path[31] = 'A' + S_ENEMY_COUNT - index - 1;
		game->enemy_sprites[index] = load_texture(cub, path);
	}
}

/// @brief initializes a single enemy's varriables
static void	init_new_enemy(t_enemy *enemy, int x, int y)
{
	enemy->sprite_index = 0;
	enemy->sprite_data.txt = NULL;
	enemy->sprite_index_time = 0;
	enemy->position.x = x;
	enemy->position.y = y;
	if (enemy->position.x > 0)
		enemy->position.x -= 0.5;
	if (enemy->position.x > 0)
		enemy->position.y -= 0.5;
}

/// @brief aallocates all enemies in the map
static void	allocate_enemy_structs(t_cub *cub, t_map *map, t_game *game)
{
	int	index;
	int	x;
	int	y;

	index = 0;
	y = -1;
	while (++y < map->map_size)
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (map->map[y][x] == ENEMY)
			{
				game->enemies[index] = malloc (sizeof * game->enemies[index]);
				if (!game->enemies[index])
					clean_exit(cub, NULL, errno);
				init_new_enemy(game->enemies[index], x, y);
				index++;
			}
		}
	}
}

/// @brief takes enemies from map to struct in the game*
void	allocate_enemies(t_cub *cub, t_game *game, t_map *map)
{
	int	index;
	int	enemies_count;
	int	y;
	int	x;

	allocate_enemy_sprites(cub, game);
	enemies_count = 0;
	y = -1;
	while (++y < map->map_size)
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (map->map[y][x] == ENEMY)
				enemies_count++;
		}
	}
	game->enemies = malloc(sizeof * game->enemies * (enemies_count + 1));
	if (!game->enemies)
		clean_exit(cub, NULL, errno);
	index = -1;
	while (++index <= enemies_count)
		game->enemies[index] = NULL;
	allocate_enemy_structs(cub, map, game);
}
