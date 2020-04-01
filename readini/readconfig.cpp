// Copyright [2017-01-09] <Copyright Owner: Frank.Long>

//#include "stdafx.h"  //-- windows下VS开发，可能需要包含此头文件，Linux下不用
//#include <Windows.h> //-- windows下VS开发，可能需要包含此头文件，Linux下不用
#include "readconfig.h"


ReadConfig::ReadConfig()
{

}



ReadConfig::~ReadConfig()
{
    if (!m_mapitem.empty()) {
        m_mapitem.clear();
    }

    if (!m_mapallitem.empty()) {
        m_mapallitem.clear();
    }
}



//-----------------------------------------------------------
//功能  ： 加载ini配置文件信息
//参数  ： ini文件名
//说明  ： ini文件必须放在与/bin目录同级的/config目录下
//
//返回  ： 成功返回true，打开文件失败或文件为空则返回false
//-----------------------------------------------------------
bool ReadConfig::loadConfigFile(const std::string& filename)
{
#ifdef _MSC_VER
    std::string inifilepath;
    inifilepath = getParentDir() + "\\config\\" + filename;
#else
    std::string inifilepath;
    inifilepath = getParentDir() + "/config/" + filename;
#endif

    std::ifstream readfile;
    readfile.open(inifilepath.c_str(), std::ios::in);

    if (!readfile) {
        return false;    //打开失败，返回false
    }

    readValue(readfile);

    if (m_mapallitem.empty()) { //ini文件里，没有section，或者只有section 没有其他的东西。
        readfile.close();
        return false;    //ini文件为空，返回false
    }

    readfile.close();
    return true;
}



//------------------------------------------------
//功能  ： 获取ini文件中 '=' 后面的字符串
//参数  ： section - 就是 [XXX] 里面的XXX
//        key     - 就是 data=89 当中的data
//返回  ： 返回int， 例如 data=89 就返回89
//------------------------------------------------
int ReadConfig::getValueInt(const std::string section, const std::string key, const int defaultval)
{
    if (!m_mapallitem.empty()) {
        MapAllItem::iterator pos_all = m_mapallitem.find(section);
        MapItem::iterator pos_item;

        if (pos_all != m_mapallitem.end()) {
            pos_item = pos_all->second.find(key);
            if (pos_item != pos_all->second.end()) {
                if (pos_item->second.size() == 0) {
                    return defaultval;
                } else {
                    if (isNum(pos_item->second)) {
                        return atoi((pos_item->second).c_str());
                    } else {
                        return defaultval;
                    }

                }
            }
        }

        return defaultval;
    } else {
        return defaultval;
    }

}



//------------------------------------------------
//功能  ： 获取ini文件中=号后面的字符串
//参数  ： section - 就是 [XXX] 里面的XXX
//        key     - 就是 data=16.5 当中的data
//返回  ： 返回float， 例如 data=16.5 就返回16.5
//------------------------------------------------
float ReadConfig::getValueFloat(const std::string section, const std::string key, const float defaultval)
{
    if (!m_mapallitem.empty()) {
        MapAllItem::iterator pos_all = m_mapallitem.find(section);
        MapItem::iterator pos_item;

        if (pos_all != m_mapallitem.end()) {
            pos_item = pos_all->second.find(key);
            if (pos_item != pos_all->second.end()) {
                if (pos_item->second.size() == 0) {
                    return defaultval;
                } else {
                    if (isNum(pos_item->second)) {
                        return atof((pos_item->second).c_str());
                    } else {
                        return defaultval;
                    }

                }
            }
        }

        return defaultval;
    } else {
        return defaultval;
    }
}



//------------------------------------------------
//功能  ： 获取ini文件中=号后面的字符串
//参数  ： section - 就是 [XXX] 里面的XXX
//        key     - 就是 user=frank 当中的user
//返回  ： 返回string，例如 user=frank 就返回frank
//------------------------------------------------
std::string ReadConfig::getValueString(const std::string section, const std::string key, const std::string str)
{
    if (!m_mapallitem.empty()) {
        MapAllItem::iterator pos_all = m_mapallitem.find(section);
        MapItem::iterator pos_item;

        if (pos_all != m_mapallitem.end()) {
            pos_item = pos_all->second.find(key);
            if (pos_item != pos_all->second.end()) {
                if (pos_item->second.size() == 0) {
                    return str;
                } else {
                    return pos_item->second;
                }
            }
        }

        return str;
    } else {
        return str;
    }
}



//------------------------------------------------------
//功能  ： 读取ini文件的内容，存入成员变量m_mapallitem里面
//参数  ： readfile - 读文件的文件描述符
//返回  ：
//------------------------------------------------------
void ReadConfig::readValue(std::ifstream& readfile)
{
    m_mapitem.clear();
    m_mapallitem.clear();

    std::string line("");
    std::vector<std::string> velem;
    std::string section("");

    while (std::getline(readfile, line, '\n')) {    //注意，最后一个'\n'，必须要加，不然报错
        #ifndef _MSC_VER
        int line_count = strlen(line.c_str()) + 1;
        char* temp_str = new char[line_count];
        memset(temp_str, 0, line_count);
        strcpy(temp_str, line.c_str());
        strDeleteCR(temp_str);
        line = temp_str;
        #endif

        if (!line.empty()) {    //检查ini文件的某一行是否为空，不为空则继续
            int lengthofline = line.length();
            if (line[0] == '[' && line[lengthofline-1] == ']') {   //找到section
                if (!section.empty() && !m_mapitem.empty()) {
                        m_mapallitem.insert(std::pair<std::string, MapItem>(section, m_mapitem));
                        m_mapitem.clear();
                }

                section = line.substr(1, lengthofline-2);
            }

            if (line.find('=') != std::string::npos) {
                    splitString(line, '=', velem);
                    m_mapitem.insert(std::pair<std::string, std::string>(velem[0], velem[1]));
                    velem.clear();
            }
        }
    }

    if (!section.empty() && !m_mapitem.empty()) {
        m_mapallitem.insert(std::pair<std::string, MapItem>(section, m_mapitem));
        m_mapitem.clear();
    }

}



//------------------------------------------------------------
//功能  ： 根据指定的分隔符，分隔string，并存入指定vector里面
//参数  ： str     - 需要分隔的字符串
//        delimit - 分隔符，例如 ',' '=' '.'
//        velem   - 存放分隔后的字符串的容器
//返回  ：
//------------------------------------------------------------
void ReadConfig::splitString(const std::string str,
                             char delimit,
                             std::vector<std::string>& velem)
{
    std::string::size_type i = 0;
    std::string::size_type j = str.find(delimit);

    while (j != std::string::npos) {
        velem.push_back(str.substr(i, j-i));
        i = ++j;
        j = str.find(delimit, j);

        if (j == std::string::npos) {
            velem.push_back(str.substr(i, str.length()));
        }
    }
}



//------------------------------------
//功能 ：获取上一级目录
//返回 ：上一级目录的绝对路径
//------------------------------------
std::string ReadConfig::getParentDir()
{
#ifdef _MSC_VER
    char dir[256] = {0};
    char syspath[256] = {0};
    HMODULE module = GetModuleHandle(0);
    GetModuleFileName(module, dir, 256);

    // 与linux不同，windows的目录的斜杠是: '\\'，而Linux下目录斜杠是:  '/'
    const char *ptr;
    ptr = strrchr(dir, '\\');
    int length = strlen(dir) - strlen(ptr);
    std::string s1(dir);
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


//-------------------------------------------------
//功能 ：检查字符串是否是数字
//返回 ：如果是数字，返回true。 否则，返回false
//-------------------------------------------------
bool ReadConfig::isNum(std::string s)
{
    std::stringstream sin(s);
    double t;
    char p;
    if (!(sin >> t)) {
        return false;
    }

    if (sin >> p) {
        return false;
    } else {
        return true;
    }
}

void ReadConfig::strDeleteCR(char *str)
{
    char* p = &str[strlen(str)-1];
    while (*p == '\r') {
        *p-- = '\0';
    }
}
