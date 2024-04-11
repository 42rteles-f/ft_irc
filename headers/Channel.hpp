/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/10 20:24:14 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Server;

class Channel {
	private:
		// Server	*observer;
		typedef void    (Channel::*t_exe)(Client&, std::string, std::string);
		std::string	_name;
		std::string	_modes[255];
		std::string	_topic;
		std::map<char, t_exe>	_functions;
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
		const std::string& name(void);
		void	removeClient(Client& remove);
		void	removeClient(std::string remove);
		void	broadcast(Client& client);
		void	broadcast(std::string message);

		void	invalidMode(void);
		void 	operatorMode(Client &client, std::string mode, std::string argument);
		void 	inviteMode(Client &client, std::string mode, std::string argument);


		bool 			isOp(Client &client);
		bool			isOp(std::string clientName);

		void			addOp(Client &client);
		std::string		getTopic();
		Client&			getClient(size_t index);
		std::vector<Client*>&	getClients();
		size_t 			NumberOfClients();
		void			setTopic(std::string newTopic);
		void			printOPName();
		Client* 		findClient(std::string clientName);
		void 			addMode(Client &client, std::string mode, std::string argument);
		void 			removeOp(Client& client);


} ;
