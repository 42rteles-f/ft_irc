/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/11 19:01:39 by rteles-f         ###   ########.fr       */
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
{
	for (std::vector<Client*>::iterator	find = _clients.begin();
				find != _clients.end(); find++)
		delete (*find);
}

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
	_clients.push_back(new Client);
}

void	Connections::erase(size_t position) {
	close(_sockets[position].fd);
	delete (_clients[position]);
	_clients.erase(_clients.begin() + position);
	_sockets.erase(_sockets.begin() + position);
}

void	Connections::erase(Client& erase) {
	size_t	position = 0;

	while (position < _clients.size() && operator[](position) != erase)
		position++;
	if (position >= _clients.size())
		return ;
	close(erase.socket->fd);
	delete (_clients[position]);
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
	_clients[position]->socket = &_sockets[position];
	return (*_clients[position]);
}

bool	Connections::serverRequest(void) {
	return (_sockets[0].revents & POLLIN ? true : false);
}

int		Connections::serverAccept(sockaddr *sock)
{
	socklen_t	sock_len = sizeof(sockaddr_in);

	return (accept(_sockets[0].fd, sock, &sock_len));
}

std::vector<Client*>::iterator	Connections::find(std::string nick) {
	std::vector<Client*>::iterator	find = _clients.begin();

	while (find != _clients.end() && (*find)->getNick() != nick)
		find++;
	return (find);
}

std::vector<Client*>::iterator	Connections::end(void) {
	return (_clients.end());
}
