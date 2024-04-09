/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/09 10:39:37 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Server.hpp>

Server::Server():
_online(false)
{
	_functions["JOIN"] = &Server::joinRequest;
	_functions["NICK"] = &Server::nickRequest;
	_functions["USER"] = &Server::userRequest;
	_functions["KICK"] = &Server::kickRequest;
	_functions["PRIVMSG"] = &Server::privmsgRequest;
}

Server::Server(const Server& tocopy)
{}

Server::~Server()
{}

Server& Server::operator=(const Server& tocopy) {
	if (this == &tocopy)
		return (*this);
	/*
	to do;
	*/
	return (*this);
}

bool	Server::setup(char **init) {
	struct pollfd	new_server;

	hostName = "irc.example.com";
	_sock.sin_family = AF_INET;
	_sock.sin_addr.s_addr = INADDR_ANY;
	_sock.sin_port = htons(atoi(init[1]));
	new_server.events = POLLIN;
	if ((new_server.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ||
		bind(new_server.fd, (struct sockaddr*)&_sock, sizeof(_sock)) != 0 ||
		listen(new_server.fd, 0) < 0)
	{
		std::cout << "Error SetingUp Server" << std::endl;
		return (false);
	}
	_connection.add(new_server);
	_online = true;
	return (_online);
}

void	Server::incomingMessages(void) {
	for (size_t i = 1; i < _connection.size(); ++i)
	{	
		_connection[i].update();
		if (_connection[i].isClosed()) {
			_connection.erase(i--);
			std::cout << "closed" << std::endl;
		}
		else
			_connection[i].makeRequest(*this);
	}
}

void	Server::incomingConnections(void) {
	struct pollfd	new_client;
	char			buffer[READSIZE];
	std::string		info;
	int 			size;

	if (_connection.serverRequest()) {
		new_client.fd = _connection.serverAccept((sockaddr *)&_sock);
		new_client.events = POLLIN;
		_connection.add(new_client);
		std::cout << "Connected: " << new_client.fd << std::endl;
	}
}

void Server::messageToClient(Client& client, std::string message) {
	message = message + "\r\n";

	if (send(client.socket->fd, message.c_str(), message.size(), 0) < 0)
	if (send(client.socket->fd, message.c_str(), message.size(), 0) < 0)
		std::cerr << "Error sending message to the client." << std::endl;
}

// ":" + hostName + " " + message + " " + client.getNickName()
//":sender_nick!user@host PRIVMSG #3 :" + input
std::string Server::format(Client& client) {
	return (":" + client.getNick() + "!" + client.getUser() + "@" + hostName);
}


void	Server::online(void) {

	while (_online)
	{
		poll(_connection.data(), _connection.size(), -1);
		incomingConnections();
		incomingMessages();
	}
}

void	Server::offline(void) {}




// void	Server::printClients(void) {

// 	for (size_t i = 1; i < _sockets.size(); i++)
// 	{
// 		char	buffer[1024] = {0};
// 		if (_sockets[i].revents & POLLIN)
// 		{
// 			if (!recv(_sockets[i].fd, (void *)buffer, 1024, MSG_DONTWAIT))
// 				_sockets.erase(_sockets.begin() + i);
// 			else
// 				printf("Client %lu: %s\n", i, buffer);
// 		}
// 	}
// }


// void	Server::fowardMessage(std::string input, int fd) {
// 	for (size_t i = 1; i < _sockets.size(); ++i)
// 	{
// 		if (_sockets[i].fd == fd)
// 			continue;
// 		std::string	remade(":sender_nick!user@host PRIVMSG #3 :" + input);
// 		send(_sockets[i].fd, remade.c_str(), remade.size(), 0);
// 		std::cout << _sockets[i].fd << std::endl;
// 	}
// }