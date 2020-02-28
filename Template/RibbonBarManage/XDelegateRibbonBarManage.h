#pragma once

#include "XConstant.h"

class XDelegateRibbonBarManage
{
public:
	XDelegateRibbonBarManage(void);
	~XDelegateRibbonBarManage(void);

	//��ȡ�ַ���
	//virtual CString GetTranslationString(CString szKey, CString szDefault) = 0;

	//���¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl) = 0;

	//�ؼ����ݸı�
	virtual void ControlDataChange(XDATATYPE type, void* pControl)=0;

	//����
	virtual void Operate(OPERATETYPE type, void* pData)=0;

	//��ȡCWnd
	virtual CWnd* GetCWND() = 0;

	//Ribbon��ʾ�����
	virtual void RibbonBarShowCategory(DWORD_PTR dwData) = 0;

	//��ȡ��ϯҳ�����
	virtual int GetPageIndex()=0;
};

