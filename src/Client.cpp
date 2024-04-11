/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:37:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/11 19:01:20 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Client.hpp>

Client::Client():
_command(false), _closed(false), socket(NULL)
{}

Client::Client(struct pollfd* socket):
_command(false), _closed(false), socket(socket)
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
	this->_read = tocopy._read;
	this->_input = tocopy._input;
	this->_request = tocopy._request;
	this->_nick = tocopy._nick;
	this->_user = tocopy._user;
	this->_real = tocopy._real;
	this->_command = tocopy._command;
	this->_closed = tocopy._closed;
	this->_myChannels = tocopy._myChannels;
	this->socket = tocopy.socket;
	return (*this);
}

bool	Client::operator==(const Client& compare) {
		return (this->socket->fd == compare.socket->fd ? true : false);
}

bool	Client::operator!=(const Client& compare) {
		return (this->socket->fd != compare.socket->fd ? true : false);
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
	if (!length)
	{
		std::cout << _read << std::endl;
		this->_closed = true;
		this->_read.clear();
		return (false);
	}
	if (_read.find("\n") != _read.npos)
		_command = true;
	return (true);
}

void	Client::makeRequest(Server& server) {
	std::istringstream	iss;
	std::string			command;
	Server::t_exe		handler;
	size_t				breakline;

	if (!_command)
		return ;
	if (_password.empty() && _read.find("PASS") == _read.npos)
		_read = "PASS \n" + _read;
	iss.str(_read);
	while (std::getline(iss, _input) && _read.find("\n") != _read.npos) {
		command = _input.substr(0, _input.find(" "));
		handler = server.requestHandler(command);
		(server.*handler)(*this);
		breakline = _read.find("\n");
		_read = (breakline != _read.npos) ? _read.substr(++breakline) : "";
	}
	_command = false;
	_input.clear();
}

void	Client::setPassword(std::string pass) {
	this->_password = pass;
}

const std::string&	Client::getPassword(void) const {
	return (this->_password);
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

const std::string&	Client::input(void) const{
	return (_input);
}

const std::string&	Client::getUser(void) const {
	return (this->_user);
}

void	Client::setRealName(std::string real) {
	this->_real = real;
}

const std::string&	Client::getRealName(void) const {
	return (this->_real);
}

std::string	Client::makeMessage(void) const {
	return (":" + _nick + "!" + _user + " " + _input + "\r\n");
}

std::string	Client::makeMessage(const std::string message) const {
	return (":" + _nick + "!" + _user + " " + message + "\r\n");
}

void	Client::sendMessage(std::string message) const {
	send(socket->fd, message.c_str(), message.size(), 0);
}

void	Client::addChannel(Channel *channel) {
	_myChannels.push_back(channel);
}

void	Client::removeChannel(Channel *channel) {
	std::vector<Channel*>::iterator find = std::find(_myChannels.begin(), _myChannels.end(), channel);

	if (find != _myChannels.end())
		_myChannels.erase(find);
}

std::vector<Channel*>	Client::getChannels(void)  {
	return (_myChannels);
}

void	Client::endConnection(void) {
	this->_read.clear();
	this->_input.clear();
	this->_command = false;
	close(this->socket->fd);
}
