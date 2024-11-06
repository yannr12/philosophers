# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 16:05:37 by yrio              #+#    #+#              #
#    Updated: 2024/11/06 11:26:34 by yrio             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror
FLAG_PHILO = -fsanitize=thread -g -pthread
SRC = main.c utils_parsing.c philo_routine.c init.c utils_execution.c monitor.c utils_libft.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		cc $(FLAGS) $(FLAG_PHILO) -o $(NAME) $(OBJ)
#$(FLAG_PHILO)
$(OBJ): $(SRC)
		cc $(FLAGS) $(FLAG_PHILO) -c $(SRC)

clean:
	rm -rf prog *.o
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all