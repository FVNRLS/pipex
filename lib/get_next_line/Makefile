# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#   By: rmazurit <rmazurit@student.42heilbronn.de>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/29 13:47:53 by rmazurit          #+#    #+#              #
#    Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 		get_next_line.a

CC 			= 		cc

FLAGS		= 		-Wall -Wextra -Werror

SRC 		= 		get_next_line.c							\
                    get_next_line_utils.c					\

OBJ 		= 		${SRC:.c=.o}

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -c $(SRC)
	ar rc $(NAME) *.o

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re