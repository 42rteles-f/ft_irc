/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/11 17:55:01 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Server;

class Channel {
	private:
		// Server	*observer;
		std::string	_name;
		std::string	_topic;
		std::vector<Client*>	_clients;
		std::vector<Client*>	_op; //the first Client is the operator

	public:
		Channel();
		Channel(std::string name);
		Channel(const Channel& tocopy);
		~Channel();

		Channel&	operator=(const Channel& tocopy);
		bool		operator==(const Client& compare);
		Channel& 	operator()(const std::string name);

		void	addClient(Client& add);
		void	removeClient(Client& remove);
		void	removeClient(std::string remove);
		void	broadcast(Client& client);
		void	broadcast(std::string message);

		bool 			isOp(Client &client);
		bool			isOp(std::string clientName);

		const std::string& name(void);
		void			changeOp(Client &client);
		std::string		getTopic();
		void			setTopic(std::string newTopic);
		Client&			getClient(size_t index);
		std::vector<Client*>&	getClients();
		size_t 			NumberOfClients();
		void			printOPName();
} ;

// 1700 sem bot
// 1830 com bot