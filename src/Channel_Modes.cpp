/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_Modes.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/13 14:18:44 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Channel.hpp>

void Channel::addMode(Client &client, std::string mode, std::string argument)
{
	std::map<char, t_exe>::const_iterator	found = _functions.find(mode[1]);
	if (found != _functions.end() && mode.size() == 2)
		(this->*(found->second))(client, mode, argument);
}

void Channel::operatorMode(Client &client, std::string mode, std::string argument)
{
	if (argument.empty())
		return ;
	Client *argClient = this->findClient(argument);
	if (mode[0] == '+' && argClient && !this->isOp(*argClient))
	{
		broadcast(client.makeMessage(("MODE " + _name + " " + mode + " " + argument)));
		addOp(*argClient);
	}
	else if (mode[0] == '-' && argClient && this->isOp(*argClient) && _op.size() > 1)
	{
		broadcast(client.makeMessage(("MODE " + _name + " " + mode + " " + argument)));
		removeOp(*argClient);
	}
}

std::string	Channel::getMode(char mode) {
	return _modes[(int)mode];
}

void Channel::addOp(Client &client) {
	if (this->isOp(client))
		return;
	this->_op.push_back(&client);
}

void Channel::removeOp(Client& client) {
	std::vector<Client*>::iterator find;

	find = std::find(_op.begin(), _op.end(), &client);
	if (find != _op.end())
		_op.erase(find);
	
	if (_clients.size() && _op.size() == 0)
		_op.push_back(_clients[0]);
}

bool Channel::isOp(Client& client) {
	std::vector<Client*>::iterator find;

	find = std::find(_op.begin(), _op.end(), &client);
	if (find != _op.end())
		return true;
	return false;
}

bool Channel::isOp(std::string clientName) {
	std::vector<Client*>::iterator find;

	find = _op.begin();
	for (;find != _op.end(); ++find) {
		if (clientName.compare((*find)->getNick()) == 0)
			return true;
	}
	return false;
}

void	Channel::setTopic(std::string topic) {
	this->_topic = topic;
}

std::string	Channel::getTopic(void) {
	return (this->_topic);
}

void Channel::inviteAndTopicMode(Client &client, std::string mode, std::string argument)
{
	(void)argument;
	if (mode[0] == '+' && _modes[(int)mode[1]].empty())
	{
		_modes[(int)mode[1]] = "yes";
		broadcast(client.makeMessage(("MODE " + _name + " " + mode)));
	}
	else if (mode[0] == '-' && !_modes[(int)mode[1]].empty())
	{
		_modes[(int)mode[1]].clear();
		broadcast(client.makeMessage(("MODE " + _name + " " + mode)));
	}
}

void Channel::keyAndLimitMode(Client &client, std::string mode, std::string argument)
{
	if (mode[0] == '+')
	{
		if (argument.empty())
			return ;
		_modes[(int)mode[1]] = argument;
		broadcast(client.makeMessage(("MODE " + _name + " " + mode + " " + argument)));
	}
	else if (mode[0] == '-' && !_modes[(int)mode[1]].empty())
	{
		_modes[(int)mode[1]].clear();
		broadcast(client.makeMessage(("MODE " + _name + " " + mode + " " + argument)));
	}
}
