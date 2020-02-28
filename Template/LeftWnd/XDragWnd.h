#pragma once

class XDragInfo;
class XLeftWnd;


class XDragWnd: public CWnd
{
	DECLARE_DYNAMIC(XDragWnd)

public:
	XDragWnd();
	virtual ~XDragWnd();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID);

public:

	inline void SetLeftWnd(XLeftWnd* p)
	{
		m_pLeftWnd=p;
	}

	inline void SetCaption(CString szCaption)
	{
		m_szCaption=szCaption;
	}

	void Show();

	void Hide();

	void Move(CPoint point);

private:

	XLeftWnd* m_pLeftWnd;

	CString m_szCaption;

};


