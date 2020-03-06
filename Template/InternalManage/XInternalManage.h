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

	//��ͼ����
	virtual void ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY);

	//��ͼ��ȡ��С
	virtual CSize ViewGetSize();

	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//��ͼ˫��
	virtual void ViewLButtonDblClk(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//��ͼ�������
	virtual void ViewLButtonUp(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//��ͼ����ƶ�
	virtual void ViewMouseMove(UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);

	//��ͼ����뿪
	virtual void ViewMouseLeave();

	//������
	virtual BOOL ViewMouseWheel(short zDelta);

	//��ͼ��������
	virtual void ViewKeyUp(UINT nChar);

	//��ͼ�Ҽ�����
	virtual void ViewRButtonUp(CWnd* pWnd,UINT& nFlags,CPoint& point,CRect& rect,int noffsetX,int noffsetY);


public:

	//��ʼ��
	virtual void Init();

	//��ʼ��ͣ�����
	virtual void InitPane();

	//�豸����
	virtual void SetIPAddr1(CString szIP);
	virtual void SetIPAddr2(CString szIP);
	virtual void SetPort1(int n);
	virtual void SetPort2(int n);

	//�豸�ڵ�ͨ������
	virtual void SetHardWareChannel(int n);

	//�����ͺ�
	virtual void SetMatrixModel(CString szModel);

	//fpga�汾��
	virtual void SetFPGAVersion(CString szVer);

	//�رճ���
	virtual BOOL AppClose();

	//��ȡCWnd
	virtual CWnd* GetCWND();

	//��ȡ���
	virtual HWND GetHWND();

	//Ribbon��ʾ�����
	virtual void RibbonBarShowCategory(DWORD_PTR dwData);

	//�������ؼ����ݱ仯
	virtual void ControlDataChange(XDATATYPE type);

	//�ؼ����ݸı�
	virtual void ControlDataChange(XDATATYPE type,void* pControl);

	//����
	virtual void Operate(OPERATETYPE type,void* pData);

	//��������
	virtual void ChangeTheme(int nType);

	//���ؽ���
	virtual void ReloadInterface();

	//�����ǩ����
	virtual void ReloadDocTitle();

	//�����������͸��¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type);

	//���¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type,void* pControl);

	//����UDP����
	virtual void HandleUDPData(unsigned char* pData,int nDataLen,SOCKADDR_IN addr);

	//����UDP��Ϣ
	virtual void HandleUDPMsg(WPARAM wParam,LPARAM lParam);

	//��������
	virtual BOOL SendData(char* pData,int nDataLen);

	//���³����ȡIP
	virtual CString GetCurIP();
	virtual int GetCurPort();

	//��ȡ�豸IP
	virtual CString GetDeviceIP();

	//��ȡ�豸�˿�
	virtual int GetDevicePort();

	//��ȡ�豸2IP
	virtual CString GetDevice2IP();

	//��ȡ�豸2�˿�
	virtual int GetDevice2Port();

	virtual CString GetDeviceMask();
	virtual CString GetDevice2Mask();
	virtual CString GetDeviceGateway();
	virtual CString GetDevice2Gateway();

	//����Ӧ����������ʱ��
	virtual void SetSendApplyTime(DWORD dwTime);

	//ͨѶ����ѡ��
	virtual void ConnectNetSelect();

	//��ȡ���翪��״̬
	virtual BOOL GetNetStatus();

	//�豸ѡ��
	virtual void SetDeviceSelect(int nSelect);

	//�������ؼ�״̬
	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);

	//���õ�ǰ�û�
	virtual void SetCurUserName(CString szName);

	virtual CString GetCurUserName();

	//�����û�ID
	virtual void SetCurUserID(int n);

	//��ȡ�û�ID
	virtual int GetCurUserID();

	//���õ�¼
	virtual void SetLogin(BOOL b);

	virtual BOOL GetLogin();

	//����״̬��
	//virtual void SetStatusBarInfo();

	//���ҳ��
	virtual void AddDocument();

	//��ȡ��ͼ
	virtual CTemplateView* GetView();

	//ע����սڵ�
	virtual void ClearNode();

	//�������ͼ
	virtual void ClearCloumn();

	//�������ͨ��
	virtual void ClearConChannel();

	//�����
	virtual void ClearTree();

	//��սڵ���
	virtual void ClearNodeGroup();

	//��յ�¼״̬
	virtual void ClearUserLoginStatus();

	//����û��и���
	virtual void ClearUserIDALL();

	//�����ϯ����
	virtual void ClearInfo(CString szGroupName);

	//ע�����ҳ��
	virtual void ClearPage();

	//��ճ�����
	virtual void ClearSceneTree();

	//������ϯ����
	virtual void UpdateGroupNameAfterAddArrage(CString szName);

	//ƥ����ϯ����
	virtual void MatchSeatNameByGroupName();

	//������������
	virtual void UpdateGroupNameAfterChange(CString szGroupName,CString szName);

	//������Ļ������Ϣ
	virtual void UpdateGroupArrageByRemoveNode(CString szGroupName,int nNodeID);

	//�Ƴ��ڵ���µڶ�ҳ
	virtual void UpdateScreenAfterRemoveNode(int nNodeID);

	//����������ʾ������
	virtual void UpdateShowMasterAfterRemoveNode(int nMaster);

	//��ȡ�û��б�
	virtual MAP_SUBUSER& GetMapSubUser();

	//��ȡ��ǰ�û�Ȩ���б�
	virtual MAP_POWER& GetMapPower();

	//��ȡ�ڵ㼯��
	virtual MAP_NODE& GetMapNode();
	virtual MAP_NODEALL& GetMapNodeAll();

	//��ȡ�ڵ�������
	virtual MAP_NODEMAINSEC& GetMapNodeMainSec();

	//��ȡ�ڵ��鼯��
	virtual MAP_NODEGROUP& GetMapNodeGroup();

	//��ȡ����������
	virtual MAP_GROUPMAINSEC& GetMapNodeGroupMainSec();

	//��ȡ��ϯ����ɾ���ڵ�
	virtual VEC_DEL& GetVecDel();

	//��ȡ���û�����
	virtual VEC_USERIDALL& GetVecUserIDAll();

	//��ȡ�����л�״̬
	virtual MAP_MATRIX& GetMapMatrix();

	//��ȡ����
	virtual MAP_BASEVIEW& GetBaseView();

	//�����б�����û�
	virtual void InsertItemToTree(CString szUserName);

	//���û�����ɾ��
	virtual void DeleteItemFromTree(CString szUserName);

	//����������������û�
	virtual void SetPropertyValue(CString szUserName);

	//����ѡ�нڵ�
	virtual void SetNodeSelected(CString szNodeName);

	//��ק����
	virtual void DragEnd(CPoint& point,CRect& rect);

	//��ʾ����ϯ
	virtual void ShowGroupSeatArrage(CString szGroup);

	//������ͼ��ɫ
	virtual void SetViewColor(Color& color);

	//������ɾ���ڵ�
	virtual void DelNodeFromGroup(CString szGroupName,int nNodeID);

	//�ж��ܲ���ɾ��
	virtual BOOL JudgetDelNodeFromGroup(CString szGroupName,int nNodeID);

	//������������Ԥ��ǽ��ɫ
	virtual void SetMultiVideoWindowBkColor(Uint8 r,Uint8 g,Uint8 b);

	//ˢ��
	virtual void AdjustMultiVideoWindowSize();

	virtual void AdjustMultiVideoWindowSize(int nWidth,int nHeight);

	//����ҳ�汳��
	virtual void SetMultiVideoFramesBg();

	//��ק�鵽��ϯ��
	virtual void DragGroupToSeat(CString szGroupName,CPoint& point);

	//������л�ҳ��
	virtual void SwitchPage(int nPage);

	//������������Ļ
	virtual void DrawGroupInScreen(CString szGroupName);

	//������ѡ��ҳ����ϯ
	virtual void SetSeatSelected(CString szGroupName);

	//���ز˵���ť
	virtual void HideMenuWnd();

	//��ȡ��ϯҳ�����
	virtual int GetPageIndex();

	//������ϯ������
	virtual void ResetRibbonBar();

	//����������ز˵���ť
	virtual void HidePopMenuBtn();

	//��ʾ��ť
	virtual void ShowPopMenuBtn();

	//���ó���
	virtual void OpenScene(int nData);

	//���¾���������Ϣ
	virtual void ResetMatrixArray();

	//���ݷֻ�״̬���� ҳ��״̬
	virtual void ResetMatrixSwitchStatus();

	//��ȡ��ǰƴ����ͼ����
	virtual float GetCurScale();

	//��ȡƴ�ӳ���
	virtual MAP_SPLITSCENE& GetMapSplitScene();

	virtual MAP_SPLITSCENEGROUP& GetMapSplitSceneGroup();

	//����Ԥ��ǽ����
	virtual void SetMultiVideoWindowScale(float fScale);

	//�Ҽ�������ʱ���������Ƹ���ҳ��
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
	//����ƴ�ӳ���
	void OperateOfOpenScene();
	void OperateOfOpenSceneOne();

public:

	void CloseSplit(XBaseViewManage* pManage);
	void CloseSplit();

	int DecideWallExistence(CString szWall);

	



private:

	//��ʼ������
	void InitManage();

	//��ʼ������
	void InitAppData();

	//��ʼ������Ip
	void InitIPAddr();

	//��ʼ��ҳ��
	void InitDocument();

	//��ȡ����
	BOOL GetAppData();

	//��ȡӦ������
	void GetAppData(CArchive& arch);

	//ע����������
	void SaveData();

	//����Ӧ������
	BOOL SaveAppData();

	//����Ӧ������
	void SaveAppData(CArchive& arch);

	//����Ӧ������
	void ResetAppData();

	//����ĵ�����
	void AddDocument(XBaseViewManage* pBase);

	//��ȡView
	CView* GetDocumentFrontView(CDocument* p);

	//�����ĵ�����
	CString GetDocTitle(CString szTitle);

	//���������л���ͼ
	XBaseViewManage* GetBaseViewManageByData(DWORD_PTR dwData,int& nIndex);

	//BOOL CheckDataSum(char* pData,int& nLen);

	//unsigned short CheckSum(unsigned char* pData,int nLen);

	//��ӻ���ҳ��
	XMultiVideoWindowFrames* AddPageToMultiVideoWindow(int nIndex,int nWidth,int nHeight);

	//�ж��������޳���
	BOOL DecideSplitGroupHasOneScene(CString szName);

public:

	void SetViewManage(XBaseViewManage* p);
	//��ʼ���߳�
	BOOL BeginHeartThread();
	//ֹͣ�߳�
	void StopHeartThread();
	//�ر��߳�Event
	void CloseHeartThreadEvent();

private:

	//���
	void Clear();
	void ClearMapData();
	void ClearMapBaseView();
	void ClearNetConfig();
	void ClearSplitScene();


	//��ȡƴ�������
	int GetIndexByAdd();
	
private:

	//����������
	XBaseRibbonBarManage* m_pRibbonBarManage=nullptr;
	//Ini����
	XIniManage* m_pIniManage=nullptr;
	//�������
	XBaseNetManage* m_pBaseNetManage=nullptr;
	//�������ݹ���
	XReciveDataManage* m_pReciveDataManage=nullptr;
	//�û�����
	XUserManage* m_pUserManage=nullptr;
	//��ǰ��ͼ��
	XBaseViewManage* m_pBaseViewManage=nullptr;
	//�ڵ����
	XBaseNodeManage* m_pNodeManage=nullptr;
	//��ϯ����
	XBaseSeatArrageManage* m_pSeatArrageManage=nullptr;
	//�����л�
	XBaseMatrixManage* m_pMatrixManage=nullptr;
	//��Ƶ����
	XVideoPlayer m_VideoPlayer;
	//��ϯҳ��Ԥ��ǽ
	XMultiVideoWindow* m_pMultiVideoWindow=nullptr;
	//�������Ի���
	XDeviceNet* m_pDeviceNet=nullptr;
	//ƴ��ǽ���� ���ڼ�����
	//XBaseSplitManage* m_pSplitManage=nullptr;


private:

	//��ǰ����
	CString m_szIPAddr1=_T("");
	CString m_szIPAddr2=_T("");
	CString m_szMask1=_T("");
	CString m_szMask2=_T("");
	CString m_szGateway1=_T("");
	CString m_szGateway2=_T("");
	int m_nPort1=0;
	int m_nPort2=0;
	DWORD m_dwApplyTime=0;
	//�豸ѡ��
	int m_nDeviceSelect=0;
	//��ǰ�û���
	CString m_szUserName=_T("");
	//��ǰ�û�ID
	int m_nUserID=0;
	//�Ƿ��¼
	BOOL m_bLogin=FALSE;
	//��ǰ�豸IP
	CString m_szCurDeviceIP=_T("");
	//��ǰ�豸�˿�
	int m_nCurDevicePort=0;
	//����ʱ��
	LONG m_dHeartTime=0;
	//�Ƿ�����
	BOOL m_bOnline=FALSE;
	//�豸�ڵ����
	int m_nHardWareChannel=0;
	//�豸�ͺ�
	CString m_szMatrixModel=_T("");
	//fpga�汾��
	CString m_szFPGAVersion=_T("");
	//��������Э��ţ��ְ���
	int m_nProtocol=0;
	//�ܰ���
	int m_nPacket=0;
	//�����
	int m_nPacketIndex=0;
	//��ͼ������
	XTabCtrl* m_pViewTabCtrl=nullptr;
	//��־�Ի���
	XLog* m_pLogDlg=nullptr;
	//����ƴ�ӳ����Ի���
	XSaveSplitScene* m_pSplitScene=nullptr;

public:

	//�����߳�
	BOOL m_bRunning=TRUE;
	HANDLE m_HeartThreadEvent=nullptr;
	CWinThread* m_HeartThread=nullptr;

private:

	//��ͼ��
	MAP_BASEVIEW m_MapBaseView;
	//���ְܷ�
	MAP_DATA m_MapData;
	//��������
	VEC_NETCONFIG m_VecNetConfig;
	//ƴ�ӳ���
	MAP_SPLITSCENE m_MapSplitScene;
	//ƴ�ӳ�����
	MAP_SPLITSCENEGROUP m_MapSplitSceneGroup;

private:

	//��ǰƴ�ӽ������,��һ��ƴ�����Ϊ3
	int m_nSplitIndex=3;

};