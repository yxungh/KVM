#pragma once


#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"
#include "XStoreTree.h"
#include "XListCtrl.h"
#include "XThemeText.h"
#include "XThemeBtn.h"

// XAbout 对话框
class XUserManage;
class XSubFolder;


class XFolder: public XBaseDialog
{
	DECLARE_DYNAMIC(XFolder)

public:
	XFolder(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XFolder();

	// 对话框数据
	enum { IDD=IDD_DIALOG_FOLDER };
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClkTree(NMHDR* pNMHDR,LRESULT* pResult);
	afx_msg void OnDblclkTree(NMHDR *pNMHDR,LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	BOOL InitImageList();

	void InitList();
	void InsertUserList();

	inline void SetRootItem(HTREEITEM h){m_hRootItem=h;}
	inline HTREEITEM GetRootItem(){return m_hRootItem;}
	inline void SetChildItem(HTREEITEM h){m_hChildItem=h;}
	inline HTREEITEM GetChildItem(){return m_hChildItem;}

	HTREEITEM AddRootItem(CString szRoot,int nType);
	HTREEITEM AddChildItem(CString szChild,HTREEITEM hItem,int nType);

	CString GetNodeNameByID(int nID);

	void DelAllSubItemByItem(HTREEITEM hItem);


	void ReloadInterface();
	void ReloadListInterface();

	//插入用户
	int AddListInfo(CString szID,CString szUserName,CString szUserGroup);
	void SetListInfo(int nCount,CString szID,CString szUserName,CString szUserGroup);
	CString GetUserNameByID(int nID);

	void SetVisibleUserSelect(CString szName);
	int GetItemIndexByUserID(int nID);

	void AddFolder();
	void DeleteFolder();

public:
	inline void SetManage(XUserManage* p){m_pManage=p;}
	void InsertFloder();
  	void InsertFloderInfo(CString szParent,HTREEITEM hItem);
	void InsertVisibleUser(CString szParent);
	//void InsetSubFolder();
	void DeleteFolderFromTree(int nID);
	void AddFolderToTree(CString szName);

	XSubFolder* GetSubFolderByName(CString szName);
	

private:

	XUserManage* m_pManage=NULL;
	XStoreTree m_Tree;
	CImageList m_ImageList;

	//HTREEITEM m_hTempItem=NULL;

	HTREEITEM m_hInputItem=NULL;
	HTREEITEM m_hOutputItem=NULL;

	HTREEITEM m_hRootItem=NULL;
	HTREEITEM m_hChildItem=NULL;
	HTREEITEM m_hSelItem=NULL;

	XListCtrl m_ListVisible;

	XThemeText m_TextTree;
	XThemeText m_TextUser;
	XThemeBtn m_BtnAddFolder;
	XThemeBtn m_BtnDelFolder;


};
