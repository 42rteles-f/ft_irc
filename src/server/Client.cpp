/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:37:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 00:42:47 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include "Client.hpp"

Client::Client(struct pollfd socket):
socket(socket), input(""), _command(false)
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
	this->input = tocopy.input;
	this->_command = tocopy._command;
	return (*this);
}
