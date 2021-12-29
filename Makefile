# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 11:16:01 by cjulienn          #+#    #+#              #
#    Updated: 2021/12/29 11:29:08 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./philosophers.c

OBJS = $(SRCS:.c=.o)

INCLUDE_PATH = .

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_PATH)

RM = rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
	@echo $(NAME) successfully made !!!

all: 
	$(NAME)

clean:
	$(RM) $(OBJS)
	
fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
