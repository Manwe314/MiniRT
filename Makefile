NAME	:= minirt
USER	= beaudibe
#CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
CFLAGS	:= -Ofast -g
LIBMLX	:= ./lib/MLX42
INCDIR = includes
HEADERS	:= -I ../include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a ./lib/libft/libft.a -ldl -lglfw -pthread -lm -L /Users/${USER}/.brew/lib/
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}
LIBFT	= ./lib/libft

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCDIR) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	make -C ${LIBFT}
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -g -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx

# SRCS = ${shell find ./src -iname "*.c"}

# OBJS = ${SRCS:.c=.o}

# CC = gcc
# CFLAGS = -Wall -Wextra -Werror -Iincludes -lmlx -lXext -lX11

# RM = rm -rf

# all: ${NAME}
# ${NAME}: ${OBJS}
# 	@${MAKE} -C ./lib/libft
# 	@${CC} ${CFLAGS} ${OBJS} ./lib/libft/libft.a ./lib/minilibx-linux/libmlx.a -o ${NAME}


# clean:
# 	@${MAKE} -C ./lib/libft fclean
# 	@${RM} ${OBJS}

# fclean: clean
# 	@${RM} ${NAME}

# re: fclean all

# .PHONY: all clean fclean re
