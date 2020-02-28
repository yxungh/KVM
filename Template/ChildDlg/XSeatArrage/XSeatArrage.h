#pragma once
#include "XBaseWnd.h"

class XSeatArrageManage;

class XSeatArrage:public XBaseWnd
{
	DECLARE_DYNAMIC(XSeatArrage)

public:
	XSeatArrage();
	virtual ~XSeatArrage();

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

public:
	void InitTips();
	void ReloadInterface();
	void DrawRect(Graphics& graphics,CRect& rt);

public:

	inline void SetManage(XSeatArrageManage* p){m_pManage=p;}

public:

	void Show();
	void Hide();
	void Move(CPoint point);

private:

	XSeatArrageManage* m_pManage;

	CToolTipCtrl m_TipCtrl;
	CString m_szTips;
};