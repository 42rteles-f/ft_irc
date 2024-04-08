/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/08 21:32:07 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Channel.hpp>

Channel::Channel() : _op()
{}

Channel::Channel(const Channel& tocopy)
{}

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

void	Channel::addClient(Client& add)
{
	std::vector<Client>::iterator find;

	find = std::find(_clients.begin(), _clients.end(), add);
	if (find == _clients.end())
		_clients.push_back(add);
	if (_op.size() == 0)
		_op.push_back(add);
}

void	Channel::removeClient(Client& remove)
{
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

void	Channel::broadcast(Client& sender)
{
	std::string	message = sender.makeMessage();

	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (sender.socket->fd != _clients[i].socket->fd)
			send(_clients[i].socket->fd, message.c_str(), message.size(), 0);
	}
}