#include "StdAfx.h"
#include "XRibbonBar.h"
#include "XDelegateRibbonBar.h"

IMPLEMENT_DYNAMIC(XRibbonBar,CMFCRibbonBar)

BEGIN_MESSAGE_MAP(XRibbonBar,CMFCRibbonBar)
END_MESSAGE_MAP()


XRibbonBar::XRibbonBar(void)
{
	m_pDelegate=NULL;
}

XRibbonBar::~XRibbonBar(void)
{
}

/***********************************************************
** ��������: ����ί��
************************************************************/
void XRibbonBar::SetDelegate(XDelegateRibbonBar* p)
{
	m_pDelegate=p;
}

/***********************************************************
** ��������: ���ù������ϵ�Сͼ�꣬��ֹ��������˵�
************************************************************/
BOOL XRibbonBar::OnShowRibbonContextMenu(CWnd* pWnd,int x,int y,CMFCRibbonBaseElement* pHit)
{
	return FALSE;
}

BOOL XRibbonBar::SetActiveCategory(CMFCRibbonCategory* pCategory,BOOL bForceRestore)
{
	CMFCRibbonBar::SetActiveCategory(pCategory,bForceRestore);

	if(NULL!=m_pDelegate)
	{
		//��ȡ��ʾҳ������
		DWORD_PTR dwData=pCategory->GetData();
		m_pDelegate->RibbonBarShowCategory(dwData);
	}

	return true;
}
