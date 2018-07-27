/*
 * Sem.h
 *
 *  Created on: 2018年4月13日
 *      Author: wang
 */

#ifndef SRC_SEM_H_
#define SRC_SEM_H_

union semun{
    int 					val;
    struct semid_ds *buf;
    unsigned short 	*array;
    struct seminfo*	buf_info;
    void*				pad;
};

int Sem_Creat(const char *pathname, int proj_id, int members, int init_val);

int Sem_Open(const char* pathName, int projId);

int Sem_P(int semId, int index);

int Sem_V(int semId, int index);

int Sem_Delete(int semId);

int Sem_Wait(int semId, int index);

#endif /* SRC_SEM_H_ */
