#pragma once

class XThemeBtn: public CWnd
{
	DECLARE_DYNAMIC(XThemeBtn)

public:
	XThemeBtn();
	virtual ~XThemeBtn();

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

private:

	enum
	{
		State_Normal,
		State_Focus,
		State_Press,
		State_Disable
	};

public:

	void SetCaption(CString szText);
	void SetCheck(BOOL bCheck);
	BOOL GetCheck();
	void SetFillColor(Gdiplus::Color col);

protected:

	virtual BOOL DrawItem(CDC *pDC);
	virtual void PostLClickMsg();

private:

	void DrawText(Graphics& graphics,CRect& rt);
	void DrawFillColor(Graphics& graphics,CRect& rt);

protected:

	//״̬
	DWORD m_dwState=State_Normal;
	//�ж�����Ƿ��뿪
	BOOL m_bMouseLeave=TRUE;
	//�ж�����Ƿ���
	BOOL m_bDowned=FALSE;
	//�ж�����Ƿ񼤻�
	BOOL m_bFocus=FALSE;
	//��ʾ����
	CString m_strText=_T("");
	//�����ɫ
	Gdiplus::Color m_FillColor;
};


