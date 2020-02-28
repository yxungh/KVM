#pragma once
#include "XConstant.h"

class XDelegateTranslationManage;

#define _C(x,y)  XTranslationManage::GetInstance()->GetTranslationString(x,y)

class XTranslationManage
{
private:

	XTranslationManage();
	~XTranslationManage();

public:

	//获取单例
	static XTranslationManage* GetInstance();

public:

	//初始化
	void Init();

	//代理
	void SetDelegate(XDelegateTranslationManage* p);

	//获取字符串
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

	//获取语言类型
	LANGUAGETYPE GetLanguageType();

	//根据名称获取语言类型
	LANGUAGETYPE GetLanguageType(CString szLanguageName);

	//设置语言类型
	void SetLanguageType(LANGUAGETYPE type);

	//根据类型获取语言名称
	CString GetLanguageName(LANGUAGETYPE type);

	void Operate(OPERATETYPE type,void* pData);

	void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);

private:


	//根据语言类型获取语言文件路径
	CString GetTranslationFilePath(LANGUAGETYPE type);

	//保存语言类型
	void SaveLanguageType(int nType);


private:

	//代理
	XDelegateTranslationManage* m_pDelegate;

	//语言类型
	LANGUAGETYPE m_LanguageType;

	//语言文件路径
	CString m_szTranslationFilePath;

private:

	static XTranslationManage* m_pTranslationManage;

	//单例回收释放
	class GC
	{
	public:
		~GC();
	};

	static GC gc;
};