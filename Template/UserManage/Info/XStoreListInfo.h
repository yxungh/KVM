#pragma once

class XStoreListInfo
{
public:
	XStoreListInfo();
	~XStoreListInfo();

public:

	inline void SetNodeType(int n){m_nNodeType=n;}
	inline int GetNodeType(){return m_nNodeType;}

	inline void SetUserID(int n){m_nUserID=n;}
	inline int GetUserID(){return m_nUserID;}

	inline void SetUserName(CString szName){m_szUserName=szName;}
	inline CString GetUserName(){return m_szUserName;}


	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetNodeName(CString szName){m_szNodeName=szName;}
	inline CString GetNodeName(){return m_szNodeName;}

	inline void SetNumber(int n){m_nNumber=n;}
	inline int GetNumber(){return m_nNumber;}

	inline void SetTreeItem(HTREEITEM h){m_hItem=h;}
	inline HTREEITEM GetTreeItem(){return m_hItem;}

private:

	int m_nNodeType=2;
	int m_nUserID=-1;
	CString m_szUserName=_T("");
	int m_nNodeID=0;
	CString m_szNodeName=_T("");
	//返回序号暂时没用到
	int m_nNumber=0;
	//所在节点
	HTREEITEM m_hItem=NULL;
};