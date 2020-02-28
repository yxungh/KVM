#pragma once


class XThemeGroupBox:public CStatic
{
	DECLARE_DYNAMIC(XThemeGroupBox)

public:
	XThemeGroupBox();
	virtual ~XThemeGroupBox();

	void SetHeaderTheme(COLORREF clrs[],UINT nEffect);
	inline void SetBorderColor(COLORREF clr) { m_crBorder=clr; };
	inline void SetTextColor(COLORREF clr) { m_crText=clr; }
	void SetHeaderHeight(int nY);
	void Draw(CDC *pDC=NULL);


protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
	int		m_nHeaderHeight;
	COLORREF	m_crBorder;
	COLORREF	m_crText;
};

