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

	//������������˫���¼����ÿؼ�������Ӧ��������˫���¼�
	virtual BOOL OnDblClk(CPoint point);

	//���ػ���ֵ������ʵ��ռλ����ʾ
	//virtual void OnDrawValue(CDC* pDC, CRect rect);

private:

	XNode* m_pNode;//������������ʾ�Ŀؼ�ָ��
	XSeat* m_pSeat;

	CString m_szPlaceholder;//ռλ��

};