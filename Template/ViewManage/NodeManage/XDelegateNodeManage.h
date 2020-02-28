#pragma once
#include "XConstant.h"

class CTemplateView;

class XDelegateNodeManage
{
public:
	XDelegateNodeManage();
	~XDelegateNodeManage();

public:

	virtual CTemplateView* GetView()=0;

	virtual void SetHardWareChannel(int n)=0;

	virtual void SetMatrixModel(CString szModel)=0;

	virtual void SetFPGAVersion(CString szVer)=0;

	virtual MAP_SUBUSER& GetMapSubUser()=0;

	virtual MAP_POWER& GetMapPower()=0;

	virtual VEC_DEL& GetVecDel()=0;

	virtual VEC_USERIDALL& GetVecUserIDAll()=0;

	virtual CWnd* GetCWND()=0;

	virtual CString GetCurUserName()=0;

	virtual BOOL GetLogin()=0;

	//virtual void SetSeatArrageMaster(int nMaster)=0;

	virtual void ClearInfo(CString szGroupName)=0;

	//������ϯ����
	virtual void UpdateGroupNameAfterAddArrage(CString szName)=0;
	//�Ƴ��ڵ���µڶ�ҳ
	virtual void UpdateScreenAfterRemoveNode(int nNodeID)=0;
	//����������ʾ������
	virtual void UpdateShowMasterAfterRemoveNode(int nMaster)=0;
	//ƥ����ϯ����
	virtual void MatchSeatNameByGroupName()=0;

	//���¾���������Ϣ
	virtual void ResetMatrixArray()=0;
	//���ݷֻ�״̬���� ҳ��״̬
	virtual void ResetMatrixSwitchStatus()=0;
	//�Ҽ�������ʱ���������Ƹ���ҳ��
	virtual void SetGroupNameByAddGroupIn(CString szName)=0;

};