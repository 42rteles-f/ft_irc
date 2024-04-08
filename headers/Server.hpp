/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/07 12:57:04 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

typedef struct  protoent     t_protocol;
typedef struct  sockaddr_in  t_sock;

#define READSIZE	1024
#define CLIENT_ADDED "Client was added successfully"
#define ERROR_JOIN "Error: fail to join."

class Server {
	public:
		typedef void    (Server::*t_exe)(Client&);

	private:
		std::string	hostName;
		Connections	_connection;
		t_sock		_sock;
		bool		_online;
		std::map<std::string, Channel>	_channels;
		std::map<std::string, t_exe>	_functions;

		void	incomingConnections(void);
		void	incomingMessages(void);
		void	invalidCommand(Client& client);
		// void	printClients(void);
		// void	whoIsRequest(Client& client);
		void	joinRequest(Client& client);
		void	nickRequest(Client& client);
		

	public:
		Server();
		Server(const Server& tocopy);
		~Server();

		Server& operator=(const Server& tocopy);
		void messageToClient(Client& client, std::string message);
		t_exe	requestHandler(std::string target);

		void	privmsgRequest(Client& client);
		void	nickRequest(Client& client);
		void	userRequest(Client& client);
		void	capLsRequest(Client& client);

		bool	setup(char **init);
		void	run(void);
		void	online(void);
		void	offline(void);
		void	setHostName(std::string name);
		std::string format(Client& client);
} ;
