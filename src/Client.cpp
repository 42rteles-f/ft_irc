/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:37:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 22:35:48 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Client.hpp>

Client::Client():
_socket(NULL), _input(""), _command(false), _closed(false)
{}

Client::Client(struct pollfd* socket):
_socket(socket), _input(""), _command(false), _closed(false)
{}

Client::Client(const Client& tocopy):
_socket(tocopy._socket)
{
	*this = tocopy;
}

Client::~Client() {}

Client& Client::operator=(const Client& tocopy) {
	if (this == &tocopy)
		return (*this);
	this->_socket = tocopy._socket;
	this->_input = tocopy._input;
	this->_command = tocopy._command;
	this->_closed = tocopy._closed;
	return (*this);
}

bool	Client::isClosed(void) {
	return (this->_closed ? true : false);
}

bool	Client::update(void) {
	char		buffer[READSIZE];
	int			length;

	if (!(_socket->revents & POLLIN))
		return (false);
	while ((length = recv(_socket->fd, (void *)buffer, READSIZE, MSG_DONTWAIT)) > 0)
		this->_input.append(buffer, length);
	if (!length) {
		this->_closed = true;
		this->_input.clear();
		return (false);
	}
	if (_input.find("\n") != _input.npos)
		_command = true;
	return (true);
}

void	Client::makeRequest(void) {
	std::stringstream	ss(_input);
	std::string			command;

	if (!_command)
		return ;
	ss >> command;
	// Server::t_exe	execute = Server::requests.find(command);
	// if (execute != Server::requests.end())
	// 	(*execute)(*this);
	_command = false;
	_input.clear();
}
