#include "stdafx.h"
#include "XFolderInfo.h"


XFolderInfo::XFolderInfo()
{
}


XFolderInfo::~XFolderInfo()
{
}


XSubFolder::XSubFolder()
{

}

XSubFolder::~XSubFolder()
{
	m_MapUserList.clear();
	m_MapTermList.clear();
	ClearMapFolderList();
}

void XSubFolder::ClearMapFolderList()
{
	for(auto& map:m_MapSubFolderList)
	{
		delete map.second;
	}
	m_MapSubFolderList.clear();
}