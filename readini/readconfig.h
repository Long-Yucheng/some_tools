// Copyright [2017-01-09] <Copyright Owner: Frank.Long>
// ----------------------------------------------------------------------------------------------------------------
// Introduction :   this class is used for reading config file(ini file).
// Author       :   Frank.Long
// Version      :   2.0.2
// Date         :   2017-02-22 11:30
// Usage        :   简单2步：(1) loadConfigFile("inifile") //ini文件必须放在与/bin目录同级的/config目录
//                               加载之后，记得检查返回值，返回true说明加载成功，返回false说明，配置文件有问题
//                           (2) getValue...()      //获取值
//
// Note         :
//                1.这是跨平台的，windows xp平台和linux平台适用。
//                  (1)在windows xp平台，请使用VS开发，可能需要在readconfig.cpp中包含头文件 #include "stdafx.h"
//				      【新建vc++工程】->【WIN32控制台程序】->【添加公共头文件以用于MFC】->【完成】
//					(2)如果在Windows VS上新建 - 空的工程，需要包含#include <Windows.h>
//					
//                2.只适用于标准的ini文件，包含[section], key=value例如：
//                  [DBINFO]
//                  user=frank
//                  ip=192.168.10.2
//                  [DIRINFO]
//                  datapath=/home/xxx/data
//                  logpath=/home/xxx/log
//-----------------------------------------------------------------------------------------------------------------

#ifndef READCONFIG_H
#define READCONFIG_H

#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <map>
#include <sstream>



typedef std::map<std::string, std::string> MapItem;    //每一单项 key=value , 例如 DBNAME=NRFMDB
typedef std::map<std::string, MapItem> MapAllItem;    //所有配置信息集合 <section, map<key, value>>

class ReadConfig
{
public:
    ReadConfig();
    ~ReadConfig();
    //加载配置文件
    bool loadConfigFile(const std::string& filename);
    //获取int类型参数
    int  getValueInt(const std::string section, const std::string key, const int defaultval = 0);
    //获取float类型参数
    float getValueFloat(const std::string section, const std::string key, const float defaultval = 0.0);
    //获取string类型参数
    std::string getValueString(const std::string section, const std::string key, const std::string str = "");

private:
    void readValue(std::ifstream &readfile);
    void splitString(const std::string str, char delimit, std::vector<std::string>& velem); //切割string
    std::string getParentDir();
    bool isNum(std::string s);
    void strDeleteCR(char *str);

private:
    MapItem    m_mapitem;
    MapAllItem m_mapallitem;
};

#endif // READCONFIG_H
