/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:53:57 by yzirri            #+#    #+#             */
/*   Updated: 2024/03/01 18:38:19 by yzirri           ###   ########.fr       */
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

# pragma region define varriables

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

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1780
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1000
# endif

# pragma endregion

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
	t_map	*map_data;
	mlx_t	*mlx;
	mlx_image_t	*img;
	int		fd;
}	t_cub;

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













void	start_game(t_cub *cub, t_map *map);

#endif