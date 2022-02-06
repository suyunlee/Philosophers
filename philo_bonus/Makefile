# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suylee <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 00:24:18 by suylee            #+#    #+#              #
#    Updated: 2021/07/27 00:24:45 by suylee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRCS = bonus_main.c bonus_action.c bonus_utils.c
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
