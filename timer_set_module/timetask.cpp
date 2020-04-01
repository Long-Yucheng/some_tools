// Copyright [2017-03-08] <Copyright Owner: Frank.Long>
#include "timetask.h"

CTimegTask::CTimegTask(): m_time_tomorrow(0)
{

}

CTimegTask::~CTimegTask()
{

}

//------------------------------------------------
//功能 ：每天到了指定时间，就返回true，否则返回false
//参数 ：
//      hour   - 指定几点, [0~23]
//      minute - 指定分钟, [0~59]
//返回 ：1.功能描述
//      2.如果输入错误的小时和分钟，返回false
//------------------------------------------------
bool CTimegTask::timeToDo(int hour, int minute)
{
    if (hour > 23 || hour < 0 || minute > 59 || minute < 0) {
        return false;
    }

    int temp_nowhour   = 0;
    int temp_nowminute = 0;
    time_t timenow = time(NULL);

    #ifdef _MSC_VER
    struct tm* stm = localtime(&timenow);
    temp_nowhour   = stm->tm_hour;
    temp_nowminute = stm->tm_min;
    #else
    struct tm stm  = {0};
    localtime_r(&timenow, &stm);
    temp_nowhour   = stm.tm_hour;
    temp_nowminute = stm.tm_min;
    #endif

    if (m_time_tomorrow == 0) {
        m_time_tomorrow = CTIMETM;
        return true;
    } else {
        if (temp_nowhour == hour && temp_nowminute >= minute && timenow >= m_time_tomorrow) {
            m_time_tomorrow = CTIMETM;
            return true;
        } else {
            return false;
        }
    }
}



//--------------------------------------
//功能 : 获取本月1号的00：00
//
//--------------------------------------
time_t CTimegTask::getMonFirstDay()
{
    time_t timenow = time(NULL);

    #ifdef _MSC_VER
    struct tm* stm = localtime(&timenow);
    stm->tm_hour = 0;
    stm->tm_min  = 0;
    stm->tm_sec  = 0;
    stm->tm_mday = 1;
    return mktime(stm);
    #else
    struct tm stm  = {0};
    localtime_r(&timenow, &stm);
    stm.tm_hour = 0;
    stm.tm_min  = 0;
    stm.tm_sec  = 0;
    stm.tm_mday = 1;
    return mktime(&stm);
    #endif
}



//--------------------------------------
//功能 : 获取上个月1号的00：00
//
//--------------------------------------
time_t CTimegTask::getLastMonFirstDay()
{
    time_t timenow = time(NULL);

    #ifdef _MSC_VER
    struct tm* stm = localtime(&timenow);
    stm->tm_hour = 0;
    stm->tm_min  = 0;
    stm->tm_sec  = 0;
    stm->tm_mday = 1;
    if (stm->tm_mon == 0) {
        stm->tm_year = stm->tm_year - 1;
        stm->tm_mon  = 11;
    } else {
        stm->tm_mon = stm->tm_mon - 1;
    }
    return mktime(stm);
    #else
    struct tm stm  = {0};
    localtime_r(&timenow, &stm);
    stm.tm_hour = 0;
    stm.tm_min  = 0;
    stm.tm_sec  = 0;
    stm.tm_mday = 1;
    if (stm.tm_mon == 0) {
        stm.tm_year = stm.tm_year - 1;
        stm.tm_mon  = 11;
    } else {
        stm.tm_mon = stm.tm_mon - 1;
    }
    return mktime(&stm);
    #endif
}



//--------------------------------------
//功能 : 获取今年1月1号的00：00
//
//--------------------------------------
time_t CTimegTask::getYearFirstDay()
{
    time_t timenow = time(NULL);

    #ifdef _MSC_VER
    struct tm* stm = localtime(&timenow);
    stm->tm_hour = 0;
    stm->tm_min  = 0;
    stm->tm_sec  = 0;
    stm->tm_mday = 1;
    stm->tm_mon  = 0;
    return mktime(stm);
    #else
    struct tm stm  = {0};
    localtime_r(&timenow, &stm);
    stm.tm_hour = 0;
    stm.tm_min  = 0;
    stm.tm_sec  = 0;
    stm.tm_mday = 1;
    stm.tm_mon  = 0;
    return mktime(&stm);
    #endif
}



//--------------------------------------
//功能 : 获取去年1月1号的00：00
//
//--------------------------------------
time_t CTimegTask::getLastYearFirstDay()
{
    time_t timenow = time(NULL);

    #ifdef _MSC_VER
    struct tm* stm = localtime(&timenow);
    stm->tm_hour = 0;
    stm->tm_min  = 0;
    stm->tm_sec  = 0;
    stm->tm_mday = 1;
    stm->tm_mon  = 0;
    stm->tm_year = stm->tm_year - 1;
    return mktime(stm);
    #else
    struct tm stm  = {0};
    localtime_r(&timenow, &stm);
    stm.tm_hour = 0;
    stm.tm_min  = 0;
    stm.tm_sec  = 0;
    stm.tm_mday = 1;
    stm.tm_mon  = 0;
    stm.tm_year = stm.tm_year - 1;
    return mktime(&stm);
    #endif
}



//--------------------------------------
//功能 : 获取某个月有多少天
//
//--------------------------------------
int CTimegTask::getDaysOfMon(int year, int mon)
{
    int days;
    int day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (mon == 2) {
        days = (((year%4 == 0) && (year%100 != 0)) || (0 == year%400)) ? 29 : 28;
    } else if (mon == 0) {
        days = day[0];
    } else {
        days = day[mon - 1];
    }
    return days;
}



//----------------------------------------------------------------------
//功能 : string日期 转 UNIX时间戳
//参数 ：timedate是string类型的日期，例如 timedate="2017-04-14 16:41:40";
//----------------------------------------------------------------------
time_t CTimegTask::strTime2unix(std::string timedate)
{
    struct tm tm;
    memset(&tm, 0, sizeof(tm));

    sscanf(timedate.c_str(), "%d-%d-%d %d:%d:%d",
           &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
           &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

    tm.tm_year -= 1900;
    tm.tm_mon--;

    return mktime(&tm);
}


//-------------------------------------------------
//功能 ：获取昨天，或今天，或明天的日期
//返回 ：例如 ： 20170306
//-------------------------------------------------
std::string CTimegTask::GetDate(DATEFLAG flag)
{
    time_t timenow = 0;

    switch (flag) {
    case DATE_YESTERDAY:
        timenow = time(NULL) - 86400;
        break;
    case DATE_TODAY:
        timenow = time(NULL);
        break;
    case DATE_TOMORROW:
        timenow = time(NULL) + 86400;
        break;
    default:
        break;
    }

    struct tm stm  = {0};
    localtime_r(&timenow, &stm);
    int year  = stm.tm_year + 1900;
    int month = stm.tm_mon  + 1;
    int day   = stm.tm_mday;
    char time_str[16] = {0};
    snprintf(time_str, 16, "%d%02d%02d", year, month, day);
    std::string date_str = "";
    date_str = time_str;
    return date_str;
}

