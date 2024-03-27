/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/03/27 20:55:22 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>
# include <iostream>
# include <vector>
# include <list>
# include <map>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <stdlib.h>
# include <netdb.h>
# include <netinet/in.h>
# include <stdio.h>
# include <unistd.h>
# include <strings.h>
# include <string.h>


typedef struct protoent     t_protocol;
typedef struct sockaddr_in  t_sock;

class Client;
class Channel;

class Server {
	private:
		std::map<std::string, Channel>	_channels;
		std::vector<int>	connections;
		int		server_fd;
		t_sock	_sock;
		fd_set	request_set;
		fd_set	client_set;
		bool	_online;

		void	updateChannels(void);

	public:
		Server();
		Server(const Server& tocopy);
		~Server();

		Server& operator=(const Server& tocopy);

		void	setup(void);
		void	online(void);
		void	offline(void);
} ;
