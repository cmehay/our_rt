#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 15:09:23 by cmehay            #+#    #+#              #
#    Updated: 2013/11/26 11:09:29 by cmehay           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a
SRCDIR = .
HEADDIR = .
HEAD = libft.h
HEADFILES = $(addprefix $(HEADDIR)/, $(HEAD))
SRC = ft_memset.c ft_putchar.c ft_putstr.c ft_bzero.c ft_putchar_fd.c \
	ft_putnbr.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putendl.c \
	ft_strlen.c ft_strcat.c ft_strncat.c ft_strtrim.c ft_isalpha.c \
	ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_atoi.c ft_tolower.c \
	ft_toupper.c ft_memalloc.c ft_strnew.c ft_memcpy.c ft_memccpy.c \
	ft_memmove.c ft_memchr.c ft_memcmp.c ft_strdup.c ft_strchr.c ft_strlcat.c \
	ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_memdel.c \
	ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
	ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
	ft_strsplit.c ft_strcpy.c ft_strncpy.c ft_itoa.c get_next_line.c \
	mem_lst.c cool_itoa.c cool_next_line.c ft_arraydel.c ft_strtest.c \
	ft_strrep.c ft_higher.c ft_lower.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	ft_lstiter.c
SRCFILES = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(SRC:.c=.o)
CC = gcc
AR = ar
RANLIB = ranlib
CFLAGS = -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rc $(NAME) $(OBJ)
	$(RANLIB) $(NAME)

%.o: %.c $(HEADFILES)
	$(CC) $(CFLAGS) -I$(HEADDIR) -c -o $@ $<

.PHONY: all clean fclean re

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
