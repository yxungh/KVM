#pragma once
#include "XChart.h"

class XInserument:public XChart
{
public:
	XInserument();
	~XInserument();

public:
	void Draw(Graphics& graphics) override;
	RECTF GetRect() override;
	void SetInstrumentColor(Color b,Color e,Color ba,Color f) override;
	void SetDegress(int nTemper) override;
	void SetTitlt(CString szTitle) override;

private:
	Color m_colorBack;
	Color m_colorFront;
	Color m_colorBegin;
	Color m_colorEnd;

	float m_nDegress=0;
	int m_nTemper=0;
	CString m_szTitle=_T("");

};

