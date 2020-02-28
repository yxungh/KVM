#pragma once

class XSocketTCP
{
public:
	XSocketTCP(void);
	~XSocketTCP(void);

	//打开端口
	BOOL Open(int nPort);

	//连接
	BOOL Connect(int nServerPort,CString szServerIP);

	//发送数据
	BOOL SendData(char* pData,int nDataLen);

	//关闭端口
	void Close();

	//获取状态
	BOOL GetState();

	//设置窗口句柄
	void SetHWND(HWND hwnd);

	//读取数据
	BOOL ReadData(char* pData,int nDataLen,int& nReadLen);

protected:

	//状态:TRUE:运行;FALSE:没有运行
	BOOL m_bState;

	//套接字
	SOCKET m_Socket;

	//端口号
	int m_nPort;

	//窗口句柄
	HWND m_HWNd;
};

