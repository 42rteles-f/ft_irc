# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 20:08:19 by rteles-f          #+#    #+#              #
#    Updated: 2024/04/11 19:28:49 by rteles-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_RESET =	\033[0m
COLOR_GREEN =	\033[32m

NAME	=	ft_irc
SRCS = src/Channel.cpp src/Client.cpp src/Connections.cpp src/main.cpp src/Server.cpp src/Server_Requests.cpp
CXX		=	c++

SRCS = src/Channel.cpp src/Client.cpp src/Connections.cpp src/main.cpp src/Server.cpp src/Server_Requests.cpp

OBJS_PATH = obj/
SRC_PATH = src/

CXXFLAGS	=	-I ./headers -std=c++98 -Wall -Wextra -Werror -g# -fsanitize=address

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
			@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: IRC Built"


clean:			
				@$(RM) $(OBJS_PATH)	
				@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: Clean"


fclean:			clean
				@$(RM) $(NAME)
				@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: Full"


re:				fclean att all

att:
				@sed -i "17s,.*,SRCS = $$(echo src/*.cpp)," Makefile

r:				re
				@valgrind ./$(NAME)

.PHONY: 	all clean fclean re norm