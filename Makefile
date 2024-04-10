# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 20:08:19 by rteles-f          #+#    #+#              #
#    Updated: 2024/04/03 21:59:08 by rteles-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_irc

CXX		=	c++

SRCS = src/Channel.cpp src/Client.cpp src/Connections.cpp src/Server.cpp src/Server_Requests.cpp src/main.cpp

OBJS_PATH = obj/
SRC_PATH = src/

CXXFLAGS	=	-I ./headers #-Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

RM			= 	rm -fr

$(OBJS): 	$(OBJS_PATH)

OBJS	=	$(SRCS:$(SRC_PATH)%.cpp=$(OBJS_PATH)%.o)

all: 		$(NAME)

$(OBJS_PATH)%.o: $(SRC_PATH)%.cpp | $(OBJS_PATH)
			@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(NAME):	$(OBJS)
			@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:			
				@$(RM) $(OBJS_PATH)	

fclean:			clean
				@$(RM) $(NAME)

re:				fclean att all

att:
				@sed -i "17s,.*,SRCS = $$(echo src/*.cpp)," Makefile

r:				re
				@valgrind ./$(NAME)

.PHONY: 	all clean fclean re norm