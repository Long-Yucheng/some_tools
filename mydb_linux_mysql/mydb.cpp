// Copyright [2017-01-10] <Copyright Owner: Frank.Long>
#include "mydb.h"

Mydb::Mydb()
{
    num_fields = 0;
    num_rows   = 0;
    result     = NULL;  //初始化，很重要
    error_msg  = "";
}



Mydb::~Mydb()
{
    num_fields = 0;
    num_rows   = 0;
    result     = NULL;
    error_msg  = "";

    closeDB();
}



//------------------------------------
//功能  ： 初始化数据库连接
//参数  ：
//返回  ： 成功返回true，失败返回false
//------------------------------------
bool Mydb::initDB()
{
    connection = mysql_init(NULL); // 初始化数据库连接变量
    clearErrorMsg();
    if (connection == NULL) {
        error_msg = "Mysql init connection failed!";
        return false;
    } else {
        return true;
    }
}



//------------------------------------
//功能  ： 关闭连接
//参数  ：
//返回  ：
//------------------------------------
void Mydb::closeDB()
{
    releaseResult();

    if (connection != NULL) { // 关闭数据库连接
        mysql_close(connection);
        connection = NULL;
    }

    mysql_library_end();
}



//------------------------------------------------------------------
//功能  ： 连接数据库
//参数  ： host - 数据库ip， user - 用户名， pwd - 密码, dbname - 库名字
//返回  ： 连接成功返回true，连接失败返回false
//------------------------------------------------------------------
bool Mydb::connectDB(const std::string& host,
                     const std::string& user,
                     const std::string& pwd,
                     const std::string& dbname)
{
    //初始化数据库连接
    if (!initDB()) {
        return false;
    }

    // 函数mysql_real_connect建立一个数据库连接
    // 成功返回MYSQL*连接句柄，失败返回NULL
    connection = mysql_real_connect(connection, host.c_str(), user.c_str(),
                                    pwd.c_str(), dbname.c_str(), 0, NULL, 0);

    clearErrorMsg();
    if (!connection) {
        error_msg = "Mysql connection failed! Can't connect to DB!";
        return false;
    }

    return true;
}



//------------------------------------------
//功能  ： 释放执行SQL语句的结果集
//参数  ：
//返回  ：
//------------------------------------------
void Mydb::releaseResult()
{
    if (result != NULL) {
        mysql_free_result(result); //释放结果集
        result = NULL;
    }
}



//-------------------------------------------------------------------
//功能  ： 执行SQL语句（用于除了select之外的其他语句，千万别用select语句）
//参数  ： sql - SQL语句
//返回  ： 成功返回true，失败返回false
//-------------------------------------------------------------------
bool Mydb::exeSQL(const std::string& sql)
{
    num_fields = 0;
    num_rows   = 0;
    releaseResult();    //保险起见，先释放一次

    clearErrorMsg();
    if (mysql_query(connection, sql.c_str())) { //进入if分支，说明执行SQL失败
            error_msg = mysql_error(connection);
            releaseResult();
            return false;
    } else {
            releaseResult();
            return true;
    }
}



//------------------------------------------
//功能  ： 查询单个数据
//参数  ： sql - SQL语句 , str - 获取到的结果
//返回  ： 成功返回true，失败返回false
//------------------------------------------
bool Mydb::exeSQL(const std::string& sql, std::string &str)
{
    if (!str.empty()) {
        str = "";
    }

    num_fields = 0;
    num_rows   = 0;

    releaseResult(); //保险起见，先释放一次
    clearErrorMsg();

    if (mysql_query(connection, sql.c_str())) {
        error_msg = mysql_error(connection);
        releaseResult();
        return false;
    } else {
        result = mysql_store_result(connection);

        if (result) {
                num_rows = mysql_num_rows(result);

                if (num_rows < 1) {
                    str = "";   //没有查到结果，赋一个空值
                } else {
                    if ((row = mysql_fetch_row(result)) != NULL) {
                        str = row[0] ? row[0] : "";
                    }   //因为row[0]是string类型，所以即便row[0]是“0”，也会赋给str
                }

                releaseResult();
                return true;
        } else {
                error_msg = mysql_error(connection);
                releaseResult();
                return false;
        }
    }
}

//------------------------------------------
//功能  ： 查询1列数据，存入vec
//参数  ： sql - SQL语句 , vec - 获取到1列的结果
//返回  ： 成功返回true，失败返回false
//------------------------------------------
bool Mydb::exeSQL(const std::string& sql, std::vector<std::string> &vec)
{
    if (!vec.empty()) {
        vec.clear();
    }

    num_fields = 0;
    num_rows   = 0;

    releaseResult();   //保险起见，先释放一次
    clearErrorMsg();

    if (mysql_query(connection, sql.c_str())) {
            error_msg = mysql_error(connection);
            releaseResult();
            return false;
    } else {
            result = mysql_store_result(connection);

            if (result) {
                    num_rows = mysql_num_rows(result);  //查询结果有多少行

                    if (num_rows < 1) {
                            releaseResult();    //没有查到结果
                            return true;
                    } else {
                            while ((row = mysql_fetch_row(result)) != NULL) {
                                //由于每次只查询1个字段，所以用row[0]遍历查询结果中的各行记录
                                vec.push_back(row[0]?row[0]:"");
                            }
                            releaseResult();
                            return true;
                    }
            } else {
                    error_msg = mysql_error(connection);
                    releaseResult();
                    return false;
            }
    }
}



//------------------------------------------------------------
//功能  ： 查询多列数据
//参数  ： sql - SQL语句 , mapvec - 获取到的结果
//返回  ： 成功返回true，失败返回false
//注意  ：
//        mapvec.size()    得到的是 字段 数量
//        mapvec[0].size() 得到的是 每个字段内元素的数量
//------------------------------------------------------------
bool Mydb::exeSQL(const std::string& sql, std::map<int, std::vector<std::string> > &mapvec)
{
    if (!mapvec.empty()) {
        mapvec.clear();
    }

    num_fields = 0;
    num_rows   = 0;

    releaseResult();   //保险起见，先释放一次
    clearErrorMsg();

    if (mysql_query(connection, sql.c_str())) {
            error_msg = mysql_error(connection);
            releaseResult();
            return false;
    } else {
            result = mysql_store_result(connection);
            if (result) {
                    num_rows   = mysql_num_rows(result);
                    num_fields = mysql_num_fields(result);

                    if (num_rows < 1) {
                        //没有查到结果
                        releaseResult();
                        return true;
                    } else {
                        while ((row = mysql_fetch_row(result)) != NULL) {
                            for (int i = 0; i < num_fields; ++i) {
                                mapvec[i].push_back(row[i] ? row[i] : "");
                            }
                        }                        
                        releaseResult();
                        return true;
                    }
            } else {
                    error_msg = mysql_error(connection);
                    releaseResult();
                    return false;
            }
    }
}


//------------------------------------------------------------
//功能  ： 清空mysql_error的信息
//参数  ：
//
//------------------------------------------------------------
void Mydb::clearErrorMsg()
{
    error_msg = "";
}


//------------------------------------------------------------
//功能  ： 当出现错误，返回mysql_error的信息
//参数  ：
//
//------------------------------------------------------------
std::string Mydb::getErrorMsg()
{
    return error_msg;
}
