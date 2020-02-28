#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeBtn.h"
#include "XThemeText.h"



class XAddSplit:public XBaseDialog
{
	DECLARE_DYNAMIC(XAddSplit)

public:
	XAddSplit(CWnd* pParent=NULL);   // 标准构造函数
	virtual ~XAddSplit();

	// 对话框数据
	enum {IDD=IDD_DIALOG_ADDSPLIT};
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void ReloadInterface();
	void OnBtnOk();

public:
	inline CString GetSplitName(){return m_szName;}
	inline int GetRow(){return m_nRow;}
	inline int GetColumn(){return m_nColumn;}

private:

	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnCancel;
	XThemeText m_TextName;
	XThemeText m_TextRow;
	XThemeText m_TextColumn;



	CString m_szName=_T("");
	int m_nRow=0;
	int m_nColumn=0;

};

