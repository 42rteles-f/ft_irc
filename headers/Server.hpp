/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/11 17:44:10 by rteles-f         ###   ########.fr       */
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
		bool		_online;
		t_sock		_sock;
		std::string	hostName;
		std::string	password;
		Connections						_connection;
		std::map<std::string, Channel>	_channels;
		std::map<std::string, t_exe>	_functions;

		void	incomingConnections(void);
		void	incomingMessages(void);

		void	privmsgRequest(Client& client);
		void	nickRequest(Client& client);
		void	userRequest(Client& client);
		void	capLsRequest(Client& client);
		void	joinRequest(Client& client);
		void 	whoRequest(Client& client);
		void 	updateChannel(Channel &channel);
		void	kickRequest(Client& client);
		void	partRequest(Client& client);
		void	topicRequest(Client& client);
		void	quitRequest(Client& client);
		void	passRequest(Client& client);
		void	invalidCommand(Client& client);
		void	modeRequest(Client &client);


		//Code -> client.nick -> message;
		std::string	makeMessage(const std::string) const;
		std::string	makeMessage(std::string code, std::string message) const;
		std::string	makeMessage(std::string code, std::string client, std::string message) const;

	public:
		Server();
		~Server();

		Server& operator=(const Server& tocopy);
		t_exe	requestHandler(std::string target);

		bool	setup(char **init);
		void	online(void);
		void	offline(void);
} ;
