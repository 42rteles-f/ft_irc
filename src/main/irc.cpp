/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:05:27 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/19 18:40:58 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

int main(int ac, char **args)
{
    t_protocol  *tcp;
    t_sock      sock;
    int         server_fd;
    int         test;
    int         size;
    int         port;
    char        buffer[1024];

    if (ac != 2)
        return (write(2, "Usage: ./program <port number>\n", 32));
    port = atoi(args[1]);
    tcp = getprotobyname("tcp");
    server_fd = socket(AF_INET, SOCK_STREAM, tcp->p_proto);
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = INADDR_ANY;
    sock.sin_port = htons(port);
    bind(server_fd, (struct sockaddr*)&sock, sizeof(sock));
    listen(server_fd, 0);
    size = sizeof(struct sockaddr_in);
    if ((test = accept(server_fd, (sockaddr *)&sock, (socklen_t *)&size)) > 0)
        printf("connection %i.\n", test);
    else
        printf("fail.\n");
    while (1) {
        recv(test, (void *)buffer, 1024, 0);
        printf("information: %s\n", buffer);
        bzero(buffer, 1024);
    }
    if ((test = accept(server_fd, (sockaddr *)&sock, (socklen_t *)&size)) > 0)
        printf("connection %i.\n", test);
    else
        printf("fail.\n");
}
