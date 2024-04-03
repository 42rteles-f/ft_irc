/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 01:36:25 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

typedef struct  protoent     t_protocol;
typedef struct  sockaddr_in  t_sock;
typedef void    (Server::*t_exe)();

#define READSIZE 1024

class Server {
	private:
		// std::map<std::string, Channel>	_channels;
		// std::map<std::string, t_exe>		commands;
		Connections					_connection;
		t_sock	_sock;
		bool	_online;
		static void	invalidCommand(std::string);

		void	updateChannels(void);
		void	fowardMessage(std::string input, int fd);
		void	executeClient(Client& client);

	public:
		Server();
		Server(const Server& tocopy);
		~Server();

		Server& operator=(const Server& tocopy);

		void	incomingConnections(void);
		void	incomingMessages(void);
		void	printClients(void);

		void	online(void);
		void	run(void);
		bool	setup(char **init);
		void	offline(void);
} ;