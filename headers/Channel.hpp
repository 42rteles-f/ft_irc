/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 22:06:41 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Server;

class Channel {
	private:
		std::vector<Client> _sockets;
		std::vector<Client> _op;

	public:
		Channel();
		Channel(const Channel& tocopy);
		~Channel();

		Channel& operator=(const Channel& tocopy);
		bool	operator==(const Client& compare);

		void	addClient(Client& add);
		void	removeClient(Client& remove);
} ;
