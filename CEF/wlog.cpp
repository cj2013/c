
#include "wlog.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
int  g_fileID;
int     wlog_open(const char* fileName)
{
    g_fileID = open(fileName, O_CREAT  | O_WRONLY   | O_APPEND);
    if (g_fileID < 0)
        return -1;
    return 1;
}

int     wlog_write(const char* strtext)
{
    if(g_fileID < 0)
    {
      return -1;
    }
   char strLog[256];
   time_t timep;
   struct tm *p;
   time(&timep);
   p = localtime(&timep);
   sprintf(strLog, "%d-%d-%d %d:%d:%d  %s\n", (1900 + p->tm_year), ( 1 + p->tm_mon), p->tm_mday,
                                (p->tm_hour), p->tm_min, p->tm_sec, strtext);
   write(g_fileID, strLog, strlen(strLog));
   return 1;
}

int     wlog_close()
{
	if(g_fileID > 0)
	{
		close(g_fileID);
	}
  return 1;
}
