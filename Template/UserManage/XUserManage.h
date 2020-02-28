#pragma once
#include "XConstant.h"
#include "XDelegateLogin.h"
#include "XDelegateLogin.h"
#include "XDelegatePowerManage.h"
#include "XConstant.h"

class XDelegateUserManage;
class XLogin;
class XPowerManage;
class XFolder;

class XUserManage:public XDelegateLogin,
	public XDelegatePowerManage
{


public:
	XUserManage();
	~XUserManage();

public:

	virtual void SetLoginUser(CString szUserName,CString szPassWd);
	virtual MAP_POWER& GetMapPower();
	virtual MAP_SUBUSER& GetMapSubUser();
	virtual MAP_STORE& GetMapStore();
	virtual CString GetUserName();
	virtual int GetUserID();
	virtual MAP_NODE& GetMapNode();
	virtual MAP_NODEALL& GetMapNodeAll();

public:

	void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);
	void Operate(OPERATETYPE type,void* pData);
	void ClearUserIDALL();
	//�������ļ���
	void ObtainSubFolder();
	void ObtainSubFolderInfo();
	//�������ʼۼл���
	void InsetTempSubFolder(int nID,CString szName);
	void ClearMapTempSubFolder();
	void SetThreadRun();

public:

	inline void SetDelegate(XDelegateUserManage* p) { m_pDelegate=p; }
	inline void SetPassWd(CString szPassWd) { m_szLoginPassWd=szPassWd; }
	inline CString GetPassWd() { return m_szLoginPassWd; }
	inline int GetUserAll() { return m_nUserALL; }
	inline VEC_USERALL& GetVecUserAll() { return m_VecUserAll; }
	inline MAP_ROOTFOLDER& GetMapRootFolder(){return m_MapRootFolder;}
	inline MAP_SUBFOLDER& GetMapSubFolder(){return m_MapSubFolder;}
	inline MAP_TEMPSUBFOLDER& GetMapTempSubFolder(){return m_MapTempSubFolder;}
private:

	//���õ�ǰ�û���
	void SetUserName(CString szName);
	//���õ�ǰ�û�ID
	void SetUserID(int n);
	//���õ�¼״̬
	void SetLogin(BOOL b);
	//��ȡ��¼״̬
	BOOL GetLogin();
	//�������û�Ȩ�ޣ��յ����û��б�֮��
	void ObtainSubUserPower();


private:

	//���Ȩ�޼���
	void ClearMapPower();
	//������û�����
	void ClearMapSubUser();
	//����ղ��û��б�
	void ClearMapStore();

	void ClearUserAll();
	void ClearUserIDAll();

	void ClearMapRoot();
	void ClearMapSubFolder();

private:

	//����-��¼
	void OperateOfLogin();
	//����-�˳�
	void OperateOfLoginOut();
	//����-��ȡȨ��
	void OperateOfPowerManage();
	//������ȡ�ļ���
	void OperateOfFolder();
	//��������-��¼
	void OperateOfReLogin(char* pData);
	//��������-�˳�
	void OperateOfReLoginOut(char* pData);
	//��������-��¼�û�Ȩ��
	void OperateOfRePowerManage(char* pData);
	//��������-�û��б�
	void OperateOfReUserList(char* pData);
	//��������-�ղ��б�
	void OperateOfReStoreList(char* pData);
	//�������ݡ�����Ŀ¼
	void OperateOfReRootFolder(char* pData);

private:
	//��ʼ���Ҹ�Ŀ¼
	BOOL BeginRootFolderThread();


	//������Ŀ¼
	BOOL BeginSubFolderThread();
	//ֹͣ�߳�
	void StopSubFolderThread();
	//�ر��߳�Event
	void CloseSubFolderThreadEvent();

private:

	//�û�Ȩ��(�û���)
	MAP_POWER m_MapPower;
	//���û��б�(�û���)
	MAP_SUBUSER m_MapSubUser;
	//�ղ��б�(�ڵ�ID)
	MAP_STORE m_MapStore;
	//64��16λ������ʾ֪���û�����
	VEC_USERALL m_VecUserAll;
	//�����û�ID(�û�ID),��ʱֻ��ȡ�������û�ID,
	VEC_USERIDALL m_VecUserIDAll;

private:

	XLogin* m_pLogin=nullptr;
	XPowerManage* m_pPowerManage=nullptr;
	XFolder* m_pFolder=NULL;
	XDelegateUserManage* m_pDelegate=nullptr;
	BOOL m_bLogin=FALSE;
	CString m_szLoginUser=_T("");
	CString m_szLoginPassWd=_T("");
	LONG m_dLoginTime=0;
	int m_nUserALL=0;

public:

	//��ȡ�ļ����߳�
	BOOL m_bRunning=FALSE;
	HANDLE m_ThreadEvent=nullptr;
	CWinThread* m_Thread=nullptr;
	CRITICAL_SECTION m_CS;

private:
	MAP_ROOTFOLDER m_MapRootFolder;
	//�ļ���������Ϣ�������ļ������û��ڵ㣨���ļ���ID��
	MAP_SUBFOLDER m_MapSubFolder;

	//�¼��ļ��л���
	MAP_TEMPSUBFOLDER m_MapTempSubFolder;
};