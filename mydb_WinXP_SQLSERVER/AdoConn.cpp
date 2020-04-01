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
		//sprintf(sMsg,"Warning: 打开数据库连接(OpenAdoConn)异常.错误信息：%s; 文件：%s; 行：%d",e.ErrorMessage(),__FILE__,__LINE__);
		//memset(sMsg,0,512);
		//sprintf(sMsg,"错误代码:%08x,错误代码信息:%s,错误源:%s,错误描述:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());
		
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
		//sprintf(sMsg,"Warning: 判断数据库是否打开(IsOpenAdoConn)异常. 错误信息: %s; 文件: %s; 行: %d",e.ErrorMessage(),__FILE__,__LINE__);

		//memset(sMsg,0,512);
		//sprintf(sMsg,"错误代码:%08x,错误代码信息:%s,错误源:%s,错误描述:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());

		//断开重连
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
		//sprintf(sMsg,"Warning: 重新打开数据库(ReOpenAdoConn)异常.错误信息：%s; 文件：%s; 行：%d",e.ErrorMessage(),__FILE__,__LINE__);

		//memset(sMsg,0,512);
		//sprintf(sMsg,"错误代码:%08x,错误代码信息:%s,错误源:%s,错误描述:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());
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
		//连接数据库，如果Connection为空，则重新连接数据库
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
		//sprintf(sMsg,"Warning:执行语句(ExecuteSql)异常.SQL语句:%s,错误信息：%s; 文件：%s; 行：%d",pSql, e.ErrorMessage(),__FILE__,__LINE__);

		//memset(sMsg,0,512);
		//sprintf(sMsg,"错误代码:%08x,错误代码信息:%s,错误源:%s,错误描述:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());

		//断开重连
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
		//连接数据库，如果Connection为空，则重新连接数据库
		if(!IsOpenAdoConn())
		{
			ReOpenAdoConn();
		}
		//创建记录集对象
		recordSet.CreateInstance(__uuidof(Recordset));
		//取得表中记录	
		recordSet->Open(_bstr_t(pSql),m_pAdoConn.GetInterfacePtr(),CursorType,LockType,lOption);
	}
	//捕捉异常
	catch(_com_error e)
	{
		//显示错误信息
		//char sMsg[512];
		//memset(sMsg,0,512);
		//sprintf(sMsg,"Warning:打开记录集(OpenAdoRecordSet)异常.语句:%s, 错误信息: %s; 文件：%s; 行: %d",pSql,e.ErrorMessage(),__FILE__,__LINE__);

		//memset(sMsg,0,512);
		//sprintf(sMsg,"错误代码:%08x,错误代码信息:%s,错误源:%s,错误描述:%s",e.Error(),e.ErrorMessage(),(char*)e.Source(),(char*)e.Description());

		//断开重连
		CloseAdoConn();
		ReOpenAdoConn();
		
		return false;
	}

	return true;
}
