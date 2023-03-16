# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 15:01:56 by zasabri           #+#    #+#              #
#    Updated: 2023/03/16 15:17:04 by zasabri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_atoi.c\
		philosopher.c\

OBJS	= $(SRCS:.c=.o)

PROG	= philosopher

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

all : $(PROG)

$(PROG) : $(OBJS)

	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

clean :
	
	$(RM) $(OBJS)

fclean : clean

	$(RM) $(PROG)

re : fclean all