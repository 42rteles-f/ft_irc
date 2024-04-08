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
socket(NULL), _input(""), _command(false), _closed(false)
{}

Client::Client(struct pollfd* socket):
socket(socket), _input(""), _command(false), _closed(false)
{}

Client::Client(const Client& tocopy):
socket(tocopy.socket)
{
	*this = tocopy;
}

Client::~Client() {}

Client& Client::operator=(const Client& tocopy) {
	if (this == &tocopy)
		return (*this);
	this->socket = tocopy.socket;
	this->_input = tocopy._input;
	this->_command = tocopy._command;
	this->_closed = tocopy._closed;
	return (*this);
}

bool	Client::operator==(const Client& compare) {
		return (this->socket->fd == compare.socket->fd ? true : false);
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

	if (!(socket->revents & POLLIN))
		return (false);
	while ((length = recv(socket->fd, (void *)buffer, READSIZE, MSG_DONTWAIT)) > 0)
		this->_read.append(buffer, length);
	if (!length) {
		this->_closed = true;
		this->_read.clear();
		return (false);
	}
	std::cout << _read << std::endl;
	if (_read.find("\n") != _read.npos)
		_command = true;
	return (true);
}

const std::string&	Client::input(void) const {
	return (_input);
}

void	Client::makeRequest(Server& server) {
	std::istringstream	iss;
	std::string			command;
	Server::t_exe		handler;

	if (!_command)
		return ;
	iss.str(_read);
	while (std::getline(iss, _input)) {
		command = _input.substr(0, _input.find(" "));
		handler = server.requestHandler(command);
		(server.*handler)(*this);
	}
	_command = false;
	_input.clear();
	_read.clear();
	std::cout << _nick << " | " << _user << std::endl;
}

void	Client::setNick(std::string nick) {
	this->_nick = nick;
}

const std::string&	Client::getNick(void) const {
	return (this->_nick);
}

void	Client::setUser(std::string user) {
	this->_user = user;
}

const std::string&	Client::getUser(void) const {
	return (this->_user);
}