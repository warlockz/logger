/*
 * logger.h
 *
 *  Created on: 11-Oct-2016
 *      Author: yoge
 */

#ifndef LOGGER_H_
#define LOGGER_H_

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
	LEVEL1 = 0x01,
	LEVEL2 = 0x02,
	LEVEL3 = 0x01,

}log_level_t;

// TODO : if trace diabled or not
//#define LOG(level,printf_exp)



#define LOG(level,printf_exp) \
		(level ? MSGOUT("%s \n",printf_exp) : MSGOUT("%s \n",MSGFAIL))

#endif /* LOGGER_H_ */
