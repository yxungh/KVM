#pragma once
#include "..\resource.h"
#include "XListCtrl.h"
#include <map>
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"


class XDelegateAddStore;

class XAddStore:public XBaseDialog
{
	DECLARE_DYNAMIC(XAddStore)

public:
	XAddStore(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XAddStore();

	// 对话框数据
	enum{IDD=IDD_DIALOG_ADDSTORE};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnNMClickPowerList(NMHDR *pNMHDR,LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()


public:
	inline void SetDelegate(XDelegateAddStore* p){m_pDelegate=p;}
	inline void SetCurUser(int n){m_nUserID=n;}

private:
	void Init();
	void InitList();
	void AddStoreList();
	void AddStoreList(int nNodeID,CString szNodeName,int nNodeType);
	void SetListInfo(int nCount,int nNodeID,CString szNodeName,int nNodeType);
	void ReloadInterface();

private:
	XListCtrl m_NodeList;
	XDelegateAddStore* m_pDelegate=NULL;
	std::map<int,int> m_MapSelect;
	int m_nUserID=0;

	XThemeText m_TextTitle;
	XThemeBtn m_BtnOK;
	XThemeBtn m_BtnCancel;
	
};

