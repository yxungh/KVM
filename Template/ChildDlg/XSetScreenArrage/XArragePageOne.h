#pragma once
#include "..\resource.h"


// XArragePageOne 对话框
class XDelegateArragePageOne;

class XArragePageOne : public CPropertyPage
{
	DECLARE_DYNAMIC(XArragePageOne)

public:
	XArragePageOne();   // 标准构造函数
	virtual ~XArragePageOne();
	virtual BOOL OnInitDialog();


// 对话框数据
	enum { IDD = IDD_DIALOG_SEATARRAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	//virtual void OnShowWindow(BOOL bShow, UINT nStatus);

private:
	void Init();
	void InitData();
	void ReloadInterface();
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

	BOOL DecidedNameExist(CString szName);

public:
	inline void SetDelegate(XDelegateArragePageOne* p){m_pDelegate=p;}

private:
	XDelegateArragePageOne* m_pDelegate;
};
