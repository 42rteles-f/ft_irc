/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:05:27 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/09 14:23:21 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	ft_signal_handler(int signal, Server *save) {
	static Server	*server;

	if (!server) {
		server = save;
		return ;
	}
	server->offline();
	return ;
}

int main(int ac, char **args)
{
	Server				server;
	struct sigaction	info;

	if (ac != 2 || !server.setup(args)) {
		std::cout << "Error" << std::endl;
		return (1);
	}
	ft_signal_handler(0, &server);
	info.sa_sigaction = (void (*)(int, siginfo_t *, void *))ft_signal_handler;
	info.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &info, 0);

	server.online();
	return (0);
}
