#pragma once
#include "XConstant.h"

class XFolderInfo
{
public:
	XFolderInfo();
	virtual ~XFolderInfo();

public:
	inline void SetID(int n){m_nID=n;}
	inline int GetID(){return m_nID;}

	inline void SetName(CString szName){m_szName=szName;}
	inline CString GetName(){return m_szName;}
	
	inline void SetType(int nType){m_nType=nType;}
	inline int GetType(){return m_nType;}

	inline void SetTreeItem(HTREEITEM h){m_hItem=h;}
	inline HTREEITEM GetTreeItem(){return m_hItem;}


protected:
	int m_nID=0;
	CString m_szName=_T("");
	//����1Ϊ���� 2Ϊ���
	int m_nType=0;

	HTREEITEM m_hItem=NULL;

};

class XSubFolder:public XFolderInfo
{
public:
	XSubFolder();
	virtual ~XSubFolder();

public:
	
	inline MAP_USERLIST& GetMapUserList(){return m_MapUserList;}
	inline MAP_TERMLIST& GetMapTermList(){return m_MapTermList;}
	inline MAP_SUBFOLDERLIST& GetMapSubFolderList(){return m_MapSubFolderList;}

	inline void SetParent(CString szParent){m_szParent=szParent;}
	inline CString GetParent(){return m_szParent;}

	inline void SetParentID(int nID){m_nParentID=nID;}
	inline int GetParentID(){return m_nParentID;}

public:
	void ClearMapFolderList();

private:
	//��ʵ�������ļ������ƺ�ID
	CString m_szParent=_T("");
	int m_nParentID=0;

	//��Ŀ¼�û��б�
	MAP_USERLIST m_MapUserList;
	//��Ŀ¼�ڵ��б�
	MAP_TERMLIST m_MapTermList;
	//���ļ����б�
	MAP_SUBFOLDERLIST m_MapSubFolderList;

};

