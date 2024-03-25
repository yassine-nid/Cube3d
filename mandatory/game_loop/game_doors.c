/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:08:19 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/25 01:31:38 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/// @brief the actual function where door allocation happens
static void	do_allocate_door(t_cub *cub, t_game *game, int x, int y)
{
	int	index;

	y = -1;
	index = 0;
	while (++y < cub->map_data->map_size)
	{
		x = -1;
		while (++x < cub->map_data->longest_line)
		{
			if (cub->map_data->map[y][x] == DOOR)
			{
				game->doors[index] = malloc (sizeof * game->doors[index]);
				if (!game->doors[index])
					clean_exit(cub, NULL, errno);
				game->doors[index]->current_texture = 0;
				game->doors[index]->door_x = x;
				game->doors[index]->door_y = y;
				game->doors[index]->is_open = false;
				game->doors[index]->is_opening = false;
				game->doors[index]->door_update_time = 0;
				index++;
			}
		}
	}
}

/// @brief allocates doors using the map data
void	allocate_doors(t_cub *cub, t_game *game)
{
	int	x;
	int	y;
	int	door_count;
	int	index;

	door_count = 0;
	y = -1;
	while (++y < cub->map_data->map_size)
	{
		x = -1;
		while (++x < cub->map_data->longest_line)
		{
			if (cub->map_data->map[y][x] == DOOR)
				door_count++;
		}
	}
	game->doors = malloc (sizeof * game->doors * (door_count + 1));
	if (!game->doors)
		clean_exit(cub, NULL, errno);
	index = -1;
	while (++index <= door_count)
		game->doors[index] = NULL;
	do_allocate_door(cub, game, 0, 0);
}

/// @brief takes a rayHit and returns a door data
t_door	*get_door_data(t_cub *cub, t_rayhit hit)
{
	int		x;
	int		y;
	int		index;
	t_door	**doors;

	index = -1;
	x = ceil(hit.point.x);
	y = ceil(hit.point.y);
	doors = cub->game->doors;
	while (hit.target == DOOR && doors && doors[++index])
	{
		if (doors[index]->door_x != x)
			continue ;
		if (doors[index]->door_y != y)
			continue ;
		return (doors[index]);
	}
	return (NULL);
}

/// @brief updates all doors varriables
void	door_update(t_cub *cub, t_game *game)
{
	int		index;
	t_door	*door;

	(void)cub;
	index = -1;
	while (game->doors[++index])
	{
		door = game->doors[index];
		if (door->is_opening)
		{
			door->door_update_time += DOOR_ANIM_SPEED * game->frame_time;
			if (door->door_update_time >= 100)
			{
				door->door_update_time = 0;
				door->current_texture++;
				if (!game->door_texts[door->current_texture])
				{
					door->is_open = true;
					door->current_texture = 0;
					door->is_opening = false;
				}
			}
		}
	}
}

/// @brief this is called when the enteract button is clicked
void	on_interact_clicked(t_cub *cub)
{
	t_rayhit	hit;
	t_door		*door_data;

	hit = ray_cast(cub, cub->game->angle, DOOR);
	if (hit.did_hit_target && hit.hit_distance <= DOOR_INTERACT_DISTANCE)
	{
		door_data = get_door_data(cub, hit);
		if (!door_data || door_data->is_opening)
			return ;
		door_data->is_opening = true;
	}
}
