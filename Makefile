#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/24 01:47:17 by sde-segu          #+#    #+#              #
#    Updated: 2014/02/24 01:47:18 by sde-segu         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: all, clean, fclean, re

HEADER = raytracer.h

NAME = raytracer

FCTS = main.c \
		get_infos.c \
		set_mlx.c \
		raytracer.c \
		light.c \
		draw_sphere.c \
		draw_plan.c \
		draw_cone.c \
		draw_cylinder.c

OBJ = $(FCTS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

all: lib $(NAME)

$(NAME): $(OBJ)
	 gcc $(FLAGS) -o $(NAME) $^ -L libft/ -lft -L/usr/X11/lib -lXext -lX11 -lmlx

%.o: %.c
	gcc $(FLAGS) -o $@ -c $< -I libft/includes/

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

lib:
	make -C libft/

re: fclean all