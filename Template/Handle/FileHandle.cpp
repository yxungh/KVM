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
** 功能描述: 根据路径创建文件夹

** 输入参数: CString& path 路径

** 输出结果: BOOL TRUE:成功;FALSE :失败
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
** 功能描述: 复制文件

** 输入参数: CString& szUrl		要复制的文件路径
			 CString& szNewUrl	目标文件路径

** 输出结果: BOOL TRUE:成功;FALSE :失败
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

	//存在则覆盖文件
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
