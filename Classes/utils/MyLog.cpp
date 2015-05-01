#include "MyLog.h"

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

#endif

USING_NS_CC;

#define MAX_STRING_LEN (1024*100)
#define LOG_V 1
#define LOG_D 2
#define LOG_I 4
#define LOG_W 8
#define LOG_E 16

const int MyLog::LOG_VALUE=LOG_V|LOG_D|LOG_I|LOG_W|LOG_E;

MyLog::MyLog(void)
{
}


MyLog::~MyLog(void)
{
}

void MyLog::verbose(const char * pszFormat, ...) {
        if (LOG_V & LOG_VALUE) {
                va_list ap;
                va_start(ap, pszFormat);
                MyLog::printLog(MYLOG_VERBOSE, pszFormat, ap);
                va_end(ap);
        }
}

void MyLog::debug(const char* pszFormat, ...) {
        if (LOG_D & LOG_VALUE) {
                va_list ap;
                va_start(ap, pszFormat);
                MyLog::printLog(MYLOG_DEBUG, pszFormat, ap);
                va_end(ap);
        }
}

void MyLog::info(const char* pszFormat, ...) {
        if (LOG_I & LOG_VALUE) {
                va_list ap;
                va_start(ap, pszFormat);
                MyLog::printLog(MYLOG_INFO, pszFormat, ap);
                va_end(ap);
        }
}

void MyLog::warn(const char* pszFormat, ...) {
        if (LOG_W & LOG_VALUE) {
                va_list ap;
                va_start(ap, pszFormat);
                MyLog::printLog(MYLOG_WARN, pszFormat, ap);
                va_end(ap);
        }
}

void MyLog::error(const char* pszFormat, ...) {
        if (LOG_E & LOG_VALUE) {
                va_list ap;
                va_start(ap, pszFormat);
                MyLog::printLog(MYLOG_ERROR, pszFormat, ap);
                va_end(ap);
        }
}

void MyLog::printLog(int type, const char* format, va_list ap) {
        char* pBuf = (char*) malloc(MAX_STRING_LEN);
        std::string mstr;
        if (pBuf != NULL) {
                vsnprintf(pBuf, MAX_STRING_LEN, format, ap);
                mstr = pBuf;
                free(pBuf);
        }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        printAndroidLog(LOG_ANDROID_METHOD[type].c_str(), mstr.c_str());
#else
        log("%s :%s", LOG_NAME[type].c_str(), mstr.c_str());
#endif
}

void MyLog::printAndroidLog(const char* methodName, const char* log) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo t;
        bool isHave = JniHelper::getStaticMethodInfo(t,
                "android/util/Log",
                methodName,
                "(Ljava/lang/String;Ljava/lang/String;)I");
        if (isHave)
        {
                jstring jTitle = t.env->NewStringUTF("cocos2d-x");
                jstring jMsg = t.env->NewStringUTF(
                        log);
                t.env->CallStaticVoidMethod(t.classID, t.methodID, jTitle,
                        jMsg);
                t.env->DeleteLocalRef(jTitle);
                t.env->DeleteLocalRef(jMsg);
        }
        else
        {
                Log("the jni method is not exits");
        }
#endif
}