/*
 * ServerData.cpp
 *
 *  Created on: 2018年4月11日
 *      Author: root
 */

//values : server state, current guid pid array

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <vector>
#include "Shm.h"
using namespace std;

const int MAX_RENDER_PROCESS = 1;

struct RenderInfo {
	char guid[100];	//program guid,used to stop and send feedback meg to control server
	pid_t pId;     	//process id
};

vector<RenderInfo*> g_vecRender;

int Shm_Create(char* pathName, int nProjId, size_t nSize)
{
	key_t shmkey = ftok(pathName, nProjId);

	if(shmkey == -1){
		perror("ftok error!\n");
		return -1;
	}
	int sid = shmget(shmkey, nSize, IPC_CREAT | 0666);
	if(sid == -1){
		perror("shm call failed!\n");
		return -1;
	}
	return sid;
}

int Shm_Release(int sid)
{
	int nRes = shmctl(sid, IPC_RMID, NULL);
	return nRes;
}

bool IsRenderValid() {
	int nSize = (int) g_vecRender.size();
	if (nSize < MAX_RENDER_PROCESS) {
		return true;
	}
	return false;
}

bool RemoveFromRenderArray(pid_t pId)
{
	vector<RenderInfo*>::iterator iter = g_vecRender.begin();
	for(; iter != g_vecRender.end(); iter++)
	{
		RenderInfo* pInfo = *iter;
		if(pInfo->pId == pId)
		{
			g_vecRender.erase(iter);
			delete pInfo;
			pInfo = NULL;
			return true;
		}
	}
	return false;
}

pid_t GetPidFromRender(string guid)
{
	vector<RenderInfo*>::iterator iter = g_vecRender.begin();
	for(; iter != g_vecRender.end(); iter++)
	{
		RenderInfo* pInfo = *iter;
		if(pInfo->guid == guid)
		{
			return pInfo->pId;
		}
	}
	return -1;
}

