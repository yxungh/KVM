#pragma once

class XSocketTCP
{
public:
	XSocketTCP(void);
	~XSocketTCP(void);

	//�򿪶˿�
	BOOL Open(int nPort);

	//����
	BOOL Connect(int nServerPort,CString szServerIP);

	//��������
	BOOL SendData(char* pData,int nDataLen);

	//�رն˿�
	void Close();

	//��ȡ״̬
	BOOL GetState();

	//���ô��ھ��
	void SetHWND(HWND hwnd);

	//��ȡ����
	BOOL ReadData(char* pData,int nDataLen,int& nReadLen);

protected:

	//״̬:TRUE:����;FALSE:û������
	BOOL m_bState;

	//�׽���
	SOCKET m_Socket;

	//�˿ں�
	int m_nPort;

	//���ھ��
	HWND m_HWNd;
};

