# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 16:05:37 by yrio              #+#    #+#              #
#    Updated: 2024/05/22 10:40:33 by yrio             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror
FLAG_PHILO = -fsanitize=thread -g -pthread
LIBFT = libft/libft.a
SRC = main.c utils_parsing.c philo_routine.c init.c utils_execution.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		cc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
#$(FLAG_PHILO)
$(OBJ): $(SRC)
		make bonus -C libft
		cc $(FLAGS) -c $(SRC)

clean:
	make clean -C libft
	rm -rf prog *.o
	
fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all