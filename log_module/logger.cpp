// Copyright [2017-01-09] <Copyright Owner: Frank.Long>
//#include "stdafx.h" // windows专用
#include "Logger.h"

Logger::Logger()
{

}


Logger::~Logger()
{

}

Logger &Logger::operator=(const Logger& rhs)
{
    if (this == &rhs) {
        return *this;
    }

    return *this;
}



//------------------------------------
//功能 ：获取当前时间，并写入timebuffer
//
//------------------------------------
void Logger::getTimeBuffer()
{
#ifdef _MSC_VER
    // 与linux不同，xp 不支持 localtime_r
    memset(timebuffer, 0, sizeof(timebuffer));
    time_t timenow = time(NULL);
    struct tm* stm = localtime(&timenow);
    // 与linux不同，下面的函数，开头多一个下划线
    _snprintf(timebuffer, 32, "%04d-%02d-%02d %02d:%02d:%02d",
             stm->tm_year+1900, stm->tm_mon+1, stm->tm_mday,
             stm->tm_hour, stm->tm_min, stm->tm_sec);
#else
    memset(timebuffer, 0, sizeof(timebuffer));
    time_t timenow = time(NULL);
    struct tm stm = {0};
    localtime_r(&timenow, &stm);
    snprintf(timebuffer, 32, "%04d-%02d-%02d %02d:%02d:%02d",
             stm.tm_year+1900, stm.tm_mon+1, stm.tm_mday,
             stm.tm_hour, stm.tm_min, stm.tm_sec);
#endif
}

//------------------------------------
//功能 ：获取上一级目录
//返回 ：上一级目录的绝对路径
//------------------------------------
std::string Logger::getParentDir()
{
#ifdef _MSC_VER
    // 与linux不同，xp 不支持 localtime_r
    char pFileName[256] = {0};
    char syspath[256] = {0};
    HMODULE module = GetModuleHandle(0);
    GetModuleFileName(module, pFileName, 256);

    // 与linux不同，windows的目录的斜杠是: '\\'，而Linux下目录斜杠是:  '/'
    const char *ptr;
    ptr = strrchr(pFileName, '\\');
    int length = strlen(pFileName) - strlen(ptr);
    std::string s1(pFileName);
    std::string s2;
    s2 = s1.substr(0, length);
    memcpy(syspath, s2.c_str(), strlen(s2.c_str()) + 1);
    ptr = strrchr(syspath, '\\');
    length = strlen(syspath) - strlen(ptr);
    s2 = s2.substr(0, length);
    return s2;
#else
    char dir[256] = {0};
    char syspath[256] = {0};
    int n = readlink("/proc/self/exe", dir, 256);

    if (n < 0 || n >= 256) {
        return NULL;
    }

    const char *ptr;
    ptr = strrchr(dir, '/');
    int length = strlen(dir) - strlen(ptr);
    std::string s1(dir);
    std::string s2;
    s2 = s1.substr(0, length);
    memcpy(syspath, s2.c_str(), strlen(s2.c_str()) + 1);
    ptr = strrchr(syspath, '/');
    length = strlen(syspath) - strlen(ptr);
    s2 = s2.substr(0, length);
    return s2;
#endif
}



//---------------------------------------------------------------
//功能 ：获取log文件夹路径，必须是  /-
//                                /home
//                                    -/xxx/bin (可执行文件存放)
//                                    -/xxx/log (log存放)
//
//返回 ：log文件的绝对路径，格式： appname-2017-01-11.log
//---------------------------------------------------------------
std::string Logger::getLogPath()
{
#ifdef _MSC_VER
    time_t timenow = time(NULL);
    struct tm* stm = localtime(&timenow);
    char logfilenametime[32] = {0};

    _snprintf(logfilenametime, 32, "%s-%02d-%02d-%02d.log", APPNAME,
             stm->tm_year+1900, stm->tm_mon+1, stm->tm_mday);

    // 与linux不同，windows的目录的斜杠是: '\\'，而Linux下目录斜杠是:  '/'
    std::string logpath;
    std::string parentdir = getParentDir();
    logpath =  parentdir + "\\log\\" + logfilenametime;

    return logpath;
#else
    time_t timenow = time(NULL);
    struct tm stm = {0};
    localtime_r(&timenow, &stm);

    char logfilenametime[32] = {0};

    snprintf(logfilenametime, 32, "%s-%02d-%02d-%02d.log", APPNAME,
             stm.tm_year+1900, stm.tm_mon+1, stm.tm_mday);

    std::string logpath;
    logpath = getParentDir() + "/log/" + logfilenametime;
    return logpath;
#endif
}
