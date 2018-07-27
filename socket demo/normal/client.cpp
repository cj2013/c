/*
 * clint.cpp
 *
 *  Created on: 2018年3月7日
 *      Author: wang
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>
#include <fcntl.h>

#define MAXLINE 4096

int main(int argc, char** argv)
{
	int sockfd;
	char buffer[MAXLINE];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("socket error: %s(errno:%d)", strerror(errno), errno);
		exit(0);
	}

	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(6666);
	int confd = connect(sockfd, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	if(confd == -1)
	{
		printf("connect error:%s(errno:%d)", strerror(errno), errno);
		exit(0);
	}

	printf("msg to send:\n");
	fgets(buffer, MAXLINE, stdin);

	int n = send(sockfd, buffer, strlen(buffer), 0);
	if (n == -1)
	{
		printf("send data error:%s", strerror(errno));
		exit(0);
	}
	n = read(sockfd, buffer, MAXLINE);
	if(n > 0)
	{
		printf("recv:%s\n", buffer);
	}
	close(sockfd);
	exit(0);
}

