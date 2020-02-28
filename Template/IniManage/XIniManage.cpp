#include "stdafx.h"
#include "XIniManage.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "HandleCalculate.h"
#include "XMessageBox.h"
#include "XDelegateIniManage.h"
#include "XConstant.h"


XIniManage::XIniManage()
{
	m_pDelegate=NULL;
	m_nThemeIndex=0;
}

XIniManage::~XIniManage()
{

}

void XIniManage::SetDelegate(XDelegateIniManage* p)
{
	m_pDelegate=p;
}

void XIniManage::Init()
{
	GetIniData();
}

void XIniManage::GetIniData()
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);

	m_nThemeIndex=HandleIni::GetInt(_T("Info"),_T("Theme"),0,szPath);
}

void XIniManage::SaveDataOfTheme(int n)
{
	CString szIniPath=HandlePath::GetIniPath(APP_ININAME);

	CString szTheme;
	szTheme.Format(_T("%d"),n);

	HandleIni::WriteData(_T("Info"),_T("Theme"),szTheme,szIniPath);
}
//////////////////////////////////////////////////////////////////////////
void XIniManage::Operate(OPERATETYPE type,void* pData)
{
	switch(type)
	{
		case OPERATETYPE_THEMEWIN7:
		case OPERATETYPE_THEMEBLUE:
		case OPERATETYPE_THEMEBLACK:
		case OPERATETYPE_THEMESLIVER:
		case OPERATETYPE_THEMEAQUE:
			{
				SaveDataOfTheme(int(type));
				m_pDelegate->ChangeTheme(int(type));
			}
			break;
		default:
			break;
	}
}


void XIniManage::UpdateControlDataShow(XDATATYPE type,void* pControl)
{

}

void XIniManage::ControlDataChange(XDATATYPE type,void* pControl)
{

}

void XIniManage::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);
	int nThemeIndex=HandleIni::GetInt(_T("Info"),_T("Theme"),0,szPath);

	if(type==nThemeIndex)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}