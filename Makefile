# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 11:35:34 by ael-bagh          #+#    #+#              #
#    Updated: 2021/10/23 12:17:55 by ael-bagh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c dining_table.c helpers.c initialisation.c parser.c supervisor.c time_functions.c
NAME = philo

all: $(NAME)

$(NAME): 
	gcc -Wall -Werror -Wextra -pthread -o philo $(SRC)
clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)
re: fclean all