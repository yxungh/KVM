#pragma once

#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"

// XMessageBoxDlg 对话框

class XMessageBoxDlg : public XBaseDialog
{
	DECLARE_DYNAMIC(XMessageBoxDlg)

public:
	XMessageBoxDlg(CString szText, CString szCaption, UINT uType, 
		CWnd* pParent = NULL);

	virtual ~XMessageBoxDlg();

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	// 对话框数据
	enum { IDD = IDD_DIALOG_MESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()


private:

	//初始化控件
	void InitControl();

	//初始化静态文本控件
	void InitControlOfStatic();

	//初始化按钮控件
	void InitControlOfButtn();

	//调整布局
	void AdjustLayout();

	//调整静态文本布局
	void AdjustLayoutOfStatic(CRect& rectDlg);

	//调整按钮布局
	void AdjustLayoutOfButtn(CRect& rectDlg);

	//清除
	void Clear();


private:

	CString m_szText;

	CString m_szCaption;

	UINT m_uType;

	XThemeText* m_pStatic;

	XThemeBtn* m_pBtnArr;

	int m_nBtnCount;
};
