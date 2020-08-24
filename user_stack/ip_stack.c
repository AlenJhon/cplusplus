#include <stdio.h>

#define ETH_LEN     6

//以太网协议 头部 14字节
struct ethhdr {
    unsigned char h_dest[ETH_LEN]; //mac
    unsigned char h_src[ETH_LEN];
    unsigned short h_proto;
};


//IP协议头部 20字节
struct iphdr {
    unsigned char version:4, 
                  hdrlen:4;  //32位 个数
    unsigned char tos; //
    unsigned short length;

    unsigned short id;
    unsigned short flag:3,
                   offset:13;

    unsigned char ttl;
    unsigned char proto;
    unsigned short check;

    unsigned int sip;
    unsigned int dip;
};


//udp协议 头部8字节
struct udphdr {
    unsigned short sport;
    unsigned short dport;
    unsigned short length;
    unsigned short check;
};

//udp 数据包头部
struct udppkt {
    struct ethhdr eh;
    struct iphdr ip;
    struct udphdr udp;

    unsigned char body[0]; // sizeof(body)=0;
};


int main() {

    printf("sizeof(ethhdr)=%d\n", sizeof(struct ethhdr));
    printf("sizeof(udppkt)=%d\n", sizeof(struct udppkt));

    return 0;
}




