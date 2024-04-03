/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 22:06:10 by rteles-f         ###   ########.fr       */
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
	_clients[position]._socket = &_sockets[position];
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