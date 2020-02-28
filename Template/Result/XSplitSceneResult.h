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
	//���һ���ڵ�
	HTREEITEM m_hItem=NULL;

	//�Ƿ�Ϊ��������
	int m_nAlter=0;
};

