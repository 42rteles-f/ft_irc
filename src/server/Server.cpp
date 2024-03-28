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
    int         	port;
	struct pollfd	new_server;
    t_protocol  	*tcp;

    port = atoi(init[1]);
    tcp = getprotobyname("tcp");
    _sock.sin_family = AF_INET;
    _sock.sin_addr.s_addr = INADDR_ANY;	
    _sock.sin_port = htons(port);
	if ((new_server.fd = socket(AF_INET, SOCK_STREAM, tcp->p_proto)) < 0 ||
		bind(new_server.fd, (struct sockaddr*)&_sock, sizeof(_sock)) != 0 ||
		listen(new_server.fd, 0) < 0)
	{
		std::cout << "Error SetingUp Server" << std::endl;
	}
	new_server.events = POLLIN;
	_clients.push_back(new_server);
	_online = true;
	return (_online);
}

void	Server::incomingConnections(void) {
	
	struct pollfd		new_client;
	long unsigned int	time_out = sizeof(_sock);

	if (_clients[0].revents & POLLIN) {
		new_client.fd = accept(_clients[0].fd, (sockaddr *)&_sock, (socklen_t*)&time_out);
		new_client.events = POLLIN;
		_clients.push_back(new_client);
	}
}

void	Server::online(void) {

	while (_online)
	{
		poll(_clients.data(), _clients.size(), -1);
		incomingConnections();
		printClients();
	}
}

void	Server::offline(void){

}

void	Server::printClients(void) {

	for (size_t i = 1; i < _clients.size(); i++) {
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
