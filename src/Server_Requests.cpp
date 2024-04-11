/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Requests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:02:13 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/11 17:31:16 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Server.hpp>

void	Server::privmsgRequest(Client& sender) {
	std::istringstream	iss(sender.input());
	std::string			recipient;
	std::vector<Client*>::iterator	found;

	iss >> recipient;
	iss >> recipient;
	if (_channels.find(recipient) != _channels.end())
		_channels[recipient].broadcast(sender);
	else if ((found = _connection.find(recipient)) != _connection.end()) {
		(*found)->sendMessage(sender.makeMessage());
    }
}

void	Server::nickRequest(Client& client) {
	std::istringstream	iss(client.input());
	std::string			nick;

	iss >> nick;
	iss >> nick;
	// if (_connection.size())
	// 	std::cout << "end: " + _connection.end()->getNick() << std::endl;
	if (_connection.find(nick) == _connection.end()) {
        if (client.getNick().empty()) client.setNick(nick);
        client.sendMessage(client.makeMessage());
		client.setNick(nick);
	}
	else {
        if (client.getNick().empty()) client.setNick(nick);
		client.sendMessage(this->makeMessage(
			"433 " + client.getNick() + " " + nick));
	}
}

void	Server::userRequest(Client& client) {
	std::istringstream	iss(client.input());
	std::string			user;

	iss >> user;
	iss >> user;
	client.setUser(user);
	client.setRealName(client.input().substr(client.input().find(":")));
}

//check if the client who sent the message is a op
//check if the client who will be kicked is in the channel
//
// >> :lliberal_!lliberal KICK #3 lliberal :pqsim
// /KICK #example user123 Spamming is not allowed!
void	Server::kickRequest(Client& client) {
	std::istringstream	iss(client.input());
	std::string			channel;
	std::string			remove;
	std::string			message;

	iss >> channel;
	iss >> channel;
	iss >> remove;
	iss >> message;
	if (_channels.find(channel) != _channels.end() && _channels[channel].isOp(client)) {
		if (!message.empty())
			_channels[channel].broadcast(client.makeMessage("KICK " + channel + " " + remove + " " + message));
		else
			_channels[channel].broadcast(client.makeMessage("KICK " + channel + " " + remove + " :" + client.getNick()));
		_channels[channel].removeClient(remove);
	}
}

void	Server::joinRequest(Client& client) {
	std::string input = client.input();
	std::istringstream iss(input);
	std::string channel;

	std::replace(input.begin(), input.end(), ',', ' ');
	iss >> channel;
	while (iss >> channel) {
		if (channel[0] == '#') {
			_channels[channel](channel).addClient(client);
			// client.sendMessage(client.makeMessage("JOIN :" + channel));
		}
		else {
			//foi o xaleira
			client.sendMessage(client.makeMessage(channel + ": Channel not found"));
		}
	}
	_channels[channel].printOPName();
}

void Server::topicRequest(Client& client) {
	std::string input = client.input();
	std::replace(input.begin(), input.end(), ',', ' ');
	std::istringstream iss(input);
	std::string channel;
	std::string topic;

	iss >> channel;
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
	if (_channels.find(channel) != _channels.end()) {
		_channels[channel].broadcast(client.makeMessage());
		_channels[channel].removeClient(client);
		this->updateChannel(_channels[channel]);
	}
}

void	Server::invalidCommand(Client& client) {
	std::istringstream	iss(client.input());
	std::string			command;

	iss >> command;
	std::cout << command << ": Not a valid Command in this Server." << std::endl;
}

void Server::whoRequest(Client& client) {
	std::istringstream iss(client.input());
	std::string channel;

	iss >> channel; //Ignoring the Command in the input
	iss >> channel;
	if (_channels.find(channel) != _channels.end()) {
		client.sendMessage(this->makeMessage(" 332 " + client.getNick() + " " + channel + " " + _channels[channel].getTopic()));
		std::vector<Client*>::iterator it = _channels[channel].getClients().begin();
		std::string message;
		for (; it != _channels[channel].getClients().end(); it++) {
			if (_channels[channel].isOp(**it))
				message += "@" + (*it)->getNick() + " ";
			else
				message += (*it)->getNick() + " ";
		}
		client.sendMessage(this->makeMessage(" 353 " + client.getNick() + " = " + channel + " :" + message));
	}
	client.sendMessage(this->makeMessage(" 366 " + client.getNick() + " " + channel + " :End of /WHO list."));
}

void	Server::quitRequest(Client& client) {
	std::vector<Channel*>	channels = client.getChannels();
	
	for (size_t i = 0; i < channels.size(); i++)
	{
		channels[i]->broadcast(client.makeMessage());
		channels[i]->removeClient(client);
		this->updateChannel(*channels[i]);
	}
	std::cout << "channells removed" << std::endl;
}

void	Server::modeRequest(Client &client)
{
	std::istringstream	iss(client.input());
	std::string			channel;
	std::string			mode;
	std::string			modeArg;

	iss >> channel;
	iss >> channel;
	iss >> mode;
	iss >> modeArg;
	if (mode[0] != '+' && mode[0] != '-')
		mode = "+" + mode;
	if (_channels.find(channel) != _channels.end() && _channels[channel].isOp(client)) {
		_channels[channel].addMode(client, mode, modeArg);
	}
	else
		client.sendMessage(":" + hostName + " 482 " + client.getNick() + " "
							+ channel + " :You're not channel operator" + "\r\n");
}

void	Server::passRequest(Client& client) {
	std::istringstream iss(client.input());
	std::string pass;

	iss >> pass;
	iss >> pass;
	if (this->password != pass) {
		client.sendMessage(this->makeMessage("464 User :Password incorrect"));
		client.endConnection();
		return ;
	}
	client.setPassword(pass);
}
// :server.example.com 464 <nickname> :Password incorrect