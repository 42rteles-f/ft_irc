/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/20 16:39:26 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	setup(char **init) {
    int         port;

    if (ac != 2)
        return (write(2, "Usage: ./program <port number>\n", 32));

	FD_ZERO(&request_set);
    port = atoi(args[1]);
    tcp = getprotobyname("tcp");
    _sock.sin_family = AF_INET;
    _sock.sin_addr.s_addr = INADDR_ANY;	
    _sock.sin_port = htons(port);
	if ((server_fd = socket(AF_INET, SOCK_STREAM, tcp->p_proto)) < 0 ||
		bind(server_fd, (struct sockaddr*)&_sock, sizeof(_sock)) != 0 ||
		listen(server_fd, 0) < 0)
	{
		std::cout << "Error SetingUp Server" << std::endl;
	}
	FD_SET(_sock, &request_set);
	_online = true;
}

void	Server::incomingConnections(void) {
	
	struct timeval time;
	int	value, connection, size;

	bzero(time, sizeof(struct timeval));
	do {
		value = select(server_socket, &request_set, NULL, NULL, &time);
		if (value < 0)
			std::cout << "Error" << std::endl;
		else if (value) {
			size = sizeof(struct sockaddr_in);
			connection = accept(server_socket, (sockaddr *)&sock, (socklen_t *)&size);
		}
			
	}
	while (value)
}

std::list<Client>	Server::getChannel(int channel) {
	
	return ()
}

void	Server::online(void) {

	while (_online)
	{
		this->incomingConnections();
		connections.update();
	}
}

void	Server::offline(void){

}

void	changeChannel() {

}

void	Server::updateChannels(void) {
	std::map<std::string, std::list<Channel>>::iterator	it;

	for (it = _channels.begin(); it != _channels.end(); it++) {
		channel.update();
	}
}