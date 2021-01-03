#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define SERVER_PORT 6666

int main()
{
//调用socket函数返回的文件描述符
int serverSocket;
//声明两个套接字sockaddr_in结构体变量，分别表示客户端和服务器
struct sockaddr_in server_addr;
struct sockaddr_in clientAddr;
int addr_len = sizeof(clientAddr);
int client;
char buffer[200];
int iDataNum;
//socket函数，失败返回-1
//int socket(int domain, int type, int protocol);
//第一个参数表示使用的地址类型，一般都是ipv4，AF_INET
//第二个参数表示套接字类型：tcp：面向连接的稳定数据传输SOCK_STREAM
//第三个参数设置为0
if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
perror("socket");
return 1;
}
bzero(&server_addr, sizeof(server_addr));
//初始化服务器端的套接字，并用htons和htonl将端口和地址转成网络字节序
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(SERVER_PORT);
//ip可是是本服务器的ip，也可以用宏INADDR_ANY代替，代表0.0.0.0，表明所有地址
server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//对于bind，accept之类的函数，里面套接字参数都是需要强制转换成(struct sockaddr *)
//bind三个参数：服务器端的套接字的文件描述符，
if(bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
{
perror("connect");
return 1;
}
//设置服务器上的socket为监听状态
if(listen(serverSocket, 5) < 0)
{
perror("listen");
return 1;
}
while(1)
{
printf("监听端口: %d\n", SERVER_PORT);
client = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addr_len);
if(client < 0)
{
perror("accept");
continue;
}
printf("等待消息...\n");
printf("IP is %s\n", inet_ntoa(clientAddr.sin_addr));
printf("Port is %d\n", htons(clientAddr.sin_port));
while(1)
{
printf("读取消息:");
buffer[0] = '\0';
iDataNum = recv(client, buffer, 1024, 0);
if(iDataNum < 0)
{
perror("recv null");
continue;
}
buffer[iDataNum] = '\0';
if(strcmp(buffer, "quit") == 0)
break;
printf("%s\n", buffer);
printf("发送消息:");
scanf("%s", buffer);
printf("\n");
send(client, buffer, strlen(buffer), 0);
if(strcmp(buffer, "quit") == 0)
break;
}
}
close(serverSocket);
return 0;
}
