# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 08:28:08 by beaudibe          #+#    #+#              #
#    Updated: 2022/12/08 21:49:29 by beaudibe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR_PRINTF = printf/

SRCS			=	ft_striteri.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c	\
ft_putchar_fd.c ft_strmapi.c ft_itoa.c ft_split.c ft_strjoin.c ft_strtrim.c		\
ft_substr.c ft_calloc.c ft_toupper.c ft_isalpha.c ft_isdigit.c ft_isalnum.c		\
ft_isascii.c ft_isprint.c ft_tolower.c ft_atoi.c ft_strncmp.c ft_strnstr.c		\
ft_strchr.c ft_strrchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strdup.c		\
ft_memcmp.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c		\
ft_memchr.c ft_strclen.c ft_putnbr_base.c ft_lstmap.c ft_lstiter.c ft_lstclear.c\
ft_lstdelone.c ft_lstadd_back.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c		\
ft_lstnew.c ft_printf.c ft_putchar_printf.c ft_putnbr_base_printf.c				\
ft_putnbr_printf.c ft_putstr_printf.c get_next_line.c ft_isspace.c
OBJS			=	$(SRCS:.c=.o)

SRCS_PRINTF		=	ft_printf.c ft_putchar_printf.c ft_putnbr_base_printf.c\
ft_putnbr_printf.c ft_putstr_printf.c
OBJS_PRINTF		=	$(SRCS_PRINTF:.c=.o)
PRINTF			=	$(addprefix $(SRC_DIR_PRINTF), $(SRCS_PRINTF))


INCLUDES		=	./includes/
CC				=	clang
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -I $(INCLUDES)
NAME			=	libft.a

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					ar rcs $(NAME) $(OBJS)



clean			:
					$(RM) $(OBJS)

fclean			:	clean
					$(RM) $(NAME)

re				:	fclean $(NAME)

.c.o			:
					${CC} ${CFLAGS}  -c $< -o ${<:.c=.o}

.PHONY			:	all clean fclean re
