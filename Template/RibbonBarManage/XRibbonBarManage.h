#pragma once

#include "XBaseRibbonBarManage.h"
#include "XRibbonBar.h"
#include "XDelegateRibbonBar.h"
#include "XConstant.h"

class XRibbonBarManage: public XBaseRibbonBarManage,XDelegateRibbonBar
{
public:
	XRibbonBarManage(void);
	~XRibbonBarManage(void);

	//初始化
	virtual void Init();

	//控件数据改变
	virtual void ControlDataChange(XDATATYPE type);

	//重载界面
	virtual void ReloadInterface();

	//根据数据类型更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type);

	//Ribbon显示的类别
	virtual void RibbonBarShowCategory(DWORD_PTR dwData);

	//virtual void SetStatusInfo();

	//virtual void SetCurUserName(CString szUserName);

	virtual void SetActiveCategory(int nBaseIndex);

	virtual void ResetRibbonBar();


private:

	//初始化RibbonBar
	void InitRibbonBar();

	//初始化状态栏
	//void InitStatusBar();

	//初始化RibbonBar
	void InitRibbonBar(CMFCRibbonBar* pRibbonBar);

	BOOL InitImageList();

	//获取CWnd
	CWnd* GetCWND();

	//更新所有控件数据显示
	void UpdateControlDataShowOfAll();

private:

	CString m_szUserName=_T("");

	//工具栏
	XRibbonBar m_wndRibbonBar;

	static CMFCRibbonBar* m_pTempBar;

	//状态栏
	//CMFCRibbonStatusBar m_wndStatusBar;

	//关于
	CMFCRibbonButton* m_pAboutButton=NULL;
	//主页
	CMFCRibbonCategory* m_pCategoryMain=NULL;
	//界面
	CMFCRibbonPanel* m_pPanelMainSet=NULL;
	//语言
	CMFCRibbonButton* m_pBtnLanguage=NULL;
	//主题
	CMFCRibbonButton* m_pBtnTheme=NULL;
	//缩放
	CMFCRibbonButton* m_pBtnScale=NULL;
	//登录
	CMFCRibbonPanel* m_pPanelLogin=NULL;
	//登陆
	CMFCRibbonButton* m_pLogin=NULL;
	//注销
	CMFCRibbonButton* m_pLoginOut=NULL;

	//用户管理
	CMFCRibbonPanel* m_pPanelUser=NULL;
	//用户权限
	CMFCRibbonButton* m_pPowerManage=NULL;
	//安全中心
	CMFCRibbonButton* m_pPowerSecurity=NULL;
	//文件夹
	CMFCRibbonButton* m_pFloder=NULL;

	//////////////////////////////////////////////////////////////////////////
	//底图
	CMFCRibbonPanel* m_pPanelImage=NULL;
	//OSD底图
	CMFCRibbonButton* m_pBtnOSDImage=NULL;
	//////////////////////////////////////////////////////////////////////////
	////中控
	//CMFCRibbonPanel* m_pPanelControl=NULL;
	////控制
	//CMFCRibbonButton* m_pBtnControl=NULL;
	//////////////////////////////////////////////////////////////////////////
	//保存预案
	CMFCRibbonPanel* m_pPanelScene=NULL;
	CMFCRibbonButton* m_pBtnScene=NULL;
	//////////////////////////////////////////////////////////////////////////
	//日志
	CMFCRibbonPanel* m_pPanelLog=NULL;
	CMFCRibbonButton* m_pBtnLog=NULL;
	//////////////////////////////////////////////////////////////////////////
	//设备
	CMFCRibbonPanel* m_pPanelDevice=NULL;
	//互联
	CMFCRibbonButton* m_pBtnConn=NULL;
	//升级服务器
	CMFCRibbonButton* m_pBtnUpdate=NULL;
	//网络
	CMFCRibbonButton* m_pBtnNet=NULL;
	
	//打开网络
	//CMFCRibbonButton* m_pBtnOpenNet=NULL;
	//关闭网络
	//CMFCRibbonButton* m_pBtnCloseNet=NULL;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//第二页
	//坐席编排
	CMFCRibbonCategory* m_pCategorySeatArrage=NULL;
	//界面
	CMFCRibbonPanel* m_pPanelMainSeat=NULL;
	//比例
	CMFCRibbonButton* m_pBtnSeatScale=NULL;
	//背景
	CMFCRibbonButton* m_pBtnBg=NULL;
	//坐席
	CMFCRibbonPanel* m_pPanelSeat=NULL;
	//坐席
	CMFCRibbonButton* m_pBtnSeat=NULL;
	//对齐
	CMFCRibbonButton* m_pBtnAlign=NULL;
	//范围
	CMFCRibbonPanel* m_pPanelSeatRange=NULL;
	////坐席范围行
	CMFCRibbonButton* m_pBtnArray=NULL;
	//CMFCRibbonEdit* m_pEditSeatRow;

	////坐席范围列
	//CMFCRibbonEdit* m_pEditSeatColumn;
	//操作
	CMFCRibbonPanel* m_pPanelOperate=NULL;
	//保存坐席
	CMFCRibbonButton* m_pBtnSaveSeat=NULL;
	//发送
	//CMFCRibbonButton* m_pBtnSendSeat=NULL;
	//清除
	CMFCRibbonButton* m_pBtnClearSeat=NULL;
	//////////////////////////////////////////////////////////////////////////
	//第三页矩阵
	CMFCRibbonCategory* m_pCategoryMatrix=NULL;
	//行列
	CMFCRibbonPanel* m_pPanelMatrixArray=NULL;
	//矩阵行列
	CMFCRibbonButton* m_pBtnMatrixArray=NULL;
	//界面
	CMFCRibbonPanel* m_pPanelMatrixScale=NULL;
	CMFCRibbonButton* m_pBtnMatrixScale=NULL;
	//////////////////////////////////////////////////////////////////////////
	//拼接界面
	CMFCRibbonCategory* m_pCategorySplit=NULL;
	//添加拼接屏
	CMFCRibbonPanel* m_pPanelOne=NULL;
	//新建
	CMFCRibbonButton* m_pBtnAdd=NULL;
	//界面
	CMFCRibbonPanel* m_pPanelTwo=NULL;
	//比例
	CMFCRibbonButton* m_pBtnSplitScale=NULL;
	//操作
	CMFCRibbonPanel* m_pPanelThree=NULL;
	//限制模式
	CMFCRibbonButton* m_pBtnLimitModel=NULL;
	//开窗模式
	//CMFCRibbonButton* m_pBtnAddModel=NULL;

	//快速置顶
	CMFCRibbonButton* m_pBtnQuickTop=NULL;
	//清空信号
	CMFCRibbonButton* m_pBtnClearSignal=NULL;
	//场景保存
	CMFCRibbonButton* m_pBtnSplitScene=NULL;

};



