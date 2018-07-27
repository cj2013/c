/*
 * main.cpp
 *
 *  Created on: 2018年3月9日
 *      Author: wang
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>

//使用select函数实现TCP并发服务器

#define N 128

#define errlog(errmsg) do{perror(errmsg); exit(1);}while(0)

int main(int argc, const char *argv[]) {
	int sockfd;
	struct sockaddr_in serveraddr, clientaddr;
	int acceptfd;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	fd_set readfds;
	int maxfd;

	fd_set tempfds;

	int i = 0;

	char buf[N] = { };

	//创建套接字
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		errlog("fail to socket");
	}

	//填充网络信息结构体
	//inet_addr 将点分十进制转化成网络字节
	//htons表示将主机字节序转化成网络字节序
	//atoi 将字符串转化成整型数据
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(6666);

	//将套接字与IP地址和端口号绑定
	if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
		errlog("fail to bind");
	}

	//将套接字设置为被动监听状态
	if (listen(sockfd, 10) < 0) {
		errlog("fail to listen");
	}

	//第一步：清空集合
	FD_ZERO(&readfds);

	//第二步：将文件描述符添加到集合当中
	//注意：当select函数调用成功后，他会清除没有准备就绪的文件描述符，所以需要每次重复添加
	FD_SET(sockfd, &readfds);

	maxfd = sockfd;

	while (1) {
		tempfds = readfds;

		//第三步：调用select函数将添加进去的文件描述符准备就绪
		if (select(maxfd + 1, &tempfds, NULL, NULL, NULL) < 0) //此处若不用第三方tempfds代替的话，select执行后会将集合中没有准备就绪的
				//文件描述符删除
		{
			errlog("fail to select");
		}

		//使用FD_ISSET判断文件描述符
		for (i = 0; i < maxfd + 1; i++) {
			if (FD_ISSET(i, &tempfds) == 1)      //
			{
				if (i == sockfd) {
					//接收客户端的连接请求
					if ((acceptfd = accept(sockfd, (struct sockaddr *) &clientaddr, &addrlen)) < 0) {
						errlog("fail to accept");
					}

					printf("%s ---> %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

					FD_SET(acceptfd, &readfds);

					maxfd = maxfd > acceptfd ? maxfd : acceptfd;

				} else {

					if (recv(i, buf, N, 0) < 0) {
						errlog("fail to recv");
					}

					if (strncmp(buf, "quit", 4) == 0) {
						printf("%s is quited...\n",
								inet_ntoa(clientaddr.sin_addr));
						break;
					} else {
						printf("from client >>> %s\n", buf);

						strcat(buf, " from server...");

						send(i, buf, N, 0);

					}
				}
			}
		}
	}

	close(sockfd);
	close(acceptfd);
	return 0;
}

