#pragma once
#include "XConstant.h"
#include "XChart.h"


class XColumnChart:public XChart
{
public:
	XColumnChart();
	~XColumnChart();

public:
	void Draw(Graphics& graphics) override;
	RECTF GetRect() override;
public:
	void InsertColumnData(CString nKey,int nData,BOOL bMainSecond=FALSE) override;
	void SetShowIndex() override;
	void Clear() override;
	void SetColumnSelect(CString nID) override;

private:
	int GetMaxData();
private:
	int m_nShowIndex=1;
	int m_nCount=0;
	int m_nLimit=0;
	static int m_nCloumnWidth;
	static int m_nColumnSize;
	Color m_colorBegin;
	Color m_colorEnd;

	MAP_COLUMN m_MapColumnData;
	//键值与区域(柱形图)
	MAP_KEYCOLOR m_MapKeyColor;

	std::vector<CString> m_VecKey;
	std::vector<CString> m_VecTempKey;
	std::vector<int> m_VecData;
	std::vector<CString> m_VecKeyFront;
	std::vector<CString> m_VecKeyBack;
	//颜色
	std::vector<Color> m_VecColor;
	//颜色缓存
	std::vector<Color> m_VecTempColor;
	BOOL m_bFalg=FALSE;
};

