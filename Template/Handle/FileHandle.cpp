#include "StdAfx.h"
#include "FileHandle.h"
#include "HandlePath.h"

FileHandle::FileHandle(void)
{
}


FileHandle::~FileHandle(void)
{
}

/***********************************************************
** ��������: ����·�������ļ���

** �������: CString& path ·��

** ������: BOOL TRUE:�ɹ�;FALSE :ʧ��
************************************************************/
BOOL FileHandle::createFolder(CString& path)
{
	if(!HandlePath::PathExists(path))
	{
		return CreateDirectory(path,NULL);
	}
	else
	{
		return TRUE;
	}
}

/***********************************************************
** ��������: �����ļ�

** �������: CString& szUrl		Ҫ���Ƶ��ļ�·��
			 CString& szNewUrl	Ŀ���ļ�·��

** ������: BOOL TRUE:�ɹ�;FALSE :ʧ��
************************************************************/
BOOL FileHandle::copyFile(CString& szUrl,CString& szNewUrl)
{
	if(!HandlePath::PathExists(szUrl))
	{
		return FALSE;
	}

	if(szUrl==szNewUrl)
	{
		return TRUE;
	}

	//if(MoveFileEx(szUrl,szNewUrl,MOVEFILE_REPLACE_EXISTING))
	//{
	//	return TRUE;
	//}
	//else
	//{
	//	return FALSE;
	//}

	//�����򸲸��ļ�
	if(CopyFile(szUrl,szNewUrl,FALSE))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL FileHandle::delFile(CString path)
{
	return ::DeleteFile(path);
}

BOOL FileHandle::CopyDirectory(CString szSrcDirectry,CString szDstDirectory)
{
	if(!createFolder(szDstDirectory))
	{
		return false;
	}

	BOOL result=TRUE;

	CFileFind finder;

	CString stPath=szSrcDirectry+_T("/*.*");

	BOOL bWorking=finder.FindFile(stPath);

	while(bWorking && result)
	{
		bWorking=finder.FindNextFile();

		if(finder.IsDots())
		{
			continue;
		}
		else if(finder.IsDirectory())
		{
			result=CopyDirectory(finder.GetFilePath(),szDstDirectory+_T("/")+finder.GetFileName());
		}
		else
		{
			result=copyFile(finder.GetFilePath(),szDstDirectory+_T("/")+finder.GetFileName());
		}
	}

	return result;
}

BOOL FileHandle::renamefile(CString path,CString newpath)
{
	CFile::Rename(path,newpath);

	return TRUE;
}
