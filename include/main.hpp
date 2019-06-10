//////////////////////////
/*#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif*/

#include <windows.h> 		// WINDOWS
#include <wininet.h>

#include <stdio.h> 			// Language C
#include <stdarg.h>			// Language C
//#include <unistd.h> 		// Language C
#include <wchar.h>			// Language C
#include <stdlib.h>			// Language C
#include <string.h>			// Language C
#include <wctype.h>			// Language C

// htonl, htons, ntohl, ntohs - convert values between host and network byte order
#include <iostream>			// Language C++
#include <vector>			// Language C++

using std::vector;

#define DEFFLAGPUT		0xFF
#define DEFFLAGGET		0xFE
#define DEFFLAGFIRST	0xDD
#define DEFFLAGNOTFIRST 0xCC