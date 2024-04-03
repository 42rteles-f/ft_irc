/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:37:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 19:48:55 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Client.hpp>

Client::Client():
socket(NULL), input(""), _command(false), closed(false)
{}

Client::Client(struct pollfd* socket):
socket(NULL), input(""), _command(false), closed(false)
{}

Client::Client(const Client& tocopy):
socket(tocopy.socket)
{
	*this = tocopy;
}

Client::~Client() {}

Client& Client::operator=(const Client& tocopy) {
	if (this == &tocopy)
		return (*this);
	this->socket = tocopy.socket;
	this->input = tocopy.input;
	this->_command = tocopy._command;
	this->closed = tocopy.closed;
	return (*this);
}

bool	Client::isClosed(void) {
	return (this->closed ? true : false);
}

bool	Client::update(void) {
	char		buffer[READSIZE];
	int			length;

	if (!(socket->revents & POLLIN)) {
		std::cout << "here" << std::endl;
		return (false);
	}
	while ((length = recv(socket->fd, (void *)buffer, READSIZE, MSG_DONTWAIT)) > 0)
		this->input.append(buffer, length);
	if (!length) {
		this->closed = true;
		this->input.clear();
		return (false);
	}
	std::cout << this->input << std::endl;
	return (true);
}
