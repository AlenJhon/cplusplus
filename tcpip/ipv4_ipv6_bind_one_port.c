#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

int 
main() {
    
    //ipv4
    int fdv4 = socket(AF_INET, SOCK_STREAM, 0);
    if (fdv4 < 0) {
        printf("socket failed \n");
        return -1;
    }
    printf("fdv4:%d\n", fdv4);

    struct sockaddr_in server;
    memset( &server, 0, sizeof(server) );
    server.sin_family = AF_INET;
    
    
    
    return 0;
}
