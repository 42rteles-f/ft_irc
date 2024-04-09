/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Requests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:02:13 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/09 16:22:45 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Server.hpp>

void	Server::privmsgRequest(Client& sender) {
	std::istringstream	iss(sender.input());
	std::string			recipient;
	std::vector<Client>::iterator	found;

	iss >> recipient;
	iss >> recipient;
	if (_channels.find(recipient) != _channels.end())
		_channels[recipient].broadcast(sender);
	else if ((found = _connection.find(recipient)) != _connection.end()) {
		found->sendMessage(sender.makeMessage());
    }
}

void	Server::nickRequest(Client& client) {
	std::istringstream	iss(client.input());
	std::string			nick;

	iss >> nick;
	iss >> nick;
	if (_connection.find(nick) == _connection.end()) {
        if (client.getNick().empty()) client.setNick(nick);
        client.sendMessage(client.makeMessage());
        client.setNick(nick);
	}
	else {
		client.sendMessage(this->makeMessage("433 " + client.getNick() + " " + nick));
		client.sendMessage(":" + hostName + " 433 " + client.getNick() + " " + nick);
	}
}

void	Server::userRequest(Client& client) {
	std::istringstream	iss(client.input());
	std::string			user;

	iss >> user;
	iss >> user;
	client.setUser(user);
}

// /KICK #example user123 Spamming is not allowed!
void	Server::kickRequest(Client& client) {
	// client.input().;
}

void	Server::joinRequest(Client& client) {
	std::string input = client.input();
	std::istringstream iss(input);
	std::string channel;

	std::replace(input.begin(), input.end(), ',', ' ');
	iss >> channel; //Ignoring the Command in the input
	while (iss >> channel) {
		_channels[channel].addClient(client);
		messageToClient(client, ":" + client.getNick() + " JOIN :" + channel);
	}
	// messageToClient(client, ":" + client.getNick() + " JOIN :" + channel);
	if (_channels[channel].NumberOfClients() == 1)
		_channels[channel].changeOp(client);
	_channels[channel].printOPName();
}

void Server::topicRequest(Client& client) {
	std::string input = client.input();
	std::replace(input.begin(), input.end(), ',', ' ');
	std::istringstream iss(input);
	std::string channel;
	std::string topic;

	iss >> channel; //Ignoring the Command in the input
	iss >> channel;
	iss >> topic;
	if (_channels.find(channel) != _channels.end() && _channels[channel].isOp(client)) {
		_channels[channel].setTopic(topic);
		_channels[channel].broadcast(client.makeMessage());
	}
	else
		client.sendMessage(":" + hostName + " 482 " + client.getNick() + " "
							+ channel + " :You're not channel operator" + "\r\n");
}

void	Server::partRequest(Client& client) {
	std::istringstream	iss(client.input());
	std::string			channel;

	iss >> channel;
	iss >> channel;
	if (_channels.find(channel) != _channels.end())
		_channels[channel].removeClient(client);
}

void	Server::invalidCommand(Client& client) {
	std::istringstream	iss(client.input());
	std::string			command;

	iss >> command;
	std::cout << command << ": Not a valid Command in this Server." << std::endl;
}

void Server::whoRequest(Client& client) {
	std::string input = client.input();
	std::replace(input.begin(), input.end(), ',', ' ');
	std::istringstream iss(input);
	std::string channel;

	iss >> channel; //Ignoring the Command in the input
	iss >> channel;
	if (_channels.find(channel) != _channels.end()) {
		_channels[channel].broadcast(client.makeMessage());
	}
}
