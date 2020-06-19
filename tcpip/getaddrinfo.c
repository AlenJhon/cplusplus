#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(void) {

    struct addrinfo hints, *servinfo, *p;
    
    memset( &hints, 0, sizeof(hints) );
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    int rv = getaddrinfo(NULL, "36001", &hints,  &servinfo);
    if (rv != 0) {
        printf("getaddrinfo failed errno:%d err:%s\n", errno, strerror(errno));
        return -1;
    }


    for (p = servinfo; p != NULL; p = p->ai_next) {
        printf("%d, ai_canonname:%s \n", p->ai_family, p->ai_canonname);
    }

    return 0;
}
