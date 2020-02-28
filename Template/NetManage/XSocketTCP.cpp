#include "StdAfx.h"
#include "XSocketTCP.h"
#include <winsock2.h>
#include <Ws2tcpip.h>
#include "XConstant.h"


XSocketTCP::XSocketTCP(void)
{
	m_bState=FALSE;
	m_Socket=INVALID_SOCKET;
	m_nPort=0;
}


XSocketTCP::~XSocketTCP(void)
{
	Close();
}

/***********************************************************
** 功能描述: 打开端口
** 输出结果: BOOL TRUE:打开成功;	FALSE:打开失败
************************************************************/
BOOL XSocketTCP::Open(int nPort)
{
	m_bState=FALSE;

	//打开端口
	m_Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(m_Socket==INVALID_SOCKET)
	{
		return FALSE;
	}

	BOOL bReuseaddr=TRUE;
	if(setsockopt(m_Socket,SOL_SOCKET,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(BOOL))==SOCKET_ERROR)
	{
		return FALSE;
	}

	if(-1!=nPort)
	{
		//绑定地址
		SOCKADDR_IN	addr;
		addr.sin_family=AF_INET;
		addr.sin_addr.s_addr=htonl(INADDR_ANY);
		addr.sin_port=htons((u_short)nPort);

		if(bind(m_Socket,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN))==SOCKET_ERROR)
		{
			return FALSE;
		}
	}

	m_nPort=nPort;

	m_bState=TRUE;

	return TRUE;
}

BOOL XSocketTCP::Connect(int nServerPort,CString szServerIP)
{
	//注册事件
	if(WSAAsyncSelect(m_Socket,m_HWNd,MSG_TCP,FD_CONNECT|FD_CLOSE|FD_READ)==SOCKET_ERROR)
	{
		return FALSE;
	}

	int ret=0;

	unsigned long ul=1;
	ioctlsocket(m_Socket,FIONBIO,&ul); //设置为非阻塞模式

	if(ret==SOCKET_ERROR)
	{
		return FALSE;
	}

	//设置写数据缓冲区大小
	int nBufLen=1024*128;
	int nOptlen=sizeof(int);

	int nErrCode;
	nErrCode=setsockopt(m_Socket,SOL_SOCKET,SO_SNDBUF,(char*)&nBufLen,nOptlen);
	if(SOCKET_ERROR==nErrCode)
	{
		return FALSE;
	}

	int uiNewSendBuf;
	nErrCode=getsockopt(m_Socket,SOL_SOCKET,SO_SNDBUF,(char*)&uiNewSendBuf,&nOptlen);
	if(SOCKET_ERROR==nErrCode||uiNewSendBuf!=nBufLen)
	{
		return FALSE;
	}

	USES_CONVERSION;
	char* serverip=W2A(szServerIP);

	//连接
	SOCKADDR_IN	addrServer;
	addrServer.sin_family=AF_INET;
	addrServer.sin_addr.s_addr=inet_addr(serverip);
	addrServer.sin_port=htons((u_short)nServerPort);

	connect(m_Socket,(SOCKADDR*)&addrServer,sizeof(SOCKADDR_IN));

	//一般非阻塞模式套接比较难控制，可以根据实际情况考虑 再设回阻塞模式
	unsigned long ul1=0;
	ret=ioctlsocket(m_Socket,FIONBIO,(unsigned long*)&ul1);

	return TRUE;
}

/***********************************************************
** 功能描述: 发送数据

** 输入参数：char* pData			发送数据的指针
			 int nDataLen			发送数据长度

** 输出结果: BOOL TRUE:发送成功;	FALSE:发送失败
************************************************************/
BOOL XSocketTCP::SendData(char* pData,int nDataLen)
{
	BOOL bResult=FALSE;

	if(m_bState)
	{
		if(send(m_Socket,(const char*)pData,nDataLen,0)!=SOCKET_ERROR)
		{
			bResult=TRUE;
		}
	}

	return bResult;
}

/***********************************************************
** 功能描述: 关闭端口
************************************************************/
void XSocketTCP::Close()
{
	m_bState=FALSE;
	if(m_Socket!=INVALID_SOCKET)
	{
		closesocket(m_Socket);
		m_Socket=INVALID_SOCKET;
	}
}

/***********************************************************
** 功能描述: 获取状态
************************************************************/
BOOL XSocketTCP::GetState()
{
	return m_bState;
}

/***********************************************************
** 功能描述: 设置窗口句柄
************************************************************/
void XSocketTCP::SetHWND(HWND hwnd)
{
	m_HWNd=hwnd;
}

/***********************************************************
** 功能描述: 读取数据

** 输入参数：char* pData				读取数据的指针
			 int nDataLen				读取数据数组长度
			 int& nReadLen				读取长度

** 输出结果: BOOL TRUE:读取成功;	FALSE:读取失败
************************************************************/
BOOL XSocketTCP::ReadData(char* pData,int nDataLen,int& nReadLen)
{
	int nAddrLen=sizeof(SOCKADDR_IN);
	nReadLen=recv(m_Socket,pData,nDataLen,0);

	if(SOCKET_ERROR==nReadLen)
	{
		return FALSE;
	}
	else
	{

		return TRUE;
	}
}