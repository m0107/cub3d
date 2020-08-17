UNAME_S				:= $(shell uname -s)
OS					= 0

ifeq ($(UNAME_S), Linux)
	OS = 1
	LGL := -lGL -lm
	LGL_INC := /usr/include/
	MLXFLAG := -lXext -lX11 -lbsd
else ifeq ($(UNAME_S), Darwin)
	OS = 2
	MLXFLAG := -framework OpenGL -framework Appkit
endif

$(info    VAR is $(MLXFLAG))

CC=gcc


NAME = cub3D
CC = gcc  # C compiler
# -fsanitize=address

#CFLAGS = -Wall -Werror -Wextra -I. -Ilibft/. -c  # C flags
INCLUDES =  -Isrc -Ilibft -Ignl # C flags

CFLAGS	= -Ofast -D OS=$(OS)  $(INCLUDES)

RM = rm -f   # rm command
LIBFT_DIR	=	./libft
LIBFT =	$(LIB_DIR)/libft.a

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a


# Include all your bonus files here
#B_SRCS = ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstsize.c \


#include all your main .c files here
SRCS = ./src/main.c \
src/error.c \
src/parser/main_parser.c \
src/parser/tex_parser.c \
src/parser/sprite_parser.c \
src/parser/res_parser.c \
src/parser/color_parser.c \
src/parser/map_parser.c \
src/utils/ft_atoi_cub.c \
src/utils/map_check.c \
src/utils/player_pos_helper.c \
src/utils/space.c \

GNL_SRCS = gnl/get_next_line.c \
gnl/get_next_line_utils.c \

GNL_OBJS = $(GNL_SRCS:.c=.o)

OBJS = $(SRCS:.c=.o)


all:  $(LIBFT)  $(NAME)
	@printf "Makefile starts\n"


$(MLX):
	@printf "compiling mlx\n"
	make -C mlx/

$(LIBFT):
	@printf "compiling libft\n"
	make -C libft/

$(NAME): $(OBJS) $(GNL_OBJS)
	@printf "$(OBJS)\n"
	$(CC) $(CFLAGS) $^ -o $@  -lmlx  $(MLXFLAG) -lm   -Llibft -lft






#$(B_OBJS):$(B_SRCS)
#	$(CC) $(CFLAGS) $(B_SRCS)

#bonus: $(OBJS) $(B_OBJS)
#	rm -f $(NAME)
#	ar rcs $(NAME) $(OBJS) $(B_OBJS)

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
