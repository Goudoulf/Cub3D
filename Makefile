# **************************************************************************** #
#																			   #
#														  :::	   ::::::::    #
#	 Makefile											:+:		 :+:	:+:    #
#													  +:+ +:+		  +:+	   #
#	 By: cassie <marvin@42.fr>						+#+  +:+	   +#+		   #
#												  +#+#+#+#+#+	+#+			   #
#	 Created: 2023/12/12 12:53:45 by cassie			   #+#	  #+#			   #
#	 Updated: 2023/12/12 12:54:51 by cassie			  ###	########.fr		   #
#																			   #
# **************************************************************************** #

NAME = cub3D

SRCS_FILE = main.c init.c event.c ./parsing/init_parsing.c \
			./parsing/ft_read_file.c ./parsing/ft_init_final_map.c \
			./parsing/check_parsing.c ft_free.c ./parsing/convert_char_to_int.c \
			./render/raycasting.c ./render/render.c event_utils.c ./parsing/parsing_texture.c \
			./minimap/minimap.c movement_ennemy.c parsing/check_texture.c parsing/parse_statue.c \
			next_move_ennemy.c init_texture.c close_window.c ./render/tex_color.c \
			print_error.c ./minimap/init_text.c ./minimap/resize_image.c ./minimap/alpha_channel.c

INC = includes

FT_PRINTF_DIR = ./lib/ft_printf/
LIBFT_DIR = ./lib/libft/
MLX_DIR = ./mlx_linux

DIR_SRC := src/
DIR_OBJ := .object/

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS})
SRCS = $(addprefix ${DIR_SRC},${SRCS_FILE})

FT_PRINTF = ./lib/ft_printf/libftprintf.a
LIBFT = ./lib/libft/libft.a

CC = cc
MD := mkdir -p
CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -I${INC} -g -O3 -fsanitize=address
NFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

RM = rm -rf

all: libft ft_printf ${NAME}

${NAME}: ${OBJS} ${FT_PRINTF} ${LIBFT} ${MLX}
	${CC} ${OBJS} ${NFLAGS} ${FT_PRINTF} ${LIBFT} -o $(NAME) -fsanitize=address

mlx: ${MLX_DIR}
	${MAKE} -C ./mlx_linux

libft: ${LIBFT_DIR}
	${MAKE} -C ./lib/libft all

ft_printf: ${FT_PRINTF_DIR}
	${MAKE} -C ./lib/ft_printf all

${DIR_OBJ}%.o: %.c ${INC}/cub3D.h Makefile
	mkdir -p $(shell dirname $@)
	$(CC) ${CFLAGS} -c $< -o $@

clean:
	${MAKE} -C ./lib/ft_printf clean
	${MAKE} -C ./lib/libft clean
	${RM} ${DIR_OBJ}

fclean: clean
	${MAKE} -C ./lib/ft_printf fclean
	${MAKE} -C ./lib/libft fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
