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
    if (fd < 0) {
        perror("create socket failed .");
        exit(-1);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.sin_port = htons(8080);

    int ret = bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if (ret < 0) {
        perror("bind socket failed .");
        exit(-1);
    }

    char recvbuff[2048] = {0};
    struct sockaddr_in client;
    int addrlen = sizeof(struct sockaddr_in);
    while (1) {

        ret = recvfrom(fd, recvbuff, sizeof(recvbuff), 0,  (struct sockaddr *)&client, &addrlen);
        if (ret < 0)
		{
			perror("recvfrom error\n");
			//close(sockfd);
			continue;
		}
		printf("recvfrom : %s\n", recvbuff);
        recvbuff[0] = 0;

        sleep(2);
    }   
    close(fd);

    return 0;
}