/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:52:45 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/27 22:44:07 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/// @brief convert player start position from array[y][x] into image pixel loca
static t_vector2	load_player_start_position(t_map *map)
{
	t_vector2	result;
	int			x;
	int			y;

	y = -1;
	while (++y < map->map_size)
	{
		x = -1;
		while (++x < map->longest_line)
		{
			if (map->map[y][x] == map->start_location_type)
			{
				result.x = x;
				result.y = y;
				if (result.x > 0)
					result.x -= 0.5;
				if (result.x > 0)
					result.y -= 0.5;
				break ;
			}
		}
	}
	return (result);
}

/// @brief setup and initialize game variables
static void	init_game_vars(t_map *map, t_game *game)
{
	game->player_position = load_player_start_position(map);
	game->angle = 90;
	if (map->start_location_type == EAST)
		game->angle = 0;
	if (map->start_location_type == SOUTH)
		game->angle = 270;
	if (map->start_location_type == WEST)
		game->angle = 180;
}

/// @brief load MLX and essential images
static void	initial_mlx_load(t_cub *cub, t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, GAME_NAME, false);
	if (!game->mlx)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	game->game_img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->game_img)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->game_img, 0, 0) < 0)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	game->mimimap_texture = load_texture(cub, MMAP_PATH);
	game->minimap_img = texture_to_image(cub, game->mimimap_texture);
	if (!mlx_resize_image(game->minimap_img, MMAP_WIDTH, MMAP_HEIGHT))
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->minimap_img, 10, 10) < 0)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	mlx_set_cursor_mode(cub->game->mlx, MLX_MOUSE_DISABLED);
	cub->game->loose_txt = load_texture(cub, LOOSE_TXT);
	cub->game->win_txt = load_texture(cub, WIN_TXT);
}

/// @brief creates mlx_ptr and the image to be used for drawing
static void	init_mlx(t_cub *cub, t_game *game, int x, int y)
{
	initial_mlx_load(cub, game);
	cub->game->n_txt = load_texture(cub, cub->map_data->tx_north);
	cub->game->s_txt = load_texture(cub, cub->map_data->tx_south);
	cub->game->e_txt = load_texture(cub, cub->map_data->tx_east);
	cub->game->w_txt = load_texture(cub, cub->map_data->tx_west);
	game->door_text = load_texture(cub, DOOR_PATH);
	game->trophy_sprite.txt = load_texture(cub, TROPHY_PATH);
	allocate_doors(cub, game);
	allocate_enemies(cub, game, cub->map_data);
	while (++y < cub->map_data->map_size)
	{
		x = -1;
		while (cub->map_data->map[y][++x])
		{
			if (cub->map_data->map[y][x] == TROPHY)
			{
				game->trophy_sprite.position.x = x;
				game->trophy_sprite.position.y = y;
				if (game->trophy_sprite.position.x > 0)
					game->trophy_sprite.position.x -= 0.5;
				if (game->trophy_sprite.position.x > 0)
					game->trophy_sprite.position.y -= 0.5;
			}
		}
	}
}

void	do_init_game(t_cub *cub, t_game *game, t_map *map)
{
	init_mlx(cub, game, 0, -1);
	init_game_vars(map, game);
}
