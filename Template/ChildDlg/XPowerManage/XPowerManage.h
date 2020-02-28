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
	XPowerManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XPowerManage();

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	// �Ի�������
	enum { IDD = IDD_DIALOG_POWERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

	//����û������û���
	void UpdateUserList(int nID,CString szUserName);
	//ɾ���û�
	void DelUserFromMapAndList(CString szDelUserName);
	//�����ղ��б�
	void UpdateStoreList();
	//����Ȩ��ѡ���б�
	void UpdatePowerList(CString szName);
	//ɾ���ղ��б�
	void DelStoreList(int nNodeID);
	//�ر�����û�����
	void CloseAddUserDlg();
	void CloseAlterUserDlg();
	void CloseCopyUserDlg();
	
private:

	void Init();
	//��ʼ��Ȩ������
	void InitData();
	//��ʼ���б�
	void InitList();
	//��ʼ��Ȩ���б�
	void InitPowerList();
	//����Ȩ���б�
	void InitUserPower();
	//��ʼ���û��б�
	void InitUserList();
	//��ʼ����ǰ�û���Ϣ�б�
	void InitUserInfoList();
	//���õ�ǰ�û���Ϣ
	void InitUserInfo();
	//�������û��б�
	void InitUser();
	//��ʼ���ղ��б�
	void InitStoreList();
	//�����ղ��б�
	void InitStore();
	//���Ȩ����Ϣ
	void AddPowerInfo();	
	//��ʼ����Ȩ���б�
	void InitSubPowerList();
	void InitSubPower(int nIndex);
	//�����Ȩ��
	int AddSubPowerInfo(int nNodeID,CString szNodeName);
	//��ʼ�������б�
	//void InitSubCombo();
	void InitRadio();
	//���ؽ���
	void ReloadInterface();
	//�����б����
	void ReloadListInterface();
	//��ȡ��ǰ�û����û��б�(��ҳ)
	void GetCurUserSubUserList(int nIndex,int nSize);
	//����
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));
	//��ǰ�û��б�
	int AddListInfo(CString szInfo,CString szUserInfo=_T(""));
	void SetListInfo(int nCount,CString szInfo,CString szUserInfo=_T(""));
	//�û��б�
	int AddUserListInfo(int nID,CString szUserName,CString szCreateTime,CString szGroup=_T(""));
	void SetUserListInfo(int nCount,CString szID,CString szUserName,CString szCreateTime,CString szGroup=_T(""));
	//�ղ��б�
	int AddStoreListInfo(int nNodeID,CString szNodeName,int nNodeType,int nNumber=0);
	void SetStoreListInfo(int nCount,CString szNodeID,CString szNodeName,int nNodeType,int nNumber);

	//�������ƻ�ȡȨ�����
	//int GetPowerIndexByName(CString szPowerName);
	//��ʼ�����û�Ȩ��
	void InitSubUserPower(CString szSubUser);
	//��ʼ����ѯ�û�ID
	void InitQueryUserID();

	//��ʼ����Ȩ��
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

	//������дȨ��
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

	//����û�����
	CString m_szUserName=_T("");
	CString m_szPassWd=_T("");
	CString m_szCopyUserName=_T("");
	DWORD m_dwTime=0;
	int m_nRadioSelect=0;

private:
	//�û�Ȩ��(32λ���)
	MAP_USERPOWER m_MapUserPower;
	//���û�Ȩ��(32λ���)
	MAP_USERPOWER m_MapSubUserPower;
	//ѡ��Ȩ���б�(Ȩ�����)
	MAP_SELECT m_MapSelect;
	//�ӹ�ѡ��
	VEC_SUBSELECT m_VecCtrlSel;
	//Ԥ��ѡ��
	VEC_SUBSELECT m_VecViewSel;
	//��¼ѡ��
	VEC_SUBSELECT m_VecLoginSel;
	VEC_SUBSELECT m_VecMonCtrlSel;

	//�û���Ȩ�޽ڵ�ID����
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
