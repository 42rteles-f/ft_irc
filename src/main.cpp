/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:05:27 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/11 14:00:44 by rteles-f         ###   ########.fr       */
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
	struct sigaction	info = {0};

	if (ac != 3 && std::cout << "Error: Usage: /ft_irc <Port> <Password>" << std::endl
		|| !server.setup(args)) {		
		return (1);
	}
	ft_signal_handler(0, &server);
	info.sa_sigaction = (void (*)(int, siginfo_t *, void *))ft_signal_handler;
	info.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &info, 0);

	server.online();
	return (0);
}
