#include "stdafx.h"
#include "XSceneData.h"
#include "XNodeManage.h"
#include "XTakeOver.h"


XSceneData::XSceneData()
{
}


XSceneData::~XSceneData()
{
}

BOOL XSceneData::SaveData(XNodeManage* p,CString szPath)
{
	CFile mFile;
	if(mFile.Open(szPath,CFile::modeCreate|CFile::modeWrite))
	{
		CArchive arch(&mFile,CArchive::store);
		SaveData(p,arch);
		arch.Close();
		mFile.Close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void XSceneData::SaveData(XNodeManage* p,CArchive& arch)
{
	MAP_TAKEOVER& MapTakeOver=p->GetMapTakeOver();
	int nSize=MapTakeOver.size();
	arch<<nSize;

	for(auto& map:MapTakeOver)
	{
		int nFirst=map.first;
		arch<<nFirst;

		XTakeOver* pTakeOver=map.second;
		arch<<pTakeOver->GetNodeID();
		arch<<pTakeOver->GetTargetID();
		arch<<pTakeOver->GetExclusive();
	}
}

//////////////////////////////////////////////////////////////////////////
BOOL XSceneData::GetData(XNodeManage* p,CString szPath)
{
	CFile mFile;
	if(mFile.Open(szPath,CFile::modeRead))
	{
		CArchive arch(&mFile,CArchive::load);
		GetData(p,arch);
		arch.Close();
		mFile.Close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void XSceneData::GetData(XNodeManage* p,CArchive& arch)
{
	MAP_TAKEOVER& MapTakeOver=p->GetMapTakeOver();
	for(auto& map:MapTakeOver)
	{
		delete map.second;
	}
	MapTakeOver.clear();
	//////////////////////////////////////////////////////////////////////////
	int nSize=0;
	arch>>nSize;

	for(int i=0;i<nSize;i++)
	{
		int nFirst=0;
		arch>>nFirst;

		int nNodeID=0;
		arch>>nNodeID;

		int nTargetID=0;
		arch>>nTargetID;

		BOOL bExclesive=FALSE;
		arch>>bExclesive;

		XTakeOver* pTakeOver=new XTakeOver;
		pTakeOver->SetNodeID(nNodeID);
		pTakeOver->SetTargetID(nTargetID);
		pTakeOver->SetExclusive(bExclesive);

		if(MapTakeOver.find(nFirst)==MapTakeOver.end())
		{
			MapTakeOver.insert(std::pair<int,XTakeOver*>(nFirst,pTakeOver));
		}
		else
		{
			MapTakeOver[nFirst]=pTakeOver;
		}
	}
}
