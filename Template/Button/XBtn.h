#pragma once

class XBtn: public CWnd
{
	DECLARE_DYNAMIC(XBtn)

public:
	XBtn();
	virtual ~XBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);

protected:

	enum
	{
		State_Normal,
		State_Focus,
		State_Press,
		State_Disable
	};

public:

	void SetImage(CString szImg);

	void SetCaption(CString szText);

	void SetCheck(BOOL bCheck);

	BOOL GetCheck();

	void SetFillColor(Gdiplus::Color col);

	void SetStatus(BOOL b);

protected:

	virtual BOOL DrawItem(CDC *pDC);

	virtual void DrawImg(Graphics& graphics,CRect& rt);

	virtual void PostLClickMsg();

public:

	void DrawText(Graphics& graphics,CRect& rt);

	void DrawFillColor(Graphics& graphics,CRect& rt);

protected:

	//״̬
	DWORD m_dwState;

	//�ж�����Ƿ��뿪
	BOOL m_bMouseLeave;

	//�ж�����Ƿ���
	BOOL m_bDowned;

	//�ж�����Ƿ񼤻�
	BOOL m_bFocus;

	//ͼƬ·��
	CString m_strImg;

	//��ʾ����
	CString m_strText;

	//�Ƿ������ɫ
	BOOL m_bFillColor;

	//�����ɫ
	Gdiplus::Color m_FillColor;
};


