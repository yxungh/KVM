#pragma once
#include "XChart.h"
//#include "XConstant.h"

class XString:public XChart
{
public:
	XString();
	~XString();

public:
	void Draw(Graphics& graphics) override;
	RECTF GetRect() override;
	void SetDrawType(STRING nType) override;
	void SetDrawInfo(CString szInfo) override;

private:
	STRING m_nDrawType=STRING::STRING_NULL;
	CString m_szDrawInfo=_T("");
};

