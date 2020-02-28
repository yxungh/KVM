#pragma once

class XThemeText: public CWnd
{
	DECLARE_DYNAMIC(XThemeText)

public:
	XThemeText();
	virtual ~XThemeText();

	virtual void PreSubclassWindow();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:

	void SetText(CString szText,BOOL bLeft=FALSE,BOOL bCenter=FALSE);
	void SetFillColor(COLORREF color);
	void SetTextColor(COLORREF color);
	void SetVertical(BOOL b);
	void SetTextSize(int nSize);
	//void SetLeft(BOOL b);

private:

	void DrawText(Graphics& graphics,CRect& rt);

protected:

	//填充颜色
	COLORREF m_FillColor=RGB(232,239,242);
	//文字颜色
	//COLORREF m_TextColor=RGB(0,0,0);
	//文字
	CString m_Text=_T("");
	//垂直
	BOOL m_Vertical=FALSE;
	//居左
	BOOL m_Left=FALSE;
	BOOL m_Center=FALSE;
	//字体大小
	int m_nTextSize=9;
};


