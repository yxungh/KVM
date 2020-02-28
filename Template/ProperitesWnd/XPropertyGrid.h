#pragma once

class XNode;
class XSeat;
class XPropertyGridFile;

class XPropertyGrid:public CMFCPropertyGridProperty
{
public:
	DECLARE_DYNAMIC(XPropertyGrid)

	XPropertyGrid(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	XPropertyGrid(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);


public:

	inline void SetNode(XNode* p){m_pNode=p;}
	inline void SetSeat(XSeat* p){m_pSeat=p;}

	inline void SetPlaceholder(CString s){m_szPlaceholder=s;}

protected:

	//重载属性网格双击事件。让控件可以响应属性网格双击事件
	virtual BOOL OnDblClk(CPoint point);

	//重载绘制值函数，实现占位符提示
	//virtual void OnDrawValue(CDC* pDC, CRect rect);

private:

	XNode* m_pNode;//属性网络所显示的控件指针
	XSeat* m_pSeat;

	CString m_szPlaceholder;//占位符

};