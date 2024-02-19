# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 20:08:19 by rteles-f          #+#    #+#              #
#    Updated: 2024/02/19 18:08:49 by rteles-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	ft_irc

CC			= 	c++ #-g -fsanitize=address

CFLAGS		= 	#-Wall -Wextra -Werror -std=c++98

RM			= 	rm -f

INCLUDES	= 	-Iheaders/

SRCS		=	src/gnl/get_next_line.c src/main/irc.cpp

OBJS		= 	$(SRCS:.cpp=.o)

all: 		$(NAME)

$(NAME):	$(OBJS) 
			@$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
			$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

clean:
			@$(RM) $(OBJS)

fclean: 	clean
				@$(RM) $(NAME)

re:			fclean all

norm :
			@norminette -R CheckForbiddenSourceHeader $(SRCS) headers/

.PHONY: 	all clean fclean re norm