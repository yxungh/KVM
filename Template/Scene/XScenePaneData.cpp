#include "stdafx.h"
#include "XScenePaneData.h"
#include "XScene.h"
#include "XSceneInfo.h"
#include "XSceneGroupInfo.h"


XScenePaneData::XScenePaneData()
{
}


XScenePaneData::~XScenePaneData()
{
}

void XScenePaneData::GetData(XScene* pPane,CArchive& arch)
{
	MAP_SCENEGROUP& MapSceneGroup=pPane->GetMapSceneGroup();
	int nCount=0;
	arch>>nCount;
	for(int i=0;i<nCount;i++)
	{
		CString szGroupName=_T("");
		arch>>szGroupName;

		XSceneGroupInfo* pInfo=new XSceneGroupInfo;
		pInfo->SetGroupName(szGroupName);
		MapSceneGroup.insert(std::pair<CString,XSceneGroupInfo*>(szGroupName,pInfo));
	}

	//////////////////////////////////////////////////////////////////////////
	MAP_SCENE& MapScene=pPane->GetMapScene();
	int nSize=0;
	arch>>nSize;

	for(int i=0;i<nSize;i++)
	{
		CString szName=_T("");
		arch>>szName;

		CString szGroupName=_T("");
		arch>>szGroupName;

		XSceneInfo* pInfo=new XSceneInfo;
		pInfo->SetSceneName(szName);
		pInfo->SetSceneGroupName(szGroupName);
		if(MapScene.find(szName)==MapScene.end())
		{
			MapScene.insert(std::pair<CString,XSceneInfo*>(szName,pInfo));
		}
		else
		{
			MapScene[szName]=pInfo;
		}
	}
}


void XScenePaneData::SaveData(XScene* pPane,CArchive& arch)
{
	MAP_SCENEGROUP& MapSceneGroup=pPane->GetMapSceneGroup();
	int nCount=MapSceneGroup.size();
	arch<<nCount;
	for(auto& map:MapSceneGroup)
	{
		XSceneGroupInfo* pInfp=map.second;
		arch<<pInfp->GetGroupName();
	}

	//////////////////////////////////////////////////////////////////////////
	MAP_SCENE& MapScene=pPane->GetMapScene();
	int nSize=MapScene.size();
	arch<<nSize;

	for(auto& map:MapScene)
	{
		XSceneInfo* pInfo=map.second;
		arch<<pInfo->GetSceneName()
			<<pInfo->GetSceneGroupName();
	}
}