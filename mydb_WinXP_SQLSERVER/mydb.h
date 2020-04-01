// Copyright [2017-01-09] <Copyright Owner: Frank.Long>
//-----------------------------------------------------------------------
// ˵��������windows�汾��mydb��Ϊ��ͳһ�ӿڣ�����windowsʹ��SQL SERVER
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

	//ִ��SQL
	bool exeSQL(const std::string& sql);

	//��ȡһ�����������һ��string
	bool exeSQL(const std::string& sql, std::string &str);

	//��ȡһ�����ݣ�����һ��vector
	bool exeSQL(const std::string& sql, std::vector<std::string> &vec);

	//��ȡ���ж������ݣ�����һ��map
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
        std::string error_msg;  //�������ʱ�򣬴�����Ϣ��������
};
