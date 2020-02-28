#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"
#include "XListCtrl.h"
#include <vector>


class XDelegateSaveSplitScene;

class XSaveSplitScene:public XBaseDialog
{
	DECLARE_DYNAMIC(XSaveSplitScene)

public:
	XSaveSplitScene(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XSaveSplitScene();

	// 对话框数据
	enum{IDD=IDD_DIALOG_SAVESPLITSCENE};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	afx_msg void OnUpdateEditName();
	DECLARE_MESSAGE_MAP()

private:

	void OnBtnOk();
	int AddListInfo(CString szName);
	void SetListInfo(int nCount,CString szName);

public:
	inline void SetDelegate(XDelegateSaveSplitScene* p){m_pDelegate=p;}
	inline std::vector<CString>& GetVecSplit(){return m_VecSplit;}
	inline CString GetName(){return m_szName;}
	inline CString GetGroup(){return m_szGroup;}

public:
	void Init();
	void InitList();
	void InitData();
	void InitCombo();
	void ReloadInterface();

	void OnCloseDlg();


private:
	XDelegateSaveSplitScene* m_pDelegate=NULL;
	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;
	XThemeText m_TextName;
	XThemeText m_TextList;
	XThemeText m_TextGroup;
	//XThemeText m_TextScene;
	XListCtrl m_SplitList;

	std::vector<CString> m_VecSplit;
	CString m_szName=_T("");
	CString m_szGroup=_T("");

};

