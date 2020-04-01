// Copyright [2017-01-10] <Copyright Owner: Frank.Long>
// ----------------------------------------------------------------------------
// Introduction :   this class is used for operating mysql.
// Author       :   Frank.Long
// Version      :   2.0.2
// Date         :   2017-03-14
// Usage        :   (1)包含头文件, 然后实例化出一个对象:    Mydb *mydb = new Mydb;
//                  (2)连接数据库    :                   mydb->connectDB(...);
//                  (3)多次执行SQL   :                   mydb->exeSQL(...);
//                  (4)用完关闭      :                   mydb->closeDB();
// Note         :   结果集不用手动释放，已经将其自动化了。
//
// log          :   v2.0.1 , 将mydb和log分离开，之前耦合太紧密 , 2017-03-13
//                  v2.0.2 , 增加error_msg和getErrorMsg() , 2017-03-14
//-----------------------------------------------------------------------------

#ifndef MYDB_H
#define MYDB_H

#include <mysql/mysql.h>
#include <sys/timeb.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>


class Mydb {
public:
    Mydb();
    ~Mydb();

    bool connectDB(const std::string& host,
                   const std::string& user,
                   const std::string& pwd,
                   const std::string& dbname);

    void closeDB();

    bool exeSQL(const std::string& sql);
    //获取一个结果，存入一个string
    bool exeSQL(const std::string& sql, std::string &str);
    //获取一列数据，存入一个vector
    bool exeSQL(const std::string& sql, std::vector<std::string> &vec);
    //获取多列多行数据，存入一个map
    bool exeSQL(const std::string& sql, std::map<int, std::vector<std::string> > &mapvec);

    std::string getErrorMsg();

private:
    Mydb(const Mydb& orig);
    bool initDB();
    void releaseResult();
    void clearErrorMsg();

private:
    int num_fields;   //有多少个字段(列)
    int num_rows;     //有多少行数据(被查到/受影响)
    std::string error_msg;  //当出错的时候，错误信息放在这里

    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW row;
};

#endif /* MYDB_H */

