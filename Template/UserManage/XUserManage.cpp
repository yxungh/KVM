#include "stdafx.h"
#include "XUserManage.h"
#include "XLogin.h"
#include "XMessageBox.h"
#include "XLoginLoad.h"
#include "XLoginInfo.h"
#include "XJsonManage.h"
#include "XDelegateUserManage.h"
#include "XSendDataManage.h"
#include "XResult.h"
#include "XPowerManage.h"
#include "XPower.h"
#include "XSubUserInfo.h"
#include "XStoreListInfo.h"
#include "XUpdateUserInfo.h"
#include "XChart.h"
#include "XStoreList.h"
#include "XFolder.h"
#include "XFolderResult.h"
#include "XFolderInfo.h"



XUserManage::XUserManage()
{
	InitializeCriticalSection(&m_CS);
}

XUserManage::~XUserManage()
{
	ClearMapPower();
	ClearMapSubUser();
	ClearMapStore();
	ClearUserAll();
	ClearUserIDAll();
	ClearMapRoot();
	ClearMapSubFolder();
	StopSubFolderThread();
	DeleteCriticalSection(&m_CS);
}

void XUserManage::ClearMapSubFolder()
{
	for(auto& map:m_MapSubFolder)
	{
		delete map.second;
	}
	m_MapSubFolder.clear();
}

void XUserManage::ClearMapRoot()
{
	for(auto& root:m_MapRootFolder)
	{
		delete root.second;
	}
	m_MapRootFolder.clear();
}

void XUserManage::ClearMapPower()
{
	for(auto iter=m_MapPower.begin();iter!=m_MapPower.end();++iter)
	{
		delete iter->second;
	}
	m_MapPower.clear();
}

void XUserManage::ClearMapSubUser()
{
	for(auto iter=m_MapSubUser.begin();iter!=m_MapSubUser.end();++iter)
	{
		delete iter->second;
	}
	m_MapSubUser.clear();
}

void XUserManage::ClearMapStore()
{
	for(auto iter=m_MapStore.begin();iter!=m_MapStore.end();++iter)
	{
		delete iter->second;
	}
	m_MapStore.clear();
}

void XUserManage::ClearUserAll()
{
	m_VecUserAll.clear();
}
void XUserManage::ClearUserIDAll()
{
	m_VecUserIDAll.clear();
}

void XUserManage::ClearUserIDALL()
{
	ClearUserAll();
	ClearUserIDAll();
}

void XUserManage::SetLoginUser(CString szUserName,CString szPassWd)
{
	m_szLoginUser=szUserName;
	m_szLoginPassWd=szPassWd;
}

MAP_POWER& XUserManage::GetMapPower()
{
	return m_MapPower;
}

MAP_NODE& XUserManage::GetMapNode()
{
	return m_pDelegate->GetMapNode();
}

MAP_NODEALL& XUserManage::GetMapNodeAll()
{
	return m_pDelegate->GetMapNodeAll();
}

MAP_SUBUSER& XUserManage::GetMapSubUser()
{
	return m_MapSubUser;
}

MAP_STORE& XUserManage::GetMapStore()
{
	return m_MapStore;
}

void XUserManage::SetUserName(CString szName)
{
	m_pDelegate->SetCurUserName(szName);
}

void XUserManage::SetUserID(int n)
{
	m_pDelegate->SetCurUserID(n);
}

CString XUserManage::GetUserName()
{
	return m_pDelegate->GetCurUserName();
}

int XUserManage::GetUserID()
{
	return m_pDelegate->GetCurUserID();
}

void XUserManage::SetLogin(BOOL b)
{
	m_pDelegate->SetLogin(b);
	m_bLogin=b;
}

BOOL XUserManage::GetLogin()
{
	return m_pDelegate->GetLogin();
}

//////////////////////////////////////////////////////////////////////////
void XUserManage::OperateOfLogin()
{
	XLogin dlg;

	m_pLogin=&dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();

	m_pLogin=NULL;
}

void XUserManage::OperateOfPowerManage()
{
	//����RTCʱ��
	XSendDataManage::GetInstance()->AddSendDataOfRTCTime();

	XPowerManage dlg;

	m_pPowerManage=&dlg;
	dlg.SetDelegate(this);
	dlg.DoModal();

	m_pPowerManage=NULL;
}

void XUserManage::OperateOfLoginOut()
{
	//TRACE(_T("LoginOut\n"));
	if(GetLogin())
	{
		XSendDataManage::GetInstance()->AddSendDataOfLoginOut(GetUserName());
	}
}

void XUserManage::ObtainSubUserPower()
{
	for(auto iter=m_MapSubUser.begin();iter!=m_MapSubUser.end();++iter)
	{
		CString szSubUserName=iter->first;
		XSubUserInfo* pSubUser=iter->second;
		int nID=pSubUser->GetID();
		XSendDataManage::GetInstance()->SendDataOfObtainSubUserPower(nID);
		//XSendDataManage::GetInstance()->SendDataOfObtainUserPower(szSubUserName);
	}
}

void XUserManage::OperateOfFolder()
{
	XFolder dlg;
	dlg.SetManage(this);
	m_pFolder=&dlg;

	dlg.DoModal();
	m_pFolder=NULL;
}

//////////////////////////////////////////////////////////////////////////
//Ҫ����
void XUserManage::ClearMapTempSubFolder()
{
	EnterCriticalSection(&m_CS);
	m_MapTempSubFolder.clear();
	LeaveCriticalSection(&m_CS);
}

void XUserManage::InsetTempSubFolder(int nID,CString szName)
{
	EnterCriticalSection(&m_CS);
	m_MapTempSubFolder.insert(std::pair<int,CString>(nID,szName));
	LeaveCriticalSection(&m_CS);
}

void XUserManage::ObtainSubFolderInfo()
{
	EnterCriticalSection(&m_CS);

	//int nSize=m_MapTempSubFolder.size();
	//if(nSize!=0)
		//TRACE(_T("nSize=%d\n"),m_MapTempSubFolder.size());

	for(auto& folder:m_MapTempSubFolder)
	{
		int nID=folder.first;
		XSendDataManage::GetInstance()->AddSendDataOfObtainSubFolder(nID);
	}
	//ѭ���� ��Ϊ��
	m_MapTempSubFolder.clear();
	LeaveCriticalSection(&m_CS);
}

void XUserManage::SetThreadRun()
{
	if(m_MapTempSubFolder.size()==0)
	{
		m_bRunning=FALSE;
	}
}

static UINT SendSubFolderThread(void* p)
{
	XUserManage* pManage=(XUserManage*)p;
	while(pManage->m_bRunning)
	{
		pManage->ObtainSubFolderInfo();
	}

	if(NULL!=pManage->m_ThreadEvent)
	{
		SetEvent(pManage->m_ThreadEvent);
	}
	return 0;
}

BOOL XUserManage::BeginSubFolderThread()
{
	//�����ļ�������
	if(!m_bRunning)
	{
		m_bRunning=TRUE;
		m_ThreadEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
		if(NULL!=m_ThreadEvent)
		{
			CWinThread* pThread=AfxBeginThread((AFX_THREADPROC)SendSubFolderThread,(void*)this);
			if(NULL==pThread)
			{
				CloseSubFolderThreadEvent();
				m_bRunning=FALSE;
			}
		}
		else
		{
			m_bRunning=FALSE;
		}
	}

	return m_bRunning;
}

void XUserManage::StopSubFolderThread()
{
	m_bRunning=FALSE;
	if(m_ThreadEvent!=NULL)
	{
		WaitForSingleObject(m_ThreadEvent,INFINITE);
		CloseHandle(m_ThreadEvent);
		m_ThreadEvent=NULL;
	}
}

void XUserManage::CloseSubFolderThreadEvent()
{
	if(m_ThreadEvent!=NULL)
	{
		CloseHandle(m_ThreadEvent);
		m_ThreadEvent=NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
void XUserManage::ObtainSubFolder()
{
	//���ݸ��ڵ� �ж��߳̽���
	for(auto rootFolder:m_MapRootFolder)
	{
		XFolderInfo* pInfo=rootFolder.second;
		XSendDataManage::GetInstance()->AddSendDataOfObtainSubFolder(pInfo->GetID());
	}
}
static UINT SendFolderThread(void* p)
{
	//�������ļ��кͽڵ�
	XUserManage* pManage=(XUserManage*)p;
	pManage->ObtainSubFolder();

	return 0;
}

BOOL XUserManage::BeginRootFolderThread()
{
	//�������ļ�������
	AfxBeginThread((AFX_THREADPROC)SendFolderThread,(void*)this);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void XUserManage::OperateOfReLogin(char* pData)
{
	XLoginInfo UserInfo;
	XJsonManage::GetInstance()->ParseJsonToLogin(pData,UserInfo);

	//TRACE(_T("result=%d\n"),UserInfo.GetResult());

	switch(UserInfo.GetResult())
	{
		//�����¼Ӽ��ܵ�¼ ����ֵΪ1
		case 1:
		case 2:
		case KVM_ERR_USER_ALREADY_LOGIN:
			{
				if(m_szLoginUser==UserInfo.GetUserName()&&
				   m_szLoginPassWd==UserInfo.GetPassWd())
				{
					//��½�ɹ�
					SetLogin(TRUE);
					SetUserName(UserInfo.GetUserName());
					SetUserID(UserInfo.GetUserID());

					//m_pDelegate->SetStatusBarInfo();
					m_pLogin->SetDlgStatus(FALSE);
					m_pLogin->OnOk();

					//�����ϯ
					m_pDelegate->Operate(OPERATETYPE_ADDSEAT,NULL);

					//��ȡȫ���û�
					XSendDataManage::GetInstance()->AddSendDataOfObtainAllUser();

					//��ȡ��ǰ�û�Ȩ��
					XSendDataManage::GetInstance()->SendDataOfObtainUserPower(UserInfo.GetUserName());
					//��ȡ���û��б�
					//�û�̫��Ļ���Ҫ��ҳ��ȡ(��ʱ����ҳ)
					XSendDataManage::GetInstance()->AddSendDataOfObtainUserList(0,0);
					//��ȡ�ղ��б�(Ĭ�ϲ�ѯ��¼�û��б�)
					XSendDataManage::GetInstance()->AddSendDataOfObtainStoreList(UserInfo.GetUserID());

					//��ȡȫ���ڵ��б����ߺͲ����ߣ�
					m_pDelegate->Operate(OPERATETYPE_ALLNODE,NULL);
					//��ȡ�豸ͨ������
					m_pDelegate->Operate(OPERATETYPE_DEVICEINFO,NULL);
					//��ѯ�ڵ�����״̬���������߽ڵ�
					//m_pDelegate->Operate(OPERATETYPE_GETNODECHANNEL,NULL);
					//��ȡ��¼�û�����
					m_pDelegate->Operate(OPERATETYPE_GETLOGINUSER,NULL);
					//��ȡ�����л�״̬
					m_pDelegate->Operate(OPERATETYPE_MATRIXSTATUS,NULL);
					//��ȡȫ���ڵ���
					m_pDelegate->Operate(OPERATETYPE_READNODEGROUP,NULL);
					//��ȡ���߽ڵ���
					m_pDelegate->Operate(OPERATETYPE_READONLINENODEGROUP,NULL);
					//��ȡ�������б�
					m_pDelegate->Operate(OPERATETYPE_GETMAINANDSECOND,NULL);
					//��ȡ�ļ���(�����߳�)
					//BeginRootThread();
					XSendDataManage::GetInstance()->AddSendDataOfObtainRootFolder();
					//��ʼ���������б�
					m_pDelegate->Operate(OPERATETYPE_INITSCENE,NULL);
					//��ȡƴ��ǽ�б�
					m_pDelegate->Operate(OPERATETYPE_GETSPLITWALL,NULL);
					//��ȡƴ�ӳ���
					m_pDelegate->Operate(OPERATETYPE_SPLITSCENE,NULL);



					////��¼�ɹ���ʼ��������Ļ����
					//m_pDelegate->Operate(OPERATETYPE_INITMATRIXARRAY,NULL);
				
					//��ȡ�豸�������
					//m_pDelegate->Operate(OPERATETYPE_SYSTEMSTATUS,NULL)��

					//ʲô�ǲ����û�column����
				}
			}
			break;
		case KVM_ERR_USER_NOT_FOUND:
			{
				m_pLogin->KillTimer(1);
				m_pLogin->SetDlgStatus(TRUE);
				_M(_T("208"),_T("δ�ҵ��û���"),MB_OK);
			}
			break;
		case KVM_ERR_PASSWORD_MISMATCH:
			{
				m_pLogin->KillTimer(1);
				m_pLogin->SetDlgStatus(TRUE);
				_M(_T("209"),_T("�������"),MB_OK);
			}
			break;
		case KVM_ERR_USER_ALREADY_LOGIN_OTHER_IP:
			{
				m_pLogin->KillTimer(1);
				m_pLogin->SetDlgStatus(TRUE);
				_M(_T("210"),_T("���û��Ѿ���¼��"),MB_OK);
			}
			break;
		default:
			break;
	}
}


void XUserManage::OperateOfReLoginOut(char* pData)
{
	XResult result;
	XJsonManage::GetInstance()->ParseJsonToLoginOut(pData,result);

	if(result.GetResult()==0||
	   result.GetResult()==-1)
	{
		//ע��
		SetUserName(_T(""));
		SetUserID(0);
		SetLogin(FALSE);

		m_pDelegate->SetHardWareChannel(0);
		m_pDelegate->SetMatrixModel(_T(""));

		//��ռ���
		ClearMapPower();
		ClearMapSubUser();
		ClearMapStore();
		m_pDelegate->ClearNode();
		m_pDelegate->ClearNodeGroup();
		m_pDelegate->ClearPage();
		m_pDelegate->ClearTree();
		m_pDelegate->ClearConChannel();
		m_pDelegate->ClearUserLoginStatus();
		m_pDelegate->ClearUserIDALL();
		m_pDelegate->ClearCloumn();
		m_pDelegate->SaveData();
		m_pDelegate->ClearSceneTree();
		//���ƴ��ҳ��
		m_pDelegate->Operate(OPERATETYPE_CLEARSPLITVIEW,NULL);
	}
}

void XUserManage::OperateOfRePowerManage(char* pData)
{
	XUpdateUserInfo updateUserInfo;
	XJsonManage::GetInstance()->ParseJsonToPower(pData,this,updateUserInfo);

	if(updateUserInfo.GetType()==POWER_REDATA_LIST)
	{
		if(updateUserInfo.GetResult()==0)
		{
			//ת���û�ID
			m_VecUserIDAll.clear();
			int nIndex=0;
			for(auto iter=m_VecUserAll.begin();iter!=m_VecUserAll.end();++iter)
			{
				int nValue=*iter;
				for(int i=0;i<16;i++)
				{
					if((nValue&(1<<i))!=0)
					{
						int nUserID=i+(nIndex*16);
						nUserID+=1;

						m_VecUserIDAll.push_back(nUserID);
					}
				}
				nIndex++;
			}
		}
		//���û�����
		m_nUserALL=m_VecUserIDAll.size();
	}
	else if(updateUserInfo.GetType()==POWER_REDATA_QUERY)
	{
		if(updateUserInfo.GetResult()==0)
		{
			if(updateUserInfo.GetUserType()==_T("QUERY_CURUSER"))
			{

			}
			else if(updateUserInfo.GetUserType()==_T("QUERY_SUBUSER"))
			{
				//��¼�û������û���
				//���뵽�û����б�
				m_pDelegate->InsertItemToTree(updateUserInfo.GetUserName());
			}
			else if(updateUserInfo.GetUserType()==_T("QUERY_ADDUSER"))
			{
				m_pDelegate->InsertItemToTree(updateUserInfo.GetUserName());
				//�����û��б�
				m_pPowerManage->UpdateUserList(updateUserInfo.GetUserID(),updateUserInfo.GetUserName());
				m_pPowerManage->CloseAddUserDlg();
				m_pPowerManage->CloseCopyUserDlg();
			}
		}
	}
	else if(updateUserInfo.GetType()==POWER_REDATA_ADD)
	{
		switch(updateUserInfo.GetResult())
		{
			case KVM_DATABASE_DONE:
				{
					//��ȡ�����û�Ȩ��
					XSendDataManage::GetInstance()->SendDataOfObtainAddUserPower(updateUserInfo.GetUserID());
				}
				break;
			case KVM_ERR_USER_ALREADY_EXIST:
				{
					//�û��Ѿ�����
					_M(_T("212"),_T("�û��Ѿ����ڣ�"),MB_OK);
				}
				break;
			default:
				break;
		}
	}
	else if(updateUserInfo.GetType()==POWER_REDATA_DEL)
	{
		if(updateUserInfo.GetResult()==0)
		{
			CString szDelUserName=updateUserInfo.GetUserName();
			m_pPowerManage->DelUserFromMapAndList(szDelUserName);
			//���û�����ɾ��
			m_pDelegate->DeleteItemFromTree(szDelUserName);
		}
	}
	else if(updateUserInfo.GetType()==POWER_REDATA_UPDATE)
	{
		switch(updateUserInfo.GetResult())
		{
			case KVM_DATABASE_DONE:
				{
					//����ı� ����Ȩ���б�
					m_pPowerManage->UpdatePowerList(updateUserInfo.GetUserName());
					m_pPowerManage->CloseAlterUserDlg();

					//XSendDataManage::GetInstance()->SendDataOfObtainSubUserPower(updateUserInfo.GetUserID());
				}
				break;
			default:
				break;
		}
	}
}

void XUserManage::OperateOfReUserList(char* pData)
{
	//XSubUserInfo* pSubUser=new XSubUserInfo;
	XJsonManage::GetInstance()->ParseJsonToUserList(pData,m_MapSubUser);

	//�յ�����֮������������û�Ȩ��
	ObtainSubUserPower();
}

void XUserManage::OperateOfReStoreList(char* pData)
{
	//�����ղؼ���
	//ClearMapStore();
	XStoreList storeList;
	XJsonManage::GetInstance()->ParseJsonToStoreList(pData,m_MapStore,storeList);

	if(storeList.GetSendType()==STORE_REDATA_QUERY)
	{
		if(storeList.GetResult()==0)
		{
			//�����б�
			//TRACE(_T("Name=%s\n"),szUserName);
			if(NULL!=m_pPowerManage)
			{
				m_pPowerManage->UpdateStoreList();
				m_pPowerManage->SetQueryUserID(storeList.GetUserID());
				//TRACE(_T("UserID=%d\n"),storeList.GetUserID());
			}
		}
	}
	else if(storeList.GetSendType()==STORE_REDATA_ADD)
	{
		if(storeList.GetResult()==0)
		{
			if(NULL!=m_pPowerManage)
			{
				m_pPowerManage->UpdateStoreList();
				//m_pPowerManage->SetQueryUserID(storeList.GetUserID());
				//TRACE(_T("UserID=%d\n"),storeList.GetUserID());
			}
		}
	}
	else if(storeList.GetSendType()==STORE_REDATA_DEL)
	{
		if(storeList.GetResult()==0)
		{
			m_pPowerManage->DelStoreList(storeList.GetNodeID());
		}
	}
}

void XUserManage::OperateOfReRootFolder(char* pData)
{
	XFolderResult result;
	XJsonManage::GetInstance()->ParseJsonToFolder(pData,this,result);
	if(result.GetSendType()==_T("QUERY"))
	{
		if(result.GetSubType()==_T("ROOT"))
		{
			//TRACE(_T("Root\n"));
			//��ѯ��Ŀ¼ ���߳�������
			BeginRootFolderThread();
	
			//ͬʱ���������ļ����µ����ļ����߳�
			BeginSubFolderThread();
		}
		else if(result.GetSubType()==_T("CHILD"))
		{
			//TRACE(_T("Child\n"));
			//if(NULL!=m_pFolder)
			//{
			//	m_pFolder->InsetSubFolder();
			//}
		}
	}
	else if(result.GetSendType()==_T("DEL"))
	{
		if(result.GetResult()!=0)
			return;

		int nID=result.m_nID;
		if(NULL!=m_pFolder)
		{
			m_pFolder->DeleteFolderFromTree(nID);
		}
	}
	else if(result.GetSendType()==_T("ADD"))
	{
		if(result.GetResult()!=101)
			return;

		//�����ļ�����
		if(result.m_nParentID!=0)
		{
			XSendDataManage::GetInstance()->AddSendDataOfObtainSubFolder(result.m_nParentID);
		}
		else
		{
			XSendDataManage::GetInstance()->AddSendDataOfObtainSubFolder(result.m_nID);
		}

		//InsetTempSubFolder(result.m_nID,result.m_szFolderName);

		if(NULL!=m_pFolder)
		{
			m_pFolder->AddFolderToTree(result.m_szFolderName);
		}
	}
		 
}

//////////////////////////////////////////////////////////////////////////
void XUserManage::Operate(OPERATETYPE type,void* pData)
{
	switch(type)
	{
		case OPERATETYPE_LOGIN:
			{
				OperateOfLogin();
			}
			break;
		case OPERATETYPE_LOGINOUT:
			{
				OperateOfLoginOut();
			}
			break;
		case OPERATETYPE_POWER:
			{
				OperateOfPowerManage();
			}
			break;
		case OPERATETYPE_FOLDER:
			{
				OperateOfFolder();
			}
			break;
		case OPERATETYPE_REROOTFOLDER:
			{
				OperateOfReRootFolder((char*)pData);
			}
			break;
		case OPERATETYPE_RELOGIN:
			{
				OperateOfReLogin((char*)pData);
			}
			break;
		case OPERATETYPE_RELOGINOUT:
			{
				OperateOfReLoginOut((char*)pData);
			}
			break;
		case OPERATETYPE_REPOWER:
			{
				OperateOfRePowerManage((char*)pData);
			}
			break;
		case OPERATETYPE_REUSERLIST:
			{
				OperateOfReUserList((char*)pData);
			}
			break;
		case OPERATETYPE_RESTORELIST:
			{
				OperateOfReStoreList((char*)pData);
			}
			break;
		default:
			break;
	}
}

void XUserManage::UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI)
{
	switch(type)
	{
		case CMDUITYPE_LOGIN:
			{
				if(NULL!=pCmdUI)
					pCmdUI->Enable(!m_bLogin);
			}
			break;
		case CMDUITYPE_LOGINOUT:
		case CMDUITYPE_POWER:
		case CMDUITYPE_OSDIMAGE:
		//case CMDUITYPE_ADDSPLIT:
		//case CMDUITYPE_SPLITSCALE:
		//case CMDUITYPE_CLEARSIGNAL:
		case CMDUITYPE_UPDATE:
		//case CMDUITYPE_FOLDER:
		//case CMDUITYPE_ADDMODEL:
		//case CMDUITYPE_LIMITNMODEL:
		//case CMDUITYPE_SAVESPLITSCENE:
		case CMDUITYPE_SAVESCENE:
		case CMDUITYPE_SAVESEAT:
		case CMDUITYPE_SENDSEAT:
		case CMDUITYPE_CLEARSEAT:
		case CMDUITYPE_SEAT:
		case CMDUITYPE_ALIEN:
		case CMDUITYPE_LOG:
		case CMDUITYPE_MATRIXARRAY:
			{
				if(NULL!=pCmdUI)
					pCmdUI->Enable(m_bLogin);
			}
			break;
		default:
			break;
	}
}