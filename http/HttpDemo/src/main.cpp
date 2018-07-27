/*
 * main.cpp
 *
 *  Created on: 2018年3月21日
 *      Author: wang
 */
#include <stdio.h>
#include <string>
#include <iostream>
#include <signal.h>

#include "log.h"

#include "address.h"
#include "tcpserver.h"

#include "connection.h"

#include "httpserver.h"
#include "httprequest.h"
#include "httpresponse.h"
#include "httpconnection.h"

#include "httpclient.h"
#include "ioloop.h"
#include "stringutil.h"

#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include <pthread.h>

#include "ServerInfo.h"
#include "ServerManager.h"
#include "wlog.h"

using namespace std;
using namespace tnet;
using namespace std::placeholders;

const int MAX_RENDER_PROCESS = 4;	//max number of render process
const string SERVER_STATUS_URL="http://172.29.4.118:8090/server/status";
const string RENDER_PATH="/mnt/hgfs/ShareFile/C/Render/crender";

ServerManager* g_pServerManager = NULL;

void WaitRenderProcess();

void onResponse(IOLoop* loop, const HttpResponse& resp)
{
   cout << resp.statusCode << endl;
   //cout << resp.body.size() << endl << endl;
   loop->stop();
}

//send server information
void* StatusThread(void *ptr) {
	int nSize = 200;
	char* pBuffer = (char*)malloc(nSize);
	while (true) {
		memset(pBuffer, 0, nSize * sizeof(char));
		g_pServerManager->SetServerInfo("40%", "20%");
		g_pServerManager->UpdateServerStatus();
		bool bRes = g_pServerManager->GetServerInfoBuffer(pBuffer);
		if(!bRes)
		{
			continue;
		}

		IOLoop loop;
		HttpClientPtr_t client = std::make_shared<HttpClient>(&loop);
		Headers_t header;
		client->request(SERVER_STATUS_URL, header, pBuffer, std::bind(&onResponse, &loop, _1));
		loop.start();
		sleep(1);
	}
	free(pBuffer);
	return 0;
}

//parse input params,if two param: first filepath, the second is guid
//if one param: guid only
void parseQuery(string query, vector<string>& result) {
	string sep1 = "&";
	string sep2 = "=";

	vector<string> args = StringUtil::split(query, sep1);

	string key;
	string value;
	for (size_t i = 0; i < args.size(); ++i) {
		vector<string> p = StringUtil::split(args[i], sep2);
		if (p.size() == 2) {
			key = p[0];
			value = p[1];
			result.push_back(value);
		} else {
			continue;
		}
	}
}

//callback when recieve task request
void onTaskHandler(const HttpConnectionPtr_t& conn,const HttpRequest& request)
{
	//request.query:  url=http://***/*/*/*/program.st&guid=fdafdfadf
	//pasture
	wlog_open("log.txt");
	wlog_write("on task handler");
	wlog_write(request.query.c_str());
	vector<string> queryRes;
	parseQuery(request.query, queryRes);
	int nSize = (int)queryRes.size();
	if(nSize != 2)
	{
		HttpResponse resp;
		resp.statusCode = 200;
		resp.setContentType("text/html");
		resp.setKeepAlive(true);
		resp.enableDate();
		resp.body.append("参数错误");
		conn->send(resp);
		queryRes.clear();
		return;
	}
	for (int i = 0; i < (int) queryRes.size(); i++) {
		//cout << (string) queryRes[i] << endl;
	}

	//check if can do render, if can't return notify
	bool bValid = g_pServerManager->IsRenderValid();
	cout << "is valid :" << bValid << endl;


	char szvalid[10];
	sprintf(szvalid, "is valid:%d", bValid);
	wlog_write(szvalid);
	wlog_close();

	if(!bValid)
	{
		HttpResponse resp;
		resp.statusCode = 200;
		resp.setContentType("text/html");
		resp.setKeepAlive(true);
		resp.enableDate();
		resp.body.append("服务器忙，请稍后重试");
		conn->send(resp);
		queryRes.clear();
		return;
	}

	//vector queryRes has two element, the first is the task's url, the second is task's guid
	//task begin
	pid_t pid = fork();
	switch (pid) {
		case -1:
		{
			cout << "fork failed" << endl;
			break;
		}
		case 0:
		{
			cout << "Child, ps Begin\n" << endl;
			HttpResponse resp;
				resp.statusCode = 200;
				resp.setContentType("text/html");
				resp.setKeepAlive(true);
				resp.enableDate();
				resp.body.append("success");
				conn->send(resp);
				queryRes.clear();
			execlp(RENDER_PATH.c_str(), "/mnt/hgfs/ShareFile/C/Render/crender", queryRes[0].c_str(), queryRes[1].c_str(), (char*) 0);
			return;
		}
		default:
		{
			//begin to render, get render process pid, save to share memary,meanwhile,update server status
			RenderInfo* pInfo = new RenderInfo;
			sprintf(pInfo->m_guid, "%s", queryRes[1].c_str());
			pInfo->m_pId = pid;
			//这是在父进程中，输出相关提示信息
			g_pServerManager->UpdateRenderInfo(pInfo);
			delete pInfo;
			pInfo = NULL;
			g_pServerManager->OutPutAll();
			cout << "Parent, ps Done\n" << endl;
			break;
		}
	}

	HttpResponse resp;
	resp.statusCode = 200;
	resp.setContentType("text/html");
	resp.setKeepAlive(true);
	resp.enableDate();
	resp.body.append("success");
	conn->send(resp);
	queryRes.clear();
	if(pid != 0){
		WaitRenderProcess();
	}
}

void onTaskCancelHandler(const HttpConnectionPtr_t& conn,const HttpRequest& request)
{
	cout << "cancel cancel canvel cancel" << endl;
	vector<string> queryRes;
	parseQuery(request.query, queryRes);
	int nSize = (int)queryRes.size();
	if(nSize != 1)
	{
		queryRes.clear();
		HttpResponse resp;
		resp.statusCode = 200;
		resp.setContentType("text/html");
		resp.setKeepAlive(true);
		resp.enableDate();
		cout << "cancel 参数错误" << endl;
		resp.body.append("参数错误");
		conn->send(resp);
		return;
	}

	string guid = queryRes[0];
	int pId = g_pServerManager->GetRenderPid(guid.c_str());
	cout <<"cancel pid:" <<  pId << endl;
	if(pId > 0)
	{
		//send cancel message to render process
		int killRes = kill(pId, SIGKILL);
		cout << "kill Res:" << killRes << endl;
	}

	queryRes.clear();
	HttpResponse resp;
	resp.statusCode = 200;
	resp.setContentType("text/html");
	resp.setKeepAlive(true);
	resp.enableDate();
	resp.body.append("success");
	conn->send(resp);
}

void onQuitResponse(IOLoop* loop, const HttpResponse& resp)
{
    cout << resp.statusCode << endl;
    loop->stop();
}

void Sub_quit_signal_handle(int sig) {
	int status;
	//获取退出的那个子进程的状态
	int quit_pid = wait(&status);
	printf("sub process %d quit, exit status %d\n", quit_pid, status);

	//send message to server
	if(status == 0)
	{
		//finish nromal
	}
	else
	{
		//fault occor
	}

	//get guid
	cout << "out put all line 271" << endl;
	g_pServerManager->OutPutAll();
	char* guid = g_pServerManager->GetRenderGuid(quit_pid);
	if(guid != NULL)
	{
		 IOLoop loop;
		 HttpClientPtr_t client = std::make_shared<HttpClient>(&loop);
		 string strGuid = guid;
		 string url = "http://172.29.4.118:8090/task/taskfinish?guid=" + strGuid;
		 client->request(url, std::bind(&onQuitResponse, &loop, _1));
		 loop.start();
	}

	g_pServerManager->RemoveRenderInfo(quit_pid);
	cout << "out put all line 285" << endl;
	g_pServerManager->OutPutAll();
	return;
}

void WaitRenderProcess() {
	signal(SIGCHLD, Sub_quit_signal_handle);
	while (1) {
		pause();
	}
}

int main() {
	g_pServerManager = new ServerManager();
	pthread_t thStatus;
	pthread_create(&thStatus, NULL, StatusThread, NULL);
	Log::rootLog().setLevel(Log::ERROR);

	TcpServer s;

	HttpServer httpd(&s);

	httpd.setHttpCallback("/task", std::bind(&onTaskHandler, _1, _2));
	httpd.setHttpCallback("/task/cancel",std::bind(&onTaskCancelHandler, _1, _2));

	httpd.listen(Address(SERVER_PORT));

	s.setMaxIdleTimeout(1);				//time out:1 minute
	s.start(MAX_RENDER_PROCESS);		//muliti process

	pthread_join(thStatus, NULL);

	delete g_pServerManager;
	g_pServerManager = NULL;
	return 0;
}

