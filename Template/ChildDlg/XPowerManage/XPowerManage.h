#pragma once
#include "..\resource.h"
#include "XConstant.h"
#include "XListCtrl.h"
#include "XDelegateAddUser.h"
#include "XDelegateAlterUser.h"
#include "XDelegateCopyUser.h"
#include "XDelegateAddStore.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"
#include "XThemeGroupBox.h"


class XDelegatePowerManage;
class XPower;
class XSubUserInfo;
class XAddUser;
class XAlterUser;
class XCopyUser;

class XPowerManage:public XBaseDialog,
				   public XDelegateAddUser,
				   public XDelegateAlterUser,
	               public XDelegateCopyUser,
	               public XDelegateAddStore
{
	DECLARE_DYNAMIC(XPowerManage)

public:
	XPowerManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XPowerManage();

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	// 对话框数据
	enum { IDD = IDD_DIALOG_POWERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBtnClickedAll();
	afx_msg void OnBtnClickedAllNot();
	afx_msg void OnBtnClickedOther();

	afx_msg void OnBtnClickedAdd();
	afx_msg void OnBtnClickedAlter();
	afx_msg void OnBtnClickedCopy();
	afx_msg void OnBtnClickedDel();

	afx_msg void OnBtnClickedQueryStore();
	afx_msg void OnBtnClickedAddStore();
	afx_msg void OnBtnClickedDelStore();

	afx_msg void OnNMClickPowerList(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnNMClickUserList(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnNMClickSubPowerList(NMHDR *pNMHDR,LRESULT *pResult);

	afx_msg void OnBnClickedSuball();
	afx_msg void OnBnClickedSubother();
	afx_msg void OnBnClickedSuballnot();

	afx_msg void OnBnClickedRadiosel();
	//afx_msg void OnBnClickedRadioTypeAll();
	//afx_msg void OnBnClickedRadioTypeNone();
	//afx_msg void OnBnClickedRadioTypeValid();

	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);
	
	DECLARE_MESSAGE_MAP()

public:
	virtual MAP_POWER& GetMapPower();
	virtual CString GetUserName();
	virtual int GetPowerIndexByName(CString szPowerName);
	virtual void SetUserInfo(CString szUserName,CString szPassWd);
	virtual void AddUser();
	virtual void AlterUser();
	virtual void CopyUser();
	virtual MAP_NODE& GetMapNode();
	virtual MAP_STORE& GetMapStore();

public:
	inline void SetDelegate(XDelegatePowerManage* p){m_pDelegate=p;}
	inline void SetQueryUserID(int n){m_nQueryStoreUserID=n;}

public:

	//添加用户更新用户表
	void UpdateUserList(int nID,CString szUserName);
	//删除用户
	void DelUserFromMapAndList(CString szDelUserName);
	//更新收藏列表
	void UpdateStoreList();
	//更新权限选中列表
	void UpdatePowerList(CString szName);
	//删除收藏列表
	void DelStoreList(int nNodeID);
	//关闭添加用户窗口
	void CloseAddUserDlg();
	void CloseAlterUserDlg();
	void CloseCopyUserDlg();
	
private:

	void Init();
	//初始化权限数据
	void InitData();
	//初始化列表
	void InitList();
	//初始化权限列表
	void InitPowerList();
	//设置权限列表
	void InitUserPower();
	//初始化用户列表
	void InitUserList();
	//初始化当前用户信息列表
	void InitUserInfoList();
	//设置当前用户信息
	void InitUserInfo();
	//设置子用户列表
	void InitUser();
	//初始化收藏列表
	void InitStoreList();
	//设置收藏列表
	void InitStore();
	//添加权限信息
	void AddPowerInfo();	
	//初始化子权限列表
	void InitSubPowerList();
	void InitSubPower(int nIndex);
	//添加子权限
	int AddSubPowerInfo(int nNodeID,CString szNodeName);
	//初始化下拉列表
	//void InitSubCombo();
	void InitRadio();
	//重载界面
	void ReloadInterface();
	//重载列表界面
	void ReloadListInterface();
	//获取当前用户自用户列表(分页)
	void GetCurUserSubUserList(int nIndex,int nSize);
	//翻译
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));
	//当前用户列表
	int AddListInfo(CString szInfo,CString szUserInfo=_T(""));
	void SetListInfo(int nCount,CString szInfo,CString szUserInfo=_T(""));
	//用户列表
	int AddUserListInfo(int nID,CString szUserName,CString szCreateTime,CString szGroup=_T(""));
	void SetUserListInfo(int nCount,CString szID,CString szUserName,CString szCreateTime,CString szGroup=_T(""));
	//收藏列表
	int AddStoreListInfo(int nNodeID,CString szNodeName,int nNodeType,int nNumber=0);
	void SetStoreListInfo(int nCount,CString szNodeID,CString szNodeName,int nNodeType,int nNumber);

	//根据名称获取权限序号
	//int GetPowerIndexByName(CString szPowerName);
	//初始化子用户权限
	void InitSubUserPower(CString szSubUser);
	//初始化查询用户ID
	void InitQueryUserID();

	//初始化子权限
	void InitSubPowerByUser(CString szUserName);

	void SetSubPowerTitle(CString szTitle,int nIndex);
	void SetSubPowerList(int nCount,int nNodeID,CString szName,CString szItem=_T(""));
	void SubSelectByNodeID(VEC_SUBSELECT& VecSelect,int nNodeID,int nIndex);
	void SubPowerListSelectAll(VEC_SUBSELECT& VecSel);
	void SubPowerListSelectOther(VEC_SUBSELECT& VecSel);
	BOOL GetNodeInVecSelect(VEC_SUBSELECT& VecSel,CString szName);
	BOOL GetNodeInVecSelect(VEC_NODEID& VecNodeID,CString szName);
	void DeleteNodeByName(VEC_SUBSELECT& VecSel,CString szName);

	void SetPowerListSelectByUser();
	void SetSubPowerListSelectByUser();

	//解析和写权限
	void ParsePrivilege(VEC_PRIVILEGE& VecPrivilige,VEC_NODEID& VecNodeID,CString szUserName=_T(""));
	void ParsePrivilege(VEC_PRIVILEGE& VecPrivilige,MAP_CTRLPRIVILEGE& MapPrivilege,CString szUserName=_T(""));
	void WritePrivilege(VEC_PRIVILEGE& VecPrivilige,VEC_SUBSELECT& VecNodeID);
	void WritePrivilege(VEC_PRIVILEGE& VecPrivilige,MAP_CTRLPRIVILEGE& MapPrivilege);

	void SetPrivilegeBySelect(VEC_SUBSELECT& VecSelect,MAP_CTRLPRIVILEGE& MapPrivilege,int nType);
	//////////////////////////////////////////////////////////////////////////
	int GetColumnCount();
	int GetItemCount();
	void InsertSubPowerList(int nItem,int nRadio);


private:
	void ClearMapUserPower();
	void ClearMapSubUserPower();
	void ClearMapSelect();
	void ClearMapPrivilege();

private:
	XDelegatePowerManage* m_pDelegate=nullptr;
	XPower* m_pPower=nullptr;
	XAddUser* m_pAddUser=nullptr;
	XAlterUser* m_pAlterUser=nullptr;
	XCopyUser* m_pCopyUser=nullptr;

	XListCtrl m_PowerList;
	XListCtrl m_UserInfo;
	XListCtrl m_UserList;
	XListCtrl m_StoreList;
	XListCtrl m_SubPowerList;

	CString m_szQueryStoreUser=_T("");
	int m_nQueryStoreUserID=0;

	//添加用户名称
	CString m_szUserName=_T("");
	CString m_szPassWd=_T("");
	CString m_szCopyUserName=_T("");
	DWORD m_dwTime=0;
	int m_nRadioSelect=0;

private:
	//用户权限(32位序号)
	MAP_USERPOWER m_MapUserPower;
	//子用户权限(32位序号)
	MAP_USERPOWER m_MapSubUserPower;
	//选择权限列表(权限序号)
	MAP_SELECT m_MapSelect;
	//接管选择
	VEC_SUBSELECT m_VecCtrlSel;
	//预览选择
	VEC_SUBSELECT m_VecViewSel;
	//登录选择
	VEC_SUBSELECT m_VecLoginSel;
	VEC_SUBSELECT m_VecMonCtrlSel;

	//用户子权限节点ID集合
	//VEC_NODEID m_VecCtrlNodeID;
	//VEC_NODEID m_VecViewNodeID;
	MAP_CTRLPRIVILEGE m_MapPrivilege;
	VEC_NODEID m_VecLoginNodeID;

	//////////////////////////////////////////////////////////////////////////
	XThemeText m_TextGroup1;
	XThemeText m_TextGroup2;
	XThemeText m_TextGroup3;
	XThemeText m_TextGroup4;
	XThemeText m_TextTip;

	XThemeBtn m_BtnAll;
	XThemeBtn m_BtnOther;
	XThemeBtn m_BtnAllNot;
	XThemeBtn m_BtnSubAll;
	XThemeBtn m_BtnSubOther;
	XThemeBtn m_BtnSubAllNot;

	XThemeBtn m_BtnAddUser;
	XThemeBtn m_BtnAlterUser;
	XThemeBtn m_BtnCopyUser;
	XThemeBtn m_BtnDelUser;

	XThemeBtn m_BtnQueryStore;
	XThemeBtn m_BtnAddStore;
	XThemeBtn m_BtnDelStore;

	
};
