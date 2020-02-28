#pragma once


class XColorWnd:public CWnd
{
	DECLARE_DYNAMIC(XColorWnd)

public:
	XColorWnd();
	virtual ~XColorWnd();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID);

public:
	inline void SetClicked(BOOL b){m_bClicked=b;}
	inline BOOL GetClicked(){return m_bClicked;}

private:

	BOOL m_bClicked=FALSE;
};

