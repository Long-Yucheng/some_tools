// Copyright [2017-03-08] <Copyright Owner: Frank.Long>
/* ----------------------------------------------------------------------------
Introduction :  用于触发定时任务，以及获取一些特殊的时间点
Author       :  Frank.Long
Version      :  1.0.0
Date         :  2017-03-08
Usage        :  触发demo如下：

                CTimegTask tt;
                while ( tt.timeToDo ) {
                    // do your work

                    Sleep(600); //linux下假设10分钟检查一次时间,windows下600000毫秒
                }

Note         : 第1次执行不会检查时间，所以第1次启动程序一定成功，然后就会进入每日定时循环
//------------------------------------------------------------------------------*/

#ifndef CTIMETASK_H
#define CTIMETASK_H

#include <time.h>

#define CTIME   (((time(NULL)+8*3600)/86400)*86400 - 8*3600) - 86400  // 昨天的00点
#define CTIME15 (((time(NULL)+8*3600)/86400)*86400 - 8*3600) + 900    // 今天的0点15
#define CTIME0  (((time(NULL)+8*3600)/86400)*86400 - 8*3600)          // 今天的0点00
#define CTIMETM (((time(NULL)+8*3600)/86400)*86400 - 8*3600) + 86400  // 明天的00点


class CTimegTask
{
public:
    CTimegTask();
    ~CTimegTask();
    bool timeToDo(int hour=0, int minute=0);    //每天定时做一次
    time_t getMonFirstDay();       //获取本月1号的00:00
    time_t getLastMonFirstDay();   //获取上个月1号的00:00
    time_t getYearFirstDay();      //获取今年1月1号的00:00
    time_t getLastYearFirstDay();  //获取去年1月1号的00:00
    int getDaysOfMon(int year, int mon);    //获取某个月有多少天

private:
    CTimegTask(const CTimegTask&);//禁用拷贝构造
    CTimegTask& operator=(const CTimegTask&);//禁用赋值运算符

private:
    int  m_time_tomorrow;
};

#endif // CTIMETASK_H
