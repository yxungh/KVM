#pragma once
#include "XBaseWnd.h"

class XSeatArrageManage;

class XMenuWnd:public XBaseWnd
{
	DECLARE_DYNAMIC(XMenuWnd)
public:
	XMenuWnd();
	virtual ~XMenuWnd();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL DrawItem(CDC *pDC);
	virtual void Move(CPoint point);


public:

	void DrawRect(Graphics& graphics, CRect& rt);
};