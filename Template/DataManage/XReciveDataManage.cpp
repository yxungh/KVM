#include "StdAfx.h"
#include "XReciveDataManage.h"
#include "XDelegateReciveDataManage.h"



XReciveDataManage::XReciveDataManage(void)
{
	m_pDelegate = NULL;
}

XReciveDataManage::~XReciveDataManage(void)
{
}

void XReciveDataManage::SetDelegate(XDelegateReciveDataManage* p)
{
	m_pDelegate = p;
}

void XReciveDataManage::Init()
{
	
}

//////////////////////////////////////////////////////////////////////////
BOOL XReciveDataManage::HandleUDPData(unsigned char* pData,int nDataLen,SOCKADDR_IN addr)
{
	CString szIP;
	szIP.Format(_T("%d.%d.%d.%d"),addr.sin_addr.S_un.S_un_b.s_b1,
								  addr.sin_addr.S_un.S_un_b.s_b2,
								  addr.sin_addr.S_un.S_un_b.s_b3,
								  addr.sin_addr.S_un.S_un_b.s_b4);

	DecodeHeart(pData,nDataLen);
	DecodeLogin(pData,nDataLen);
	DecodeLoginOut(pData,nDataLen);
	DecodePower(pData,nDataLen);
	DecodeUserList(pData,nDataLen);
	DecodeStoreList(pData,nDataLen);
	DecodeGetDeviceInfo(pData,nDataLen);
	DecodeGetNodeByChannel(pData,nDataLen);
	DecodeNodeInfo(pData,nDataLen);
	DecodeNodeDetailInfo(pData,nDataLen);
	DecodeNodeStatus(pData,nDataLen);
	DecodeGetLoginUser(pData,nDataLen);
	DecodeAlterNodeName(pData,nDataLen);
	DecodeGetLoginUserStatus(pData,nDataLen);
	DecodeGetNodeLogin(pData,nDataLen);
	DecodeGetNodeLogOut(pData,nDataLen);
	DecodeTakeOver(pData,nDataLen);
	DecodeTakeOverCancel(pData,nDataLen);
	DecodePreview(pData,nDataLen);
	DecodeGetMatrixStatus(pData,nDataLen);
	DecodeMatrix(pData,nDataLen);
	DecodeOSDImage(pData,nDataLen);
	DecodeHideOSDImage(pData,nDataLen);
	DecodeNodeGroup(pData,nDataLen);
	DecodeNodeGroupInfo(pData,nDataLen);
	DecodeRefreashGroup(pData,nDataLen);
	DecodeSystemStatus(pData,nDataLen);
	DecodeMainAndSecond(pData,nDataLen);
	DecodeMainAndSecondList(pData,nDataLen);
	DecodeNetConfig(pData,nDataLen);
	DecodeReLog(pData,nDataLen);
	DecodeRootFolder(pData,nDataLen);
	DecodeSplit(pData,nDataLen);
	DecodeSplitWindow(pData,nDataLen);
	DecodeSplitScene(pData,nDataLen);
	DecodeUserSecurity(pData,nDataLen);
	DecodeAsServer(pData,nDataLen);
	DecodeAsClient(pData,nDataLen);


	return TRUE;
}

void XReciveDataManage::DecodeLogin(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x01&&
		pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RELOGIN,(char*)pTemp);
		delete []pTemp;
	}
}

void XReciveDataManage::DecodeHeart(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x04&&
		pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REHEART,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeLoginOut(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x05&&
		pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RELOGINOUT,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodePower(unsigned char* pData,int nDataLen)
{

	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x02&&
		pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REPOWER,(char*)pTemp);
		delete []pTemp;	
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x02&&
		pData[9]==0x07)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REPOWER,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeUserList(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x06&&
		pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REUSERLIST,(char*)pTemp);
		delete []pTemp;	
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x06&&
		pData[9]==0x07)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REUSERLIST,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeStoreList(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x07&&
		pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RESTORELIST,(char*)pTemp);
		delete []pTemp;	
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x07&&
		pData[9]==0x07)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RESTORELIST,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeUserSecurity(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x09&&
	   pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REUSERSECURITY,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x09&&
			pData[9]==0x07)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REUSERSECURITY,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeGetDeviceInfo(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x01&&
		pData[5]==0x0A)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REDEVICEINFO,(char*)pTemp);
		delete []pTemp;	
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x01&&
		pData[9]==0x0A)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REDEVICEINFO,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeGetNodeByChannel(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x00&&
		pData[5]==0x0B)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODECHANNEL,(char*)pTemp);
		delete []pTemp;	
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x00&&
		pData[9]==0x0B)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODECHANNEL,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeNodeInfo(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x01&&
		pData[5]==0x0B)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODEINFO,(char*)pTemp);
		delete []pTemp;	
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x01&&
		pData[9]==0x0B)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODEINFO,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeNodeDetailInfo(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x03&&
		pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODEDETAILINFO,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x03&&
		pData[9]==0x07)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODEDETAILINFO,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeNodeStatus(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x07&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODESTATUS,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x07&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODESTATUS,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeGetLoginUser(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x02&&
		pData[5]==0x0B)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RELOGINUSER,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x02&&
		pData[9]==0x0B)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RELOGINUSER,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeGetLoginUserStatus(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x03&&
		pData[5]==0x0B)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RELOGINUSERSTATUS,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x03&&
		pData[9]==0x0B)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RELOGINUSERSTATUS,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeAlterNodeName(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x01&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_ALTERNODENAME,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x01&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_ALTERNODENAME,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeGetNodeLogin(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x02&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODELOGIN,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x02&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODELOGIN,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeGetNodeLogOut(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x03&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODELOGOUT,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x03&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODELOGOUT,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeTakeOver(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x04&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RETAKEOVER,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x04&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RETAKEOVER,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeTakeOverCancel(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x06&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RETAKEOVERCANCEL,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x06&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RETAKEOVERCANCEL,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodePreview(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x05&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_PREVIEW,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x05&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_PREVIEW,(char*)pTemp);
		delete []pTemp;	
	}	
}

void XReciveDataManage::DecodeMatrix(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x0A&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REMATRIX,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x0A&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REMATRIX,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeGetMatrixStatus(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x04&&
		pData[5]==0x0B)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REMATRIXSTATUS,(char*)pTemp);
		delete []pTemp;	     
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x04&&
		pData[9]==0x0B)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REMATRIXSTATUS,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeOSDImage(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x0B&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REOSDIMAGE,(char*)pTemp);
		delete []pTemp;	    
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x0B&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REOSDIMAGE,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeHideOSDImage(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x0C&&
		pData[5]==0x09)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REHIDEOSDIMAGE,(char*)pTemp);
		delete []pTemp;	    
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x0C&&
		pData[9]==0x09)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REHIDEOSDIMAGE,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeMainAndSecondList(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x00&&
	   pData[5]==0x08)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REMAINANDSECONDLIST,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x00&&
			pData[9]==0x08)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REREADNODEGROUP,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeNodeGroup(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x01&&
		pData[5]==0x08)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REREADNODEGROUP,(char*)pTemp);
		delete []pTemp;	    
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x01&&
		pData[9]==0x08)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REREADNODEGROUP,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeNodeGroupInfo(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x03&&
		pData[5]==0x08)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODEGROUPINFO,(char*)pTemp);
		delete []pTemp;	    
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x03&&
		pData[9]==0x08)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENODEGROUPINFO,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeMainAndSecond(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x02&&
	   pData[5]==0x08)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REMAINANDSECOND,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x02&&
			pData[9]==0x08)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REMAINANDSECOND,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeRefreashGroup(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
		pData[1]==0x00&&
		pData[4]==0x03&&
		pData[5]==0x08)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REREFREASGGROUP,(char*)pTemp);
		delete []pTemp;	    
	}
	else if(pData[0]==0xFF&&
		pData[1]==0x01&&
		pData[8]==0x03&&
		pData[9]==0x08)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REREFREASGGROUP,(char*)pTemp);
		delete []pTemp;	
	}
}

void XReciveDataManage::DecodeSystemStatus(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x05&&
	   pData[5]==0x0B)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RESYSTEMSTATUS,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x05&&
			pData[9]==0x0B)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RESYSTEMSTATUS,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeNetConfig(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x00&&
	   pData[5]==0x0A)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENETCONFIG,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x00&&
			pData[9]==0x0A)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RENETCONFIG,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeReLog(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x07&&
	   pData[5]==0x0B)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RELOG,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x07&&
			pData[9]==0x0B)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RELOG,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeRootFolder(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x08&&
	   pData[5]==0x07)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REROOTFOLDER,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x08&&
			pData[9]==0x07)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REROOTFOLDER,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeSplit(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x00&&
	   pData[5]==0x0D)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REGETSPLITWALL,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x00&&
			pData[9]==0x0D)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REGETSPLITWALL,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeSplitWindow(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x01&&
	   pData[5]==0x0D)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REGETSPLITWINDOW,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x01&&
			pData[9]==0x0D)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REGETSPLITWINDOW,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeSplitScene(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x03&&
	   pData[5]==0x0D)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RESPLITSCENE,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x03&&
			pData[9]==0x0D)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RESPLITSCENE,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeSplitInput(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x04&&
	   pData[5]==0x0D)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RESPLITINPUT,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x04&&
			pData[9]==0x0D)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_RESPLITINPUT,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeAsServer(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x07&&
	   pData[5]==0x0A)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REASSERVER,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x07&&
			pData[9]==0x0A)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REASSERVER,(char*)pTemp);
		delete[]pTemp;
	}
}

void XReciveDataManage::DecodeAsClient(unsigned char* pData,int nDataLen)
{
	if(pData[0]==0xFF&&
	   pData[1]==0x00&&
	   pData[4]==0x08&&
	   pData[5]==0x0A)
	{
		unsigned char* pTemp=AddDataOfFull(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REASCLIENT,(char*)pTemp);
		delete[]pTemp;
	}
	else if(pData[0]==0xFF&&
			pData[1]==0x01&&
			pData[8]==0x08&&
			pData[9]==0x0A)
	{
		unsigned char* pTemp=AddDataOfPacket(pData,nDataLen);

		m_pDelegate->Operate(OPERATETYPE_REASCLIENT,(char*)pTemp);
		delete[]pTemp;
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
unsigned char* XReciveDataManage::AddDataOfFull(unsigned char* pData,int nLen)
{
	nLen-=8;

	unsigned char* pTemp=new unsigned char[nLen+1];
	memset(pTemp,0,nLen+1);
	memcpy(pTemp,pData+6,nLen);
	pTemp[nLen]='\0';

	return pTemp;
}

unsigned char* XReciveDataManage::AddDataOfPacket(unsigned char* pData,int nLen)
{
	nLen-=10;

	unsigned char* pTemp=new unsigned char[nLen+1];
	memset(pTemp,0,nLen+1);
	memcpy(pTemp,pData+10,nLen);
	pTemp[nLen]='\0';

	return pTemp;
}



//////////////////////////////////////////////////////////////////////////
void XReciveDataManage::Operate(OPERATETYPE type, void* pData)
{
	//switch(type)
	//{
	//case OPERATETYPE_RESETTEMPERATURE:
	//	{
	//		ResetTemperature();
	//	}
	//	break;
	//default:
	//	break;
	//}
}
