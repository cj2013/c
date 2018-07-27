/**
 * Simple example app using Chromium Embedded Framework
 * Lassi Maksimainen, 2014
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <memory>
#include "include/cef_app.h"
#include "OffscreenBrowserApp.h"
#include "OffscreenBrowserClient.h"
#include "wlog.h"

int testmain(int argc, char** argv);
int main(int argc, char** argv)
{
	pid_t fpid; 	//fpid表示fork函数返回的值
	fpid=fork();
	if(fpid > 0)
	{
		//int k = 0;
		//const char* pName = "argvext";
		//char* pp = const_cast<char*>(pName);

		//char** p = &pp;
		testmain(argc, argv);
	}
	else if(fpid < 0)
	{
		sleep(2);
	}
	else
	{
		return  0;
	}
}

// Entrypoint to the whole application
int testmain(int argc, char** argv) {
	wlog_open("osrrender.log");


	if(true)
	{
		std::cout << "init" << std::endl << std::flush;
		CefRefPtr<OffscreenBrowserApp> app = new OffscreenBrowserApp();
			CefMainArgs main_args(argc, argv);
			int exit_code = CefExecuteProcess(main_args, app.get(), nullptr);
			//wlog_write("CefExecuteProcess");
			if (exit_code >= 0) {
				return exit_code;
			}
			// Initialize the app without sandbox on for simplicity and cookies & page cache turned off
			CefSettings settings;
			settings.windowless_rendering_enabled = true;
			settings.single_process = false;
			settings.no_sandbox = true;
			settings.persist_session_cookies = false;
			//settings.multi_threaded_message_loop=false;


			CefString(&settings.user_agent).FromASCII("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/38.0.2125.104 Safari/537.36");
			CefString(&settings.cache_path).FromASCII("");
			CefInitialize(main_args, settings, app.get(), nullptr);
	}

	CefRefPtr<OffscreenBrowserClient> client = new OffscreenBrowserClient();
	CefWindowInfo info;
	info.SetAsWindowless(0, true);
	CefBrowserSettings browser_settings;
	browser_settings.plugins = STATE_DISABLED;
	CefRefPtr<CefBrowser> browser = CefBrowserHost::CreateBrowserSync(info, client.get(), "http://www.baidu.com", browser_settings, NULL);

	while (!client->GetBrowser()) {
		usleep(10000);
	}

		// Parse command line parameters
		//std::string url;
		//url="file:///home/wang/preview03.html";

		std::string url;
		CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();
		//url = command_line->GetSwitchValue("url");
		url="file:///home/wang/preview03.html";

		std::string output = "true"; //command_line->GetSwitchValue("output");
		if (output.compare("true") == 0)
		{
			client->SetOutput(true);
		}

		// Start loading web page, wait for 10 seconds to ensure that javascript etc have been succesfully executed and then terminate load
		client->GetBrowser()->GetMainFrame()->LoadURL(url);
		while(true)
		{
			CefDoMessageLoopWork();
			usleep(40 * 1000);
		}
		client->GetBrowser()->StopLoad();
		CefDoMessageLoopWork();
		CefShutdown();
		wlog_close();
		return 0;
}
