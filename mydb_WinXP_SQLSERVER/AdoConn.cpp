// Copyright [2017-01-09] <Copyright Owner: Frank.Long>
// AdoConn.cpp: implementation of the CAdoConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdoConn.h"
#include <stdio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAXBCPCOUNT 10000

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoConn::CAdoConn()
{
	m_pAdoConn = NULL;
	CoInitialize(NULL);
}

CAdoConn::~CAdoConn()
{
	CloseAdoConn();
	CoUninitialize();
}


bool CAdoConn::OpenAdoConn(const char *pUser,const char *pPsw, const char *pDb, const char *pSrc)
{
	if (strlen(pUser)==0||strlen(pPsw)==0||strlen(pDb)==0)
	{
		return false;
	}

	try
	{
		char sSql[256];
		memset(sSql,0,256);
		sprintf(sSql,"Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%s;Data Source=%s",pPsw,pUser,pDb,pSrc);
		m_bstrSql = (_bstr_t)sSql;
		m_pAdoConn.CreateInstance("ADODB.Connection");
		m_pAdoConn->Open(m_bstrSql,"","",adModeUnknown);
	}
	catch(_com_error e)
	{
		//char sMsg[512];
		//memset(sMsg,0,512);
		//sprintf(sMsg,"Warning: �����ݿ�����(OpenAdoConn)�쳣.������Ϣ��%s; �ļ���%s; �У�%d",e.ErrorMessage(),__FILE__,__LINE__);
		//memset(sMsg,0,512);
		//sprintf(sMsg,"�������:%08x,���������Ϣ:%s,����Դ:%s,��������:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());
		
		return false;
	}

	return true;
}

bool CAdoConn::IsOpenAdoConn()
{
	try
	{
		return (m_pAdoConn != NULL && (m_pAdoConn->State & adStateOpen));
	}
	catch (_com_error e)
	{
		//char sMsg[512];
		//memset(sMsg,0,512);
		//sprintf(sMsg,"Warning: �ж����ݿ��Ƿ��(IsOpenAdoConn)�쳣. ������Ϣ: %s; �ļ�: %s; ��: %d",e.ErrorMessage(),__FILE__,__LINE__);

		//memset(sMsg,0,512);
		//sprintf(sMsg,"�������:%08x,���������Ϣ:%s,����Դ:%s,��������:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());

		//�Ͽ�����
		CloseAdoConn();
		ReOpenAdoConn();
		
		return false;
	} 
	return false;
}

bool CAdoConn::ReOpenAdoConn()
{
	try
	{
		m_pAdoConn.CreateInstance("ADODB.Connection");
		m_pAdoConn->Open(m_bstrSql,"","",adModeUnknown);
	}
	catch(_com_error e)
	{
		//char sMsg[512];
		//memset(sMsg,0,512);
		//sprintf(sMsg,"Warning: ���´����ݿ�(ReOpenAdoConn)�쳣.������Ϣ��%s; �ļ���%s; �У�%d",e.ErrorMessage(),__FILE__,__LINE__);

		//memset(sMsg,0,512);
		//sprintf(sMsg,"�������:%08x,���������Ϣ:%s,����Դ:%s,��������:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());
		//adolog.writeLog(error, sMsg);
		
		return false;
	}

	return true;
}

void CAdoConn::CloseAdoConn()
{
	if (m_pAdoConn != NULL)
	{
		m_pAdoConn->Close();
		m_pAdoConn.Release();
		m_pAdoConn = NULL;	
	}
}

bool CAdoConn::ExecuteSql(const char *pSql, long lOptions/* = adCmdText*/)
{
	if (strlen(pSql)==0)
	{
		return false;
	}
	try
	{
		//�������ݿ⣬���ConnectionΪ�գ��������������ݿ�
		if (!IsOpenAdoConn())
		{
			ReOpenAdoConn();
		}
		m_pAdoConn->Execute(_bstr_t(pSql),NULL,lOptions);
		return true;
	}
	catch(_com_error e)
	{
		//char sMsg[512];
		//memset(sMsg,0,512);
		//sprintf(sMsg,"Warning:ִ�����(ExecuteSql)�쳣.SQL���:%s,������Ϣ��%s; �ļ���%s; �У�%d",pSql, e.ErrorMessage(),__FILE__,__LINE__);

		//memset(sMsg,0,512);
		//sprintf(sMsg,"�������:%08x,���������Ϣ:%s,����Դ:%s,��������:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());

		//�Ͽ�����
		CloseAdoConn();
		ReOpenAdoConn();

		return false;
	}
}

bool CAdoConn::OpenAdoRecordSet(_RecordsetPtr &recordSet,const char* pSql, long lOption/* = adCmdText*/, CursorTypeEnum CursorType/* = adOpenStatic*/, LockTypeEnum LockType/* = adLockOptimistic*/)
{
	if (strlen(pSql)==0)
	{
		return false;
	}
	try
	{
		//�������ݿ⣬���ConnectionΪ�գ��������������ݿ�
		if(!IsOpenAdoConn())
		{
			ReOpenAdoConn();
		}
		//������¼������
		recordSet.CreateInstance(__uuidof(Recordset));
		//ȡ�ñ��м�¼	
		recordSet->Open(_bstr_t(pSql),m_pAdoConn.GetInterfacePtr(),CursorType,LockType,lOption);
	}
	//��׽�쳣
	catch(_com_error e)
	{
		//��ʾ������Ϣ
		//char sMsg[512];
		//memset(sMsg,0,512);
		//sprintf(sMsg,"Warning:�򿪼�¼��(OpenAdoRecordSet)�쳣.���:%s, ������Ϣ: %s; �ļ���%s; ��: %d",pSql,e.ErrorMessage(),__FILE__,__LINE__);

		//memset(sMsg,0,512);
		//sprintf(sMsg,"�������:%08x,���������Ϣ:%s,����Դ:%s,��������:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());

		//�Ͽ�����
		CloseAdoConn();
		ReOpenAdoConn();
		
		return false;
	}

	return true;
}
