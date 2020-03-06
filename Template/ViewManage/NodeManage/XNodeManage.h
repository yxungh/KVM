#pragma once
#include "XBaseNodeManage.h"
#include "XConstant.h"
#include "XDelegateBaseMap.h"
#include "XDelegateDeviceConn.h"


class XBaseMap;
class XProgressCtrl;
class XDeviceConn;


class XNodeManage:public XBaseNodeManage,
	public XDelegateBaseMap,
	public XDelegateDeviceConn
{
public:
	XNodeManage();
	virtual ~XNodeManage();

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
	//工具栏
	virtual void ControlDataChange(XDATATYPE type,void* pControl);
	//更新控件数据显示
	virtual void UpdateControlDataShow(XDATATYPE type,void* pControl);
	//重置视图
	virtual void ResetView();
	//重置左侧面板
	virtual void ResetLeftWnd();
	//重置场景面板
	virtual void ResetSceneWnd();
	//切换视图，清空属性面板
	virtual void ClearProperityWnd();
	//获取页面名称
	virtual CString GetTitle();
	//设置页面名称
	virtual void SetTitle(CString szTitle);
	//操作
	virtual void Operate(OPERATETYPE type,void* pData);
	//改变UI
	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);
	//清空连接通道
	virtual void ClearConChannel();
	//清空用户登录状态
	virtual void  ClearUserLoginStatus();
	//注销
	virtual void ClearNode();
	virtual void ClearCloumn();
	//清空节点组
	virtual void ClearNodeGroup();
	//初始化
	virtual void Init();
	//翻译重载界面
	virtual void ReloadInterface();
	//获取用户列表
	virtual MAP_SUBUSER& GetMapSubUser();
	//获取权限当前用户权限列表
	virtual MAP_POWER& GetMapPower();
	//设置属性用户
	virtual void SetPropertyValue(CString szUserName);
	//拖拽结束
	virtual void DragEnd(CPoint& point,CRect& rect);
	//获取底图集合
	virtual MAP_IMAGE& GetMapImage();
	//获取设备通道数
	virtual int GetHardWareChannel();
	//发送OSD底图
	virtual void SendDataOfOSDImage(int nIndex);
	//输入源切到输出
	virtual void SetMatrixInputToOutput(int nInputChannel);
	//设置视图颜色
	virtual void SetViewColor(Color& color);
	//设置视图颜色
	virtual Color GetViewColor();
	//调用场景
	//virtual void OpenScene(CString szSceneName);
	//获取客户端集合
	virtual VEC_CLIENT& GetVecClient();

public:

	constexpr inline MAP_CHANNEL& GetMapChannel() { return m_MapChannel; }
	constexpr inline VEC_PART& GetVecChannel() { return m_VecChannel; }
	constexpr inline VEC_PART& GetVecLoginUser() { return m_VecLoginUser; }
	constexpr inline VEC_PART& GetVecNodeStatus() { return m_VecNodeStatus; }
	constexpr inline MAP_USERLOGINSTATUS& GetMapUserLoginStatus() { return m_MapUserLoginStatus; }
	constexpr inline MAP_RESULATIONINFO& GetMapResoluationInfo() { return m_MapResoluationInfo; }
	constexpr inline VEC_NODELIST& GetVecNodeList() { return m_VecNodeList; }
	constexpr inline VEC_NODEID& GetVecNodeID() { return m_VecNodeID; }	
	constexpr inline VEC_CHANNEL& GetVecCheBridge() { return m_VecCheBridge; }
	constexpr inline void SetLBtnDown(BOOL b) { m_bLBtnDown=b; }
	constexpr inline BOOL GetLBtnDown() { return m_bLBtnDown; }
	constexpr inline void SetCreateDragRect(BOOL b) { m_bCreateDragRect=b; }
	constexpr inline BOOL GetCreateDragRect() { return m_bCreateDragRect; }
	inline RECTF GetDragRect() { return m_DragRect; }
	inline MAP_NODEGROUP& GetMapNodeGroup() { return m_MapNodeGroup; }
	inline MAP_NODE& GetMapNode() { return m_MapNode; }
	inline MAP_NODEALL& GetMapNodeAll() { return m_MapNodeAll; }
	inline MAP_NODEMAINSEC& GetMapNodeMainSec(){return m_MapNodeMainSec;}
	inline MAP_GROUPMAINSEC& GetMapGroupMainSec(){return m_MapGroupMainSec;}
	inline MAP_TAKEOVER& GetMapTakeOver(){return m_MapTakeOver;}
	inline MAP_MATRIX& GetMapMatrix() { return m_MapMatrix; }
	inline MAP_KEYVALUE& GetMapKeyValue(){return m_MapKeyValue;}

private:
	//缩放
	void ChangeScale(int nType);
	//保存缩放
	void SaveDataOfScale(int nType);
	//点击选中节点
	void SetNodeSelected(XNode* pNode);
	//输入菜单
	void ShowMeunOfIn();
	//输出菜单
	void ShowMeunOfOut();
	//获取输入被接管个数
	int GetTakeOverByID(int nNodeID);
	//获取成员个数
	int GetNodeNumByGroupID(int nGroupID,BOOL bMainSecond);
	//根据ID获取通道
	int GetNodeChannelByID(int nNodeID);
	//保存所有接管到文件
	void SaveAllTakeOver();


private:
	//获取节点总数（在线和不在线）
	void OperateOfGetAllNode();
	//获取设备信息
	void OperateOfGetDeviceInfo();
	//返回数据-设备信息
	void OperateOfReDeviceInfo(char* pData);
	//获取连接节点状态
	//void OperateOfGetNodeByChannel();
	//返回数据-连接节点状态
	void OperateOfReNodeByChannel(char* pData);
	//返回数据-节点信息
	void OperateOfReNodeInfo(char* pData);
	//返回数据-节点详细信息
	void OperateOfReNodeDetailInfo(char* pData);
	//返回数据-节点状态
	void OperateOfReNodeStatus(char* pData);
	//获取登录用户
	void OperateOfGetLoginUser();
	//返回数据-登录用户
	void OperateOfReLoginUser(char* pData);
	//返回数据-登录用户状态
	void OperateOfReLoginUserStatus(char* pData);
	//返回数据-节点登录
	void OperateOfReNodeLogin(char* pData);
	//返回数据-节点退出
	void OperateOfReNodeLogOut(char* pData);
	//返回数据-接管
	void OperateOfReTakeOver(char* pData);
	//返回数据-取消接管
	void OperateOfReTakeOverCancel(char *pData);
	//返回数据-预览
	void OperateOfRePreview(char* pData);
	//返回数据-更改节点名称
	void OperateOfReAlterNodeName(char* pData);
	//输出菜单
	void OperateOfMeunOutOfLogout();
	//获取矩阵切换状态
	void OperateOfGetMatrixStatus();
	//返回数据-矩阵切换状态
	void OperateOfReMatrixStatus(char* pData);
	//返回数据-矩阵切换
	void OperateOfReMatrix(char* pData);
	//osd底图
	void OperateOfOSDImage();
	//返回数据-osd底图
	void OperateOfReOSDImage(char* pData);
	//返回数据-隐藏osd底图
	void OperateOfReHideOSDImage(char* pData);
	//读取节点组
	void OperateOfReadNodeGroup();
	//读取在线节点组
	void OperateOfReadOnLineNodeGroup();
	//返回数据-节点组
	void OperateOfReReadNodeGroup(char* pData);
	//返回数据-节点组信息
	void OperateOfReNodeGroupInfo(char* pData);
	//获取主副屏列表
	void OperateOfMainAndSecondList();
	//返回数据-主副屏列表
	void OperateOfReMainAndSecondList(char* pData);
	//返回数据-主副屏
	void OperateOfReMainAndSecond(char* pData);
	//返回数据-更新组成员信息
	void OperateOfReRefreashGroup();
	//获取设备运行情况
	void OperateOfSystemStatus();
	//返回数据-设备运行
	void OperateOfReSystemStatus(char* pData);
	//保存场景
	void OperateOfSaveScene();
	//调用场景
	void OperateOfOpenScene();
	//设备互联
	void OperateOfDeviceConn();
	//作为服务器
	void OperateOfReAsServer(char* pData);
	//客户端
	void OperateOfReAsClient(char* pData);



public:

	BOOL GetLogin();
	float GetScale();
	int GetUserIDByName(CString szUserName);
	//获取输入高度
	int GetHightOfNodeIn();
	//获取输出高度
	int GetHightOfNodeOut();
	int GetWidthOfNodeIn();
	int GetWidthOfNodeOut();
	//创建线程
	void BeginQueryNodeThread();
	//查询所有节点
	void QueryNodeAll();
	//创建查询节点详细信息线程
	void BeginNodeNodeDetailInfoThread();
	//查询节点信息
	void QueryNodeDetailInfo();

public:

	//获取设备类型
	CString GetMatrixType();
	//获取通道连接数
	int GetChannelConnect();
	//获取连接通道序号
	std::vector<int> GetVecConnectChannel();
	//获取总用户数量
	int GetAllUserCount();
	//当前用户
	CString GetCurUser();
	//获取用户数量
	int GetUserCount();
	//获取用户登录状态
	int GetLoginUser(int nType);
	//获取全部节点
	int GetNodeAll();
	//获取节点个数
	int GetNodeOnline(TERMTYPE type);
	//获取组数量
	int GetNodeGroupByType(NODEGROUP type);
	//初始化连接通道位置集合
	void InitVecChannelAbridge(int nRow,int nColumn,POINTF& point);
	//根据通道获取节点
	XNode* GetNodeByChannel(int nChannel);
	//设置输入节点并发柱形图数据
	void InsertNodeColumnData();
	//初始添加饼图数据
	void InsertDevicePieData();
	//插入节点组数据
	void InsertNodeGroupColumnData();

private:
	void InitData();
	void InitMapResoluationInfo();
	void InitKeyValue();
	void InvalidateView();
	void ResetViewSize();
	void SetCursor(CURSORTYPE type);
	HCURSOR GetCursor(CURSORTYPE type);
	void MoveSignal(POINTF& point1,POINTF& point2);
	void PointInCloumn(POINTF& point);
	void PointInRect(POINTF& point);
	void RectScale(RECTF& rect,float dwScale);
private:
	void ClearMapChannel();
	void ClearMapNode();
	void ClearNodeList();
	void ClearNodeID();
	void ClearMapUserLoginStatus();
	void ClearMapResoluationInfo();
	void ClearMapMatrix();
	void ClearMapImage();
	void ClearMapNodeGroup();
	void ClearMapNodeAll();
	void ClearVecCheBridge();
	void ClearMapGroupMainSec();
	void ClearMapNodeMainSec();
	void ClearMapTakeOver();

	void ClearVecClient();
	void ClearVecServer();

private:

	//硬件节点总数
	int m_nHardWareChannel=0;
	//矩阵型号
	CString m_szMatrixModel=_T("");
	//鼠标按下位置
	POINTF m_Point=POINTF(0,0);
	//鼠标按下位置
	POINTF m_TempPoint=POINTF(0,0);;
	//选中的节点
	XNode* m_pNodeSel=NULL;
	//缩放
	int m_nScale=100;
	//左键按下
	BOOL m_bLBtnDown=FALSE;
	//创建拖拽框
	BOOL m_bCreateDragRect=FALSE;
	//拖拽框区域
	RECTF m_DragRect;
	XBaseMap* m_pBaseMapDlg=NULL;
	//记录时间
	DWORD m_dwCurTime=0;
	//所有节点
	int m_nNodeAll=0;
	//拖拽接管节点ID
	//int nTakeOverID=0;
	//被接管ID
	//int nTargetID=0;

	//互联窗口
	XDeviceConn* m_pDeviceConn=NULL;

private:
	//通道连接状态
	MAP_CHANNEL m_MapChannel;
	//节点集合(节点ID),只是在线节点
	MAP_NODE m_MapNode;
	//节点组（存放主副屏输入节点）
	MAP_NODEMAINSEC m_MapNodeMainSec;
	//连接节点通道(获取信息每次最多24)
	VEC_PART m_VecChannel;
	//用户登录(用户ID)
	MAP_USERLOGINSTATUS m_MapUserLoginStatus;
	//查询登录用户状态（分开）
	VEC_PART m_VecLoginUser;
	//查询节点状态
	VEC_PART m_VecNodeStatus;
	//输出节点分辨率信息
	MAP_RESULATIONINFO m_MapResoluationInfo;
	//矩阵切换关系(通道号)
	MAP_MATRIX m_MapMatrix;
	//底图集合
	MAP_IMAGE m_MapImage;
	//节点组(节点名称)
	MAP_NODEGROUP m_MapNodeGroup;
	//节点主副屏组
	MAP_GROUPMAINSEC m_MapGroupMainSec;
	//节点信息（64个16位表示全部节点ID）
	VEC_NODELIST m_VecNodeList;
	//根据16位信息 获取全部节点ID
	VEC_NODEID m_VecNodeID;
	//节点集合（全部节点，包括在线和不在线）
	MAP_NODEALL m_MapNodeAll;
	//连接通道缩略图
	VEC_CHANNEL m_VecCheBridge;
	//接管信息
	MAP_TAKEOVER m_MapTakeOver;
	//键盘键值
	MAP_KEYVALUE m_MapKeyValue;

	//作为服务端
	VEC_CLIENT m_VecClient;
	//作为客户端
	VEC_SERVER m_VecServer;

};
