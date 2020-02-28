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

	//��ȡ����
	static XTranslationManage* GetInstance();

public:

	//��ʼ��
	void Init();

	//����
	void SetDelegate(XDelegateTranslationManage* p);

	//��ȡ�ַ���
	CString GetTranslationString(CString szKey,CString szDefault=_T(""));

	//��ȡ��������
	LANGUAGETYPE GetLanguageType();

	//�������ƻ�ȡ��������
	LANGUAGETYPE GetLanguageType(CString szLanguageName);

	//������������
	void SetLanguageType(LANGUAGETYPE type);

	//�������ͻ�ȡ��������
	CString GetLanguageName(LANGUAGETYPE type);

	void Operate(OPERATETYPE type,void* pData);

	void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);

private:


	//�����������ͻ�ȡ�����ļ�·��
	CString GetTranslationFilePath(LANGUAGETYPE type);

	//������������
	void SaveLanguageType(int nType);


private:

	//����
	XDelegateTranslationManage* m_pDelegate;

	//��������
	LANGUAGETYPE m_LanguageType;

	//�����ļ�·��
	CString m_szTranslationFilePath;

private:

	static XTranslationManage* m_pTranslationManage;

	//���������ͷ�
	class GC
	{
	public:
		~GC();
	};

	static GC gc;
};