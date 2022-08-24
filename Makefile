# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 11:52:23 by rmazurit          #+#    #+#              #
#    Updated: 2022/08/02 15:35:43 by rmazurit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	pipex
BONUS_NAME	=	pipex_bonus

CC 		= 	cc

FLAGS		= 	-Wall -Wextra -Werror

SRC 		= 	./main.c				\
			./src/input_parser.c			\
			./src/pipe_processor.c			\
			./src/error_manager.c			\
			./src/tools/free_all_malloc.c		\

TOOLS_SRC	=	./src/tools/ft_split.c			\
			./src/tools/ft_strdup.c			\
			./src/tools/ft_strjoin.c		\
			./src/tools/ft_strncmp.c		\
			./src/tools/ft_strlen.c			\

BONUS_SRC	= 	./src/bonus/main_bonus.c		\
			./src/bonus/error_manager_bonus.c	\
			./src/bonus/input_parser_bonus.c	\
			./src/bonus/command_extractor.c		\
			./src/bonus/execv_commands_bonus.c	\
			./src/bonus/pipe_processor_bonus.c	\
			./src/bonus/heredoc_processor.c		\
			./src/tools/free_all_malloc_bonus.c	\

OBJ 		= 	${SRC:.c=.o}
TOOLS_OBJ 	= 	${TOOLS_SRC:.c=.o}
BONUS_OBJ	=	${BONUS_SRC:.c=.o}

LIBS		=	./lib/get_next_line/get_next_line.a	\

$(NAME): $(OBJ) $(TOOLS_OBJ)
	${CC} ${FLAGS} ${OBJ} ${TOOLS_OBJ} -o pipex

all: $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(TOOLS_OBJ)
	make -C ./lib/get_next_line
	${CC} ${FLAGS} ${BONUS_OBJ} ${TOOLS_OBJ} ${LIBS} -o pipex

bonus: $(BONUS_NAME)

clean:
	cd ./lib/get_next_line && make clean && cd .. && cd ..
	rm -f ${OBJ} ${TOOLS_OBJ} ${BONUS_OBJ}

fclean:
	cd ./lib/get_next_line && make fclean && cd .. && cd ..
	rm -f ${OBJ} ${TOOLS_OBJ} ${BONUS_OBJ} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
