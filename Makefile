# Makefile template for a shared library in C

NAME = cub3D
CC = gcc  # C compiler

#CFLAGS = -Wall -Werror -Wextra -I. -Ilibft/. -c  # C flags
CFLAGS =  -I. -Ilibft/. -c  # C flags

RM = rm -f   # rm command
LB_NAME =	libft.a
LIB_DIR	=	./libft

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
SRCS = test1.c 




OBJS = $(SRCS:.c=.o)

#B_OBJS = $(B_SRCS:.c=.o)

all: libft minilibx $(NAME)

libft:
	make -C libft/

minilibx:
	make -C minilibx/

${LIB_DIR}/${LB_NAME}:
		${MAKE} -C $(LIB_DIR)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -Lminilibx/ -lmlx -framework OPENGL -framework Appkit -Llibft -lft

$(OBJS):$(SRCS)
	@printf "Compiling $<"
	@gcc  -Imlx -Iinc -Ilibft -c $< -o $@
	#@gcc -Wall -Wextra -Werror -Imlx -Iinc -Ilibft -c $< -o $@

#$(B_OBJS):$(B_SRCS)
#	$(CC) $(CFLAGS) $(B_SRCS)

#bonus: $(OBJS) $(B_OBJS)
#	rm -f $(NAME)
#	ar rcs $(NAME) $(OBJS) $(B_OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)
	${MAKE} -C $(LIB_DIR) fclean
	make -C ./minilibx/ clean

fclean: clean
	rm -f $(NAME)
	${MAKE} -C $(LIB_DIR) fclean
	make -C ./minilibx/ clean


re: fclean all

# I use .PHONY to make sure that gnu make will still run even if files called
# clean / fclean / all and re already exist in the directory
.PHONY: clean fclean all re
