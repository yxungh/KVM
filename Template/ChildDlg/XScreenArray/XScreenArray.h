#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"

// XScreenArray 对话框

class XScreenArray : public XBaseDialog
{
	DECLARE_DYNAMIC(XScreenArray)

public:
	XScreenArray(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XScreenArray();
	virtual BOOL OnInitDialog();


// 对话框数据
	enum { IDD = IDD_DIALOG_SCREENARRAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnClickOk();
	DECLARE_MESSAGE_MAP()

private:

	void Init();
	void InitData();
	void ReloadInterface();
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

public:
	inline void SetScreenRow(int n){m_nScreenRow=n;}
	inline void SetScreenColumn(int n){m_nScreenColumn=n;}

	inline int GetScreenRow(){return m_nScreenRow;}
	inline int GetScreenColumn(){return m_nScreenColumn;}

private:

	int m_nScreenRow;
	int m_nScreenColumn;

	XThemeText m_TextRow;
	XThemeText m_TextColumn;

};
