// Copyright [2017-01-09] <Copyright Owner: Frank.Long>
// ----------------------------------------------------------------------------
// Introduction :   this class is used for writing log.
// Author       :   Frank.Long
// Version      :   1.0.0
// Date         :   2017-01-11
// Usage        :   由于使用了泛型，所以可以任意输出各种类型，int, float, string ...
//                  Logger &log = Logger::getInstance();
//                  log.writeLog(debug, 10.96);
//                  log.writeLog(debug, 586);
//                  log.writeLog(debug, "I am the best!");
//-----------------------------------------------------------------------------
#ifndef _LOGGER_H
#define _LOGGER_H

#include <time.h>
#include <memory.h>
#include <stddef.h>

#include <fstream>
#include <iostream>
#include <string>

#define APPNAME "SPFS-STool"
#define VERSION "v1.0.0"


#define CTIME   (((time(NULL)+8*3600)/86400)*86400 - 8*3600) - 86400  // 昨天的00点
#define CTIME15 (((time(NULL)+8*3600)/86400)*86400 - 8*3600) + 900   // 今天的0点15
#define CTIME0  (((time(NULL)+8*3600)/86400)*86400 - 8*3600)         // 今天的0点00
#define CTIMETM (((time(NULL)+8*3600)/86400)*86400 - 8*3600) + 86400  // 明天的00点


//日志级别
typedef enum _LogLevel {
    debug = 0,
    info,
    warning,
    error
}LogLevel;



class Logger
{
public:
    static Logger* getInstance() {
        static Logger instance;
        return &instance;
    }


    //由于泛型，不能分开.h 和 .cpp ，所以这个函数只能写在这

    template<typename T>
    void writeLog(const LogLevel state, const T& val) {
        getTimeBuffer();

        if (state == debug) {
            std::cout << val << std::endl;
        } else {
            std::ofstream outfile;
            outfile.open(getLogPath().data(), std::ios::out|std::ios::app);

            if (outfile.is_open()) {
                switch (state) {
                    case debug:
                        break;
                    case info:
                        outfile << "[" << timebuffer << "][" << VERSION << "][INFO] " << val << "\n";
                        break;
                    case warning:
                        outfile << "[" << timebuffer << "][" << VERSION <<"][WARNING] " << val << "\n";
                        break;
                    case error:
                        outfile << "[" << timebuffer << "][" << VERSION <<"][ERROR] " << val << "\n";
                        break;
                }

                outfile.close();
            }
        }
    }


public:
    std::string getParentDir();

private:
    Logger();
    ~Logger();
    Logger(Logger const&) {}
    Logger& operator=(Logger const& rhs);


    void getTimeBuffer();

    std::string getLogPath();

public:


private:
    char timebuffer[32];
};



#endif
