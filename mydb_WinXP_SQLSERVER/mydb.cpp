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
//����  �� ��ѯ��������
//����  �� sql - SQL��� , str - ��ȡ���Ľ��
//����  �� �ɹ�����true��ʧ�ܷ���false
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

	if (!recordSet->adoEOF) {	//��ȡ1��
		cstr = recordSet->GetCollect(_variant_t((long)0)); //ȡ��һ�е�ֵ���еļ�����0��ʼ
	}

	if (!cstr.IsEmpty()) {
		str = cstr.GetBuffer(0);	//CString ת string		
	} else {
        error_msg = "Query result is NULL!";
		str = "";	//�����ѯ���Ϊ�գ��򸳿�
	}

	recordSet->Close();
	recordSet.Release();
	return true;
}



//------------------------------------------------
//����  �� ��ѯ1�����ݣ�����vec
//����  �� sql - SQL��� , vec - ��ȡ��1�еĽ��
//����  �� �ɹ�����true��ʧ�ܷ���false
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

		m_col = recordSet->Fields->GetCount(); //��ò�ѯ����
                //m_row = recordSet->GetRecordCount();   //��ò�ѯ����

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
//����  �� ��ѯ���ж������ݣ�����map
//����  �� sql - SQL��� , mapvec - ��ȡ�����ж��еĽ��
//����  �� �ɹ�����true��ʧ�ܷ���false
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

		m_col = recordSet->Fields->GetCount(); //��ò�ѯ����
		//m_row = recordSet->GetRecordCount();   //��ò�ѯ���� -- ̫���ˣ���������-1

		_variant_t value;
		std::string str_temp;

		//for (int i = 0; i < m_row; ++i) {
		while (!recordSet->adoEOF) {
			for (int j=0; j < m_col; ++j) {
				value = recordSet->Fields->Item[(long)(j)]->Value;
				str_temp = (const char*)_bstr_t(value);	// _variant_t ת string
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
//����  �� �����ִ��󣬷���mysql_error����Ϣ
//����  ��
//
//------------------------------------------------------------
std::string Mydb::getErrorMsg()
{
    return error_msg;
}



//------------------------------------------------------------
//����  �� ���mysql_error����Ϣ
//����  ��
//
//-----------------------------------------------------------
void Mydb::clearErrorMsg()
{
    error_msg = "";
}


