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
SRCS = ./src/parser/main_parser.c \
./src/main.c \
./gnl/get_next_line.c \
./gnl/get_next_line_utils.c \



OBJS = $(SRCS:.c=.o)


all:  $(MLX) $(LIBFT) $(NAME)
	@printf "mohit"
$(MLX):
	@printf "compiling mlx"
	make -C mlx/

$(LIBFT):
	@printf "compiling libft\n"
	make -C libft/

$(NAME): $(OBJS)
	@printf "$(OBJS)"
	$(CC) -Imlx -Ilibft -Ignl -o $@ $^ -Lmlx -lmlx -framework OPENGL -framework Appkit -lm -Llibft -lft

$(OBJS):$(SRCS)
	@printf "$(OBJS)"
	@printf "Compiling $<"
	@gcc  -Imlx -Ilibft -Ignl -c $< -o $@
	#@gcc -Wall -Wextra -Werror -Imlx -Iinc -Ilibft -c $< -o $@

#$(B_OBJS):$(B_SRCS)
#	$(CC) $(CFLAGS) $(B_SRCS)

#bonus: $(OBJS) $(B_OBJS)
#	rm -f $(NAME)
#	ar rcs $(NAME) $(OBJS) $(B_OBJS)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(MLX)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) fclean


re: fclean all

# I use .PHONY to make sure that gnu make will still run even if files called
# clean / fclean / all and re already exist in the directory
.PHONY: clean fclean all re
