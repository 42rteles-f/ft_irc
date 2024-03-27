/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:05:27 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/20 16:12:54 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ft_irc.hpp>

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
# include <strings.h>
# include <string.h>

typedef struct protoent     t_protocol;
typedef struct sockaddr_in  t_sock;

void    end_chat(int server, int fd1, int fd2)
{
    close(fd1);
    close(fd2);
    close(server);
    exit(0);
}

int main(int ac, char **args)
{
	Server	server;

	if (!server.setup(args)) {
		std::cout << "Error" << std::endl;
		return (1);
	}
	server.run();
	server.end();




    t_protocol  *tcp;
    t_sock      sock;
    int         server_fd;
    int         test;
    int         size;
    int         port;
    int         fd1;
    int         fd2;
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
    if ((fd1 = accept(server_fd, (sockaddr *)&sock, (socklen_t *)&size)) > 0)
        printf("connection %i.\n", fd1);
    else
        printf("fail.\n");
    if ((fd2 = accept(server_fd, (sockaddr *)&sock, (socklen_t *)&size)) > 0)
        printf("connection %i.\n", fd2);
    else
        printf("fail.\n");
    while (1) {
        recv(fd1, (void *)buffer, 1024, MSG_DONTWAIT);
        if (*buffer) {
            if (!strcmp(buffer, "QUIT\n"))
                end_chat(server_fd, fd1, fd2);
            send(fd2, (void *)"User 1:\n", 9, 0);
            send(fd2, (void *)buffer, strlen(buffer), 0);
            send(fd1, (void *)"\n", 1, 0);
            send(fd2, (void *)"\n", 1, 0);
            send(fd1, (void *)"User 1:\n", 9, 0);
        }
        bzero(buffer, 1024);
        recv(fd2, (void *)buffer, 1024, MSG_DONTWAIT);
        if (*buffer) {
            send(fd1, (void *)"User 2:\n", 9, 0);
            send(fd1, (void *)buffer, strlen(buffer), 0);
            send(fd1, (void *)"\n", 1, 0);
            send(fd2, (void *)"\n", 1, 0);
            send(fd2, (void *)"User 2:\n", 9, 0);
        }
        bzero(buffer, 1024);
    }
}
