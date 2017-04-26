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
#define MSGOUT print
#define MSGFAIL "Failed"
#define LOG_TO_STD_FILE '0'

int print(const char* format,...);

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

extern _uchar_t getLogLevel();

extern void InitLogger(_uchar_t level,_uchar_t devmode,char* filepath,_uchar_t stdpath = 0);

extern FILE* g_File;

#define LOG(level ,printf_exp) \
		(level ? MSGOUT("%s \n",printf_exp) : MSGOUT("%s \n",MSGFAIL))


#define LOGL(level ,printf_exp) \
		((getLogLevel() & LEVEL1) ? MSGOUT("%s \n",printf_exp) : MSGOUT("%s \n",MSGFAIL))


#ifdef __cplusplus
}
#endif


#endif /* LOGGER_H_ */
