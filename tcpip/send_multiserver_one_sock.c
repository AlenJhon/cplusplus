#include <stdio.h>
// #include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h> //socket connect
#include <netinet/in.h>
#include <errno.h> // errno strerrno
#include <string.h> //memset

/**
 * 共用一个socket 向不同的server发送消息 tcp是需要一对一不能这样
 * client code
*/

int main() {

    // client
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        printf("call socket failed errno:%d strerrno:%s\n", errno, strerror(errno));
        return -1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    // server.sin_family = AF_INET;
    // server.sin_addr.s_addr = INADDR_ANY;
    // server.sin_port = htons(8080);

    // socklen_t addrlen = sizeof(struct sockaddr_in);

    // int rv = connect(fd, (const struct sockaddr *)&server, sizeof(struct sockaddr_in));
    // if (rv < 0) {
    //     printf("call connect failed errno:%d strerrno:%s\n", errno, strerror(errno));
    //     return -1;
    // }
    int rv = 0;
    char sendbuff[512] = {0};
    while (1) 
    {
        memset(sendbuff, 0, sizeof(sendbuff));
        char select_case[24] = {0};
        printf("=========================="
        "new while \n\ninput casea | stopa | stopb | others :\n");
        fgets(select_case, 24, stdin);
        printf("select_case:%s", select_case);
        if (strcmp(select_case, "casea\n") == 0) 
        {
            snprintf(sendbuff, sizeof(sendbuff), "%s", select_case);
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(8081);
        } 
        else if (strcmp(select_case, "stopa\n") == 0)
        {
            snprintf(sendbuff, sizeof(sendbuff), "%s", "stop");
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(8081);
        }
        else if (strcmp(select_case, "stopb\n") == 0)
        {
            snprintf(sendbuff, sizeof(sendbuff), "%s", "stop");
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(8082);
        }
        else 
        {
            snprintf(sendbuff, sizeof(sendbuff), "%s", select_case);
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(8082);
        }

        printf("connect ...\n", sendbuff);
        rv = connect(fd, (const struct sockaddr *)&server, sizeof(struct sockaddr_in));
        if (rv < 0) {
            printf("call connect failed errno:%d strerrno:%s\n", errno, strerror(errno));
            return -1;
        }

        printf("sendto %s\n", sendbuff);
        rv = sendto(fd, sendbuff, strlen(sendbuff), 0, (struct sockaddr *)&server, sizeof(server));
        if (rv < 0)
        {
            printf("call sendto failed errno:%d strerrno:%s\n", errno, strerror(errno));
            return -1;
        }
    }

    return 0;
}