// Copyright [2017-01-09] <Copyright Owner: Frank.Long>
#include "StdAfx.h"
#include ".\mydb.h"

Mydb::Mydb(void): m_row(0), m_col(0)
{
}



Mydb::~Mydb(void)
{
}



bool Mydb::connectDB(const std::string& host,
					 const std::string& user,
					 const std::string& pwd,
					 const std::string& dbname)
{
    clearErrorMsg();
	if (m_adoconn.OpenAdoConn(user.data(), pwd.data(), dbname.data(), host.data())) {
		return true;
	} else {
        error_msg = "DB connection failed! Can't connect to DB!";
		return false;
	}
}




void Mydb::closeDB()
{
	m_adoconn.CloseAdoConn();
}




bool Mydb::exeSQL(const std::string& sql)
{	
    clearErrorMsg();
	if (m_adoconn.ExecuteSql(sql.data())) {
		return true;
	} else {
        error_msg = "Execute SQL Failed! Please check !";
		return false;
	}
}



//----------------------------------------------
//功能  ： 查询单个数据
//参数  ： sql - SQL语句 , str - 获取到的结果
//返回  ： 成功返回true，失败返回false
//----------------------------------------------
bool Mydb::exeSQL(const std::string& sql, std::string &str)
{
    clearErrorMsg();
	if (!str.empty()) {
		str = "";
	}

	_RecordsetPtr recordSet = NULL;

	if (!m_adoconn.OpenAdoRecordSet(recordSet, sql.data(), adCmdText, adOpenStatic)) {
        error_msg = "Query Failed! Please check !";
		return false;
	}

	if (recordSet == NULL) {
        error_msg = "Query result is NULL!";
		recordSet->Close();
		recordSet.Release();
		return true;
	}

	CString cstr;

	if (!recordSet->adoEOF) {	//获取1行
		cstr = recordSet->GetCollect(_variant_t((long)0)); //取第一列的值，列的计数从0开始
	}

	if (!cstr.IsEmpty()) {
		str = cstr.GetBuffer(0);	//CString 转 string		
	} else {
        error_msg = "Query result is NULL!";
		str = "";	//如果查询结果为空，则赋空
	}

	recordSet->Close();
	recordSet.Release();
	return true;
}



//------------------------------------------------
//功能  ： 查询1列数据，存入vec
//参数  ： sql - SQL语句 , vec - 获取到1列的结果
//返回  ： 成功返回true，失败返回false
//------------------------------------------------
bool Mydb::exeSQL(const std::string& sql, std::vector<std::string> &vec)
{
    clearErrorMsg();
	if (!vec.empty()) {
		vec.clear();
	}

	m_col = 0;
	m_row = 0;

	try {
		_RecordsetPtr recordSet = NULL;

		if (!m_adoconn.OpenAdoRecordSet(recordSet, sql.data(), adCmdText, adOpenStatic)) {
            error_msg = "Query Failed! Please check !";
			return false;
		}

		if (recordSet == NULL) {
            error_msg = "Query result is NULL!";
			recordSet->Close();
			recordSet.Release();
			return true;
		}

		m_col = recordSet->Fields->GetCount(); //获得查询列数
                //m_row = recordSet->GetRecordCount();   //获得查询行数

		CString cstr;

		if (m_col == 1) {
			while (!recordSet->adoEOF) {
				cstr = recordSet->GetCollect(_variant_t((long)0));
				vec.push_back(cstr.GetBuffer(0));
				cstr.ReleaseBuffer();
				recordSet->MoveNext();
			}
		} else {
			recordSet->Close();
			recordSet.Release();
            error_msg = "too many fields, your SQL is wrong, please check your SQL!";
			return  false;
		}

		recordSet->Close();
		recordSet.Release();
		return true;
	}
	catch (...) {
		if (!vec.empty()) {
			vec.clear();
		}

        error_msg = "Query exception! Please check !";
		return  false;
	}
}



//---------------------------------------------------------
//功能  ： 查询多行多列数据，存入map
//参数  ： sql - SQL语句 , mapvec - 获取到多行多列的结果
//返回  ： 成功返回true，失败返回false
//---------------------------------------------------------
bool Mydb::exeSQL(const std::string& sql, std::map<int, std::vector<std::string> > &mapvec)
{
    clearErrorMsg();

	m_col = 0;
	m_row = 0;

	if (!mapvec.empty()) {
		mapvec.clear();
	}

	try {
		_RecordsetPtr recordSet = NULL;

		if (!m_adoconn.OpenAdoRecordSet(recordSet, sql.data(), adCmdText, adOpenStatic)) {
            error_msg = "Query Failed! Please check !";
			return false;
		}

		if (recordSet == NULL) {
            error_msg = "Query result is NULL!";
			recordSet->Close();
			recordSet.Release();
			return true;
		}

		m_col = recordSet->Fields->GetCount(); //获得查询列数
		//m_row = recordSet->GetRecordCount();   //获得查询行数 -- 太坑了，经常返回-1

		_variant_t value;
		std::string str_temp;

		//for (int i = 0; i < m_row; ++i) {
		while (!recordSet->adoEOF) {
			for (int j=0; j < m_col; ++j) {
				value = recordSet->Fields->Item[(long)(j)]->Value;
				str_temp = (const char*)_bstr_t(value);	// _variant_t 转 string
				mapvec[j].push_back(str_temp);
			}
			recordSet->MoveNext();
		}

		recordSet->Close();
		recordSet.Release();
		return true;
	}
	catch (...) {
         error_msg = "Query exception! Please check !";
		
		if (!mapvec.empty()) {
			mapvec.clear();
		}

		return  false;
    }
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



//------------------------------------------------------------
//功能  ： 清空mysql_error的信息
//参数  ：
//
//-----------------------------------------------------------
void Mydb::clearErrorMsg()
{
    error_msg = "";
}


