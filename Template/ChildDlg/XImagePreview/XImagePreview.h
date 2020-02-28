#pragma once
#include "..\resource.h"


class XDelegateImagePreview;
class XBtn;

class XImagePreview:public CDialogEx
{
	DECLARE_DYNAMIC(XImagePreview)

public:
	XImagePreview(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XImagePreview();

	virtual BOOL OnInitDialog();
	virtual void OnOk();

	// 对话框数据
	enum { IDD = IDD_DIALOG_IMAGEPREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnBTNLClick(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

protected:

	virtual void DrawDlg(CDC* pDC);

public:

	inline void SetDelegate(XDelegateImagePreview* p){m_pDelegate=p;}

	inline void SetImageIndex(int n){m_nImageIndex=n;}

private:

	void Init();

	void InitData();

	void CreateBtn();

	void OnBtnFront();

	void OnBtnBack();

	void UpdateBtnStatus();

	void ReloadInterface();



private:

	XDelegateImagePreview* m_pDelegate;

	CString m_szPhotoPath;

	int m_nImageCount;

	XBtn* m_pFront;

	XBtn* m_pBack;

	int m_nImageIndex;

};
