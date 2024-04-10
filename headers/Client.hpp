/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/10 14:17:25 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Server;
class Channel;

class Client {
	private:
		std::string				_read;
		std::string				_input;
		std::string				_request;
		std::string				_nick;
		std::string				_user;
		std::string				_real;
		bool					_command;
		bool					_closed;
		std::vector<Channel*>	_myChannels;

	public:
		struct pollfd			*socket;

		Client();
		Client(struct pollfd* socket);
		Client(const Client& tocopy);
		~Client();

		Client& operator=(const Client& tocopy);
		bool	operator==(const Client& compare);
		bool	operator!=(const Client& compare);

		bool	update(void);
		bool	isClosed(void);
		bool	hasRequest(void);
		void	makeRequest(Server& server);
		void	sendMessage(std::string user) const;
		std::string	makeMessage(void) const;
		std::string	makeMessage(const std::string) const;
		void	addChannel(Channel *channel);
		void	removeChannel(Channel *channel);
		std::vector<Channel*>	getChannels(void);

		std::string getRequest();
		const std::string&	input(void) const;
		void	setNick(std::string);
		const std::string&	getNick(void) const;
		void	setUser(std::string);
		const std::string&	getUser(void) const;
		void	setRealName(std::string);
		const std::string&	getRealName(void) const;
} ;
