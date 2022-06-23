# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamzil <yamzil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/18 22:15:05 by yamzil            #+#    #+#              #
#    Updated: 2022/06/23 23:06:40 by yamzil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread

SRC =	philo_bonus.c\
		ft_pars_init_bonus.c\
		libft_utils.c\
		utils_bonus.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean : 
	@rm -rf $(OBJ)

fclean :
	@rm -rf $(OBJ) $(NAME)

re : fclean all