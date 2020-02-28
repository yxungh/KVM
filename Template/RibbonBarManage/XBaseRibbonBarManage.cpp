#include "StdAfx.h"
#include "XBaseRibbonBarManage.h"
#include "XDelegateRibbonBarManage.h"


XBaseRibbonBarManage::XBaseRibbonBarManage(void)
{
}


XBaseRibbonBarManage::~XBaseRibbonBarManage(void)
{
}

void XBaseRibbonBarManage::SetDelegate(XDelegateRibbonBarManage* p)
{
	m_pDelegate=p;
}
