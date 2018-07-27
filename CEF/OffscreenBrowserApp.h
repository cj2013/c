/*
 * OffscreenBrowserApp.h
 *
 *  Created on: 2017年3月22日
 *      Author: root
 */

#ifndef OFFSCREENBROWSERAPP_H_
#define OFFSCREENBROWSERAPP_H_


#include "include/cef_base.h"
#include "include/cef_app.h"

// Handles the browser process related functionality
class OffscreenBrowserApp : public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {

public:
	OffscreenBrowserApp();
	virtual ~OffscreenBrowserApp();

	// CefApp methods
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE { return this; }

	// CefRenderProcessHandler methods
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) OVERRIDE;
	virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

	IMPLEMENT_REFCOUNTING(OffscreenBrowserApp);
};



#endif /* OFFSCREENBROWSERAPP_H_ */
