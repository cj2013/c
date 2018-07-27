#ifndef WLOG_H
#define WLOG_H

int     wlog_open(const char* fileName);

int     wlog_write(const char* strtext);

int     wlog_close();

#endif // WLOG_H

