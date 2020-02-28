#pragma once
#include "XChart.h"
class XProgressBar:public XChart
{
public:
	XProgressBar();
	~XProgressBar();

public:
	void Draw(Graphics& graphics) override;
	RECTF GetRect() override;
	void SetWidth(int m,int n) override;
	void SetColor(Color c1,Color c2) override;
public:
	inline void SetColorFront(Color color){m_colorFront=color;}
	inline void SetColorBack(Color color){m_colorBack=color;}
private:
	Color m_colorFront;
	Color m_colorBack;
	int m_nWidth=0;
	int m_nProWidth=0;
};

