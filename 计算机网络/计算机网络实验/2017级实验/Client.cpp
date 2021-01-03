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
int clientSocket;
struct sockaddr_in serverAddr;
char sendbuf[200];
char recvbuf[200];
int iDataNum;
if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
perror("socket");
return 1;
}
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(SERVER_PORT);
serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
{
perror("connect");
return 1;
}
printf("连接到主机...\n");
while(1)
{
printf("发送消息:");
scanf("%s", sendbuf);
printf("\n");
send(clientSocket, sendbuf, strlen(sendbuf), 0);
if(strcmp(sendbuf, "quit") == 0)
break;
printf("读取消息:");
recvbuf[0] = '\0';
iDataNum = recv(clientSocket, recvbuf, 200, 0);
recvbuf[iDataNum] = '\0';
printf("%s\n", recvbuf);
}
close(clientSocket);
return 0;
}
