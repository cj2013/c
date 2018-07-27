/*
 * ServerData.h
 *
 *  Created on: 2018年4月11日
 *      Author: root
 *
 *   server common data: current render process
 */

#ifndef SHM_H_
#define SHM_H_

#include <sys/types.h>
using namespace std;

int Shm_Create(char* pathName, int nProjId, size_t nSize);

int Shm_Release(int sid);



#endif /* SRC_SHM_H_ */
