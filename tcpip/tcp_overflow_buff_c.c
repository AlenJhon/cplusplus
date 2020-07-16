#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>

/**
 * tcp  client 和 server 建立好连接之后， client一直往服务器发送消息，server并没有接收，
 * 最终的结果
 * netstat -anlp | grep 8080
 * tcp        0      0 0.0.0.0:8080            0.0.0.0:*               LISTEN      11609/server    
 * tcp        0      0 192.168.1.98:50677      192.168.1.87:8080       TIME_WAIT   -               
 * tcp   767311      0 127.0.0.1:8080          127.0.0.1:57255         ESTABLISHED 11609/server    
 * tcp        0      0 192.168.1.98:50678      192.168.1.87:8080       TIME_WAIT   -               
 * tcp        0 2025749 127.0.0.1:57255         127.0.0.1:8080          ESTABLISHED 11610/client    
 * tcp        0      0 127.0.0.1:57135         127.0.0.1:8080          TIME_WAIT   - 
 * client 总发送 2025749 + 767311 = 2793060
 * 767311  在server  socket buffer
 * 2025749 在client  socket buffer
 * 这个时候client继续发送消息已经发送不出去了，因为server没有接收，client的kernel buffer已经满了
 * 这个时候如果服务器开始接收，还是能接收到所有的数据，不会丢失
*/

#define CHECK_RET(rv, reason)                                                           \
    if (rv < 0)                                                                         \
    {                                                                                   \
    printf("call " #reason " failed errno:%d strerror:%s\n", errno, strerror(errno));   \
        return -1;                                                                      \
    }

#define CHECK_RET_EAGAIN(rv, reason)                                                    \
    if (rv < 0) {                                                                       \
        if (errno == EAGAIN) {                                                          \
            sleep(1);                                                                   \
            continue;                                                                   \
        }                                                                               \
        printf("call "#reason" failed errno:%d strmsg:%s\n", errno, strerror(errno));   \
        return -1;                                                                      \
    }


int main() 
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    CHECK_RET(fd, "socket");

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    int rv = connect(fd, (const struct sockaddr *)&server, sizeof(struct sockaddr));
    CHECK_RET(rv, "connect");


    char sendbuff[1024*1024*5] = {0};
    // int ncheck_tcp_send_buff_sz = 4194304; //力度太大了不便于观察
    int ncheck_tcp_send_buff_sz = 1024;
    int len = 0;
    while (len < sizeof(sendbuff) - 1 && len < ncheck_tcp_send_buff_sz)
    {
        len += snprintf(sendbuff + len, ncheck_tcp_send_buff_sz - len - 1, "<%s>", "Hello World!");
    }

    int total_send_sz = 0;
    int index = 0;

    while (1)
    {
        // if (total_send_sz >= 4194304)
        // {
        //     printf("send total_send_sz:%d stop  wait server recv buff \n", total_send_sz);
        //     getchar();

        //     rv = send(fd, "stop", 4, MSG_DONTWAIT);
        //     CHECK_RET(rv, "send stop");
        //     ncheck_tcp_send_buff_sz = 0;
        // }

        printf("send data before %d ...\n", index++);
        rv = send(fd, sendbuff, strlen(sendbuff), MSG_DONTWAIT);
        if (rv < 0) 
        {
            if (errno == EAGAIN)
            {
                printf("total_send_sz:%d send failed ...\n", total_send_sz);
                total_send_sz = 0;
                getchar();
            }
        }
        // CHECK_RET_EAGAIN(rv, "send")
        // 发送失败 缓冲区满了不结束
        total_send_sz += rv;
        printf("total_send_size: %d\n", total_send_sz);

    }
    


    return 0;
}