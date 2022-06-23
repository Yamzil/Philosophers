# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 20:11:40 by yamzil            #+#    #+#              #
#    Updated: 2022/06/23 22:13:02 by yamzil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread

SRC = 	philosopher.c\
		ft_parsingandinit.c\
		philo_utils.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean : 
	@rm -rf $(OBJ)

fclean :
	@rm -rf $(OBJ) $(NAME)

re : fclean all