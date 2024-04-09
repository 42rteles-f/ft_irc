/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/08 21:40:36 by lliberal         ###   ########.fr       */
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
		std::vector<Client>	_op; //the first Client is the operator

	public:
		Channel();
		Channel(const Channel& tocopy);
		~Channel();

		Channel& operator=(const Channel& tocopy);
		bool	operator==(const Client& compare);

		void	addClient(Client& add);
		void	removeClient(Client& remove);
		void	broadcast(Client& client);
		void	broadcast(std::string message);

		bool 			isOp(Client &client);

		void			changeOp(Client &client);
		std::string		getTopic();
		Client&			getClient(size_t index);
		std::vector<Client>&	getClients();
		size_t 			NumberOfClients();
		void			setTopic(std::string newTopic);
		void			printOPName();
} ;
