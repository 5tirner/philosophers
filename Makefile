# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 23:34:17 by zasabri           #+#    #+#              #
#    Updated: 2023/04/20 01:21:42 by zasabri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= philosopher.c\
		check_input.c\
		ft_atoi.c\
		take_forks.c\
		timer.c\
		if_finish.c\
		
OBJS	= $(SRC:.c=.o)

RM		= rm -rf

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -pthread #-fsanitize=thread

PROG	= philo

all : $(PROG)

$(PROG) : $(OBJS)

	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)
	
clean :

	$(RM) $(OBJS)

fclean : clean

	$(RM) $(PROG)
	
re : fclean all