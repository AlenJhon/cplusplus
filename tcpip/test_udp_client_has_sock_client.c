
#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main() {

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("create socket failed .");
        return -1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    int ret = connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if (ret < 0) {
        perror("connect failed .");
        close(fd);
        exit(1);
    }

    char sendbuff[1024] = {"send hello world."};
    // char recvbuff[1024] = {0};
    while(1) {

        // snprintf(sendbuff, sizeof(sendbuff), "hello", )
        ret = sendto(fd, sendbuff, sizeof(sendbuff), 0, (struct sockaddr*)&server, sizeof(server) );
        if ( ret < 0 ) {
            perror("sendto failed .");
            close(fd);
            exit(1);
        }

        sleep(5);
    }
    close(fd);

    return 0;
}