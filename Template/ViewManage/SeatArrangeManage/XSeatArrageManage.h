#pragma once
#include "XBaseSeatArrageManage.h"
#include "XDelegateBackGround.h"
#include "XDelegateArragePageTwo.h"
#include "XDelegateArragePageOne.h"

class XMultiVideoWindowFrame; 
class XMenuWnd;
class XSeatMap;
class XSeatArrage;
class XSeatDraw;
class XAlignLeft;
class XBaseWnd;
class XSetScreenArrage;
class XSeatArrageDlg;

class XSeatArrageManage:public XBaseSeatArrageManage,
						public XDelegateBackGround,
						public XDelegateArragePageTwo,
						public XDelegateArragePageOne
{
public:
	XSeatArrageManage();
	virtual ~XSeatArrageManage();

public:

	//��ͼ����
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, int noffsetY);
	//��ͼ��ȡ��С
	virtual CSize ViewGetSize();
	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//��ͼ˫��
	virtual void ViewLButtonDblClk(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//��ͼ�������
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//��ͼ����ƶ�
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//��ͼ����뿪
	virtual void ViewMouseLeave();
	//������
	virtual BOOL ViewMouseWheel(short zDelta);
	//��ͼ��������
	virtual void ViewKeyUp(UINT nChar);
	//��ͼ�Ҽ�����
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY);
	//������
	virtual void ControlDataChange(XDATATYPE type, void* pControl);
	//���¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl);
	//����
	virtual void Operate(OPERATETYPE type, void* pData);
	//�ı�UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI);
	//��������
	virtual void SaveData(CArchive& arch);
	//��ȡ����
	virtual void GetData(CArchive& arch);
	//��������
	virtual void ResetData();
	//��ק����
	virtual void DragEnd(CPoint& point,CRect& rect);
	//������ͼ
	virtual void ResetView();
	//����������
	virtual void ResetLeftWnd();
	//���ó������
	virtual void ResetSceneWnd();
	//�л���ͼ������������
	virtual void ClearProperityWnd();
	//��ʼ��
	virtual void Init();
	//�������ؽ���
	virtual void ReloadInterface();
	//��ȡҳ������
	virtual CString GetTitle();
	//���ñ���
	virtual void SetTitle(CString szTitle);
	//��ʾ����ϯ
	virtual void ShowGroupSeatArrage(CString szGroup);
	//����ѡ�нڵ�
	virtual void SetNodeSelected(CString szNodeName);
	//�����ϯ����
	virtual void ClearInfo(CString szGroupName);
	//ע�����ҳ��
	virtual void ClearPage();
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
	//������ͼ��ɫ
	virtual void SetViewColor(Color& color);
	//������ͼ��ɫ
	virtual Color GetViewColor();
	//��ȡ��ϯ����ɾ���ڵ�
	//virtual VEC_DEL& GetVecDel();

	//������ɾ���ڵ�
	virtual void DelNodeFromGroup(CString szGroupName,int nNodeID);
	//�ж��ܲ���ɾ��
	BOOL JudgetDelNodeFromGroup(CString szGroupName,int nNodeID);	
	virtual void AdjustMultiVideoWindowSize();
	virtual MAP_PAGE& GetMapPage();
	virtual MAP_TEMPFRAME& GetMapTempFrame();
	virtual MAP_NODE& GetMapNode();
	virtual MAP_NODEGROUP& GetMapNodeGroup();
	virtual CWnd* GetCWND();

	//��ȡ��ǰ�û�
	virtual int GetCurUserID();
	//��ק�鵽��ϯ��
	virtual void DragGroupToSeat(CString szGroupName,CPoint& point);
	//��ȡ��ǰҳ��
	virtual XPage* GetCurPage();
	//������л�ҳ��
	virtual void SwitchPage(int nPage);
	//����������ز˵���ť
	virtual void HidePopMenuBtn();
	//��ʾ��ť
	virtual void ShowPopMenuBtn();
	//������������Ļ
	virtual void DrawGroupInScreen(CString szGroupName);
	//������ѡ��ҳ����ϯ
	virtual void SetSeatSelected(CString szGroupName);

	//���ز˵���ť
	virtual void HideMenuWnd();
	virtual void HideBtn();
	virtual void Unselected();

	//��ʾ������ϯ��ť
	virtual void ShowSeatDrawWnd();
	virtual void HideSeatDrawWnd();
	virtual void MoveSeatDrawWnd();
	virtual void EnableSeatDrawWnd(BOOL b);

	//��ȡ��ϯҳ�����
	virtual int GetPageIndex();

	//�Ҽ�������ʱ���������Ƹ���ҳ��
	virtual void SetGroupNameByAddGroupIn(CString szName);

public:

	constexpr inline int GetSeatRow(){return m_nSeatRow;}
	constexpr inline int GetSeatColumn(){return m_nSeatColumn;}
	constexpr inline void SetSeatRow(int n){m_nSeatRow=n;}
	constexpr inline void SetSeatColumn(int n){m_nSeatColumn=n;}

private:

	void InitData();
	//ˢ����ͼ
	void InvalidateView();
	//������ͼ��С
	void ResetViewSize();
	//�ı�����
	void ChangeScale(int nTYpe);
	//��������
	void SaveDataOfScale(int nType);
	//����
	void ResetSeatRange();
	//���
	void SetCursor(CURSORTYPE type);
	//���
	HCURSOR GetCursor(CURSORTYPE type);
	//�ƶ��ź�
	void MoveSignal(POINTF& point1,POINTF& point2);
	void MoveSignalOfNew(POINTF& point1, POINTF& point2);
	void MoveSignalOfCopy(POINTF& point1, POINTF& point2);

	//�жϽڵ��Ƿ����鼯����
	BOOL JudgeNodeInVec(VEC_ARRAGE& VecArrage,int nNodeID);
	
	//�����קframe
	void AddDragFrame();

	//����ȫ����ѡ����ϯ
	void SetVecSeatSelect(XSeat* p);
	void SetVecSeatUnselect();
	void SetSeatSelect(XSeat* p,BOOL b);
	//ѡ����Ļ
	void SetVecScreenSelect(XScreen* p);
	void SetVecScreenUnselect();
	void SetScreenSelect(XScreen* p,BOOL b);

	//��������
	XScreen* GetScreenByIndex(int nIndex);
	//������Ļ������Ϣ
	void SetVecArrage();
	//��ȡ���о���
	CString GetArrayInfo();
	//��ȡ��������
	CString GetArrayMatrix();
	//���ݽڵ����ƻ�ȡID
	int GetNodeIDByName(CString szNodeName);
	XNode* GetNodeByID(int nNodeID);

	//ɾ����ϯ
	void DeleteSeat(int nIndex);

	//��ȡԪ�����
	int GetVecSeatIndex(VEC_SEAT& VecSeat);
	//�������м���(ȥ��ɾ����)
	void CopyArray(VEC_ARRAGE& VecArrage,int nNodeID);
	//ɾ����֮�󣬲��ҵ�һ����Ϊ��Ľڵ�
	int GetMasterInArray();
	//���ݽڵ�ID������Ļ
	XScreen* GetScreenByNodeID(int nNodeID);
	//��ȡ����Ϣ
	XNodeGroupInfo* GetNodeGroupInfoByName(CString szGroupName);

public:

	//��ȡ����
	float GetScale();

	//��ϯ��ť�˵�
	XMenuWnd* CreateMenuWnd();
	void CreateMenuWnd(CPoint& point);
	void ShowMenuWnd();
	void ShowMenu();

	void ShowBtn();
	void ShowPopBtn();
	void HidePopBtn();

	//��ͼ
	XSeatMap* CreateSeatMapWnd();
	void OnBtnBaseMap();

	//����
	XSeatArrage* CreateSeatArrageWnd();
	void OnBtnArrage();

	//������ϯ��ť
	void CreateSeatDrawWnd();
	void CreateSeatDrawWnd(CPoint& point);
	void DrawSeat();
	
	//��������������ť
	void CreateAlignWnd();
	RECTF GetRectBySelectedSeat(VEC_SEAT& VecSeat);
	void ShowALignWnd();
	void MoveAlignWnd();
	void HideAlignWnd();

	//������Ӧ����
	void OnAlignLeft();
	void OnAlignHorzion();
	void OnAlignRight();
	void OnAlignTop();
	void OnAlignVertical();
	void OnAlignBottom();

	//����������ť
	void CreateSuspendBtn(XBaseWnd* pWnd,CRect& rect,CString szImage);

	//����ԭ��λ��
	void CacluOrgPoint(CSize& size);

	
public:

	//���Ը���
	void UpdateMultiWindowByPropertyChange(XSeat* pSeat,int nType);

private:

	void OperateOfSaveSeat();
	void OperateOfSendSeat();
	void OperateOfClearSeat();
	void OperateOfSetBg();
	void OperateOfSetBtnStatus();

	void OperateOfAlignLeft();
	void OperateOfAlignHorizon();
	void OperateOfAlignRight();
	void OperateOfAlignUp();
	void OperateOfAlignDown();
	void OperateOfAlignVertical();
	void OperateOfAlignSame();

	void OperateOfAlignHSame();
	void OperateOfAlignVSame();
	void OperateOfAlignWidth();
	void OperateOfAlignHeight();

	void OperateOfScreenArray();
public:

	void ClearDragFrame();

private:

	void ClearMapPage();
	void ClearVecArrage();
	void ClearMapAlign();

private:

	//����
	int m_nScale=100;
	//��
	int m_nSeatRow=0;
	//��
	int m_nSeatColumn=0;
	//�������
	POINTF m_Point;
	//�������
	BOOL m_bLBtnDown=FALSE;
	//�������ʼ��
	POINTF m_BeginPoint=POINTF(0,0);
	//��������
	POINTF m_EndPoint=POINTF(0,0);
	//��ϯ����
	RECTF m_rect;
	//�½��������
	RECTF m_EndRect;
	//�ƶ����
	RECTF m_DragRect;
	//��Ļ�����ҳ��ƫ��
	POINTF m_DeviationPoint=POINTF(0,0);

private:
	//�����������ϯ��ť
	static BOOL m_bFlag;

	//ҳ�����
	static int m_nPageIndex;

	const int m_nFirstPage=1;
	const int m_nSecondPage=2;

	//�����״
	static CURSORTYPE m_CursorType;
	//������źŵ�λ��,���������ź�
	static POSITIONTYPE m_PositionType;
	
	//��קFrame
	XMultiVideoWindowFrame* m_pDragFrame=NULL;

	//��ǰҳ�棨Ŀǰ����ҳ�棩
	static XPage* m_pPage;
	static BOOL m_bFirstPage;

	//����Ctrl�Ƿ񣬴����϶�ҳ��
	static BOOL m_bCreateDrag;
	//��Ļ����
	static XScreen* m_pTempScreen;
	//��ϯ����
	static XSeat* m_pTempSeat;

	//�˵���ť
	static XMenuWnd* m_pMenuWnd;
	static XSeatMap* m_pSeatMap;
	static XSeatArrage* m_pSeatArrage;

	//������ϯ��ť
	static XSeatDraw* m_pSeatDraw;
	static BOOL m_bMenuFlag;

	//�Ƿ񴴽����밴ť
	static BOOL m_bCreateAlignWnd;

private:
	//��ϯҳ��
	MAP_PAGE m_MapPage;
	//ѡ����ϯ(�������)
	VEC_SEAT m_VecTempSeat;
	//��ʱFrame���ϡ�����ѡ��ĳ��frame���������
	MAP_TEMPFRAME m_MapFrame;
	//�ڶ�ҳ����
	MAP_TEMPFRAME m_MapSecondFrame;
	//��Ļ����
	VEC_ARRAGE m_VecArrage;
	//����������ť
	MAP_ALIGN m_MapAlign;
};
