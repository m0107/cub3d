UNAME_S				:= $(shell uname -s)
OS					= 0

ifeq ($(UNAME_S), Linux)
	OS = 1
	LGL := -lGL -lm
	LGL_INC := -I/usr/include/
	MLXFLAG := -lXext -lX11 -lbsd
else ifeq ($(UNAME_S), Darwin)
	OS = 2
	MLXFLAG := -framework OpenGL -framework Appkit
endif

$(info    VAR is $(MLXFLAG))

CC=gcc


NAME = cub3D
CC = gcc  -fsanitize=address -g3 # C compiler
# -fsanitize=address

#CFLAGS = -Wall -Werror -Wextra -I. -Ilibft/. -c  # C flags
INCLUDES =  -Isrc -Ignl # C flags

CFLAGS	= -Ofast -D OS=$(OS)  $(INCLUDES)

RM = rm -f   # rm command

#include all your main .c files here
SRCS = ./src/main.c \
src/error.c \
src/keys_hook.c \
src/parser/main_parser.c \
src/parser/tex_parser.c \
src/parser/sprite_parser.c \
src/parser/res_parser.c \
src/parser/color_parser.c \
src/parser/map_parser.c \
src/parser/map_parser_helper.c \
src/utils/ft_atoi_cub.c \
src/utils/map_check.c \
src/utils/player_pos_helper.c \
src/utils/space.c \
src/movement/move.c \
src/movement/move1.c \
src/render/render.c \
src/render/render_sprites.c \
src/render/render_sprites_helper.c \
src/render/render_helper.c \
src/render/render_component.c \


GNL_SRCS = gnl/get_next_line.c \
gnl/get_next_line_utils.c \

GNL_OBJS = $(GNL_SRCS:.c=.o)

OBJS = $(SRCS:.c=.o)


all:  $(LIBFT)  $(NAME)
	@printf "Makefile starts\n"

$(NAME): $(OBJS) $(GNL_OBJS)
	@printf "$(OBJS)\n"
	$(CC) $(CFLAGS) $^ -o $@  -lmlx $(LGL_INC) $(MLXFLAG) -lm


clean:
	rm -f $(OBJS) $(GNL_OBJS)
	#make -C $(LIBFT_DIR) clean
	#make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	#make -C $(LIBFT_DIR) fclean
	#make -C $(MLX_DIR) fclean


re: fclean all

# I use .PHONY to make sure that gnu make will still run even if files called
# clean / fclean / all and re already exist in the directory
.PHONY: clean fclean all re
