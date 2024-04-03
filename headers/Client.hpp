/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:30:16 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/03 01:41:53 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <ft_irc.hpp>

class Client {
	private:
		const struct pollfd&	socket;
		std::string				input;
		bool					_command;
		bool					closed;

	public:
		Client(struct pollfd& socket);
		Client(const Client& tocopy);
		~Client();

		Client& operator=(const Client& tocopy);

		bool	hasInput(void);
		bool	update(void);
		bool	isClosed(void);

} ;
