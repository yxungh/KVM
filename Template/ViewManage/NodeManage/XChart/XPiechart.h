#pragma once
#include "XChart.h"

class XPieChartInfo;


class XPiechart:public XChart
{
public:
	XPiechart();
	~XPiechart();

public:
	void Draw(Graphics& graphics) override;
	RECTF GetRect() override;
	void PushPieData(int nID,CString szTitle,int nDegress,Color color=Color(0,0,0)) override;
	void PushPieData(int nID,XPieChartInfo* pInfo) override;
	void SetInterRect(RECTF rect) override;
	void SetType(CString szType) override;
	void SetColorFlag(BOOL b) override;
	void ClearMap() override;

private:
	std::map<int,XPieChartInfo*> m_MapPie;
	//是否随机生成颜色
	BOOL m_bFalg=TRUE;	
	RECTF m_InterRect;
	CString m_szType=_T("");
};

