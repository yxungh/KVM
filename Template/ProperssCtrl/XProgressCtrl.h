#pragma once


class XProgressCtrl:public CProgressCtrl
{
	DECLARE_DYNAMIC(XProgressCtrl)
public:
	XProgressCtrl();
	virtual ~XProgressCtrl();

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	int SetPos(float nPos);
	int GetPos();
	void SetRange(int nLower,int nUpper);
	void SetPrgsColor(COLORREF cloor);
	void SetFreeColor(COLORREF cloor);
	void SetPrgsTextColor(COLORREF cloor);
	void SetFreeTextColor(COLORREF cloor);

private:
	COLORREF m_prgsColor;
	COLORREF m_freeColor;
	COLORREF m_prgsTextColor;
	COLORREF m_freeTextColor;

	int m_nMin=0;    //进度条的最小值，通常是0
	int m_nMax=150;    //进度条的最大值，通常是100
	float m_nPos=0;    //当前的进度
	float m_nBarWidth=0;  //进度条宽度
};
