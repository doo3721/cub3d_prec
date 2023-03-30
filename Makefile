# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doohkim <doohkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 15:22:41 by doohkim           #+#    #+#              #
#    Updated: 2023/03/21 16:30:43 by doohkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
LIB_MLX = libmlx.dylib
LIBFT = libft.a
CC = cc
CPPFLAGS = -Wall -Wextra -Werror -g
FRAMEWORK = -framework metal
MLX_INCS = ./minilibx_mms/
PRINTF_INCS = ./ft_printf/
LIBFT_INCS = ./libft/
HEADER_INCS = ./includes/
SRCS_INCS = ./srcs/
SRCS_NAME = main \
			utils \
			error
SRCS = $(addsuffix .c, $(addprefix $(SRCS_INCS), $(SRCS_NAME)))
OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(LIB_MLX):
	make -C $(MLX_INCS)
	mv $(MLX_INCS)$(LIB_MLX) $(LIB_MLX)

$(LIBFT):
	make -C $(LIBFT_INCS)
	mv $(LIBFT_INCS)$(LIBFT) $(LIBFT)

$(NAME): $(OBJS) $(LIBFT) $(LIB_MLX)
	$(CC) $(CPPFLAGS) -o $@ $^ $(FRAMEWORK) -I$(HEADER_INCS)

%.o: %.c
	$(CC) $(CPPFLAGS) -c -o $@ $< -I$(HEADER_INCS)

clean:
	make clean -C $(MLX_INCS)
	make clean -C $(LIBFT_INCS)
	$(RM) $(LIBFT)
	$(RM) $(OBJS)

fclean:
	make clean
	$(RM) $(LIB_MLX)
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re