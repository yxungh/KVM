#pragma once


class XTabCtrl:public CMFCTabCtrl
{
	DECLARE_DYNCREATE(XTabCtrl)

public:
	XTabCtrl();
	virtual ~XTabCtrl();

	virtual CWnd* FindTargetWnd(const CPoint& pt);

protected:

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()

};