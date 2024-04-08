/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/08 20:14:55 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Server;

class Channel {
	private:
		// Server	*observer;
		std::string	_topic;
		std::vector<Client> _clients;
		std::vector<Client>	_op; 

	public:
		Channel();
		Channel(const Channel& tocopy);
		~Channel();

		Channel& operator=(const Channel& tocopy);

		void	addClient(Client& add);
		void	removeClient(Client& remove);

		void			changeOp(Client &client);
		std::string		getTopic();
		size_t 			NumberOfClients();
		void			setTopic(std::string newTopic);
		void			printOPName();
} ;
