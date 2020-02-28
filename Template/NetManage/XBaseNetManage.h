#pragma once

#include "XConstant.h"

class XDelegateNetManage;

class XBaseNetManage
{
public:
	XBaseNetManage(void);
	virtual ~XBaseNetManage(void);

	//��ʼ��
	virtual void Init()=0;

	//��ȡ״̬
	virtual BOOL GetState()=0;

	//���ʹ�������
	virtual BOOL SendData(CString szIP,int nPort,const char* pData,const int nLen)=0;

	//����
	virtual void Operate(OPERATETYPE type,void* pData)=0;

	//���¿ؼ�UI
	//virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)=0;

	//����UDP��Ϣ
	virtual void HandleUDPMsg(WPARAM wParam,LPARAM lParam)=0;

public:

	//����ί��
	void SetDelegate(XDelegateNetManage* p);

protected:

	//ί��
	XDelegateNetManage* m_pDelegate;
};

