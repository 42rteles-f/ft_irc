/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:37:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/19 21:37:23 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client():
{ std::cout << "Client Default Constructor called." << std::endl; }

Client::Client(const Client& tocopy)
{
	std::cout << "Client Copy Constructor called." << std::endl;
	*this = tocopy;
}

Client::~Client()
{ std::cout << "Client Destructor called." << std::endl; }

Client& Client::operator=(const Client& tocopy) {
	if (this == &tocopy)
		return (*this);
	asdasd;
	/*
	to do;
	*/
	return (*this);
}
