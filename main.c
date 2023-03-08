
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

#define PORT 15000

int main(int argc, char **argv) {
    int listenfd, connfd, r;
    int opt = 1;
    struct sockaddr_in  servaddr;
    int servaddr_len = sizeof(servaddr);

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // if (setsockopt(listenfd, SOL_SOCKET,
    //                SO_REUSEADDR | SO_REUSEPORT, &opt,
    //                sizeof(opt))) {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if ((listen(listenfd, 5)) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((connfd = accept(listenfd, (struct sockaddr *)&servaddr, (socklen_t *)&servaddr_len)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    const char *sendto = "From serv\n";
    while (1) {

        fflush(stdout);

        memset(buffer, 0, 1024);

        r = read(connfd, buffer, 1023);
        printf("%s\n", buffer);

        send(connfd, sendto, strlen(sendto), 0);

        if (!strcmp(buffer, "\n"))
            break ;

    }
    close(connfd);
    return (0);
}