#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#define CHECK_RET(rv, reason)                                                           \
    if (rv < 0)                                                                         \
    {                                                                                   \
        printf("call "#reason" failed errno:%d strerror:%s", errno, strerror(errno));   \
        return -1;                                                                      \
    }

#define CHECK_RET_EAGAIN(rv, reason)                                                    \
    if (rv < 0)                                                                         \
    {                                                                                   \
        if (errno == EAGAIN)                                                            \
        {                                                                               \
            sleep(1);                                                                   \
            continue;                                                                   \
        }                                                                               \
        printf("call " #reason " failed errno:%d strmsg:%s\n", errno, strerror(errno)); \
        return -1;                                                                      \
    }

int main() 
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    CHECK_RET(fd, "socket");

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    int rv = fcntl(fd, F_GETFL, 0);
    CHECK_RET(rv, "fcntl F_GETFL");

    rv = fcntl(fd, F_SETFL, rv | O_NONBLOCK);
    CHECK_RET(rv, "fcntl F_SETFL");

    const int on = 1;
    rv = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    CHECK_RET(rv, "setsockopt SO_REUSEADDR");

    rv = bind(fd, (const struct sockaddr *)&server, sizeof(struct sockaddr));
    CHECK_RET(rv, "bind");

    rv = listen(fd, 5);
    CHECK_RET(rv, "listen");

    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    socklen_t addrlen = sizeof(client);

    printf("start server port 8080 ...\n");
    while (1) // wait client connect 
    {
        rv = accept(fd, (struct sockaddr *)&client, &addrlen);
        CHECK_RET_EAGAIN(rv, "accept")

        break;
    }


    // printf("sin_addr.s_addr: %s\n", inet_ntoa(client.sin_addr));
    printf("accept ok ...");

    int newfd = rv;

    //stop run wait overflow socket buff 
    getchar();

    char recvbuf[512] = {0};
    int total_recv_sz = 0;
    while (1)
    {
        recvbuf[0] = '\0';
        rv = recv(newfd, recvbuf, sizeof(recvbuf)-1, MSG_DONTWAIT);
        CHECK_RET_EAGAIN(rv, "recv");
        
        if (rv == 0)
        {
            printf("======>[rv==0] break while recv \n");
            break;
        }

        if (strncmp(recvbuf, "stop", 4) == 0) 
        {
            printf("recv msg stop ...\n");
            printf("total_recv_sz: %d \n", total_recv_sz);
            total_recv_sz = 0;
            getchar();
        } 
        else
        {
            total_recv_sz += rv;
            printf("total_recv_sz: %d, recvbuf strlen():%d\n", total_recv_sz, strlen(recvbuf));
        }
        

    }
        
    
    close(fd);

    return 0;
}