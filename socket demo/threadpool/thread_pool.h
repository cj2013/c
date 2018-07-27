/*
 * thread_pool.h
 *
 *  Created on: 2018年3月8日
 *      Author: wang
 */

#ifndef SERVER_THREAD_POOL_H_
#define SERVER_THREAD_POOL_H_

#include <map>
#include <vector>
#include "command.h"

const int MAX_THREAD_NUM = 50; // 该值目前需要设定为初始线程数的整数倍
const int ADD_FACTOR = 4;		 	// 该值表示一个线程可以处理的最大任务数
const int THREAD_NUM = 10; 		// 初始线程数

class ThreadPool
{
public:
    ThreadPool() {};
    static void InitializeThreads();
    void 	AddWork(Command command);
    void 	ThreadDestroy(int iwait = 2);
private:
    static void* 	Process(void* arg);
    static void 	AddThread();
    static void 	DeleteThread();
    static bool 	bshutdown_;
    static int 		icurr_thread_num_;
    static std::map<pthread_t,int> thread_id_map_;
    static std::vector<Command> 		command_;
    static pthread_mutex_t 	command_mutex_;
    static pthread_cond_t 		command_cond_;
};



#endif /* SERVER_THREAD_POOL_H_ */
