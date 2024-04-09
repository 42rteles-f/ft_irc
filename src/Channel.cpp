/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/09 20:02:19 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Channel.hpp>

Channel::Channel() : _op(), _topic("")
{}

Channel::Channel(const Channel& tocopy)
{
	*this = tocopy;
}

Channel::~Channel()
{}

Channel& Channel::operator=(const Channel& tocopy) {
	if (this == &tocopy)
		return (*this);
	/*
	to do;
	*/
	return (*this);
}

void	Channel::addClient(Client& add) {
	std::vector<Client>::iterator find;

	find = std::find(_clients.begin(), _clients.end(), add);
	if (find == _clients.end())
		_clients.push_back(add);
	if (_op.size() == 0)
		_op.push_back(add);
	// add.addChannel(this.);
}

void	Channel::removeClient(Client& remove) {
	std::vector<Client>::iterator find;

	find = std::find(_op.begin(), _op.end(), remove);
	if (find != _op.end())
		_op.erase(find);
	find = std::find(_clients.begin(), _clients.end(), remove);
	if (find != _clients.end())
		_clients.erase(find);
	if (_clients.size() && _op.size() == 0)
		_op.push_back(_clients[0]);
}

size_t Channel::NumberOfClients() {
	return _clients.size();
}

void	Channel::printOPName() {
	std::vector<Client>::iterator it = _op.begin();
	for (; it != _op.end(); it++) {
		std::cout << it->getNick() << std::endl;
	}
}

void Channel::changeOp(Client &client) {
	this->_op.push_back(client);
}

void	Channel::broadcast(Client& sender)
{
	std::string	message = sender.makeMessage();

	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (sender.socket->fd != _clients[i].socket->fd)
			send(_clients[i].socket->fd, message.c_str(), message.size(), 0);
	}
}

void	Channel::broadcast(std::string message)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		send(_clients[i].socket->fd, message.c_str(), message.size(), 0);
	}
}

void	Channel::setTopic(std::string topic) {
	this->_topic = topic;
}

std::string	Channel::getTopic(void) {
	return (this->_topic);
}

bool Channel::isOp(Client& client) {
	std::vector<Client>::iterator find;

	find = std::find(_op.begin(), _op.end(), client);
	if (find != _op.end())
		return true;
	return false;
}

bool Channel::isOp(std::string clientName) {
	std::vector<Client>::iterator find;

	find = _op.begin();
	for (;find != _op.end(); ++find) {
		if (clientName.compare(find->getNick()) == 0)
			return true;
	}
	return false;
}

// Client Channel::findClient(std::string clientName) {
// 	std::vector<Client>::iterator find;

// 	find = _clients.begin();
// 	for (;find != _clients.end(); ++find) {
// 		if (clientName.compare(find->getNick()) == 0)
// 			return *find;
// 	}
// 	return (NULL);
// }
