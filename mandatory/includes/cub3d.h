/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:53:57 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/15 21:35:26 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/MLX42.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef PI
#  define PI 3.14159
# endif

/// @brief a simple vector 2 of 2 doubles
typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

/// @brief holds the result of a raycast
typedef struct s_rayhit
{
	bool		did_hit_target;
	double		hit_distance;
	t_vector2	point;
	char		target;
	bool		is_vertical;
}	t_rayhit;

/// @brief Holds all inputs used during the game
typedef struct s_inputs
{
	bool	key_forward;
	bool	key_backward;
	bool	key_right;
	bool	key_left;
	bool	key_turn_left;
	bool	key_turn_right;
	bool	key_close_game;
	double	old_x;
	double	change_x;
}	t_inputs;


/// @brief holds game data
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*game_img;
	mlx_image_t		*minimap_img;
	mlx_texture_t	*mimimap_texture;
	double			angle;
	t_vector2		player_position;
	t_inputs		m_inputs;
}	t_game;

/// @brief data required to draw a stripe
typedef struct s_stripe_data
{
	uint32_t	height;
	uint32_t	start_x_pos;
	uint32_t	end_x_pos;
	int			color;
	mlx_image_t	*img;
}	t_stripe_data;

/// @brief parsed data you get from reading the file provided
typedef struct s_map
{
	char			**map;
	char			*tx_north;
	char			*tx_south;
	char			*tx_west;
	char			*tx_east;
	char			*flor_color;
	unsigned int	f_int_color;
	char			*ceiling_color;
	unsigned int	c_int_color;
	int				map_start_index;
	int				longest_line;
	int				map_size;
	char			start_location_type;
}	t_map;

/// @brief holds refrences to pretty much everything
typedef struct s_cub
{
	t_map		*map_data;
	t_game		*game;
	int			fd;
}	t_cub;

#pragma region Mini map varriables

# ifndef MMAP_HEIGHT
# 	define MMAP_HEIGHT 230
# endif

# ifndef MMAP_WIDTH
# 	define MMAP_WIDTH 230
# endif

# ifndef MMAP_GRID
# 	define MMAP_GRID 30
# endif

# ifndef MMAP_EDGE
# 	define MMAP_EDGE 10
# endif

# ifndef MMAP_PLAYER_SIZE
# 	define MMAP_PLAYER_SIZE 4.5
# endif

# ifndef MMAP_PLAYER_COLOR
# 	define MMAP_PLAYER_COLOR 0x2c4c9cFF
# endif

# ifndef MMAP_BACKGROUND_COLOR
# 	define MMAP_BACKGROUND_COLOR 0xd5dbebFF
# endif

# ifndef MMAP_WALL_COLOR
# 	define MMAP_WALL_COLOR 0xabb7d7FF
# endif

# ifndef MMAP_SPAWN_POINT_COLOR
# 	define MMAP_SPAWN_POINT_COLOR 0xccffe2FF
# endif

# ifndef MMAP_DOOR_COLOR
# 	define MMAP_DOOR_COLOR 0x69696aFF
# endif

#pragma endregion

# pragma region error messages

# ifndef INVALID_MAP_CONTENT
#  define INVALID_MAP_CONTENT "Invalid map content"
# endif

# ifndef INVALID_MAP_CHECK
#  define INVALID_MAP_CHECK "Invalid map"
# endif

# ifndef INVALID_MAP_VARRIABLES
#  define INVALID_MAP_VARRIABLES "Invalid map varriables"
# endif

# pragma endregion

# pragma region parsing varriables

# ifndef WALL
#  define WALL '1'
# endif

# ifndef EMPTY
#  define EMPTY '0'
# endif

# ifndef NORTH
#  define NORTH 'N'
# endif

# ifndef SOUTH
#  define SOUTH 'S'
# endif

# ifndef WEST
#  define WEST 'W'
# endif

# ifndef EAST
#  define EAST 'E'
# endif

# ifndef DOOR
#  define DOOR 'D'
# endif

# pragma endregion

#pragma region Cleanup

void	clean_exit(t_cub *cub, char *error, int code);
void	cleanup(t_cub *cub);

#pragma endregion

#pragma region Utils

int		ft_putstr_fd(char *s, int fd);
bool	is_valid_extention(const char *src, const char *ne);
bool	ft_isspace(char c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);

#pragma endregion

#pragma region Parser

void	do_parse(t_cub *cub, int argc, char *argv[]);
void	varriables_parse(t_cub *cub, t_map *map, char *line, char *argv[]);
void	map_parse(t_cub *cub, t_map *map, char *argv[]);
void	open_map_file(t_cub *cub, char *argv[]);
void	close_map_file(t_cub *cub);
int		str_len_no_endspace(char *line);
void	remove_new_line(char *line);
void	save_line(t_cub *cub, t_map *map, char **line, int map_index);
void	read_x_lines(int fd, int count);
void	alloc_init_map(t_cub *cub, t_map *map);

bool	check_x(char **map, int len, int x, int y);
bool	check_y(char **map, int len, int x, int y);
bool	check_angles(t_map *map, int x, int y);

void	colors_parse(t_cub *cub, t_map *map);

#pragma endregion

#pragma region Get_next_line

char	*get_next_line(int fd);
char	*append(char *src, char *dst, int *new_l);
int		str_len(char *str1, char *str2);

#pragma endregion

#pragma region game_loop

void	do_game(t_cub *cub);
void	do_init_game(t_cub *cub, t_game *game, t_map *map);
void	register_events(t_cub *cub);
void	do_draw_game(t_cub *cub, t_game *game, t_map *map);
void	do_handle_keys(t_cub *cub, t_game *game, t_map *map);

double	clamp_angle(double angle);
t_vector2	calc_direction(t_vector2 start_position, double dis, double angle);
double	ang_to_rad(double angle);
void	draw_stripe(t_stripe_data *data);

void	do_draw_mini_map(t_cub *cub, t_game *game, t_map *map);

#pragma endregion

#pragma region raycaster

t_rayhit	ray_cast(t_cub *cub, double angle, char target);

#pragma endregion

#endif