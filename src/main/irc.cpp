/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:05:27 by rteles-f          #+#    #+#             */
/*   Updated: 2024/03/27 20:45:05 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include "../server/Server.hpp"

int main(int ac, char **args)
{
	Server	server;

	if (ac != 2 || !server.setup(args)) {
		std::cout << "Error" << std::endl;
		return (1);
	}
	server.online();
}
