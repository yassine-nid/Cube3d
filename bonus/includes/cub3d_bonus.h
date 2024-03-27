/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:53:57 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/27 03:54:29 by yzirri           ###   ########.fr       */
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
# include <sys/time.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# pragma region General varriables

# define WIN_HEIGHT 1000.0
# define WIN_WIDTH 1780.0
# define GAME_QUALITY 2
# define GAME_NAME "cub3D_bonus"
# define PI 3.14159

/// @brief a simple vector 2 of 2 doubles
typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

/// @brief line drawing data
typedef struct s_line_data
{
	int	p0_x;
	int	p0_y;
	int	p1_x;
	int	p1_y;
	int	diffrence_x;
	int	diffrence_y;
	int	direction_x;
	int	direction_y;
	int	err;
	int	temp_err;
}	t_line_data;

# pragma endregion

# pragma region Movement varriables

# define MOVE_SPEED 2
# define ROTATE_SPEED 45
# define MOUSE_ROTATE_SPEED 2.5

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

# pragma endregion

# pragma region t_rayhit

/// @brief holds the result of a raycast
typedef struct s_rayhit
{
	bool		did_hit_target;
	double		hit_distance;
	t_vector2	point;
	char		target;
	bool		is_vertical;
}	t_rayhit;

# pragma endregion

# pragma region t_game

// Enemy Sprites Count
# define DOOR_PATH "./assets/doors/Door_Texture_A.png"
# define TROPHY_PATH "./assets/sprites/trophy_texture_A.png"
# define S_ENEMY_COUNT 4
# define ENEMY_COLLISION_DISTANCE 0.1
# define THROPHY_COLLISION_DIST 0.1
# define ENEMY_ANIM_SPEED 500
# define DOOR_INTERACT_DISTANCE 2
# define DOOR_ANIM_SPEED 1200

typedef struct s_door
{
	int			door_x;
	int			door_y;
	bool		is_open;
}	t_door;

typedef struct s_sprite
{
	mlx_texture_t	*txt;
	t_vector2		position;
	uint32_t		height;
	uint32_t		width;
	int				start_x;
	int				start_y;
	double			distance;
	double			angle;
}				t_sprite;

typedef struct s_enemy
{
	t_vector2	position;
	int			sprite_index;
	t_sprite	sprite_data;
	double		sprite_index_time;
}	t_enemy;

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
	mlx_texture_t	*n_txt;
	mlx_texture_t	*w_txt;
	mlx_texture_t	*e_txt;
	mlx_texture_t	*s_txt;
	t_door			**doors;
	mlx_texture_t	*door_text;
	long long		current_time;
	long long		preveus_time;
	double			frame_time;
	double			frame_rate;
	t_enemy			**enemies;
	mlx_texture_t	**enemy_sprites;
	t_sprite		trophy_sprite;
}	t_game;

# pragma endregion

# pragma region Stripe Data

/// @brief data required to draw a stripe
typedef struct s_stripe_data
{
	uint32_t	height;
	uint32_t	height_y;
	uint32_t	start_x_pos;
	uint32_t	end_x_pos;
	char		direction;
	mlx_image_t	*img;
	t_rayhit	*hit;
}	t_stripe_data;

# pragma endregion

# pragma region t_map

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

# pragma endregion

# pragma region t_cub

/// @brief holds refrences to pretty much everything
typedef struct s_cub
{
	t_map			*map_data;
	t_game			*game;
	int				fd;
}	t_cub;

# pragma endregion

# pragma region Mini map varriables

# define MMAP_DIRECTION_LENGTH 15
# define MMAP_HEIGHT 230
# define MMAP_WIDTH 230
# define MMAP_GRID 30
# define MMAP_EDGE 10
# define MMAP_PLAYER_SIZE 4.5
# define MMAP_PLAYER_COLOR 0x2c4c9cFF
# define MMAP_BACKGROUND_COLOR 0xd5dbebFF
# define MMAP_WALL_COLOR 0xabb7d7FF
# define MMAP_SPAWN_POINT_COLOR 0xccffe2FF
# define MMAP_DOOR_COLOR 0x69696aFF
# define MMAP_PATH "./assets/minimap/minimap_background.png"

# pragma endregion

# pragma region error messages

# define INVALID_MAP_CONTENT "Invalid map content"
# define INVALID_MAP_CHECK "Invalid map"
# define INVALID_MAP_VARRIABLES "Invalid map varriables"

# pragma endregion

# pragma region parsing varriables

# define WALL '1'
# define EMPTY '0'
# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'
# define DOOR 'D'
# define ENEMY 'M'
# define TROPHY 'T'

# pragma endregion

# pragma region Cleanup

void			clean_exit(t_cub *cub, char *error, int code);
void			cleanup(t_cub *cub);
void			cleanup_game(t_game *game);
void			cleanup_exit(t_cub *cub, char *msg);

# pragma endregion

# pragma region Utils

int				ft_putstr_fd(char *s, int fd);
bool			is_valid_extention(const char *src, const char *ne);
bool			ft_isspace(char c);
int				ft_strlen(const char *str);
char			*ft_strdup(const char *s1);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
void			ft_strcpy(char *dst, const char *src);
char			*ft_itoa(int n);

# pragma endregion

# pragma region Parser

void			do_parse(t_cub *cub, int argc, char *argv[]);
void			varriables_parse(t_cub *cub, t_map *map,
					char *line, char *argv[]);
void			map_parse(t_cub *cub, t_map *map, char *argv[]);
void			open_map_file(t_cub *cub, char *argv[]);
void			close_map_file(t_cub *cub);
int				str_len_no_endspace(char *line);
void			remove_new_line(char *line);
void			save_line(t_cub *cub, t_map *map, char **line, int map_index);
void			read_x_lines(int fd, int count);
void			alloc_init_map(t_cub *cub, t_map *map);

bool			check_x(char **map, int len, int x, int y);
bool			check_y(char **map, int len, int x, int y);

void			colors_parse(t_cub *cub, t_map *map);

# pragma endregion

# pragma region Get_next_line

char			*get_next_line(int fd);
char			*append(char *src, char *dst, int *new_l);
int				str_len(char *str1, char *str2);

# pragma endregion

# pragma region game_loop

void			do_draw_map(t_cub *cub, t_game *game, int ray_nt, double str);
t_rayhit		get_valid_hit(t_cub *cub, double angle);

void			do_game(t_cub *cub);
void			do_init_game(t_cub *cub, t_game *game, t_map *map);
void			register_events(t_cub *cub);
void			do_draw_game(t_cub *cub, t_game *game, t_map *map);
void			do_handle_keys(t_cub *cub, t_game *game);
void			draw_stripe(t_stripe_data data, t_cub *cub);
void			do_draw_mini_map(t_cub *cub, t_game *game, t_map *map);
double			clamp_angle(double angle);
double			ang_to_rad(double angle);

t_vector2		calc_direction(t_vector2 start_pos, double dis, double angle);

mlx_texture_t	*load_texture(t_cub *cub, char *path);
mlx_image_t		*texture_to_image(t_cub *cub, mlx_texture_t *texture);

void			allocate_doors(t_cub *cub, t_game *game);
t_door			*get_door_data(t_cub *cub, t_rayhit hit);

void			on_interact_clicked(t_cub *cub);

void			draw_sprite(t_cub *cub, t_sprite *sprite);
void			sprite_init(t_cub *cub, t_sprite *sprite);
double			angle_diff(double ang1, double ang2);

void			update_enemies(t_cub *cub, t_game *game);
void			allocate_enemies(t_cub *cub, t_game *game, t_map *map);
# pragma endregion

# pragma region raycaster

t_rayhit		ray_cast(t_cub *cub, double angle, char target);

# pragma endregion

#endif