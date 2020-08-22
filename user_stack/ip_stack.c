#include <stdio.h>

#define ETH_LEN     6

//��̫��Э�� ͷ�� 14�ֽ�
struct ethhdr {
    unsigned char h_dest[ETH_LEN]; //mac
    unsigned char h_src[ETH_LEN];
    unsigned short h_proto;
};


//IPЭ��ͷ�� 20�ֽ�
struct iphdr {
    unsigned char version:4, 
                  hdrlen:4;  //32λ ����
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


//udpЭ�� ͷ��8�ֽ�
struct udphdr {
    unsigned short sport;
    unsigned short dport;
    unsigned short length;
    unsigned short check;
};

//udp ���ݰ�ͷ��
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




