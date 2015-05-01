#ifndef __MYCCLOG_H__
#define __MYCCLOG_H__
#include "cocos2d.h"
enum
{
        MYLOG_VERBOSE=0,
        MYLOG_DEBUG,
        MYLOG_INFO,
        MYLOG_WARN,
        MYLOG_ERROR,
        MYLOG_COUNT,
};

const std::string LOG_NAME[MYLOG_COUNT]={"(verbose)\t","(debug)\t\t","(info)\t\t","(warn)\t\t","(error)\t\t"};

const std::string LOG_ANDROID_METHOD[MYLOG_COUNT]={"v","d","i","w","e"};

class MyLog :public cocos2d::Ref
{
public:
        MyLog(void);
        ~MyLog(void);
        //һ�㳣�õĴ�ӡ��Ϣ
        static void verbose(const char * pszFormat,...);
        //������Ϣ
        static void debug(const char * pszFormat,...);
        //һ����Ϣ
        static void info(const char * pszFormat,...);
        //������Ϣ
        static void warn(const char * pszFormat,...);
        //������Ϣ
        static void error(const char *pszFormat,...);

private:
        static const int LOG_VALUE;
        static void printLog(int type,const char * format,va_list ap);
        static void printAndroidLog(const char * methodName,const char * log);
};
#endif