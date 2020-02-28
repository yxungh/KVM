#pragma once
#include "XArragePageOne.h"
#include "XArragePageTwo.h"

// XPropSheet

class XPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(XPropSheet)

public:
	XPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	XPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~XPropSheet();

	virtual BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()

public:
	inline XArragePageOne* GetPageOne(){return &m_PageOne;}
	inline XArragePageTwo* GetPageTwo(){return &m_PageTwo;}

private:

	XArragePageOne m_PageOne;
	XArragePageTwo m_PageTwo;
};


