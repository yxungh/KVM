#pragma once

class XNode;
class XSeat;

class XPropertyGridFile:public CMFCPropertyGridFileProperty
{
public:

	XPropertyGridFile(const CString& strName, const CString& strFolderName, DWORD_PTR dwData = 0, LPCTSTR lpszDescr = NULL);
	XPropertyGridFile(const CString& strName, BOOL bOpenFileDialog, const CString& strFileName, LPCTSTR lpszDefExt = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0);

	virtual ~XPropertyGridFile();

	virtual void OnClickButton(CPoint point);
	virtual BOOL OnDblClk(CPoint point);

public:

	inline void SetNode(XNode* p){m_pNode=p;}
	inline void SetSeat(XSeat* p){m_pSeat=p;}

private:

	XNode* m_pNode;
	XSeat* m_pSeat;
};