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
NAME_BONUS = cub3D_bonus

SRCS_FILE = main.c init.c event.c ./parsing/init_parsing.c \
			./parsing/ft_read_file.c \
			./parsing/check_parsing.c ft_free.c ./parsing/convert_char_to_int.c \
			./render/raycasting.c ./render/render.c event_utils.c ./parsing/parsing_texture.c \
			parsing/check_texture.c \
			init_texture.c init_texture_utils.c close_window.c ./render/tex_color.c \
			print_error.c

SRCS_FILE_BONUS = main_bonus.c init_bonus.c event_bonus.c ./parsing_bonus/init_parsing_bonus.c \
			./parsing_bonus/ft_read_file_bonus.c \
			./parsing_bonus/check_parsing_bonus.c ft_free_bonus.c ./parsing_bonus/convert_char_to_int_bonus.c \
			./render_bonus/raycasting_bonus.c ./render_bonus/render_bonus.c event_utils_bonus.c \
			./parsing_bonus/parsing_texture_bonus.c \
			./minimap_bonus/minimap_bonus.c parsing_bonus/check_texture_bonus.c \
			init_texture_bonus.c init_texture_utils_bonus.c close_window_bonus.c ./render_bonus/tex_color_bonus.c \
			print_error_bonus.c ./minimap_bonus/init_text_bonus.c ./minimap_bonus/resize_image_bonus.c \
			list_free_bonus.c

INC = includes
INC_BONUS = includes_bonus

INC_FILES = includes/cub3D.h \
			includes/my_struct.h
INC_BONUS_FILES = includes_bonus/cub3D_bonus.h \
					includes_bonus/my_struct_bonus.h


FT_PRINTF_DIR = ./lib/ft_printf/
LIBFT_DIR = ./lib/libft/
MLX_DIR = ./mlx_linux

DIR_SRC := src/
DIR_OBJ := .object/

DIR_SRC_BONUS := src_bonus/
DIR_OBJ_BONUS := .object_bonus/

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS})
SRCS = $(addprefix ${DIR_SRC},${SRCS_FILE})

OBJS_BONUS = $(patsubst %.c, ${DIR_OBJ_BONUS}%.o, ${SRCS_BONUS})
SRCS_BONUS = $(addprefix ${DIR_SRC_BONUS},${SRCS_FILE_BONUS})

FT_PRINTF = ./lib/ft_printf/libftprintf.a
LIBFT = ./lib/libft/libft.a

CC = cc
MD := mkdir -p
CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -I${INC}
CFLAGS_BONUS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -I${INC_BONUS}
NFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

RM = rm -rf

all: libft ft_printf mlx ${NAME}

${NAME}: ${OBJS} ${FT_PRINTF} ${LIBFT} ${MLX}
	${CC} ${OBJS} ${NFLAGS} ${FT_PRINTF} ${LIBFT} -o $(NAME)

mlx: ${MLX_DIR}
	${MAKE} -C ./mlx_linux

libft: ${LIBFT_DIR}
	${MAKE} -C ./lib/libft all

ft_printf: ${FT_PRINTF_DIR}
	${MAKE} -C ./lib/ft_printf all

${DIR_OBJ}%.o: %.c ${INC_FILES} Makefile
	mkdir -p $(shell dirname $@)
	$(CC) ${CFLAGS} -c $< -o $@

${NAME_BONUS}: ${OBJS_BONUS} ${FT_PRINTF} ${LIBFT} ${MLX}
	${CC} ${OBJS_BONUS} ${NFLAGS} ${FT_PRINTF} ${LIBFT} -o $(NAME_BONUS)

${DIR_OBJ_BONUS}%.o: %.c ${INC_BONUS_FILES} Makefile
	mkdir -p $(shell dirname $@)
	$(CC) ${CFLAGS_BONUS} -c $< -o $@

clean:
	${MAKE} -C ./lib/ft_printf clean
	${MAKE} -C ./lib/libft clean
	${RM} ${DIR_OBJ}
	${RM} ${DIR_OBJ_BONUS}

fclean: clean
	${MAKE} -C ./lib/ft_printf fclean
	${MAKE} -C ./lib/libft fclean
	${RM} ${NAME}
	${RM} ${NAME_BONUS}

bonus: libft ft_printf mlx ${NAME_BONUS}

re: fclean all

.PHONY: all clean fclean bonus re
