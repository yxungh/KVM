// MFCMyPropertyGridProperty.cpp : 实现文件
//

#include "stdafx.h"
#include "XPropertyGrid.h"
#include "XNode.h"
#include "XSeat.h"

// XPropertyGrid

IMPLEMENT_DYNAMIC(XPropertyGrid, CMFCPropertyGridProperty)

	// XPropertyGrid 消息处理程序

	XPropertyGrid::XPropertyGrid(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
	LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars):CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars),
		m_pNode(NULL),
		m_pSeat(NULL),
		m_szPlaceholder(_T(""))
{

}

XPropertyGrid::XPropertyGrid(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList):CMFCPropertyGridProperty(strGroupName,dwData, bIsValueList)
{

}

BOOL XPropertyGrid::OnDblClk(CPoint point)
{
	if(m_pWndInPlace==NULL)
		return FALSE;

	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	if(m_lstOptions.GetCount()>1)
	{
		CString szText;
		m_pWndInPlace->GetWindowText(szText);

		POSITION pos=m_lstOptions.Find(szText);
		if(pos==NULL)
			return FALSE;

		m_lstOptions.GetNext(pos);
		if(pos==NULL)
			pos=m_lstOptions.GetHeadPosition();

		ENSURE(pos!=NULL);
		szText=m_lstOptions.GetAt(pos);

		m_pWndInPlace->SetWindowText(szText);
		OnUpdateValue();
	}

	if (m_pNode!=NULL)
	{
		if(m_pNode->OnDblClkPropertyGrid(this))
		{
			return TRUE;
		}
	}

	if(m_pSeat!=NULL)
	{
		if(m_pSeat->OnDblClkPropertyGrid(this))
		{
			return TRUE;
		}
	}

	return CMFCPropertyGridProperty::OnDblClk(point);
}
