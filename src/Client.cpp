/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:37:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/07 20:58:24 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Client.hpp>

Client::Client():
_socket(NULL), _input(""), _command(false), _closed(false), _nick(""), _user(""), _real("")
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
	return (this->_closed);
}

bool	Client::hasRequest(void) {
	return (this->_command);
}

bool	Client::update(void) {
	char		buffer[READSIZE];
	int			length;

	if (!(_socket->revents & POLLIN))
		return (false);
	while ((length = recv(_socket->fd, (void *)buffer, READSIZE, MSG_DONTWAIT)) > 0)
		this->_input.append(buffer, length);
	std::cout << _input << std::endl;
	if (!length) {
		this->_closed = true;
		this->_input.clear();
		return (false);
	}
	if (_input.find("\n") != _input.npos)
		_command = true;
	return (true);
}

std::string	Client::input(void) {
	return (_input);
}

std::string	Client::getInput(void) {
	std::cout << _input << std::endl;
	return _input;
}

std::string Client::getNick() {
	return _nick;
}

std::string Client::getRequest() {
	return _request;
}

std::string Client::getUser() {
	return _user;
}

void	Client::makeRequest(Server& server) {
	std::istringstream	iss;
	std::string			command;
	Server::t_exe		handler;

	if (!_command)
		return ;
	iss.str(_input);
	iss >> command;
	handler = server.requestHandler(command);
	(server.*handler)(*this);
	_command = false;
	_input.clear();
}
	// (server.*server.requestHandler(command))(*this);
