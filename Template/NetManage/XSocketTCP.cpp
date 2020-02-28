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
** ��������: �򿪶˿�
** ������: BOOL TRUE:�򿪳ɹ�;	FALSE:��ʧ��
************************************************************/
BOOL XSocketTCP::Open(int nPort)
{
	m_bState=FALSE;

	//�򿪶˿�
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
		//�󶨵�ַ
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
	//ע���¼�
	if(WSAAsyncSelect(m_Socket,m_HWNd,MSG_TCP,FD_CONNECT|FD_CLOSE|FD_READ)==SOCKET_ERROR)
	{
		return FALSE;
	}

	int ret=0;

	unsigned long ul=1;
	ioctlsocket(m_Socket,FIONBIO,&ul); //����Ϊ������ģʽ

	if(ret==SOCKET_ERROR)
	{
		return FALSE;
	}

	//����д���ݻ�������С
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

	//����
	SOCKADDR_IN	addrServer;
	addrServer.sin_family=AF_INET;
	addrServer.sin_addr.s_addr=inet_addr(serverip);
	addrServer.sin_port=htons((u_short)nServerPort);

	connect(m_Socket,(SOCKADDR*)&addrServer,sizeof(SOCKADDR_IN));

	//һ�������ģʽ�׽ӱȽ��ѿ��ƣ����Ը���ʵ��������� ���������ģʽ
	unsigned long ul1=0;
	ret=ioctlsocket(m_Socket,FIONBIO,(unsigned long*)&ul1);

	return TRUE;
}

/***********************************************************
** ��������: ��������

** ���������char* pData			�������ݵ�ָ��
			 int nDataLen			�������ݳ���

** ������: BOOL TRUE:���ͳɹ�;	FALSE:����ʧ��
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
** ��������: �رն˿�
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
** ��������: ��ȡ״̬
************************************************************/
BOOL XSocketTCP::GetState()
{
	return m_bState;
}

/***********************************************************
** ��������: ���ô��ھ��
************************************************************/
void XSocketTCP::SetHWND(HWND hwnd)
{
	m_HWNd=hwnd;
}

/***********************************************************
** ��������: ��ȡ����

** ���������char* pData				��ȡ���ݵ�ָ��
			 int nDataLen				��ȡ�������鳤��
			 int& nReadLen				��ȡ����

** ������: BOOL TRUE:��ȡ�ɹ�;	FALSE:��ȡʧ��
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