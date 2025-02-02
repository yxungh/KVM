#pragma once
#include "..\resource.h"
#include "XColorWnd.h"
#include "XThemeText.h"
#include "XThemeBtn.h"
#include "XBaseDialog.h"

// XCenterControl 对话框

class XCenterControl : public XBaseDialog
{
	DECLARE_DYNAMIC(XCenterControl)

public:
	XCenterControl(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~XCenterControl();
	virtual BOOL OnInitDialog();

// 对话框数据

	enum {IDD=IDD_DIALOG_CONTROL};


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();
	afx_msg void OnBnClickedBtn3();
	afx_msg void OnBnClickedBtn4();
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void InitColorWnd1();
	void InitColorWnd2();
	void InitColorWnd3();
	void InitColorWnd4();
	void InitShow();
	void SaveStatus(CString szKey,BOOL b);
private:

	XColorWnd* m_pColorWnd1=NULL;
	XColorWnd* m_pColorWnd2=NULL;
	XColorWnd* m_pColorWnd3=NULL;
	XColorWnd* m_pColorWnd4=NULL;
	BOOL m_bFirstClick=FALSE;
	BOOL m_bSecondClick=FALSE;
	BOOL m_bThreeClick=FALSE;
	BOOL m_bFourClick=FALSE;

	XThemeBtn m_Btn1;
	XThemeBtn m_Btn2;
	XThemeBtn m_Btn3;
	XThemeBtn m_Btn4;
	XThemeText m_TextTip;
};
