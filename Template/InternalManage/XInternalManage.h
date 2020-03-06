#pragma once
#include "XBaseInternalManage.h"
#include "XDelegateRibbonBarManage.h"
#include "XDelegateTranslationManage.h"
#include "XDelegateIniManage.h"
#include "XDelegateNetManage.h"
#include "XDelegateSendDataManage.h"
#include "XDelegateReciveDataManage.h"
#include "XDelegateUserManage.h"
#include "XDelegateNodeManage.h"
#include "XDelegatePropertiesWnd.h"
#include "XDelegateLeftWnd.h"
#include "XDelegateSeatArrageManage.h"
#include "XDelegateMatrixManage.h"
#include "XDelegateConstantData.h"
#include "XVideoPlayer.h"
#include "XDelegateDeviceNet.h"
#include "XDelegateScene.h"
#include "XLog.h"
#include "XDelegateLog.h"
#include "XDelegateUpdate.h"
#include "XDelegateStatusBar.h"
#include "XDelegateSplitManage.h"
#include "XDelegateSaveSplitScene.h"



class XBaseRibbonBarManage;
class XTranslationManage;
class XIniManage;
class XBaseNetManage;
class XReciveDataManage;
class XUserManage;
class XBaseNodeManage;
class XBaseViewManage;
class XBaseMatrixManage;
class XPropertiesWnd;
class XBaseSeatArrageManage;
class XTabCtrl;
class XMultiVideoWindow;
class XDeviceNet;
class XBaseSplitManage;
class XSaveSplitScene;



class XInternalManage:public XBaseInternalManage,
	public XDelegateRibbonBarManage,
	public XDelegateTranslationManage,
	public XDelegateIniManage,
	public XDelegateNetManage,
	public XDelegateSendDataManage,
	public XDelegateReciveDataManage,
	public XDelegateUserManage,
	public XDelegateNodeManage,
	public XDelegateProperitiesWnd,
	public XDelegateLeftWnd,
	public XDelegateSeatArrageManage,
	public XDelegateMatrixManage,
	public XDelegateConstantData,
	public XDelegateDeviceNet,
	public XDelegateScene,
	public XDelegateLog,
	public XDelegateUpdate,
	public XDelegateStatusBar,
	public XDelegateSplitManage,
	public XDelegateSaveSplitScene
{
public:

	XInternalManage();
	~XInternalManage();

public:

	//视图绘制
	virtual void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY);

	//视图获取大小
	virtual CSize ViewGetSize();

	//视图左键按下
	virtual void ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//视图双击
	virtual void ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//视图左键提起
	virtual void ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//视图鼠标移动
	virtual void ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//视图鼠标离开
	virtual void ViewMouseLeave();

	//鼠标滚轮
	virtual BOOL ViewMouseWheel(short zDelta);

	//视图按键提起
	virtual void ViewKeyUp(UINT nChar);

	//视图右键提起
	virtual void ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);


public:

	//初始化
	virtual void Init();

	//初始化停靠面板
	virtual void InitPane();

	//设备网络
	virtual void SetIPAddr1(CString szIP);
	virtual void SetIPAddr2(CString szIP);
	virtual void SetPort1(int n);
	virtual void SetPort2(int n);

	//设备节点通道个数
	virtual void SetHardWareChannel(int n);

	//矩阵型号
	virtual void SetMatrixModel(CString szModel);

	//fpga版本号
	virtual void SetFPGAVersion(CString szVer);

	//关闭程序
	virtual BOOL AppClose();

	//获取CWnd
	virtual CWnd* GetCWND();

	//获取句柄
	virtual HWND GetHWND();

	//Ribbon显示的类别
	virtual void RibbonBarShowCategory(DWORD_PTR dwData);

	//工具栏控件数据变化
	virtual void ControlDataChange(XDATATYPE type);

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type,void* pControl);

	//操作
	virtual void Operate(OPERATETYPE type,void* pData);

	//更改主题
	virtual void ChangeTheme(int nType);

	//重载界面
	virtual void ReloadInterface();

	//翻译标签标题
	virtual void ReloadDocTitle();

	//根据数据类型更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type);

	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type,void* pControl);

	//处理UDP数据
	virtual void HandleUDPData(unsigned char* pData,int nDataLen,SOCKADDR_IN addr);

	//处理UDP消息
	virtual void HandleUDPMsg(WPARAM wParam,LPARAM lParam);

	//发送数据
	virtual BOOL SendData(char* pData,int nDataLen);

	//更新程序获取IP
	virtual CString GetCurIP();
	virtual int GetCurPort();

	//获取设备IP
	virtual CString GetDeviceIP();

	//获取设备端口
	virtual int GetDevicePort();

	//获取设备2IP
	virtual CString GetDevice2IP();

	//获取设备2端口
	virtual int GetDevice2Port();

	virtual CString GetDeviceMask();
	virtual CString GetDevice2Mask();
	virtual CString GetDeviceGateway();
	virtual CString GetDevice2Gateway();

	//发送应用网络配置时间
	virtual void SetSendApplyTime(DWORD dwTime);

	//通讯网络选择
	virtual void ConnectNetSelect();

	//获取网络开启状态
	virtual BOOL GetNetStatus();

	//设备选择
	virtual void SetDeviceSelect(int nSelect);

	//工具栏控件状态
	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);

	//设置当前用户
	virtual void SetCurUserName(CString szName);

	virtual CString GetCurUserName();

	//设置用户ID
	virtual void SetCurUserID(int n);

	//获取用户ID
	virtual int GetCurUserID();

	//设置登录
	virtual void SetLogin(BOOL b);

	virtual BOOL GetLogin();

	//设置状态栏
	//virtual void SetStatusBarInfo();

	//添加页面
	virtual void AddDocument();

	//获取视图
	virtual CTemplateView* GetView();

	//注销清空节点
	virtual void ClearNode();

	//清空柱形图
	virtual void ClearCloumn();

	//清空连接通道
	virtual void ClearConChannel();

	//清空树
	virtual void ClearTree();

	//清空节点组
	virtual void ClearNodeGroup();

	//清空登录状态
	virtual void ClearUserLoginStatus();

	//清空用户中个数
	virtual void ClearUserIDALL();

	//清空坐席集合
	virtual void ClearInfo(CString szGroupName);

	//注销清空页面
	virtual void ClearPage();

	//清空场景树
	virtual void ClearSceneTree();

	//更新坐席名称
	virtual void UpdateGroupNameAfterAddArrage(CString szName);

	//匹配坐席名称
	virtual void MatchSeatNameByGroupName();

	//更改组名名称
	virtual void UpdateGroupNameAfterChange(CString szGroupName,CString szName);

	//更新屏幕编排信息
	virtual void UpdateGroupArrageByRemoveNode(CString szGroupName,int nNodeID);

	//移除节点更新第二页
	virtual void UpdateScreenAfterRemoveNode(int nNodeID);

	//更新主屏显示（主）
	virtual void UpdateShowMasterAfterRemoveNode(int nMaster);

	//获取用户列表
	virtual MAP_SUBUSER& GetMapSubUser();

	//获取当前用户权限列表
	virtual MAP_POWER& GetMapPower();

	//获取节点集合
	virtual MAP_NODE& GetMapNode();
	virtual MAP_NODEALL& GetMapNodeAll();

	//获取节点主副屏
	virtual MAP_NODEMAINSEC& GetMapNodeMainSec();

	//获取节点组集合
	virtual MAP_NODEGROUP& GetMapNodeGroup();

	//获取主副屏集合
	virtual MAP_GROUPMAINSEC& GetMapNodeGroupMainSec();

	//获取坐席排列删除节点
	virtual VEC_DEL& GetVecDel();

	//获取总用户数量
	virtual VEC_USERIDALL& GetVecUserIDAll();

	//获取矩阵切换状态
	virtual MAP_MATRIX& GetMapMatrix();

	//获取集合
	virtual MAP_BASEVIEW& GetBaseView();

	//向树列表插入用户
	virtual void InsertItemToTree(CString szUserName);

	//从用户树中删除
	virtual void DeleteItemFromTree(CString szUserName);

	//点击树设置属性栏用户
	virtual void SetPropertyValue(CString szUserName);

	//单击选中节点
	virtual void SetNodeSelected(CString szNodeName);

	//拖拽结束
	virtual void DragEnd(CPoint& point,CRect& rect);

	//显示组坐席
	virtual void ShowGroupSeatArrage(CString szGroup);

	//设置视图颜色
	virtual void SetViewColor(Color& color);

	//从组中删除节点
	virtual void DelNodeFromGroup(CString szGroupName,int nNodeID);

	//判断能不能删除
	virtual BOOL JudgetDelNodeFromGroup(CString szGroupName,int nNodeID);

	//更改主题设置预览墙颜色
	virtual void SetMultiVideoWindowBkColor(Uint8 r,Uint8 g,Uint8 b);

	//刷新
	virtual void AdjustMultiVideoWindowSize();

	virtual void AdjustMultiVideoWindowSize(int nWidth,int nHeight);

	//设置页面背景
	virtual void SetMultiVideoFramesBg();

	//拖拽组到坐席上
	virtual void DragGroupToSeat(CString szGroupName,CPoint& point);

	//点击组切换页面
	virtual void SwitchPage(int nPage);

	//绘制输入组屏幕
	virtual void DrawGroupInScreen(CString szGroupName);

	//点击输出选中页面坐席
	virtual void SetSeatSelected(CString szGroupName);

	//隐藏菜单按钮
	virtual void HideMenuWnd();

	//获取坐席页面序号
	virtual int GetPageIndex();

	//重置坐席工具栏
	virtual void ResetRibbonBar();

	//点击输入隐藏菜单按钮
	virtual void HidePopMenuBtn();

	//显示按钮
	virtual void ShowPopMenuBtn();

	//调用场景
	virtual void OpenScene(int nData);

	//更新矩阵排列信息
	virtual void ResetMatrixArray();

	//根据分会状态设置 页面状态
	virtual void ResetMatrixSwitchStatus();

	//获取当前拼接视图放缩
	virtual float GetCurScale();

	//获取拼接场景
	virtual MAP_SPLITSCENE& GetMapSplitScene();

	virtual MAP_SPLITSCENEGROUP& GetMapSplitSceneGroup();

	//设置预览墙放缩
	virtual void SetMultiVideoWindowScale(float fScale);

	//右键创建组时，把组名称赋给页面
	virtual void SetGroupNameByAddGroupIn(CString szName);

private:
	void OperateOfReHeart(char* pData);
	void OperateOfReNetConfig(char* pData);
	void OperateOfReLog(char* pData);
	void OperateOfDeviceNet();
	void OperateOfAddSplit();
	void OperateOfObtainSplit();
	void OperateOfSplit(char* pData);
	void OperateOfSplitWindow(char* pData);
	void OperateOfClearSplitView();
	void OperateOfObtainSplitScene();
	void OperateOfReSplitScene(char* pData);
	void OperateOfReSplitInput(char* pData);

public:
	void OperateOfAbout();
	void OperateOfHeart();
	void OperateOfAddSeat();
	//void OperateOfControl();
	void OperateOfLog();
	void OperateOfUpdate();
	void OperateOfStatusTime();
	void OperateOfSaveSplitScene();
	//调用拼接场景
	void OperateOfOpenScene();
	void OperateOfOpenSceneOne();

public:

	void CloseSplit(XBaseViewManage* pManage);
	void CloseSplit();

	int DecideWallExistence(CString szWall);

	



private:

	//初始化管理
	void InitManage();

	//初始化数据
	void InitAppData();

	//初始化网络Ip
	void InitIPAddr();

	//初始化页面
	void InitDocument();

	//获取数据
	BOOL GetAppData();

	//获取应用数据
	void GetAppData(CArchive& arch);

	//注销保存数据
	void SaveData();

	//保存应用数据
	BOOL SaveAppData();

	//保存应用数据
	void SaveAppData(CArchive& arch);

	//重置应用数据
	void ResetAppData();

	//添加文档界面
	void AddDocument(XBaseViewManage* pBase);

	//获取View
	CView* GetDocumentFrontView(CDocument* p);

	//设置文档名称
	CString GetDocTitle(CString szTitle);

	//根据名称切换视图
	XBaseViewManage* GetBaseViewManageByData(DWORD_PTR dwData,int& nIndex);

	//BOOL CheckDataSum(char* pData,int& nLen);

	//unsigned short CheckSum(unsigned char* pData,int nLen);

	//添加绘制页面
	XMultiVideoWindowFrames* AddPageToMultiVideoWindow(int nIndex,int nWidth,int nHeight);

	//判断组中有无场景
	BOOL DecideSplitGroupHasOneScene(CString szName);

public:

	void SetViewManage(XBaseViewManage* p);
	//开始主线程
	BOOL BeginHeartThread();
	//停止线程
	void StopHeartThread();
	//关闭线程Event
	void CloseHeartThreadEvent();

private:

	//清除
	void Clear();
	void ClearMapData();
	void ClearMapBaseView();
	void ClearNetConfig();
	void ClearSplitScene();


	//获取拼接屏序号
	int GetIndexByAdd();
	
private:

	//工具栏管理
	XBaseRibbonBarManage* m_pRibbonBarManage=nullptr;
	//Ini管理
	XIniManage* m_pIniManage=nullptr;
	//网络管理
	XBaseNetManage* m_pBaseNetManage=nullptr;
	//接受数据管理
	XReciveDataManage* m_pReciveDataManage=nullptr;
	//用户管理
	XUserManage* m_pUserManage=nullptr;
	//当前视图类
	XBaseViewManage* m_pBaseViewManage=nullptr;
	//节点管理
	XBaseNodeManage* m_pNodeManage=nullptr;
	//坐席编排
	XBaseSeatArrageManage* m_pSeatArrageManage=nullptr;
	//矩阵切换
	XBaseMatrixManage* m_pMatrixManage=nullptr;
	//视频管理
	XVideoPlayer m_VideoPlayer;
	//坐席页面预览墙
	XMultiVideoWindow* m_pMultiVideoWindow=nullptr;
	//网络管理对话框
	XDeviceNet* m_pDeviceNet=nullptr;
	//拼接墙缓存 不在集合中
	//XBaseSplitManage* m_pSplitManage=nullptr;


private:

	//当前网络
	CString m_szIPAddr1=_T("");
	CString m_szIPAddr2=_T("");
	CString m_szMask1=_T("");
	CString m_szMask2=_T("");
	CString m_szGateway1=_T("");
	CString m_szGateway2=_T("");
	int m_nPort1=0;
	int m_nPort2=0;
	DWORD m_dwApplyTime=0;
	//设备选择
	int m_nDeviceSelect=0;
	//当前用户名
	CString m_szUserName=_T("");
	//当前用户ID
	int m_nUserID=0;
	//是否登录
	BOOL m_bLogin=FALSE;
	//当前设备IP
	CString m_szCurDeviceIP=_T("");
	//当前设备端口
	int m_nCurDevicePort=0;
	//心跳时间
	LONG m_dHeartTime=0;
	//是否在线
	BOOL m_bOnline=FALSE;
	//设备节点个数
	int m_nHardWareChannel=0;
	//设备型号
	CString m_szMatrixModel=_T("");
	//fpga版本号
	CString m_szFPGAVersion=_T("");
	//接受数据协议号（分包）
	int m_nProtocol=0;
	//总包数
	int m_nPacket=0;
	//包序号
	int m_nPacketIndex=0;
	//视图标题栏
	XTabCtrl* m_pViewTabCtrl=nullptr;
	//日志对话框
	XLog* m_pLogDlg=nullptr;
	//保存拼接场景对话框
	XSaveSplitScene* m_pSplitScene=nullptr;

public:

	//心跳线程
	BOOL m_bRunning=TRUE;
	HANDLE m_HeartThreadEvent=nullptr;
	CWinThread* m_HeartThread=nullptr;

private:

	//视图类
	MAP_BASEVIEW m_MapBaseView;
	//接受分包
	MAP_DATA m_MapData;
	//网络配置
	VEC_NETCONFIG m_VecNetConfig;
	//拼接场景
	MAP_SPLITSCENE m_MapSplitScene;
	//拼接场景组
	MAP_SPLITSCENEGROUP m_MapSplitSceneGroup;

private:

	//当前拼接界面序号,第一个拼接序号为3
	int m_nSplitIndex=3;

};