/*
 * thread_process.cpp
 *
 *  Created on: 2018年3月8日
 *      Author: wang
 */

#include <stdio.h>
#include <unistd.h>
#include "thread_process.h"
#include <pthread.h>

void ThreadProcess::Process0(void* arg)
{
    printf("thread %u is starting process %s\n",pthread_self(),arg);
    usleep(100*1000);
}
void ThreadProcess::Process1(void* arg)
{
    printf("thread %u is starting process %s\n",pthread_self(),arg);
    usleep(100*1000);
}

void ThreadProcess::Process2(void* arg)
{
    printf("thread %u is starting process %s\n",pthread_self(),arg);
    usleep(100*1000);
}


