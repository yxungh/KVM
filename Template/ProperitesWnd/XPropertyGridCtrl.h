#pragma once


// PropertyGridCtrl

class XPropertyGridCtrl : public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(XPropertyGridCtrl)

public:
	XPropertyGridCtrl();
	virtual ~XPropertyGridCtrl();


	//virtual BOOL PreTranslateMessage(MSG* pMsg);




protected:
	DECLARE_MESSAGE_MAP()


private:
	//void KeyValue(CMFCPropertyGridProperty* pTemp,int nValue,char c);
	//void DbClick(CMFCPropertyGridProperty* pTemp,CString szFront);
};


