# Makefile template for a shared library in C

NAME = cub3D
CC = gcc  # C compiler

#CFLAGS = -Wall -Werror -Wextra -I. -Ilibft/. -c  # C flags
CFLAGS =  -Isrc/. -Ilibft/. -Imlx/. -Ignl/. -c  # C flags

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
src/parser/main_parser.c \
src/parser/tex_parser.c \
src/parser/res_parser.c \
src/parser/color_parser.c \


GNL_SRCS = gnl/get_next_line.c \
gnl/get_next_line_utils.c \

GNL_OBJS = $(GNL_SRCS:.c=.o)

OBJS = $(SRCS:.c=.o)


all:  $(MLX) $(LIBFT)  $(NAME)
	@printf "Makefile starts\n"

gnl/%.o: gnl/%.c
	$(CC) -Ignl -c $< -o $@

$(MLX):
	@printf "compiling mlx\n"
	make -C mlx/

$(LIBFT):
	@printf "compiling libft\n"
	make -C libft/

$(NAME): $(OBJS) $(GNL_OBJS)
	@printf "$(OBJS)\n"
	$(CC) -Isrc -Imlx -Ilibft -Ignl -o $@ $^ -Lmlx -lmlx -framework OPENGL -framework Appkit -lm -Llibft -lft


src/%.o: src/%.c
	$(CC) -Ignl -c $< -o $@


src/parser/%.o: src/parser/%.c
	$(CC) -Ignl -c $< -o $@


#$(B_OBJS):$(B_SRCS)
#	$(CC) $(CFLAGS) $(B_SRCS)

#bonus: $(OBJS) $(B_OBJS)
#	rm -f $(NAME)
#	ar rcs $(NAME) $(OBJS) $(B_OBJS)

clean:
	rm -f $(OBJS)
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
