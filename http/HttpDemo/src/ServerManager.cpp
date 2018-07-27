/*
 * ServerManager.cpp
 *
 *  Created on: 2018年4月13日
 *      Author: wang
 *
 *   share memory save data: int serverStatus; int renderSize; vector<RenderInfo*> vecRenderInfo
 */
#include "Shm.h"
#include "Sem.h"
#include "RenderInfo.h"
#include "ServerManager.h"
#include <iostream>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
using namespace std;

const int SHM_SIZE = 1024;

ServerManager::ServerManager()
{
	m_pServerInfo = new ServerInfo();
	m_nShmId = -1;
	m_nSemId = -1;
	Init();

	//idle
	SaveServerStatus(Server_Idle);
}

ServerManager::~ServerManager()
{
	if(m_pServerInfo != NULL)
	{
		delete m_pServerInfo;
		m_pServerInfo = NULL;
	}
	Sem_Delete(m_nSemId);
	Shm_Release(m_nShmId);
}

bool  ServerManager::Init()
{
	char write_str[SHM_SIZE];
	char *ret;
	m_nShmId = Shm_Create(".", 57, SHM_SIZE);
	if(m_nShmId == -1) //创建或者获取共享内存
	{
		return false;
	}

	m_nSemId = Sem_Creat("./", 39, 1, 1);
	if(m_nSemId == -1)//创建信号量
	{
		return false;
	}
	return true;
}

int	ServerManager::GetServerStatus()
{
	int nRes = -1;
	char* shmaddr = (char*)shmat(m_nShmId, (char*)0, 0);
	if(shmaddr == (char*)-1)
	{
		return nRes;
	}

	//read share memory
	Sem_Wait(m_nSemId, 0);	//等待信号量可以被获取
	if(Sem_P(m_nSemId, 0) == -1)
	{
		shmdt(shmaddr);
		return nRes;
	}

	int *pRes = (int*)shmaddr;
	if(pRes != NULL)
	{
		nRes = *pRes;
	}

	shmdt(shmaddr);

	//close
	Sem_V(m_nSemId, 0);
	return nRes;
}

int	ServerManager::SaveServerStatus(int nStatus)
{
	int nRes = -1;
	char* shmaddr = (char*)shmat(m_nShmId, (char*)0, 0);
	if(shmaddr == (char*)-1)
	{
		return nRes;
	}

	//read share memory
	Sem_Wait(m_nSemId, 0);	//等待信号量可以被获取
	if(Sem_P(m_nSemId, 0) == -1)
	{
		shmdt(shmaddr);
		return nRes;
	}

	memcpy(shmaddr, &nStatus, sizeof(int));

	shmdt(shmaddr);

	//close
	Sem_V(m_nSemId, 0);
	return true;
}

bool  ServerManager::GetRenderInfoVec(vector<RenderInfo*>& vecRenderInfo)
{
	char* shmaddr = (char*)shmat(m_nShmId, (char*)0, 0);
	if(shmaddr == (char*)-1)
	{
		return false;
	}

	//read share memory
	Sem_Wait(m_nSemId, 0);	//等待信号量可以被获取
	if(Sem_P(m_nSemId, 0) == -1)
	{
		shmdt(shmaddr);
		return false;
	}

	char* pTemp = shmaddr;

	//status
	pTemp += sizeof(int);

	int* pSize = (int*)pTemp;
	int nRerderInfoSize = *pSize;
	pTemp += sizeof(int);

	for(int i = 0; i < nRerderInfoSize; i++){
		RenderInfo* pRenderInfo = new RenderInfo();
		int nLen = pRenderInfo->LoadFromBuffer(pTemp);
		vecRenderInfo.push_back(pRenderInfo);
		pTemp += nLen;
	}

	//close
	shmdt(shmaddr);
	Sem_V(m_nSemId, 0);
	return true;
}

bool  ServerManager::SaveRenderInfoVec(vector<RenderInfo*>& vecRenderInfo)
{
	char* shmaddr = (char*)shmat(m_nShmId, (char*)0, 0);
	if(shmaddr == (char*)-1)
	{
		return false;
	}

	//read share memory
	Sem_Wait(m_nSemId, 0);	//等待信号量可以被获取
	if(Sem_P(m_nSemId, 0) == -1)
	{
		shmdt(shmaddr);
		return false;
	}

	char* pTemp = shmaddr;

	int nSize = (int)vecRenderInfo.size();
	if (nSize == MAX_RENDER_NUM)
	{
		m_pServerInfo->m_nStatus = Server_Busy;
	}
	else
	{
		m_pServerInfo->m_nStatus = Server_Idle;
	}

	//save status
	memcpy(pTemp, &m_pServerInfo->m_nStatus, sizeof(int));
	pTemp += sizeof(int);

	memcpy(pTemp, &nSize, sizeof(int));
	pTemp += sizeof(int);

	for(int i = 0; i < nSize; i++)
	{
		RenderInfo* pInfo = (RenderInfo*)vecRenderInfo.at(i);
		int nLen = pInfo->SaveToBuffer(pTemp);
		pTemp += nLen;
	}

	//close
	shmdt(shmaddr);
	Sem_V(m_nSemId, 0);
	return true;
}

bool	ServerManager::SetServerInfo(const char* pMemory, const char* pVMemory)
{
	if(m_pServerInfo == NULL){
		return false;
	}
	m_pServerInfo->SetValue(pMemory, pVMemory);
	return true;
}

bool ServerManager::GetServerInfoBuffer(char* pBuffer)
{
	return m_pServerInfo->ToBuffer(pBuffer);
}

void  ServerManager::UpdateServerStatus()
{
	int nSatus = GetServerStatus();
	m_pServerInfo->m_nStatus = nSatus;
}

bool  ServerManager::IsRenderValid()
{
	int nState = GetServerStatus();
	if(nState == Server_Idle){
		return true;
	}
	return false;
}

pid_t ServerManager::GetRenderPid(const char* guid)
{
	vector<RenderInfo*> vecRenderInfo;
	GetRenderInfoVec(vecRenderInfo);
	vector<RenderInfo*>::iterator iter = vecRenderInfo.begin();
	for(; iter != vecRenderInfo.end(); iter++){
		RenderInfo* pInfo = *iter;
		if(strcmp(guid, pInfo->m_guid) == 0){
			return pInfo->m_pId;
		}
	}
	return -1;
}

char* ServerManager::GetRenderGuid(pid_t pid)
{
	vector<RenderInfo*> vecRenderInfo;
		GetRenderInfoVec(vecRenderInfo);
		vector<RenderInfo*>::iterator iter = vecRenderInfo.begin();
		for(; iter != vecRenderInfo.end(); iter++){
			RenderInfo* pInfo = *iter;
			if(pid == pInfo->m_pId){
				return pInfo->m_guid;
			}
		}
		return NULL;
}

//when begin to render, update renderinfo to share memory, meanwhile, update server status
bool  ServerManager::UpdateRenderInfo(RenderInfo* pRenderInfo)
{
	//get current render info vector
	vector<RenderInfo*> vecRender;
	GetRenderInfoVec(vecRender);

	vector<RenderInfo*>::iterator iter = vecRender.begin();
	for(; iter != vecRender.end(); iter++)
	{
		RenderInfo* pInfo = *iter;
		if(strcmp(pInfo->m_guid, pRenderInfo->m_guid) == 0)
		{
			//task has this guid already exist,there must be something wrong
			return false;
		}
	}

	vecRender.push_back(pRenderInfo);

	//save vecRender, modify server status
	SaveRenderInfoVec(vecRender);

	return true;
}

bool  ServerManager::RemoveRenderInfo(pid_t pid)
{
		vector<RenderInfo*> vecRender;
		GetRenderInfoVec(vecRender);

		vector<RenderInfo*>::iterator iter = vecRender.begin();
		for(; iter != vecRender.end(); iter++)
		{
			RenderInfo* pInfo = *iter;
			if(pInfo->m_pId == pid)
			{
				vecRender.erase(iter);
				delete pInfo;
				pInfo = NULL;
				SaveRenderInfoVec(vecRender);
				return true;
			}
		}
	return false;
}

bool 	ServerManager::OutPutAll()
{
	char* shmaddr = (char*)shmat(m_nShmId, (char*)0, 0);
		if(shmaddr == (char*)-1)
		{
			return false;
		}

		//read share memory
		Sem_Wait(m_nSemId, 0);	//等待信号量可以被获取
		if(Sem_P(m_nSemId, 0) == -1)
		{
			shmdt(shmaddr);
			return false;
		}

		char* pTemp = shmaddr;

		//status
		int* pStatus = (int*)pTemp;
		cout << "server status: " << *pStatus << endl;
		pTemp += sizeof(int);

		int* pSize = (int*)pTemp;
		int nRerderInfoSize = *pSize;
		cout << "render info size:" << nRerderInfoSize << endl;
		pTemp += sizeof(int);

		for(int i = 0; i < nRerderInfoSize; i++){
			RenderInfo* pRenderInfo = new RenderInfo();
			int nLen = pRenderInfo->LoadFromBuffer(pTemp);
			cout << "render info guid: " << pRenderInfo->m_guid << endl;
			cout << "render info pid: " << pRenderInfo->m_pId << endl;
			pTemp += nLen;
		}

		//close
		shmdt(shmaddr);
		Sem_V(m_nSemId, 0);
		return true;
}






