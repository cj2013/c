/*
 * server.cpp
 *
 *  Created on: 2018年3月7日
 *      Author: wang
 */

#include <stdio.h>
#include <iostream>
#include <unistd.h>
using namespace std;

#include "thread_pool.h"
#include "command.h"

int main() {
	ThreadPool thread_pool;
	thread_pool.InitializeThreads();
	Command command;
	char arg[8] = { 0 };
	for (int i = 1; i <= 200; ++i) {
		command.set_cmd(i % 3);
		sprintf(arg, "%d", i);
		command.set_arg(arg);
		thread_pool.AddWork(command);
	}
	sleep(30); // 用于测试线程池缩容
	thread_pool.ThreadDestroy();
	return 0;
}

