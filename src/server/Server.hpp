/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/19 21:46:21 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <ft_irc.hpp>
# include <iostream>
# include <list>
# include <map>

class Client;

class Server {
	private:
		std::map<int, std::list<Client>> test;

	public:
		Server();
		Server(const Server& tocopy);
		~Server();

		Server& operator=(const Server& tocopy);
} ;

#endif