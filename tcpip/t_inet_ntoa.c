#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main() {

	int nip = ntohl(0xc0a8006d);
	//unsigned int  nip = 0xc0a8006d;
	struct in_addr stClient;
    memset(&stClient, 0, sizeof(struct in_addr));
    stClient.s_addr = nip;
    printf( "str ip: %s from dwip:%u \n", inet_ntoa(stClient), nip );
	return 0;	
}
