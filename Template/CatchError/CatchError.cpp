#include "stdafx.h"
#include "CatchError.h"
#include "DbgHelp.h"
#pragma comment(lib,"DbgHelp.Lib") 

CString CatchError::m_DumpFolderPath=_T("");

/***********************************************************
** ��������: ����Dump�ļ�
************************************************************/
void CreateDumpFile(LPCTSTR lpstrDumpFilePathName,EXCEPTION_POINTERS* pException)
{
	// ����Dump�ļ�     
	HANDLE hDumpFile=CreateFile(lpstrDumpFilePathName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	// Dump��Ϣ   
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers=pException;
	dumpInfo.ThreadId=GetCurrentThreadId();
	dumpInfo.ClientPointers=TRUE;

	// д��Dump�ļ�����   
	MiniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),hDumpFile,MiniDumpNormal,&dumpInfo,NULL,NULL);
	CloseHandle(hDumpFile);
}

/***********************************************************
** ��������: Ӧ�ó����쳣���ú���
************************************************************/
LONG ApplicationCrashHandler(EXCEPTION_POINTERS* pException)
{
	CreateDumpFile(CatchError::DumpPath(),pException);
	FatalAppExit(-1,_T("The Application Error!"));
	return EXCEPTION_EXECUTE_HANDLER;
}

void CatchError::SetCatchError(CString folderPath)
{
	m_DumpFolderPath=folderPath;
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
}

CString CatchError::DumpPath()
{
	CString szTemp=_T("");

	CTime t=CTime::GetCurrentTime();

	szTemp.Format(_T("%s\\%d-%02d-%02d %02d:%02d.dmp"),m_DumpFolderPath,
				  t.GetYear(),
				  t.GetMonth(),
				  t.GetDay(),
				  t.GetHour(),
				  t.GetMinute(),
				  t.GetSecond());

	return szTemp;
}