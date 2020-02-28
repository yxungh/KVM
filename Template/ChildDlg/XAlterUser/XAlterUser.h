#pragma once
#include "..\resource.h"
#include "XListCtrl.h"
#include "XConstant.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"


class XDelegateAlterUser;

// XAlterUser 对话框

class XAlterUser:public XBaseDialog
{
	DECLARE_DYNAMIC(XAlterUser)

public:
	XAlterUser(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XAlterUser();

	virtual BOOL OnInitDialog();
	virtual void OnOK();

// 对话框数据
	enum { IDD=IDD_DIALOG_ALTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnButtonClick();
	afx_msg void OnNMClickPowerList(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:

	void Init();
	//void InitPowerList();
	void ReloadInterface();
	//void AddPowerInfo();
	//void SetPowerSelect();
	//int AddListInfo(CString szInfo);
	//void SetListInfo(int nCount,CString szInfo);
	////int GetPowerIndexByName(CString szPowerName);
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

public:

	inline void SetDelegate(XDelegateAlterUser* p){m_pDelegate=p;}

	inline void SetUserName(CString szName){m_szUserName=szName;}
	inline CString GetUserName(){return m_szUserName;}
	inline CString GetPassWd(){return m_szPassWd;}
	//inline MAP_SELECT& GetMapSelect(){return m_MapSelect;}


public:

	void ClearMapUserPower();
	void ClearMapSelect();

private:

	XDelegateAlterUser* m_pDelegate=nullptr;
	//XListCtrl m_PowerList;

	CString m_szUserName=_T("");
	CString m_szPassWd=_T("");

private:

	XThemeText m_TextName;
	XThemeText m_TextPassWd;
	XThemeText m_TextTip;

	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;

};
