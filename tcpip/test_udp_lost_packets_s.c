#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

/**
 * 测试UDP丢包的接收端代码
*/

int main() {

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("create socket failed .");
        exit(-1);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    // server.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    int rv = bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if (rv < 0) {
        perror("bind socket failed .");
        exit(-1);
    }

    // get system limit recv/send buffer size
    int buff_size = -1;
    socklen_t optlen = sizeof(buff_size);
    if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buff_size, &optlen) < 0) {
        printf("getsockopt failed . errno:%d strerrno:%s", errno, strerror(errno));
        exit(-1);
    }
    printf("getsockopt recv buff size = %d\n", buff_size); // 212992

    // 1024 * 1024 > 212992
    char recvbuff[1024*1024] = {0};
    struct sockaddr_in client;
    int addrlen = sizeof(struct sockaddr_in);

    int ctrl = -1;
    int total_recv_size = 0;

    while (1) {

        if (ctrl >= 0) {
            // printf("first in while need input any char .");
        } else {
            printf("first in while need input any char .");
            ctrl = getchar();
        }

        rv = recvfrom(fd, recvbuff, sizeof(recvbuff), 0, (struct sockaddr *)&client, &addrlen);
        if (rv < 0)
        {
            perror("recvfrom error\n");
            //close(sockfd);
            continue;
        }
        total_recv_size += strlen(recvbuff);
        printf("recvform ret: %d, recvfrom total_recv_size: %d\n", rv, total_recv_size);

        recvbuff[0] = 0;

        // sleep(2);
    }   
    close(fd);

    return 0;
}