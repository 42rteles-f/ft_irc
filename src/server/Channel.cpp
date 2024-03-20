/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/20 16:54:06 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

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

std::list<Client>	Channel::getChannel(int channel) {

	return ()
}

void	Channel::update(void) {
	std::list<Client>::iterator	client;
	std::string					input;

	for (client = _clients.begin(); client!= _clients.end(); client++) {
		client.readInput();
		if (isCommand(client.getInput()))
			executeCommand(client);
		else if (!input.empty())
			this->broadcast(client.getInput());
		client.clearInput();
	}
}
