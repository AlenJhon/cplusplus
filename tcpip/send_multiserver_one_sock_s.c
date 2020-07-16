#include <stdio.h>
// #include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h> //socket connect
#include <netinet/in.h>
#include <errno.h>  // errno strerrno
#include <string.h> //memset

/**
 * 共用一个socket 向不同的server发送消息 tcp是需要一对一不能这样
 * server code
*/


int server_sim(unsigned short port)
{
    printf("start server port:%d...\n", port);

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        printf("call socket failed errno:%d strerrno:%s\n", errno, strerror(errno));
        return -1;
    }
    printf("create socket success .\n");

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    int rv = bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if (rv < 0)
    {
        printf("call bind failed errno:%d strerrno:%s\n", errno, strerror(errno));
        return -1;
    }
    printf("bind success .\n");

    char recvbuff[512] = {0};
    struct sockaddr_in client;
    int addrlen = sizeof(struct sockaddr_in);

    fflush(stdout);
    while (1)
    {
        rv = recvfrom(fd, recvbuff, sizeof(recvbuff), 0, (struct sockaddr *)&client, &addrlen);
        if (rv < 0)
        {
            printf("call recvfrom failed errno:%d strerrno:%s\n", errno, strerror(errno));
            close(fd);
            break;
        }
        recvbuff[rv] = '\0';
        printf("recv msg:%s\n", recvbuff);
        if (strcmp(recvbuff, "stop") == 0) 
        {
            break;
        }
    }
    printf("stop server_sim port:%d \n", port);

    return 0;
}


int main(int argc, char **argv) 
{
    printf("argc=%d\n", argc);

    int port = 8080;
    if (argc > 1) 
    {
        port = atoi(argv[1]);
    }
    printf("listen port=%d\n", port);

    server_sim(port);

    return 0;
}