# Basic Logger (blog)
Very fast, header only, C++ logging library.
For priniting mechanism to debug during programming and testing in
actual hardware or kit or host system.  

## Install
#### Just copy the headers:

* Copy the source to your build tree and use a C89/C99/C++98 or greater version libs.

## Platforms
 * Linux, FreeBSD, Solaris
 * TODO : Windows  
 * Mac OSX 
 * TODO : Android

## Features
* Very fast - performance is the primary goal so developed in C implementation.
* Headers only, just copy and use.
* Prints minute details pid, tid, time and more.

## Usage Example
```c/c++

#include "logger.h"

int main(int argc, char **argv)
{
	// Initialize the logger and specify the level to display and 2 arg as developer mode on (1)
	InitLogger(LEVEL1|LEVEL2|LEVEL3,1,(char *)"/tmp/core.txt",LOG_TO_STD_FILE);
  //Redirected the print or log msg to /tmp/core.txt file
	LOGV(LEVEL3,"Init core.txt Log Actual 3 lvl Test\n");
  //Now Filepath is empty so redirected to std tty or stdout
	InitLogger(LEVEL1|LEVEL2|LEVEL3,0,(char *)"",0);
	LOGV(LEVEL2,"Init tty Log Actual 2 lvl Test\n");
	return 0;
}

```

## Documentation
Documentation or method in logger.h is self explainatory or soon will add a wiki page.
