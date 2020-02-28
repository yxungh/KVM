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

	//�����ɫ
	COLORREF m_FillColor=RGB(232,239,242);
	//������ɫ
	//COLORREF m_TextColor=RGB(0,0,0);
	//����
	CString m_Text=_T("");
	//��ֱ
	BOOL m_Vertical=FALSE;
	//����
	BOOL m_Left=FALSE;
	BOOL m_Center=FALSE;
	//�����С
	int m_nTextSize=9;
};


