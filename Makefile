NAME	:= miniRT
CFLAGS	:= -Wextra -Wall -Werror -Ofast -g -DDEBUG=1
LIBMLX	:= ./lib/MLX42
INCDIR = includes
LGLFW_PATH := $(shell brew --prefix glfw)
HEADERS	:= -I ../include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a ./lib/libft/libft.a -ldl -lglfw -pthread -lm -L $(LGLFW_PATH)/lib/

SRCS	= 	src/add.c					\
			src/advanced_collision.c	\
			src/checking_input.c		\
			src/hook2.c					\
			src/random.c				\
			src/utils_input2.c			\
			src/cone.c					\
			src/light.c 				\
			src/ray.c 					\
			src/validate_input.c		\
			src/ambient.c				\
			src/cylinder.c				\
			src/main.c					\
			src/ray_tracing.c			\
			src/validate_input2.c		\
			src/basic_collision.c		\
			src/get_input_list.c		\
			src/math.c					\
			src/ray_tracing_bonus.c		\
			src/vector_math.c			\
			src/basic_collision2.c		\
			src/get_obj.c				\
			src/matrice.c				\
			src/sphere.c				\
			src/vector_math2.c			\
			src/calculate_collision.c	\
			src/get_obj2.c				\
			src/utils.c					\
			src/vector_math3.c			\
			src/camera.c				\
			src/get_to_next_param.c		\
			src/param_pixel.c			\
			src/utils2.c				\
			src/vector_math4.c			\
			src/camera_eye.c			\
			src/hook.c					\
			src/plane.c					\
			src/utils_input.c			\
			src/vector_math5.c

OBJS	= ${SRCS:.c=.o}
LIBFT	= ./lib/libft

all: libmlx $(NAME)


libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCDIR) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	make -C ${LIBFT}
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

bonus: libmlx $(OBJS)
	make -C ${LIBFT}
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o miniRT_bonus

clean:
	@make -C $(LIBFT) clean
	@rm -f $(OBJS)


fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@rm -f $(NAME)_bonus

git: fclean
	git add *
	git commit -m "auto commit"
	git push

brew:
	brew install glfw

re: clean all

.PHONY: all, clean, fclean, re, libmlx, git, brew, bonus