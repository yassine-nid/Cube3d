/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:52:45 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/03/20 00:52:46 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

/// @brief convert player start position from array[y][x] into image pixel location
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

/// @brief creates mlx_ptr and the image to be used for drawing
static void	init_mlx(t_cub *cub, t_game *game)
{
	uint32_t	win_height;
	uint32_t	win_width;

	win_height = 1000;
	win_width = 1780;
	game->mlx = mlx_init(win_width, win_height, "cub3D", false);
	if (!game->mlx )
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	game->game_img = mlx_new_image(game->mlx, win_width, win_height);
	if (!game->game_img)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->game_img , 0, 0) < 0)
        clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	

	game->mimimap_texture = mlx_load_png("./minimap_background.png");
	if (!game->mimimap_texture)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	
	game->minimap_img = mlx_texture_to_image(game->mlx, game->mimimap_texture);
	if (!game->minimap_img)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	
	if (!mlx_resize_image(game->minimap_img, MMAP_WIDTH, MMAP_HEIGHT))
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);

	if (mlx_image_to_window(game->mlx, game->minimap_img , 10, 10) < 0)
        clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	

	mlx_set_cursor_mode(cub->game->mlx, MLX_MOUSE_DISABLED);
	// cub->txt1 = mlx_load_png("./wl.png");
	cub->game->n_txt = mlx_load_png(cub->map_data->tx_north);
	if (!cub->game->n_txt)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	cub->game->s_txt = mlx_load_png(cub->map_data->tx_south);
	if (!cub->game->s_txt)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	cub->game->e_txt = mlx_load_png(cub->map_data->tx_east);
	if (!cub->game->e_txt)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	cub->game->w_txt = mlx_load_png(cub->map_data->tx_west);
	if (!cub->game->w_txt)
		clean_exit(cub, (char *)mlx_strerror(mlx_errno), EXIT_FAILURE);
	

	// 5000 * 3000 > 5000 * 3000
}

void	do_init_game(t_cub *cub, t_game *game, t_map *map)
{
	init_mlx(cub, game);
	init_game_vars(map, game);
}