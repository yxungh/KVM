#pragma once

class XDelegateConstantData;

class XConstantData
{
public:	
	~XConstantData();
private:
	XConstantData();

public:

	static XConstantData* GetInstance();

	static void Release();

	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetNodeType(int n){m_nNodeType=n;}
	inline int GetNodeType(){return m_nNodeType;}

	inline void SetNodeChannel(int n){m_nNodeChannel=n;}
	inline int GetNodeChannel(){return m_nNodeChannel;}

	inline void SetUserName(CString szName){m_szUserName=szName;}
	inline CString GetUserName(){return m_szUserName;}

	inline void SetDragType(int n){m_nDragType=n;}
	inline int GetDragType(){return m_nDragType;}

	inline void SetNodeName(CString szName){m_szNodeName=szName;}
	inline CString GetNodeName(){return m_szNodeName;}

	inline void SetMaster(BOOL b){m_bMaster=b;}
	inline BOOL GetMaster(){return m_bMaster;}

	inline void SetTreeItem(HTREEITEM item){m_hItem=item;}
	inline HTREEITEM GetTreeItem(){return m_hItem;}

	inline void SetGroupID(int n){m_nGroupID=n;}
	inline int GetGroupID(){return m_nGroupID;}

	inline void SetType(int n){m_nType=n;}
	inline int GetType(){return m_nType;}

	inline void SetGroupName(CString szName){m_szGroupName=szName;}
	inline CString GetGroupName(){return m_szGroupName;}

	//////////////////////////////////////////////////////////////////////////
	inline void SetSeatIndex(int n){m_nSeatIndex=n;}
	inline int GetSeatIndex(){return m_nSeatIndex;}
	//////////////////////////////////////////////////////////////////////////
	inline void SetNodeCaption(CString szName){m_szNodeCaption=szName;}
	inline CString GetNodeCaption(){return m_szNodeCaption;}

	inline void SetAvliNodeID(int n){m_nAvliNodeID=n;}
	inline int GetAvliNodeID(){return m_nAvliNodeID;}

	inline std::vector<int>& GetVecBlinkNodeID(){return m_VecBlinkNodeID;}

	inline void SetOldSceneName(CString szName){m_szOldSceneName=szName;}
	inline CString GetOldSceneName(){return m_szOldSceneName;}

	inline void SetOpenSceneName(CString szName) { m_szSceneName=szName; }
	inline CString GetOpenSceneName() { return m_szSceneName; }

	inline void SetSceneWall(CString szWall){m_szSceneWall=szWall;}
	inline CString GetSceneWall(){return m_szSceneWall;}

	inline void SetSceneType(int n){m_nSceneType=n;}
	inline int GetSceneType(){return m_nSceneType;}

	inline void SetInChannel(int nCh){m_nInChannel=nCh;}
	inline int GetInChannel(){return m_nInChannel;}
	
	inline void SetOutChannel(int nCh){m_nOutChannel=nCh;}
	inline int GetOutChannel(){return m_nOutChannel;}

	inline void SetSignalName(CString szName){ m_szSignalName=szName;}
	inline CString GetSignalName(){return m_szSignalName;}

	inline void SetSignalID(int n){m_nSignalID=n;}
	inline int GetSignalID(){return m_nSignalID;}

	inline void SetInputCh(int n){m_nInputCh=n;}
	inline int GetInputCh(){return m_nInputCh;}

	inline void SetSplitGroup(CString szName){m_szSplitGroup=szName;}
	inline CString GetSplitGroup(){return m_szSplitGroup;}

public:

	inline void SetDelegate(XDelegateConstantData* p){m_pDelegate=p;}

public:

	//void SetSeatArrageMaster(int nMaster);

private:

	static XConstantData* m_pData;

	XDelegateConstantData* m_pDelegate;

	//拖拽节点数据
	int m_nNodeID;
	int m_nNodeType;
	int m_nNodeChannel;

	//拖拽类型
	int m_nDragType;

	//拖拽用户列表
	CString m_szUserName;

	//拖拽节点
	CString m_szNodeName;
	BOOL m_bMaster;

	//坐席场景树项
	HTREEITEM m_hItem;

	//节点所在组
	int m_nGroupID;

	//拖拽类型（输入、输出）
	int m_nType;

	//拖拽节点组
	CString m_szGroupName;
	//////////////////////////////////////////////////////////////////////////
	//新
	//拖动坐席
	int m_nSeatIndex;

	//屏幕排列拖拽
	CString m_szNodeCaption;

	//排列推拽节点ID
	int m_nAvliNodeID;

	//////////////////////////////////////////////////////////////////////////
	//点击灯闪烁
	std::vector<int> m_VecBlinkNodeID;
	//////////////////////////////////////////////////////////////////////////
	//场景树旧名称
	CString m_szOldSceneName=_T("");
	int m_nSceneType=0;
	//调用场景名称
	CString m_szSceneName=_T("");
	CString m_szSceneWall=_T("");
	//////////////////////////////////////////////////////////////////////////
	//矩阵切换
	int m_nInChannel=0;
	int m_nOutChannel=0;
	//////////////////////////////////////////////////////////////////////////
	//拼接
	CString m_szSignalName=_T("");
	int m_nSignalID=0;
	int m_nInputCh=0;
	CString m_szSplitGroup=_T("");

};