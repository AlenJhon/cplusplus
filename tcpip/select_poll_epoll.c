#include <sys/socket.h>
#include <inet>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>


int sockfd  = 0;
void do_sigo(int sig)
{
    char buffer[256] = {0};

    struct sockaddr_in cliaddr;
    int addrlen = sizeof(struct sockaddr_in);
    recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *)&cliaddr, &addrlen);
}

//proactor
int main( ) {

    struct sigaction sigio_action;
    sigio_action.sa_flags = 0;
    sigio_action.sa_handler = do_sigo;
    sigaction(SIGIO, &sigio_action, NULL);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6016);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));

    fcntl(sockfd, F_SETOWN, getpid());

    int flags = fcntl(sockfd, F_GETFL, 0);
    flags |= O_READ | O_WRITE;
}