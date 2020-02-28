#pragma once
#include "XConstant.h"
class XPieChartInfo;
class XChart
{
public:
	XChart();
	~XChart();

public:
	inline void SetRect(RECTF rect){m_rect=rect;}
	inline void SetScale(float f){m_dwScale=f;}
public:
	virtual void Draw(Graphics& graphics)=0;
	virtual RECTF GetRect()=0;
public:
	void RectScale(RECTF& rect);
public:
	//������
	virtual void SetWidth(int m,int n){}
	virtual void SetColor(Color c1,Color c2){}
	//��ͼ
	virtual void PushPieData(int nID,CString szTitle,int nDegress,Color color=Color(0,0,0)){}
	virtual void PushPieData(int nID,XPieChartInfo* pInfo){}
	virtual void SetInterRect(RECTF rect){}
	virtual void SetColorFlag(BOOL b){}
	virtual void SetType(CString szType){}
	virtual void ClearMap(){}
	//�ٷֱ�
	virtual void SetPrecentageColor(Color b,Color e,Color ba,Color f){}
	virtual void SetCurRate(int n){};
	virtual void SetCurRate(CString szTemper){}
	virtual void SetTitlt(CString szTitle){}
	//����ͼ
	virtual void InsertColumnData(CString nKey,int nData,BOOL bMainSecond=FALSE){}
	virtual void SetShowIndex(){};
	virtual void Clear(){};
	virtual void SetColumnSelect(CString nID){}
	//���⼰����
	virtual void SetDrawType(STRING nType){}
	virtual void SetDrawInfo(CString szInfo){}
	//�Ǳ���
	virtual void SetInstrumentColor(Color b,Color e,Color ba,Color f){}
	virtual void SetDegress(int nTemper){}

public:
	static XChart* Get(CHART chartType);
protected:
	RECTF m_rect;
	float m_dwScale=0.0f;
};

