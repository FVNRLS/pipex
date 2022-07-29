
NAME 		= 		fractol

CC 			= 		cc

FLAGS		= 		-Wall -Wextra -Werror -g

SRC 		= 		./main.c																	\

OBJ 		= 		${SRC:.c=.o}

#LIBS		=

$(NAME): $(OBJ)
	${CC} ${FLAGS} ${OBJ} -o pipex

all: $(NAME)

clean:
	rm -f ${OBJ}

fclean:
	rm -f ${OBJ}
	rm -f ${NAME}

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus