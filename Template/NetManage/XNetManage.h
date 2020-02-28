#pragma once

#include "XBaseNetManage.h"

class XSocketUDP;

class XNetManage: public XBaseNetManage
{
public:
	XNetManage(void);
	~XNetManage(void);

	//��ʼ��
	virtual void Init();

	//��ȡ״̬
	virtual BOOL GetState();

	//���ʹ�������
	virtual BOOL SendData(CString szIP,int nPort,const char* pData,const int nLen);

	//����
	virtual void Operate(OPERATETYPE type,void* pData);

	//���¿ؼ�UI
	//virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);

	//����UDP��Ϣ
	virtual void HandleUDPMsg(WPARAM wParam,LPARAM lParam);

public:

	//����UDP����
	void HandleUDPData(unsigned char* pData,int nDataLen,SOCKADDR_IN addr);

private:

	//����״̬���¿ؼ�UI
	//void UpdateControlUIByState(CCmdUI* pCmdUI,BOOL bState);

	//��
	void Open();

	//�ر�
	void Close();

private:

	//Socket
	XSocketUDP* m_pSocketUDP;
};

