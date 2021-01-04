// test.cc
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

#define MAXLINE 4096
 
int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: ./tcptest_client <ipAddress>\n");
        return 0;
    }
 
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof localAddr);
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(12345);
    if(bind(sockfd, (struct sockaddr*)&localAddr, sizeof localAddr) == -1) {
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof serverAddr);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12346);
    if(inet_pton(AF_INET, argv[1], &serverAddr.sin_addr) == -1) {
        perror("inet_pton error");
        exit(EXIT_FAILURE);
    }

    auto start = system_clock::now();
    if(connect(sockfd, (struct sockaddr*)&serverAddr, sizeof serverAddr) == -1) {
        perror("connect error");
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "It cost "
             << static_cast<double>(duration.count()) * microseconds::period::num / microseconds::period::den
             << " s." << endl;
        
        exit(EXIT_FAILURE);
    }
 
    printf("connect success\n");
    close(sockfd);
    
    return 0;
}
