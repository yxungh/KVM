#include "stdafx.h"
#include "XNode.h"
#include "XSeat.h"
#include "XProprtyGridFile.h"

XPropertyGridFile::XPropertyGridFile(const CString& strName,const CString& strFolderName,DWORD_PTR dwData,LPCTSTR lpszDescr):
	CMFCPropertyGridFileProperty(strName,strFolderName,dwData,lpszDescr),
	m_pNode(NULL),
	m_pSeat(NULL)
{

}

XPropertyGridFile::XPropertyGridFile(const CString& strName,BOOL bOpenFileDialog,const CString& strFileName,LPCTSTR lpszDefExt,
		DWORD dwFlags,LPCTSTR lpszFilter,LPCTSTR lpszDescr,DWORD_PTR dwData):
	CMFCPropertyGridFileProperty(strName,bOpenFileDialog,strFileName,lpszDefExt,dwFlags,lpszFilter,lpszDescr,dwData)
{

}

XPropertyGridFile::~XPropertyGridFile()
{

}

void XPropertyGridFile::OnClickButton(CPoint point)
{
	if(NULL!=m_pNode)
	{
		m_pNode->OnClickButtonPropertyGridFile(this);
	}

	if(NULL!=m_pSeat)
	{
		m_pSeat->OnClickButtonPropertyGridFile(this);
	}
}

BOOL XPropertyGridFile::OnDblClk(CPoint point)
{
	if(NULL!=m_pNode)
	{
		return m_pNode->OnDblClkPropertyGridFile(this);
	}

	if(NULL!=m_pSeat)
	{
		return m_pSeat->OnDblClkPropertyGridFile(this);
	}

	return TRUE;
}