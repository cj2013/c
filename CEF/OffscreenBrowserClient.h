/*
 * OffscreenBrowserClient.h
 *
 *  Created on: 2017年3月22日
 *      Author: root
 */

#ifndef OFFSCREENBROWSERCLIENT_H_
#define OFFSCREENBROWSERCLIENT_H_

#include <string>
#include "include/cef_client.h"
#include "include/cef_frame.h"
#include "include/cef_string_visitor.h"

// Handles the "rendering" of the page to off-screen bitmap and other client lifecycle methods
class OffscreenBrowserClient : public CefClient, public CefLifeSpanHandler, public CefRenderHandler, public CefStringVisitor {

private:
	CefRefPtr<CefBrowser> mBrowser;

	bool visitActive;
	std::string pageHtml;

	static const int OFFSCREEN_BROWSER_WINDOW_WIDTH = 1280;
	static const int OFFSCREEN_BROWSER_WINDOW_HEIGHT =720;

	int			m_nCurWidth;
	int			m_nCurHeight;
	unsigned char*	 m_pViewBuffer;
	bool			m_bOutPutPng;

public:
	OffscreenBrowserClient();
	virtual ~OffscreenBrowserClient();

	std::string GetHTMLSource();

	// CefClient methods
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this; }
	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE { return this; }

	// CefLifeSpanHandler methods
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

	// CefRenderHandler methods
	virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) OVERRIDE;
	virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) OVERRIDE { rect.Set(0, 0, OFFSCREEN_BROWSER_WINDOW_WIDTH, OFFSCREEN_BROWSER_WINDOW_HEIGHT);  return true; };

	// CefStringVisitor methods
	virtual void Visit(const CefString& html);

	// Own methods
	CefRefPtr<CefBrowser> GetBrowser() { return mBrowser; }

	void			SetOutput(bool bOutPut){m_bOutPutPng = bOutPut;};

	IMPLEMENT_REFCOUNTING(OffscreenBrowserClient);
};





#endif /* OFFSCREENBROWSERCLIENT_H_ */
