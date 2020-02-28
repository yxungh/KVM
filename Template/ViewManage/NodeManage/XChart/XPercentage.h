#pragma once
#include "XChart.h"


class XPercentage:public XChart
{
public:
	XPercentage();
	~XPercentage();

public:
	void Draw(Graphics& graphics) override;
	RECTF GetRect() override;
	void SetPrecentageColor(Color b,Color e,Color ba,Color f) override;
	void SetCurRate(int n) override;
	void SetTitlt(CString szTitle) override;
	void SetCurRate(CString szTemper) override;
private:
	Color m_colorBack;
	Color m_colorFront;
	Color m_colorBegin;
	Color m_colorEnd;
	int m_nCurRate=0;
	static int m_nCount;
	CString m_szTitle=_T("");
};

