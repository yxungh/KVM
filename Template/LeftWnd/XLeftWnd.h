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
	//���ݼ��ϳ�ʼ����
	void InitTreeListItemOfUser();
	//���ݼ��ϳ�ʼ����
	void InitTreeListItemOfNode();
	//��ʼ�������л���
	void InitTreeListItemOfMatrix();
	//��ʼ����ƴ��
	void InitTreeListItemOfSplit();
	//������
	void InsertItemToTree(CString szUserName);
	//ɾ����
	void DeleteItemFromTree(CString szUserName);
	void DeleteNodeGroupFromTree(HTREEITEM item);
	//�˳���¼
	void ClearTree();
	//��������������û���
	void SetPropertyValue(CString szUserName);
	//���ѡ�нڵ�
	void SetNodeSelected(CString szNodeName);
	//����
	void ReloadInterface();

	//��ȡȨ�޼���
	MAP_POWER& GetMapPower();
	MAP_NODE& GetMapNode();
	MAP_NODEGROUP& GetMapNodeGroup();
	MAP_GROUPMAINSEC& GetMapNodeGroupMainSec();
	VEC_DRAG& GetVecDrag();
	MAP_DRAG& GetMapDrag();
	//��ȡ������ɾ���Ľڵ�
	VEC_DEL& GetVecDel();
	//�����϶�����
	XDragWnd* CreateDragWnd();
	//��ק����
	void DragEnd(CPoint& point,CRect& rect);
	//���ýڵ㲻����ק
	void SetNodeDrag(int nNodeID,BOOL b);
	//���ýڵ���ɫ
	void SetNodeColor(int nNodeID,BOOL b);
	//��ʾ��ϯ
	void ShowGroupSeatArrage(CString szGroup);
	//������ϯ����
	void UpdateGroupNameAfterChange(HTREEITEM item,CString szName);
	//��������
	void ChangeGroupItemText(HTREEITEM item,CString szName);
	//��������
	void AddNodeGroup(CString szGroupName,int nType,BOOL bMainSec);
	//��ӽڵ㵽��
	void AddNodeInGroup(XNode* pNode,int nGroupID);
	void AddNodeInGroupMaster(int nNodeID,int nGroupID);
	//���Ľڵ�����
	void ChangeNodeItemText(HTREEITEM item,CString szNodeName);
	//��ȡ���ڵ�
	HTREEITEM GetParentItem(HTREEITEM item);
	//���û��ڵ㵽��
	void AddNodeInTreeLast(XNode* pNode,int nType);
	//��ק�����
	void AddGroup(HTREEITEM hItemFirst,HTREEITEM hItemSecond);
	//��קɾ����
	void DragDelGroup(CString szGroupName);
	//������������ز˵���ť
	void HidePopMenuBtn();
	//��ʾ��ť
	void ShowPopMenuBtn();
	//�л�������
	void ResetRibbonBar();
	//�ж������Ƿ����
	BOOL DecidedGroupNameExist(CString szName);
	BOOL DecidedNodeNameExist(CString szName);
	//�������ݣ�ƴ������
	void ReciveDataOfSplitInput(char* pData);

private:

	//����Pane
	void CreatePane();
	//��ʼ�����οؼ�
	BOOL InitTreeCtrl();
	//��ʼ��ͼƬ�б�
	BOOL InitImageList();
	//��������
	void AdjustLayout();
	//�ݹ������
	HTREEITEM FindItem(HTREEITEM item,CString szItemText);
	//������ק����
	void CreateWnd();
	//��ȡ�ڵ�
	XNode* GetNodeByID(int nNodeID);
	//��ȡ�ڵ�
	XNode* GetNodeByName(CString szName);
	//��ȡ��
	XNodeGroupInfo* GetNodeGroupByName(CString szName);
	//��Ӹ��ڵ�
	HTREEITEM AddRootItem(CString szRoot,int nType);
	//���ýڵ�
	void SetItemRoot(HTREEITEM h);
	//��ȡ���ڵ�
	HTREEITEM GetItemRoot();
	//����ӽڵ�
	HTREEITEM AddChildItem(CString szChild,int nType,int nGroupType=-1);
	//�����ӽڵ�
	void SetItemChild(HTREEITEM h);
	//��ȡ�ӽڵ�
	HTREEITEM GetItemChild();
	//��ӽڵ�
	HTREEITEM AddSubItem(CString szSub);
	//����������е�˳��
	int GetGroupIndexInTree(std::vector<CString>& VecStr,CString szGroupName);
	//��ȡĬ��������
	CString GetGroupNameByFrontName(CString szName);
	//��ʾ��˵�
	void ShowGroupMenu();
	//��ʾ�ڵ�˵�
	void ShowNodeMenuInGroup();
	void ShowNodeMenuNotInGroup();
	//�Ҽ�������
	void ShowMenuOfAddGroup(DWORD& dData);
	//���������ƻ�ȡID
	int GetGroupIDByName(CString szGroupName);
	//�жϽڵ��ڲ�������
	BOOL DecidedNodeInGroup(VEC_ARRAGE& VecArrage,int nNodeID);
	//�жϽڵ��ڲ�������
	BOOL JudgeNodeInGroup(XNode* pNode);


private:

	void ClearVecDrag();
	void ClearVecDel();
	void ClearSplitInput();

	//////////////////////////////////////////////////////////////////////////
public:
	//��ק�鵽��ϯ����
	void DragGroupToSeat(CString szGroupName,CPoint& point);
	//������л�ҳ��
	void SwitchPage(int nPage);
	//����������Ļ
	void DrawGroupInScreen(CString szGroupName);
	//ѡ��ҳ����ϯ
	void SetSeatSelected(CString szGroupName);
	//��ȡ��ǰƴ�ӷ�������
	float GetCurScale();

private:

	static XLeftWnd* m_pLeftWnd;
	XDelegateLeftWnd* m_pDelegate;
	XTreeCtrl m_TreeCtrl;
	CImageList m_ImageList;

	//��ק����
	XDragWnd* m_pDragWnd;

	CString m_szTitle;

	HTREEITEM m_hRootItem;

	HTREEITEM m_hChildItem;

	HTREEITEM m_hSubItem;

	HTREEITEM m_hItemInput;
	HTREEITEM m_hItemOutput;

	//��ק�ڵ�ID��������ɾ���ڵ�ID,��ͼ��Ҫɾ����������קɾ���飬�������Ա
	VEC_DRAG m_VecDrag;

	//����������(��קID������קID)
	MAP_DRAG m_MapDrag;

	//������ɾ���Ľڵ�
	VEC_DEL m_VecDel;

private:

	//����Դ����
	VEC_SPLITINPUT m_VecSplitInput;


};