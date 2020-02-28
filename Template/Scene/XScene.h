#pragma once
#include "XSceneTree.h"
#include "XConstant.h"

class XDelegateScene;
class XLeftWnd;

class XScene:public CDockablePane
{
	DECLARE_DYNAMIC(XScene)

public:
	virtual ~XScene();
private:
	XScene();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* pWnd,CPoint point);
	afx_msg void OnNMRClickTree(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnDblclkTree(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void AlterScene();
	afx_msg void DelScene();
	afx_msg void Remove();
	afx_msg void RemoveFromSplitGroup();

	afx_msg void AlterSplitScene();
	afx_msg void DelSplitScene();
	afx_msg void AlterSplitGroup();
	afx_msg void DelSplitGroup();

	DECLARE_MESSAGE_MAP()


public:

	static XScene* GetInstance();
	static void Release();
	void AddSceneToTree(CString szName);
	void AddGroup(HTREEITEM hItemFirst,HTREEITEM hItemSecond);
	void AddSplitGroup(HTREEITEM hItemFirst,HTREEITEM hItemSecond);
	void AddSplitGroup(CString szGroupName,HTREEITEM hItem);
	void AddSplitSceneToGroup(CString szGroupName,CString szSceneName);
	void DelSplitSceneByItem(CString szSceneName);
	void DelSplitGroupByItem(HTREEITEM hItem);
	void AddSplitSceneAtLast(CString szSceneName);


public:
	inline void SetDelegate(XDelegateScene* p){m_pDelegate=p;}
	inline MAP_SCENE& GetMapScene(){return m_MapScene;}
	inline MAP_SCENEGROUP& GetMapSceneGroup(){return m_MapSceneGroup;}

public:

	void Init();
	void SetUpPane(XLeftWnd* p);
	//void InitScene();
	void InitSceneOfTakeOver();
	void InitSceneOfSplit();
	void ClearSceneTree();

	void ReloadInterface();

	void OpenScene(int nData);
	void AddSplitScene(CString szName,CString szGroup);
	void DeleteSplitScene(HTREEITEM hItem);

private:

	//创建Pane
	void CreatePane();
	//初始化树形控件
	BOOL InitTreeCtrl();
	//初始化图片列表
	BOOL InitImageList();
	//调整布局
	void AdjustLayout();
	

	HTREEITEM AddRootItem(CString szRoot,int nType=0,HTREEITEM hItem=NULL);
	HTREEITEM AddChildItem(CString szChild,int nType=0);
	void SetItemRoot(HTREEITEM h);
	HTREEITEM GetItemRoot();
	void ShowGroupMenu();
	void ShowSceneMenu();
	void ShowSplitMenu();
	void ShowSplitGroup();
	BOOL DecidedNameExist(CString szName,int nType=0);
	CString GetGroupNameByFrontName(CString szName);
	CString GetSplitGroupNameByFrontName(CString szName);
	void SaveItem(CString szName,HTREEITEM hItem);
	HTREEITEM GetItemWhere();
	void SetSceneGroupName(CString szName,CString szGroupName);


private:

	void ClearMapScene();
	void ClearMapItem();
	void ClearMapSceneGroup();

public:

	void SaveData(CArchive& arch);
	void GetData(CArchive& arch);
	
private:

	static XScene* m_pInstance;
	XDelegateScene* m_pDelegate=NULL;
	XSceneTree m_TreeCtrl;
	CImageList m_ImageList;
	XLeftWnd* m_pLeftWnd=NULL;
	HTREEITEM m_hRootItem=NULL;
	HTREEITEM m_TempItem=NULL;

	CString m_szTitle=_T("");

private:
	//场景集合（场景名称）
	MAP_SCENE m_MapScene;
	MAP_SCENEGROUP m_MapSceneGroup;
	MAP_HTREEITEM m_MapItem;

};

