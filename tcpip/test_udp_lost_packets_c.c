
#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

/*
 * 测试目的：UDP协议 将接收端的缓冲区填满了数据是会被丢弃吗？ 这是最初写改测试用例的意图，
 * 在测试过程中一步步的发现其它的问题，也矫正了已有的一些认知同时认识了很多新的东西
 * 思考调试代码变迁的过程并没有记录下来，只是记录最终的结果状态
 * 
 * 数据流向 ：
 * 用户数据 app -> socket buff -> udp / ip -> kernel -> nic -> internet -> nic -> kernel -> udp /ip -> socket buff -> app
 * 
 * 内核缓冲 tcp udp 共用
 * cat /proc/sys/net/core/rmem_default  (212992 测试机中大小)
 * cat /proc/sys/net/core/wmem_default  (212992)
 * 
 * 协议栈中缓冲区大小  
 * cat /proc/sys/net/ipv4/udp_mem 
 * 92406 123210	184812  
 * 
 * 
 * 测试方法 ：让client发送字节超过预期的字节数，这个过程中服务器不接收，等client都发送完了再接收，收到的字节确实是小于发送的字节
 * 
 * 参考网址
 * https://blog.csdn.net/xingzheouc/article/details/49946191
 * https://ref.onixs.biz/lost-multicast-packets-troubleshooting.html
 * 
 * 查看网卡缓冲区是否溢出
 * netstat -i udp <NIC>   =  netstat -i udp eth1
 * RX-DRP列显示网卡丢失的数据包个数
 * 
 * 查看系统缓冲区溢出
 * cat /proc/net/snmp |grep -w Udp
 * InErrors 列显示操作系统UDP队列溢出时丢失的UDP数据包总个数
 * wath -d "cat /proc/net/snmp |grep -w Udp"   实时监测查看
 * 
 * 查看应用程序socket缓冲区溢出
 * cat /proc/net/snmp |grep -w Udp 
 * RcvBufErrors 列显示当应用程序socket缓冲区溢出时丢失的UDP数据包的总个数
*/

//一下这几个宏没有具体的含义 只是一个定义在下面程序中使用而且,并不代表什么
#define MAX_INET4_DEFAULT_SEND_BUFF_SIZE 16384
#define MAX_INET4_DEFAULT_RECV_BUFF_SIZE 87380
#define MAX_INET4_DEFAULT_UDP_SEND_BUFF_SIZE 123210

// ipv4 UDP协议中udp长度使用的16位记录 最大是65535
#define MAX_INET4_UDP_HEAD_DEF_SIZE 65535

int main() {

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("create socket failed .");
        return -1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    // server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_addr.s_addr = INADDR_ANY; // /* Address to accept any incoming messages. */
    server.sin_port = htons(8080);

    int ret = connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr));
    if (ret < 0) {
        perror("connect failed .");
        close(fd);
        exit(1);
    }

    // get recv buff size
    int buff_size = -1;
    socklen_t optlen = sizeof(buff_size);
    if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buff_size, &optlen) < 0) {
        printf("getsockopt error=%d strerror:%s", errno, strerror(errno));
        exit(1);
    }
    printf("current recv buff size=%d\n", buff_size);

#if 0
    // set ================================================================
    // getsockopt 
    // 获取  /proc/sys/net/core/wmem_default   /proc/sys/net/core/rmem_default   文件中设置的数值
    // setsockopt 并不会去修改 wmem_default / rmem_default 文件中的数值  只是针对本调用程序
    buff_size *= 2;
    optlen =  sizeof(buff_size);
    if (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buff_size, optlen) < 0)
    {
        printf("getsockopt error=%d strerror:%s", errno, strerror(errno));
        exit(1);
    }
    buff_size = -1;
    optlen = sizeof(buff_size);
    if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buff_size, &optlen) < 0)
    {
        printf("getsockopt error=%d strerror:%s", errno, strerror(errno));
        exit(1);
    }
    printf("current recv buff size=%d\n", buff_size);
    // end set ============================================================
#endif


    buff_size = -1;
    if (getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buff_size, &optlen) < 0)
    {
        printf("getsockopt error=%d strerror:%s", errno, strerror(errno));
        exit(1);
    }
    printf("current send buff size=%d\n", buff_size);

    char sendbuff[100 * 1024] = {0};
    // char recvbuff[1024] = {0};
    int i = 1, len, total_send_size = 0;
    len = 0;

    // 每次发送的自己必须小于 65535
    // int ncheck_upd_send_buff_sz = MAX_INET4_UDP_HEAD_DEF_SIZE - 100;
    int ncheck_upd_send_buff_sz = (1024 * 90) / 2; // 180 * 1024 ~  184812  //  90 * 1024 = 92160 > 65535 //  92160 / 2 = 46080 < 65535 ok
    while (len < sizeof(sendbuff) - 1 && len < ncheck_upd_send_buff_sz)
    {
        // sizeof(sendbuff) > MAX_INET4_DEFAULT_SEND_BUFF_SIZE
        len += snprintf(sendbuff + len, ncheck_upd_send_buff_sz - len - 1, "<%s>", "Hello World!");
    }

    while(1) {

        int will_send_count = strlen(sendbuff);

        /* 
         * 把接收端的 接收缓冲区填充满了，停止发送
         *  cat /proc/sys/net/ipv4/udp_mem  = 92406	123210	184812
         *  cat /proc/sys/net/core/rmem_default  = 212992
         * 有两个缓冲区值
         * 在这个测试过程中没有发现网卡的硬件缓冲区溢出情况，所以就没有考虑在内了
         */
        buff_size = 184812; // udp_mem 第三列的值 猜测是受这个值限制，其它地方的限制大小都比这个大
        if (total_send_size + will_send_count >= buff_size)
        {
            printf("total_send_size=%d\n", total_send_size);
            printf("getchar stop proccess .\n");
            getchar();
        }

        ret = sendto(fd, sendbuff, strlen(sendbuff), 0, (struct sockaddr *)&server, sizeof(server));
        if ( ret < 0 ) {
            perror("sendto failed .");
            close(fd);
            exit(1);
        }
        printf("sendto len=%u , while count = %d \n", ret, i);
        total_send_size += ret;
        i += 1;
        // sleep(1);
    }
    close(fd);

    return 0;
}