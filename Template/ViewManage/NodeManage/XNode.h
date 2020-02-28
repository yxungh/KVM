#pragma once
#include "XDelegateNodeLoginUser.h"


class XPropertyGrid;
class XPropertyGridFile;
class XNodeManage;


class XNode:public XDelegateNodeLoginUser
{
public:
	XNode();
	~XNode();

public:

	virtual MAP_SUBUSER& GetMapSubUser();

	virtual MAP_POWER& GetMapPower();

public:

	inline void SetNodeManage(XNodeManage* p){m_pNodeManage=p;}

	inline void SetTreeItem(HTREEITEM item){m_NodeItem=item;}
	inline HTREEITEM GetTreeItem(){return m_NodeItem;}

	inline void SetIndex(int n){m_nIndex=n;}
	inline int GetIndex(){return m_nIndex;}

	inline void SetRect(CRect rect){m_rect=rect;}
	inline CRect GetRect(){return m_rect;}

	inline void SetTextRect(CRect rect){m_TextRect=rect;}
	inline CRect GetTextRect(){return m_TextRect;}

	inline void SetSelected(BOOL b){m_bSelected=b;}
	inline BOOL GetSelected(){return m_bSelected;}

	inline void SetDrag(BOOL b){m_bDrag=b;}
	inline BOOL GetDrag(){return m_bDrag;}

public:

	inline void SetRealID(CString szID){m_szRealID=szID;}
	inline CString GetRealID(){return m_szRealID;}

	inline void SetNodeName(CString szName){m_szNodeName=szName;}
	inline CString GetNodeName(){return m_szNodeName;}

	inline void SetCreateTime(time_t time){m_tConnectTime=time;}
	inline time_t GetCreateTime(){return m_tConnectTime;}

	inline void SetGroup(int nGroup){m_nGroup=nGroup;}
	inline int GetGroup(){return m_nGroup;}

	inline void SetMaster(int n){m_nMaster=n;}
	inline int GetMaster(){return m_nMaster;}

	inline void SetControl(int n){m_nControl=n;}
	inline int GetControl(){return m_nControl;}


public:

	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetChannel(int n){m_nChannel=n;}
	inline int GetChannel(){return m_nChannel;}

	inline void SetNodeType(int n){m_nNodeType=n;}
	inline int GetNodeType(){return m_nNodeType;}

	inline void SetConnectTime(time_t time){m_tCreateTime=time;}
	inline time_t GetConnectTime(){return m_tCreateTime;}

	inline void SetMainCh(int n){m_nMainCh=n;}
	inline int GetMainCh(){return m_nMainCh;}

public:

	//in
	inline void SetNodeInStatus(int n){m_nInStatus=n;}
	inline int GetNodeInStatus(){return m_nInStatus;}

	inline void SetIsSignal(BOOL b){m_bSignal=b;}
	inline BOOL GetIsSignal(){return m_bSignal;}

	inline void SetInResolusationH(int n){m_nInResolusationH=n;}
	inline int GetInResolusationH(){return m_nInResolusationH;}

	inline void SetInResolusationV(int n){m_nInResolusationV=n;}
	inline int GetInResolusationV(){return m_nInResolusationV;}

	inline void SetAudioModel(int n){m_nAudioModel=n;}
	inline int GetAudioModel(){return m_nAudioModel;}

	inline void SetHidModel(int n){m_nHidModel=n;}
	inline int GetHidModel(){return m_nHidModel;}

	inline void SetSplitScreen(int n){m_nSplitScreen=n;}
	inline int GetSplitScreen(){return m_nSplitScreen;}

	inline void SetSoftVer(CString szVer){m_szSoftVer=szVer;}
	inline CString GetSoftVer(){return m_szSoftVer;}

	inline void SetHardVer(CString szVer){m_szHardVer=szVer;}
	inline CString GetHardVer(){return m_szHardVer;}

	inline void SetAudioSrc(int n){m_nAudioSrc=n;}
	inline int GetAudioSrc(){return m_nAudioSrc;}


	//out
	inline void SetOutStatus(int n){m_nOutStatus=n;}
	inline int GetOutStatus(){return m_nOutStatus;}

	inline void SetOutResoluationIndex(int n){m_nOutResoluationIndex=n;}
	inline int GetOutResoluationIndex(){return m_nOutResoluationIndex;}

	inline void SetOutModel(int n){ m_nOutModel=n;}
	inline int GetOutModel(){return m_nOutModel;}

	inline void SetIsNodeLogin(BOOL b){m_bNodeLogin=b;}
	inline BOOL GetIsNodeLogin(){return m_bNodeLogin;}

	inline void SetIsTakeOver(BOOL b){m_bTakeOver=b;}
	inline BOOL GetIsTakeOver(){return m_bTakeOver;}

	inline void SetLoginUserID(int n){m_nLoginUserID=n;}
	inline int GetLoginUserID(){return m_nLoginUserID;}

	inline void SetTakeOverNodeID(int n){m_nTakeOverNodeID=n;}
	inline int GetTakeOverNodeID(){return m_nTakeOverNodeID;}

	inline void SetPreviewNodeID(int n){m_nPreviewNodeID=n;}
	inline int GetPreviewNodeID(){return m_nPreviewNodeID;}

	inline void SetBindCfg(int n){m_nBindCfg=n;}
	inline int GetBindCfg(){return m_nBindCfg;}

	inline void SetBindNodeID(int n){m_nBindNodeID=n;}
	inline int GetBindNodeID(){return m_nBindNodeID;}

	inline void SetOutSoftVer(CString szVer) { m_szOutSoftVer=szVer; }
	inline CString GetOutSoftVer() { return m_szOutSoftVer; }

	inline void SetOutHardVer(CString szVer) { m_szOutHardVer=szVer; }
	inline CString GetOutHardVer() { return m_szOutHardVer; }

	inline std::vector<int>& GetVecHotKey(){return m_VecHotKey;}

private:

	//基本信息
	void PropertyInfo();
	//登录节点
	void PropertyLoginStatus();
	//接管
	void PropertyTakeOver();
	//预览
	void PropertyPreview();
	//矩阵切换
	void PropertyMatrix();
	//显示隐藏OSD底图
	void PropertyOSDImage();
	//绑定设置
	void PropertyBindSet();
	//热键
	void PropertyHotKey();

	//void UpdateOptionList(CString& szOptionText);

	XUserLogStatus* GetUserLoginStatusByNodeID(MAP_USERLOGINSTATUS& MapUserLogin,int nNodeID);
	int GetNodeIDByChannel(int nChannel);

public:

	//设置属性框
	void SetPropertiesWnd();

	//属性值改变
	void OnPropertyChanged(CMFCPropertyGridProperty* pProperty);

	//双击属性
	BOOL OnDblClkPropertyGrid(XPropertyGrid* pPropertyGrid);

	BOOL OnDblClkPropertyGridFile(XPropertyGridFile* pPropertyGridFile);

	//单击属性框
	void OnClickButtonPropertyGridFile(XPropertyGridFile* pPropertyGridFile);

private:
	void ClearMapHotKey();
	CString GetKeyByValue(int nValue);
	void ParseVecValue();
	void ParseHotKey(int nIndex,CString& szFunction,CString& szValue,CString& szEnable);
	void WriteHotKey(int nIndex,CString szFunction,CString szValue,CString szEnable);

private:

	XNodeManage* m_pNodeManage=NULL;
	//节点所在项
	HTREEITEM m_NodeItem=NULL;
	//序号
	int m_nIndex=0;
	//区域
	CRect m_rect;
	//字体字体区域
	CRect m_TextRect;
	//是否选中
	BOOL m_bSelected=FALSE;
	//能否拖拽
	BOOL m_bDrag=TRUE;

private:

	//真实ID
	CString m_szRealID=_T("");
	//节点名称
	CString m_szNodeName=_T("");
	//创建时间
	time_t m_tCreateTime=0;
	//节点IP
	CString m_szNodeIP=_T("");
	//组
	int m_nGroup=0;
	//主
	int m_nMaster=0;
	//控制
	int m_nControl=0;
	//用户登录信息集合
	//////////////////////////////////////////////////////////////////////////
	//登录用户
	CString m_szLoginUser=_T("");
	//用户是否网络登录
	BOOL m_bNetLogin=FALSE;
	//网络登录IP
	CString m_szIP=_T("");
	//网络登录端口
	int m_nPort=0;
	//是否节点登录
	BOOL m_bNodeLogin=FALSE;
	//////////////////////////////////////////////////////////////////////////

//根据连接情况获取到的部分参数
private:

	//通道
	int m_nChannel=0;
	//ID的编号
	int m_nNodeID=0;
	//类型
	int m_nNodeType=-1;
	//连接时间
	time_t m_tConnectTime=0;
	//主通道
	int m_nMainCh=0;

private:
	//节点状态
	//In
	int m_nInStatus=-1;
	BOOL m_bSignal=FALSE;

	int m_nInResolusationH=0;
	int m_nInResolusationV=0;
	int m_nAudioModel=-1;//音频模式
	int m_nHidModel=-1;//系统
	int m_nSplitScreen=1;//分屏模式
	CString m_szSoftVer=_T("");//软件版本
	CString m_szHardVer=_T("");//硬件版本
	int m_nAudioSrc=0;//当前监听音频源节点ID


	//out
	int m_nOutStatus=0;
	//DVI,HDMI
	int m_nOutModel=-1;
	//分辨率信息序号
	int m_nOutResoluationIndex=-1;
	//是否接管
	BOOL m_bTakeOver=FALSE;
	//登录的用户
	int m_nLoginUserID=0;
	//接管节点ID
	int m_nTakeOverNodeID=0;
	//预览节点ID
	int m_nPreviewNodeID=0;
	//绑定设置
	int m_nBindCfg=0;
	//绑定输出节点ID
	int m_nBindNodeID=0;
	CString m_szOutSoftVer=_T("");//软件版本
	CString m_szOutHardVer=_T("");//硬件版本

	//热键 
	VEC_HOTKEY m_VecHotKey;
	//菜单和值
	MAP_HOTKEY m_MapHotKey;
};