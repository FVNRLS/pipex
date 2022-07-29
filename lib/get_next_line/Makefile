# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/29 13:47:53 by rmazurit          #+#    #+#              #
#    Updated: 2022/07/29 13:58:27 by rmazurit         ###   ########.fr        #
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