
NAME 		= 		pipex

CC 			= 		cc

FLAGS		= 		-Wall -Wextra -Werror -g

SRC 		= 		./main.c													\
					./src/input_parser.c										\
					./src/pipe_manager.c										\
					./src/error_manager.c										\
					./src/tools/ft_split.c										\
					./src/tools/free_all_malloc.c								\
					./src/tools/ft_strdup.c										\
					./src/tools/ft_strjoin.c									\
					./src/tools/ft_strncmp.c									\

OBJ 		= 		${SRC:.c=.o}

LIBS		=		./lib/get_next_line/get_next_line.a							\
					./lib/ft_printf/libftprintf.a 								\

$(NAME): $(OBJ)
	make -C ./lib/get_next_line
	make -C ./lib/ft_printf
	${CC} ${FLAGS} ${OBJ} ${LIBS} -o pipex

all: $(NAME)

clean:
	cd ./lib/get_next_line && make clean && cd .. && cd ..
	cd ./lib/ft_printf && make clean && cd .. && cd ..
	rm -f ${OBJ}

fclean:
	cd ./lib/get_next_line && make fclean && cd .. && cd ..
	cd ./lib/ft_printf && make fclean && cd .. && cd ..
	rm -f ${OBJ}
	rm -f ${NAME}

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus