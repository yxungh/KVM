#pragma once
#include "XResult.h"


class XSplitSceneResult:public XResult
{
public:
	XSplitSceneResult();
	virtual ~XSplitSceneResult();


public:
	CString m_szSceneName=_T("");
	CString m_szWallName=_T("");
	BOOL m_bExist=FALSE;
	int m_nLast=0;
	BOOL m_bNewGroup=FALSE;
	CString m_szGroupName=_T("");
	//最后一个节点
	HTREEITEM m_hItem=NULL;

	//是否为改组名称
	int m_nAlter=0;
};

