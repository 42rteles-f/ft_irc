/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:04:14 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/19 18:07:46 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <stdlib.h>
# include <netdb.h>
# include <netinet/in.h>
# include <stdio.h>
# include <unistd.h>

typedef struct protoent     t_protocol;
typedef struct sockaddr_in  t_sock;
typedef char *(*ter_char)();

char	*get_next_line(int fd);

#endif