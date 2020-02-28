#include "stdafx.h"
#include "XTranslationManage.h"
#include "HandlePath.h"
#include "HandleIni.h"
#include "XConstant.h"
#include "XDelegateTranslationManage.h"



XTranslationManage* XTranslationManage::m_pTranslationManage=NULL;

//程序退出时，全局变量释放会调用析构函数来释放单例
XTranslationManage::GC XTranslationManage::gc;

XTranslationManage::XTranslationManage()
{
	m_LanguageType=LANGUAGETYPE_NULL;
	m_szTranslationFilePath=_T("");
	m_pDelegate=NULL;
}

XTranslationManage::~XTranslationManage()
{
	//SaveLanguageType();
}

XTranslationManage::GC::~GC()
{
	if(NULL!=m_pTranslationManage)
	{
		delete m_pTranslationManage;
		m_pTranslationManage=NULL;
	}
}

XTranslationManage* XTranslationManage::GetInstance()
{
	if(NULL==m_pTranslationManage)
	{
		m_pTranslationManage=new XTranslationManage;
	}

	return m_pTranslationManage;
}

void XTranslationManage::SetDelegate(XDelegateTranslationManage* p)
{
	m_pDelegate=p;
}

void XTranslationManage::Init()
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);
	int nLangueType=HandleIni::GetInt(_T("Info"),_T("Language"),205,szPath);

	CString szLanguageName=_T("");
	switch(nLangueType)
	{
		case OPERATETYPE_LANGUAGEZN:
			{
				szLanguageName=GetTranslationString(_T("10"),_T("中文(简体)"));
			}
			break;
		case OPERATETYPE_LANGUAGETW:
			{
				szLanguageName=GetTranslationString(_T("11"),_T("中文(繁体)"));
			}
			break;
		case OPERATETYPE_LANGUAGEEN:
			{
				szLanguageName=GetTranslationString(_T("12"),_T("英文"));
			}
			break;
		default:
			break;
	}

	LANGUAGETYPE LangueType=GetLanguageType(szLanguageName);
	if(LangueType!=m_LanguageType)
	{
		m_LanguageType=LangueType;
		SetLanguageType(LangueType);
		SaveLanguageType(int(nLangueType));
		//m_pDelegate->Operate(OPERATETYPE_RELOADINTERFACE, NULL);
		//m_pDelegate->ReloadDocTitle();
	}
}

CString XTranslationManage::GetTranslationString(CString szKey,CString szDefault)
{
	CString szData=HandleIni::GetString(_T("Info"),szKey,_T(""),m_szTranslationFilePath);

	if(_T("")==szData)
	{
		return szDefault;
	}
	else
	{
		return szData;
	}
}

LANGUAGETYPE XTranslationManage::GetLanguageType()
{
	return m_LanguageType;
}

void XTranslationManage::SetLanguageType(LANGUAGETYPE type)
{
	m_LanguageType=type;
	m_szTranslationFilePath=GetTranslationFilePath(type);
}

CString XTranslationManage::GetTranslationFilePath(LANGUAGETYPE type)
{
	CString szFileName=_T("");

	switch(type)
	{
		case LANGUAGETYPE_ZH_TW:
			{
				szFileName=_T("ZH_TW");
			}
			break;
		case LANGUAGETYPE_EN:
			{
				szFileName=_T("EN");
			}
			break;
		default:
			{
				szFileName=_T("ZH_CN");
			}
			break;
	}

	return HandlePath::GetTranslationFilePath(szFileName);
}

void XTranslationManage::SaveLanguageType(int nType)
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);

	CString szTemp=_T("");
	szTemp.Format(_T("%d"),nType);

	HandleIni::WriteData(_T("Info"),_T("Language"),szTemp,szPath);
}

LANGUAGETYPE XTranslationManage::GetLanguageType(CString szLanguageName)
{
	LANGUAGETYPE type=LANGUAGETYPE_NULL;

	if(szLanguageName==GetLanguageName(LANGUAGETYPE_EN))
	{
		type=LANGUAGETYPE_EN;
	}
	else if(szLanguageName==GetLanguageName(LANGUAGETYPE_ZH_CN))
	{
		type=LANGUAGETYPE_ZH_CN;
	}
	else if(szLanguageName==GetLanguageName(LANGUAGETYPE_ZH_TW))
	{
		type=LANGUAGETYPE_ZH_TW;
	}

	return type;
}

CString XTranslationManage::GetLanguageName(LANGUAGETYPE type)
{
	CString szName=_T("");

	switch(type)
	{
		case LANGUAGETYPE_ZH_CN:
			{
				szName=GetTranslationString(_T("10"),_T("中文(简体)"));
			}
			break;
		case LANGUAGETYPE_ZH_TW:
			{
				szName=GetTranslationString(_T("11"),_T("中文(繁体)"));
			}
			break;
		case LANGUAGETYPE_EN:
			{
				szName=GetTranslationString(_T("12"),_T("英文"));
			}
			break;
		default:
			break;
	}

	return szName;
}

void XTranslationManage::Operate(OPERATETYPE type,void* pData)
{
	CString szLanguageName=_T("");

	switch(type)
	{
		case OPERATETYPE_LANGUAGEZN:
			{
				szLanguageName=GetTranslationString(_T("10"),_T("中文(简体)"));
			}
			break;
		case OPERATETYPE_LANGUAGETW:
			{
				szLanguageName=GetTranslationString(_T("11"),_T("中文(繁体)"));
			}
			break;
		case OPERATETYPE_LANGUAGEEN:
			{
				szLanguageName=GetTranslationString(_T("12"),_T("英文"));
			}
			break;
		default:
			break;
	}

	LANGUAGETYPE LangueType=GetLanguageType(szLanguageName);
	if(LangueType!=m_LanguageType)
	{
		m_LanguageType=LangueType;
		SetLanguageType(LangueType);
		SaveLanguageType(int(type));
		m_pDelegate->Operate(OPERATETYPE_RELOADINTERFACE,NULL);
	}
}

void XTranslationManage::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	CString szPath=HandlePath::GetIniPath(APP_ININAME);
	int nType=HandleIni::GetInt(_T("Info"),_T("Language"),0,szPath);

	switch(type)
	{
		case CMDUITYPE_LANGUAGEZN:
			{
				pCmdUI->SetText(GetTranslationString(_T("10"),_T("中文(简体)")));
			}
			break;
		case CMDUITYPE_LANGUAGETW:
			{
				pCmdUI->SetText(GetTranslationString(_T("11"),_T("中文(繁体)")));
			}
			break;
		case CMDUITYPE_LANGUAGEEN:
			{
				pCmdUI->SetText(GetTranslationString(_T("12"),_T("英文")));
			}
			break;
		default:
			break;
	}

	if(nType==type)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}