/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/13 15:54:37 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Server.hpp>

std::string	Server::hostName = "irc.example.com";

Server::Server():
_online(false)
{
	_functions["QUIT"] = &Server::quitRequest;
	_functions["JOIN"] = &Server::joinRequest;
	_functions["PART"] = &Server::partRequest;
	_functions["NICK"] = &Server::nickRequest;
	_functions["USER"] = &Server::userRequest;
	_functions["KICK"] = &Server::kickRequest;
	_functions["PRIVMSG"] = &Server::privmsgRequest;
	_functions["privmsg"] = &Server::privmsgRequest;
	_functions["WHO"] = &Server::whoRequest;
	_functions["TOPIC"] = &Server::topicRequest;
	_functions["PASS"] = &Server::passRequest;
	_functions["MODE"] = &Server::modeRequest;
	_functions["INVITE"] = &Server::inviteRequest;

}

Server::~Server()
{}

Server& Server::operator=(const Server& tocopy) {
	if (this == &tocopy)
		return (*this);
	this->_online = tocopy._online;
	this->_sock = tocopy._sock;
	this->password = tocopy.password;
	this->_connection = tocopy._connection;
	this->_channels = tocopy._channels;
	this->_functions = tocopy._functions;
	return (*this);
}

Server::t_exe	Server::requestHandler(std::string target)
{
	std::map<std::string, t_exe>::const_iterator	found = _functions.find(target);
	if (found != _functions.end())
		return (found->second);
	return (&Server::invalidCommand);
}

bool	Server::setup(char **init) {
	struct pollfd	new_server;
	const char		*defaultPort = "6667";

	if (!*(init[1])) init[1] = (char *)defaultPort;
	this->password = init[2];
	_sock.sin_family = AF_INET;
	_sock.sin_addr.s_addr = INADDR_ANY;
	_sock.sin_port = htons(atoi(init[1]));
	new_server.events = POLLIN;
	if ((new_server.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0
	||	bind(new_server.fd, (struct sockaddr*)&_sock, sizeof(_sock)) != 0
	||	listen(new_server.fd, 0) < 0)
	{
		setsockopt(new_server.fd, SOL_SOCKET, SO_REUSEADDR, &new_server.events, sizeof(new_server.events));
		std::cout << "Error SetingUp Server" << std::endl;
		return (false);
	}
	_connection.add(new_server);
	_online = true;
	return (_online);
}

void	Server::incomingMessages(void) {
	for (size_t i = 1; i < _connection.size(); ++i)
	{	
		_connection[i].update();
		if (_connection[i].isClosed()) {
			_connection.erase(i--);
			std::cout << "closed" << std::endl;
		}
		else
			_connection[i].makeRequest(*this);
	}
}

void	Server::incomingConnections(void) {
	struct pollfd	new_client;
	std::string		info;

	if (_connection.serverRequest()) {
		new_client.fd = _connection.serverAccept((sockaddr *)&_sock);
		new_client.events = POLLIN;
		new_client.revents = 0;
		_connection.add(new_client);
		std::cout << "Connected: " << new_client.fd << std::endl;
	}
}

void	Server::online(void) {

	while (_online)
	{
		poll(_connection.data(), _connection.size(), -1);
		incomingConnections();
		incomingMessages();
	}
}

void	Server::offline(void) {
	int reuse = 1;

	this->_online = false;
	for (size_t i = 1; i < _connection.size(); i++) {
		_connection[i].sendMessage(this->makeMessage("421", this->hostName, ":Server Closing Down."));
		close(_connection[i].socket->fd);
	}
	close(_connection[0].socket->fd);
	setsockopt(_connection[0].socket->fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
}

std::string	Server::makeMessage(const std::string message) {
	return (":" + hostName + " " + message + "\r\n");
}

std::string	Server::makeMessage(std::string code, std::string message) {
	return (":" + hostName + " " + code + " " + message + "\r\n");
}

std::string	Server::makeMessage(std::string code, std::string client, std::string message) {
	return (":" + hostName + " " + code + " " + client + " " + message + "\r\n");
}

void Server::updateChannel(Channel &channel)
{
	std::vector<Client*> annouce = channel.getClients();

	for (size_t j = 0; j < annouce.size(); j++) {

	annouce[j]->sendMessage(this->makeMessage(" 332 " + annouce[j]->getNick() + " " + channel.name() + " " + channel.getTopic()));
	std::vector<Client*>::iterator it = channel.getClients().begin();
	std::string message;
	for (; it != channel.getClients().end(); it++) {
		if (channel.isOp(**it))
			message += "@" + (*it)->getNick() + " ";
		else
			message += (*it)->getNick() + " ";
	}
	annouce[j]->sendMessage(this->makeMessage(" 353 " + annouce[j]->getNick() + " = " + channel.name() + " :" + message));
	annouce[j]->sendMessage(this->makeMessage(" 366 " + annouce[j]->getNick() + " " + channel.name() + " :End of /WHO list."));
	}
}
