/*
 * logger.c
 *
 *  Created on: 11-Oct-2016
 *      Author: yoge
 */
#include "stdio.h"
#include "logger.h"

int print(const char* format,...)
{
	va_list myargs;
	va_start(myargs,format);

	vprintf(format,myargs);
	va_end(myargs);
	//printf("Msg \n");
	return 0;
}

int main(int argc, char **argv)
{
	// Test basic initial logger
	LOG(LEVEL1,"Hello");

	return 0;
}

