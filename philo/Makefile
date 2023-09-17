# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmonpeat <mmonpeat@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 12:51:36 by mmonpeat          #+#    #+#              #
#    Updated: 2023/09/17 13:01:24 by mmonpeat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = include/philo.h

INCLUDE = -I./ 

SRCS = main.c loop.c utils.c check.c

OBJS = $(addprefix ${OBJ_DIR}/,$(SRCS:.c=.o))

DEPS = $(addsuffix .d,$(basename ${OBJS}))

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m

OBJ_DIR = obj

${OBJ_DIR}/%.o : %.c Makefile
	@mkdir -p ${OBJ_DIR}
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${INCLUDE} -c $< -o $@

all:
	@${MAKE} ${NAME} #--no-print-directory
#all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)philosphers compiled 😎$(NC)"

-include ${DEPS}

clean:
	rm -rf ${OBJ_DIR}
	@echo "$(RED)\nDestruction successful 👀\n$(NC)"

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
#.SILENT: all clean fclean re ${NAME}
