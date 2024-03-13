# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 08:51:59 by yzirri            #+#    #+#              #
#    Updated: 2024/03/13 20:18:22 by yzirri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
OBJ_DIR = objects
NAME = cub3D

SRC = bonus/main/main.c bonus/cleanup/clean_exits.c bonus/utils/str_utils.c \
	bonus/parser/parser.c bonus/get_next_line/get_next_line.c \
	bonus/get_next_line/get_next_line_utils.c bonus/parser/parser_varriables.c \
	bonus/parser/parser_map.c bonus/parser/parser_map_utils.c \
	bonus/parser/parser_utils.c bonus/utils/ft_split.c bonus/parser/parser_colors.c \
	bonus/utils/ft_atoi.c bonus/utils/str_utils2.c

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
DEPS = $(patsubst %.c, $(OBJ_DIR)/%.d, $(SRC))
HBLU = '\e[1;94m'
NC = '\e[0m'

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c bonus/includes/cub3d.h
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