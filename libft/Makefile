# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 13:57:19 by doohkim           #+#    #+#              #
#    Updated: 2023/03/21 15:29:05 by doohkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
AR = ar rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c		\
	ft_bzero.c			\
	ft_calloc.c			\
	ft_isalnum.c		\
	ft_isalpha.c		\
	ft_isascii.c		\
	ft_isdigit.c		\
	ft_isprint.c		\
	ft_itoa.c			\
	ft_memchr.c			\
	ft_memcmp.c			\
	ft_memcpy.c			\
	ft_memmove.c		\
	ft_memset.c			\
	ft_putchar_fd.c		\
	ft_putendl_fd.c		\
	ft_putnbr_fd.c		\
	ft_putstr_fd.c		\
	ft_split.c			\
	ft_strchr.c			\
	ft_strdup.c			\
	ft_striteri.c		\
	ft_strjoin.c		\
	ft_strlcat.c		\
	ft_strlcpy.c		\
	ft_strlen.c			\
	ft_strmapi.c		\
	ft_strncmp.c		\
	ft_strnstr.c		\
	ft_strrchr.c		\
	ft_strtrim.c		\
	ft_substr.c			\
	ft_tolower.c		\
	ft_toupper.c		\
	get_next_line.c		\
	get_next_line_util.c	\
	get_next_line_clear.c
BOUNS_SRCS = ft_lstadd_back.c	\
			ft_lstadd_front.c	\
			ft_lstclear.c		\
			ft_lstdelone.c		\
			ft_lstiter.c		\
			ft_lstlast.c		\
			ft_lstnew.c			\
			ft_lstsize.c		\
			ft_lstmap.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BOUNS_SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I .

clean:
	$(RM) $(OBJS) $(BONUS_OBJS) bonus_ok

fclean:
	make clean
	$(RM) $(NAME)

re:
	make fclean
	make all

bonus: bonus_ok

bonus_ok: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $^
	touch bonus_ok

.PHONY : all clean fclean re bonus