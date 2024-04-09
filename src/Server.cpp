/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/09 20:28:38 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Server.hpp>

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
}

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

Server::t_exe	Server::requestHandler(std::string target)
{
	std::map<std::string, t_exe>::const_iterator	found = _functions.find(target);
	std::cout << target << std::endl;
	if (found != _functions.end())
		return (found->second);
	return (&Server::invalidCommand);
}

bool	Server::setup(char **init) {
	struct pollfd	new_server;

	hostName = "irc.example.com";
	_sock.sin_family = AF_INET;
	_sock.sin_addr.s_addr = INADDR_ANY;
	_sock.sin_port = htons(atoi(init[1]));
	new_server.events = POLLIN;
	if ((new_server.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ||
		bind(new_server.fd, (struct sockaddr*)&_sock, sizeof(_sock)) != 0 ||
		listen(new_server.fd, 0) < 0)
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
	char			buffer[READSIZE];
	std::string		info;
	int 			size;

	if (_connection.serverRequest()) {
		new_client.fd = _connection.serverAccept((sockaddr *)&_sock);
		new_client.events = POLLIN;
		_connection.add(new_client);
		std::cout << "Connected: " << new_client.fd << std::endl;
	}
}

void Server::messageToClient(Client& client, std::string message) {
	message = message + "\r\n";

	if (send(client.socket->fd, message.c_str(), message.size(), 0) < 0)
	if (send(client.socket->fd, message.c_str(), message.size(), 0) < 0)
		std::cerr << "Error sending message to the client." << std::endl;
}

// ":" + hostName + " " + message + " " + client.getNickName()
//":sender_nick!user@host PRIVMSG #3 :" + input
std::string Server::format(Client& client) {
	return (":" + client.getNick() + "!" + client.getUser() + "@" + hostName);
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
		_connection[i].sendMessage(this->makeMessage("Server Closing Down."));
		close(_connection[i].socket->fd);
	}
	close(_connection[0].socket->fd);
	setsockopt(_connection[0].socket->fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
}

std::string	Server::makeMessage(const std::string message) const {
	return (":" + hostName + " " + message + "\r\n");
}

std::string	Server::makeMessage(std::string code, std::string message) const {
	return (":" + hostName + " " + message + "\r\n");
}

std::string	Server::makeMessage(std::string code, std::string client, std::string message) const {
	return (":" + hostName + " " + code + " " + client + " " + message + "\r\n");
}
