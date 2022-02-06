# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suylee <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 20:46:11 by suylee            #+#    #+#              #
#    Updated: 2021/07/26 20:46:34 by suylee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c thread_action.c utils.c
OBJS = ${SRCS:.c=.o}
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

.c.o:
	gcc ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
		gcc -o ${NAME} ${OBJS} -lpthread

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
