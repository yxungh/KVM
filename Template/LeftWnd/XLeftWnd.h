#pragma once
#include "XTreeCtrl.h"
#include "XConstant.h"

class XDelegateLeftWnd;

class XLeftWnd:public CDockablePane
{
	DECLARE_DYNAMIC(XLeftWnd)

public:
	virtual ~XLeftWnd();
private:
	XLeftWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* pWnd,CPoint point);
	afx_msg void OnNMRClickTree(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnDblclkTree(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnTvnEndlabeledit(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnAlterGroup();
	afx_msg void OnDelGroup();
	afx_msg void OnAlterNode();
	afx_msg void OnRemoveNodeInGroup();
	afx_msg void OnAddGroup();
	afx_msg void OnAddMainAndSecond();

	DECLARE_MESSAGE_MAP()

public:

	inline void SetDelagate(XDelegateLeftWnd* p){m_pDelegate=p;}

public:

	static XLeftWnd* GetInstance();
	static void Release();
	void Init();
	//根据集合初始化树
	void InitTreeListItemOfUser();
	//根据集合初始化树
	void InitTreeListItemOfNode();
	//初始化矩阵切换树
	void InitTreeListItemOfMatrix();
	//初始化树拼接
	void InitTreeListItemOfSplit();
	//插入项
	void InsertItemToTree(CString szUserName);
	//删除项
	void DeleteItemFromTree(CString szUserName);
	void DeleteNodeGroupFromTree(HTREEITEM item);
	//退出登录
	void ClearTree();
	//点击设置属性中用户栏
	void SetPropertyValue(CString szUserName);
	//点击选中节点
	void SetNodeSelected(CString szNodeName);
	//翻译
	void ReloadInterface();

	//获取权限集合
	MAP_POWER& GetMapPower();
	MAP_NODE& GetMapNode();
	MAP_NODEGROUP& GetMapNodeGroup();
	MAP_GROUPMAINSEC& GetMapNodeGroupMainSec();
	VEC_DRAG& GetVecDrag();
	MAP_DRAG& GetMapDrag();
	//获取从组里删除的节点
	VEC_DEL& GetVecDel();
	//创建拖动窗口
	XDragWnd* CreateDragWnd();
	//拖拽结束
	void DragEnd(CPoint& point,CRect& rect);
	//设置节点不能拖拽
	void SetNodeDrag(int nNodeID,BOOL b);
	//设置节点颜色
	void SetNodeColor(int nNodeID,BOOL b);
	//显示坐席
	void ShowGroupSeatArrage(CString szGroup);
	//更该坐席名称
	void UpdateGroupNameAfterChange(HTREEITEM item,CString szName);
	//更改组名
	void ChangeGroupItemText(HTREEITEM item,CString szName);
	//逐个添加组
	void AddNodeGroup(CString szGroupName,int nType,BOOL bMainSec);
	//添加节点到组
	void AddNodeInGroup(XNode* pNode,int nGroupID);
	void AddNodeInGroupMaster(int nNodeID,int nGroupID);
	//更改节点名称
	void ChangeNodeItemText(HTREEITEM item,CString szNodeName);
	//获取父节点
	HTREEITEM GetParentItem(HTREEITEM item);
	//添加没组节点到树
	void AddNodeInTreeLast(XNode* pNode,int nType);
	//拖拽添加组
	void AddGroup(HTREEITEM hItemFirst,HTREEITEM hItemSecond);
	//拖拽删除组
	void DragDelGroup(CString szGroupName);
	//点击输入组隐藏菜单按钮
	void HidePopMenuBtn();
	//显示按钮
	void ShowPopMenuBtn();
	//切换工具栏
	void ResetRibbonBar();
	//判断名称是否存在
	BOOL DecidedGroupNameExist(CString szName);
	BOOL DecidedNodeNameExist(CString szName);
	//返回数据，拼接输入
	void ReciveDataOfSplitInput(char* pData);

private:

	//创建Pane
	void CreatePane();
	//初始化树形控件
	BOOL InitTreeCtrl();
	//初始化图片列表
	BOOL InitImageList();
	//调整布局
	void AdjustLayout();
	//递归遍历树
	HTREEITEM FindItem(HTREEITEM item,CString szItemText);
	//创建拖拽窗口
	void CreateWnd();
	//获取节点
	XNode* GetNodeByID(int nNodeID);
	//获取节点
	XNode* GetNodeByName(CString szName);
	//获取组
	XNodeGroupInfo* GetNodeGroupByName(CString szName);
	//添加父节点
	HTREEITEM AddRootItem(CString szRoot,int nType);
	//设置节点
	void SetItemRoot(HTREEITEM h);
	//获取根节点
	HTREEITEM GetItemRoot();
	//添加子节点
	HTREEITEM AddChildItem(CString szChild,int nType,int nGroupType=-1);
	//设置子节点
	void SetItemChild(HTREEITEM h);
	//获取子节点
	HTREEITEM GetItemChild();
	//添加节点
	HTREEITEM AddSubItem(CString szSub);
	//求出组在树中的顺序
	int GetGroupIndexInTree(std::vector<CString>& VecStr,CString szGroupName);
	//获取默认组名称
	CString GetGroupNameByFrontName(CString szName);
	//显示组菜单
	void ShowGroupMenu();
	//显示节点菜单
	void ShowNodeMenuInGroup();
	void ShowNodeMenuNotInGroup();
	//右键创建组
	void ShowMenuOfAddGroup(DWORD& dData);
	//根据组名称获取ID
	int GetGroupIDByName(CString szGroupName);
	//判断节点在不在组中
	BOOL DecidedNodeInGroup(VEC_ARRAGE& VecArrage,int nNodeID);
	//判断节点在不在组里
	BOOL JudgeNodeInGroup(XNode* pNode);


private:

	void ClearVecDrag();
	void ClearVecDel();
	void ClearSplitInput();

	//////////////////////////////////////////////////////////////////////////
public:
	//拖拽组到坐席上面
	void DragGroupToSeat(CString szGroupName,CPoint& point);
	//点击组切换页面
	void SwitchPage(int nPage);
	//绘制输入屏幕
	void DrawGroupInScreen(CString szGroupName);
	//选中页面坐席
	void SetSeatSelected(CString szGroupName);
	//获取当前拼接放缩比例
	float GetCurScale();

private:

	static XLeftWnd* m_pLeftWnd;
	XDelegateLeftWnd* m_pDelegate;
	XTreeCtrl m_TreeCtrl;
	CImageList m_ImageList;

	//拖拽窗口
	XDragWnd* m_pDragWnd;

	CString m_szTitle;

	HTREEITEM m_hRootItem;

	HTREEITEM m_hChildItem;

	HTREEITEM m_hSubItem;

	HTREEITEM m_hItemInput;
	HTREEITEM m_hItemOutput;

	//拖拽节点ID（从组中删除节点ID,视图中要删除）或者拖拽删除组，保存组成员
	VEC_DRAG m_VecDrag;

	//移至其他组(拖拽ID，被拖拽ID)
	MAP_DRAG m_MapDrag;

	//从组里删除的节点
	VEC_DEL m_VecDel;

private:

	//输入源集合
	VEC_SPLITINPUT m_VecSplitInput;


};