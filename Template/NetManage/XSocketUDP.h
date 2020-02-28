#pragma once

class XNetManage;

class XSocketUDP
{
public:
	XSocketUDP(void);
	~XSocketUDP(void);

	//�򿪶˿�
	BOOL Open();

	//�رն˿�
	void Close();

	//��ȡ״̬
	BOOL GetState();

	//��������
	BOOL SendData(const char* pData,const int nDataLen,char* pIp,u_short nTargetPort);

	//�����������
	void SetNetManage(XNetManage* p);

	//���ô��ھ��
	void SetHWND(HWND h);

	//������Ϣ
	void HandleMsg(WPARAM wParam,LPARAM lParam);

private:

	void HandleFD_READ();

protected:

	XNetManage* m_NetManage;

	//״̬
	BOOL m_bState;

	//�׽���
	SOCKET m_Socket;

	//���ھ��
	HWND m_HWND;

	//�������ݻ���
	unsigned char m_Data[2048];
};

