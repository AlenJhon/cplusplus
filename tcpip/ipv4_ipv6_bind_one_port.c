#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
// #include <time.h>




int net_tcp_server(int port, int af, int backlog) {
    
    char _port[6];  /* strlen("65535") */
    snprintf(_port, 6, "%d", port);

    int rv = 0, s = -1;

    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = af;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;    /* No effect if bindaddr != NULL */

   
    if ((rv = getaddrinfo(NULL, _port, &hints, &servinfo)) != 0) {
        printf("getaddrinfo failed errno:%d err:%s \n", errno, strerror(errno));
        return -1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {

        if ((s = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        // if (af == AF_INET6 && anetV6Only(err,s) == ANET_ERR) goto error;
        // if (anetSetReuseAddr(err,s) == ANET_ERR) goto error;
        

        if (af == AF_INET6) {
            int yes = 1;
            if (setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &yes, sizeof(yes)) == -1) {
                printf("setsockopt failed \n");
                close(s);
                return -1;
            }
        }

        int yes = 1;
        /* Make sure connection-intensive things like the redis benchmark
        * will be able to close/open sockets a zillion of times */
        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
            printf("setsockopt failed \n");
            close(s);
            return -1;
        }


        rv = bind(s, p->ai_addr, p->ai_addrlen);
        if (rv < 0) {
            printf("bind socket:%d failed errno:%d err:%s .", s, errno, strerror(errno));
            close(s);
            return -2;
        }

        rv = listen(s, backlog);
        if (rv != 0) {
            printf("listen failed \n");
            close(s);
            return -3;
        }
    }

    return 0;
}


int 
main() {
    
#if 0
    //ipv4
    int fdv4 = socket(AF_INET, SOCK_STREAM, 0);
    if (fdv4 < 0) {
        printf("socket failed \n");
        return -1;
    }
    printf("fdv4:%d\n", fdv4);

    struct sockaddr_in server;
    memset( &server, 0, sizeof(server) );
    server.sin_family = AF_INET;
    server.sin_port = htonl(8618);
    // server.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.sin_addr.s_addr = INADDR_ANY;

    int rv = bind(fdv4, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if (rv < 0) {
        printf("bind socket:%d failed .", fdv4);
        return -2;
    }

    rv = listen(fdv4, 10);
    if (rv != 0) {
        printf("listen failed \n");
        return -3;
    }


    //ipv6
    int fdv6 = socket(AF_INET6, SOCK_STREAM, 0);
    if (fdv6 < 0) {
        printf("AF_INET6 socket failed \n");
        return -1;
    }
    printf("AF_INET6 create success fdv6:%d\n", fdv6);

    // struct sockaddr_in server6;
    // memset( &server6, 0, sizeof(server6) );
    // server6.sin_family = AF_INET6;
    // server.sin_port = htonl(8619);
    // server.sin_addr.s_addr = inet_addr(":::");

    struct sockaddr_in6 addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htonl(8618);
    addr.sin6_addr = in6addr_any;
    // rv = inet_pton(AF_INET6, "fe80::20c:29ff:fe35:bf1e", &addr.sin6_addr);
    rv = bind(fdv6, (struct sockaddr *)&addr, sizeof(struct sockaddr_in6));
    if (rv < 0) {
        printf("AF_INET6 bind socket:%d failed errno:%d err:%s.\n", fdv6,  errno,  strerror(errno));
        return -2;
    }
    printf("AF_INET6 bind success\n");

    rv = listen(fdv6, 10);
    if (rv != 0) {
        printf("AF_INET6 listen failed \n");
        return -3;
    }
    printf("AF_INET6 listen success\n");
#else 
    int rv = net_tcp_server(8618, AF_INET, 10);
    if (rv != 0) {
        printf("net_tcp_server failed\n");
        return -1;
    }
    printf("AF_INET listen success\n");

    rv = net_tcp_server(8618, AF_INET6, 10);
    if (rv != 0) {
        printf("net_tcp_server failed\n");
        return -1;
    }
    printf("AF_INET6 listen success\n");

#endif




    while(1) {
        sleep(1);
    }
    
    
    return 0;
}
