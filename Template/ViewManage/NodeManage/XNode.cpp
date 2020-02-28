#include "stdafx.h"
#include "XNode.h"
#include "XPropertiesWnd.h"
#include "XPropertyGrid.h"
#include "XProprtyGridFile.h"
#include "XTranslationManage.h"
#include "HandleCalculate.h"
#include "XNodeLoginUser.h"
#include "XNodeManage.h"
#include "XUserLogStatus.h"
#include "XSendDataManage.h"
#include "XOutResoluation.h"
#include "XAlterName.h"
#include "XKeyValue.h"



XNode::XNode()
{
	m_rect.SetRectEmpty();
	m_TextRect.SetRectEmpty();
}

XNode::~XNode()
{
	ClearMapHotKey();
}

void XNode::ClearMapHotKey()
{
	for(auto& key:m_MapHotKey)
	{
		delete key.second;
	}
	m_MapHotKey.clear();
}


MAP_SUBUSER& XNode::GetMapSubUser()
{
	return m_pNodeManage->GetMapSubUser();
}

MAP_POWER& XNode::GetMapPower()
{
	return m_pNodeManage->GetMapPower();
}

void XNode::OnPropertyChanged(CMFCPropertyGridProperty* pProperty)
{
	int nData=(int)pProperty->GetData();

	switch(nData)
	{
	case ID_NODEGROUP:
		{
			int nGroup=(_variant_t)(pProperty->GetValue());
			int nMark=UPDATAMAKE_GROUP;
			XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroup(GetNodeID(),nGroup,nMark);
		}
		break;
	case ID_NODEMASTER:
		{
			int nMaster=(_variant_t)(pProperty->GetValue());
			int nMark=UPDATAMAKE_MASTER;
			XSendDataManage::GetInstance()->AddSendDataOfUpdateNodeGroupMaster(GetNodeID(),nMaster,nMark);
		}
		break;
	case ID_NODENAME:
		{
			CString szNodeName=(_variant_t)(pProperty->GetValue());
			if(szNodeName!=_T(""))
			{
				int n=GetNodeID();
				XSendDataManage::GetInstance()->AddSendDataOfAlterNodeName(GetNodeID(),szNodeName);
			}
		}
		break;
	case ID_NODELOGIN:
		{
			CString szLogin=(_variant_t)(pProperty->GetValue());
			//TRACE(_T("szLogin=%s\n"),szLogin);

			if(szLogin==_T("True"))
			{
				//登录
				CMFCPropertyGridProperty* pTemp=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_NODELOGINUSER);
				CString szUserName=(_variant_t)(pTemp->GetValue());
				XSendDataManage::GetInstance()->AddSendDataOfNodeLogin(GetNodeID(),szUserName);
			}
			else if(szLogin==_T("False"))
			{
				//退出
				XSendDataManage::GetInstance()->AddSendDataOfNodeLogOut(GetNodeID());
			}	
		}
		break;
	case ID_NODELOGINUSER:
		{
			CString szUserName=(_variant_t)(pProperty->GetValue());

			int nUserID=m_pNodeManage->GetUserIDByName(szUserName);
			MAP_USERLOGINSTATUS& MapLoginUser=m_pNodeManage->GetMapUserLoginStatus();
			MAP_USERLOGINSTATUS::iterator iter=MapLoginUser.find(nUserID);
			if(iter!=MapLoginUser.end())
			{
				XUserLogStatus* pUser=iter->second;

				CMFCPropertyGridProperty* pIP=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_LOGINIP);
				pIP->SetValue((_variant_t)pUser->GetIP());

				CString szPort;
				if(pUser->GetPort()!=0)
					szPort.Format(_T("%d"),pUser->GetPort());
				else
					szPort=_T("");

				CMFCPropertyGridProperty* pPort=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_LOGINPORT);
				pPort->SetValue((_variant_t)szPort);
			}
			else
			{
				CMFCPropertyGridProperty* pIP=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_LOGINIP);
				pIP->SetValue((_variant_t)_T(""));

				CMFCPropertyGridProperty* pPort=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_LOGINPORT);
				pPort->SetValue((_variant_t)_T(""));
			}
		}
		break;
	case ID_TAKEOVERNODE:
		{
			//接管（输出）
			CMFCPropertyGridProperty* pTakeOverModel=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_TAKEOVERMODEL);
			CString szTakeOverModel=_variant_t(pTakeOverModel->GetValue());

			BOOL bExclusive=FALSE;
			if(szTakeOverModel==_C(_T("794"),_T("独占")))
			{
				bExclusive=TRUE;
			}
			else if(szTakeOverModel==_C(_T("795"),_T("共享")))
			{
				bExclusive=FALSE;
			}
			//根据通道获取ID
			int nTargetChannel=_variant_t(pProperty->GetValue());
			if(nTargetChannel==0)
			{
				XSendDataManage::GetInstance()->AddSendDataOfTakeOverCancel(GetNodeID());
			}
			else
			{
				int nNodeID=GetNodeIDByChannel(nTargetChannel);
				if(nNodeID!=0)
				{
					XSendDataManage::GetInstance()->AddSendDataOfTakeOver(GetNodeID(),nNodeID,bExclusive);
				}
			}
		}
		break;
	case ID_TARGETNODE:
		{
			//被接管（输入）
			CMFCPropertyGridProperty* pTakeOverModel=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_TAKEOVERMODEL);
			CString szTakeOverModel=(_variant_t)(pTakeOverModel->GetValue());

			BOOL bExclusive=FALSE;
			if(szTakeOverModel==_C(_T("794"),_T("独占")))
			{
				bExclusive=TRUE;
			}
			else if(szTakeOverModel==_C(_T("795"),_T("共享")))
			{
				bExclusive=FALSE;
			}

			CString szChannel=(_variant_t)(pProperty->GetValue());
			//分割字符串
			std::vector<int> vecInt;
			int nPos=0;
			CString szTemp;
			szTemp=szChannel.Tokenize(_T(";"),nPos);
			while(szTemp.Trim()!=_T(""))
			{
				int n=_ttoi(szTemp);
				vecInt.push_back(n);
				szTemp=szChannel.Tokenize(_T(";"),nPos);
			}

			if(vecInt.size()==1&&vecInt[0]==0)
			{
				//取消被接管
				XSendDataManage::GetInstance()->AddSendDataOfTakeOverCancel(GetNodeID());
			}
			else
			{
				//多个通道
				for(auto& nChannel:vecInt)
				{
					int nNodeID=GetNodeIDByChannel(nChannel);
					if(nNodeID!=0)
					{
						XSendDataManage::GetInstance()->AddSendDataOfTakeOver(nNodeID,GetNodeID(),bExclusive);
					}
				}
			}
		}
		break;
	case ID_PREVIEW:
		{
			//预览
			int nTargetChannel=(_variant_t)(pProperty->GetValue());

			int nTargetID=0;
			MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
			for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
			{
				XNode* pNode=iter->second;
				if(nTargetChannel==pNode->GetChannel())
					nTargetID=pNode->GetNodeID();
			}

			if(nTargetChannel==0)
			{
				XSendDataManage::GetInstance()->AddSendDataOfTakeOverCancel(GetNodeID());
			}
			else
			{
				int nNodeID=GetNodeIDByChannel(nTargetChannel);
				if(nNodeID!=0)
				{
					XSendDataManage::GetInstance()->AddSendDataOfPreview(GetNodeID(),nTargetID);
				}
			}		
		}
		break;
	case ID_PREVIEWTARGET:
		{
			CString szChannel=(_variant_t)(pProperty->GetValue());
			//分割字符串
			std::vector<int> vecInt;
			int nPos=0;
			CString szTemp;
			szTemp=szChannel.Tokenize(_T(";"),nPos);
			while(szTemp.Trim()!=_T(""))
			{
				int n=_ttoi(szTemp);
				vecInt.push_back(n);
				szTemp=szChannel.Tokenize(_T(";"),nPos);
			}

			if(vecInt.size()==1&&vecInt[0]==0)
			{
				XSendDataManage::GetInstance()->AddSendDataOfTakeOverCancel(GetNodeID());
			}
			else
			{
				for(auto& nChannel:vecInt)
				{
					int nNodeID=GetNodeIDByChannel(nChannel);
					if(nNodeID!=0)
					{
						XSendDataManage::GetInstance()->AddSendDataOfPreview(nNodeID,GetNodeID());
					}
				}
			}
		}
		break;
	case ID_AUDIOMODEL:
		{
			CString szAudioModel=(_variant_t)(pProperty->GetValue());

			int nAudioModel=0;
			if(szAudioModel==_C(_T("812"),_T("数字音频")))
				nAudioModel=1;
			else if(szAudioModel==_C(_T("811"),_T("模拟音频")))
				nAudioModel=0;

			XSendDataManage::GetInstance()->AddSendDataOfAlterAudioModel(GetNodeID(),nAudioModel);
		}
		break;
	case ID_AUDIOSRC:
		{
			//更改
			CString szAudioSrc=(_variant_t)(pProperty->GetValue());
			int nAudioSrc=_ttoi(szAudioSrc);
			if(nAudioSrc!=0)
				XSendDataManage::GetInstance()->AddSendDataOfAlterAudioSrc(GetNodeID(),nAudioSrc);
		}
		break;
	case ID_HIDMODEL:
		{
			CString szHidModel=(_variant_t)(pProperty->GetValue());
			int nHidModel=0;
			if(szHidModel==_T("Windows"))
				nHidModel=0;
			else if(szHidModel==_T("Windows10"))
				nHidModel=1;
			else if(szHidModel==_T("Android"))
				nHidModel=2;
			else if(szHidModel==_T("Ubuntu"))
				nHidModel=3;
			else if(szHidModel==_T("Redhat"))
				nHidModel=4;
			else if(szHidModel==_C(_T("861"),_T("透传")))
				nHidModel=5;

			XSendDataManage::GetInstance()->AddSendDataOfAlterHidModel(GetNodeID(),nHidModel);
		}
		break;
	case ID_SPLITSCREEN:
		{
			CString szSplitScreen=(_variant_t)(pProperty->GetValue());

			int nScreenModel=_ttoi(szSplitScreen);
			XSendDataManage::GetInstance()->AddSendDataOfAlterSplitScreenModel(GetNodeID(),nScreenModel);
		}
		break;
	case ID_RESOLUATION:
		{
			CString szRes=(_variant_t)(pProperty->GetValue());

			int nResIndex=0;
			MAP_RESULATIONINFO& MapResulation=m_pNodeManage->GetMapResoluationInfo();
			for(auto& info:MapResulation)
			{
				int nIndex=info.first;
				XOutResoluation* pResulation=info.second;
				if(pResulation->GetName()==szRes)
					nResIndex=nIndex;
			}


			//if(szResIndex==_T("4K 30Hz"))
			//	nResIndex=0;
			//else if(szResIndex==_T("1080p 60Hz"))
			//	nResIndex=1;
			//else if(szResIndex==_T("1080p 50Hz"))
			//	nResIndex=2;
			//else if(szResIndex==_T("1080p 30Hz"))
			//	nResIndex=3;
			//else if(szResIndex==_T("1080p 25Hz"))
			//	nResIndex=4;
			//else if(szResIndex==_T("1080i 60Hz"))
			//	nResIndex=5;
			//else if(szResIndex==_T("1080i 50Hz"))
			//	nResIndex=6;
			//else if(szResIndex==_T("720p 60hz"))
			//	nResIndex=7;
			//else if(szResIndex==_T("720p 60hz"))
			//	nResIndex=7;
			//else if(szResIndex==_T("1920*1200 60hz"))
			//	nResIndex=8;
			//else if(szResIndex==_T("1680*1050 60hz"))
			//	nResIndex=9;
			//else if(szResIndex==_T("1600*1200 60hz"))
			//	nResIndex=10;
			//else if(szResIndex==_T("1440*900 60hz"))
			//	nResIndex=11;
			//else if(szResIndex==_T("1366*768 60hz"))
			//	nResIndex=12;
			//else if(szResIndex==_T("1360*768 60hz"))
			//	nResIndex=13;
			//else if(szResIndex==_T("1280*768 60hz"))
			//	nResIndex=14;
			//else if(szResIndex==_T("1024*768 60hz"))
			//	nResIndex=15;

			XSendDataManage::GetInstance()->AddSendDataOfAlterResoluationIndex(GetNodeID(),nResIndex);
		}
		break;
	case ID_OUTMODEL:
		{
			CString szOutModel=(_variant_t)(pProperty->GetValue());
			int nOutModel=0;
			if(szOutModel==_T("DVI"))
				nOutModel=0;
			else if(szOutModel==_T("HDMI"))
				nOutModel=1;

			XSendDataManage::GetInstance()->AddSendDataOfAlterOutModel(GetNodeID(),nOutModel);
		}
		break;
	case ID_MATRIX:
		{
			int nInNodeChannel=_variant_t(pProperty->GetValue());
			if(nInNodeChannel!=0)
				XSendDataManage::GetInstance()->AddSendDataOfMatrix(nInNodeChannel,GetChannel());
		}
		break;
	case ID_OSDIMAGE:
		{
			CString szOSDModel=(_variant_t)(pProperty->GetValue());
			int nShow=0;
			if(szOSDModel==_C(_T("822"),_T("显示")))
				nShow=1;
			else if(szOSDModel==_C(_T("823"),_T("隐藏")))
				nShow=0;

			XSendDataManage::GetInstance()->AddSendDataOfHideOSDImage(nShow,GetChannel());
		}
		break;
	case ID_BINDCFG:
		{
			CString szBindCfg=(_variant_t)(pProperty->GetValue());
			int nBindCfg=_ttoi(szBindCfg);
			if(nBindCfg!=0)
			{
				XSendDataManage::GetInstance()->AddSendDataOfAlterBindCfg(GetNodeID(),nBindCfg);
			}
		}
		break;
	case ID_BINDNODEID:
		{
			CString szBindNodeID=(_variant_t)(pProperty->GetValue());
			int nBindNodeID=_ttoi(szBindNodeID);
			if(nBindNodeID!=0)
			{
				XSendDataManage::GetInstance()->AddSendDataOfAlterBindNodeID(GetNodeID(),nBindNodeID);
			}
		}
		break;
	case ID_FUNCTION1:
		{
			//功能键1
			CString szFunction=(_variant_t)(pProperty->GetValue());
			CString szValue;
			CMFCPropertyGridProperty* pValue=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE1);
			if(NULL!=pValue)
			{
				szValue=(_variant_t)(pValue->GetValue());
			}

			CString szEnable;
			CMFCPropertyGridProperty* pEnable=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE1);
			if(NULL!=pEnable)
			{
				szEnable=(_variant_t)(pEnable->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable==_T(""))
			{
				WriteHotKey(1,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
		break;
	case ID_VALUE1:
		{
			CString szValue=(_variant_t)(pProperty->GetValue());
			CString szFunction;
			CMFCPropertyGridProperty* pFunction=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION1);
			if(NULL!=pFunction)
			{
				szFunction=(_variant_t)(pFunction->GetValue());
			}

			CString szEnable;
			CMFCPropertyGridProperty* pEnable=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE1);
			if(NULL!=pEnable)
			{
				szEnable=(_variant_t)(pEnable->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(1,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
		break;
	case ID_ENABLE1:
		{
			CString szEnable=(_variant_t)(pProperty->GetValue());		
			CString szFunction;
			CMFCPropertyGridProperty* pFunction=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION1);
			if(NULL!=pFunction)
			{
				szFunction=(_variant_t)(pFunction->GetValue());
			}
			CString szValue;
			CMFCPropertyGridProperty* pValue=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE1);
			if(NULL!=pValue)
			{
				szValue=(_variant_t)(pValue->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(1,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
		break;
	case ID_FUNCTION2:
		{
			//功能键2
			CString szFunction=(_variant_t)(pProperty->GetValue());
			CString szValue;
			CMFCPropertyGridProperty* pValue=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE2);
			if(NULL!=pValue)
			{
				szValue=(_variant_t)(pValue->GetValue());
			}

			CString szEnable;
			CMFCPropertyGridProperty* pEnable=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE2);
			if(NULL!=pEnable)
			{
				szEnable=(_variant_t)(pEnable->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(2,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
		break;
	case ID_VALUE2:
		{
			CString szValue=(_variant_t)(pProperty->GetValue());
			CString szFunction;
			CMFCPropertyGridProperty* pFunction=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION2);
			if(NULL!=pFunction)
			{
				szFunction=(_variant_t)(pFunction->GetValue());
			}

			CString szEnable;
			CMFCPropertyGridProperty* pEnable=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE2);
			if(NULL!=pEnable)
			{
				szEnable=(_variant_t)(pEnable->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(2,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
		break;
	case ID_ENABLE2:
		{
			CString szEnable=(_variant_t)(pProperty->GetValue());
			CString szFunction;
			CMFCPropertyGridProperty* pFunction=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION2);
			if(NULL!=pFunction)
			{
				szFunction=(_variant_t)(pFunction->GetValue());
			}
			CString szValue;
			CMFCPropertyGridProperty* pValue=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE2);
			if(NULL!=pValue)
			{
				szValue=(_variant_t)(pValue->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(2,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
		break;
	case ID_FUNCTION3:
		{
			//功能键3
			CString szFunction=(_variant_t)(pProperty->GetValue());
			CString szValue;
			CMFCPropertyGridProperty* pValue=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE3);
			if(NULL!=pValue)
			{
				szValue=(_variant_t)(pValue->GetValue());
			}

			CString szEnable;
			CMFCPropertyGridProperty* pEnable=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE3);
			if(NULL!=pEnable)
			{
				szEnable=(_variant_t)(pEnable->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(3,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
		break;
	case ID_VALUE3:
		{
			CString szValue=(_variant_t)(pProperty->GetValue());
			CString szFunction;
			CMFCPropertyGridProperty* pFunction=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION3);
			if(NULL!=pFunction)
			{
				szFunction=(_variant_t)(pFunction->GetValue());
			}

			CString szEnable;
			CMFCPropertyGridProperty* pEnable=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE3);
			if(NULL!=pEnable)
			{
				szEnable=(_variant_t)(pEnable->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(3,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
	case ID_ENABLE3:
		{
			CString szEnable=(_variant_t)(pProperty->GetValue());
			CString szFunction;
			CMFCPropertyGridProperty* pFunction=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION3);
			if(NULL!=pFunction)
			{
				szFunction=(_variant_t)(pFunction->GetValue());
			}
			CString szValue;
			CMFCPropertyGridProperty* pValue=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE3);
			if(NULL!=pValue)
			{
				szValue=(_variant_t)(pValue->GetValue());
			}

			//登录写数据
			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(3,szFunction,szValue,szEnable);
				//发送
				XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
			}
		}
		break;
	case ID_RECOVER:
		{
			//恢复出厂 全部设置为
			CString szRecover=(_variant_t)(pProperty->GetValue());
			if(szRecover==_T("False"))
				return;

			//////////////////////////////////////////////////////////////////////////
			//设置
			CMFCPropertyGridProperty* pEnable1=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE1);
			if(NULL!=pEnable1)
			{
				pEnable1->SetValue(_C(_T("889"),_T("关闭")));
			}
			CMFCPropertyGridProperty* pFunction2=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION2);
			if(NULL!=pFunction2)
			{
				pFunction2->SetValue(_T("Ctrl"));
			}
			CMFCPropertyGridProperty* pValue2=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE2);
			if(NULL!=pValue2)
			{
				pValue2->SetValue(_C(_T("307"),_T("双击")));
			}
			CMFCPropertyGridProperty* pFunction3=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION3);
			if(NULL!=pFunction3)
			{
				pFunction3->SetValue(_T("Shift"));
			}
			CMFCPropertyGridProperty* pValue3=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE3);
			if(NULL!=pValue3)
			{
				pValue3->SetValue(_C(_T("307"),_T("双击")));
			}
			//////////////////////////////////////////////////////////////////////////
			CString szFunction;
			CMFCPropertyGridProperty* pFunctionS1=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION1);
			if(NULL!=pFunctionS1)
			{
				szFunction=(_variant_t)(pFunctionS1->GetValue());
			}

			CString szValue;
			CMFCPropertyGridProperty* pValueS1=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE1);
			if(NULL!=pValueS1)
			{
				szValue=(_variant_t)(pValueS1->GetValue());
			}

			CString szEnable;
			CMFCPropertyGridProperty* pEnableS1=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE1);
			if(NULL!=pEnableS1)
			{
				szEnable=(_variant_t)(pEnableS1->GetValue());
			}

			if(szFunction!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(1,szFunction,szValue,szEnable);
			}
			//-----------------------
			CMFCPropertyGridProperty* pFunctionS2=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION2);
			if(NULL!=pFunctionS2)
			{
				szFunction=(_variant_t)(pFunctionS2->GetValue());
			}

			CMFCPropertyGridProperty* pValueS2=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE2);
			if(NULL!=pValueS2)
			{
				szValue=(_variant_t)(pValueS2->GetValue());
			}

			CMFCPropertyGridProperty* pEnableS2=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE2);
			if(NULL!=pEnableS2)
			{
				szEnable=(_variant_t)(pEnableS2->GetValue());
			}

			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(2,szFunction,szValue,szEnable);
			}
			//-----------------------
			CMFCPropertyGridProperty* pFunctionS3=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_FUNCTION3);
			if(NULL!=pFunctionS3)
			{
				szFunction=(_variant_t)(pFunctionS3->GetValue());
			}

			CMFCPropertyGridProperty* pValueS3=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_VALUE3);
			if(NULL!=pValueS3)
			{
				szValue=(_variant_t)(pValueS3->GetValue());
			}

			CMFCPropertyGridProperty* pEnableS3=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().FindItemByData(ID_ENABLE3);
			if(NULL!=pEnableS3)
			{
				szEnable=(_variant_t)(pEnableS3->GetValue());
			}

			if(szFunction!=_T("")&&szValue!=_T("")&&szEnable!=_T(""))
			{
				WriteHotKey(3,szFunction,szValue,szEnable);
			}
			//发送
			XSendDataManage::GetInstance()->AddSendDataOfAlterHotKey(GetNodeID(),m_MapHotKey);
		}
		break;
	default:
		break;
	}
}

int XNode::GetNodeIDByChannel(int nChannel)
{
	MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
	for(auto& map:MapNode)
	{
		XNode* pNode=map.second;
		if(pNode->GetChannel()==nChannel)
			return pNode->GetNodeID();
	}
	return 0;
}

BOOL XNode::OnDblClkPropertyGrid(XPropertyGrid* pPropertyGrid)
{
	int nData=(int)pPropertyGrid->GetData();

	switch(nData)
	{
	case ID_NODENAME:
		{
			//更改名称
			XAlterName dlg;
			if(IDOK==dlg.DoModal())
			{
				CString szNodeName=dlg.GetNodeName();
				XSendDataManage::GetInstance()->AddSendDataOfAlterNodeName(GetNodeID(),szNodeName);
			}
		}
		break;
	default:
		break;
	}

	return TRUE;
}

BOOL XNode::OnDblClkPropertyGridFile(XPropertyGridFile* pPropertyGridFile)
{
	int nData=(int)pPropertyGridFile->GetData();

	switch(nData)
	{
	case ID_NODELOGINUSER:
		{
			XNodeLoginUser dlg;
			dlg.SetDelegate(this);
			if(IDOK==dlg.DoModal())
			{
				CString szUserName=dlg.GetUserName();

				if(_T("")!=szUserName)
					pPropertyGridFile->SetValue(szUserName);
			}
		}
		break;
	default:
		break;
	}

	return TRUE;
}

void XNode::OnClickButtonPropertyGridFile(XPropertyGridFile* pPropertyGridFile)
{
	int nData=(int)pPropertyGridFile->GetData();

	switch(nData)
	{
	case ID_NODELOGINUSER:
		{
			XNodeLoginUser dlg;
			dlg.SetDelegate(this);
			if(IDOK==dlg.DoModal())
			{
				CString szUserName=dlg.GetUserName();

				if(_T("")!=szUserName)
					pPropertyGridFile->SetValue(szUserName);
			}
		}
		break;
	default:
		break;
	}
}


void XNode::SetPropertiesWnd()
{
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RemoveAll();
	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().RedrawWindow();
	
	PropertyInfo();

	if(GetNodeType()==TERM_OUT)
		PropertyLoginStatus();

	PropertyTakeOver();

	PropertyPreview();

	if(GetNodeType()==TERM_OUT)
	{
		PropertyMatrix();
		PropertyOSDImage();
		PropertyBindSet();
		PropertyHotKey();
	}	
}

void XNode::PropertyInfo()
{
	XPropertyGrid* pGroup1=new XPropertyGrid(_C(_T("750"),_T("基本信息")));
	//ID
	XPropertyGrid* pNodeID=new XPropertyGrid(_C(_T("773"),_T("ID")),_variant_t(GetRealID()),
											 _C(_T("774"),_T("ID")),ID_NODEID);
	if(NULL!=pNodeID)
	{
		pNodeID->Enable(FALSE);
		pGroup1->AddSubItem(pNodeID);
	}

	//名称
	XPropertyGrid* pNodeName=new XPropertyGrid(_C(_T("753"),_T("名称")),_variant_t(GetNodeName()),
											   _C(_T("754"),_T("节点名称")),ID_NODENAME);
	if(NULL!=pNodeName)
	{
		pNodeName->SetNode(this);
		pNodeName->SetSeat(NULL);
		pGroup1->AddSubItem(pNodeName);
	}

	//编号
	XPropertyGrid* pNodeNO=new XPropertyGrid(_C(_T("751"),_T("编号")),_variant_t((long)GetNodeID(),VT_I4),
											 _C(_T("752"),_T("节点编号")),ID_NODENO);
	if(NULL!=pNodeNO)
	{
		pNodeNO->Enable(FALSE);
		pGroup1->AddSubItem(pNodeNO);
	}

	//通道
	XPropertyGrid* pNodeChannel=new XPropertyGrid(_C(_T("755"),_T("通道")),_variant_t((long)GetChannel(),VT_I4),
												  _C(_T("756"),_T("节点所在物理通道")),ID_NODECHANNEL);
	if(NULL!=pNodeChannel)
	{
		pNodeChannel->Enable(FALSE);
		pGroup1->AddSubItem(pNodeChannel);
	}


	//主通道
	XPropertyGrid* pNodeMainCh=new XPropertyGrid(_C(_T("763"),_T("主通道")),_variant_t((long)GetMainCh(),VT_I4),
												 _C(_T("764"),_T("主通道")));
	if(NULL!=pNodeMainCh)
	{
		pNodeMainCh->Enable(FALSE);
		pGroup1->AddSubItem(pNodeMainCh);
	}


	//类型
	CString szType;
	switch(GetNodeType())
	{
	case TERM_IN:
		{
			szType=_C(_T("759"),_T("输入"));
			XPropertyGrid* pType=new XPropertyGrid(_C(_T("757"),_T("类型")),(_variant_t)szType,
												   _C(_T("758"),_T("节点类型")),ID_NODETYPE);
			if(NULL!=pType)
			{
				pType->Enable(FALSE);
				pGroup1->AddSubItem(pType);
			}
			//////////////////////////////////////////////////////////////////////////
			CString szSignal=_T("");
			if(GetIsSignal())
				szSignal=_C(_T("892"),_T("有"));
			else
				szSignal=_C(_T("893"),_T("无"));

			XPropertyGrid* pSignal=new XPropertyGrid(_C(_T("805"),_T("信号")),(_variant_t)szSignal,
													 _C(_T("806"),_T("输入是否有信号")),ID_NODEINHASSIGNAL);
			if(NULL!=pSignal)
			{
				pGroup1->AddSubItem(pSignal);
				pSignal->Enable(FALSE);
			}
			//////////////////////////////////////////////////////////////////////////
			CString szResoluation;
			if(GetInResolusationH()!=0&&GetInResolusationV()!=0)
				szResoluation.Format(_T("%d*%d"),GetInResolusationH(),GetInResolusationV());
			else
				szResoluation=_T("");
			
			XPropertyGrid* pResoluation=new XPropertyGrid(_C(_T("807"),_T("分辨率")),(_variant_t)szResoluation,
														  _C(_T("808"),_T("输入信号分辨率")));
			if(NULL!=pResoluation)
			{
				pResoluation->Enable(FALSE);
				pGroup1->AddSubItem(pResoluation);
			}
			//////////////////////////////////////////////////////////////////////////
			//11.11添加软硬件版本
			XPropertyGrid* pSoftVer=new XPropertyGrid(_C(_T("864"),_T("软件版本")),(_variant_t)GetSoftVer(),
														  _C(_T("865"),_T("节点软件版本号")));
			if(NULL!=pSoftVer)
			{
				pSoftVer->Enable(FALSE);
				pGroup1->AddSubItem(pSoftVer);
			}
			XPropertyGrid* pHardVer=new XPropertyGrid(_C(_T("866"),_T("硬件版本")),(_variant_t)GetHardVer(),
													  _C(_T("867"),_T("节点硬件版本号")));
			if(NULL!=pHardVer)
			{
				pHardVer->Enable(FALSE);
				pGroup1->AddSubItem(pHardVer);
			}

			//////////////////////////////////////////////////////////////////////////
			CString szAudioModel;
			if(GetAudioModel()==0)
				szAudioModel=_C(_T("811"),_T("模拟音频"));
			else if(GetAudioModel()==1)
				szAudioModel=_C(_T("812"),_T("数字音频"));
			else if(GetAudioModel()==-1)
				szAudioModel=_T("");
			
			XPropertyGrid* pAudioModel=new XPropertyGrid(_C(_T("809"),_T("音频")),(_variant_t)szAudioModel,
														 _C(_T("810"),_T("音频包括模拟音频、数字音频")),ID_AUDIOMODEL);
			if(NULL!=pAudioModel)
			{
				pAudioModel->SetNode(this);
				pAudioModel->SetSeat(NULL);
				pAudioModel->AddOption(_C(_T("812"),_T("数字音频")));
				pAudioModel->AddOption(_C(_T("811"),_T("模拟音频")));
				pAudioModel->AllowEdit(FALSE);
				pGroup1->AddSubItem(pAudioModel);
			}
			//////////////////////////////////////////////////////////////////////////
			//当前监听音源
			CString szAudioSrc;
			szAudioSrc.Format(_T("%d"),GetAudioSrc());
			XPropertyGrid* pAudioSrc=new XPropertyGrid(_C(_T("868"),_T("音频源节点编号")),(_variant_t)szAudioSrc,
													  _C(_T("869"),_T("当前监听音频的源节点编号")),ID_AUDIOSRC);
			if(NULL!=pAudioSrc)
			{
				pGroup1->AddSubItem(pAudioSrc);
			}
			//////////////////////////////////////////////////////////////////////////
			CString szHidModel;
			if(GetHidModel()==0)
				szHidModel=_T("Windows");
			else if(GetHidModel()==1)
				szHidModel=_T("Windows10");
			else if(GetHidModel()==2)
				szHidModel=_T("Android");
			else if(GetHidModel()==3)
				szHidModel=_T("Ubuntu");
			else if(GetHidModel()==4)
				szHidModel=_T("Redhat");
			else if(GetHidModel()==5)
				szHidModel=_C(_T("861"),_T("透传"));
			
			XPropertyGrid* pHidModel=new XPropertyGrid(_C(_T("859"),_T("系统")),(_variant_t)szHidModel,_C(_T("860"),_T("输入操作系统")),ID_HIDMODEL);
			if(NULL!=pHidModel)
			{
				pHidModel->SetNode(this);
				pHidModel->SetSeat(NULL);
				pHidModel->AddOption(_T("Windows"));
				pHidModel->AddOption(_T("Windows10"));
				pHidModel->AddOption(_T("Android"));
				pHidModel->AddOption(_T("Ubuntu"));
				pHidModel->AddOption(_T("Redhat"));
				pHidModel->AddOption(_C(_T("861"),_T("透传")));
				pHidModel->AllowEdit(FALSE);
				pGroup1->AddSubItem(pHidModel);
			}
			//分屏//////////////////////////////////////////////////////////////////////////
			CString szSplitScreen;
			szSplitScreen.Format(_T("%d"),m_nSplitScreen);
			XPropertyGrid* pSplitScreen=new XPropertyGrid(_C(_T("862"),_T("分屏模式")),(_variant_t)szSplitScreen,_C(_T("863"),_T("分屏模式")),ID_SPLITSCREEN);
			if(NULL!=pSplitScreen)
			{
				pSplitScreen->SetNode(this);
				pSplitScreen->SetSeat(NULL);
				pSplitScreen->AddOption(_T("1"));
				pSplitScreen->AddOption(_T("2"));
				pSplitScreen->AddOption(_T("3"));
				pSplitScreen->AddOption(_T("4"));
				pSplitScreen->AddOption(_T("5"));
				pSplitScreen->AddOption(_T("6"));
				pSplitScreen->AddOption(_T("7"));
				pSplitScreen->AddOption(_T("8"));
				pSplitScreen->Enable(FALSE);
				pGroup1->AddSubItem(pSplitScreen);
			}
			//初始化时状态
			if(szHidModel==_T("Ubuntu")||szHidModel==_T("Redhat"))
			{
				pSplitScreen->Enable(TRUE);
			}
			else
			{
				pSplitScreen->Enable(FALSE);
			}
		}
		break;
	case TERM_OUT:
		{
			szType=_C(_T("760"),_T("输出"));
			XPropertyGrid* pType=new XPropertyGrid(_C(_T("757"),_T("类型")),(_variant_t)szType,
												   _C(_T("758"),_T("节点类型")),ID_NODETYPE);
			if(NULL!=pType)
			{
				pType->Enable(FALSE);
				pGroup1->AddSubItem(pType);
			}
			//////////////////////////////////////////////////////////////////////////
			//添加软硬件版本 11.19
			XPropertyGrid* pOutSoftVer=new XPropertyGrid(_C(_T("864"),_T("软件版本")),(_variant_t)GetOutSoftVer(),
													  _C(_T("865"),_T("节点软件版本号")));
			if(NULL!=pOutSoftVer)
			{
				pOutSoftVer->Enable(FALSE);
				pGroup1->AddSubItem(pOutSoftVer);
			}
			XPropertyGrid* pOutHardVer=new XPropertyGrid(_C(_T("866"),_T("硬件版本")),(_variant_t)GetOutHardVer(),
													  _C(_T("867"),_T("节点硬件版本号")));
			if(NULL!=pOutHardVer)
			{
				pOutHardVer->Enable(FALSE);
				pGroup1->AddSubItem(pOutHardVer);
			}

			//////////////////////////////////////////////////////////////////////////
			CString szOutRes=_T("");
			MAP_RESULATIONINFO& MapResInfo=m_pNodeManage->GetMapResoluationInfo();
			MAP_RESULATIONINFO::iterator iter=MapResInfo.find(GetOutResoluationIndex());
			if(iter!=MapResInfo.end())
			{
				XOutResoluation* pInfo=iter->second;
				szOutRes=pInfo->GetName();
			}

			XPropertyGrid* pOutResoluation=new XPropertyGrid(_C(_T("807"),_T("分辨率")),(_variant_t)szOutRes,
															 _C(_T("813"),_T("输出分辨率信息")),ID_RESOLUATION);
			if(NULL!=pOutResoluation)
			{
				pOutResoluation->SetNode(this);
				pOutResoluation->SetSeat(NULL);
				pOutResoluation->AddOption(_T("4K 30Hz"));
				pOutResoluation->AddOption(_T("1080p 60Hz"));
				pOutResoluation->AddOption(_T("1080p 50Hz"));
				pOutResoluation->AddOption(_T("1080p 30Hz"));
				pOutResoluation->AddOption(_T("1080p 25Hz"));
				pOutResoluation->AddOption(_T("1080i 60Hz"));
				pOutResoluation->AddOption(_T("1080i 50Hz"));
				pOutResoluation->AddOption(_T("720p 60hz"));
				pOutResoluation->AddOption(_T("1920*1200 60hz"));
				pOutResoluation->AddOption(_T("1680*1050 60hz"));
				pOutResoluation->AddOption(_T("1600*1200 60hz"));
				pOutResoluation->AddOption(_T("1440*900 60hz"));
				pOutResoluation->AddOption(_T("1366*768 60hz"));
				pOutResoluation->AddOption(_T("1360*768 60hz"));
				pOutResoluation->AddOption(_T("1280*768 60hz"));
				pOutResoluation->AddOption(_T("1024*768 60hz"));
				pOutResoluation->AllowEdit(FALSE);
				pGroup1->AddSubItem(pOutResoluation);
			}

			//////////////////////////////////////////////////////////////////////////
			CString szOutModel;
			if(GetOutModel()==0)
				szOutModel=_T("DVI");
			else if(GetOutModel()==1)
				szOutModel=_T("HDMI");
			else if(GetOutModel()==-1)
				szOutModel=_T("");

			XPropertyGrid* pOutModel=new XPropertyGrid(_C(_T("814"),_T("输出方式")),(_variant_t)szOutModel,
													   _C(_T("815"),_T("输出方式：DVI、HDMI")),ID_OUTMODEL);
			if(NULL!=pOutModel)
			{
				pOutModel->SetNode(this);
				pOutModel->SetSeat(NULL);
				pOutModel->AddOption(_T("DVI"));
				pOutModel->AddOption(_T("HDMI"));
				pOutModel->AllowEdit(FALSE);
				pGroup1->AddSubItem(pOutModel);
			}
		}
		break;
	default:
		break;
	}

	//组
	XPropertyGrid* pNodeGroup=new XPropertyGrid(_C(_T("767"),_T("组")),_variant_t((long)GetGroup(),VT_I4),
												_C(_T("768"),_T("组")),ID_NODEGROUP);
	if(NULL!=pNodeGroup)
	{
		pNodeGroup->SetNode(this);
		pNodeGroup->SetSeat(NULL);
		pNodeGroup->Enable(FALSE);
		pGroup1->AddSubItem(pNodeGroup);
	}
	
	//主
	XPropertyGrid* pNodeMaster=new XPropertyGrid(_C(_T("769"),_T("主")),_variant_t((long)GetMaster(),VT_I4),
												 _C(_T("770"),_T("主")),ID_NODEMASTER);
	if(NULL!=pNodeMaster)
	{
		pNodeMaster->SetNode(this);
		pNodeMaster->SetSeat(NULL);
		pNodeMaster->Enable(FALSE);
		pGroup1->AddSubItem(pNodeMaster);
	}

	//控制
	XPropertyGrid* pNodeControl=new XPropertyGrid(_C(_T("771"),_T("控制")),_variant_t((long)GetControl(),VT_I4),
												  _C(_T("772"),_T("控制")),ID_NODECONTROL);
	if(NULL!=pNodeControl)
	{
		pNodeControl->SetNode(this);
		pNodeControl->SetSeat(NULL);
		pNodeControl->Enable(FALSE);
		pGroup1->AddSubItem(pNodeControl);
	}


	//连接时间
	time_t time=GetConnectTime();
	CString szTime=HandleCalculate::GetTimeBySecond(time);
	XPropertyGrid* pConnectTime=new XPropertyGrid(_C(_T("761"),_T("连接时间")),(_variant_t)szTime,
												  _C(_T("762"),_T("节点开始连接的时间")));
	if(NULL!=pConnectTime)
	{
		pConnectTime->Enable(FALSE);
		pGroup1->AddSubItem(pConnectTime);
	}

	//创建时间
	time_t CreateTime=GetCreateTime();
	CString szCreateTime=HandleCalculate::GetTimeBySecond(CreateTime);
	XPropertyGrid* pCreateTime=new XPropertyGrid(_C(_T("765"),_T("创建时间")),(_variant_t)szCreateTime,
												 _C(_T("766"),_T("创建时间")));
	if(NULL!=pCreateTime)
	{
		pCreateTime->Enable(FALSE);
		pGroup1->AddSubItem(pCreateTime);
	}

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup1);
}

void XNode::PropertyLoginStatus()
{
	//节点登录
	XPropertyGrid* pGroup2=new XPropertyGrid(_C(_T("776"),_T("登录状态")));
	//////////////////////////////////////////////////////////////////////////
	MAP_USERLOGINSTATUS& MapUserLogin=m_pNodeManage->GetMapUserLoginStatus();
	XUserLogStatus* pUserLogin=GetUserLoginStatusByNodeID(MapUserLogin,GetNodeID());
	if(NULL!=pUserLogin)
	{
		m_szLoginUser=pUserLogin->GetUserName();
		m_bNetLogin=pUserLogin->GetNetLogin();
		m_szIP=pUserLogin->GetIP();
		m_nPort=pUserLogin->GetPort();
		m_bNodeLogin=pUserLogin->GetNodeLogin();
	}
	else
	{
		m_szLoginUser=_T("");
		m_bNetLogin=FALSE;
		m_szIP=_T("");
		m_nPort=0;
		m_bNodeLogin=FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////	
	//pGroup2->AddSubItem(pLoginStatus);
	//登录用户
	XPropertyGridFile* pLoginUser=new XPropertyGridFile(_C(_T("779"),_T("用户")),(_variant_t)m_szLoginUser,ID_NODELOGINUSER,
														_C(_T("780"),_T("TERM_OUT")));
	if(NULL!=pLoginUser)
	{
		pGroup2->AddSubItem(pLoginUser);

		pLoginUser->SetNode(this);
		pLoginUser->SetSeat(NULL);

		if(m_bNodeLogin)
			pLoginUser->Enable(FALSE);
		else
			pLoginUser->Enable(TRUE);
	}

	//网络登录
	XPropertyGrid* pNetLog=new XPropertyGrid(_C(_T("783"),_T("网络登录")));
	if(NULL!=pNetLog)
	{
		pGroup2->AddSubItem(pNetLog);
	}
	
	XPropertyGrid* pIP=new XPropertyGrid(_C(_T("787"),_T("IP")),(_variant_t)m_szIP,
										 _C(_T("787"),_T("网络登录IP")),ID_LOGINIP);
	if(NULL!=pIP)
	{
		pIP->Enable(FALSE);
		pNetLog->AddSubItem(pIP);
	}


	CString szPort;
	if(m_nPort)
		szPort.Format(_T("%d"),m_nPort);
	else
		szPort=_T("");

	XPropertyGrid* pPort=new XPropertyGrid(_C(_T("789"),_T("端口")),(_variant_t)szPort,
										   _C(_T("790"),_T("网络登录端口")),ID_LOGINPORT);
	if(NULL!=pPort)
	{
		pPort->Enable(FALSE);
		pNetLog->AddSubItem(pPort);
	}


	//节点登录
	XPropertyGrid* pNodeLog=new XPropertyGrid(_C(_T("785"),_T("节点登录")));
	if(NULL!=pNodeLog)
	{
		pGroup2->AddSubItem(pNodeLog);
	}
	
	//登录
	CString szLogin;
	if(m_bNodeLogin)
		szLogin=_C(_T("894"),_T("是"));
	else
		szLogin=_C(_T("895"),_T("否"));

	XPropertyGrid* pNodeLogin=new XPropertyGrid(_C(_T("777"),_T("登录")),_variant_t(szLogin),
												_C(_T("778"),_T("登录")),ID_NODELOGIN);
	if(NULL!=pNodeLogin)
	{
		pNodeLog->AddSubItem(pNodeLogin);
		pNodeLogin->SetNode(this);
		pNodeLogin->SetSeat(NULL);

		pNodeLogin->AddOption(_C(_T("894"),_T("是")));
		pNodeLogin->AddOption(_C(_T("895"),_T("否")));
		pNodeLogin->AllowEdit(FALSE);
	}

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup2);
}

void XNode::PropertyTakeOver()
{
	//节点接管
	XPropertyGrid* pGroup3=new XPropertyGrid(_C(_T("791"),_T("节点接管")));
	
	if(GetNodeType()==TERM_OUT)
	{
		//输出节点（接管节点）
		int nTakeOverNodeChannel=0;
		MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
		MAP_NODE::iterator iter=MapNode.find(GetTakeOverNodeID());
		if(iter!=MapNode.end())
		{
			XNode* pNode=iter->second;
			nTakeOverNodeChannel=pNode->GetChannel();
		}

		XPropertyGrid* pTakeOverNode=new XPropertyGrid(_C(_T("797"),_T("接管节点")),_variant_t((long)nTakeOverNodeChannel,VT_I4),
													   _C(_T("798"),_T("接管节点（输出节点）")),ID_TAKEOVERNODE);
		if(NULL!=pTakeOverNode)
		{
			pGroup3->AddSubItem(pTakeOverNode);
		}
		
		//int nID=GetTakeOverNodeID();
		//TRACE(_T("ID=%d\n"),GetTakeOverNodeID());
		//////////////////////////////////////////////////////////////////////////
		//接管方式
		CString szTakeOverModel;	
		MAP_NODE::iterator iter1=MapNode.find(GetTakeOverNodeID());
		if(iter1!=MapNode.end())
		{
			XNode* pNode=iter1->second;
			int nTakeOverModel=pNode->GetNodeInStatus();
			if(nTakeOverModel==TERM_IN_NONE)
			{
				szTakeOverModel=_T("");
			}
			else if(nTakeOverModel==TERM_IN_BE_CTRL_SHARE)
			{
				szTakeOverModel=_C(_T("795"),_T("共享"));
			}
			else if(nTakeOverModel==TERM_IN_BE_CTRL_EXCLUSIVE)
			{
				szTakeOverModel=_C(_T("794"),_T("独占"));
			}
		}

		XPropertyGrid* pTakeModel=new XPropertyGrid(_C(_T("792"),_T("接管模式")),_variant_t(szTakeOverModel),
													_C(_T("793"),_T("接管模式：独占、共享")),ID_TAKEOVERMODEL);
		if(NULL!=pTakeModel)
		{
			pGroup3->AddSubItem(pTakeModel);
			pTakeModel->SetNode(this);
			pTakeModel->SetSeat(NULL);

			pTakeModel->AddOption(_C(_T("794"),_T("独占")));
			pTakeModel->AddOption(_C(_T("795"),_T("共享")));
			pTakeModel->AllowEdit(FALSE);
		}
	}
	else if(GetNodeType()==TERM_IN)
	{
		//被谁接管
		int nID=GetNodeID();


		//可以被多个接管
		//int nBbTakeOver=0;
		//MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
		//for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
		//{
		//	XNode* pNode=iter->second;
		//	if(GetNodeID()==pNode->GetTakeOverNodeID())
		//	{
		//		nBbTakeOver=pNode->GetNodeID();
		//	}
		//}

		CString szBeTakeOver;
		MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
		for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
		{
			XNode* pNode=iter->second;
			if(GetNodeID()==pNode->GetTakeOverNodeID())
			{
				CString szTemp;
				szTemp.Format(_T("%d;"),pNode->GetChannel());
				szBeTakeOver+=szTemp;
			}
		}

		XPropertyGrid* pTargetNode=new XPropertyGrid(_C(_T("799"),_T("被接管")),_variant_t(szBeTakeOver)/*_variant_t((long)nBbTakeOver,VT_I4)*/,
													 _C(_T("800"),_T("被接管节点（输入节点）")),ID_TARGETNODE);
		if(NULL!=pTargetNode)
		{
			pGroup3->AddSubItem(pTargetNode);
		}
		
		//////////////////////////////////////////////////////////////////////////
		//接管模式
		CString szTakeOverModel;
		int nInStatus=GetNodeInStatus();
		if(nInStatus==TERM_IN_BE_CTRL_SHARE)
		{
			szTakeOverModel=_C(_T("795"),_T("共享"));
		}
		else if(nInStatus==TERM_IN_BE_CTRL_EXCLUSIVE)
		{
			szTakeOverModel=_C(_T("794"),_T("独占"));
		}
		else if(nInStatus==TERM_IN_NONE)
		{
			szTakeOverModel=_T("");
		}

		XPropertyGrid* pTakeModel=new XPropertyGrid(_C(_T("792"),_T("接管模式")),_variant_t(szTakeOverModel),
													_C(_T("793"),_T("接管模式：独占、共享")),ID_TAKEOVERMODEL);
		if(NULL!=pTakeModel)
		{
			pGroup3->AddSubItem(pTakeModel);
			pTakeModel->SetNode(this);
			pTakeModel->SetSeat(NULL);

			pTakeModel->AddOption(_C(_T("794"),_T("独占")));
			pTakeModel->AddOption(_C(_T("795"),_T("共享")));
			pTakeModel->AllowEdit(FALSE);
		}
	}

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup3);
}

void XNode::PropertyPreview()
{
	//节点预览
	XPropertyGrid* pGroup4=new XPropertyGrid(_C(_T("801"),_T("节点预览")));

	if(GetNodeType()==TERM_OUT)
	{

		//int nPreviewNodeChannel=0;
		//MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
		//MAP_NODE::iterator iter=MapNode.find(GetPreviewNodeID());
		//if(iter!=MapNode.end())
		//{
		//	XNode* pNode=iter->second;
		//	nPreviewNodeChannel=pNode->GetChannel();
		//}


		CString szBePreviewOver;
		MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
		for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
		{
			XNode* pNode=iter->second;
			if(GetNodeID()==pNode->GetPreviewNodeID())
			{
				CString szTemp;
				szTemp.Format(_T("%d;"),pNode->GetChannel());
				szBePreviewOver+=szTemp;
			}
		}

		XPropertyGrid* pPreview=new XPropertyGrid(_C(_T("801"),_T("预览")),_variant_t(szBePreviewOver),
												  _C(_T("802"),_T("预览节点编号，输入节点编号预览输入，为0时没有预览")),ID_PREVIEW);
		if(NULL!=pPreview)
		{
			pGroup4->AddSubItem(pPreview);
		}	
	}
	else if(GetNodeType()==TERM_IN)
	{
		//被预览
		int nBbPreview=0;
		MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
		for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
		{
			XNode* pNode=iter->second;
			if(GetNodeID()==pNode->GetPreviewNodeID())
			{
				nBbPreview=pNode->GetChannel();
			}
		}

		XPropertyGrid* pBePreview=new XPropertyGrid(_C(_T("803"),_T("被预览")),_variant_t((long)nBbPreview,VT_I4),
													_C(_T("804"),_T("预览者编号，输入编号则当前输入被预览，为0时没有预览者")),ID_PREVIEWTARGET);
		if(NULL!=pBePreview)
		{
			pGroup4->AddSubItem(pBePreview);
		}
	}

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup4);
}

void XNode::PropertyMatrix()
{
	XPropertyGrid* pGroup5=new XPropertyGrid(_C(_T("816"),_T("矩阵切换")));

	//根据ID查找通道号
	int nOutChannel=0;
	MAP_NODE& MapNode=m_pNodeManage->GetMapNode();
	MAP_NODE::iterator iter=MapNode.find(GetNodeID());
	if(iter!=MapNode.end())
	{
		XNode* pNode=iter->second;
		nOutChannel=pNode->GetChannel();
	}

	//输入通道号
	int nInChannel=0;
	MAP_MATRIX& MapMatrix=m_pNodeManage->GetMapMatrix();
	MAP_MATRIX::iterator iter1=MapMatrix.find(nOutChannel);
	if(iter1!=MapMatrix.end())
	{
		nInChannel=iter1->second;
	}

	XPropertyGrid* pMatrix=new XPropertyGrid(_C(_T("817"),_T("输入通道")),_variant_t((long)nInChannel,VT_I4),
											 _C(_T("818"),_T("切换到当前输出的输入通道号，改变通道号可切换")),ID_MATRIX);
	if(NULL!=pMatrix)
	{
		pGroup5->AddSubItem(pMatrix);
	}

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup5);
}

void XNode::PropertyOSDImage()
{
	XPropertyGrid* pGroup6=new XPropertyGrid(_C(_T("819"),_T("OSD底图")));
	XPropertyGrid* pOSDImage=new XPropertyGrid(_C(_T("820"),_T("底图")),_variant_t(_C(_T("822"),_T("显示"))),
											   _C(_T("821"),_T("显示或者隐藏OSD底图")),ID_OSDIMAGE);
	if(NULL!=pOSDImage)
	{
		pGroup6->AddSubItem(pOSDImage);

		pOSDImage->SetNode(this);
		pOSDImage->SetSeat(NULL);
		pOSDImage->AddOption(_C(_T("822"),_T("显示")));
		pOSDImage->AddOption(_C(_T("823"),_T("隐藏")));
		pOSDImage->AllowEdit(FALSE);
	}

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup6);
}

void XNode::PropertyBindSet()
{
	XPropertyGrid* pGroup7=new XPropertyGrid(_C(_T("870"),_T("绑定设置")));

	//绑定设置
	CString nBindCfg;
	nBindCfg.Format(_T("%d"),GetBindCfg());
	XPropertyGrid* pBindCfg=new XPropertyGrid(_C(_T("870"),_T("绑定设置")),nBindCfg,
											   _C(_T("871"),_T("显示绑定设置")),ID_BINDCFG);
	if(NULL!=pBindCfg)
	{
		pGroup7->AddSubItem(pBindCfg);
	}
	//绑定节点ID
	CString szBindNodeID;
	szBindNodeID.Format(_T("%d"),GetBindNodeID());
	XPropertyGrid* pBindNodeID=new XPropertyGrid(_C(_T("872"),_T("绑定的节点ID")),szBindNodeID,
											  _C(_T("873"),_T("显示绑定输出节点编号")),ID_BINDNODEID);
	if(NULL!=pBindNodeID)
	{
		pGroup7->AddSubItem(pBindNodeID);
	}

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup7);
}

void XNode::PropertyHotKey()
{
	//解析返回数组
	ParseVecValue();
	//////////////////////////////////////////////////////////////////////////
	MAP_KEYVALUE& MapKeyValue=m_pNodeManage->GetMapKeyValue();
	XPropertyGrid* pGroup8=new XPropertyGrid(_C(_T("874"),_T("设置快捷键")));

	//////////////////////////////////////////////////////////////////////////
	CString szFunction1,szValue1,szEnable1;
	ParseHotKey(1,szFunction1,szValue1,szEnable1);

	XPropertyGrid* pHotKey1=new XPropertyGrid(_C(_T("876"),_T("登录")),ID_HOTKEY1,TRUE);
	if(NULL!=pHotKey1)
	{
		pGroup8->AddSubItem(pHotKey1);
		pHotKey1->AllowEdit(FALSE);
		pHotKey1->SetNode(this);
		pHotKey1->SetSeat(NULL);
	}

	XPropertyGrid* pFunction1=new XPropertyGrid(_C(_T("882"),_T("功能键")),(_variant_t)szFunction1,
											   _C(_T("883"),_T("功能键")),ID_FUNCTION1);

	if(NULL!=pFunction1)
	{
		pHotKey1->AddSubItem(pFunction1);

		pFunction1->SetNode(this);
		pFunction1->SetSeat(NULL);
		pFunction1->AddOption(_T("Ctrl"));
		pFunction1->AddOption(_T("Shift"));
		pFunction1->AddOption(_T("Alt"));
		pFunction1->AddOption(_T("Win"));
		
		pFunction1->AllowEdit(FALSE);
	}

	XPropertyGrid* pValue1=new XPropertyGrid(_C(_T("884"),_T("键值")),(_variant_t)szValue1,
											   _C(_T("885"),_T("键盘键值")),ID_VALUE1);
	if(NULL!=pValue1)
	{
		pHotKey1->AddSubItem(pValue1);
		pValue1->SetNode(this);
		pValue1->SetSeat(NULL);
		pValue1->AddOption(_C(_T("307"),_T("双击")));

		for(auto& key:MapKeyValue)
		{
			CString szKey=key.first;
			pValue1->AddOption(szKey);
		}

		pValue1->AllowEdit(FALSE);
	}

	XPropertyGrid* pEnable1=new XPropertyGrid(_C(_T("886"),_T("启用")),(_variant_t)szEnable1,
											 _C(_T("887"),_T("是否开启快捷键")),ID_ENABLE1);
	if(NULL!=pEnable1)
	{
		pHotKey1->AddSubItem(pEnable1);
		pEnable1->SetNode(this);
		pEnable1->SetSeat(NULL);
		pEnable1->AddOption(_C(_T("888"),_T("开启")));
		pEnable1->AddOption(_C(_T("889"),_T("关闭")));
		pEnable1->AllowEdit(FALSE);
	}

	//////////////////////////////////////////////////////////////////////////
	CString szFunction2,szValue2,szEnable2;
	ParseHotKey(2,szFunction2,szValue2,szEnable2);
	XPropertyGrid* pHotKey2=new XPropertyGrid(_C(_T("878"),_T("接管")),ID_HOTKEY2,TRUE);
	if(NULL!=pHotKey2)
	{
		pGroup8->AddSubItem(pHotKey2);
		pHotKey2->AllowEdit(FALSE);
		pHotKey2->SetNode(this);
		pHotKey2->SetSeat(NULL);
	}

	XPropertyGrid* pFunction2=new XPropertyGrid(_C(_T("882"),_T("功能键")),(_variant_t)szFunction2,
												_C(_T("883"),_T("功能键")),ID_FUNCTION2);
	if(NULL!=pFunction2)
	{
		pHotKey2->AddSubItem(pFunction2);

		pFunction2->SetNode(this);
		pFunction2->SetSeat(NULL);
		pFunction2->AddOption(_T("Ctrl"));
		pFunction2->AddOption(_T("Shift"));
		pFunction2->AddOption(_T("Alt"));
		pFunction2->AddOption(_T("Win"));
		
		pFunction2->AllowEdit(FALSE);
	}

	XPropertyGrid* pValue2=new XPropertyGrid(_C(_T("884"),_T("键值")),(_variant_t)szValue2,
											 _C(_T("885"),_T("键盘键值")),ID_VALUE2);
	if(NULL!=pValue2)
	{
		pHotKey2->AddSubItem(pValue2);

		pValue2->SetNode(this);
		pValue2->SetSeat(NULL);
		pValue2->AddOption(_C(_T("307"),_T("双击")));
		CString szValue=(_variant_t)pFunction2->GetValue();

		for(auto& key:MapKeyValue)
		{
			CString szKey=key.first;
			pValue2->AddOption(szKey);
		}
		
		pValue2->AllowEdit(FALSE);
	}

	XPropertyGrid* pEnable2=new XPropertyGrid(_C(_T("886"),_T("启用")),(_variant_t)szEnable2,
											  _C(_T("887"),_T("是否开启快捷键")),ID_ENABLE2);
	if(NULL!=pEnable2)
	{
		pHotKey2->AddSubItem(pEnable2);
		pEnable2->SetNode(this);
		pEnable2->SetSeat(NULL);
		pEnable2->AddOption(_C(_T("888"),_T("开启")));
		pEnable2->AddOption(_C(_T("889"),_T("关闭")));
		pEnable2->AllowEdit(FALSE);
	}

	//////////////////////////////////////////////////////////////////////////
	CString szFunction3,szValue3,szEnable3;
	ParseHotKey(3,szFunction3,szValue3,szEnable3);
	XPropertyGrid* pHotKey3=new XPropertyGrid(_C(_T("880"),_T("推送")),ID_HOTKEY3,TRUE);
	if(NULL!=pHotKey3)
	{
		pGroup8->AddSubItem(pHotKey3);
		pHotKey3->AllowEdit(FALSE);
		pHotKey3->SetNode(this);
		pHotKey3->SetSeat(NULL);
	}

	XPropertyGrid* pFunction3=new XPropertyGrid(_C(_T("882"),_T("功能键")),(_variant_t)szFunction3,
												_C(_T("883"),_T("功能键")),ID_FUNCTION3);
	if(NULL!=pFunction3)
	{
		pHotKey3->AddSubItem(pFunction3);

		pFunction3->SetNode(this);
		pFunction3->SetSeat(NULL);
		pFunction3->AddOption(_T("Ctrl"));
		pFunction3->AddOption(_T("Shift"));
		pFunction3->AddOption(_T("Alt"));
		pFunction3->AddOption(_T("Win"));
		
		pFunction3->AllowEdit(FALSE);
	}

	XPropertyGrid* pValue3=new XPropertyGrid(_C(_T("884"),_T("键值")),(_variant_t)szValue3,
											 _C(_T("885"),_T("键盘键值")),ID_VALUE3);
	if(NULL!=pValue3)
	{
		pHotKey3->AddSubItem(pValue3);

		pValue3->SetNode(this);
		pValue3->SetSeat(NULL);
		pValue3->AddOption(_C(_T("307"),_T("双击")));
		CString szValue=(_variant_t)pFunction3->GetValue();

		for(auto& key:MapKeyValue)
		{
			CString szKey=key.first;
			pValue3->AddOption(szKey);
		}

		pValue3->AllowEdit(FALSE);
	}

	XPropertyGrid* pEnable3=new XPropertyGrid(_C(_T("886"),_T("启用")),(_variant_t)szEnable3,
											  _C(_T("887"),_T("是否开启快捷键")),ID_ENABLE3);
	if(NULL!=pEnable3)
	{
		pHotKey3->AddSubItem(pEnable3);
		pEnable3->SetNode(this);
		pEnable3->SetSeat(NULL);
		pEnable3->AddOption(_C(_T("888"),_T("开启")));
		pEnable3->AddOption(_C(_T("889"),_T("关闭")));
		pEnable3->AllowEdit(FALSE);
	}
	//////////////////////////////////////////////////////////////////////////
	//出厂设置
	CString szRecover;
	if(szEnable1==_C(_T("889"),_T("关闭"))&&
		(szFunction2==_T("Ctrl")&&szValue2==_C(_T("307"),_T("双击")))&&
	   (szFunction3==_T("Shift")&&szValue3==_C(_T("307"),_T("双击"))))
	{
		szRecover=_C(_T("894"),_T("是"));
	}
	else
	{
		szRecover=_C(_T("895"),_T("否"));
	}

	XPropertyGrid* pRecover=new XPropertyGrid(_C(_T("890"),_T("出厂设置")),szRecover,
												 _C(_T("891"),_T("设置为出厂设置")),ID_RECOVER);
	if(NULL!=pRecover)
	{
		pGroup8->AddSubItem(pRecover);
		pRecover->SetNode(this);
		pRecover->SetSeat(NULL);
		pRecover->AddOption(_C(_T("894"),_T("是")));
		pRecover->AddOption(_C(_T("895"),_T("否")));
		pRecover->AllowEdit(FALSE);
	}

	XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().AddProperty(pGroup8);
}

//////////////////////////////////////////////////////////////////////////
XUserLogStatus* XNode::GetUserLoginStatusByNodeID(MAP_USERLOGINSTATUS& MapUserLogin,int nNodeID)
{
	for(auto iter=MapUserLogin.begin();iter!=MapUserLogin.end();++iter)
	{
		XUserLogStatus* pUser=iter->second;
		if(nNodeID==pUser->GetNodeID())
		{
			return pUser;
		}
	}

	return NULL;
}

void XNode::ParseVecValue()
{
	ClearMapHotKey();

	//解析获取数组
	if(m_VecHotKey.size()!=8)
		return;

	for(int i=0;i<8;i++)
	{
		unsigned short nValue=m_VecHotKey[i];
		if(((nValue>>8)&0xFF)==0x82)
		{
			//登录
			XKeyValue* pKeyValue=new XKeyValue;
			pKeyValue->m_KeyValue1=m_VecHotKey[i];
			pKeyValue->m_KeyValue2=m_VecHotKey[i+1];

			m_MapHotKey.insert(std::pair<int,XKeyValue*>(1,pKeyValue));
		}
		else if(((nValue>>8)&0xFF)==0x83)
		{
			//接管
			XKeyValue* pKeyValue=new XKeyValue;
			pKeyValue->m_KeyValue1=m_VecHotKey[i];
			pKeyValue->m_KeyValue2=m_VecHotKey[i+1];

			m_MapHotKey.insert(std::pair<int,XKeyValue*>(2,pKeyValue));
		}
		else if(((nValue>>8)&0xFF)==0x84)
		{
			//推送
			XKeyValue* pKeyValue=new XKeyValue;
			pKeyValue->m_KeyValue1=m_VecHotKey[i];
			pKeyValue->m_KeyValue2=m_VecHotKey[i+1];

			m_MapHotKey.insert(std::pair<int,XKeyValue*>(3,pKeyValue));
		}
	}
}

void XNode::ParseHotKey(int nIndex,CString& szFunction,CString& szValue,CString& szEnable)
{
	if(m_MapHotKey.find(nIndex)!=m_MapHotKey.end())
	{
		XKeyValue* pKey=m_MapHotKey[nIndex];
		unsigned short nValue1=pKey->m_KeyValue1;
		unsigned short nValue2=pKey->m_KeyValue2;

		int nTemp=nValue1&0x03;
		if(nTemp==1)
		{
			szValue=_C(_T("307"),_T("双击"));
			szEnable=_C(_T("888"),_T("开启"));
		}
		else if(nTemp==2)
		{
			int nKeyValue=nValue2&0xFF;
			szValue=GetKeyByValue(nKeyValue);
			szEnable=_C(_T("888"),_T("开启"));
		}
		else if(nTemp==0)
		{
			szEnable=_C(_T("889"),_T("关闭"));
		}

		if(((nValue2>>8)&0xFF)==1)
		{
			szFunction=_T("Ctrl");
		}
		else if(((nValue2>>8)&0xFF)==2)
		{
			szFunction=_T("Shift");
		}
		else if(((nValue2>>8)&0xFF)==4)
		{
			szFunction=_T("Alt");
		}
		else if(((nValue2>>8)&0xFF)==8)
		{
			szFunction=_T("Win");
		}
	}
}

CString XNode::GetKeyByValue(int nValue)
{
	MAP_KEYVALUE& KeyValue=m_pNodeManage->GetMapKeyValue();
	for(auto& key:KeyValue)
	{
		int nKeyValue=key.second;
		if(nKeyValue==nValue)
		{
			return key.first;
		}
	}
	return _T("");
}

void XNode::WriteHotKey(int nIndex,CString szFunction,CString szValue,CString szEnable)
{
	unsigned short nValue1=0;
	unsigned short nValue2=0;

	if(szEnable==_C(_T("888"),_T("开启")))
	{
		MAP_KEYVALUE& KeyValue=m_pNodeManage->GetMapKeyValue();
		if(KeyValue.find(szValue)!=KeyValue.end())
		{
			//组合
			nValue1|=0x02;

			unsigned short nValue=KeyValue[szValue];
			nValue2|=nValue;
		}
		else
		{
			//双击
			nValue1|=0x01;
		}
	}
	else if(szEnable==_C(_T("889"),_T("关闭")))
	{
		nValue1|=0x00;
	}

	//菜单
	if(nIndex==1)
	{
		nValue1|=(0x82<<8);
	}
	else if(nIndex==2)
	{
		nValue1|=(0x83<<8);
	}
	else if(nIndex==3)
	{
		nValue1|=(0x84<<8);
	}
	
	//功能键
	if(szFunction==_T("Ctrl"))
	{
		nValue2|=(0x01<<8);
	}
	else if(szFunction==_T("Shift"))
	{
		nValue2|=(0x02<<8);
	}
	else if(szFunction==_T("Alt"))
	{
		nValue2|=(0x04<<8);
	}
	else if(szFunction==_T("Win"))
	{
		nValue2|=(0x08<<8);
	}

	if(m_MapHotKey.find(nIndex)!=m_MapHotKey.end())
	{
		XKeyValue* pKey=m_MapHotKey[nIndex];
		pKey->m_KeyValue1=nValue1;
		pKey->m_KeyValue2=nValue2;
	}
}



