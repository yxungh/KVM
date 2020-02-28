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
	//查找子文件夹
	void ObtainSubFolder();
	void ObtainSubFolderInfo();
	//保存子问价夹缓存
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

	//设置当前用户名
	void SetUserName(CString szName);
	//设置当前用户ID
	void SetUserID(int n);
	//设置登录状态
	void SetLogin(BOOL b);
	//获取登录状态
	BOOL GetLogin();
	//查找自用户权限（收到自用户列表之后）
	void ObtainSubUserPower();


private:

	//清空权限集合
	void ClearMapPower();
	//清空子用户集合
	void ClearMapSubUser();
	//清空收藏用户列表
	void ClearMapStore();

	void ClearUserAll();
	void ClearUserIDAll();

	void ClearMapRoot();
	void ClearMapSubFolder();

private:

	//操作-登录
	void OperateOfLogin();
	//操作-退出
	void OperateOfLoginOut();
	//操作-获取权限
	void OperateOfPowerManage();
	//操作获取文件夹
	void OperateOfFolder();
	//返回数据-登录
	void OperateOfReLogin(char* pData);
	//返回数据-退出
	void OperateOfReLoginOut(char* pData);
	//返回数据-登录用户权限
	void OperateOfRePowerManage(char* pData);
	//返回数据-用户列表
	void OperateOfReUserList(char* pData);
	//返回数据-收藏列表
	void OperateOfReStoreList(char* pData);
	//返回数据——根目录
	void OperateOfReRootFolder(char* pData);

private:
	//开始查找根目录
	BOOL BeginRootFolderThread();


	//查找子目录
	BOOL BeginSubFolderThread();
	//停止线程
	void StopSubFolderThread();
	//关闭线程Event
	void CloseSubFolderThreadEvent();

private:

	//用户权限(用户名)
	MAP_POWER m_MapPower;
	//子用户列表(用户名)
	MAP_SUBUSER m_MapSubUser;
	//收藏列表(节点ID)
	MAP_STORE m_MapStore;
	//64个16位数，表示知道用户个数
	VEC_USERALL m_VecUserAll;
	//所用用户ID(用户ID),暂时只获取到所有用户ID,
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

	//获取文件夹线程
	BOOL m_bRunning=FALSE;
	HANDLE m_ThreadEvent=nullptr;
	CWinThread* m_Thread=nullptr;
	CRITICAL_SECTION m_CS;

private:
	MAP_ROOTFOLDER m_MapRootFolder;
	//文件夹下面信息包含子文件夹与用户节点（父文件夹ID）
	MAP_SUBFOLDER m_MapSubFolder;

	//下级文件夹缓存
	MAP_TEMPSUBFOLDER m_MapTempSubFolder;
};