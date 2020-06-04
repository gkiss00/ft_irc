SRCS=	main.cpp \
		utils_1.cpp \
		input_check.cpp \

OBJS= ${SRCS:.cpp=.o}

NAME= ircserv

FLAGS = -Wall -Wextra -Werror

DELETE = rm -rf

all: ${NAME}
	
${NAME}: ${OBJS}
	clang++ -o ${NAME} ${FLAGS} ${OBJS}

clean:
	${DELETE} ${OBJS}

fclean: clean
	${DELETE} ${NAME};

re: fclean all

.PHONY: all clean flcean re