/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/03/27 20:55:14 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include "Server.hpp"

Server::Server()
{
	commands.default_value = &Server::invalidCommand;
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
	_clients.push_back(new_server);
	_online = true;
	return (_online);
}

void	Server::incomingMessages(void) {
	std::string	input;
	char		buffer[READSIZE];
	int			length;

	for (size_t i = 1; i < _clients.size(); ++i)
	{
		if (!(_clients[i].revents & POLLIN))
			continue;
		input.clear();
		while ((length = recv(_clients[i].fd, (void *)buffer, READSIZE, MSG_DONTWAIT)) > 0)
			input.append(buffer, length);
		if (!length)
			_clients.erase(_clients.begin() + i--);
		else {
			std::cout << input << std::endl;
			if (input.find("JOIN") != input.npos) {
				send(_clients[i].fd, ":Red!RedRubens@client_host JOIN #3\r\n", 36, 0);
				// send(_clients[i].fd, "JOIN #3\r\n", 9, 0);
				// send(_clients[i].fd, "332 username #3 :This is the topic for channel #3\r\n", 51, 0);
				// send(_clients[i].fd, "353 username = #3 :username @username2\r\n", 40, 0);
				// send(_clients[i].fd, "366 username #3 :End of /NAMES list.\r\n", 38, 0);
			}
		}
	}
}
// setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0
// makes the socket reusable for next try;

void	Server::incomingConnections(void) {

	struct pollfd	new_client;
	socklen_t		sock_len = sizeof(_sock);

	if (_clients[0].revents & POLLIN) {
		new_client.fd = accept(_clients[0].fd, (sockaddr *)&_sock, &sock_len);
		new_client.events = POLLIN;
		_clients.push_back(new_client);
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

void	Server::printClients(void) {

	for (size_t i = 1; i < _clients.size(); i++)
	{
		char	buffer[1024] = {0};
		if (_clients[i].revents & POLLIN)
		{
			if (!recv(_clients[i].fd, (void *)buffer, 1024, MSG_DONTWAIT)) {
				std::vector<struct pollfd>::const_iterator	it = _clients.begin();
				std::advance(it, i);
				_clients.erase(it);
			}
			else
				printf("Client %lu: %s\n", i, buffer);
		}
	}
}

void	Server::invalidCommand(std::string command) {
	std::cout << command << ": Not a valid Command in this Server." << std::endl;
}

