#include "stdafx.h"
#include "XJsonManage.h"
#include "XConstant.h"
#include "json.h"
#include "XLoginInfo.h"
#include "XResult.h"
#include "XPower.h"
#include "XSubUserInfo.h"
#include "XStoreListInfo.h"
#include "HandleCalculate.h"
#include "XDevicePara.h"
#include "XNodeConnect.h"
#include "XNodeManage.h"
#include "XNode.h"
#include "XUserLogStatus.h"
#include "XNodeLogin.h"
#include "XUpdateUserInfo.h"
#include "XTakeOver.h"
#include "XAlterNodeName.h"
#include "XOSDImage.h"
#include "XMatrix.h"
#include "XNodeGroupInfo.h"
#include "XNodeGroup.h"
#include "XNodeInfo.h"
#include "XNodeAll.h"
#include "XUserManage.h"
#include "XSystemStatus.h"
#include "XConstantData.h"
#include "XStoreList.h"
#include "XNetConfig.h"
#include "XLogPack.h"
#include "XLogInfo.h"
#include "XNodeStatus.h"
#include "XKeyValue.h"
#include "XFolderResult.h"
#include "XFolderInfo.h"
#include "XSplitResult.h"
#include "XSplitManage.h"
#include "XSplitWindow.h"
#include "XSignal.h"
#include "XSplitSceneResult.h"
#include "XSplitScene.h"
#include "XInternalManage.h"



XJsonManage* XJsonManage::m_pJsomManage=NULL;

XJsonManage::XJsonManage()
{

}

XJsonManage::~XJsonManage()
{

}

XJsonManage* XJsonManage::GetInstance()
{
	if(NULL==m_pJsomManage)
	{
		m_pJsomManage=new XJsonManage;
		return m_pJsomManage;
	}
	return m_pJsomManage;
}

void XJsonManage::Relase()
{
	RELEASE(m_pJsomManage);
}

void XJsonManage::ParseJsonToLogin(const char* pData,XLoginInfo& userInfo)
{
	Json::Reader reader;  
	Json::Value root;  
	if(reader.parse(pData,root)) 
	{  
		std::string UserName=root["user"].asCString();
		CString szUserName(UserName.c_str());

		std::string PassWd=root["key"].asCString();
		CString szPassWd(PassWd.c_str());

		int nID=root["ID"].asInt();
		int nResult=root["result"].asInt();
		
		userInfo.SetUserName(szUserName);
		userInfo.SetPassWd(szPassWd);
		userInfo.SetUserID(nID);
		userInfo.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToLoginOut(const char* pData,XResult& result)
{
	Json::Reader reader;  
	Json::Value root;  
	if(reader.parse(pData,root)) 
	{  
		int nResult=root["result"].asInt();
		result.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToPower(const char* pData,XUserManage* pManage,XUpdateUserInfo& updateUserInfo)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		updateUserInfo.SetResult(nResult);
		
		CString szType(root["utype"].asString().c_str());
		updateUserInfo.SetType(szType);

		CString szUserType(root["user type"].asString().c_str());
		updateUserInfo.SetUserType(szUserType);
		
		if(szType==_T("LIST"))
		{
			if(nResult==0)
			{
				VEC_USERALL& VecUserAll=pManage->GetVecUserAll();
				VecUserAll.clear();

				const Json::Value array=root["ID BitMap"];
				if(!array.isNull())
				{
					for(unsigned int i=0;i<array.size();++i)
					{
						int nValue=array[i].asInt();
						VecUserAll.push_back(nValue);
					}
				}
			}
		}
		else if(szType==POWER_REDATA_QUERY)
		{
			if(nResult==0)
			{
				CString szUserName(root["user"].asString().c_str());
				updateUserInfo.SetUserName(szUserName);
				int nID=root["ID"].asInt();
				updateUserInfo.SetUserID(nID);

				//TRACE(_T("AddUserQuery=%s\n"),szUserName);
				//TRACE(_T("AddUserIDQuery=%d\n"),nID);

				XPower* pPower=NULL;
				MAP_POWER& MapPower=pManage->GetMapPower();
				MAP_POWER::iterator iter=MapPower.find(szUserName);
				if(iter!=MapPower.end())
				{
					pPower=iter->second;
				}
				else
				{
					pPower=new XPower;
					MapPower.insert(std::pair<CString,XPower*>(szUserName,pPower));
				}
				//////////////////////////////////////////////////////////////////////////
				CString szType(root["utype"].asString().c_str());
				pPower->SetType(szType);

				pPower->SetUserID(nID);
				pPower->SetUserName(szUserName);

				CString szPassWd(root["key"].asString().c_str());
				pPower->SetPassWd(szPassWd);

				int nCreateID=root["creator ID"].asInt();
				pPower->SetCreateID(nCreateID);

				time_t lCreateTime=root["create time"].asUInt();
				pPower->SetCreateTime(lCreateTime);

				CString szUserGroup(root["user group"].asString().c_str());
				pPower->SetUserGroup(szUserGroup);

				int nLevel=root["level"].asInt();
				pPower->SetLevel(nLevel);

				int nManagePermission=root["manage permission"].asInt();
				pPower->SetManagePermission(nManagePermission);
				//////////////////////////////////////////////////////////////////////////
				int nViewType=root["privilege view"]["type"].asInt();
				pPower->GetPrivilegeView().SetType(nViewType);
				pPower->GetPrivilegeView().GetVecPrivilege().clear();
				const Json::Value arrayView=root["privilege view"]["privilege"];
				if(!arrayView.isNull())
				{
					for(unsigned int i=0;i<arrayView.size();++i)
					{
						int n=arrayView[i].asInt();
						pPower->GetPrivilegeView().GetVecPrivilege().push_back(n);
					}
				}

				int nCtrlType=root["privilege ctrl"]["type"].asInt();
				pPower->GetPrivilegeCtrl().SetType(nCtrlType);
				pPower->GetPrivilegeCtrl().GetVecPrivilege().clear();
				const Json::Value arrayCtrl=root["privilege ctrl"]["privilege"];
				if(!arrayCtrl.isNull())
				{
					for(unsigned int i=0;i<arrayCtrl.size();++i)
					{
						int n=arrayCtrl[i].asInt();
						pPower->GetPrivilegeCtrl().GetVecPrivilege().push_back(n);
					}
				}

				int nLoginType=root["privilege login"]["type"].asInt();
				pPower->GetPrivilegeLogin().SetType(nLoginType);
				pPower->GetPrivilegeLogin().GetVecPrivilege().clear();
				const Json::Value arrayLogin=root["privilege login"]["privilege"];
				if(!arrayLogin.isNull())
				{
					for(unsigned int i=0;i<arrayLogin.size();++i)
					{
						int n=arrayLogin[i].asInt();
						pPower->GetPrivilegeLogin().GetVecPrivilege().push_back(n);
					}
				}
				//////////////////////////////////////////////////////////////////////////
			}
		}
		else if(szType==POWER_REDATA_ADD)
		{
			TRACE(_T("nResult=%d\n"),nResult);

			if(nResult==101)
			{
				CString szUserName(root["user"].asString().c_str());
				updateUserInfo.SetUserName(szUserName);

				int nID=root["ID"].asInt();
				updateUserInfo.SetUserID(nID);

				MAP_SUBUSER& MapSubUser=pManage->GetMapSubUser();
				MAP_SUBUSER::iterator iter=MapSubUser.find(szUserName);
				if(iter==MapSubUser.end())
				{
					XSubUserInfo* pInfo=new XSubUserInfo;
					pInfo->SetID(nID);
					pInfo->SetUserName(szUserName);

					MapSubUser.insert(std::pair<CString,XSubUserInfo*>(szUserName,pInfo));
				}
			}
		}
		else if(szType==POWER_REDATA_DEL)
		{
			if(nResult==0)
			{
				CString szUserName(root["user"].asString().c_str());
				updateUserInfo.SetUserName(szUserName);
			}
		}
		else if(szType==POWER_REDATA_UPDATE)
		{
			if(nResult==101)
			{
				CString szUserName(root["user"].asString().c_str());
				updateUserInfo.SetUserName(szUserName);
				int nID=root["ID"].asInt();
				updateUserInfo.SetUserID(nID);

				XPower* pPower=NULL;
				MAP_POWER& MapPower=pManage->GetMapPower();
				MAP_POWER::iterator iter=MapPower.find(szUserName);
				if(iter!=MapPower.end())
				{
					pPower=iter->second;
				}

				if(!pPower)
					return;

				//////////////////////////////////////////////////////////////////////////
				CString szType(root["utype"].asString().c_str());
				pPower->SetType(szType);

				//pPower->SetUserID(nID);
				pPower->SetUserName(szUserName);

	
				if(root["key"].isString())
				{
					CString szPassWd;(root["key"].asString().c_str());
					pPower->SetPassWd(szPassWd);
				}

				//没有发的 也不会，所以不要再获取
				//pPower->SetPassWd(szPassWd);
				
				//int nCreateID=root["creator ID"].asInt();
				//pPower->SetCreateID(nCreateID);

				//time_t lCreateTime=root["create time"].asUInt();
				//pPower->SetCreateTime(lCreateTime);

				//CString szUserGroup(root["user group"].asString().c_str());
				//pPower->SetUserGroup(szUserGroup);

				//int nLevel=root["level"].asInt();
				//pPower->SetLevel(nLevel);

				int nManagePermission=root["manage permission"].asInt();
				pPower->SetManagePermission(nManagePermission);

				//TRACE(_T("nPermission RE=%d\n"),nManagePermission);
				//////////////////////////////////////////////////////////////////////////
				int nViewType=root["privilege view"]["type"].asInt();
				pPower->GetPrivilegeView().SetType(nViewType);
				pPower->GetPrivilegeView().GetVecPrivilege().clear();
				const Json::Value arrayView=root["privilege view"]["privilege"];
				if(!arrayView.isNull())
				{
					for(unsigned int i=0;i<arrayView.size();++i)
					{
						int n=arrayView[i].asInt();
						pPower->GetPrivilegeView().GetVecPrivilege().push_back(n);
					}
				}

				int nCtrlType=root["privilege ctrl"]["type"].asInt();
				pPower->GetPrivilegeCtrl().SetType(nCtrlType);
				pPower->GetPrivilegeCtrl().GetVecPrivilege().clear();
				const Json::Value arrayCtrl=root["privilege ctrl"]["privilege"];
				if(!arrayCtrl.isNull())
				{
					for(unsigned int i=0;i<arrayCtrl.size();++i)
					{
						int n=arrayCtrl[i].asInt();
						pPower->GetPrivilegeCtrl().GetVecPrivilege().push_back(n);
					}
				}

				int nLoginType=root["privilege login"]["type"].asInt();
				pPower->GetPrivilegeLogin().SetType(nLoginType);
				pPower->GetPrivilegeLogin().GetVecPrivilege().clear();
				const Json::Value arrayLogin=root["privilege login"]["privilege"];
				if(!arrayLogin.isNull())
				{
					for(unsigned int i=0;i<arrayLogin.size();++i)
					{
						int n=arrayLogin[i].asInt();
						pPower->GetPrivilegeLogin().GetVecPrivilege().push_back(n);
					}
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToUserList(const char* pData,MAP_SUBUSER& MapSubUser)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root))
	{	
		//if(root["user create list"].isArray())
		{
			const Json::Value array=root["user create list"];
			Json::Value::Members members=array.getMemberNames();// 获取所有key的值
			for (Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();iterMember++)   // 遍历每个key
			{
				std::string strKey=*iterMember; 

				//根据strKey获取ID
				CString szKey(strKey.c_str());
				int nID=HandleCalculate::GetIDByJsonKey(szKey);

				if(array[strKey.c_str()].isString()) 
				{
					std::string userName=array[strKey.c_str()].asString();  
					CString szUserName(userName.c_str());

					XSubUserInfo* pSubUser=new XSubUserInfo;
					pSubUser->SetUserName(szUserName);
					pSubUser->SetID(nID);

					MAP_SUBUSER::iterator iter=MapSubUser.find(szUserName);
					if(iter!=MapSubUser.end())
					{
						iter->second=pSubUser;
					}
					else
					{
						MapSubUser.insert(std::pair<CString,XSubUserInfo*>(szUserName,pSubUser));
					}
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToStoreList(const char* pData,MAP_STORE& MapStore,XStoreList& storeList)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root))
	{	
		CString szType(root["utype"].asString().c_str());
		int nResult=root["result"].asInt();
		int nUserID=root["ID"].asInt();

		storeList.SetResult(nResult);
		storeList.SetSendType(szType);
		storeList.SetUserID(nUserID);

		if(szType==_T("QUERY"))
		{
			if(nResult==0)
			{
				//先清除MAP
				for(auto& map:MapStore)
				{
					delete map.second;
				}
				MapStore.clear();

				const Json::Value arrayin=root["fav_list"]["favorite_in"];
				Json::Value::Members members=arrayin.getMemberNames();
				for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();iterMember++)
				{
					std::string strKey=*iterMember;
					//根据strKey获取ID
					CString szKey(strKey.c_str());
					int nID=HandleCalculate::GetIDByJsonKey(szKey);

					//TRACE(_T("nID In=%d\n"),nID);
					//ID小于1000
					//if(nID<1000)
					{
						if(arrayin!=NULL)
						{
							int nNO=0;
							if(arrayin[strKey]["no"].isInt())
							{
								nNO=arrayin[strKey]["no"].asInt();
							}
							CString szNodeName;
							if(arrayin[strKey]["name"].isString())
							{
								CString szTempNodeName(arrayin[strKey]["name"].asString().c_str());
								szNodeName=szTempNodeName;
							}

							XStoreListInfo* pStoreList=NULL;
							MAP_STORE::iterator iter=MapStore.find(nID);
							if(iter!=MapStore.end())
							{
								pStoreList=iter->second;
							}
							else
							{
								pStoreList=new XStoreListInfo;
								MapStore.insert(std::pair<int,XStoreListInfo*>(nID,pStoreList));
							}

							pStoreList->SetNumber(nNO);
							pStoreList->SetNodeID(nID);
							pStoreList->SetNodeName(szNodeName);
							pStoreList->SetUserID(nUserID);
							pStoreList->SetNodeType(NODETYPE_IN);
						}
					}
				}
				//////////////////////////////////////////////////////////////////////////
				const Json::Value arrayout=root["fav_list"]["favorite_out"];
				Json::Value::Members member=arrayout.getMemberNames();
				for(Json::Value::Members::iterator iterMember=member.begin();iterMember!=member.end();iterMember++)
				{
					std::string strKey=*iterMember;

					CString szKey(strKey.c_str());
					int nID=HandleCalculate::GetIDByJsonKey(szKey);

					//TRACE(_T("nID out=%d\n"),nID);

					//ID小于1000
					//if(nID<1000)
					{
						if(arrayout!=NULL)
						{
							int nNO=0;
							if(arrayout[strKey]["no"].isInt())
							{
								nNO=arrayout[strKey]["no"].asInt();
							}

							CString szNodeName;
							if(arrayout[strKey]["name"].isString())
							{
								CString szTempNodeName(arrayout[strKey]["name"].asString().c_str());
								szNodeName=szTempNodeName;
							}

							XStoreListInfo* pStoreList=NULL;
							MAP_STORE::iterator iter=MapStore.find(nID);
							if(iter!=MapStore.end())
							{
								pStoreList=iter->second;
							}
							else
							{
								pStoreList=new XStoreListInfo;
								MapStore.insert(std::pair<int,XStoreListInfo*>(nID,pStoreList));
							}

							pStoreList->SetNumber(nNO);
							pStoreList->SetNodeID(nID);
							pStoreList->SetNodeName(szNodeName);
							pStoreList->SetUserID(nUserID);
							pStoreList->SetNodeType(NODETYPE_OUT);
						}
					}
				}
			}
		}
		else if(szType==_T("ADD"))
		{
			if(nResult==0)
			{
				int nID=root["term NO"].asInt();
				int nType=root["type"].asInt();
				int nNO=root["no"].asInt();
				CString szName(root["name"].asString().c_str());

				storeList.SetNodeID(nID);

				auto iter=MapStore.find(nID);
				if(iter==MapStore.end())
				{
					XStoreListInfo* pStoreList=new XStoreListInfo;

					pStoreList->SetNumber(nNO);
					pStoreList->SetNodeID(nID);
					pStoreList->SetUserID(nUserID);
					pStoreList->SetNodeName(szName);
					if(nType==0)
						pStoreList->SetNodeType(NODETYPE_IN);
					else
						pStoreList->SetNodeType(NODETYPE_OUT);

					MapStore.insert(std::pair<int,XStoreListInfo*>(nID,pStoreList));		
				}
			}
		}
		else if(szType==_T("UPDATE"))
		{

		}
		else if(szType==_T("DEL"))
		{
			if(nResult==0)
			{
				int nNodeID=root["term NO"].asInt();
				storeList.SetNodeID(nUserID);
			}
		}
	}
}

void XJsonManage::ParseJsonToReDeviceInfo(const char* pData,XDevicePara& devicePara)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{  
		int nChannel=root["get"]["hardware channel"].asInt();
		std::string matrixModel=root["get"]["matrix model"].asString();  
		CString szMatrixModel(matrixModel.c_str());

		CString szFPGAVer(root["get"]["fpga_version"].asString().c_str());
		//TRACE(_T("fpgaVer=%s\n"),szFPGAVer);
		int nResult=root["result"].asInt();

		devicePara.SetHardWareChannel(nChannel);
		devicePara.SetMatrixModel(szMatrixModel);
		devicePara.SetFPGAVer(szFPGAVer);
		devicePara.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToReNodeByChannel(const char* pData,XNodeConnect& nodeConnect)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{  
		int nMaxItem=root["get"]["max item"].asInt();

		const Json::Value array=root["get"]["channel connect"];
		if(!array.isNull())
		{
			for(unsigned int i=0;i<array.size();++i)
			{
				int n=array[i].asInt();
				nodeConnect.GetVecConnect().push_back(n);
			}
		}

		int nResult=root["result"].asInt();
		nodeConnect.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToReNodeInfo(const char* pData,MAP_NODE& MapNode)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		if(nResult==0)
		{
			const Json::Value array=root["query result"];
			Json::Value::Members members=array.getMemberNames();
			for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
			{
				std::string strKey=*iterMember; 


				CString szKey(strKey.c_str());
				int nChannel=HandleCalculate::GetIDByJsonKey(szKey);
				//////////////////////////////////////////////////////////////////////////
				int nNodeID=array[strKey]["term NO"].asInt();
				int nNodeType=array[strKey]["term type"].asInt();
				int time=array[strKey]["connect time"].asInt();
				int nMainCh=array[strKey]["main ch"].asInt();

				if(nNodeID!=0)
				{
					//是否要清空（注意）
					//每次只来一个 不能在这里清空
					MAP_NODE::iterator iter=MapNode.find(nNodeID);
					if(iter!=MapNode.end())
					{
						XNode* pNode=iter->second;
						pNode->SetChannel(nChannel);
						pNode->SetNodeID(nNodeID);
						pNode->SetNodeType(nNodeType);
						pNode->SetConnectTime(time);
						pNode->SetMainCh(nMainCh);
					}
					else
					{
						XNode* pNode=new XNode;
						pNode->SetChannel(nChannel);
						pNode->SetNodeID(nNodeID);
						pNode->SetNodeType(nNodeType);
						pNode->SetConnectTime(time);
						pNode->SetMainCh(nMainCh);

						MapNode.insert(std::pair<int,XNode*>(nNodeID,pNode));
					}
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReNodeDetailInfo(const char* pData,XNodeManage* pManage,XNodeInfo& nodeInfo)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		CString szProtocolType(root["utype"].asString().c_str());
		int nResult=root["result"].asInt();
		int nNodeID=root["term NO"].asInt();
		int nMark=root["update mark"].asInt();
		CString szQueryType(root["query type"].asString().c_str());

		nodeInfo.SetResult(nResult);
		nodeInfo.SetNodeID(nNodeID);
		nodeInfo.SetSendType(szProtocolType);
		nodeInfo.SetUpdateMark(nMark);
		nodeInfo.SetQueryType(szQueryType);

		if(szProtocolType==_T("LIST"))
		{
			//数据库节点总数
			if(nResult==0)
			{
				VEC_NODELIST& VecNodeList=pManage->GetVecNodeList();
				VecNodeList.clear();
				const Json::Value array=root["ID BitMap"];
				if(!array.isNull())
				{
					for(unsigned int i=0;i<array.size();++i)
					{
						int nValue=array[i].asInt();
						VecNodeList.push_back(nValue);
					}
				}
			}
		}
		else if(szProtocolType==_T("QUERY"))
		{
			if(nResult==0)
			{
				if(szQueryType==_T("NODEONLINE"))
				{
					MAP_NODE& MapNode=pManage->GetMapNode();
					MAP_NODE::iterator iter=MapNode.find(nNodeID);
					if(iter!=MapNode.end())
					{
						XNode* pNode=iter->second;
						pNode->SetNodeID(nNodeID);

						CString szRealID(root["term ID"].asString().c_str());
						pNode->SetRealID(szRealID);		

						CString szNodeName(root["name"].asString().c_str());
						pNode->SetNodeName(szNodeName);

						time_t tCreateTime=root["create time"].asUInt();
						pNode->SetCreateTime(tCreateTime);

						int nType=root["type"].asInt();
						pNode->SetNodeType(nType);

						int nGroup=root["group"].asInt();
						pNode->SetGroup(nGroup);

						int nMaster=root["master"].asInt();
						pNode->SetMaster(nMaster);

						int nControl=root["control"].asInt();
						pNode->SetControl(nControl);
					}
				}
				else if(szQueryType==_T("NODEALL"))
				{
					XNodeAll* pNodeAll=NULL;
					MAP_NODEALL& MapNodeAll=pManage->GetMapNodeAll();
					if(MapNodeAll.find(nNodeID)==MapNodeAll.end())
					{
						pNodeAll=new XNodeAll;
						MapNodeAll.insert(std::pair<int,XNodeAll*>(nNodeID,pNodeAll));
					}
					else
					{
						pNodeAll=MapNodeAll[nNodeID];
					}

					pNodeAll->SetNodeID(nNodeID);

					CString szRealID(root["term ID"].asString().c_str());
					pNodeAll->SetRealID(szRealID);		

					CString szNodeName(root["name"].asString().c_str());
					pNodeAll->SetNodeName(szNodeName);

					time_t tCreateTime=root["create time"].asUInt();
					pNodeAll->SetCreateTime(tCreateTime);

					int nType=root["type"].asInt();
					pNodeAll->SetNodeType(nType);

					int nGroup=root["group"].asInt();
					pNodeAll->SetGroup(nGroup);

					int nMaster=root["master"].asInt();
					pNodeAll->SetMaster(nMaster);

					int nControl=root["control"].asInt();
					pNodeAll->SetControl(nControl);
				}
			}
		}
		else if(szProtocolType==_T("UPDATE"))
		{
			if(nResult==101)
			{
				switch(nMark)
				{
				case UPDATAMAKE_MASTER:
					{
						MAP_NODE& MapNode=pManage->GetMapNode();
						MAP_NODE::iterator iter=MapNode.find(nNodeID);
						if(iter!=MapNode.end())
						{
							XNode* pNode=iter->second;

							pNode->SetNodeID(nNodeID);
							int nMaster=root["master"].asInt();
							pNode->SetMaster(nMaster);
							nodeInfo.SetNodeMaster(nMaster);
						}
					}
					break;
				case UPDATAMAKE_GROUP:
					{
						MAP_NODE& MapNode=pManage->GetMapNode();
						MAP_NODE::iterator iter=MapNode.find(nNodeID);
						if(iter!=MapNode.end())
						{
							XNode* pNode=iter->second;

							pNode->SetNodeID(nNodeID);
							int nGroup=root["group"].asInt();
							pNode->SetGroup(nGroup);
							nodeInfo.SetNodeGroup(nGroup);
						}
					}
					break;
				default:
					break;
				}
			}
		}
		else if(szProtocolType==_T("ADD"))
		{

		}
		else if(szProtocolType==_T("DEL"))
		{

		}
	}
}

void XJsonManage::ParseJsonToReNodeStatus(const char* pData,MAP_NODE& MapNode,XNodeStatus& result)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		CString szFlag(root["flag"].asString().c_str());
		CString szSubType(root["sub type"].asString().c_str());

		result.SetResult(nResult);
		result.SetSendType(szFlag);
		result.SetSubSendType(szSubType);

		if(nResult!=0)
			return;


		if(szFlag==_T("BLINK"))
		{
			//节点灯闪烁
		}
		else if(szFlag==_T("NODEALL")||szFlag==_T("TAKEOVER")||szFlag==_T("ALTER"))
		{
			const Json::Value arrayRoot=root;
			Json::Value::Members membersRoot=arrayRoot.getMemberNames();
			for(Json::Value::Members::iterator iterMember=membersRoot.begin();iterMember!=membersRoot.end();++iterMember)
			{
				std::string strKey=*iterMember;
				CString szKey(strKey.c_str());
				if(szKey==_T("result"))
					continue;

				if(szKey==_T("term_status"))
				{
					const Json::Value array=root["term_status"];
					Json::Value::Members members=array.getMemberNames();
					for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
					{
						std::string strKey=*iterMember;
						CString szKey(strKey.c_str());
						int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);

						MAP_NODE::iterator iter=MapNode.find(nNodeID);
						if(iter!=MapNode.end())
						{
							XNode* pNode=iter->second;

							CString szNodeRealID(array[strKey]["term ID"].asString().c_str());
							pNode->SetRealID(szNodeRealID);

							int nChannel=array[strKey]["ch"].asInt();
							pNode->SetChannel(nChannel);

							int nType=array[strKey]["type"].asInt();
							pNode->SetNodeType(nType);

							switch(nType)
							{
								case TERM_IN:
									{
										int nInStatus=array[strKey]["in sta"].asInt();
										pNode->SetNodeInStatus(nInStatus);

										BOOL bSignal=array[strKey]["signal"].asBool();
										pNode->SetIsSignal(bSignal);

										int nResoluationH=array[strKey]["in resX"].asInt();
										pNode->SetInResolusationH(nResoluationH);

										int nResoluationV=array[strKey]["in resY"].asInt();
										pNode->SetInResolusationV(nResoluationV);

										int nAudioModel=array[strKey]["audio mode"].asInt();
										pNode->SetAudioModel(nAudioModel);

										int nHidModel=array[strKey]["hid mode"].asInt();
										pNode->SetHidModel(nHidModel);

										int nScreenModel=array[strKey]["screen mode"].asInt();
										pNode->SetSplitScreen(nScreenModel);

										CString szSoftVer(array[strKey]["soft ver"].asString().c_str());
										pNode->SetSoftVer(szSoftVer);

										CString szHardVer(array[strKey]["hard ver"].asString().c_str());
										pNode->SetHardVer(szHardVer);

										int nAudioSrc=array[strKey]["audio src"].asInt();
										pNode->SetAudioSrc(nAudioSrc);
									}
									break;
								case TERM_OUT:
									{
										int nOutStatus=array[strKey]["out sta"].asInt();
										pNode->SetOutStatus(nOutStatus);

										int nOutResulationIndex=array[strKey]["out resV"].asInt();
										pNode->SetOutResoluationIndex(nOutResulationIndex);

										int nOutModel=array[strKey]["out mode"].asInt();
										pNode->SetOutModel(nOutModel);

										int nTakeOverID=array[strKey]["video input"].asInt();
										pNode->SetPreviewNodeID(nTakeOverID);

										int nLoginUserID=array[strKey]["reg user"].asInt();
										pNode->SetLoginUserID(nLoginUserID);

										int nCtrlUserID=array[strKey]["ctrl term"].asInt();
										pNode->SetTakeOverNodeID(nCtrlUserID);

										int nBindCfg=array[strKey]["bind cfg"].asInt();
										pNode->SetBindCfg(nBindCfg);

										int nBindNodeID=array[strKey]["bind term"].asInt();
										pNode->SetBindNodeID(nBindNodeID);

										CString szOutSoftVer(array[strKey]["soft ver"].asString().c_str());
										pNode->SetOutSoftVer(szOutSoftVer);

										CString szOutHardVer(array[strKey]["hard ver"].asString().c_str());
										pNode->SetOutHardVer(szOutHardVer);

										//热键
										const Json::Value arrayKey=array[strKey]["osd ctrl key cfg"];						
										if(array[strKey]["osd ctrl key cfg"].isArray())
										{
											pNode->GetVecHotKey().clear();
											int nSize=arrayKey.size();

											for(unsigned int i=0;i<arrayKey.size();++i)
											{
												if(arrayKey[i].isInt())
												{
													int nValue=arrayKey[i].asInt();
													pNode->GetVecHotKey().push_back(nValue);
												}
											}
										}
									}
									break;
								default:
									break;
							}
						}
					}
				}
				else if(szKey==_T("cfg term"))
				{
					if(szSubType==_T("AUDIO_MODEL"))
					{
						const Json::Value array=root["cfg term"];
						Json::Value::Members members=array.getMemberNames();
						for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
						{
							std::string strKey=*iterMember;
							CString szKey(strKey.c_str());
							int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);
							int nAudioModel=array[strKey]["audio mode"].asInt();

							MAP_NODE::iterator iter=MapNode.find(nNodeID);
							if(iter!=MapNode.end())
							{
								XNode* pNode=iter->second;
								pNode->SetAudioModel(nAudioModel);
							}
						}
					}
					else if(szSubType==_T("HID_MODEL"))
					{
						const Json::Value array=root["cfg term"];
						Json::Value::Members members=array.getMemberNames();
						for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
						{
							std::string strKey=*iterMember;
							CString szKey(strKey.c_str());
							int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);
							int nHidModel=array[strKey]["hid mode"].asInt();

							result.SetHidModel(nHidModel);

							MAP_NODE::iterator iter=MapNode.find(nNodeID);
							if(iter!=MapNode.end())
							{
								XNode* pNode=iter->second;
								pNode->SetHidModel(nHidModel);
							}
						}
					}
					else if(szSubType==_T("SCREEN_MODEL"))
					{
						const Json::Value array=root["cfg term"];
						Json::Value::Members members=array.getMemberNames();
						for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
						{
							std::string strKey=*iterMember;
							CString szKey(strKey.c_str());
							int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);
							int nScreenModel=array[strKey]["screen mode"].asInt();

							MAP_NODE::iterator iter=MapNode.find(nNodeID);
							if(iter!=MapNode.end())
							{
								XNode* pNode=iter->second;
								pNode->SetSplitScreen(nScreenModel);
							}
						}
					}
					else if(szSubType==_T("RESOLUATION"))
					{
						const Json::Value array=root["cfg term"];
						Json::Value::Members members=array.getMemberNames();
						for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
						{
							std::string strKey=*iterMember;
							CString szKey(strKey.c_str());
							int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);
							int nOutResulationIndex=array[strKey]["out resV"].asInt();

							MAP_NODE::iterator iter=MapNode.find(nNodeID);
							if(iter!=MapNode.end())
							{
								XNode* pNode=iter->second;
								pNode->SetOutResoluationIndex(nOutResulationIndex);
							}
						}
					}
					else if(szSubType==_T("OUT_MODEL"))
					{
						const Json::Value array=root["cfg term"];
						Json::Value::Members members=array.getMemberNames();
						for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
						{
							std::string strKey=*iterMember;
							CString szKey(strKey.c_str());
							int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);
							int nOutModel=array[strKey]["out mode"].asInt();

							MAP_NODE::iterator iter=MapNode.find(nNodeID);
							if(iter!=MapNode.end())
							{
								XNode* pNode=iter->second;
								pNode->SetOutModel(nOutModel);
							}
						}
					}
					else if(szSubType==_T("AUDIO_SRC"))
					{
						const Json::Value array=root["cfg term"];
						Json::Value::Members members=array.getMemberNames();
						for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
						{
							std::string strKey=*iterMember;
							CString szKey(strKey.c_str());
							int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);
							int nAudioSrc=array[strKey]["audio src"].asInt();

							MAP_NODE::iterator iter=MapNode.find(nNodeID);
							if(iter!=MapNode.end())
							{
								XNode* pNode=iter->second;
								pNode->SetAudioSrc(nAudioSrc);
							}
						}

					}
					else if(szSubType==_T("BIND_CFG"))
					{
						{
							//11.11 不知道为啥else if数量多了 格式不对
							const Json::Value array=root["cfg term"];
							Json::Value::Members members=array.getMemberNames();
							for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
							{
								std::string strKey=*iterMember;
								CString szKey(strKey.c_str());
								int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);
								int nBindCfg=array[strKey]["bind cfg"].asInt();

								MAP_NODE::iterator iter=MapNode.find(nNodeID);
								if(iter!=MapNode.end())
								{
									XNode* pNode=iter->second;
									pNode->SetBindCfg(nBindCfg);
								}
							}
						}
					}
					else if(szSubType==_T("BIND_NODEID"))
					{
						{
							const Json::Value array=root["cfg term"];
							Json::Value::Members members=array.getMemberNames();
							for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
							{
								std::string strKey=*iterMember;
								CString szKey(strKey.c_str());
								int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);
								int nBindNodeID=array[strKey]["bind term"].asInt();

								MAP_NODE::iterator iter=MapNode.find(nNodeID);
								if(iter!=MapNode.end())
								{
									XNode* pNode=iter->second;
									pNode->SetBindNodeID(nBindNodeID);
								}
							}
						}
					}
					else if(szSubType==_T("HOTKEY"))
					{
						{
							const Json::Value array=root["cfg term"];
							Json::Value::Members members=array.getMemberNames();
							for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
							{
								std::string strKey=*iterMember;
								CString szKey(strKey.c_str());
								int nNodeID=HandleCalculate::GetIDByJsonKey(szKey);

								const Json::Value arrayKey=array[strKey]["osd ctrl key cfg"];
								if(array[strKey]["osd ctrl key cfg"].isArray())
								{
									MAP_NODE::iterator iter=MapNode.find(nNodeID);
									if(iter!=MapNode.end())
									{
										XNode* pNode=iter->second;
										pNode->GetVecHotKey().clear();
										for(unsigned int i=0;i<arrayKey.size();++i)
										{
											if(arrayKey[i].isInt())
											{
												int nValue=arrayKey[i].asUInt();
												pNode->GetVecHotKey().push_back(nValue);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReLoginUser(const char* pData,MAP_USERLOGINSTATUS& MapLoginUser)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		if(nResult==0)
		{
			const Json::Value array=root["get"]["use log list"];
			if(!array.isNull())
			{
				for(unsigned int i=0;i<array.size();++i)
				{
					int nUserID=array[i].asInt();
					
					MAP_USERLOGINSTATUS::iterator iter=MapLoginUser.find(nUserID);
					if(iter!=MapLoginUser.end())
					{
						XUserLogStatus* pUser=iter->second;
						pUser->SetUserID(nUserID);
					}
					else
					{
						XUserLogStatus* pUser=new XUserLogStatus;
						pUser->SetUserID(nUserID);

						MapLoginUser.insert(std::pair<int,XUserLogStatus*>(nUserID,pUser));
					}
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReLoginUserStatus(const char* pData,MAP_USERLOGINSTATUS& MapLoginUser)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		if(nResult==0)
		{
			//先清除集合中多的元素
			//const Json::Value arrayUserID=root["use log list"];
			//Json::Value::Members members=arrayUserID.getMemberNames();
			//for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
			//{
			//	std::string strKey=*iterMember; 

			//}

			//////////////////////////////////////////////////////////////////////////
			const Json::Value array=root["user_status"];
			Json::Value::Members members=array.getMemberNames();
			for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
			{
				std::string strKey=*iterMember; 

				CString szKey(strKey.c_str());
				int nUserID=HandleCalculate::GetIDByJsonKey(szKey);

				MAP_USERLOGINSTATUS::iterator iter=MapLoginUser.find(nUserID);
				if(iter!=MapLoginUser.end())
				{
					std::string szName=array[strKey]["name"].asString();

					CString szUserName(array[strKey]["name"].asString().c_str());
					int nNetStatus=array[strKey]["net sta"].asInt();
					CString szIP(array[strKey]["ip"].asString().c_str());
					int nPort=array[strKey]["port"].asInt();
					int nNodeStatus=array[strKey]["term sta"].asInt();
					int nNodeID=array[strKey]["term NO"].asInt();

					XUserLogStatus* pUser=iter->second;
					pUser->SetUserName(szUserName);

					if(nNetStatus)
					{
						pUser->SetNetLogin(TRUE);
						pUser->SetIP(szIP);
						pUser->SetPort(nPort);
					}		
					else
					{
						pUser->SetNetLogin(FALSE);
						pUser->SetIP(_T(""));
						pUser->SetPort(0);
					}

					if(nNodeStatus)
					{
						pUser->SetNodeLogin(TRUE);
						pUser->SetNodeID(nNodeID);
					}
					else
					{
						pUser->SetNodeLogin(FALSE);
						pUser->SetNodeID(0);
					}
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReNodeLogin(const char* pData,XNodeLogin& nodeLogin)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		CString szUserName(root["user"].asString().c_str());
		int nNodeID=root["term NO"].asInt();

		nodeLogin.SetResult(nResult);
		nodeLogin.SetUserName(szUserName);
		nodeLogin.SetNodeID(nNodeID);
	}
}

void XJsonManage::ParseJsonToReNodeLogOut(const char* pData,XResult& result)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();


		result.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToReTakeOver(const char* pData,XTakeOver& takeOver)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		int nNodeID=root["term NO"].asInt();
		int nTargetID=root["target term NO"].asInt();
		BOOL bExclusive=root["exclusive"].asBool();

		takeOver.SetNodeID(nNodeID);
		takeOver.SetTargetID(nTargetID);
		takeOver.SetExclusive(bExclusive);

		takeOver.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToReTakeOverCancel(const char* pData,XTakeOver& takeOver)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		int nNodeID=root["term NO"].asInt();

		takeOver.SetNodeID(nNodeID);
		takeOver.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToPreview(const char* pData,XTakeOver& takeOver)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		int nTargetID=root["target term NO"].asInt();
		int nNodeID=root["term NO"].asInt();

		takeOver.SetNodeID(nNodeID);
		takeOver.SetTargetID(nTargetID);
		takeOver.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToAlterNodeName(const char* pData,XAlterNodeName& alterNodeName)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		CString szNodeName(root["term name"].asString().c_str());
		int nNodeID=root["term NO"].asInt();

		alterNodeName.SetNodeID(nNodeID);
		alterNodeName.SetNodeName(szNodeName);
		alterNodeName.SetResult(nResult);
	}
}

void XJsonManage::ParseJsonToReMatrixStatus(const char* pData,MAP_MATRIX& MapMatrix)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		if(nResult==0)
		{
			const Json::Value array=root["get"]["matrix list"];
			if(!array.isNull())
			{
				for(unsigned int i=1;i<=array.size();i++)
				{
					//array从0开始
					int nInChannel=array[i-1].asInt();				
					MAP_MATRIX::iterator iter=MapMatrix.find(i);
					if(iter!=MapMatrix.end())
					{
						iter->second=nInChannel;
					}
					else
					{
						MapMatrix.insert(std::pair<int,int>(i,nInChannel));
					}
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReMatrix(const char* pData,MAP_MATRIX& MapMatrix,XMatrix& matrix)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		matrix.SetResult(nResult);

		CString szMatrixType(root["matrix type"].asString().c_str());
		matrix.SetMatrixType(szMatrixType);

		if(nResult==1)
		{
			const Json::Value array=root["matrix list"];
			Json::Value::Members members=array.getMemberNames();
			for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
			{
				std::string strKey=*iterMember; 
				CString szKey(strKey.c_str());
				int nInChannel=HandleCalculate::GetIDByJsonKey(szKey);

				const Json::Value arrayOut=root["matrix list"][strKey];
				int nSize=arrayOut.size();
				matrix.SetOutputChannel(nSize);

				if(!arrayOut.isNull())
				{
					for(unsigned int i=0;i<arrayOut.size();++i)
					{
						int nOutChannel=arrayOut[i].asInt();
						
						MAP_MATRIX::iterator iter=MapMatrix.find(nOutChannel);
						if(iter!=MapMatrix.end())
						{
							iter->second=nInChannel;
						}
					}
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReOSDImage(const char* pData,XOSDImage& osdImage)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		osdImage.SetResult(nResult);

		int nPicIndex=root["OSD pic"].asInt();
		osdImage.SetPicIndex(nPicIndex);
	}
}

void XJsonManage::ParseJsonToReReadNodeGroup(const char* pData,MAP_NODEGROUP& MapNodeGroup)
{
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		int nOnLine=root["connect"].asInt();
		
		if(nResult==0)
		{
			const Json::Value array=root["term group list"];
			Json::Value::Members members=array.getMemberNames();
			for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
			{
				std::string strKey=*iterMember; 
				CString szKey(strKey.c_str());
				int nGroupID=HandleCalculate::GetIDByJsonKey(szKey);
				CString szGroupName(array[strKey].asString().c_str());

				MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szGroupName);
				if(iter!=MapNodeGroup.end())
				{
					XNodeGroupInfo* pInfo=iter->second;
					pInfo->SetGroupName(szGroupName);
					pInfo->SetGroupID(nGroupID);
					if(nOnLine==1)
						pInfo->SetOnLine(TRUE);
					else if(nOnLine==0)
						pInfo->SetOnLine(FALSE);
				}
				else
				{
					XNodeGroupInfo* pInfo=new XNodeGroupInfo;
					pInfo->SetGroupName(szGroupName);
					pInfo->SetGroupID(nGroupID);
					if(nOnLine==1)
						pInfo->SetOnLine(TRUE);
					else if(nOnLine==0)
						pInfo->SetOnLine(FALSE);

					MapNodeGroup.insert(std::pair<CString,XNodeGroupInfo*>(szGroupName,pInfo));
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReNodeGroupInfo(const char* pData,MAP_NODEGROUP& MapNodeGroup,XNodeGroup& nodeGroup)
{
	//TRACE(_T("ParseJsonToReNodeGroupInfo\n"));
	Json::Reader reader;  
	Json::Value root;  

	if(reader.parse(pData,root)) 
	{
		int nResult=root["result"].asInt();
		CString szSendType(root["utype"].asString().c_str());
		CString szGroupName(root["name"].asString().c_str());
		int nGroupID=root["tgroup ID"].asInt();
		int nMark=root["update mark"].asInt();
		int nCreateMode=root["create mode"].asInt();

		nodeGroup.SetSendType(szSendType);
		nodeGroup.SetResult(nResult);
		nodeGroup.SetGroupName(szGroupName);
		nodeGroup.SetGroupID(nGroupID);
		nodeGroup.SetUpdateMark(nMark);
		nodeGroup.SetCreateMode(nCreateMode);
		
		if(szSendType==_T("QUERY"))
		{
			if(nResult==0)
			{					
				MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szGroupName);
				if(iter!=MapNodeGroup.end())
				{
					XNodeGroupInfo* pInfo=iter->second;

					pInfo->SetGroupName(szGroupName);
					pInfo->SetGroupID(nGroupID);

					int nType=root["type"].asInt();
					pInfo->SetType(nType);

					int nMaster=root["master"].asInt();
					pInfo->SetMaster(nMaster);

					int nCreatorID=root["creator ID"].asInt();
					pInfo->SetCreatorID(nCreatorID);

					time_t time=root["create time"].asUInt();
					pInfo->SetCreateTime(time);

					CString szMatrix(root["gmatrix"].asString().c_str());
					pInfo->SetMatrix(szMatrix);

					int nMatrieRow,nMatrixColumn;
					HandleCalculate::GetRowAndColumnByMatrix(szMatrix,nMatrieRow,nMatrixColumn);
					pInfo->SetMatrixRow(nMatrieRow);
					pInfo->SetMatrixColumn(nMatrixColumn);

					//没有按照在线和不在线，而是按照组集合来查找，所以会重复一次，每次要清空下面集合
					VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
					VecArrage.clear();
					CString szInfo(root["ginfo"].asString().c_str());
					pInfo->SetArray(szInfo);
					HandleCalculate::GetMatrixByInfo(szInfo,VecArrage);
				}				
			}
		}
		else if(szSendType==_T("ADD"))
		{
			if(nResult==101)
			{
				//TRACE(_T("group\n"));

				MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szGroupName);
				if(iter==MapNodeGroup.end())
				{
					XNodeGroupInfo* pInfo=new XNodeGroupInfo;

					pInfo->SetGroupName(szGroupName);
					pInfo->SetGroupID(nGroupID);

					int nType=root["type"].asInt();
					pInfo->SetType(nType);
					nodeGroup.SetType(nType);

					int nMaster=root["master"].asInt();
					pInfo->SetMaster(nMaster);

					int nCreatorID=root["creator ID"].asInt();
					pInfo->SetCreatorID(nCreatorID);

					time_t time=root["create time"].asUInt();
					pInfo->SetCreateTime(time);

					CString szMatrix(root["gmatrix"].asString().c_str());
					pInfo->SetMatrix(szMatrix);

					int nMatrieRow,nMatrixColumn;
					HandleCalculate::GetRowAndColumnByMatrix(szMatrix,nMatrieRow,nMatrixColumn);
					pInfo->SetMatrixRow(nMatrieRow);
					pInfo->SetMatrixColumn(nMatrixColumn);

					VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
					VecArrage.clear();
					CString szInfo(root["ginfo"].asString().c_str());
					pInfo->SetArray(szInfo);
					HandleCalculate::GetMatrixByInfo(szInfo,VecArrage);

					MapNodeGroup.insert(std::pair<CString,XNodeGroupInfo*>(szGroupName,pInfo));
				}	
			}
		}
		else if(szSendType==_T("UPDATE"))
		{
			if(nResult==101)
			{
				switch(nodeGroup.GetUpdateMark())
				{
				case UPDATAMAKE_GROUPARRAGE:
					{
						//更新排列
						MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szGroupName);
						if(iter!=MapNodeGroup.end())
						{
							XNodeGroupInfo* pInfo=iter->second;

							pInfo->SetGroupName(szGroupName);
							pInfo->SetGroupID(nGroupID);

							int nMaster=root["master"].asInt();
							pInfo->SetMaster(nMaster);

							CString szMatrix(root["gmatrix"].asString().c_str());
							pInfo->SetMatrix(szMatrix);

							int nMatrieRow,nMatrixColumn;
							HandleCalculate::GetRowAndColumnByMatrix(szMatrix,nMatrieRow,nMatrixColumn);
							pInfo->SetMatrixRow(nMatrieRow);
							pInfo->SetMatrixColumn(nMatrixColumn);

							VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
							VecArrage.clear();
							CString szInfo(root["ginfo"].asString().c_str());
							pInfo->SetArray(szInfo);
							HandleCalculate::GetMatrixByInfo(szInfo,VecArrage);
						}
					}
					break;
				case UPDATAMAKE_GROUPNAME:
					{
						//先找到组旧名称
						CString szOldName=_T("");
						XNodeGroupInfo* pInfo=HandleCalculate::GetNodeInfoByID(MapNodeGroup,nGroupID,szOldName,FALSE);
						if(NULL==pInfo)
							break;
						pInfo->SetGroupName(szGroupName);
						//从集合删除
						MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szOldName);
						if(iter!=MapNodeGroup.end())
						{
							MapNodeGroup.erase(iter);
						}
						//再将新名称插入集合
						MapNodeGroup.insert(std::pair<CString,XNodeGroupInfo*>(szGroupName,pInfo));
					}
					break;
				case UPDATAMAKE_GROUPMASTER:
					{
						//更改坐席主节点
						MAP_NODEGROUP::iterator iter=MapNodeGroup.find(szGroupName);
						if(iter==MapNodeGroup.end())
						{
							XNodeGroupInfo* pInfo=iter->second;
							
							int nMaster=root["master"].asInt();
							nodeGroup.SetGroupMaster(nMaster);
							pInfo->SetMaster(nMaster);
						}
					}
					break;
				default:
					break;
				}
			}
		}
		else if(szSendType==_T("DEL"))
		{
			//删除
			//TRACE(_T("szSendType==DEL\n"));

		}
	}
}

void XJsonManage::ParseJsonToReMainAndSecondList(const char* pData,MAP_GROUPMAINSEC& MapList)
{
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();

		if(nResult==0)
		{
			const Json::Value array=root["master group list"];
			Json::Value::Members members=array.getMemberNames();
			for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
			{
				std::string strKey=*iterMember;
				CString szKey(strKey.c_str());
				int nGroupID=HandleCalculate::GetIDByJsonKey(szKey);
				CString szGroupName(array[strKey].asString().c_str());

				if(MapList.find(szGroupName)!=MapList.end())
				{
					XNodeGroupInfo* pInfo=MapList[szGroupName];
					pInfo->SetGroupName(szGroupName);
					pInfo->SetGroupID(nGroupID);
				}
				else
				{
					XNodeGroupInfo* pInfo=new XNodeGroupInfo;
					pInfo->SetGroupName(szGroupName);
					pInfo->SetGroupID(nGroupID);
					MapList.insert(std::pair<CString,XNodeGroupInfo*>(szGroupName,pInfo));
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReMainAndSecond(const char* pData,MAP_GROUPMAINSEC& MapNodeGroup,XNodeGroup& nodeGroup)
{
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();
		CString szSendType(root["utype"].asString().c_str());
		CString szGroupName(root["name"].asString().c_str());
		int nGroupID=root["mgroup ID"].asInt();
		int nMark=root["update mark"].asInt();

		nodeGroup.SetResult(nResult);
		nodeGroup.SetGroupName(szGroupName);
		nodeGroup.SetGroupID(nGroupID);
		nodeGroup.SetSendType(szSendType);
		nodeGroup.SetUpdateMark(nMark);

		if(szSendType==_T("QUERY"))
		{
			if(nResult==0)
			{
				XNodeGroupInfo* pInfo=NULL;
				MAP_GROUPMAINSEC::iterator iter=MapNodeGroup.find(szGroupName);
				if(iter==MapNodeGroup.end())
				{
					pInfo=new XNodeGroupInfo;
					MapNodeGroup.insert(std::pair<CString,XNodeGroupInfo*>(szGroupName,pInfo));
				}
				else
				{
					pInfo=iter->second;
				}

				pInfo->SetGroupName(szGroupName);
				pInfo->SetGroupID(nGroupID);
				pInfo->SetMainSecond(TRUE);
				pInfo->SetType(1);//类型默认为1，输入

				int nMaster=root["master"].asInt();
				pInfo->SetMaster(nMaster);

				int nCreatorID=root["creator ID"].asInt();
				pInfo->SetCreatorID(nCreatorID);

				time_t time=root["create time"].asUInt();
				pInfo->SetCreateTime(time);

				CString szMatrix(root["gmatrix"].asString().c_str());
				pInfo->SetMatrix(szMatrix);

				int nMatrieRow,nMatrixColumn;
				HandleCalculate::GetRowAndColumnByMatrix(szMatrix,nMatrieRow,nMatrixColumn);
				pInfo->SetMatrixRow(nMatrieRow);
				pInfo->SetMatrixColumn(nMatrixColumn);

				//没有按照在线和不在线，而是按照组集合来查找，所以会重复一次，每次要清空下面集合
				VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
				VecArrage.clear();
				CString szInfo(root["ginfo"].asString().c_str());
				pInfo->SetArray(szInfo);
				HandleCalculate::GetMatrixByInfo(szInfo,VecArrage);
			}
		}
		else if(szSendType==_T("ADD"))
		{
			if(nResult==101)
			{
				//TRACE(_T("mainSec\n"));

				MAP_GROUPMAINSEC::iterator iter=MapNodeGroup.find(szGroupName);
				if(iter==MapNodeGroup.end())
				{
					XNodeGroupInfo* pInfo=new XNodeGroupInfo;

					pInfo->SetGroupName(szGroupName);
					pInfo->SetGroupID(nGroupID);
					pInfo->SetMainSecond(TRUE);
					pInfo->SetType(1);

					MapNodeGroup.insert(std::pair<CString,XNodeGroupInfo*>(szGroupName,pInfo));
				}
			}
		}
		else if(szSendType==_T("DEL"))
		{

		}
		else if(szSendType==_T("UPDATE"))
		{
			if(nResult==101)
			{
				switch(nodeGroup.GetUpdateMark())
				{
					case UPDATAMAKE_MASTERNAME:
						{
							//先找到组旧名称 ID不唯一现在
							CString szOldName=_T("");
							XNodeGroupInfo* pInfo=HandleCalculate::GetNodeInfoByID(MapNodeGroup,nGroupID,szOldName,TRUE);
							if(NULL==pInfo)
								break;

							pInfo->SetGroupName(szGroupName);
							//从集合删除
							MAP_GROUPMAINSEC::iterator iter=MapNodeGroup.find(szOldName);
							if(iter!=MapNodeGroup.end())
							{
								MapNodeGroup.erase(iter);
							}
							//再将新名称插入集合
							MapNodeGroup.insert(std::pair<CString,XNodeGroupInfo*>(szGroupName,pInfo));
						}
						break;
					case UPDATAMAKE_MASTERARRAGE:
						{
							//更新排列
							MAP_GROUPMAINSEC::iterator iter=MapNodeGroup.find(szGroupName);
							if(iter!=MapNodeGroup.end())
							{
								XNodeGroupInfo* pInfo=iter->second;

								pInfo->SetGroupName(szGroupName);
								pInfo->SetGroupID(nGroupID);

								int nMaster=root["master"].asInt();
								pInfo->SetMaster(nMaster);

								CString szMatrix(root["gmatrix"].asString().c_str());
								pInfo->SetMatrix(szMatrix);

								int nMatrieRow,nMatrixColumn;
								HandleCalculate::GetRowAndColumnByMatrix(szMatrix,nMatrieRow,nMatrixColumn);
								pInfo->SetMatrixRow(nMatrieRow);
								pInfo->SetMatrixColumn(nMatrixColumn);

								VEC_ARRAGE& VecArrage=pInfo->GetVecArrage();
								VecArrage.clear();
								CString szInfo(root["ginfo"].asString().c_str());
								pInfo->SetArray(szInfo);
								HandleCalculate::GetMatrixByInfo(szInfo,VecArrage);
							}
						}
						break;
					default:
						break;
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReSystemStatus(const char* pData,XSystemStatus* systemStatus)
{
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();
		systemStatus->SetResult(nResult);

		int nCpuTemp=root["get"]["cpu_temp"].asInt();
		systemStatus->m_nCpuTemp=nCpuTemp;

		int nMatrixTemp=root["get"]["matrix_temp"].asInt();
		systemStatus->m_nMatrixTemp=nMatrixTemp;

		CString szCpuUse(root["get"]["cpu_use"].asString().c_str());
		systemStatus->m_szCpuUse=szCpuUse;

		CString szMemUse(root["get"]["mem_use"].asString().c_str());
		systemStatus->m_szMemUse=szMemUse;
	}
}

void XJsonManage::ParseJsonToReNetConfig(const char* pData,VEC_NETCONFIG& vecConfig,XResult& result)
{
	//TRACE(_T("ParseJsonToReNetConfig\n"));

	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();
		result.SetResult(nResult);

		CString szType(root["type"].asString().c_str());
		result.SetSendType(szType);

		if(nResult==0)
		{
			if(szType==_T("APPLY")||szType==_T("SAVE"))
			{
				std::string strIP=root["set"]["ip"].asString();
				int nPort=root["set"]["port"].asInt();
				std::string strMask=root["set"]["mask"].asString();
				std::string strGateway=root["set"]["gateway"].asString();
				bool bApply=root["set"]["apply"].asBool();
				bool bSave=root["set"]["save"].asBool();

				CString szIP(strIP.c_str());
				CString szMask(strMask.c_str());
				CString szGateway(strGateway.c_str());

				XNetConfig* pNetConfig=new XNetConfig;
				pNetConfig->SetIP(szIP);
				pNetConfig->SetPort(nPort);
				pNetConfig->SetMask(szMask);
				pNetConfig->SetGateway(szGateway);
				pNetConfig->SetApply(bApply);
				pNetConfig->SetSave(bSave);

				vecConfig.push_back(pNetConfig);
			}
			else if(szType==_T("QUERY"))
			{
				std::string strIP=root["get"]["ip"].asString();
				int nPort=root["get"]["port"].asInt();
				std::string strMask=root["get"]["mask"].asString();
				std::string strGateway=root["get"]["gateway"].asString();

				CString szIP(strIP.c_str());
				CString szMask(strMask.c_str());
				CString szGateway(strGateway.c_str());

				XNetConfig* pNetConfig=new XNetConfig;
				pNetConfig->SetIP(szIP);
				pNetConfig->SetPort(nPort);
				pNetConfig->SetMask(szMask);
				pNetConfig->SetGateway(szGateway);

				vecConfig.push_back(pNetConfig);
			}
		}
	}
}

void XJsonManage::ParseJsonToLog(const char* pData,VEC_LOG& VecLog,XLogPack& logPack)
{
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();
		logPack.SetResult(nResult);

		time_t data=root["date"].asUInt();
		CString szType(root["key"].asCString());
		int nTotal=root["total"].asInt();
		
		logPack.m_time=data;
		logPack.m_szType=szType;
		logPack.m_nCount=nTotal;

		if(nResult==0)
		{
			const Json::Value arrays=root["log"];
			Json::Value::Members members=arrays.getMemberNames();
			for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
			{
				std::string strKey=*iterMember;
				CString szKey(strKey.c_str());
				int nID=HandleCalculate::GetIDByJsonKey(szKey);

				time_t time=0;
				if(arrays[strKey]["time"].isInt())
				{
					time=arrays[strKey]["time"].asUInt();
				}

				CString szEvent=_T("");
				if(arrays[strKey]["event"].isString())
				{
					CString szTempEvent(arrays[strKey]["event"].asCString());
					szEvent=szTempEvent;
				}

				CString szTermID=_T("");
				if(arrays[strKey]["term ID"].isString())
				{
					CString szTempTermID(arrays[strKey]["term ID"].asCString());
					szTermID=szTempTermID;
				}			

				int nTermNo=0;
				if(arrays[strKey]["term NO"].isInt())
				{
					nTermNo=arrays[strKey]["term NO"].asInt();
				}

				int nTermCh=0;
				if(arrays[strKey]["term CH"].isInt())
				{
					nTermCh=arrays[strKey]["term CH"].asInt();
				}

				CString szUser=_T("");
				if(arrays[strKey]["user"].isString())
				{
					CString szTempUser(arrays[strKey]["user"].asCString());
					szUser=szTempUser;
				}

				CString szTargetUser=_T("");
				if(arrays[strKey]["tg user"].isString())
				{
					CString szTempTargetUser(arrays[strKey]["tg user"].asCString());
					szTargetUser=szTempTargetUser;
				}

				CString szIpAddr=_T("");
				if(arrays[strKey]["ipaddr"].isString())
				{
					CString szTempIpAddr(arrays[strKey]["ipaddr"].asCString());
					szIpAddr=szTempIpAddr;
				}

				CString szTargetTermID=_T("");
				if(arrays[strKey]["tg term ID"].isString())
				{
					CString szTempTargetTermID(arrays[strKey]["tg term ID"].asCString());
					szTargetTermID=szTempTargetTermID;
				}

				int szTargetTermNo=0;
				if(arrays[strKey]["tg term NO"].isInt())
				{
					szTargetTermNo=(arrays[strKey]["tg term NO"].asInt());
				}
				
				CString szNote=_T("");
				if(arrays[strKey]["note"].isString())
				{
					CString szTempNote(arrays[strKey]["note"].asCString());
					szNote=szTempNote;
				}
	
				XLogInfo* pInfo=new XLogInfo;
				pInfo->m_Time=time;
				pInfo->m_szEvent=szEvent;
				pInfo->m_szTermID=szTermID;
				pInfo->m_nTermNo=nTermNo;
				pInfo->m_nTermCh=nTermCh;
				pInfo->m_szUser=szUser;
				pInfo->m_szTargetUser=szTargetUser;
				pInfo->m_szIpAddr=szIpAddr;
				pInfo->m_szTargetTermID=szTargetTermID;
				pInfo->m_nTargetTermNo=szTargetTermNo;
				pInfo->m_szNote=szNote;

				VecLog.push_back(pInfo);
			}
		}	
	}
}

void XJsonManage::ParseJsonToFolder(const char* pData,XUserManage* pManage,XFolderResult& result)
{
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();
		result.SetResult(nResult);

		CString szType(root["utype"].asCString());
		result.SetSendType(szType);

		if(szType==_T("QUERY"))
		{
			if(nResult!=0)
				return;

			CString szSubType(root["subType"].asCString());
			result.SetSubType(szSubType);


			if(szSubType==_T("ROOT"))
			{
				MAP_ROOTFOLDER& MapRootFolder=pManage->GetMapRootFolder();

				const Json::Value arrays=root["folder list"];
				Json::Value::Members members=arrays.getMemberNames();
				for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
				{
					std::string strKey=*iterMember;
					CString szKey(strKey.c_str());
					int nFolderType=HandleCalculate::GetTypeByJsonKey(szKey); //此处格式一定要正确 type_ID
					int nID=HandleCalculate::GetIDByJsonKey(szKey);
					CString szRootName(arrays[strKey].asString().c_str());

					if(MapRootFolder.find(nID)==MapRootFolder.end())
					{
						XFolderInfo* pInfo=new XFolderInfo;
						pInfo->SetID(nID);
						pInfo->SetName(szRootName);
						pInfo->SetType(nFolderType);

						MapRootFolder.insert(std::pair<int,XFolderInfo*>(nID,pInfo));
					}
					else
					{
						XFolderInfo* pInfo=MapRootFolder[nID];
						pInfo->SetID(nID);
						pInfo->SetName(szRootName);
						pInfo->SetType(nFolderType);
					}
				}
			}
			else if(szSubType==_T("CHILD"))
			{
				int nID=root["ID"].asInt();
				int nType=root["type"].asInt();
				CString szName(root["name"].asCString());

				XSubFolder* pSub=NULL;
				auto& MapSubFolder=pManage->GetMapSubFolder();
				if(MapSubFolder.find(nID)!=MapSubFolder.end())
				{
					pSub=MapSubFolder[nID];
				}
				else
				{
					pSub=new XSubFolder;
					MapSubFolder.insert(std::pair<int,XSubFolder*>(nID,pSub));
				}

				pSub->SetID(nID);
				pSub->SetName(szName);
				pSub->SetType(nType);

				CString szTermList(root["term list"].asCString());
				auto& MapTermList=pSub->GetMapTermList();
				MapTermList.clear();
				HandleCalculate::SplitCString(szTermList,MapTermList);//格式固定

				CString szUserList(root["user list"].asCString());
				auto& MapUserList=pSub->GetMapUserList();
				MapUserList.clear();
				HandleCalculate::SplitCString(szUserList,MapUserList);


				auto& MapSubFolderList=pSub->GetMapSubFolderList();
				pSub->ClearMapFolderList();
				const Json::Value arrays=root["sub list"];
				Json::Value::Members members=arrays.getMemberNames();

				//TRACE(_T("member=%d\n"),members.size());

				for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
				{
					std::string strKey=*iterMember;
					CString szKey(strKey.c_str());
					int nMyID=_ttoi(szKey);

					//TRACE(_T("ID=%d\n"),nID);
					//int nFolderType=HandleCalculate::GetTypeByJsonKey(szKey); //此处格式一定要正确 type_ID
					//int nID=HandleCalculate::GetIDByJsonKey(szKey);
					CString szMyName(arrays[strKey].asString().c_str());

					if(MapSubFolderList.find(nMyID)==MapSubFolderList.end())
					{
						XSubFolder* pInfo=new XSubFolder;
						pInfo->SetID(nMyID);
						pInfo->SetName(szMyName);
						pInfo->SetParent(szName);
						pInfo->SetParentID(nID);

						MapSubFolderList.insert(std::pair<int,XSubFolder*>(nMyID,pInfo));
					}

					//////////////////////////////////////////////////////////////////////////
					//用于下次查询
					//pManage->ClearMapTempSubFolder();
					pManage->InsetTempSubFolder(nMyID,szMyName);
				}
			}
		}
		else if(szType==_T("DEL"))
		{
			if(nResult!=0)
				return;
			result.m_szSubType=szType;
			result.m_nID=root["ID"].asInt();
		}
		else if(szType==_T("ADD"))
		{
			{}
			TRACE(_T("result=%d\n"),nResult);
			if(nResult!=101)
				return;

			int nParentID=root["PID"].asInt();
			int nType=root["type"].asInt();
			CString szName(root["name"].asCString());
			int nNewID=root["newID"].asInt();

			result.m_nID=nNewID;
			result.m_nParentID=nParentID;
			result.m_szFolderName=szName;

			if(nParentID==0)
			{
				//父节点(根据ID)
				auto& MapRootFolder=pManage->GetMapRootFolder();
				if(MapRootFolder.find(nNewID)==MapRootFolder.end())
				{
					XFolderInfo* pInfo=new XFolderInfo;
					pInfo->SetID(nNewID);
					pInfo->SetName(szName);
					pInfo->SetType(nType);
					MapRootFolder.insert(std::pair<int,XFolderInfo*>(nNewID,pInfo));
				}
			}
		}
	}
}

void XJsonManage::ParseJsonToReSplit(const char* pData,MAP_BASEVIEW& MapBaseView,XSplitResult& result)
{
	//解析拼接数据
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();
		result.SetResult(nResult);

		CString szType(root["utype"].asCString());
		result.SetSendType(szType);

		if(szType==_T("LIST"))
		{
			if(nResult!=0)
				return;

			int nIndex=root["index"].asInt();
			int nTotal=root["total"].asInt();

			const Json::Value array=root["list"];
			if(!array.isNull())
			{
				for(unsigned int i=0;i<array.size();++i)
				{
					CString szWallName(array[i].asCString());
					//TRACE(_T("Wall=%s\n"),szWallName);
					//序号从3开始 获取序号
					int nIndex=3;
					while(nIndex)
					{
						if(MapBaseView.find(nIndex)==MapBaseView.end())
							break;
						nIndex++;
					}

					XSplitManage* pManage=new XSplitManage;
					pManage->SetBaseIndex(nIndex);
					pManage->SetSplitName(szWallName);

					MapBaseView.insert(std::pair<int,XBaseViewManage*>(nIndex,pManage));
				}
			}
		}
		else if(szType==_T("QUERY"))
		{
			if(nResult!=0)
				return;

			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;

			if(szSplitName==_T(""))
				return;

			for(auto& map:MapBaseView)
			{
				XSplitManage* pManage=(XSplitManage*)map.second;
				if(pManage->GetSplitName()==szSplitName)
				{
					int nStatus=root["wall_obj"]["status"].asInt();
					pManage->SetStatus(nStatus);

					int nID=root["wall_obj"]["id"].asInt();
					pManage->SetSplitID(nID);

					int nCutUse=root["wall_obj"]["cut_use"].asInt();
					pManage->SetCutUse(nCutUse);


					auto& VecCutPix=pManage->GetVecCutPix();
					VecCutPix.clear();
					const Json::Value array1=root["wall_obj"]["cut_pix"];
					if(!array1.isNull())
					{
						for(unsigned int i=0;i<array1.size();++i)
						{
							int nCutPix=array1[i].asInt();
							VecCutPix.push_back(nCutPix);
						}
					}

					int nPixIndex=root["wall_obj"]["output_n"].asInt();
					pManage->SetPixIndex(nPixIndex);

					int nResulationH=root["wall_obj"]["output_h"].asInt();
					pManage->SetRealResulationX(nResulationH);
					
					int nResulationV=root["wall_obj"]["output_v"].asInt();
					pManage->SetRealResulationY(nResulationV);

					int nScreenCountH=root["wall_obj"]["screen_num_h"].asInt();
					pManage->SetScreenCountX(nScreenCountH);

					int nScreenCountV=root["wall_obj"]["screen_num_v"].asInt();
					pManage->SetScreenCountY(nScreenCountV);


					auto& VecSplitCh=pManage->GetVecSplitCh();
					VecSplitCh.clear();
					const Json::Value array2=root["wall_obj"]["screen_mch_list"];
					if(!array2.isNull())
					{
						for(unsigned int i=0;i<array2.size();++i)
						{
							int nSplitCh=array2[i].asInt();
							VecSplitCh.push_back(nSplitCh);
						}
					}

					auto& VecLevelList=pManage->GetVecLevelList();
					VecLevelList.clear();
					const Json::Value array3=root["wall_obj"]["screen_use_level_list"];
					if(!array3.isNull())
					{
						for(unsigned int i=0;i<array3.size();++i)
						{
							int nSplitSignalCount=array3[i].asInt();
							VecLevelList.push_back(nSplitSignalCount);
						}
					}
				}
			}
		}
		else if(szType==_T("ADD"))
		{
		    TRACE(_T("wall Add=%d\n"),nResult);

			if(nResult!=0)
				return;

			//代码格式问题	
			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;

			//计算页面序号
			int nIndex=3;
			while(nIndex)
			{
				if(MapBaseView.find(nIndex)==MapBaseView.end())
					break;
				nIndex++;
			}

			XSplitManage* pManage=new XSplitManage;
			pManage->SetBaseIndex(nIndex);
			pManage->SetSplitName(szSplitName);
			
			int nStatus=root["wall_obj"]["status"].asInt();
			pManage->SetStatus(nStatus);

			int nID=root["wall_obj"]["id"].asInt();
			pManage->SetSplitID(nID);

			int nCutUse=root["wall_obj"]["cut_use"].asInt();
			pManage->SetCutUse(nCutUse);

			auto& VecCutPix=pManage->GetVecCutPix();
			VecCutPix.clear();
			const Json::Value array1=root["wall_obj"]["cut_pix"];
			if(!array1.isNull())
			{
				for(unsigned int i=0;i<array1.size();++i)
				{
					int nCutPix=array1[i].asInt();
					VecCutPix.push_back(nCutPix);
				}
			}

			int nPixIndex=root["wall_obj"]["output_n"].asInt();
			pManage->SetPixIndex(nPixIndex);

			int nResulationH=root["wall_obj"]["output_h"].asInt();
			pManage->SetRealResulationX(nResulationH);

			int nResulationV=root["wall_obj"]["output_v"].asInt();
			pManage->SetRealResulationY(nResulationV);

			int nScreenCountH=root["wall_obj"]["screen_num_h"].asInt();
			pManage->SetScreenCountX(nScreenCountH);

			int nScreenCountV=root["wall_obj"]["screen_num_v"].asInt();
			pManage->SetScreenCountY(nScreenCountV);


			auto& VecSplitCh=pManage->GetVecSplitCh();
			VecSplitCh.clear();
			const Json::Value array2=root["wall_obj"]["screen_mch_list"];
			if(!array2.isNull())
			{
				for(unsigned int i=0;i<array2.size();++i)
				{
					int nSplitCh=array2[i].asInt();
					VecSplitCh.push_back(nSplitCh);
				}
			}

			auto& VecLevelList=pManage->GetVecLevelList();
			VecLevelList.clear();
			const Json::Value array3=root["wall_obj"]["screen_use_level_list"];
			if(!array3.isNull())
			{
				for(unsigned int i=0;i<array3.size();++i)
				{
					int nSplitSignalCount=array3[i].asInt();
					VecLevelList.push_back(nSplitSignalCount);
				}
			}

			MapBaseView.insert(std::pair<int,XBaseViewManage*>(nIndex,pManage));
		}
		else if(szType==_T("DEL"))
		{
			//删除
			//TRACE(_T("DEL"));
			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;
		}
		else if(szType==_T("REFRESH"))
		{
			//TRACE(_T("REFRESH\n"));
		}
		else if(szType==_T("DRAW"))
		{
		//TRACE(_T("REFRESH\n"));
		}
	}
}

void XJsonManage::ParseJsonToReSplitWondow(const char* pData,MAP_BASEVIEW& MapBaseView,XSplitWindow& result)
{
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();
		result.SetResult(nResult);

		CString szType(root["utype"].asCString());
		result.SetSendType(szType);
	
		if(szType==_T("LIST"))
		{
			//TRACE(_T("win list=%d\n"),nResult);

			if(nResult!=0)
				return;

			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;
			//TRACE(_T("Name=%s\n"),szSplitName);

			if(szSplitName==_T(""))
				return;

			CString szSubType(root["Subtype"].asCString());
			result.SetSubSendType(szSubType);

			//TRACE(_T("subType=%s\n"),szSubType);

			for(auto& map:MapBaseView)
			{
				XBaseViewManage* pBaseView=map.second;
				if(pBaseView->GetSplitName()==szSplitName)
				{
					auto& VecIdList=((XSplitManage*)pBaseView)->GetVecIdList();
					VecIdList.clear();

					const Json::Value array=root["list"];
					if(!array.isNull())
					{
						//ID list 已经是正确层次
						for(unsigned int i=0;i<array.size();++i)
						{
							int nSignalID=array[i].asInt();

							//TRACE(_T("ID=%d\n"),nSignalID);
							VecIdList.push_back(nSignalID);
						}
					}
				}
			}
		}
		else if(szType==_T("QUERY"))
		{
			//TRACE(_T("win QUERY=%d\n"),nResult);
			if(nResult!=0)
				return;

			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;
			
			int nSignalID=root["ID"].asInt();
			//TRACE(_T("signalID=%d\n"),nSignalID);

			if(szSplitName==_T(""))
				return;

			for(auto& map:MapBaseView)
			{
				XBaseViewManage* pBaseView=map.second;
				if(pBaseView->GetSplitName()==szSplitName)
				{
					auto& VecSignal=((XSplitManage*)pBaseView)->GetVecSignal();
					for(auto& pSignal:VecSignal)
					{
						if(pSignal->GetSignalID()==nSignalID)
						{
							//窗口信息
							int nInputCh=root["win_obj"]["input_ch"].asInt();
							pSignal->SetInputCh(nInputCh);

							int nCutUse=root["win_obj"]["cut_use"].asInt();
							pSignal->SetCutUse(nCutUse);

							auto& VecCutPix=pSignal->GetVecCutPix();
							VecCutPix.clear();
							const Json::Value array1=root["win_obj"]["cut_pix"];
							if(!array1.isNull())
							{
								for(unsigned int i=0;i<array1.size();++i)
								{
									int nCutPix=array1[i].asInt();
									VecCutPix.push_back(nCutPix);	
								}
							}

							RECTF rect(0,0,0,0);
							const Json::Value array2=root["win_obj"]["pos"];
							if(!array2.isNull())
							{
								if(array2.size()==4)
								{
									int X1=array2[(unsigned int)0].asInt();
									int X2=array2[(unsigned int)1].asInt();
									int Y1=array2[(unsigned int)2].asInt();
									int Y2=array2[(unsigned int)3].asInt();

									rect.X=X1;
									rect.Y=Y1;
									rect.Width=X2-X1;
									rect.Height=Y2-Y1;
								}

								//TRACE(_T("X=%f,Y=%f,W=%f,H=%f\n"),rect.X,rect.Y,rect.Width,rect.Height);

								pSignal->SetRealRect(rect);
							}

							int nLevel=root["win_obj"]["level"].asInt();
							pSignal->SetLevel(nLevel);
						}
					}
				}
			}
		}
		else if(szType==_T("ADD"))
		{
		//TRACE(_T("Add win=%d\n"),nResult);
			//添加信号
			if(nResult!=0)
				return;

			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;

			if(szSplitName==_T(""))
				return;

			for(auto& map:MapBaseView)
			{
				XBaseViewManage* pBaseView=map.second;
				if(pBaseView->GetSplitName()==szSplitName)
				{
					auto& VecSignal=((XSplitManage*)pBaseView)->GetVecSignal();

					XSignal* pSignal=new XSignal;
					int nID=root["win ID"].asInt();
					pSignal->SetSignalID(nID);
					result.m_nSignalID=nID;


					int nInputCh=root["win_obj"]["input_ch"].asInt();
					pSignal->SetInputCh(nInputCh);

					int nCutUse=root["win_obj"]["cut_use"].asInt();
					pSignal->SetCutUse(nCutUse);

					auto& VecCutPix=pSignal->GetVecCutPix();
					VecCutPix.clear();
					const Json::Value array1=root["win_obj"]["cut_pix"];
					if(!array1.isNull())
					{
						for(unsigned int i=0;i<array1.size();++i)
						{
							int nCutPix=array1[i].asInt();
							VecCutPix.push_back(nCutPix);
						}
					}

					RECTF rect(0,0,0,0);
					const Json::Value array2=root["win_obj"]["pos"];
					if(!array2.isNull())
					{
						if(array2.size()==4)
						{
							int X1=array2[(unsigned int)0].asInt();
							int X2=array2[(unsigned int)1].asInt();
							int Y1=array2[(unsigned int)2].asInt();
							int Y2=array2[(unsigned int)3].asInt();

							rect.X=X1;
							rect.Y=Y1;
							rect.Width=X2-X1;
							rect.Height=Y2-Y1;
						}

						pSignal->SetRealRect(rect);
					}

					int nLevel=root["win level"].asInt();
					pSignal->SetLevel(nLevel);

					VecSignal.push_back(pSignal);
				}
			}
		}
		else if(szType==_T("DEL"))
		{
		//删除单个窗口
		    if(nResult!=0)
				return;

			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;

			int nID=root["ID"].asInt();
			result.m_nSignalID=nID;
		}
		else if(szType==_T("CLEAR"))
		{
			if(nResult!=0)
				return;

			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;
		}
		else if(szType==_T("LEVEL_USE"))
		{	
			if(nResult!=0)
				return;

			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;

			if(szSplitName==_T(""))
				return;

			for(auto& map:MapBaseView)
			{
				XBaseViewManage* pBaseView=map.second;
				if(pBaseView->GetSplitName()==szSplitName)
				{
					auto& VecLevelList=((XSplitManage*)pBaseView)->GetVecLevelList();
					VecLevelList.clear();
					const Json::Value array=root["list"];
					if(!array.isNull())
					{
						for(unsigned int i=0;i<array.size();++i)
						{
							int nLevelUse=array[i].asInt();
							VecLevelList.push_back(nLevelUse);
						}
					}
				}
			}
		}
		else if(szType==_T("WIN_LEVEL"))
		{

		//TRACE(_T("WIN_LEVEL=%d\n"),nResult);
			//更改层次
			if(nResult!=0)
				return;

			CString szSplitName(root["wall name"].asCString());
			result.m_szSplitName=szSplitName;
		}
	}
}

void XJsonManage::ParseJsonToReSplitScene(const char* pData,XInternalManage* pInternal,XSplitSceneResult& result)
{
	Json::Reader reader;
	Json::Value root;

	if(reader.parse(pData,root))
	{
		int nResult=root["result"].asInt();
		result.SetResult(nResult);

		CString szType(root["utype"].asCString());
		result.SetSendType(szType);

	
		if(szType==_T("LIST"))
		{
			if(nResult!=0)
				return;

			//场景名称
			auto& MapSplitScene=pInternal->GetMapSplitScene();
			for(auto& map:MapSplitScene)
			{
				delete map.second;
			}
			MapSplitScene.clear();

			const Json::Value array=root["scene list"];
			if(!array.isNull())
			{
				for(unsigned int i=0;i<array.size();++i)
				{
					CString szScene(array[i].asCString());		
					CString szSceneName=HandleCalculate::GetSceneNameByJsonKey(szScene);

					XSplitScene* pScene=new XSplitScene;
					pScene->SetSceneName(szSceneName);
					MapSplitScene.insert(std::pair<CString,XSplitScene*>(szSceneName,pScene));
				}
			}
		}
		else if(szType==_T("GET_GROUP"))
		{
			if(nResult!=0)
				return;

			CString szSceneName(root["scene_name"].asCString());
			CString szGroup(root["group"].asCString());

			if(_T("")==szGroup)
				return;
		
			//组名称保存在场景中  
			auto& MapGroup=pInternal->GetMapSplitSceneGroup();
			MapGroup.insert(std::pair<CString,HTREEITEM>(szGroup,NULL));

			//把组设置到场景
			auto& MapScene=pInternal->GetMapSplitScene();
			if(MapScene.find(szSceneName)!=MapScene.end())
			{
				XSplitScene* pScene=MapScene[szSceneName];
				pScene->m_szSceneGroup=szGroup;
			}
		}
		else if(szType==_T("SET_GROUP"))
		{
			//TRACE(_T("SET_GROUP=%d\n"),nResult);

			if(nResult!=0)
				return;

			CString szSceneName(root["scene_name"].asCString());
			result.m_szSceneName=szSceneName;
			CString szGroup(root["group"].asCString());
			result.m_szGroupName=szGroup;
			int nAlter=root["alter"].asInt();
			result.m_nAlter=nAlter;

			if(nAlter)
			{
				//改组
				result.m_bNewGroup=FALSE;
			}
			else
			{
				//设置组
			    //如果没有插进去
				auto& MapGroup=pInternal->GetMapSplitSceneGroup();
				if(MapGroup.find(szGroup)==MapGroup.end())
				{
					result.m_bNewGroup=TRUE;
					//找到最后一个元素
					if(MapGroup.size()==0)
					{
						result.m_hItem=NULL;
					}
					else
					{
						auto iter=MapGroup.rbegin();
						HTREEITEM hItem=iter->second;
						result.m_hItem=hItem;
					}

					MapGroup.insert(std::pair<CString,HTREEITEM>(szGroup,NULL));
				}
				else
				{
					result.m_bNewGroup=FALSE;
				}
			}

			//把组设置到场景 (如果添加场景时 还没有新的场景在集合中)
			auto& MapScene=pInternal->GetMapSplitScene();
			if(MapScene.find(szSceneName)!=MapScene.end())
			{
				XSplitScene* pScene=MapScene[szSceneName];
				pScene->m_szSceneGroup=szGroup;
			}
		}
		else if(szType==_T("LIST_WALL"))
		{
		TRACE(_T("LIST_WALL=%d\n"),nResult);


			if(nResult!=0)
				return;

			auto& MapSplitScene=pInternal->GetMapSplitScene();
			CString szSceneName(root["scene_name"].asCString());

			if(MapSplitScene.find(szSceneName)!=MapSplitScene.end())
			{
				XSplitScene* pScene=MapSplitScene[szSceneName];

				auto& VecWallList=pScene->GetVecWallList();
				VecWallList.clear();

				const Json::Value array=root["wall list"];
				if(!array.isNull())
				{
					for(unsigned int i=0;i<array.size();++i)
					{
						CString szWallName(array[i].asCString());
						VecWallList.push_back(szWallName);
					}
				}
			}
		}
		else if(szType==_T("DEL"))
		{
		TRACE(_T("Scene Del=%d\n"),nResult);

			if(nResult!=0)
				return;

			CString szSceneName(root["scene_name"].asCString());
			result.m_szSceneName=szSceneName;
		}
		else if(szType==_T("ADD"))
		{
			if(nResult!=0)
				return;

			CString szSceneName(root["scene_name"].asCString());
			result.m_szSceneName=szSceneName;
		}
		else if(szType==_T("SAVE_WALL"))
		{
			//TRACE(_T("SAVE_WALL=%d\n"),nResult);

			if(nResult!=0)
				return;

			CString szSceneName(root["scene_name"].asCString());
			result.m_szSceneName=szSceneName;

			CString szWallName(root["wall_name"].asCString());
			result.m_szWallName=szWallName;

			int nLast=root["last"].asInt();
			result.m_nLast=nLast;

		}
		else if(szType==_T("RECALL_WALL"))
		{
			//TRACE(_T("RECALL_WALL=%d\n"),nResult);
			if(nResult!=0)
				return;
			CString szSceneName(root["scene_name"].asCString());
			result.m_szSceneName=szSceneName;

			CString szWallName(root["wall_name"].asCString());
			result.m_szWallName=szWallName;

		}
		else if(szType==_T("QUERY_WALL"))
		{
			if(nResult!=0)
				return;

			auto& MapBaseView=pInternal->GetBaseView();

			CString szSceneName(root["scene_name"].asCString());
			if(_T("")==szSceneName)
				return;
			result.m_szSceneName=szSceneName;

			CString szWallName(root["wall_name"].asCString());
			result.m_szWallName=szWallName;

			XSplitManage* pManage=NULL;
			int nIndex=pInternal->DecideWallExistence(szWallName);
			if(nIndex!=0)
			{
				pManage=(XSplitManage*)MapBaseView[nIndex];
				result.m_bExist=TRUE;
			}
			else
			{
				result.m_bExist=FALSE;
				//不在 新建
				//计算页面序号
				int nIndex=3;
				while(nIndex)
				{
					if(MapBaseView.find(nIndex)==MapBaseView.end())
						break;
					nIndex++;
				}

				pManage=new XSplitManage;
				pManage->SetBaseIndex(nIndex);
				pManage->SetSplitName(szWallName);

				MapBaseView.insert(std::pair<int,XBaseViewManage*>(nIndex,pManage));
			}

			int nCutUse=root["scene_wall_obj"]["cut_use"].asInt();
			pManage->SetCutUse(nCutUse);

			auto& VecCutPix=pManage->GetVecCutPix();
			VecCutPix.clear();
			const Json::Value array1=root["scene_wall_obj"]["cut_pix"];
			if(!array1.isNull())
			{
				for(unsigned int i=0;i<array1.size();++i)
				{
					int nCutPix=array1[i].asInt();
					VecCutPix.push_back(nCutPix);
				}
			}

			int nPixIndex=root["scene_wall_obj"]["output_n"].asInt();
			pManage->SetPixIndex(nPixIndex);

			int nResulationH=root["scene_wall_obj"]["output_h"].asInt();
			pManage->SetRealResulationX(nResulationH);

			int nResulationV=root["scene_wall_obj"]["output_v"].asInt();
			pManage->SetRealResulationY(nResulationV);

			int nScreenCountH=root["scene_wall_obj"]["screen_num_h"].asInt();
			pManage->SetScreenCountX(nScreenCountH);

			int nScreenCountV=root["scene_wall_obj"]["screen_num_v"].asInt();
			pManage->SetScreenCountY(nScreenCountV);

			auto& VecSplitCh=pManage->GetVecSplitCh();
			VecSplitCh.clear();
			const Json::Value array2=root["scene_wall_obj"]["screen_mch_list"];
			if(!array2.isNull())
			{
				for(unsigned int i=0;i<array2.size();++i)
				{
					int nSplitCh=array2[i].asInt();
					VecSplitCh.push_back(nSplitCh);
				}
			}
			
			//通道占用列表 没拿到
			auto& VecLevelList=pManage->GetVecLevelList();
			VecLevelList.clear();

			//墙信号
			auto& VecSignal=pManage->GetVecSignal();
			pManage->ClearVecSignal();

			const Json::Value array=root["scene_wall_obj"]["win_list"];
			Json::Value::Members members=array.getMemberNames();
			for(Json::Value::Members::iterator iterMember=members.begin();iterMember!=members.end();++iterMember)
			{
				std::string strKey=*iterMember;
				CString szKey(strKey.c_str());

				int nSignalID=array[strKey]["id"].asInt();

				XSignal* pSignal=new XSignal;
				pSignal->SetSignalID(nSignalID);

				int nInputCh=array[strKey]["input_ch"].asInt();
				pSignal->SetInputCh(nInputCh);


				int nCutUse=array[strKey]["cut_use"].asInt();
				pSignal->SetCutUse(nCutUse);

				auto& VecCutPix=pSignal->GetVecCutPix();
				VecCutPix.clear();
				const Json::Value array1=array[strKey]["cut_pix"];
				if(!array1.isNull())
				{
					for(unsigned int i=0;i<array1.size();++i)
					{
						int nCutPix=array1[i].asInt();
						VecCutPix.push_back(nCutPix);
					}
				}

				RECTF rect(0,0,0,0);
				const Json::Value array2=array[strKey]["pos"];
				if(!array2.isNull())
				{
					if(array2.size()==4)
					{
						int X1=array2[(unsigned int)0].asInt();
						int X2=array2[(unsigned int)1].asInt();
						int Y1=array2[(unsigned int)2].asInt();
						int Y2=array2[(unsigned int)3].asInt();

						rect.X=X1;
						rect.Y=Y1;
						rect.Width=X2-X1;
						rect.Height=Y2-Y1;
					}

					pSignal->SetRealRect(rect);
				}

				int nLevel=array[strKey]["level"].asInt();
				pSignal->SetLevel(nLevel);
				VecSignal.push_back(pSignal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XJsonManage::WriteJsonToLogin(CString& szUserName,CString& szPassWd,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["user"]=Json::Value(W2A(szUserName));
	root["key"]=Json::Value(W2A(szPassWd));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToLoginOut(CString& szUserName,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["user"]=Json::Value(W2A(szUserName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToObtainAllUser(CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("LIST");
	//root["user"]=Json::Value(W2A(szUserName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToObtainPower(CString szUserName,CString &szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("QUERY");
	root["user"]=Json::Value(W2A(szUserName));
	root["user type"]=Json::Value("QUERY_CURUSER");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToObtainSubPower(int nID,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["ID"]=Json::Value(nID);
	root["user type"]=Json::Value("QUERY_SUBUSER");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToObtainAddUserPower(int nID,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["ID"]=Json::Value(nID);
	root["user type"]=Json::Value("QUERY_ADDUSER");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToObtainUserList(int nIndex,int nSize,CString &szData)
{
	Json::Value root;  
	Json::FastWriter write;

	//分页查询（暂时不用）
	//root["index"]=Json::Value(nIndex);
	//root["size"]=Json::Value(nSize);

	root[""]=Json::Value();
	//root[""]=Json::Value();

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAddUser(XPower* pPower,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("ADD");
	root["user"]=Json::Value(W2A(pPower->GetUserName()));
	root["key"]=Json::Value(W2A(pPower->GetPassWd()));
	root["user group"]=Json::Value(W2A(pPower->GetUserGroup()));
	root["manage permission"]=Json::Value(pPower->GetManagePermission());
	//////////////////////////////////////////////////////////////////////////
	Json::Value arrayView;
	Json::Value itemView;
	itemView["type"]=Json::Value(pPower->GetPrivilegeView().GetType());

	Json::Value itemViewPrivilege;
	VEC_PRIVILEGE& VecViewPrivilege=pPower->GetPrivilegeView().GetVecPrivilege();
	for(auto iter=VecViewPrivilege.begin();iter!=VecViewPrivilege.end();++iter)
	{
		int nPrivilege=*iter;
		itemViewPrivilege.append(nPrivilege);
	}

	itemView["privilege"]=itemViewPrivilege;
	root["privilege view"]=itemView;
	//////////////////////////////////////////////////////////////////////////
	Json::Value arrayCtrl;
	Json::Value itemCtrl;
	itemCtrl["type"]=Json::Value(pPower->GetPrivilegeCtrl().GetType());

	Json::Value itemCtrlPrivilege;
	VEC_PRIVILEGE& VecCtrlPrivilege=pPower->GetPrivilegeCtrl().GetVecPrivilege();
	for(auto iter=VecCtrlPrivilege.begin();iter!=VecCtrlPrivilege.end();++iter)
	{
		int nPrivilege=*iter;
		itemCtrlPrivilege.append(nPrivilege);
	}

	itemCtrl["privilege"]=itemCtrlPrivilege;
	root["privilege ctrl"]=itemCtrl;
	//////////////////////////////////////////////////////////////////////////
	Json::Value arrayLogin;
	Json::Value itemLogin;
	itemLogin["type"]=Json::Value(pPower->GetPrivilegeLogin().GetType());

	Json::Value itemLoginPrivilege;
	VEC_PRIVILEGE& VecLoginPrivilege=pPower->GetPrivilegeLogin().GetVecPrivilege();
	for(auto iter=VecLoginPrivilege.begin();iter!=VecLoginPrivilege.end();++iter)
	{
		int nPrivilege=*iter;
		itemLoginPrivilege.append(nPrivilege);
	}

	itemLogin["privilege"]=itemLoginPrivilege;
	root["privilege login"]=itemLogin;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterUser(XPower* pPower,CString& szData,CString szPassWd)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("UPDATE");
	root["user"]=Json::Value(W2A(pPower->GetUserName()));

	if(szPassWd!=_T(""))
	{
		root["key"]=Json::Value(W2A(pPower->GetPassWd()));
	}
	
	//root["user group"]=Json::Value(W2A(pPower->GetUserGroup()));
	root["manage permission"]=Json::Value(pPower->GetManagePermission());
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	Json::Value arrayView;
	Json::Value itemView;
	itemView["type"]=Json::Value(pPower->GetPrivilegeView().GetType());

	Json::Value itemViewPrivilege;
	VEC_PRIVILEGE& VecViewPrivilege=pPower->GetPrivilegeView().GetVecPrivilege();
	for(auto iter=VecViewPrivilege.begin();iter!=VecViewPrivilege.end();++iter)
	{
		int nPrivilege=*iter;
		itemViewPrivilege.append(nPrivilege);
	}

	itemView["privilege"]=itemViewPrivilege;
	root["privilege view"]=itemView; //发了不解析
	//////////////////////////////////////////////////////////////////////////
	Json::Value arrayCtrl;
	Json::Value itemCtrl;
	itemCtrl["type"]=Json::Value(pPower->GetPrivilegeCtrl().GetType());

	Json::Value itemCtrlPrivilege;
	VEC_PRIVILEGE& VecCtrlPrivilege=pPower->GetPrivilegeCtrl().GetVecPrivilege();
	for(auto iter=VecCtrlPrivilege.begin();iter!=VecCtrlPrivilege.end();++iter)
	{
		int nPrivilege=*iter;
		itemCtrlPrivilege.append(nPrivilege);
	}

	itemCtrl["privilege"]=itemCtrlPrivilege;
	root["privilege ctrl"]=itemCtrl;
	//////////////////////////////////////////////////////////////////////////
	Json::Value arrayLogin;
	Json::Value itemLogin;
	itemLogin["type"]=Json::Value(pPower->GetPrivilegeLogin().GetType());

	Json::Value itemLoginPrivilege;
	VEC_PRIVILEGE& VecLoginPrivilege=pPower->GetPrivilegeLogin().GetVecPrivilege();
	for(auto iter=VecLoginPrivilege.begin();iter!=VecLoginPrivilege.end();++iter)
	{
		int nPrivilege=*iter;
		itemLoginPrivilege.append(nPrivilege);
	}

	itemLogin["privilege"]=itemLoginPrivilege;
	root["privilege login"]=itemLogin;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToDelUser(CString szUserName,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("DEL");
	root["user"]=Json::Value(W2A(szUserName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToObtainStore(int nUserID,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["ID"]=Json::Value(nUserID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToDelStoreList(XStoreListInfo* pListInfo,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	//USES_CONVERSION;
	root["utype"]=Json::Value("DEL");
	root["ID"]=Json::Value(pListInfo->GetUserID());
	root["term NO"]=Json::Value(pListInfo->GetNodeID());

	int nNodeType=0;
	if(pListInfo->GetNodeType()==NODETYPE_IN)
	{
		nNodeType=0;
	}
	else if(pListInfo->GetNodeType()==NODETYPE_OUT)
	{
		nNodeType=2;
	}
	root["type"]=Json::Value(nNodeType);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAddStoreList(XNode* pNode,int nUserID,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("ADD");
	root["ID"]=Json::Value(nUserID);
	root["term NO"]=Json::Value(pNode->GetNodeID());
	root["type"]=Json::Value((int)pNode->GetNodeType());
	root["name"]=Json::Value(W2A(pNode->GetNodeName()));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetAllNode(CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("LIST");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetDeviceInfo(CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["get"]=Json::Value();

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetNodeByChannel(CString &szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["get"]=Json::Value();

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetNodeInfo(XNodeManage* pNodeManage,CString &szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	VEC_PART& VecChannel=pNodeManage->GetVecChannel();
	for(auto iter=VecChannel.begin();iter!=VecChannel.end();++iter)
	{
		int nChannel=*iter;
		nChannel+=1;
		value["query channel"].append(nChannel);
	}
	
	root["get"]=value;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetNodeDetailInfo(int nNodeID,CString &szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["term NO"]=Json::Value(nNodeID);
	//自定义
	root["query type"]=Json::Value("NODEONLINE");//自定义标志 获取在线节点

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetNodeAllDetailInfo(int nNodeID,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["term NO"]=Json::Value(nNodeID);
	//自定义
	root["query type"]=Json::Value("NODEALL");//自定义标志 获取全部节点

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToUpdataNodeGroup(int nNodeID,int nGroupID,int nMark,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("UPDATE");
	root["term NO"]=Json::Value(nNodeID);
	root["group"]=Json::Value(nGroupID);
	root["update mark"]=Json::Value(nMark);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToUpdataNodeMaster(int nNodeID,int nMaster,int nMark,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["utype"]=Json::Value("UPDATE");
	root["term NO"]=Json::Value(nNodeID);
	root["master"]=Json::Value(nMaster);
	root["update mark"]=Json::Value(nMark);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetNodeStatus(XNodeManage* pNodeManage,CString &szData)
{
	Json::Value root;  
	Json::FastWriter write;

	VEC_PART& VecNodeStatus=pNodeManage->GetVecNodeStatus();
	for(auto iter=VecNodeStatus.begin();iter!=VecNodeStatus.end();++iter)
	{
		int nNodeID=*iter;
		root["query term"].append(nNodeID);
	}

	//自定义
	root["flag"]=Json::Value("NODEALL");//全部节点
	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetNodeStatus(int nNodeID1,int nNodeID2,CString &szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["query term"].append(nNodeID1);
	root["query term"].append(nNodeID2);

	//自定义
	root["flag"]=Json::Value("TAKEOVER");//拖拽接管两个节点

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetLoginUser(CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["get"]=Json::Value();

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetLoginUserStatus(XNodeManage* pNodeManage,CString &szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	VEC_PART& VecLoginUser=pNodeManage->GetVecLoginUser();
	for(auto iter=VecLoginUser.begin();iter!=VecLoginUser.end();++iter)
	{
		int nUserID=*iter;
		value["query user id"].append(nUserID);
	}

	root["get"]=value;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetLoginUserStatus(int nUserID,CString& szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	value["query user id"].append(nUserID);
	root["get"]=value;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToNodeLogin(int nNodeID,CString szUSerName,CString& szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	USES_CONVERSION;
	root["user"]=Json::Value(W2A(szUSerName));
	root["term NO"]=Json::Value(nNodeID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToNodeLogOut(int nNodeID,CString& szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	root["term NO"]=Json::Value(nNodeID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToTakeOver(int nNodeID,int nTargetID,BOOL bExclusive,CString& szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	root["term NO"]=Json::Value(nNodeID);
	root["target term NO"]=Json::Value(nTargetID);
	root["exclusive"]=Json::Value(bExclusive);


	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToTakeOverCancel(int nNodeID,CString& szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	root["term NO"]=Json::Value(nNodeID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToPreview(int nNodeID,int nTargetID,CString& szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	root["term NO"]=Json::Value(nNodeID);
	root["target term NO"]=Json::Value(nTargetID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterNodeName(int nNodeID,CString szNodeName,CString& szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	USES_CONVERSION;
	root["term NO"]=Json::Value(nNodeID);
	root["term name"]=Json::Value(W2A(szNodeName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterAudioModel(int nNodeID,int nAudioModel,CString& szData)
{
	Json::Value root;  
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);

	std::string strKey(CW2A(szKey.GetString()));

	value1["audio mode"]=Json::Value(nAudioModel);
	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("AUDIO_MODEL");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterAudioSrc(int nNodeID,int nAudioSrc,CString& szData)
{
	Json::Value root;
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);

	std::string strKey(CW2A(szKey.GetString()));

	value1["audio src"]=Json::Value(nAudioSrc);
	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("AUDIO_SRC");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterHidModel(int nNodeID,int nHidModel,CString& szData)
{
	Json::Value root;
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);

	std::string strKey(CW2A(szKey.GetString()));

	value1["hid mode"]=Json::Value(nHidModel);
	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("HID_MODEL");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterSplitScreenModel(int nNodeID,int nScreenModel,CString& szData)
{
	Json::Value root;
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);

	std::string strKey(CW2A(szKey.GetString()));

	value1["screen mode"]=Json::Value(nScreenModel);
	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("SCREEN_MODEL");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterResoluationIndex(int nNodeID,int nResIndex,CString& szData)
{
	Json::Value root;  
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);

	std::string strKey(CW2A(szKey.GetString()));

	value1["out resV"]=Json::Value(nResIndex);
	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("RESOLUATION");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterOutModel(int nNodeID,int nOutModel,CString& szData)
{
	Json::Value root;  
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);

	std::string strKey(CW2A(szKey.GetString()));

	value1["out mode"]=Json::Value(nOutModel);
	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("OUT_MODEL");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterBindCfg(int nNodeID,int nBindCfg,CString& szData)
{
	Json::Value root;
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);

	std::string strKey(CW2A(szKey.GetString()));

	value1["bind cfg"]=Json::Value(nBindCfg);
	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("BIND_CFG");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterBindNodeID(int nNodeID,int nBindNodeID,CString& szData)
{
	Json::Value root;
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);

	std::string strKey(CW2A(szKey.GetString()));

	value1["bind term"]=Json::Value(nBindNodeID);
	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("BIND_NODEID");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToAlterHotKey(int nNodeID,MAP_HOTKEY& HotKey,CString& szData)
{
	Json::Value root;
	Json::Value value1;
	Json::Value value2;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("term_%d"),nNodeID);
	std::string strKey(CW2A(szKey.GetString()));

	//现在三个热键 循环三次
	for(auto& hotkey:HotKey)
	{
		XKeyValue* pKeyValue=hotkey.second;
		unsigned short nValue1=pKeyValue->m_KeyValue1;
		unsigned short nValue2=pKeyValue->m_KeyValue2;

		value1["osd ctrl key cfg"].append(nValue1);
		value1["osd ctrl key cfg"].append(nValue2);
	}

	value1["osd ctrl key cfg"].append(0);
	value1["osd ctrl key cfg"].append(0);

	value2[strKey]=value1;
	root["cfg term"]=value2;

	//自定义
	root["flag"]=Json::Value("ALTER");//改变节点属性
	root["sub type"]=Json::Value("HOTKEY");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonToGetMatrixStatus(CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["get"]=Json::Value();

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonMatrix(int nInNodeChannel,int nOutNodeChannel,CString& szData)
{
	Json::Value root;  
	Json::Value value1;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("ch_%d"),nInNodeChannel);
	std::string strKey(CW2A(szKey.GetString()));

	value1[strKey].append(nOutNodeChannel);
	root["matrix list"]=value1;

	//自定义
	root["matrix type"]=Json::Value("MATRIXONE");//自定义标志 单个切换

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonMatrix(XNodeManage* pNodeManage,int nInputChannel,CString &szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	CString szKey;
	szKey.Format(_T("ch_%d"),nInputChannel);
	std::string strKey(CW2A(szKey.GetString()));

	MAP_NODE& MapNode=pNodeManage->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			value[strKey].append(pNode->GetChannel());
		}
	}

	root["matrix list"]=value;

	//自定义
	root["matrix type"]=Json::Value("MATRIXALL");//自定义标志 osd底图 切给所有输出

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonOSDImage(XNodeManage* pNodeManage,int nIndex,CString &szData)
{
	Json::Value root;  
	Json::Value value;
	Json::FastWriter write;

	root["OSD pic"]=Json::Value(nIndex);

	MAP_NODE& MapNode=pNodeManage->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			value.append(pNode->GetChannel());
		}
	}

	root["term CH list"]=value;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonHideOSDImage(int nShow,int nChaannel,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["OSD show"]=Json::Value(nShow);
	root["term CH list"].append(nChaannel);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonReadNodeGroup(CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["connect"]=Json::Value(0);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonReadOnLineNodeGroup(CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["connect"]=Json::Value(1);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonNodeGroupInfo(int nNodeGroupID,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["tgroup ID"]=Json::Value(nNodeGroupID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonUpdataSeatArrage(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("UPDATE");
	root["tgroup ID"]=Json::Value(nodeGroupInfo.GetGroupID());
	root["name"]=Json::Value(W2A(nodeGroupInfo.GetGroupName()));
	root["master"]=Json::Value(nodeGroupInfo.GetMaster());
	root["ginfo"]=Json::Value(W2A(nodeGroupInfo.GetArray()));
	root["gmatrix"]=Json::Value(W2A(nodeGroupInfo.GetMatrix()));

	//自定义
	root["update mark"]=Json::Value(UPDATAMAKE_GROUPARRAGE);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonUpdataMasterSeatArrage(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("UPDATE");
	root["mgroup ID"]=Json::Value(nodeGroupInfo.GetGroupID());
	root["name"]=Json::Value(W2A(nodeGroupInfo.GetGroupName()));
	root["master"]=Json::Value(nodeGroupInfo.GetMaster());
	root["ginfo"]=Json::Value(W2A(nodeGroupInfo.GetArray()));
	root["gmatrix"]=Json::Value(W2A(nodeGroupInfo.GetMatrix()));

	//自定义
	root["update mark"]=Json::Value(UPDATAMAKE_MASTERARRAGE);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonAddSeatArrage(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("ADD");
	root["name"]=Json::Value(W2A(nodeGroupInfo.GetGroupName()));
	root["type"]=Json::Value(nodeGroupInfo.GetType());
	root["master"]=Json::Value(nodeGroupInfo.GetMaster());
	root["ginfo"]=Json::Value(W2A(nodeGroupInfo.GetArray()));
	root["gmatrix"]=Json::Value(W2A(nodeGroupInfo.GetMatrix()));
	root["creator ID"]=Json::Value(nodeGroupInfo.GetCreatorID());
	root["create mode"]=Json::Value((int)nodeGroupInfo.GetCreateMode());

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonMainAndSecondList(CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root[""]=Json::Value();

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonQueryMainAndSecond(int nGroupID,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["mgroup ID"]=Json::Value(nGroupID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonAddMainAndSecond(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("ADD");
	root["name"]=Json::Value(W2A(nodeGroupInfo.GetGroupName()));
	root["master"]=Json::Value(nodeGroupInfo.GetMaster());
	root["ginfo"]=Json::Value(W2A(nodeGroupInfo.GetArray()));
	root["gmatrix"]=Json::Value(W2A(nodeGroupInfo.GetMatrix()));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonDelNodeGroup(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("DEL");
	root["name"]=Json::Value(W2A(nodeGroupInfo.GetGroupName()));
	root["tgroup ID"]=Json::Value(nodeGroupInfo.GetGroupID());

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonDelNodeGroupMainSecond(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("DEL");
	root["name"]=Json::Value(W2A(nodeGroupInfo.GetGroupName()));
	root["mgroup ID"]=Json::Value(nodeGroupInfo.GetGroupID());

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonUpdataNodeGroupName(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("UPDATE");
	root["tgroup ID"]=Json::Value(nodeGroupInfo.GetGroupID());
	root["name"]=Json::Value(W2A(nodeGroupInfo.GetGroupName()));

	//自定义
	root["update mark"]=Json::Value(UPDATAMAKE_GROUPNAME);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonUpdataMasterNodeGroupName(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("UPDATE");
	root["mgroup ID"]=Json::Value(nodeGroupInfo.GetGroupID());
	root["name"]=Json::Value(W2A(nodeGroupInfo.GetGroupName()));

	//自定义
	root["update mark"]=Json::Value(UPDATAMAKE_MASTERNAME);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonUpdataSeatMasterNode(XNodeGroupInfo& nodeGroupInfo,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("UPDATE");
	root["tgroup ID"]=Json::Value(nodeGroupInfo.GetGroupID());
	root["master"]=Json::Value(nodeGroupInfo.GetMaster());

	//自定义
	root["update mark"]=Json::Value(UPDATAMAKE_GROUPMASTER);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonRefreashGroup(int nGroupID,CString& szData)
{
	Json::Value root;  
	Json::FastWriter write;

	root["utype"]=Json::Value("REFRESH");
	root["tgroup ID"]=Json::Value(nGroupID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonRefreashMainSecGroup(int nGroupID,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["utype"]=Json::Value("REFRESH");
	root["mgroup ID"]=Json::Value(nGroupID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonSystemStatu(CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["get"]=Json::Value();

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonBlink(CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	auto& VecBlink=XConstantData::GetInstance()->GetVecBlinkNodeID();
	for(auto nodeID:VecBlink)
	{
		root["blink term"].append(nodeID);
	}

	//自定义
	root["flag"]=Json::Value(_T("BLINK"));
	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonGetNetConfig(CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["get"]=Json::Value();
	root["type"]=Json::Value("QUERY");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonApplyNetConfig(XNetConfig& config,CString& szData)
{
	Json::Value root;
	Json::Value value;
	Json::FastWriter write;

	USES_CONVERSION;
	value["ip"]=Json::Value(W2A(config.GetIP()));
	value["port"]=Json::Value(config.GetPort());
	value["mask"]=Json::Value(W2A(config.GetMask()));
	value["gateway"]=Json::Value(W2A(config.GetGateway()));
	value["apply"]=Json::Value(true);
	value["save"]=Json::Value(false);


	root["set"]=value;
	root["type"]=Json::Value("APPLY");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonSaveNetConfig(XNetConfig& config,CString& szData)
{
	Json::Value root;
	Json::Value value;
	Json::FastWriter write;

	USES_CONVERSION;
	value["ip"]=Json::Value(W2A(config.GetIP()));
	value["port"]=Json::Value(config.GetPort());
	value["mask"]=Json::Value(W2A(config.GetMask()));
	value["gateway"]=Json::Value(W2A(config.GetGateway()));
	value["apply"]=Json::Value(false);
	value["save"]=Json::Value(true);


	root["set"]=value;
	root["type"]=Json::Value("SAVE");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonLightControl(int nIndex,int nStatus,CString& szData)
{
	Json::Value root;
	Json::Value value;
	Json::FastWriter write;

	CString szControl;
	szControl.Format(_T("%s:%d,%d"),_T("control light"),nIndex,nStatus);

	USES_CONVERSION;
	root["data type"]=Json::Value("string");
	root["term NO"]=Json::Value(56);
	root["port"]=Json::Value(2);
	root["str"]=Json::Value(W2A(szControl));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonLogByData(XLogPack& logPack,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["date"]=Json::Value((int)logPack.m_time);
	root["key"]=Json::Value("ALL");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonLogByUser(XLogPack& logPack,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["date"]=Json::Value((int)logPack.m_time);
	root["key"]=Json::Value("USER");
	root["user"]=Json::Value(W2A(logPack.m_szUserName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonLogByNode(XLogPack& logPack,CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["date"]=Json::Value((int)logPack.m_time);
	root["key"]=Json::Value("TERM ID");
	root["term ID"]=Json::Value(W2A(logPack.m_szRealName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonRTCTime(CString& szData)
{
	TIME_ZONE_INFORMATION tziTime;
	ZeroMemory(&tziTime,sizeof(tziTime));
	GetTimeZoneInformation(&tziTime);
	int nZoon=tziTime.Bias/(-60);

	CTime time=CTime::GetCurrentTime();
	time_t t=time.GetTime();

	Json::Value root;
	Json::Value value;
	Json::FastWriter write;

	value["rtc sec"]=Json::Value((int)t);
	value["zoon"]=Json::Value(nZoon);

	root["set"]=value;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonNotifyMonitor(CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["notify"]=Json::Value("TCP");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonObtainRootFolder(CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["ID"]=Json::Value(0);
	root["subType"]=Json::Value("ROOT");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonObtainSubFolder(CString& szData,int nID)
{
	Json::Value root;
	Json::FastWriter write;

	root["utype"]=Json::Value("QUERY");
	root["ID"]=Json::Value(nID);
	root["subType"]=Json::Value("CHILD");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonDeleteFolder(CString& szData,int nID)
{
	Json::Value root;
	Json::FastWriter write;

	root["utype"]=Json::Value("DEL");
	root["ID"]=Json::Value(nID);
	//root["subType"]=Json::Value("CHILD");

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonAddFolder(CString& szData,XSubFolder& sub)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("ADD");
	root["PID"]=Json::Value(sub.GetParentID());
	root["name"]=Json::Value(W2A(sub.GetName()));
	root["type"]=Json::Value(sub.GetType());

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonObtainSplit(CString& szData)
{
	Json::Value root;
	Json::FastWriter write;

	root["utype"]=Json::Value("LIST");
	root["index"]=Json::Value(0);
	root["len"]=Json::Value(32);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonQuerySplitWall(CString& szData,CString szName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("QUERY");
	root["wall name"]=Json::Value(W2A(szName));


	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonAddSplitWall(CString& szData,XSplitResult& splitInfo)
{
	Json::Value root;
	Json::Value value;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("ADD");
	root["wall name"]=Json::Value(W2A(splitInfo.m_szSplitName));

	value["id"]=Json::Value(splitInfo.m_nSplitID);
	value["cut_use"]=Json::Value(splitInfo.m_nCutUse);

	auto& VecCutPix=splitInfo.m_VecCutPix;
	for(auto cutPix:VecCutPix)
	{
		value["cut_pix"].append(cutPix);
	}
	
	value["output_n"]=Json::Value(splitInfo.m_nPixIndex);
	value["output_h"]=Json::Value(splitInfo.m_nReaulationH);
	value["output_v"]=Json::Value(splitInfo.m_nReaulationV);
	value["screen_num_h"]=Json::Value(splitInfo.m_nScreenCountX);
	value["screen_num_v"]=Json::Value(splitInfo.m_nScreenCountY);

	auto& VecSplitCh=splitInfo.m_VecSplitCh;
	for(auto& splitCh:VecSplitCh)
	{
		value["screen_mch_list"].append(splitCh);
	}

	root["wall_obj"]=value;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonRefreashSplit(CString& szData,CString szName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("REFRESH");
	root["wall name"]=Json::Value(W2A(szName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonDraw(CString& szData,CString szName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("DRAW");
	root["wall name"]=Json::Value(W2A(szName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonDelSplit(CString& szData,CString szName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("DEL");
	root["wall name"]=Json::Value(W2A(szName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonObtainSplitWindow(CString& szData,CString szName,BOOL bFirst)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("LIST");
	root["wall name"]=Json::Value(W2A(szName));
	root["index"]=Json::Value(0);
	root["len"]=Json::Value(128);

	if(bFirst)
		root["Subtype"]=Json::Value("FIRST");
	else
		root["Subtype"]=Json::Value("NOFIRST");
	
	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonObtainSplitWindowInfo(CString& szData,CString szSplitName,int nSignalID)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("QUERY");
	root["wall name"]=Json::Value(W2A(szSplitName));
	root["ID"]=Json::Value(nSignalID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonAddSignal(CString& szData,CString szName,XSignal& signal)
{
	Json::Value root;
	Json::Value value;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("ADD");
	root["wall name"]=Json::Value(W2A(szName));

	value["id"]=Json::Value(signal.GetSignalID());
	value["input_ch"]=Json::Value(signal.GetInputCh());
	value["cut_use"]=Json::Value(signal.GetCutUse());

	auto& VecCutUse=signal.GetVecCutPix();
	for(auto& cutPix:VecCutUse)
	{
		value["cut_pix"].append(cutPix);
	}

	RECTF rect=signal.GetRealRect();

	int nX1=(int)rect.X;
	int nX2=(int)(rect.X+rect.Width-1);
	int nY1=(int)rect.Y;
	int nY2=(int)(rect.Y+rect.Height-1);

	value["pos"].append(nX1);
	value["pos"].append(nX2);
	value["pos"].append(nY1);
	value["pos"].append(nY2);

	value["level"]=Json::Value(0);

	root["win_obj"]=value;

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonDelSignal(CString& szData,CString szSplitName,int nSignalID)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("DEL");
	root["wall name"]=Json::Value(W2A(szSplitName));
	root["ID"]=Json::Value(nSignalID);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonCLearSignal(CString& szData,CString szSplitName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("CLEAR");
	root["wall name"]=Json::Value(W2A(szSplitName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonLevelUseList(CString& szData,CString szSplitName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("LEVEL_USE");
	root["wall name"]=Json::Value(W2A(szSplitName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonAlterLevel(CString& szData,CString szSplitName,XSignalLevel& level)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("WIN_LEVEL");
	root["wall name"]=Json::Value(W2A(szSplitName));
	root["ID"]=Json::Value(level.m_nSignalID);
	root["act"]=Json::Value(W2A(level.m_szType));

	if(level.m_szType==_T("SET"))
		root["level"]=Json::Value(level.m_nLevel);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonObtainSplitScene(CString& szData)
{
	Json::Value root;
	Json::FastWriter write;


	root["utype"]=Json::Value("LIST");
	root["index"]=Json::Value(0);
	root["len"]=Json::Value(16);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonObtainWallList(CString& szData,CString szSceneName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("LIST_WALL");
	root["scene_name"]=Json::Value(W2A(szSceneName));
	root["index"]=Json::Value(0);
	root["len"]=Json::Value(16);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonOpenScene(CString& szData,CString szSceneName,CString szWallName,int nOpt)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("RECALL_WALL");
	root["scene_name"]=Json::Value(W2A(szSceneName));
	root["wall_name"]=Json::Value(W2A(szWallName));
	root["opt"]=Json::Value(nOpt);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonQuerySceneWall(CString& szData,CString szSceneName,CString szWallName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("QUERY_WALL");
	root["scene_name"]=Json::Value(W2A(szSceneName));
	root["wall_name"]=Json::Value(W2A(szWallName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonSplitScene(CString& szData,CString szSceneName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("ADD");
	root["scene_name"]=Json::Value(W2A(szSceneName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonSaveWallToNewScene(CString& szData,CString szSceneName,CString szSplit,BOOL bLast)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("SAVE_WALL");
	root["scene_name"]=Json::Value(W2A(szSceneName));
	root["wall_name"]=Json::Value(W2A(szSplit));
	if(bLast)
		root["last"]=Json::Value(1);
	else
		root["last"]=Json::Value(0);


	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonObtainSceneGroup(CString& szData,CString szSceneName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("GET_GROUP");
	root["scene_name"]=Json::Value(W2A(szSceneName));

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonSetSceneGroup(CString& szData,CString szSceneName,CString& szGroup,BOOL bAlter)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("SET_GROUP");
	root["scene_name"]=Json::Value(W2A(szSceneName));
	root["group"]=Json::Value(W2A(szGroup));

	if(bAlter)
		root["alter"]=Json::Value(1);
	else
		root["alter"]=Json::Value(0);

	std::string str=write.write(root);
	szData=str.c_str();
}

void XJsonManage::WriteJsonDeleteSplitScene(CString& szData,CString szSceneName)
{
	Json::Value root;
	Json::FastWriter write;

	USES_CONVERSION;
	root["utype"]=Json::Value("DEL");
	root["scene_name"]=Json::Value(W2A(szSceneName));

	std::string str=write.write(root);
	szData=str.c_str();
}