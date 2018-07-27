/*
 * OffscreenBrowserClient.cpp
 *
 *  Created on: 2017年3月22日
 *      Author: root
 */


#include <iostream>
#include <unistd.h>
#include "include/cef_app.h"
#include "OffscreenBrowserClient.h"
#include <png.h>
#include <wlog.h>

// Constructor
OffscreenBrowserClient::OffscreenBrowserClient() {
	visitActive = false;
	pageHtml = "";
	m_nCurWidth = OFFSCREEN_BROWSER_WINDOW_WIDTH;
	m_nCurHeight = OFFSCREEN_BROWSER_WINDOW_HEIGHT;
	m_pViewBuffer = new unsigned char[m_nCurWidth * m_nCurHeight * 4];
	m_bOutPutPng = false;
}

// Destructor
OffscreenBrowserClient::~OffscreenBrowserClient() {
	if(m_pViewBuffer != NULL)
	{
		delete[] m_pViewBuffer;
		m_pViewBuffer = NULL;
	}
}

// Fetches HTML source synchronically
std::string OffscreenBrowserClient::GetHTMLSource() {
	visitActive = false;
	pageHtml = "";
	mBrowser->GetMainFrame()->GetSource(this);

	while (!visitActive) {
		usleep(10000);
		CefDoMessageLoopWork();
	}
	std::cout << "visit done" << std::endl;

	return pageHtml;
}

// Called after the browser client is succesfully created
void OffscreenBrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	mBrowser = browser;
}

// Called before the browser is shutdown
void OffscreenBrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	mBrowser = NULL;
}

int save_png(char* filename, int width, int height,
             unsigned char* data)
 {
   int i = 0;
   int r = 0;
   FILE* fp = NULL;
   png_structp png_ptr = NULL;
   png_infop info_ptr = NULL;
   png_bytep* row_pointers = NULL;

   if (NULL == data) {
     printf("Error: failed to save the png because the given data is NULL.\n");
     r = -1;
     goto error;
   }

   fp = fopen(filename, "wb");
   if (NULL == fp) {
     printf("Error: failed to open the png file: %s\n", filename);
     r = -4;
     goto error;
   }

   png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   if (NULL == png_ptr) {
     printf("Error: failed to create the png write struct.\n");
     r = -5;
     goto error;
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (NULL == info_ptr) {
     printf("Error: failed to create the png info struct.\n");
     r = -6;
     goto error;
   }

   png_set_IHDR(png_ptr,
                info_ptr,
                width,
                height,
                8,                 /* e.g. 8 */
							 PNG_COLOR_TYPE_RGBA,                /* PNG_COLOR_TYPE_{GRAY, PALETTE, RGB, RGB_ALPHA, GRAY_ALPHA, RGBA, GA} */
                PNG_INTERLACE_NONE,       /* PNG_INTERLACE_{NONE, ADAM7 } */
                PNG_COMPRESSION_TYPE_BASE,
                PNG_FILTER_TYPE_BASE);

   row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);

   for (i = 0; i < height; ++i) {
     row_pointers[i] = data + i * width * 4;
   	   }

   png_init_io(png_ptr, fp);
   png_set_rows(png_ptr, info_ptr, row_pointers);
   png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  error:
  	  if (NULL != fp)
  	  {
     fclose(fp);
     fp = NULL;
  	  }

   if (NULL != png_ptr) {

     if (NULL == info_ptr) {
       printf("Error: info ptr is null. not supposed to happen here.\n");
     }

     png_destroy_write_struct(&png_ptr, &info_ptr);
     png_ptr = NULL;
     info_ptr = NULL;
   }

   if (NULL != row_pointers) {
     free(row_pointers);
     row_pointers = NULL;
   }
   return r;
 }

// Called everytime there is something to paint to a "page". This is ignored, for drawing to e.g. offscreen bitmap, implement the logic here
int nFileIndex = 0;
static int nPaintIndex = 0;
#include <sys/time.h>
void OffscreenBrowserClient::OnPaint(CefRefPtr<CefBrowser> browser,
																	PaintElementType type,
																	const RectList& dirtyRects,
																	const void* buffer,
																	int width,
																	int height)
{
	if(width <= 0 || height <= 0 || buffer == NULL)
	{
		return;
	}

	if(m_nCurWidth != width || m_nCurHeight != height)
	{
		if(m_pViewBuffer != NULL)
		{
			delete[] m_pViewBuffer;
			m_pViewBuffer = NULL;
		}
		m_pViewBuffer = new unsigned char[width * height * 4];
		m_nCurWidth = width;
		m_nCurHeight = height;
	}

	int nSize = (int)dirtyRects.size();
	for(int i = 0; i < nSize; i++)
	{
		CefRect rect = dirtyRects[i];

		//buffer offset
		int nBufOffset = rect.y * width * 4 + rect.x * 4;
		unsigned char* pStartReadPos = (unsigned char*)buffer + nBufOffset;
		//bgra----rgba
		/*
		for(int nRow = rect.y; nRow < rect.y + rect.height; nRow++)
		{
			for(int nCol = rect.x; nCol < rect.x + rect.width; nCol++)
			{
				int nCurOffset = nRow * width * 4 + nCol * 4;
				unsigned char* pCurPos = (unsigned char*)buffer + nCurOffset;
				unsigned char temp = pCurPos[0];
				pCurPos[0] = pCurPos[2];
				pCurPos[2] = temp;
			}
		}
		*/

		//start write pos
		unsigned char* pStartWritePos = m_pViewBuffer + nBufOffset;

		for(int nRow = 0; nRow < rect.height; nRow++)
		{
			int nLineOffset = nRow * width * 4;
			memcpy(pStartWritePos + nLineOffset, pStartReadPos + nLineOffset, rect.width * 4);
		}

		//save png
		/*
		gettimeofday(&tpend,NULL);
		float timeuse= 1000000*(tpend.tv_sec-tpstart.tv_sec)+(tpend.tv_usec-tpstart.tv_usec);
		char sz[256];
		timeuse = timeuse / 1000;
		sprintf(sz, "%f", timeuse);
		wlog_write(sz);
		*/

	}

	std::cout << nPaintIndex << std::endl << std::flush;
	nPaintIndex++;

	//save buffer to file
	if(m_bOutPutPng && nPaintIndex > 1)
	{
		unsigned char* pBeginBuf = (unsigned char*)m_pViewBuffer;
		char filename[256];
		sprintf(filename, "%d.png", nFileIndex % 100);
		save_png(filename, m_nCurWidth, m_nCurHeight, pBeginBuf);
		nFileIndex++;
	}
}

// Called when access to HTML source is given on the UI thread side
void OffscreenBrowserClient::Visit(const CefString& html) {
	pageHtml = html.ToString();
	visitActive = true;
}


