# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 11:35:34 by ael-bagh          #+#    #+#              #
#    Updated: 2021/10/18 11:39:02 by ael-bagh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c
NAME = philosophers

all: $(NAME)

$(NAME): 
	gcc -Wall -Werror -Wextra -pthread -o philosophers $(SRC)
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re: fclean all