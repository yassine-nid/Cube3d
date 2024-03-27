# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 08:51:59 by yzirri            #+#    #+#              #
#    Updated: 2024/03/27 03:54:13 by yzirri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# General Varriables
ANS_START = '\e[1;94m'
ANS_END = '\e[0m'
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast #-fsanitize=address

# MLX
NAME_LIBMLX = libmlx
LIBMLX := ./MLX42
LIBMLX_HEADER := -I ./include -I $(LIBMLX)/include
LIBMLX_LIBS := ./MLX42/build/libmlx42.a -L"/Users/$(USER)/.brew/Cellar/glfw/" -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework OpenGL -framework AppKit

NAME_BONUS = cub3D_bonus
OBJ_DIR_BONUS = objects_bonus

SRC_BONUS = bonus/main/main_bonus.c bonus/cleanup/clean_exits_bonus.c bonus/utils/str_utils_bonus.c \
	bonus/parser/parser_bonus.c bonus/get_next_line/get_next_line_bonus.c \
	bonus/get_next_line/get_next_line_utils_bonus.c bonus/parser/parser_varriables_bonus.c \
	bonus/parser/parser_map_bonus.c bonus/parser/parser_map_utils_bonus.c \
	bonus/parser/parser_utils_bonus.c bonus/utils/ft_split_bonus.c bonus/parser/parser_colors_bonus.c \
	bonus/utils/ft_atoi_bonus.c bonus/utils/str_utils2_bonus.c \
	bonus/game_loop/game_loop_bonus.c bonus/game_loop/game_init_bonus.c bonus/game_loop/game_hooks_bonus.c \
	bonus/game_loop/game_draw_bonus.c bonus/game_loop/game_utils_bonus.c \
	bonus/game_loop/game_handle_keys_bonus.c \
	bonus/game_loop/game_minimap_bonus.c \
	bonus/raycaster/raycaster_bonus.c \
	bonus/game_loop/game_draw_stripe_bonus.c \
	bonus/game_loop/game_draw_map_bonus.c \
	bonus/game_loop/game_doors_bonus.c \
	bonus/game_loop/game_draw_sprites_bonus.c \
	bonus/cleanup/clean_tgame_bonus.c \
	bonus/game_loop/game_draw_sprites_utils_bonus.c \
	bonus/game_loop/game_enemies_bonus.c

OBJ_BONUS = $(patsubst %.c, $(OBJ_DIR_BONUS)/%.o, $(SRC_BONUS))

NAME = cub3D
OBJ_DIR_MANDATORY = objects_mandatory
	
SRC_MANDATORY = mandatory/main/main.c mandatory/cleanup/clean_exits.c mandatory/utils/str_utils.c \
	mandatory/parser/parser.c mandatory/get_next_line/get_next_line.c \
	mandatory/get_next_line/get_next_line_utils.c mandatory/parser/parser_varriables.c \
	mandatory/parser/parser_map.c mandatory/parser/parser_map_utils.c \
	mandatory/parser/parser_utils.c mandatory/utils/ft_split.c mandatory/parser/parser_colors.c \
	mandatory/utils/ft_atoi.c mandatory/utils/str_utils2.c \
	mandatory/game_loop/game_loop.c mandatory/game_loop/game_init.c mandatory/game_loop/game_hooks.c \
	mandatory/game_loop/game_draw.c mandatory/game_loop/game_utils.c \
	mandatory/game_loop/game_handle_keys.c mandatory/raycaster/raycaster.c \
	mandatory/game_loop/game_draw_stripe.c mandatory/game_loop/game_draw_map.c \
	mandatory/cleanup/clean_tgame.c \

OBJ_MANDATORY = $(patsubst %.c, $(OBJ_DIR_MANDATORY)/%.o, $(SRC_MANDATORY))

all : $(NAME_LIBMLX) $(NAME)

$(NAME_LIBMLX) :
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME) : $(OBJ_MANDATORY)
	$(CC) $(CFLAGS) $(OBJ_MANDATORY) $(LIBMLX_LIBS) $(LIBMLX_HEADER) -o $(NAME)

$(NAME_BONUS) : $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBMLX_LIBS) $(LIBMLX_HEADER) -o $(NAME_BONUS)

$(OBJ_DIR_BONUS)/%.o : %.c bonus/includes/cub3d_bonus.h
	mkdir -p $(dir $@)
	printf $(ANS_START)"[%-37s] 🕝 \r"$(ANS_END) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBMLX_HEADER)

$(OBJ_DIR_MANDATORY)/%.o : %.c mandatory/includes/cub3d.h
	mkdir -p $(dir $@)
	printf $(ANS_START)"[%-37s] 🕝 \r"$(ANS_END) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBMLX_HEADER)

bonus : $(NAME_LIBMLX) $(NAME_BONUS)

clean :
	rm -rf $(OBJ_DIR_BONUS)
	rm -rf $(OBJ_DIR_MANDATORY)
	rm -rf $(LIBMLX)/build

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re : fclean all

.PHONY : clean fclean all

.SILENT : $(NAME) $(NAME_BONUS) clean fclean all ${OBJ_BONUS} ${OBJ_MANDATORY} lib bonus