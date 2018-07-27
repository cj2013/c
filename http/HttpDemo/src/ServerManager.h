/*
 * ServerManager.h
 *
 *  Created on: 2018年4月13日
 *      Author: wang
 */

#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "ServerInfo.h"
#include "Sem.h"
#include "Shm.h"
#include "RenderInfo.h"
#include <vector>
using namespace std;

class ServerManager
{
public:
	ServerManager();
	~ServerManager();

	bool  	Init();
	int		GetServerStatus();
	bool  	GetRenderInfoVec(vector<RenderInfo*>& vecRenderInfo);
	bool  	SaveRenderInfoVec(vector<RenderInfo*>& vecRenderInfo);
	bool		SetServerInfo(const char* pMemory, const char* pVMemory);

	//可能别的进程修改了服务器状态，需要从共享内存更新
	void  UpdateServerStatus();

	bool  GetServerInfoBuffer(char* pBuffer);

	bool  IsRenderValid();
	pid_t GetRenderPid(const char* guid);
	char* GetRenderGuid(pid_t pid);

	//when begin to render, update renderinfo to share memory, meanwhile, update server status
	bool  UpdateRenderInfo(RenderInfo* pRenderInfo);
	bool  RemoveRenderInfo(pid_t pid);
	int		SaveServerStatus(int nStatus);

	bool 	OutPutAll();

private:
	ServerInfo*		m_pServerInfo;
	int				m_nShmId;
	int				m_nSemId;

};

#endif


