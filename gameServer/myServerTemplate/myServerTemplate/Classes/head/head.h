#ifndef __HEAD_HEAD_H__
#define __HEAD_HEAD_H__

#include <iostream>
#include <stdarg.h>
#include <map>
#include <vector>

//using namespace std;

#define CC_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define CC_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)



static char* GetFormatString(const char* lpFormat, ...)
{
	static char buff[1024*2];
	va_list ap;
	va_start( ap, lpFormat );
	vsprintf_s( buff,lpFormat, ap );
	va_end(ap);
	return buff;
}

static void log(const char * lpFormat, ...)
{
	static char buff[1024*2];

	va_list ap;
	va_start( ap, lpFormat );
	vsprintf_s( buff,lpFormat, ap );
	va_end(ap);
	
	std::cout<<buff<<std::endl;
}

#endif