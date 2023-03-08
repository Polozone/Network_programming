
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int status;
    struct addrinfo hints, *p, *serv;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    status = getaddrinfo(argv[1], NULL, &hints, &serv);
    
    for (p = serv; p != NULL; p = p->ai_next)
    {
        void *addr;
        char ipstr[1024];
        memset(ipstr, 0, 1024);

        if (p->ai_family == AF_INET)
        {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            // dprintf(2, "%s\n", hints.ai_family);
        }
        else
        {
            struct sockaddr_in *ipv6 = (struct sockaddr_in *)p->ai_addr;
                        addr = &(ipv6->sin6_addr);

            // addr = &(ipv6->sin6_addr);
        }
        // convert IP to a string and print it;
        inet_ntop(p->ai_family, addr, ipstr, 1024);
        dprintf(2, "%s\n", ipstr);
    }
    freeaddrinfo(serv);
    return 0;
}
