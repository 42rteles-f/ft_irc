/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/20 16:40:34 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <ft_irc.hpp>
# include <iostream>
# include <list>
# include <map>

class Client;
class Channel;

class Server {
	private:
		std::map<std::string, Channel>	_channels;
		Channel	connections;
		int		server_socket;
		bool	_online;

		void	updateChannels(void);

	public:
		Server();
		Server(const Server& tocopy);
		~Server();

		Server& operator=(const Server& tocopy);

		void	setup(void);
		void	online(void);
		void	offline(void);
} ;

#endif