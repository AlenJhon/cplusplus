#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>


int main() {
    
    const char* sip = "192.168.1.98";

#if 1
    uint32_t nip = 0;
    inet_pton(AF_INET, sip, &nip);
    
    printf("nip=%u\n", nip);
    //int i = 0, j = 3;
    //unsigned char chtmp;
    //while (i < j) {
    //    chtmp = *((unsigned char*)&nip + i);
    //    *((unsigned char*)&nip + i) = *((unsigned char*)&nip + j);
    //    *((unsigned char*)&nip + j) = chtmp;

    //    ++i;
    //    --j;
    //}
    //printf("little end nip:%u\n", nip);

    char buf[32] = { 0 };
    inet_ntop(AF_INET, &nip, buf, sizeof(buf));
    printf("buf:%s \n", buf);

#elif 0

    char buf[5] = { 0 };
    inet_pton(AF_INET, "192.168.1.98", &buf);

    printf("big end ip:%u\n", *(unsigned int*)buf);
    int l = 0, r = 3;
    while (l < r) {
        char c = buf[l];
        buf[l] = buf[r];
        buf[r] = c;

        l += 1;
        r -= 1;
    }
    printf("little end ip:%u\n", *(unsigned int*)buf);

#elif 0 
    
    struct sockaddr_in addr;
    char _port[6];  /* strlen("65535"); */
    snprintf(_port, 6, "%d", 0);

    struct addrinfo hints, * servinfo, *p;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(sip, _port, &hints, &servinfo) != 0) {
        hints.ai_family = AF_INET6;
        if (getaddrinfo(sip, _port, &hints, &servinfo) != 0) {
            //GLOG_SER("getaddrinfo error try 6 and 4 host:%s", sip);
            return -1;
        }
    }


    for (p = servinfo; p != NULL; p = p->ai_next) {
        int sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            continue;
        }
        close(sockfd);
        memcpy(&addr, p->ai_addr, p->ai_addrlen);
        freeaddrinfo(servinfo);

        printf("ip num :%u \n", addr.sin_addr.s_addr);

        return 0;
    }
    freeaddrinfo(servinfo);

#elif 0
    struct in_addr stClient;
    memset(&stClient, 0, sizeof(struct in_addr));
    inet_aton(sip, &stClient);
    printf("ip num :%u \n", stClient.s_addr);

#endif

    return 0;
}
