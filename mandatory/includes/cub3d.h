/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:53:57 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/13 02:59:46 by yzirri           ###   ########.fr       */
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
# include "../../MLX42/MLX42.h"
# include <math.h>

# pragma region define varriables

# ifndef PI
#  define PI 3.1415926
# endif

# ifndef INVALID_MAP_CONTENT
#  define INVALID_MAP_CONTENT "Invalid map content"
# endif

# ifndef INVALID_MAP_CHECK
#  define INVALID_MAP_CHECK "Invalid map"
# endif

# ifndef INVALID_MAP_VARRIABLES
#  define INVALID_MAP_VARRIABLES "Invalid map varriables"
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

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

# ifndef MAX_FOV
#  define MAX_FOV 10
# endif

# ifndef ROTATE_SPEED
#  define ROTATE_SPEED 6
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 4
# endif

# pragma endregion

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_ve2;

typedef struct s_game
{
	t_ve2	*player_pos;
	double	angle;
}	t_game;


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

typedef struct s_cub
{
	t_map		*map_data;
	mlx_t		*mlx;
	mlx_image_t	*game_img;
	int			win_height;
	int			win_width;
	int			grid_x;
	int			grid_y;
	t_game		*game;
	int			fd;

	mlx_texture_t	*test_texture;
}	t_cub;

typedef struct	s_rayhit
{
	bool	hit_target;
	double	hit_distance;
	t_ve2	point;
	char	target;
	bool	is_vertical;
}	t_rayhit;


// #################### Cleanup #########################
void	clean_exit(t_cub *cub, char *error, int code);
void	cleanup(t_cub *cub);

// ################## Utils #############################
int		ft_putstr_fd(char *s, int fd);
bool	is_valid_extention(const char *src, const char *ne);
bool	ft_isspace(char c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
// Split
char	**ft_split(char const *s, char c);
// Atoi
int		ft_atoi(const char *str);

// ################## Parser ############################
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

// ################## Get next line ####################
char	*get_next_line(int fd);
char	*append(char *src, char *dst, int *new_l);
int		str_len(char *str1, char *str2);











double	ang_to_rad(double angle);
double	clamp_angle(double angle);
void	calc_direction(const t_ve2 *st_pos, t_ve2 *res, double dis, double angle);
// bool	limits_check(t_map *map, double g_x, double g_y);
t_rayhit	ray_cast(t_cub *cub, double angle, char target);

// debug
void	draw_line(t_ve2 start, double len, int color, int line_size, double angle, mlx_image_t *img);

void	start_game(t_cub *cub, t_map *map);
void	register_events(t_cub *cub);
void	draw_map(t_cub *cub, t_map *map);
void	draw_player(t_cub *cub, t_map *map);


#endif