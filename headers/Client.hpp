/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 22:22:20 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Server;

class Client {
	private:
		std::string				_input;
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

		bool	update(void);
		bool	isClosed(void);
		void	execute(const Server& server);

} ;
