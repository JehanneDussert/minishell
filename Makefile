NAME = minishell
CC = gcc
C_FLAGS = -Wall -Werror -Wextra

ERROR_PATH = ms_error/
ERROR_FILES = 
ERROR =

EXECUTION_PATH = ms_execution/
EXECUTION_FILES = 
EXECUTION =

PARSING_PATH = ms_parsing/
PARSING_FILES =
PARSING =

SRCS_PATH = srcs/
SRCS_FILES = ${ERROR} ${EXECUTION} ${PARSING}
SRCS =

OBJS = ${SRCS:.c=.o}

$(NAME):	${OBJS}
		${CC}

all:	${NAME}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

make re: fclean all