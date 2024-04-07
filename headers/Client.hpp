/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/07 00:54:53 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Server;

class Client {
	private:
		std::string				_input;
		std::string				_request;
		std::string				_nick;
		std::string				_user;
		std::string				_real;
		bool					_command;
		bool					_closed;

	public:
		struct pollfd			*_socket;

		Client();
		Client(struct pollfd* socket);
		Client(const Client& tocopy);
		~Client();

		Client& operator=(const Client& tocopy);

		std::string	getInput();
		std::string getNick();
		std::string getUser();
		std::string getRequest();
		bool	update(void);
		bool	isClosed(void);
		bool	hasRequest(void);
		void	makeRequest(Server& server);

		std::string	input(void);
} ;
