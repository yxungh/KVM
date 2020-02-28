#pragma once

#include "..\resource.h"
#include "XDialog.h"
#include "HandlePath.h"

class XDelegateImage;
class XProgressCtrl;

class XImage : public XDialog
{
	DECLARE_DYNAMIC(XImage)

public:
	XImage(CWnd* pParent = NULL,CString szPhotoPath=_T(""));   // 标准构造函数
	virtual ~XImage();

	virtual BOOL OnInitDialog();
	virtual void OnOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawDlg(CDC* pDC);

	// 对话框数据
	enum { IDD = IDD_DIALOG_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	inline void SetDelegate(XDelegateImage* p){m_pDelegate=p;}

	inline void SetInputChannel(int n){m_nInputChannel=n;}

public:

	void SetOperate(int nPixIndex);

	void SendOSDPicOrder();

private:

	void Init();

	void ResetDlgSize();

	void HideCursor(BOOL bHide);

	void SetShowImage(int nIndex);

	void CreateProgressBar();

	void SendDataOfOSDImage(int nIndex);

	void SetMatrixInputToOutput();

private:

	XDelegateImage* m_pDelegate;

	XProgressCtrl* m_pProgress;

	int m_nPicIndex;

	int m_nPos;
	int m_nInputChannel;

	DWORD m_dwTime=0;

};
