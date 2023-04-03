#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

//迷你 Web 服务器程序
int main(int argc, char* argv[])
{
	int sockfd;  //1 创建socket
	int len;
	struct sockaddr_in address; //2 创建服务器协议地址簇
	int result;
	char ch = 'A';

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) printf("创建socket失败:%m\n"), exit(-1);
	printf("创建socket成功!\n");

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET; //协议类型 和socket函数第一个参数一致 // IPv4 地址
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(4000); //端口
	len = sizeof(address);
	//3 连接服务器
	result = connect(sockfd, (struct sockaddr*)&address, len);
	if (-1 == result)printf("连接服务器失败:%m\n"), close(sockfd), exit(-2);
	printf("连接服务器成功!n");
	// 4. 通信
	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("来自服务器的: %c\n", ch);
	close(sockfd);
	exit(0);
}