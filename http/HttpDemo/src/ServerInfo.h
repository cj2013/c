/*
 * ServerInfo.h
 *
 *  Created on: 2018年4月12日
 *      Author: root
 */

#ifndef SRC_SERVERINFO_H_
#define SRC_SERVERINFO_H_

const int SERVER_PORT = 11181;
const int MAX_RENDER_NUM = 1;

//mustn't be changed, the same struct defined as go server
enum Server_State{
	Server_Disconnect, 			//断开连接
	Server_Busy,              //忙碌状态（正在合成任务）
	Server_Idle              //空闲状态，可以分配合成任务
};

class ServerInfo
{
public:
	ServerInfo();
	~ServerInfo();
	bool ToBuffer(char* pBuffer);  //save serverInfo to buffer, used for sending to control server
	void SetValue(const char* memory, const char* vmemory); //set memory and video memory information

public:
	char* 	m_pHost;
	int   m_nPort;
	int 		m_nStatus;		//get from shm
	char* 	m_pMemory;
	char* 	m_pVMemory;
};


#endif /* SRC_SERVERINFO_H_ */
