// XUpdate.cpp: 实现文件
//

#include "stdafx.h"
#include "XUpdate.h"
#include "afxdialogex.h"
#include "..\resource.h"
#include "XTranslationManage.h"
#include "XMessageBox.h"
#include "XConstant.h"
#include "XDelegateUpdate.h"
#include "XSendDataManage.h"

// XUpdate 对话框

#define DATA_LEN 1024
#define PACKET_LEN 1024+12

IMPLEMENT_DYNAMIC(XUpdate,XBaseDialog)

XUpdate::XUpdate(CWnd* pParent /*=nullptr*/)
	: XBaseDialog(IDD_DIALOG_UPDATE,pParent)
{

}

XUpdate::~XUpdate()
{
}

void XUpdate::DoDataExchange(CDataExchange* pDX)
{
	XBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_PROGRESS_RATE,m_Progress);
	DDX_Control(pDX,IDC_STATIC_FILE,m_TextFile);
	DDX_Control(pDX,IDC_STATIC_RATE,m_TextRate);
	DDX_Control(pDX,IDC_STATIC_INFO,m_TextInfo);
	DDX_Control(pDX,IDC_STATIC_TIP,m_TextTip);

	DDX_Control(pDX,IDC_BTN_SEND,m_BtnOk);
	DDX_Control(pDX,IDC_BTN_SELECT,m_BtnSel);
	DDX_Control(pDX,IDCANCEL,m_BtnCancel);
}


BEGIN_MESSAGE_MAP(XUpdate,XBaseDialog)
	ON_BN_CLICKED(IDC_BTN_SELECT,&XUpdate::OnBnClickedBtnSelect)
	ON_BN_CLICKED(IDC_BTN_SEND,&XUpdate::OnBnClickedBtnSend)
	ON_MESSAGE(MSG_TCP,&XUpdate::OnTCP)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// XUpdate 消息处理程序
BOOL XUpdate::OnInitDialog()
{
	XBaseDialog::OnInitDialog();

	Init();
	return TRUE;
}

void XUpdate::Init()
{
	ReloadInterface();

	m_Progress.SetFreeColor(RGB(166,202,240));
	m_Progress.SetRange(0,100);
	m_Progress.SetPos(0);
	m_SocketTCP.SetHWND(GetSafeHwnd());

	SetBtnStatus(TRUE,TRUE);
}

void XUpdate::ReloadInterface()
{
	SetWindowText(_C(_T("270"),_T("升级服务器")));

	m_BtnOk.SetCaption(_C(_T("87"),_T("发送")));
	m_BtnCancel.SetCaption(_C(_T("2"),_T("取消")));
	m_BtnSel.SetCaption(_T("..."));
	m_TextRate.SetText(_C(_T("282"),_T("传输进度"))+_T(":"));
	m_TextInfo.SetText(_C(_T("284"),_T("提示消息"))+_T(":"));
	m_TextFile.SetText(_C(_T("285"),_T("更新文件"))+_T(":"));
}

void XUpdate::ShowTips(CString szTip)
{
	m_TextTip.SetText(szTip,TRUE);
}

void XUpdate::SetBtnStatus(BOOL b1,BOOL b2)
{
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(b1);
	GetDlgItem(IDCANCEL)->EnableWindow(b2);
}

void XUpdate::OnBnClickedBtnSelect()
{
	CString szFileName;
	CString szFilePath;
	if(OpenSelectPhotoFileDialog(szFileName,szFilePath))
	{
		GetDlgItem(IDC_EDIT_FILE)->SetWindowText(szFilePath);
	}
}

BOOL XUpdate::OpenSelectPhotoFileDialog(CString& szFileName,CString& szFilePath)
{
	CFileDialog fileDlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_HIDEREADONLY);

	CString szTitle=_C(_T("286"),_T("选择升级文件"));
	fileDlg.m_ofn.lpstrTitle=szTitle;

	if(fileDlg.DoModal()==IDOK)
	{
		szFilePath=fileDlg.GetPathName();
		szFileName=fileDlg.GetFileName();
		return TRUE;
	}
	return FALSE;
}

void XUpdate::OnBnClickedBtnSend()
{
	GetDlgItem(IDC_EDIT_FILE)->GetWindowText(m_szFilePath);
	m_szFilePath.Trim();
	if(m_szFilePath==_T(""))
	{
		ShowTips(_C(_T("271"),_T("请选择升级文件！")));
		return;
	}
	GetDlgItem(IDC_STATIC_RATE)->SetWindowText(_C(_T("282"),_T("传输进度"))+_T(":"));
	//先通知监听
	XSendDataManage::GetInstance()->AddSendDataOfNotifyMonitor();
	//发送超时2s
	m_TimeOut=2000;

	ShowTips(_C(_T("275"),_T("连接传输网络")));
	SetBtnStatus(FALSE,FALSE);

	if(!ConnectTransmission())
	{
		StopTransmission();
	}
}

void XUpdate::StopTransmission()
{
	KillTimer(1);
	KillTimer(2);
	m_SocketTCP.Close();
	if(m_TransmissionFile.m_hFile!=CFile::hFileNull)
		m_TransmissionFile.Close();

	SetBtnStatus(TRUE,TRUE);
}

BOOL XUpdate::OpenTransmissionFile()
{
	if(m_TransmissionFile.Open(m_szFilePath,CFile::modeRead))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int XUpdate::SetTransmissionData()
{	
	m_nTransmissionFileLen=(int)m_TransmissionFile.GetLength();
	//TRACE(_T("FileLen=%d\n"),m_nTransmissionFileLen);
	//数据包内容大小1024
	m_nPackCount=(m_nTransmissionFileLen%1024)==0?(m_nTransmissionFileLen/1024):(m_nTransmissionFileLen/1024)+1;
	//TRACE(_T("PackCount=%d\n"),m_nPackCount);

	return m_nTransmissionFileLen;
}

void XUpdate::BeginTransmission()
{
	if(!OpenTransmissionFile())
	{
		StopTransmission();
		ShowTips(_C(_T("277"),_T("打开升级文件失败！")));
		return;
	}	
	//限制33M
	if(SetTransmissionData()>34603008)
	{
		StopTransmission();
		ShowTips(_C(_T("289"),_T("发送文件过大，文件大小<33M！")));
		return;
	}
	
	m_dwRecvDataTime=GetTickCount();
	m_Progress.SetPos(0);
	
	SetTimer(2,500,NULL);

	m_nPacketIndex=1;
	SendUpdateFile(m_nPacketIndex);
}

void XUpdate::SetProgressByPacketIndex(int nPacketIndex)
{
	if(nPacketIndex==m_nPackCount)
	{
		m_Progress.SetPos(100);
	}
	else
	{
		float nTemp=(float)(1024*100)/m_nTransmissionFileLen;
		float nPos=nPacketIndex*nTemp;
		m_Progress.SetPos(nPos);
	}
}

void XUpdate::ConnectTransmissionSuccess()
{
	KillTimer(1);
	ShowTips(_C(_T("273"),_T("网络连接成功！")));
	Sleep(500);
	ShowTips(_C(_T("274"),_T("开始传输文件")));

	BeginTransmission();
}

BOOL XUpdate::ConnectTransmission()
{
	if(!m_SocketTCP.Open(-1))
	{
		ShowTips(_C(_T("272"),_T("初始化网络失败！")));
		return FALSE;
	}

	//端口12346
	if(!m_SocketTCP.Connect(12346,m_pDelegate->GetCurIP()))
	{
		ShowTips(_C(_T("272"),_T("初始化网络失败！")));
		return FALSE;
	}

	SetTimer(1,2000,NULL);

	return TRUE;
}

void XUpdate::SendUpdateFile(int nPacketIndex)
{
	//TRACE(_T("PackIndex=%d\n"),nPacketIndex);

	//数据包负载1024
	int nSendDataLen=0;
	if(nPacketIndex==m_nPackCount)
	{
		nSendDataLen=m_nTransmissionFileLen-(nPacketIndex-1)*1024;
	}
	else
	{
		nSendDataLen=1024;
	}

	char* pData=new char[nSendDataLen];
	memset(pData,0,nSendDataLen);

	//文件定位
	int nFilePos=(nPacketIndex-1)*1024;
	m_TransmissionFile.Seek(nFilePos,CFile::begin);
	m_TransmissionFile.Read(pData,nSendDataLen);

	AddSendData(pData,nSendDataLen);
	delete pData;
}

void XUpdate::AddSendData(char* pData,int nDataLen)
{
	int nPacketLen=nDataLen+16;

	char* pSendData=new char[nPacketLen];
	memset(pSendData,0,nPacketLen);

	pSendData[0]=0x53;
	pSendData[1]=0x4a;
	pSendData[2]=0x55;
	pSendData[3]=0x50;

	memcpy(pSendData+4,&m_nTransmissionFileLen,4);//文件大小
	memcpy(pSendData+8,&m_nPacketIndex,4);//包序号
	memcpy(pSendData+12,&nPacketLen,4);//包大小
	memcpy(pSendData+16,pData,nDataLen);

	m_SocketTCP.SendData(pSendData,nPacketLen);
	delete pSendData;
}

void XUpdate::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
		case 1:
			{
				StopTransmission();
				ShowTips(_C(_T("276"),_T("网络连接失败！")));
			}
			break;
		case 2:
			{
				DWORD dwNow=GetTickCount();
				
				if((dwNow-m_dwRecvDataTime)>m_TimeOut)
				{
					StopTransmission();
					ShowTips(_C(_T("278"),_T("接受返回数据失败！")));
				}
			}
			break;
		default:
			break;
	}
}

LRESULT XUpdate::OnTCP(WPARAM wParam,LPARAM lParam)
{
	if(WSAGETSELECTERROR(lParam))
	{
		return false;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
		case FD_CLOSE:
			{

			}
			break;
		case FD_READ:
			{
				//回复一个字节
				int nLen=0;
				if(!m_SocketTCP.ReadData(m_recvData,1024,nLen))
				{
					return -1;
				}
				//TRACE(_T("Len=%d\n"),nLen);

				if(nLen==0)
				{
					StopTransmission();
					ShowTips(_C(_T("279"),_T("断开连接!")));
				}
				else if(nLen==1)
				{
					//更新时间
					m_dwRecvDataTime=GetTickCount();

					if(m_bSendFile)
					{
						//更新进度条
						SetProgressByPacketIndex(m_nPacketIndex);
						//包序号
						m_nPacketIndex+=nLen;

						if(m_nPacketIndex==(m_nPackCount+1))
						{
							//StopTransmission();
							ShowTips(_C(_T("280"),_T("发送文件成功！")));
							Sleep(1000);
							ShowTips(_C(_T("292"),_T("等待升级！")));
							m_bSendFile=FALSE;
							//等待升级超时10s
							m_TimeOut=20000;

							//DWORD Time=GetTickCount();
						}
						else
						{
							SendUpdateFile(m_nPacketIndex);
						}
					}
					else
					{
						//升级
						//TRACE(_T("Update\n"));

						//升级超时10s
						//m_TimeOut=2000;

						ShowTips(_C(_T("281"),_T("开始升级！")));
						GetDlgItem(IDC_STATIC_RATE)->SetWindowText(_C(_T("283"),_T("升级进度"))+_T(":"));

						int nIndex=m_recvData[0];
						//TRACE(_T("nIndex=%d\n"),nIndex);
						m_Progress.SetPos((float)nIndex);
						if(nIndex==100)
						{
							StopTransmission();
							ShowTips(_C(_T("291"),_T("升级完成！")));
						}
					}
				}
				else
				{
					//TRACE(_T("Len=%d\n"),nLen);

					StopTransmission();
					ShowTips(_C(_T("290"),_T("接受回复数据错误!")));
				}
			}
			break;
		case FD_CONNECT:
			{
				ConnectTransmissionSuccess();
			}
			break;
		default:
			break;
	}

	return 0;
}