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

#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>
#include <stdarg.h>

int print(const char* format,...);

#define MSGOUT print

#define MSGFAIL "Failed"

typedef enum log_level
{
	LEVEL_INVALID = 0x00,
	LEVEL1 = 0x01, //  Low level information
	LEVEL2 = 0x02, // entry Info
	LEVEL3 = 0x03, // Detail Info
	LEVEL_ERR, // Error info
	LEVEL_WARN, // Warning info
}log_level_t;

// TODO : if trace diabled or not
//#define LOG(level,printf_exp)



#define LOG(level,printf_exp) \
		(level ? MSGOUT("%s \n",printf_exp) : MSGOUT("%s \n",MSGFAIL))



#ifdef __cplusplus
}
#endif


#endif /* LOGGER_H_ */
