/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:04:14 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/09 11:56:17 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# define HOSTNAME "irc.example.com"

# include <iostream>
# include <vector>
# include <map>
# include <list>
# include <sstream>
# include <string>
# include <algorithm>
# include <unistd.h>
# include <poll.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <signal.h>
# include "Client.hpp"
# include "Channel.hpp"
# include "Connections.hpp"
# include "Server.hpp"
# include <algorithm>
