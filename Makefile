#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/24 01:47:17 by sde-segu          #+#    #+#              #
#    Updated: 2014/03/16 16:05:53 by dcouly           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = raytracer
SRCDIR = srcs
HEADDIR = srcs
HEAD = raytracer.h
HEADFILES = $(addprefix $(HEADDIR)/, $(HEAD))
SCRFILES = $(addprefix $(SRCDIR)/, $(SRC))
SRC =	main.c \
		get_infos.c \
		set_mlx.c \
		raytracer.c \
		light.c \
		draw_sphere.c \
		draw_plan.c \
		draw_cone.c \
		draw_cylinder.c \
		utils.c \
		map_parser.c \
		errors.c \
		rotate.c \
		cam.c \
		mlx_utils.c \
		downscale.c \
		pixels.c

OBJS = $(SCRFILES:.c=.o)
CC = clang
CFLAGS = -g -O3 -Wall -Werror -Wextra
LDFLAGS = -L libft/ -lft -L/usr/X11/lib -lXext -lX11 -lmlx -lm
LIBFT = libft/libft.a

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C libft/

%.o: %.c $(HEADERFILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE) -C libft/ $@
	/bin/rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft/ $@
	/bin/rm -f $(NAME)

re: fclean all
