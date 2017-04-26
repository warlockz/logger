/*
 * logger.c
 *
 *  Created on: 11-Oct-2016
 *      Author: yoge
 */

#include "logger.h"

#include <stdarg.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>


FILE* g_File = NULL;
static logsetting g_log_setting;

int print(const char* format,...)
{
	va_list myargs;
	va_start(myargs,format);

	vprintf(format,myargs);
	va_end(myargs);
	//printf("Msg \n");
	return 0;
}

_uchar_t getLogLevel()
{
	return g_log_setting.Level.value;
}

void InitLogger(_uchar_t level,_uchar_t devmode,char* filepath,_uchar_t stdpath)
{
	g_log_setting.Level.value = level;
	g_log_setting.devmode = devmode;
	if(stdpath == LOG_TO_STD_FILE)
	{
		if((!filepath) || strlen(filepath))
		{
			g_File = freopen(filepath,"a",stderr);
		}
		else
		{
			g_File = freopen("/dev/tty","a",stderr);
		}
	}
	else
	{
		g_File = freopen("/dev/tty","a",stderr);
	}
}

int main(int argc, char **argv)
{
	//default log level setted to 1 ;
	g_log_setting.Level.value = LEVEL1;

	LOG(LEVEL1,"Hello");

	LOGL(LEVEL1,"Hello World Enter to new World");

	return 0;
}

