/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:18:22 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/13 03:40:58 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
static void	do_draw_player(t_cub *cub, t_map *map, t_game *game)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;

	y = -(PLAYER_SIZE / 2) - 1;
	while (++y < (PLAYER_SIZE / 2))
	{
		x = -(PLAYER_SIZE / 2) - 1;
		while (++x < (PLAYER_SIZE / 2))
		{
			draw_x = game->player_pos->x + x;
			draw_y = game->player_pos->y + y;
			mlx_put_pixel(cub->img, draw_x, draw_y, map->c_int_color);
		}
	}
}


static void	draw_sky_and_floor(t_cub *cub, t_map *map)
{
	// sky
	for (int y = 0; y < WIN_HEIGHT / 2; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			mlx_put_pixel(cub->img, x, y, map->c_int_color);
	
	// floor
	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			mlx_put_pixel(cub->img, x, y, map->f_int_color);
}


void	draw_player(t_cub *cub, t_map *map)
{
	draw_sky_and_floor(cub, map);
	
	if (0)
		do_draw_player(cub, map, cub->game);

	

	double angle = cub->game->angle;
	int pixel_per_ray = WIN_WIDTH / 60;

	angle -= 30;
	angle = clamp_angle(angle);
	int x_tss = 0;

	for (int i = 0; i < 60; i++)
	{
		// do a single ray
		t_rayhit hit = ray_cast(cub, angle, WALL);


		
		double wall_height = floor((WIN_HEIGHT / 2) / hit.hit_distance);
		printf("Wall height %f\n", wall_height);
		int from = (WIN_HEIGHT / 2) - wall_height;
		int to = (WIN_HEIGHT / 2) + wall_height;

		if (from <= 0)
			from = 0;
		if (to <= 0)
			to = 0;
		for (int y = from; y < to; y++)
		{
			for (int x = 0; x < pixel_per_ray; x++)
			{
				if (hit.hit_target)
					mlx_put_pixel(cub->img, x + x_tss, y, 0x1C80F2);
				else
					mlx_put_pixel(cub->img, x + x_tss, y, 0xFFFFFF);
			}
		}
		x_tss += pixel_per_ray;
		
		
		// increase angle
		angle++;
		angle = clamp_angle(angle);
	}
	
}
*/

void	draw_stripe(uint32_t len, uint32_t start_pos, uint32_t end_pos, int color, mlx_image_t *img)
{
	if (start_pos < 0 || end_pos < 0)
	{
		printf("outside range 1\n");
		return ;
	}
	if (len > (img->height / 2))
	{
		printf("outside range 2\n");
		return ;
	}
	if (start_pos > img->width || end_pos > img->width)
	{
		if (start_pos > img->width )
			return ;
		end_pos = start_pos;
	}
	while (start_pos <= end_pos)
	{
		for (uint32_t y = (img->height / 2) - len; y < ((img->height / 2) + len); y++)
		{
			mlx_put_pixel(img, start_pos, y, color);
		}
		start_pos++;
	}
}

unsigned int	test_combine_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return ((int)r << 24 | (int)g << 16 |  (int)b << 8 | (int)255);
}

void	draw_player(t_cub *cub, t_map *map)
{
	(void)map;


	// if (1)
	// {
	// 	// void *pix = cub->test_texture->pixels;
	// 			void *pix = cub->test_texture->pixels;
	// 	for (uint32_t y = 0; y < cub->test_texture->height; y++)
	// 	{
	// 		for (uint32_t x = 0; x < cub->test_texture->width; x++)
	// 		{
				
	// 			mlx_put_pixel(cub->game_img, x, y, *((int *)pix));
	// 			pix += 4;
	// 		}
	// 	}
	// 	// clean_exit(cub, NULL, errno);
	// 	return ;
	// }
	
	if (1)
	{
		for (uint32_t y = 0; y < cub->game_img->height; y++)
			for (uint32_t x = 0; x < cub->game_img->width; x++)
				mlx_put_pixel(cub->game_img, x, y, 0xF50505);
			
		double angle = cub->game->angle;
		int	ray_count = (int)cub->game_img->width;
		
		angle += 30;
		angle = clamp_angle(angle);
		uint32_t len = 100;
		double stripe_size = cub->game_img->width / ray_count;
		int color = 0;
		
		// draw strips
		for (int i = 0; i <= ray_count; i++)
		{
			t_rayhit hit = ray_cast(cub, angle, WALL);
			
			double rrrrang = clamp_angle(angle - cub->game->angle);
			hit.hit_distance = hit.hit_distance * cos(ang_to_rad(rrrrang));

			
			if (hit.hit_target == true)
			{
				color = 0xFFFFFF;
				if (!hit.is_vertical)
					color = 0xFFFFD0;
				if (hit.hit_distance > 0)
				{
					len /= (hit.hit_distance * 0.03);
					len = (64 * 320) / hit.hit_distance;
					if (len >= cub->game_img->height / 2)
						len = cub->game_img->height / 2;
					if (len < 0)
						len = 0;
				}
			}
			else
			{
				color = 0;
				len = 0;
			}
			int	stripe_start_pos = i * stripe_size;
			
			draw_stripe(len, stripe_start_pos, stripe_start_pos + stripe_size, color, cub->game_img);
			angle -= ((double)60 / (double)ray_count);
			angle = clamp_angle(angle);
		}
		
		
		return ;
	}


	
	if (1)
	{
		for (uint32_t y = 0; y < cub->game_img->height; y++)
		{
			for (uint32_t x = 0; x < cub->game_img->width; x++)
			{
				int	player_size = 10;
				
				int color = 0xFFFFFF;
				if (map->map[y / cub->grid_y][x / cub->grid_x] == '1')
					color = 0x1C80F2;
				if (y >= cub->game->player_pos->y - player_size
				&& y <= cub->game->player_pos->y + player_size
				&& x >= cub->game->player_pos->x - player_size
				&& x <= cub->game->player_pos->x + player_size)
					color = 0xF50505;
				mlx_put_pixel(cub->game_img, x, y, color);
			}
		}

		double angle = cub->game->angle;
		angle -= 30;
		angle = clamp_angle(angle);
		int ray_count = (int)cub->game_img->width;

		for (int i = 0; i < ray_count; i++)
		{
			t_rayhit hit = ray_cast(cub, angle, WALL);
			draw_line(*cub->game->player_pos, hit.hit_distance, 0xF50505, 8, angle, cub->game_img);
			angle += ((double)60 / (double)ray_count);
			angle = clamp_angle(angle);
		}
		
		return ;
	}
	
	for (uint32_t y = 0; y < cub->game_img->height; y++)
		for (uint32_t x = 0; x < cub->game_img->width; x++)
			mlx_put_pixel(cub->game_img, x, y, 0xF50505);
	

	double angle = cub->game->angle;
	
	angle -= 30;
	angle = clamp_angle(angle);

	int pixel_per_width = cub->win_width / 60;

	int current_x = 0;
	for (int i = 0; i < 60; i++)
	{
		// do a single ray
		t_rayhit hit = ray_cast(cub, angle, WALL);

		//draw_line(*cub->game->player_pos, hit.hit_distance, 0xF50505, 8, angle, cub->game_img);
		
		double wall_height = floor((cub->win_height / 2) / hit.hit_distance);
		int from = (cub->win_height / 2) - wall_height;
		int to = (cub->win_height / 2) + wall_height;

		if (from <= 0)
			from = 0;
		if (to <= 0)
			to = 0;
		for (int y = from; y < to; y++)
		{
			for (int x = 0; x < pixel_per_width; x++)
			{
				if (hit.hit_target)
					mlx_put_pixel(cub->game_img, current_x + current_x, y, 0x1C80F2);
				else
					mlx_put_pixel(cub->game_img, current_x + current_x, y, 0xFFFFFF);
				
			}
			// mlx_put_pixel(cub->game_img, 5, y, 0xFFFFFF);
		}
		current_x += pixel_per_width;
		
		
		// increase angle
		angle++;
		angle = clamp_angle(angle);
	}
	
}
