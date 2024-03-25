/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:52:45 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/25 01:41:34 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
}

/// @brief creates mlx_ptr and the image to be used for drawing
static void	init_mlx(t_cub *cub, t_game *game)
{
	char	door_path[34];
	int		index;

	initial_mlx_load(cub, game);
	cub->game->n_txt = load_texture(cub, cub->map_data->tx_north);
	cub->game->s_txt = load_texture(cub, cub->map_data->tx_south);
	cub->game->e_txt = load_texture(cub, cub->map_data->tx_east);
	cub->game->w_txt = load_texture(cub, cub->map_data->tx_west);
	game->door_texts = malloc(sizeof * game->door_texts * (S_DOOR_COUNT + 1));
	if (!game->door_texts)
		clean_exit(cub, NULL, errno);
	index = -1;
	while (++index <= S_DOOR_COUNT)
		game->door_texts[index] = NULL;
	ft_strcpy(door_path, "./assets/doors/Door_Texture_A.png");
	index = -1;
	while (++index < S_DOOR_COUNT)
	{
		door_path[28] = 'A' + S_DOOR_COUNT - index - 1;
		game->door_texts[index] = load_texture(cub, door_path);
	}
	allocate_doors(cub, game);
}

void	do_init_game(t_cub *cub, t_game *game, t_map *map)
{
	init_mlx(cub, game);
	init_game_vars(map, game);
}
