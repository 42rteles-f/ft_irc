/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 22:17:11 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

typedef struct  protoent     t_protocol;
typedef struct  sockaddr_in  t_sock;
typedef void    (Server::*t_exe)();

#define READSIZE	1024

class Server {
	private:
		Connections	_connection;
		t_sock		_sock;
		bool		_online;
		std::map<std::string, Channel>	_channels;

		void	executeClient(Client& client);		
		void	incomingConnections(void);
		void	incomingMessages(void);

		void	printClients(void);

	public:
		Server();
		Server(const Server& tocopy);
		~Server();

		Server& operator=(const Server& tocopy);

		const std::map<std::string, t_exe>	commands;

		bool	setup(char **init);
		void	run(void);
		void	online(void);
		void	offline(void);
} ;
