/*
 * OffscreenBrowserApp.cpp
 *
 *  Created on: 2017年3月22日
 *      Author: root
 */


#include <iostream>
#include <string>
#include "OffscreenBrowserApp.h"

// Constructor
OffscreenBrowserApp::OffscreenBrowserApp() : CefApp() {
}

// Destructor
OffscreenBrowserApp::~OffscreenBrowserApp() {
}

// For passing messages to UI thread
bool OffscreenBrowserApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) {
	return true;
}

// Called after the browser process thread
void OffscreenBrowserApp::OnBrowserCreated(CefRefPtr<CefBrowser> browser) {
}


