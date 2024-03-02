# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 08:51:59 by yzirri            #+#    #+#              #
#    Updated: 2024/03/01 18:35:35 by yzirri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
OBJ_DIR = objects
LIBMLX	:= ./MLX42
LIBS = ./MLX42/libmlx42.a -L"/Users/$(USER)/.brew/Cellar/glfw/" -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework OpenGL -framework AppKit

NAME = cub3D

SRC = mandatory/main/main.c mandatory/cleanup/clean_exits.c mandatory/utils/str_utils.c \
	mandatory/parser/parser.c mandatory/get_next_line/get_next_line.c \
	mandatory/get_next_line/get_next_line_utils.c mandatory/parser/parser_varriables.c \
	mandatory/parser/parser_map.c mandatory/parser/parser_map_utils.c \
	mandatory/parser/parser_utils.c mandatory/utils/ft_split.c mandatory/parser/parser_colors.c \
	mandatory/utils/ft_atoi.c mandatory/game_loop/game_loop.c

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
DEPS = $(patsubst %.c, $(OBJ_DIR)/%.d, $(SRC))
HBLU = '\e[1;94m'
NC = '\e[0m'

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o : %.c mandatory/includes/cub3d.h MLX42/MLX42.h
	mkdir -p $(dir $@)
	printf $(HBLU)"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) -o $@ -c $<

lib:

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean all

.SILENT : $(NAME) clean fclean all ${OBJ} lib bonus