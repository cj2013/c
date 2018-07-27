/*
 * ServerInfo.cpp
 *
 *  Created on: 2018年4月12日
 *      Author: root
 */

#include <stdio.h>
#include <string.h>
#include "ServerInfo.h"

ServerInfo::ServerInfo()
{
	m_nPort = SERVER_PORT;
	m_pHost = new char[40];
	memset(m_pHost, 0, 40);
	strcat(m_pHost, "172.29.4.118");
	m_pMemory = NULL;
	m_pVMemory = NULL;
}

ServerInfo::~ServerInfo()
{
	if(m_pHost != NULL)
	{
		delete[] m_pHost;
		m_pHost = NULL;
	}
	if(m_pMemory != NULL)
	{
		delete[] m_pMemory;
		m_pMemory = NULL;
	}
	if(m_pVMemory != NULL)
	{
		delete[] m_pVMemory;
		m_pVMemory = NULL;
	}
}

void ServerInfo::SetValue(const char* memory, const char* vmemory)
{
	if(memory == NULL || vmemory == NULL){
		return;
	}
	m_pMemory = new char[20];
	strcat(m_pMemory, memory);
	m_pVMemory = new char[20];
	strcat(m_pVMemory, vmemory);
}

bool ServerInfo::ToBuffer(char* pBuffer)
{
	if(pBuffer == NULL)
	{
		return false;
	}

	strcat(pBuffer, "{\r\n");
	strcat(pBuffer, "\"host\" : \"");
	strcat(pBuffer, m_pHost);
	strcat(pBuffer, "\",\r\n");

	char sPort[10];
	sprintf(sPort, "%d", m_nPort);
	strcat(pBuffer, "\"port\" : ");
	strcat(pBuffer, sPort);
	strcat(pBuffer, ",\r\n");

	char sStatus[10];
	sprintf(sStatus, "%d", m_nStatus);
	strcat(pBuffer, "\r\"status\" : ");
	strcat(pBuffer, sStatus);
	strcat(pBuffer, ",\r\n");

	strcat(pBuffer, "\r\"memory\" : \"");
	strcat(pBuffer, m_pMemory);
	strcat(pBuffer, "\",\r\n");

	strcat(pBuffer, "\r\"vmemory\" : \"");
	strcat(pBuffer, m_pVMemory);
	strcat(pBuffer, "\"\r\n");

	strcat(pBuffer, "}\r\n");
	return true;
}

