/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/08 20:37:56 by lliberal         ###   ########.fr       */
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
}

void	Channel::removeClient(Client& remove) {
	std::vector<Client>::iterator find;

	find = std::find(_op.begin(), _op.end(), remove);
	if (find != _op.end())
		_op.erase(find);
	find = std::find(_clients.begin(), _clients.end(), remove);
	if (find != _op.end())
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
