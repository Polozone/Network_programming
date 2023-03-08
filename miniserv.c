

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdint.h>

int main()
{
    struct sockaddr_in  server_addr;
    int                 server_fd;
    int                 len_servaddr;
    int                 fd_accepted;

    len_servaddr = sizeof(server_addr);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        dprintf(2, "socket:");
        perror("");
        return (-1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1400);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_fd, (struct sockaddr*)&server_addr, len_servaddr) < 0){
        dprintf(2, "bind:");
        perror("");
        return (-2);
    }
    if ((listen(server_fd, 5)) < 0){
        dprintf(2, "listen:");
        perror("");
        return (-3);
    }
    if ((fd_accepted = accept(server_fd, (struct sockaddr *)&server_addr, (socklen_t *)&len_servaddr)) < 0){
        dprintf(2, "listen:");
        perror("");
        return (-4);
    }
    char buffer[1024];
    while (1)
    {
        memset(buffer, 0, 1024);
        read(fd_accepted, buffer, 1024);
        dprintf(2, ":%s\n", buffer);
        if (!strcmp(buffer, "exit\n"))
            break ;
    }
    return (0);
}