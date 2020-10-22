NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT_PATH = libft/
LIBFT = libft.a

GNL_PATH = get_next_line/
GNL_FILES = get_next_line.c get_next_line_utils.c
GNL_SRCS = ${addprefix ${GNL_PATH}, ${GNL_FILES}}

MS_ERRORS_PATH = ms_errors/
MS_ERRORS_FILES = line_errors.c ft_error_msg.c free_splits.c
SRCS_MS_ERRORS = ${addprefix ${MS_ERRORS_PATH}, ${MS_ERRORS_FILES}}

MS_PARSING_PATH = ms_parsing/
MS_PARSING_FILES = command_id.c echo.c cd.c pwd.c unset.c export.c exec.c export_2.c env.c
SRCS_MS_PARSING = ${addprefix ${MS_PARSING_PATH}, ${MS_PARSING_FILES}}

MS_UTILS_PATH = ms_utils/
MS_UTILS_FILES = skips.c split_quote.c welcome_bye.c ft_init.c lst_utils.c lst_utils2.c
SRCS_MS_UTILS = ${addprefix ${MS_UTILS_PATH}, ${MS_UTILS_FILES}}

SRCS_PATH = srcs/
SRCS_FILES = ${SRCS_MS_ERRORS} ${SRCS_MS_PARSING} ${SRCS_MS_UTILS}
SRCS_MS = ${addprefix ${SRCS_PATH}, ${SRCS_FILES}}

SRCS = main.c \
		${GNL_SRCS} ${SRCS_MS}

SRCS_LIBFT = ft_memset.c ft_bzero.c ft_strlen.c ft_toupper.c ft_tolower.c \
			ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c \
			ft_strnstr.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_isascii.c ft_isprint.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_split.c ft_strmapi.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c ft_itoa_base.c ft_free.c ft_memalloc.c ft_free.c \
			ft_strcmp.c

OBJS	= ${SRCS:.c=.o}

$(NAME)	:	${OBJS} ${LIBFT_PATH}${LIBFT}
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L ${LIBFT_PATH} -lft

$(LIBFT_PATH)$(LIBFT): ${LIBFT_FILES}
	make all -C ${LIBFT_PATH}

all : ${NAME}

clean :
		rm -f ${OBJS}

fclean : clean
		rm -f ${NAME}
		make -C ${LIBFT_PATH} fclean

re : fclean all

work : all clean
