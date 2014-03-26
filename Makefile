#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-segu <sde-segu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/24 01:47:17 by sde-segu          #+#    #+#              #
#    Updated: 2014/03/26 19:47:38 by dcouly           ###   ########.fr        #
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
		light_cone.c \
		light_demi_cone.c \
		light_cylinder.c \
		light_demi_cylinder.c \
		light_plan.c \
		light_sphere.c \
		light_dsphere.c \
		draw_sphere.c \
		draw_demi_sphere.c \
		draw_plan.c \
		draw_cone.c \
		draw_demi_cone.c \
		draw_cylinder.c \
		draw_demi_cylinder.c \
		get_dcylindre.c \
		get_dsphere.c \
		get_dcone.c \
		utils.c \
		map_parser.c \
		errors.c \
		rotate.c \
		cam.c \
		mlx_utils.c \
		downscale.c \
		pixels.c \
		progress.c

OBJS = $(SCRFILES:.c=.o)
CC = clang
CFLAGS = -g -Wall -Werror -Wextra -O3
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
