/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/08 21:43:22 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
# include "Client.hpp"
# include "Channel.hpp"
# include "Connections.hpp"
#include <Server.hpp>

Server::Server():
_online(false)
{
	// _functions["CAP"] = ;
	_functions["NICK"] = &Server::nickRequest;
	_functions["USER"] = &Server::userRequest;
	_functions["KICK"] = &Server::kickRequest;
	_functions["PRIVMSG"] = &Server::privmsgRequest;
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
		else {
			// sendAN-A795207B.226.108.93.rev.vodafone.pt(_connection[i]._socket.fd, "")
			_connection[i].makeRequest(*this);
	}
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

void	Server::joinRequest(Client& client) {
	std::string input = client.input();
	std::replace(input.begin(), input.end(), ',', ' ');
	std::istringstream iss(input);
	std::string channel;

	iss >> channel; //Ignoring the Command in the input
	while (iss >> channel) {
		_channels[channel];
		messageToClient(client, ":" + client.getNick() + " JOIN :" + channel);
	}
	messageToClient(client, ":" + client.getNick() + " JOIN :" + channel);
	if (_channels[channel].NumberOfClients() == 1)
		_channels[channel].changeOp(client);
	_channels[channel].printOPName();
}

void	Server::online(void) {

	while (_online)
	{
		poll(_connection.data(), _connection.size(), -1);
		incomingConnections();
		incomingMessages();
	}
}

void	Server::offline(void) {}

Server::t_exe	Server::requestHandler(std::string target)
{
	std::map<std::string, t_exe>::const_iterator	found = _functions.find(target);
	std::cout << target << std::endl;
	if (found != _functions.end())
		return (found->second);
	return (&Server::invalidCommand);
}

void	Server::invalidCommand(Client& client) {
	std::istringstream	iss(client.input());
	std::string			command;

	iss >> command;
	std::cout << command << ": Not a valid Command in this Server." << std::endl;
}

// std::string	Server::formatRequest(std::string input) {

// }

void	Server::privmsgRequest(Client& sender) {
	std::istringstream	iss(sender.input());
	std::string			recipient;
	std::vector<Client>::iterator	found;

	std::cout << sender.input() << std::endl;
	std::cout << sender.makeMessage() << std::endl;
	iss >> recipient;
	iss >> recipient;
	if (_channels.find(recipient) != _channels.end()) {
		_channels[recipient].broadcast(sender);
		std::cout << "found channel" << std::endl;
	}
	else if ((found = _connection.find(recipient)) != _connection.end()) {
		(*found).sendMessage(sender.makeMessage());
	}
}

void	Server::nickRequest(Client& client) {
	std::istringstream	iss(client.input());
	std::string			nick;

	iss >> nick;
	iss >> nick;
	if (_connection.find(nick) == _connection.end()) {
		client.setNick(nick);
		client.sendMessage(client.makeMessage());
	}
	// else
	// 	client.send(this->makeMessage("Not a valid nick"));
}

void	Server::userRequest(Client& client) {
	std::istringstream	iss(client.input());
	std::string			nick;

	iss >> nick;
	iss >> nick;
	client.setUser(nick);
}

// /KICK #example user123 Spamming is not allowed!
void	Server::kickRequest(Client& client) {
	// client.input().;
}


// void	Server::printClients(void) {

// 	for (size_t i = 1; i < _sockets.size(); i++)
// 	{
// 		char	buffer[1024] = {0};
// 		if (_sockets[i].revents & POLLIN)
// 		{
// 			if (!recv(_sockets[i].fd, (void *)buffer, 1024, MSG_DONTWAIT))
// 				_sockets.erase(_sockets.begin() + i);
// 			else
// 				printf("Client %lu: %s\n", i, buffer);
// 		}
// 	}
// }


// void	Server::fowardMessage(std::string input, int fd) {
// 	for (size_t i = 1; i < _sockets.size(); ++i)
// 	{
// 		if (_sockets[i].fd == fd)
// 			continue;
// 		std::string	remade(":sender_nick!user@host PRIVMSG #3 :" + input);
// 		send(_sockets[i].fd, remade.c_str(), remade.size(), 0);
// 		std::cout << _sockets[i].fd << std::endl;
// 	}
// }