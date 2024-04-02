/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 00:42:37 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include "Server.hpp"

Server::Server():
_online(false)
{}

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
	_clients.add(new_server);
	_online = true;
	return (_online);
}

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

void	Server::incomingMessages(void)
{
	char		buffer[READSIZE];
	int			length;

	for (size_t i = 1; i < _clients.size(); ++i)
	{
		if (!(_clients[i].revents & POLLIN))
			continue;
		while ((length = recv(_clients[i].fd, (void *)buffer, READSIZE, MSG_DONTWAIT)) > 0)
			_clients[i].addInput(buffer, length);
		if (!length)
			_clients.erase(i--);
		// else if (_clients[i].hasCommand())
		// 	this->executeClient(_clients[i]);
	}
}

void	Server::incomingConnections(void) {

	struct pollfd	new_socket;
	socklen_t		sock_len = sizeof(_sock);

	if (_clients[0].revents & POLLIN) {
		new_socket.fd = accept(_clients[0].fd, (sockaddr *)&_sock, &sock_len);
		new_socket.events = POLLIN;
		_clients->add(new_socket);
		std::cout << "Connect" << std::endl;
	}
}

void	Server::online(void) {

	while (_online)
	{
		poll(_clients.data(), _clients.size(), -1);
		incomingConnections();
		incomingMessages();
	}
}

void	Server::offline(void){

}

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

void	Server::invalidCommand(std::string command) {
	std::cout << command << ": Not a valid Command in this Server." << std::endl;
}



void	Server::executeClient(Client& client) {
}

// setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0
// makes the socket reusable for next try;