/*
 * RenderInfo.h
 *
 *  Created on: 2018年4月13日
 *      Author: wang
 */

#ifndef SRC_RENDERINFO_H_
#define SRC_RENDERINFO_H_

#include <sys/types.h>

class RenderInfo{
public:
	RenderInfo();
	~RenderInfo();
	int LoadFromBuffer(void* pBuffer);
	int SaveToBuffer(void* pBuffer);
public:
	char m_guid[100];	//program guid,used to stop and send feedback message to control server
	pid_t m_pId;     	//render process id
};



#endif /* SRC_RENDERINFO_H_ */
