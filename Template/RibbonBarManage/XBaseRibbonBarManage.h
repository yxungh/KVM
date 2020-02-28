#pragma once

#include "XConstant.h"

class XDelegateRibbonBarManage;

class XBaseRibbonBarManage
{
public:
	XBaseRibbonBarManage(void);
	virtual ~XBaseRibbonBarManage(void);

public:

	//��ʼ��
	virtual void Init()=0;

	//�ؼ����ݸı�
	virtual void ControlDataChange(XDATATYPE type)=0;

	//���ؽ���
	virtual void ReloadInterface()=0;

	//�����������͸��¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type)=0;

	//virtual void SetStatusInfo()=0;

	//virtual void SetCurUserName(CString szUserName)=0;

	virtual void SetActiveCategory(int nBaseIndex)=0;

	//����
	//virtual void Operate(OPERATETYPE type, void* pData) = 0;

	virtual void ResetRibbonBar()=0;

public:

	//����ί��
	void SetDelegate(XDelegateRibbonBarManage* p);



protected:

	//ί��
	XDelegateRibbonBarManage* m_pDelegate;
};

