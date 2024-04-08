/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 22:06:00 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Channel.hpp>

Channel::Channel()
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

	find = std::find(_sockets.begin(), _sockets.end(), add);
	if (find == _sockets.end())
		_sockets.push_back(add);
	if (_op.size() == 0)
		_op.push_back(add);
}

void	Channel::removeClient(Client& remove)
{
	std::vector<Client>::iterator find;

	find = std::find(_op.begin(), _op.end(), remove);
	if (find != _op.end())
		_op.erase(find);
	find = std::find(_sockets.begin(), _sockets.end(), remove);
	if (find != _op.end())
		_sockets.erase(find);
	if (_sockets.size() && _op.size() == 0)
		_op.push_back(_sockets[0]);
}
