/*
 * server.cpp
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

void doAcc(int sock)
{
	char buffer[4096];
	int n = recv(sock, buffer, MAXLINE, 0);
	buffer[n] = '\0';
	printf("receive message:%s", buffer);

	n = write(sock,"I got your message",18);
 if (n < 0)
  {
	 printf("ERROR writing to socket");
	}
}

int main(int argc, char** argv) {
	int listenfd, connfd;
	sockaddr_in servaddr;
	char buffer[4096];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd == -1) {
		printf("create socket error: %s(errno:%d)", strerror(errno), errno);
		exit(0);
	}

	memset(&servaddr, 0, sizeof(sockaddr_in));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);

	int bd = bind(listenfd, (struct sockaddr*) (&servaddr), sizeof(servaddr));
	if (bd == -1) {
		printf("bind socket error:%s (errorno:%d)", strerror(errno), errno);
		exit(0);
	}

	if(listen(listenfd, 10) == -1)
	{
		printf("listen socket error:%s(errno:%d)", strerror(errno), errno);
		exit(0);
	}

	printf("------begin receive-------:\n");
	while(true)
	{
		int accfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
		if(accfd == -1)
		{
			printf("accect error:%s (errno:%d)", strerror(errno), errno);
			continue;
		}

		int pid = fork();
		if(pid < 0)
		{
			printf("fork error");
		}
		else if(pid == 0){
			close(listenfd);
			doAcc(accfd);
			exit(0);
		}
		else{
			close(accfd);
		}
	}
	close(listenfd);
}

