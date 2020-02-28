#include "stdafx.h"
#include "XSendDataManage.h"
#include "XDelegateSendDataManage.h"
#include "XJsonManage.h"
#include "XNodeManage.h"
#include "XNode.h"
#include "XNodeGroupInfo.h"
#include "XNodeGroup.h"


XSendDataManage* XSendDataManage::m_pSendDataManage=NULL;
XSendDataManage::XSendDataManage()
	:m_pDelegate(NULL),
	m_nTotalPacket(0),
	m_nCurPacket(0),
	m_nPacketLen(0)
{

}

XSendDataManage::~XSendDataManage()
{
	//TRACE(_T("~XSendDataManage\n"));
}

void XSendDataManage::SetDelegate(XDelegateSendDataManage* p)
{
	m_pDelegate=p;
}

XSendDataManage* XSendDataManage::GetInstance()
{
	if(NULL==m_pSendDataManage)
	{
		m_pSendDataManage=new XSendDataManage;
	}

	return m_pSendDataManage;
}

void XSendDataManage::Release()
{
	if(NULL!=m_pSendDataManage)
	{
		delete m_pSendDataManage;
		m_pSendDataManage=NULL;
	}
}

BOOL XSendDataManage::SendData(char* pData,int nDataLen)
{
	return m_pDelegate->SendData(pData,nDataLen);
}

//////////////////////////////////////////////////////////////////////////
void XSendDataManage::AddFullSendDataByProtocol(unsigned char* pSrcData,unsigned short nSrcDataLen,PROTOCOLTYPE ProtocolType)
{
	int nLen=nSrcDataLen+8;
	unsigned char* pData=new unsigned char[nLen];
	memset(pData,0,nLen);

	//包头
	pData[0]=0xFF;
	pData[1]=0x00;

	//包长
	int nPackLen=nSrcDataLen+2;
	memcpy(pData+2,&nPackLen,2);

	//协议号
	switch(ProtocolType)
	{
		case PROTOCOLTYPE_USERLIST:
			{
				pData[4]=0x00;
				pData[5]=0x07;
			}
			break;
		case PROTOCOLTYPE_LOGIN:
			{
				pData[4]=0x01;
				pData[5]=0x07;
			}
			break;
		case PROTOCOLTYPE_OBTAINPOWER:
			{
				pData[4]=0x02;
				pData[5]=0x07;
			}
			break;
		case PROTOCOLTYPE_GETALLNODE:
		case PROTOCOLTYPE_GETNODEDETAILINFO:
		case PROTOCOLTYPE_GETNODEALLDETAILINFO:
			{
				pData[4]=0x03;
				pData[5]=0x07;
			}
			break;
		case PACKERHEAD_HEART:
			{
				pData[4]=0x04;
				pData[5]=0x07;
			}
			break;
		case PROTOCOLTYPE_LOGINOUT:
			{
				pData[4]=0x05;
				pData[5]=0x07;
			}
			break;
		case PROTOCOLTYPE_OBTAINUSERLIST:
			{
				pData[4]=0x06;
				pData[5]=0x07;
			}
			break;
		case PROTOCOLTYPE_OBTAINSTORE:
		case PROTOCOLTYPE_DELSTORELIST:
		case PROTOCOLTYPE_ADDSTORELIST:
			{
				pData[4]=0x07;
				pData[5]=0x07;
			}
			break;
		case PROTOCOLTYPE_ROOTFOLDER:
		case PROTOCOLTYPE_SUBFOLDER:
			{
				pData[4]=0x08;
				pData[5]=0x07;
			}
			break;
		case PROTOCOLTYPE_NETCONFIG:
			{
				pData[4]=0x00;
				pData[5]=0x0A;
			}
			break;
		case PROTOCOLTYPE_GETDEVICEINFO:
			{
				pData[4]=0x01;
				pData[5]=0x0A;
			}
			break;
		case PROTOCOLTYPE_RTC:
			{
				pData[4]=0x02;
				pData[5]=0x0A;
			}
			break;
		case PROTOCOLTYPE_GETNODE:
			{
				pData[4]=0x00;
				pData[5]=0x0B;
			}
			break;
		case PROTOCOLTYPE_GETNODEINFO:
			{
				pData[4]=0x01;
				pData[5]=0x0B;
			}
			break;
		case PROTOCOLTYPE_GETLOGINUSER:
			{
				pData[4]=0x02;
				pData[5]=0x0B;
			}
			break;
		case PROTOCOLTYPE_GETLOGINUSERSTATUS:
			{
				pData[4]=0x03;
				pData[5]=0x0B;
			}
			break;
		case PROTOCOLTYPE_MATRIXSTATUS:
			{
				pData[4]=0x04;
				pData[5]=0x0B;
			}
			break;
		case PROTOCOLTYPE_LOG:
			{
				pData[4]=0x07;
				pData[5]=0x0B;
			}
			break;
		case PROTOCOLTYPE_NOTIFY:
			{
				pData[4]=0x08;
				pData[5]=0x0B;
			}
			break;
		case PROTOCOLTYPE_ALTERNODENAME:
			{
				pData[4]=0x01;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_NODELOGIN:
			{
				pData[4]=0x02;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_NODELOGOUT:
			{
				pData[4]=0x03;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_TAKEOVER:
			{
				pData[4]=0x04;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_PREVIEW:
			{
				pData[4]=0x05;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_TAKEOVERCANCEL:
			{
				pData[4]=0x06;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_GETNODESTATUS:
		case PROTOCOLTYPE_ALTERAUDIOMODEL:
		case PROTOCOLTYPE_ALTERRESOLUATIONINDEX:
		case PROTOCOLTYPE_ALTEROUTMODEL:
		case PROTOCOLTYPE_NODEBLINK:
		case PROTOCOLTYPE_ALTERHIDMODEL:
		case PROTOCOLTYPE_ALTERSCREENMODEL:
		case PROTOCOLTYPE_ALTERAUDIOSRC:
		case PROTOCOLTYPE_ALTERBINDCFG:
		case PROTOCOLTYPE_ALTERBINDNODEID:
		case PROTOCOLTYPE_ALTERHOTKEY:
			{
				pData[4]=0x07;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_LIGHTCONTROL:
			{
				pData[4]=0x09;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_MATRIX:
			{
				pData[4]=0x0A;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_OSDIMAGE:
			{
				pData[4]=0x0B;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_HIDEOSDIMAGE:
			{
				pData[4]=0x0C;
				pData[5]=0x09;
			}
			break;
		case PROTOCOLTYPE_MAINANDSECONDLIST:
			{
				pData[4]=0x00;
				pData[5]=0x08;
			}
			break;
		case PROTOCOLTYPE_READNODEGROUP:
			{
				pData[4]=0x01;
				pData[5]=0x08;
			}
			break;
		case PROTOCOLTYPE_MAINANDSECOND:
		case PROTOCOLTYPE_QUERYMAINANDSECOND:
		case PROTOCOLTYPE_DELGROUPMAINSECOND:
		case PROTOCOLTYPE_UPDATAMASTERNAME:
		case PROTOCOLTYPE_UPDATAMASTERSEATARRAGE:
			{
				pData[4]=0x02;
				pData[5]=0x08;
			}
			break;
		case PROTOCOLTYPE_NODEGROUPINFO:
			{
				pData[4]=0x03;
				pData[5]=0x08;
			}
			break;
		case PROTOCOLTYPE_SYSTEMSTATUS:
			{
				pData[4]=0x05;
				pData[5]=0x0B;
			}
			break;
		case PROTOCOLTYPE_OBTIANSPLIT:
			{
				pData[4]=0x00;
				pData[5]=0x0D;
			}
			break;
		case PROTOCOLTYPE_OBTIANSPLITWINDOW:
			{
				pData[4]=0x01;
				pData[5]=0x0D;
			}
			break;
		case PROTOCOLTYPE_SPLITSCENE:
			{
				pData[4]=0x03;
				pData[5]=0x0D;
			}
			break;
		default:
			break;
	}

	if(NULL!=pSrcData)
	{
		memcpy(pData+6,pSrcData,nSrcDataLen);

		unsigned char* pTemp=pData;
		unsigned short nSum=CheckSum(pTemp+4,nSrcDataLen+4);
		memcpy(pData+6+nSrcDataLen,&nSum,2);
	}

	SendData((char*)pData,nLen);
	//////////////////////////////////////////////////////////////////////////

	//if(ProtocolType==PROTOCOLTYPE_OSDIMAGE)
	//{
	//	CString szTemp=_T("");
	//	CString szStr=_T("");
	//	for(int i=0;i<nLen;i++)
	//	{
	//		szTemp.Format(_T("%02X "),pData[i]);
	//		szStr+=szTemp;
	//	}

	//	TRACE(_T("str_SendData=%s\n"),szStr);
	//}

	//////////////////////////////////////////////////////////////////////////
	delete[]pData;
}

void XSendDataManage::AddPackSendDataByProtocol(unsigned char* pSrcData,unsigned short nSrcDataLen,unsigned int nPacket,unsigned int nPacketIndex,PROTOCOLTYPE ProtocolType)
{
	//组包12各字节
	int nLen=nSrcDataLen+12;
	unsigned char* pData=new unsigned char[nLen];
	memset(pData,0,nLen);

	//包头
	pData[0]=0xFF;
	pData[1]=0x01;

	//总包数
	memcpy(pData+2,&nSrcDataLen,2);

	//包号
	memcpy(pData+4,&nPacketIndex,2);

	//包长
	int nPacketLen=nSrcDataLen+2;
	memcpy(pData+6,&nPacketLen,2);

	switch(nPacketIndex)
	{
		case 1:
			{
				//协议号
				switch(ProtocolType)
				{
					case PROTOCOLTYPE_USERLIST:
						{
							pData[8]=0x00;
							pData[9]=0x07;
						}
						break;
					case PROTOCOLTYPE_LOGIN:
						{
							pData[8]=0x01;
							pData[9]=0x07;
						}
						break;
					case PROTOCOLTYPE_OBTAINPOWER:
						{
							pData[8]=0x02;
							pData[9]=0x07;
						}
						break;
					case PROTOCOLTYPE_GETNODEDETAILINFO:
						{
							pData[8]=0x03;
							pData[9]=0x07;
						}
						break;
					case PACKERHEAD_HEART:
						{
							pData[4]=0x04;
							pData[5]=0x07;
						}
						break;
					case PROTOCOLTYPE_LOGINOUT:
						{
							pData[8]=0x05;
							pData[9]=0x07;
						}
						break;
					case PROTOCOLTYPE_OBTAINUSERLIST:
						{
							pData[8]=0x06;
							pData[9]=0x07;
						}
						break;
					case PROTOCOLTYPE_OBTAINSTORE:
						{
							pData[8]=0x07;
							pData[9]=0x07;
						}
						break;
					case PROTOCOLTYPE_GETLOGINUSERSTATUS:
						{
							pData[8]=0x03;
							pData[9]=0x0B;
						}
						break;
					case PROTOCOLTYPE_NETCONFIG:
						{
							pData[4]=0x00;
							pData[5]=0x0A;
						}
						break;
					default:
						break;
				}

				//参数
				memcpy(pData+10,pSrcData,nSrcDataLen);

				//校验和
				unsigned char* pTemp=pData;
				unsigned short nSum=CheckSum(pTemp+8,nSrcDataLen+4);
				memcpy(pData+10+nSrcDataLen,&nSum,2);

				SendData((char*)pData,nLen);
				delete[]pData;
			}
			break;
		default:
			{
				//参数
				memcpy(pData+8,pSrcData,nSrcDataLen);

				//校验和
				unsigned char* pTemp=pData;
				unsigned short nSum=CheckSum(pTemp+8,nSrcDataLen+2);
				memcpy(pData+8+nSrcDataLen,&nSum,2);

				SendData((char*)pData,nLen);
				delete[]pData;
			}
			break;
	}
}

/////////////////////////////////////////////////////////////////////////
unsigned short XSendDataManage::CheckSum(unsigned char* pData,int nLen)
{
	unsigned short nSum=0;
	for(int i=0;i<nLen;i++)
	{
		nSum+=pData[i];
	}
	return nSum;
}

void XSendDataManage::AddData(CString szData,PROTOCOLTYPE nType)
{
	USES_CONVERSION;
	char* pData=W2A(szData);
	int nDataLen=strlen(pData)+1;

	int nTempLen=0;
	if(nDataLen%2!=0)
		nTempLen=nDataLen+1;
	else
		nTempLen=nDataLen;

	unsigned char* pTemp=new unsigned char[nTempLen];
	memset(pTemp,0,nTempLen);
	memcpy(pTemp,pData,nDataLen);

	//////////////////////////////////////////////////////////////////////////
	int nMaxSendDataLen=1024;
	if(nDataLen>nMaxSendDataLen)
	{
		//如果超过1024，分包发送
		unsigned char* pTempData=pTemp;
		int nLen=nDataLen;

		//求出发送次数
		int nPacketCount=(nLen%nMaxSendDataLen==0)?(nLen/nMaxSendDataLen):((nLen/nMaxSendDataLen)+1);
		int nRemaindLen=nLen;

		for(int i=1;i<=nPacketCount;i++)
		{
			int nPacketIndex=i;
			//数据偏移
			pTempData+=nMaxSendDataLen*(nPacketIndex-1);
			if(nRemaindLen>=1024)
			{
				//剩余超过1024
				unsigned char* pSendData=new unsigned char[nMaxSendDataLen];
				memcpy(pSendData,pTempData,nMaxSendDataLen);

				AddPackSendDataByProtocol(pSendData,nMaxSendDataLen,nPacketCount,nPacketIndex,nType);
				delete []pSendData;

				nRemaindLen-=nMaxSendDataLen;
			}
			else
			{
				//最后剩余
				unsigned char* pSendData=new unsigned char[nRemaindLen];
				memcpy(pSendData,pTempData,nRemaindLen);

				AddPackSendDataByProtocol(pSendData,nRemaindLen,nPacketCount,nPacketIndex,nType);
				delete []pSendData;
			}
		}
	}
	else
	{
		AddFullSendDataByProtocol(pTemp,nTempLen,nType);
	}

	delete []pTemp;
}

void XSendDataManage::SendDataOfHeart(DWORD dHeartTime)
{
	int nLen=4;
	unsigned char pData[4]={0};

	memcpy(pData,&dHeartTime,4);

	AddFullSendDataByProtocol(pData,nLen,PACKERHEAD_HEART);
}

void XSendDataManage::AddSendDataOfLogin(CString szUserName,CString szPassWd)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToLogin(szUserName,szPassWd,szData);

	AddData(szData,PROTOCOLTYPE_LOGIN);
}

void XSendDataManage::AddSendDataOfLoginOut(CString szUserName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToLoginOut(szUserName,szData);

	AddData(szData,PROTOCOLTYPE_LOGINOUT);
}

void XSendDataManage::AddSendDataOfObtainAllUser()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToObtainAllUser(szData);

	AddData(szData,PROTOCOLTYPE_OBTAINPOWER);
}

void XSendDataManage::SendDataOfObtainUserPower(CString szUserName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToObtainPower(szUserName,szData);

	AddData(szData,PROTOCOLTYPE_OBTAINPOWER);
}

void XSendDataManage::SendDataOfObtainSubUserPower(int nID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToObtainSubPower(nID,szData);

	AddData(szData,PROTOCOLTYPE_OBTAINPOWER);
}

void XSendDataManage::SendDataOfObtainAddUserPower(int nID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToObtainAddUserPower(nID,szData);

	AddData(szData,PROTOCOLTYPE_OBTAINPOWER);
}

void XSendDataManage::AddSendDataOfObtainUserList(int nIndex,int nSize)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToObtainUserList(nIndex,nSize,szData);

	AddData(szData,PROTOCOLTYPE_OBTAINUSERLIST);
}

void XSendDataManage::AddSendDataOfAddUser(XPower* pPower)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAddUser(pPower,szData);

	AddData(szData,PROTOCOLTYPE_OBTAINPOWER);
}

void XSendDataManage::AddSendDataOfAlterUser(XPower* pPower,CString szPassWd)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterUser(pPower,szData,szPassWd);

	AddData(szData,PROTOCOLTYPE_OBTAINPOWER);
}

void XSendDataManage::AddSendDataOfDelUser(CString szUserName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToDelUser(szUserName,szData);

	AddData(szData,PROTOCOLTYPE_OBTAINPOWER);
}

void XSendDataManage::AddSendDataOfObtainStoreList(int nUserID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToObtainStore(nUserID,szData);

	AddData(szData,PROTOCOLTYPE_OBTAINSTORE);
}

void XSendDataManage::AddSendDataOfDelStoreList(XStoreListInfo* pListInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToDelStoreList(pListInfo,szData);

	AddData(szData,PROTOCOLTYPE_DELSTORELIST);
}

void XSendDataManage::AddSendDataOfAddStoreList(XNode* pNode,int nUserID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAddStoreList(pNode,nUserID,szData);

	AddData(szData,PROTOCOLTYPE_ADDSTORELIST);
}

void XSendDataManage::AddSendDataOfGetAllNode()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetAllNode(szData);

	AddData(szData,PROTOCOLTYPE_GETALLNODE);
}

void XSendDataManage::AddSendDataOfGetDeviceInfo()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetDeviceInfo(szData);

	AddData(szData,PROTOCOLTYPE_GETDEVICEINFO);
}

void XSendDataManage::AddSendDataOfGetNodeByChannel()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetNodeByChannel(szData);

	AddData(szData,PROTOCOLTYPE_GETNODE);
}

void XSendDataManage::AddSendDataOfGetNodeInfo(XNodeManage* pNodeManage)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetNodeInfo(pNodeManage,szData);

	AddData(szData,PROTOCOLTYPE_GETNODEINFO);
}

void XSendDataManage::AddSendDataOfGetNodeDetailInfo(XNodeManage* pNodeManage)
{
	//每次读一个节点
	MAP_NODE& MapNode=pNodeManage->GetMapNode();

	int nIndex=0;

	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		int nID=pNode->GetNodeID();

		if(nIndex%16==0)
			Sleep(500);

		//TRACE(_T("Detial\n"));

		CString szData=_T("");
		XJsonManage::GetInstance()->WriteJsonToGetNodeDetailInfo(nID,szData);

		AddData(szData,PROTOCOLTYPE_GETNODEDETAILINFO);
		nIndex++;
	}
}

void XSendDataManage::AddSendDataOfGetNodeAllDetailInfo(int nNodeID)
{
	CString szData=_T("");
	XJsonManage::GetInstance()->WriteJsonToGetNodeAllDetailInfo(nNodeID,szData);

	AddData(szData,PROTOCOLTYPE_GETNODEALLDETAILINFO);
}

void XSendDataManage::AddSendDataOfUpdateNodeGroup(int nNodeID,int nGroupID,int nMark)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToUpdataNodeGroup(nNodeID,nGroupID,nMark,szData);

	AddData(szData,PROTOCOLTYPE_GETNODEDETAILINFO);
}

void XSendDataManage::AddSendDataOfUpdateNodeGroupMaster(int nNodeID,int nMasterID,int nMark)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToUpdataNodeMaster(nNodeID,nMasterID,nMark,szData);

	AddData(szData,PROTOCOLTYPE_GETNODEDETAILINFO);
}

void XSendDataManage::AddSendDataOfGetNodeStatus(XNodeManage* pNodeManage)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetNodeStatus(pNodeManage,szData);

	AddData(szData,PROTOCOLTYPE_GETNODESTATUS);
}

void XSendDataManage::AddSendDataOfGetNodeStatus(int nNodeID1,int nNodeID2)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetNodeStatus(nNodeID1,nNodeID2,szData);

	AddData(szData,PROTOCOLTYPE_GETNODESTATUS);
}

void XSendDataManage::AddSendDataOfGetLoginUser()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetLoginUser(szData);

	AddData(szData,PROTOCOLTYPE_GETLOGINUSER);
}

void XSendDataManage::AddSendDataOfGetLoginUserStatus(XNodeManage* pNodeManage)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetLoginUserStatus(pNodeManage,szData);

	AddData(szData,PROTOCOLTYPE_GETLOGINUSERSTATUS);
}

void XSendDataManage::AddSendDataOfGetLoginUserStatus(int nUserID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetLoginUserStatus(nUserID,szData);

	AddData(szData,PROTOCOLTYPE_GETLOGINUSERSTATUS);
}

void XSendDataManage::AddSendDataOfNodeLogin(int nNodeID,CString szUserName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToNodeLogin(nNodeID,szUserName,szData);

	AddData(szData,PROTOCOLTYPE_NODELOGIN);
}

void XSendDataManage::AddSendDataOfNodeLogOut(int nNodeID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToNodeLogOut(nNodeID,szData);

	AddData(szData,PROTOCOLTYPE_NODELOGOUT);
}

void XSendDataManage::AddSendDataOfTakeOver(int nNodeID,int nTargetID,BOOL bExclusive)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToTakeOver(nNodeID,nTargetID,bExclusive,szData);

	AddData(szData,PROTOCOLTYPE_TAKEOVER);
	TRACE(_T("szData=%s\n"),szData);
}

void XSendDataManage::AddSendDataOfTakeOverCancel(int nNodeID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToTakeOverCancel(nNodeID,szData);

	AddData(szData,PROTOCOLTYPE_TAKEOVERCANCEL);
}

void XSendDataManage::AddSendDataOfPreview(int nNodeID,int nTargetID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToPreview(nNodeID,nTargetID,szData);

	AddData(szData,PROTOCOLTYPE_PREVIEW);
}

void XSendDataManage::AddSendDataOfAlterNodeName(int nNodeID,CString szName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterNodeName(nNodeID,szName,szData);

	AddData(szData,PROTOCOLTYPE_ALTERNODENAME);
}

void XSendDataManage::AddSendDataOfAlterAudioModel(int nNodeID,int nAudioModel)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterAudioModel(nNodeID,nAudioModel,szData);

	AddData(szData,PROTOCOLTYPE_ALTERAUDIOMODEL);
}

void XSendDataManage::AddSendDataOfAlterAudioSrc(int nNodeID,int nAudioSrc)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterAudioSrc(nNodeID,nAudioSrc,szData);

	AddData(szData,PROTOCOLTYPE_ALTERAUDIOSRC);
}

void XSendDataManage::AddSendDataOfAlterHidModel(int nNodeID,int nHidModel)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterHidModel(nNodeID,nHidModel,szData);

	AddData(szData,PROTOCOLTYPE_ALTERHIDMODEL);
}

void XSendDataManage::AddSendDataOfAlterSplitScreenModel(int nNodeID,int nScreenModel)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterSplitScreenModel(nNodeID,nScreenModel,szData);

	AddData(szData,PROTOCOLTYPE_ALTERSCREENMODEL);
}

void XSendDataManage::AddSendDataOfAlterResoluationIndex(int nNodeID,int nResIndex)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterResoluationIndex(nNodeID,nResIndex,szData);

	//TRACE(_T("Index=%d\n"),nResIndex);
	//TRACE(_T("szData=%s\n"),szData);

	AddData(szData,PROTOCOLTYPE_ALTERRESOLUATIONINDEX);
}

void XSendDataManage::AddSendDataOfAlterOutModel(int nNodeID,int nOutModel)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterOutModel(nNodeID,nOutModel,szData);

	AddData(szData,PROTOCOLTYPE_ALTEROUTMODEL);
}

void XSendDataManage::AddSendDataOfGetMatrixStatus()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToGetMatrixStatus(szData);

	AddData(szData,PROTOCOLTYPE_MATRIXSTATUS);
}

void XSendDataManage::AddSendDataOfMatrix(int nInNodeChannel,int nOutNodeChannel)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonMatrix(nInNodeChannel,nOutNodeChannel,szData);

	AddData(szData,PROTOCOLTYPE_MATRIX);
}

void XSendDataManage::AddSendDataOfMatrix(XNodeManage* pNodeManage,int nInputChannel)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonMatrix(pNodeManage,nInputChannel,szData);

	AddData(szData,PROTOCOLTYPE_MATRIX);
}

void XSendDataManage::AddSendDataOfOSDImage(XNodeManage* pNodeManage,int nIndex)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonOSDImage(pNodeManage,nIndex,szData);

	AddData(szData,PROTOCOLTYPE_OSDIMAGE);
	//TRACE(_T("str=%s\n"),szData);
}

void XSendDataManage::AddSendDataOfHideOSDImage(int nShow,int nChannel)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonHideOSDImage(nShow,nChannel,szData);

	AddData(szData,PROTOCOLTYPE_HIDEOSDIMAGE);
}

void XSendDataManage::AddSendDataOfAlterBindCfg(int nNodeID,int bBindCfg)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterBindCfg(nNodeID,bBindCfg,szData);

	AddData(szData,PROTOCOLTYPE_ALTERBINDCFG);
}
void XSendDataManage::AddSendDataOfAlterBindNodeID(int nNodeID,int bBindNodeID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterBindNodeID(nNodeID,bBindNodeID,szData);

	AddData(szData,PROTOCOLTYPE_ALTERBINDNODEID);
}

void XSendDataManage::AddSendDataOfAlterHotKey(int nNodeID,MAP_HOTKEY& MapHotKey)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonToAlterHotKey(nNodeID,MapHotKey,szData);

	AddData(szData,PROTOCOLTYPE_ALTERHOTKEY);
}

void XSendDataManage::AddSendDataOfReadNodeGroup()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonReadNodeGroup(szData);

	AddData(szData,PROTOCOLTYPE_READNODEGROUP);
}

void XSendDataManage::AddSendDataOfReadOnLineNodeGroup()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonReadOnLineNodeGroup(szData);

	AddData(szData,PROTOCOLTYPE_READNODEGROUP);
}

void XSendDataManage::AddSendDataOfNodeGroupInfo(XNodeManage* pNodeManage)
{
	MAP_NODEGROUP& MapNodeGroup=pNodeManage->GetMapNodeGroup();
	for(auto iter=MapNodeGroup.begin();iter!=MapNodeGroup.end();++iter)
	{
		XNodeGroupInfo* pInfo=iter->second;
		int nNodeGroupID=pInfo->GetGroupID();

		CString szData;
		XJsonManage::GetInstance()->WriteJsonNodeGroupInfo(nNodeGroupID,szData);

		AddData(szData,PROTOCOLTYPE_NODEGROUPINFO);
	}
}

void XSendDataManage::AddSendDataOfUpdataSeatArrage(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonUpdataSeatArrage(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_NODEGROUPINFO);
}

void XSendDataManage::AddSendDataOfUpdataMasterSeatArrage(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonUpdataMasterSeatArrage(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_UPDATAMASTERSEATARRAGE);
}

void XSendDataManage::AddSendDataOfAddSeatArrage(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonAddSeatArrage(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_NODEGROUPINFO);
}

void XSendDataManage::AddSendDataOfMainAndSecondList()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonMainAndSecondList(szData);

	AddData(szData,PROTOCOLTYPE_MAINANDSECONDLIST);
}

void XSendDataManage::AddSendDataOfQueryMainAndSecond(int nGroupID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonQueryMainAndSecond(nGroupID,szData);

	AddData(szData,PROTOCOLTYPE_QUERYMAINANDSECOND);
}

void XSendDataManage::AddSendDataOfMainAndSecond(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonAddMainAndSecond(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_MAINANDSECOND);
}

void XSendDataManage::AddSendDataOfDelNodeGroup(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonDelNodeGroup(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_NODEGROUPINFO);
}

void XSendDataManage::AddSendDataOfDelNodeGroupMainSecond(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonDelNodeGroupMainSecond(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_DELGROUPMAINSECOND);
}

void XSendDataManage::AddSendDataOfUpdataNodeGroupName(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonUpdataNodeGroupName(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_NODEGROUPINFO);
}

void XSendDataManage::AddSendDataOfUpdataMasterNodeGroupName(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonUpdataMasterNodeGroupName(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_UPDATAMASTERNAME);
}

void XSendDataManage::AddSendDataOfUpdataSeatMasterNode(XNodeGroupInfo& nodeGroupInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonUpdataSeatMasterNode(nodeGroupInfo,szData);

	AddData(szData,PROTOCOLTYPE_NODEGROUPINFO);
}

void XSendDataManage::AddSendDataOfRefreashGroup(int nGroupID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonRefreashGroup(nGroupID,szData);

	AddData(szData,PROTOCOLTYPE_NODEGROUPINFO);
}

void XSendDataManage::AddSendDataOfRefreashMainSecGroup(int nGroupID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonRefreashMainSecGroup(nGroupID,szData);

	AddData(szData,PROTOCOLTYPE_MAINANDSECOND);
}

void XSendDataManage::AddSendDataSystemStatus()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonSystemStatu(szData);

	AddData(szData,PROTOCOLTYPE_SYSTEMSTATUS);
}

void XSendDataManage::AddSendDataOfBlink()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonBlink(szData);

	AddData(szData,PROTOCOLTYPE_NODEBLINK);
}

void XSendDataManage::AddSendDataOfNetConfig()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonGetNetConfig(szData);

	AddData(szData,PROTOCOLTYPE_NETCONFIG);
}

void XSendDataManage::AddSendDataOfApplyNetConfig(XNetConfig& config)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonApplyNetConfig(config,szData);

	AddData(szData,PROTOCOLTYPE_NETCONFIG);
}

void XSendDataManage::AddSendDataOfSaveNetConfig(XNetConfig& config)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonSaveNetConfig(config,szData);

	AddData(szData,PROTOCOLTYPE_NETCONFIG);
}

void XSendDataManage::AddSendDataOfLightControl(int nIndex,int nStatus)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonLightControl(nIndex,nStatus,szData);

	AddData(szData,PROTOCOLTYPE_LIGHTCONTROL);
}

void XSendDataManage::AddSendDataOfGetLogByData(XLogPack& logPack)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonLogByData(logPack,szData);

	AddData(szData,PROTOCOLTYPE_LOG);
}

void XSendDataManage::AddSendDataOfGetLogByUser(XLogPack& logPack)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonLogByUser(logPack,szData);

	AddData(szData,PROTOCOLTYPE_LOG);
}

void XSendDataManage::AddSendDataOfGetLogByNode(XLogPack& logPack)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonLogByNode(logPack,szData);

	AddData(szData,PROTOCOLTYPE_LOG);
}

void XSendDataManage::AddSendDataOfRTCTime()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonRTCTime(szData);

	AddData(szData,PROTOCOLTYPE_RTC);
}

void XSendDataManage::AddSendDataOfNotifyMonitor()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonNotifyMonitor(szData);

	AddData(szData,PROTOCOLTYPE_NOTIFY);
}

void XSendDataManage::AddSendDataOfObtainRootFolder()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonObtainRootFolder(szData);

	AddData(szData,PROTOCOLTYPE_ROOTFOLDER);
}

void XSendDataManage::AddSendDataOfObtainSubFolder(int nID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonObtainSubFolder(szData,nID);

	AddData(szData,PROTOCOLTYPE_SUBFOLDER);
}

void XSendDataManage::AddSendDataOfDeleteFolder(int nID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonDeleteFolder(szData,nID);

	AddData(szData,PROTOCOLTYPE_SUBFOLDER);
}

void XSendDataManage::AddSendDataOfAddFolder(XSubFolder& sub)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonAddFolder(szData,sub);

	AddData(szData,PROTOCOLTYPE_SUBFOLDER);
}

void XSendDataManage::AddSendDataOfObtainSplit()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonObtainSplit(szData);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLIT);
}

void XSendDataManage::AddSendDataOfQuerySplitWall(CString szName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonQuerySplitWall(szData,szName);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLIT);
}

void XSendDataManage::AddSendDataOfAddSplit(XSplitResult& splitInfo)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonAddSplitWall(szData,splitInfo);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLIT);
}

void XSendDataManage::AddSendDataOfDraw(CString szName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonDraw(szData,szName);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLIT);
}

void XSendDataManage::AddSendDataOfRefreashSplit(CString szName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonRefreashSplit(szData,szName);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLIT);
}

void XSendDataManage::AddSendDataOfDelSplit(CString szName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonDelSplit(szData,szName);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLIT);
}

void XSendDataManage::AddSendDataOfObtainSplitWindow(CString szName,BOOL bFirst)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonObtainSplitWindow(szData,szName,bFirst);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLITWINDOW);
}

void XSendDataManage::AddSendDataOfObtainSplitWindowInfo(CString szSplitName,int nSignalID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonObtainSplitWindowInfo(szData,szSplitName,nSignalID);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLITWINDOW);
}

void XSendDataManage::AddSendDataOfAddSignal(CString szName,XSignal& signal)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonAddSignal(szData,szName,signal);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLITWINDOW);
}

void XSendDataManage::AddSendDataOfDelSignal(CString szName,int nID)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonDelSignal(szData,szName,nID);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLITWINDOW);
}

void XSendDataManage::AddSendDataOfClearSignal(CString szName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonCLearSignal(szData,szName);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLITWINDOW);
}

void XSendDataManage::AddSendDataOfLevelUseList(CString szName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonLevelUseList(szData,szName);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLITWINDOW);
}

void XSendDataManage::AddSendDataOfAlterLevel(CString szName,XSignalLevel& level)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonAlterLevel(szData,szName,level);

	AddData(szData,PROTOCOLTYPE_OBTIANSPLITWINDOW);
}

void XSendDataManage::AddSendDataOfObtainSplitScene()
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonObtainSplitScene(szData);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}

void XSendDataManage::AddSendDataOfObtainWallList(CString szName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonObtainWallList(szData,szName);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}

void XSendDataManage::AddSendDataOfOpenScene(CString szSceneName,CString szWallName,int nOpt)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonOpenScene(szData,szSceneName,szWallName,nOpt);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}

void XSendDataManage::AddSendDataOfQuerySceneWall(CString szSceneName,CString szWallName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonQuerySceneWall(szData,szSceneName,szWallName);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}

void XSendDataManage::AddSendDataOfAddSplitScene(CString szSceneName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonSplitScene(szData,szSceneName);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}

void XSendDataManage::AddSendDataOfSaveWallToNewScene(CString szSceneName,CString szSplit,BOOL bLast)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonSaveWallToNewScene(szData,szSceneName,szSplit,bLast);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}

void XSendDataManage::AddSendDataOfObtainSceneGroup(CString szSceneName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonObtainSceneGroup(szData,szSceneName);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}

void XSendDataManage::AddSendDataOfSetSceneGroup(CString szSceneName,CString szGroup,BOOL bAlter)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonSetSceneGroup(szData,szSceneName,szGroup,bAlter);

	TRACE(_T("AddSendDataOfSetSceneGroup:scene=%s,group=%s\n"),szSceneName,szGroup);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}

void XSendDataManage::AddSendDataOfDeleteSplitScene(CString szSceneName)
{
	CString szData;
	XJsonManage::GetInstance()->WriteJsonDeleteSplitScene(szData,szSceneName);

	AddData(szData,PROTOCOLTYPE_SPLITSCENE);
}