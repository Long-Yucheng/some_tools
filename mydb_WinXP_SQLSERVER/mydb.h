// Copyright [2017-01-09] <Copyright Owner: Frank.Long>
//-----------------------------------------------------------------------
// 说明：这是windows版本的mydb，为了统一接口，仅限windows使用SQL SERVER
//
//-----------------------------------------------------------------------
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "AdoConn.h"


class Mydb
{
public:
	Mydb();
	~Mydb();

	bool connectDB(const std::string& host,
				   const std::string& user,
				   const std::string& pwd,
				   const std::string& dbname);

	void closeDB();

	//执行SQL
	bool exeSQL(const std::string& sql);

	//获取一个结果，存入一个string
	bool exeSQL(const std::string& sql, std::string &str);

	//获取一列数据，存入一个vector
	bool exeSQL(const std::string& sql, std::vector<std::string> &vec);

	//获取多列多行数据，存入一个map
	bool exeSQL(const std::string& sql, std::map<int, std::vector<std::string> > &mapvec);

        std::string getErrorMsg();

private:
        void clearErrorMsg();

private:
	Mydb(const Mydb&);
	Mydb& operator=(const Mydb&);

private:
	CAdoConn m_adoconn;
	int m_row;
	int m_col;
        std::string error_msg;  //当出错的时候，错误信息放在这里
};
