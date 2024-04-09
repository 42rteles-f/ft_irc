/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Requests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:02:13 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/09 10:04:35 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Server.hpp>

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
		client.sendMessage(client.makeMessage());
		client.setNick(nick);
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