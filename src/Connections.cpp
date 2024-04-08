/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/08 19:20:28 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Connections.hpp>

Connections::Connections()
{}

Connections::Connections(const Connections& tocopy)
{
	*this = tocopy;
}

Connections::~Connections()
{}

Connections& Connections::operator=(const Connections& tocopy) {
	if (this == &tocopy)
		return (*this);
	this->_clients = tocopy._clients;
	this->_sockets = tocopy._sockets;
	return (*this);
}

void	Connections::add(struct pollfd& socket) {
	if (socket.fd < 0) {
		return ;
	}
	_sockets.push_back(socket);
	_clients.push_back(Client());
}

void	Connections::erase(size_t position) {
	close(_sockets[position].fd);
	_sockets.erase(_sockets.begin() + position);
	_clients.erase(_clients.begin() + position);
}

struct pollfd	*Connections::data(void) {
	return (_sockets.data());
}

size_t	Connections::size(void) {
	return (_sockets.size());
}

Client& Connections::operator[](size_t position) {
	_clients[position].socket = &_sockets[position];
	return (_clients[position]);
}

bool	Connections::serverRequest(void) {
	return (_sockets[0].revents & POLLIN ? true : false);
}

int		Connections::serverAccept(sockaddr *sock)
{
	socklen_t	sock_len = sizeof(sockaddr_in);

	return (accept(_sockets[0].fd, sock, &sock_len));
}

std::vector<Client>::iterator	Connections::find(std::string nick) {
	std::vector<Client>::iterator	find = _clients.begin();

	while (find != _clients.end() && find->getNick() != nick)
		find++;
	return (find);
}

std::vector<Client>::iterator	Connections::end(void) {
	return (_clients.end());
}

// void	Connections::send(std::string message) {

// }
