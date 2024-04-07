/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/07 00:41:03 by lliberal         ###   ########.fr       */
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

size_t Channel::NumberOfClients() {
	return _sockets.size();
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

std::string		Channel::getTopic() {
	return _topic;
}

void		Channel::setTopic(std::string newTopic) {
	_topic = newTopic;
}

