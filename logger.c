/*
 * logger.c
 *
 *  Created on: 11-Oct-2016
 *      Author: yoge
 */


#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

//http://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
//http://www.geeksforgeeks.org/variable-length-arguments-for-macros/
#define lout(f,x,...) \
		fprintf(f,x,##__VA_ARGS__); fflush(f);



FILE* g_File = NULL;
static logsetting g_log_setting;

int vprint(const char* format,...)
{
	va_list myargs;
	va_start(myargs,format);

	vprintf(format,myargs);
	va_end(myargs);
	//printf("Msg \n");
	return 0;
}

char* varargstostring(const char* format,...)
{
	char* msg = (char*)calloc(MAX_EXP_SIZE,1);
	va_list myargs;
	va_start(myargs,format);
	vsnprintf(msg,MAX_EXP_SIZE,format,myargs);
	va_end(myargs);
	return msg;
}

void devlogprint(const char* filename,const char* funname,int lineno,const char* logtype,char* msg)
{
	//timespec is POSIX complaint where another struct continued till now
	//timeval was BSD legacy https://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
	struct timespec monotime;
	char timestr[MAX_TIME_SIZE];
	struct tm* calender_cur_time;
	long millisec;
	//http://man7.org/linux/man-pages/man2/clock_gettime.2.html
	memset(&monotime,0,sizeof(monotime));
	//https://linux.die.net/man/3/clock_gettime
	clock_gettime(CLOCK_MONOTONIC,&monotime);
	//http://stackoverflow.com/questions/12392278/measure-time-in-linux-time-vs-clock-vs-getrusage-vs-clock-gettime-vs-gettimeof?noredirect=1&lq=1
	//convert monotime and get time in struct like tm members
	calender_cur_time = gmtime(&monotime.tv_sec);
	//format time
	strftime(timestr,sizeof(timestr),"%H:%M:%S",calender_cur_time);
	//convert nano to milli seconds
	millisec = (monotime.tv_nsec / 1000000);

	pid_t tid = syscall(SYS_gettid);
	pid_t pid = getpid();

	if(g_File != NULL)
	{
		if(g_log_setting.devmode)
		{
			lout(g_File,"%s:%ld [%s][%d][%d]-%s@%s():[%d] :- %s",timestr,millisec,logtype,pid,tid,filename,funname,lineno,msg);
		}
		else
		{
			lout(g_File,"[%s]-%s :- %s",logtype,funname,msg);
		}
	}
	else if(g_log_setting.devmode == 2)
	{
		lout(stdout,"%s:%ld [%s]-%s@%s():[%d] :- %s",timestr,millisec,logtype,filename,funname,lineno,msg);
	}
	// freed allocated msg
	free(msg);
	msg = NULL;
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
		g_File = fopen("/dev/tty","w");
	}
}

int main(int argc, char **argv)
{
	//default log level setted to 1 ;
	g_log_setting.Level.value = LEVEL1;

	LOG(LEVEL1,"Hello");

	g_log_setting.devmode = 2;

	SMLOG(LEVEL1,("Hello World Enter to new World\n"));

	LOGL(LEVEL1,("Log lvl 1 Test\n"));

	LOGL(LEVEL_ERR,("Log lvl Err Test\n"));

	LOGL(LEVEL_INVALID,("Log lvl invalid Test\n"));

	LOGV(LEVEL_ERR,"Log V lvl Err Test\n");

	// Now test Initilogger functionality
	InitLogger(LEVEL1|LEVEL2|LEVEL3,1,(char *)"/tmp/core.txt",LOG_TO_STD_FILE);

	LOGV(LEVEL3,"Init core.txt Log Actual 3 lvl Test\n");

	InitLogger(LEVEL1|LEVEL2|LEVEL3,1,(char *)"",0);

	LOGV(LEVEL2,"Init tty dev mode Log Actual 2 lvl Test\n");

	InitLogger(LEVEL1|LEVEL2|LEVEL3,0,(char *)"",0);

	LOGV(LEVEL2,"Init tty Log Actual 2 lvl Test\n");

	return 0;
}

