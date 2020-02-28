#include "stdafx.h"
#include "XBaseInternalManage.h"
#include "XDelegateInternalManage.h"

XBaseInternalManage::XBaseInternalManage()
{
	m_pDelagate=NULL;
}

XBaseInternalManage::~XBaseInternalManage()
{

}

void XBaseInternalManage::SetDelegate(XDelegateInternalManage* p)
{
	m_pDelagate=p;
}
