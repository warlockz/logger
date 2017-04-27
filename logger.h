/*
 * logger.h
 *
 *  Created on: 11-Oct-2016
 *      Author: yoge
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#ifdef __cplusplus
// https://msdn.microsoft.com/en-us/library/0603949d.aspx
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>
#include <stdarg.h>


typedef unsigned char _uchar_t;
#define V_TEST_MSGOUT vprint
#define LOGGER_MSG_FAILUE "Internal Logger Error"
#define LOG_TO_STD_FILE '0'
#define MAX_EXP_SIZE 512
#define MAX_TIME_SIZE 64

int vprint(const char* format,...);

char* varargstostring(const char* format,...);

#define TO_VSTRING(x) varargstostring(x)
#define STRINGIFY varargstostring
#define TO_STRING(x) #x

typedef enum log_level
{
	LEVEL_INVALID = 0x00,
	LEVEL1 = 0x01, //  Low level information
	LEVEL2 = 0x02, // entry Info
	LEVEL3 = 0x03, // Detail Info
	LEVEL_WARN, // Warning info
	LEVEL_ERR, // Error info
}log_level_t;

// TODO : if trace diabled or not
//#define LOG(level,printf_exp)

typedef struct _log_options
{
	union
	{
		_uchar_t value;
		_uchar_t lvl1 : 1;
		_uchar_t lvl2 : 1;
		_uchar_t lvl3 : 1;

	}Level;
	_uchar_t devmode;
}logsetting;

extern void devlogprint(const char* filename,const char* funname,int lineno,const char* logtype,char* msg);

extern _uchar_t getLogLevel();

extern void InitLogger(_uchar_t level,_uchar_t devmode,char* filepath,_uchar_t stdpath = 0);

extern FILE* g_File;

#define LOG(level ,printf_exp) \
		(level ? V_TEST_MSGOUT("%s \n",printf_exp) : V_TEST_MSGOUT("%s \n",LOGGER_MSG_FAILUE))

//http://stackoverflow.com/questions/597078/file-line-and-function-usage-in-c
//http://stackoverflow.com/questions/9229601/what-is-in-c-code?rq=1

#define SMLOG(level ,printf_exp) \
		if(getLogLevel()&level) \
		devlogprint(__FILE__,__func__,__LINE__,TO_STRING(level),STRINGIFY printf_exp); \
		else	\
		V_TEST_MSGOUT("%s \n",LOGGER_MSG_FAILUE); \

#define LOGL(level,printf_exp) \
		((getLogLevel()&level)? devlogprint(__FILE__, __func__,__LINE__,TO_STRING(level), STRINGIFY printf_exp), 1:-!!0)

#define LOGV(level,printf_exp) \
		((getLogLevel()&level)? devlogprint(__FILE__, __func__,__LINE__,TO_STRING(level), TO_VSTRING(printf_exp)), 1:-!!0)




#ifdef __cplusplus
}
#endif


#endif /* LOGGER_H_ */
