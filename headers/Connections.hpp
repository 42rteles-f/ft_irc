/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/09 18:46:03 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Connections {
	private:
		std::vector<Client>			_clients;

	public:
		std::vector<struct pollfd> 	_sockets;
		Connections();
		Connections(const Connections& tocopy);
		~Connections();

		
		// void			fillClientData(struct pollfd& new_client);
		void			erase(size_t position);
		void			erase(Client& erase);
		void			add(struct pollfd& new_client);

		struct pollfd	*data(void);
		size_t			size(void);
		bool			serverRequest(void);
		std::vector<Client>::iterator	find(std::string nick);
		std::vector<Client>::iterator	end(void);
		int				serverAccept(sockaddr *sock);

		Connections&	operator=(const Connections& tocopy);
		Client&			operator[](size_t position);
} ;
