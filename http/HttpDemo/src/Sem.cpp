/*
 * Sem.cpp
 *
 *  Created on: 2018年4月13日
 *      Author: wang
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "Sem.h"

//create
int Sem_Creat(const char* pathName, int projId, int members, int init_val)
{
	key_t msgkey;
	int index, sid;
	union semun semopts;

	msgkey = ftok(pathName, projId);
	if (msgkey == -1)
	{
		perror("ftok error!\n");
		return -1;
	}
	sid = semget(msgkey, members, IPC_CREAT | 0666);
	if (sid == -1)
	{
		perror("semget call failed.\n");
		return -1;
	}
	semopts.val = init_val;
	for (index = 0; index < members; index++)
	{
		semctl(sid, index, SETVAL, semopts);
	}

	return sid;
	return -1;
}

int Sem_Open(const char* pathName, int projId)
{
	key_t msgkey;
	int sid;

	if ((msgkey = ftok(pathName, projId)) == -1)
	{
		perror("ftok error!\n");
		return -1;
	}

	if ((sid = semget(msgkey, 0, 0666)) == -1)
	{
		perror("open semget call failed.\n");
		return -1;
	}
	return sid;
}

int Sem_P(int semId, int index)
{
	struct sembuf sbuf = {0, -1, SEM_UNDO};

	//struct sembuf sbuf = { 0, -1, IPC_NOWAIT };
	if (index < 0)
	{
		perror("index of array cannot equals a minus value!\n");
		return -1;
	}
	sbuf.sem_num = index;
	if (semop(semId, &sbuf, 1) == -1)
	{
		perror("A wrong semop lin:77! \n");
		return -1;
	}
	return 0;
}

int Sem_V(int semId, int index)
{
	struct sembuf sbuf = {0, 1, SEM_UNDO};

	//struct sembuf sbuf = { 0, 1, IPC_NOWAIT };
	if (index < 0)
	{
		perror("index of array cannot equals a minus value!\n");
		return -1;
	}
	sbuf.sem_num = index;
	if (semop(semId, &sbuf, 1) == -1)
	{
		perror("A wrong operation to semaphore occurred, Line 96!\n");
		return -1;
	}
	return 0;
}

int Sem_Delete(int semId)
{
	return semctl(semId, 0, IPC_RMID);
}

int Sem_Wait(int semId, int index)
{
	while (semctl(semId, index, GETVAL, 0) == 0)
	{
		//wait_num++;
		usleep(100000);
	}
	//printf("wait_num = %x\n", wait_num);

	return 1;

}
