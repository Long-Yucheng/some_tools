// Copyright [2017-01-09] <Copyright Owner: Frank.Long>
// ADOConn.h: interface for the CADOConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCONN_H__67F7CB59_0AD0_4B27_9FA0_197CF8478437__INCLUDED_)
#define AFX_ADOCONN_H__67F7CB59_0AD0_4B27_9FA0_197CF8478437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#pragma warning(disable:4146)
#import "C:\Program Files\Common Files\System\ado\msado15.dll" \
	no_namespace \
	rename("EOF","adoEOF") rename ("BOF","adoBOF") 

#pragma warning(disable: 4251)


class CAdoConn  
{
public:
	CAdoConn();
	virtual ~CAdoConn();

public:
	/*--------------------------------------------------------------
	���ܣ������ݿ�����
	������pUser  �û���
	      pPsw   ����
		  pDb    ���ݿ�����
		  pSrc   ����Դ�����Ǳ���Ϊ�գ���Ϊ������������ΪIP��ַ
	����ֵ��
	---------------------------------------------------------------*/
	bool OpenAdoConn(const char *pUser,const char *pPsw, const char *pDb, const char *pSrc);
	bool IsOpenAdoConn();
	//���´�����
	bool ReOpenAdoConn();
	void CloseAdoConn();
	//ִ��SQL���
	bool ExecuteSql(const char *pSql, long lOptions = adCmdText);
	bool OpenAdoRecordSet(_RecordsetPtr &recordSet, const char* pSql, long lOption = adCmdText, CursorTypeEnum CursorType = adOpenDynamic, LockTypeEnum LockType = adLockOptimistic);
	
private:
	_ConnectionPtr m_pAdoConn;
	//_RecordsetPtr  m_pAdoRecordset;
	_bstr_t m_bstrSql;

};

#endif // !defined(AFX_ADOCONN_H__67F7CB59_0AD0_4B27_9FA0_197CF8478437__INCLUDED_)

