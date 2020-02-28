#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"
#include "XThemeText.h"
#include "XThemeBtn.h"


// XAbout 对话框


class XAbout : public XBaseDialog
{
	DECLARE_DYNAMIC(XAbout)

public:
	XAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XAbout();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//afx_msg void OnBnClickedBtnUpdate();
	//afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnBTNLClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	void Init();

	void SetLogStatus(BOOL b);
	void SetVerStatus(BOOL b);

	inline void SetFPGAVer(CString szVer){m_szFPGAVer=szVer;}
	inline void SetLogin(BOOL b){m_bLogin=b;}

private:
	CString m_szFPGAVer=_T("");
	BOOL m_bLogin=FALSE;

	XThemeText m_TextInfo;
	XThemeText m_TextCopyRight;
	XThemeText m_TextFPGA;
	XThemeText m_TextVer;
	XThemeText m_TextUpdate;
	XThemeText m_TextVer2;
	XThemeText m_TextUpdate2;
	XThemeText m_TextVer3;
	XThemeText m_TextUpdate3;

	XThemeBtn m_BtnOk;
	XThemeBtn m_BtnUpdate;
};
