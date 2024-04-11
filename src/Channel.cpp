/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/11 19:45:04 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Channel.hpp>

Channel::Channel() : _topic(""), _op()
{
	_functions['o'] = &Channel::operatorMode;
	_functions['i'] = &Channel::inviteAndTopicMode;
	_functions['t'] = &Channel::inviteAndTopicMode;
	// _functions['k'] = &Channel::keyMode;
	// _functions['l'] = &Channel::limitMode;
}

Channel::Channel(const Channel& tocopy)
{
	*this = tocopy;
}

Channel::~Channel()
{}

Channel& Channel::operator()(const std::string name) {
	_name = name;
	return(*this);
}

const std::string& Channel::name(void) {
	return (_name);
}

Channel& Channel::operator=(const Channel& tocopy) {
	if (this == &tocopy)
		return (*this);
	this->_topic = tocopy._topic;
	this->_clients = tocopy._clients;
	this->_op = tocopy._op;
	return (*this);
}

void	Channel::addClient(Client& add) {
	std::vector<Client*>::iterator find;

	find = std::find(_clients.begin(), _clients.end(), &add);
	if (find == _clients.end())
		_clients.push_back(&add);
	if (_op.size() == 0)
		_op.push_back(&add);
	this->broadcast(add.makeMessage());
	add.addChannel(this);
}

//Remove doenst broadcast the client leaving due to the kick message being custom.
void	Channel::removeClient(Client& remove) {
	std::vector<Client*>::iterator find;

	find = std::find(_op.begin(), _op.end(), &remove);
	if (find != _op.end())
		_op.erase(find);

	find = std::find(_clients.begin(), _clients.end(), &remove);
	if (find != _clients.end())
		_clients.erase(find);

	if (_clients.size() && _op.size() == 0)
		_op.push_back(_clients[0]);
	remove.removeChannel(this);
}

void Channel::removeClient(std::string clientName) {
	std::vector<Client*>::iterator find = _clients.begin();

	while (find != _clients.end() && clientName.compare((*find)->getNick()))
		find++;
	if (find != _clients.end())
		this->removeClient(**find);
}

size_t Channel::NumberOfClients() {
	return _clients.size();
}

void	Channel::printOPName() {
	std::vector<Client*>::iterator it = _op.begin();
	for (; it != _op.end(); it++) {
		std::cout << (*it)->getNick() << std::endl;
	}
}

void Channel::addOp(Client &client) {
	if (this->isOp(client))
		return;
	this->_op.push_back(&client);
}

void	Channel::broadcast(Client& sender)
{
	std::string	message = sender.makeMessage();

	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (sender.socket->fd != _clients[i]->socket->fd)
			send(_clients[i]->socket->fd, message.c_str(), message.size(), 0);
	}
}

void	Channel::broadcast(std::string message)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		send(_clients[i]->socket->fd, message.c_str(), message.size(), 0);
	}
}

void	Channel::setTopic(std::string topic) {
	this->_topic = topic;
}

std::string	Channel::getTopic(void) {
	return (this->_topic);
}

bool Channel::isOp(Client& client) {
	std::vector<Client*>::iterator find;

	find = std::find(_op.begin(), _op.end(), &client);
	if (find != _op.end())
		return true;
	return false;
}

void Channel::removeOp(Client& client) {
	std::vector<Client*>::iterator find;

	find = std::find(_op.begin(), _op.end(), &client);
	if (find != _op.end())
		_op.erase(find);
	
	if (_clients.size() && _op.size() == 0)
		_op.push_back(_clients[0]);
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

Client& Channel::getClient(size_t index){
	return (*(_clients[index]));
}

std::vector<Client*>& Channel::getClients() {
	return (_clients);
}

Client* Channel::findClient(std::string clientName) {
	std::vector<Client*>::iterator find;

	find = _clients.begin();
	for (;find != _clients.end(); ++find) {
		if (clientName.compare((*find)->getNick()) == 0)
			return (*find);
	}
	return (NULL);
}

void Channel::addMode(Client &client, std::string mode, std::string argument)
{
	std::map<char, t_exe>::const_iterator	found = _functions.find(mode[1]);
	if (found != _functions.end())
		(this->*(found->second))(client, mode, argument);
	else
		invalidMode();
}

void	Channel::invalidMode(void) {
	std::cout << "Invalid mode" << std::endl;
}

void Channel::operatorMode(Client &client, std::string mode, std::string argument)
{
	if (argument.empty())
		return ;
	Client *argClient = this->findClient(argument);
	if (mode[0] == '+' && argClient && !this->isOp(*argClient))
	{
		addOp(*argClient);
		broadcast(client.makeMessage(("MODE " + _name + " " + mode + " " + argument)));
	}
	else if (argClient && this->isOp(*argClient))
	{
		removeOp(*argClient);
		broadcast(client.makeMessage(("MODE " + _name + " " + mode + " " + argument)));
	}
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


bool Channel::isClientInChannel(Client* guest) {
	std::vector<Client *>::iterator it = std::find(_clients.begin(), _clients.end(), guest);

	if (it != _clients.end())
		return true;
	return false;
}

	// if (mode.find('o') != std::string::npos)
	// {
	// 	Client *client = this->findClient(argument);
	// 	if (client)
	// 	{
	// 		if (mode[0] == '+')
	// 			this->addOp(*client);
	// 		else
	// 			this->removeOp(*client);
	// 	}
	// }
	// if (mode[0] == '+')
	// {
	// 	if (mode[1] == 'i' || mode[1] == 't')
	// 		argument = "yes";
	// 	if (argument.empty())
	// 	{
	// 		client.sendMessage("irc.example.com 461 " + client.getNick() + " MODE " + mode + " :Not enough parameters");
	// 		return ;
	// 	}
	// 	_modes[mode[1]] = argument; 
	// }
	// else
	// {
	// 	if (_modes[mode[1]].empty())
	// 		return ;
	// 	_modes[mode[1]].clear();
	// }
	// broadcast(client.makeMessage(("MODE " + _name + " " + mode + " " + argument)));