#pragma once


// XDialog �Ի���

class XDialog : public CDialogEx
{
	DECLARE_DYNAMIC(XDialog)

public:
	XDialog(UINT nIDD,CWnd *pParent,CString szPhotoPath);   // ��׼���캯��
	virtual ~XDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	DECLARE_MESSAGE_MAP()

protected:

	//���ƶԻ���
	virtual void DrawDlg(CDC* pDC);

	//������ť
	//void CreateBtn(CWnd* pParent, XBtn* pBtn, CRect rect, 
	//	UINT nID, CString szPhotoPath);

protected:

	//VK_RETURN״̬
	BOOL m_bEnableVK_RETURN;

	//VK_ESCAPE״̬
	BOOL m_bEnableVK_ESCAPE;

	//�Ƿ��б�����
	BOOL m_bNcHitTest;

	//ͼƬ
	CString m_szPhotoPath;
};
