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
	//������
	virtual void ControlDataChange(XDATATYPE type,void* pControl);
	//���¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type,void* pControl);
	//������ͼ
	virtual void ResetView();
	//����������
	virtual void ResetLeftWnd();
	//���ó������
	virtual void ResetSceneWnd();
	//�л���ͼ������������
	virtual void ClearProperityWnd();
	//��ȡҳ������
	virtual CString GetTitle();
	//����ҳ������
	virtual void SetTitle(CString szTitle);
	//����
	virtual void Operate(OPERATETYPE type,void* pData);
	//�ı�UI
	virtual void UpdateControlUI(CMDUITYPE type,CCmdUI* pCmdUI);
	//�������ͨ��
	virtual void ClearConChannel();
	//����û���¼״̬
	virtual void  ClearUserLoginStatus();
	//ע��
	virtual void ClearNode();
	virtual void ClearCloumn();
	//��սڵ���
	virtual void ClearNodeGroup();
	//��ʼ��
	virtual void Init();
	//�������ؽ���
	virtual void ReloadInterface();
	//��ȡ�û��б�
	virtual MAP_SUBUSER& GetMapSubUser();
	//��ȡȨ�޵�ǰ�û�Ȩ���б�
	virtual MAP_POWER& GetMapPower();
	//���������û�
	virtual void SetPropertyValue(CString szUserName);
	//��ק����
	virtual void DragEnd(CPoint& point,CRect& rect);
	//��ȡ��ͼ����
	virtual MAP_IMAGE& GetMapImage();
	//��ȡ�豸ͨ����
	virtual int GetHardWareChannel();
	//����OSD��ͼ
	virtual void SendDataOfOSDImage(int nIndex);
	//����Դ�е����
	virtual void SetMatrixInputToOutput(int nInputChannel);
	//������ͼ��ɫ
	virtual void SetViewColor(Color& color);
	//������ͼ��ɫ
	virtual Color GetViewColor();
	//���ó���
	//virtual void OpenScene(CString szSceneName);
	//��ȡ�ͻ��˼���
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
	//����
	void ChangeScale(int nType);
	//��������
	void SaveDataOfScale(int nType);
	//���ѡ�нڵ�
	void SetNodeSelected(XNode* pNode);
	//����˵�
	void ShowMeunOfIn();
	//����˵�
	void ShowMeunOfOut();
	//��ȡ���뱻�ӹܸ���
	int GetTakeOverByID(int nNodeID);
	//��ȡ��Ա����
	int GetNodeNumByGroupID(int nGroupID,BOOL bMainSecond);
	//����ID��ȡͨ��
	int GetNodeChannelByID(int nNodeID);
	//�������нӹܵ��ļ�
	void SaveAllTakeOver();


private:
	//��ȡ�ڵ����������ߺͲ����ߣ�
	void OperateOfGetAllNode();
	//��ȡ�豸��Ϣ
	void OperateOfGetDeviceInfo();
	//��������-�豸��Ϣ
	void OperateOfReDeviceInfo(char* pData);
	//��ȡ���ӽڵ�״̬
	//void OperateOfGetNodeByChannel();
	//��������-���ӽڵ�״̬
	void OperateOfReNodeByChannel(char* pData);
	//��������-�ڵ���Ϣ
	void OperateOfReNodeInfo(char* pData);
	//��������-�ڵ���ϸ��Ϣ
	void OperateOfReNodeDetailInfo(char* pData);
	//��������-�ڵ�״̬
	void OperateOfReNodeStatus(char* pData);
	//��ȡ��¼�û�
	void OperateOfGetLoginUser();
	//��������-��¼�û�
	void OperateOfReLoginUser(char* pData);
	//��������-��¼�û�״̬
	void OperateOfReLoginUserStatus(char* pData);
	//��������-�ڵ��¼
	void OperateOfReNodeLogin(char* pData);
	//��������-�ڵ��˳�
	void OperateOfReNodeLogOut(char* pData);
	//��������-�ӹ�
	void OperateOfReTakeOver(char* pData);
	//��������-ȡ���ӹ�
	void OperateOfReTakeOverCancel(char *pData);
	//��������-Ԥ��
	void OperateOfRePreview(char* pData);
	//��������-���Ľڵ�����
	void OperateOfReAlterNodeName(char* pData);
	//����˵�
	void OperateOfMeunOutOfLogout();
	//��ȡ�����л�״̬
	void OperateOfGetMatrixStatus();
	//��������-�����л�״̬
	void OperateOfReMatrixStatus(char* pData);
	//��������-�����л�
	void OperateOfReMatrix(char* pData);
	//osd��ͼ
	void OperateOfOSDImage();
	//��������-osd��ͼ
	void OperateOfReOSDImage(char* pData);
	//��������-����osd��ͼ
	void OperateOfReHideOSDImage(char* pData);
	//��ȡ�ڵ���
	void OperateOfReadNodeGroup();
	//��ȡ���߽ڵ���
	void OperateOfReadOnLineNodeGroup();
	//��������-�ڵ���
	void OperateOfReReadNodeGroup(char* pData);
	//��������-�ڵ�����Ϣ
	void OperateOfReNodeGroupInfo(char* pData);
	//��ȡ�������б�
	void OperateOfMainAndSecondList();
	//��������-�������б�
	void OperateOfReMainAndSecondList(char* pData);
	//��������-������
	void OperateOfReMainAndSecond(char* pData);
	//��������-�������Ա��Ϣ
	void OperateOfReRefreashGroup();
	//��ȡ�豸�������
	void OperateOfSystemStatus();
	//��������-�豸����
	void OperateOfReSystemStatus(char* pData);
	//���泡��
	void OperateOfSaveScene();
	//���ó���
	void OperateOfOpenScene();
	//�豸����
	void OperateOfDeviceConn();
	//��Ϊ������
	void OperateOfReAsServer(char* pData);
	//�ͻ���
	void OperateOfReAsClient(char* pData);



public:

	BOOL GetLogin();
	float GetScale();
	int GetUserIDByName(CString szUserName);
	//��ȡ����߶�
	int GetHightOfNodeIn();
	//��ȡ����߶�
	int GetHightOfNodeOut();
	int GetWidthOfNodeIn();
	int GetWidthOfNodeOut();
	//�����߳�
	void BeginQueryNodeThread();
	//��ѯ���нڵ�
	void QueryNodeAll();
	//������ѯ�ڵ���ϸ��Ϣ�߳�
	void BeginNodeNodeDetailInfoThread();
	//��ѯ�ڵ���Ϣ
	void QueryNodeDetailInfo();

public:

	//��ȡ�豸����
	CString GetMatrixType();
	//��ȡͨ��������
	int GetChannelConnect();
	//��ȡ����ͨ�����
	std::vector<int> GetVecConnectChannel();
	//��ȡ���û�����
	int GetAllUserCount();
	//��ǰ�û�
	CString GetCurUser();
	//��ȡ�û�����
	int GetUserCount();
	//��ȡ�û���¼״̬
	int GetLoginUser(int nType);
	//��ȡȫ���ڵ�
	int GetNodeAll();
	//��ȡ�ڵ����
	int GetNodeOnline(TERMTYPE type);
	//��ȡ������
	int GetNodeGroupByType(NODEGROUP type);
	//��ʼ������ͨ��λ�ü���
	void InitVecChannelAbridge(int nRow,int nColumn,POINTF& point);
	//����ͨ����ȡ�ڵ�
	XNode* GetNodeByChannel(int nChannel);
	//��������ڵ㲢������ͼ����
	void InsertNodeColumnData();
	//��ʼ��ӱ�ͼ����
	void InsertDevicePieData();
	//����ڵ�������
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

	//Ӳ���ڵ�����
	int m_nHardWareChannel=0;
	//�����ͺ�
	CString m_szMatrixModel=_T("");
	//��갴��λ��
	POINTF m_Point=POINTF(0,0);
	//��갴��λ��
	POINTF m_TempPoint=POINTF(0,0);;
	//ѡ�еĽڵ�
	XNode* m_pNodeSel=NULL;
	//����
	int m_nScale=100;
	//�������
	BOOL m_bLBtnDown=FALSE;
	//������ק��
	BOOL m_bCreateDragRect=FALSE;
	//��ק������
	RECTF m_DragRect;
	XBaseMap* m_pBaseMapDlg=NULL;
	//��¼ʱ��
	DWORD m_dwCurTime=0;
	//���нڵ�
	int m_nNodeAll=0;
	//��ק�ӹܽڵ�ID
	//int nTakeOverID=0;
	//���ӹ�ID
	//int nTargetID=0;

	//��������
	XDeviceConn* m_pDeviceConn=NULL;

private:
	//ͨ������״̬
	MAP_CHANNEL m_MapChannel;
	//�ڵ㼯��(�ڵ�ID),ֻ�����߽ڵ�
	MAP_NODE m_MapNode;
	//�ڵ��飨�������������ڵ㣩
	MAP_NODEMAINSEC m_MapNodeMainSec;
	//���ӽڵ�ͨ��(��ȡ��Ϣÿ�����24)
	VEC_PART m_VecChannel;
	//�û���¼(�û�ID)
	MAP_USERLOGINSTATUS m_MapUserLoginStatus;
	//��ѯ��¼�û�״̬���ֿ���
	VEC_PART m_VecLoginUser;
	//��ѯ�ڵ�״̬
	VEC_PART m_VecNodeStatus;
	//����ڵ�ֱ�����Ϣ
	MAP_RESULATIONINFO m_MapResoluationInfo;
	//�����л���ϵ(ͨ����)
	MAP_MATRIX m_MapMatrix;
	//��ͼ����
	MAP_IMAGE m_MapImage;
	//�ڵ���(�ڵ�����)
	MAP_NODEGROUP m_MapNodeGroup;
	//�ڵ���������
	MAP_GROUPMAINSEC m_MapGroupMainSec;
	//�ڵ���Ϣ��64��16λ��ʾȫ���ڵ�ID��
	VEC_NODELIST m_VecNodeList;
	//����16λ��Ϣ ��ȡȫ���ڵ�ID
	VEC_NODEID m_VecNodeID;
	//�ڵ㼯�ϣ�ȫ���ڵ㣬�������ߺͲ����ߣ�
	MAP_NODEALL m_MapNodeAll;
	//����ͨ������ͼ
	VEC_CHANNEL m_VecCheBridge;
	//�ӹ���Ϣ
	MAP_TAKEOVER m_MapTakeOver;
	//���̼�ֵ
	MAP_KEYVALUE m_MapKeyValue;

	//��Ϊ�����
	VEC_CLIENT m_VecClient;
	//��Ϊ�ͻ���
	VEC_SERVER m_VecServer;

};
