#pragma once
#include "XBaseViewManage.h"

class XDelegateSeatArrageManage;

class XBaseSeatArrageManage:public XBaseViewManage
{
public:
	XBaseSeatArrageManage();
	virtual ~XBaseSeatArrageManage();

public:

	//��ͼ����
	virtual void ViewDraw(CDC* pDC, CRect rect, int noffsetX, int noffsetY)=0;

	//��ͼ��ȡ��С
	virtual CSize ViewGetSize()=0;

	//��ͼ�������
	virtual void ViewLButtonDown(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//��ͼ˫��
	virtual void ViewLButtonDblClk(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//��ͼ�������
	virtual void ViewLButtonUp(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//��ͼ����ƶ�
	virtual void ViewMouseMove(UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//��ͼ����뿪
	virtual void ViewMouseLeave()=0;

	//������
	virtual BOOL ViewMouseWheel(short zDelta)=0;

	//��ͼ��������
	virtual void ViewKeyUp(UINT nChar)=0;

	//��ͼ�Ҽ�����
	virtual void ViewRButtonUp(CWnd* pWnd, UINT& nFlags, CPoint& point, CRect& rect, int noffsetX, int noffsetY)=0;

	//����������
	virtual void ControlDataChange(XDATATYPE type, void* pControl)=0;

	//���¿ؼ�������ʾ
	virtual void UpdateControlDataShow(XDATATYPE type, void* pControl)=0;

	//����
	virtual void Operate(OPERATETYPE type, void* pData)=0;

	//�ı�UI
	virtual void UpdateControlUI(CMDUITYPE type, CCmdUI* pCmdUI)=0;

	//��ק����
	virtual void DragEnd(CPoint& point,CRect& rect)=0;

	//������ͼ
	virtual void ResetView()=0;

	//����������
	virtual void ResetLeftWnd()=0;

	//���ó������
	virtual void ResetSceneWnd()=0;

	//�л���ͼ������������
	virtual void ClearProperityWnd()=0;

	//��ʼ��
	virtual void Init()=0;

	//�������ؽ���
	virtual void ReloadInterface()=0;

	//��ȡҳ������
	virtual CString GetTitle()=0;

	//���ñ���
	virtual void SetTitle(CString szTitle)=0;

	//��������
	virtual void SaveData(CArchive& arch)=0;

	//��ȡ����
	virtual void GetData(CArchive& arch)=0;

	//��������
	virtual void ResetData()=0;

	//����ѡ�нڵ�
	virtual void SetNodeSelected(CString szNodeName)=0;

	//��ʾ����ϯ
	virtual void ShowGroupSeatArrage(CString szGroup)=0;

	//�����ϯ����
	virtual void ClearInfo(CString szGroupName)=0;
	
	//ע�����ҳ��
	virtual void ClearPage()=0;

	//������ϯ����
	virtual void UpdateGroupNameAfterAddArrage(CString szName)=0;

	//ƥ����ϯ����
	virtual void MatchSeatNameByGroupName()=0;

	//������������
	virtual void UpdateGroupNameAfterChange(CString szGroupName,CString szName)=0;

	//������Ļ������Ϣ
	virtual void UpdateGroupArrageByRemoveNode(CString szGroupName,int nNodeID)=0;

	//�Ƴ��ڵ���µڶ�ҳ
	virtual void UpdateScreenAfterRemoveNode(int nNodeID)=0;

	//����������ʾ������
	virtual void UpdateShowMasterAfterRemoveNode(int nMaster)=0;

	//������ͼ��ɫ
	virtual void SetViewColor(Color& color)=0;

	//������ͼ��ɫ
	virtual Color GetViewColor()=0;

	//��ȡ��ϯ����ɾ���ڵ�
	//virtual VEC_DEL& GetVecDel()=0;

	//������ɾ���ڵ�
	virtual void DelNodeFromGroup(CString szGroupName,int nNodeID)=0;

	//�ж��ܲ���ɾ��
	virtual BOOL JudgetDelNodeFromGroup(CString szGroupName,int nNodeID)=0;

	virtual void AdjustMultiVideoWindowSize()=0;

	virtual MAP_PAGE& GetMapPage()=0;

	virtual MAP_TEMPFRAME& GetMapTempFrame()=0;

	//��ק�鵽��ϯ��
	virtual void DragGroupToSeat(CString szGroupName,CPoint& point)=0;

	//������л�ҳ��
	virtual void SwitchPage(int nPage)=0;

	//����������ز˵���ť
	virtual void HidePopMenuBtn()=0;
	//��ʾ��ť
	virtual void ShowPopMenuBtn()=0;

	//������������Ļ
	virtual void DrawGroupInScreen(CString szGroupName)=0;

	//������ѡ��ҳ����ϯ
	virtual void SetSeatSelected(CString szGroupName)=0;

	//���ز˵���ť
	virtual void HideMenuWnd()=0;
	virtual void HideBtn()=0;
	virtual void Unselected()=0;

	//��ʾ������ϯ��ť
	virtual void ShowSeatDrawWnd()=0;
	virtual void HideSeatDrawWnd()=0;

	virtual void MoveSeatDrawWnd()=0;
	virtual void EnableSeatDrawWnd(BOOL b)=0;

	//��ȡ��ϯҳ�����
	virtual int GetPageIndex()=0;

	//�Ҽ�������ʱ���������Ƹ���ҳ��
	virtual void SetGroupNameByAddGroupIn(CString szName)=0;


public:

	inline void SetDelegate(XDelegateSeatArrageManage* p){m_pDelegate=p;}

protected:

	XDelegateSeatArrageManage* m_pDelegate;

};