/*
 * RenderInfo.cpp
 *
 *  Created on: 2018年4月13日
 *      Author: wang
 */

#include "RenderInfo.h"
#include <string.h>


RenderInfo::RenderInfo()
{

}

RenderInfo::~RenderInfo()
{

}

int RenderInfo::LoadFromBuffer(void* pBuffer)
{
	int nLen = 0;
	char* pTemp = (char*)pBuffer;
	memcpy(m_guid, pTemp, 100*sizeof(char));
	pTemp = pTemp + 100 * sizeof(char);
	nLen += 100 * sizeof(char);

	pid_t *pId = (pid_t*)pTemp;
	m_pId = *pId;
	nLen += sizeof(pid_t);

	return nLen;
}

int RenderInfo::SaveToBuffer(void* pBuffer)
{
	int nLen = 0;
	char* pTemp = (char*)pBuffer;
	memcpy(pTemp, m_guid, 100 * sizeof(char));
	pTemp += 100 * sizeof(char);
	nLen += 100 * sizeof(char);

	memcpy(pTemp, &m_pId, sizeof(pid_t));
	nLen += sizeof(pid_t);
	return nLen;
}
