#pragma once
#include "XConstant.h"

class CTemplateView;

class XDelegateSeatArrageManage
{
public:
	XDelegateSeatArrageManage();
	~XDelegateSeatArrageManage();

public:

	virtual CTemplateView* GetView()=0;

	virtual CWnd* GetCWND()=0;

	virtual BOOL GetLogin()=0;

	virtual MAP_NODE& GetMapNode()=0;

	virtual void UpdateControlDataShow(XDATATYPE type)=0;

	virtual MAP_NODEGROUP& GetMapNodeGroup()=0;

	virtual MAP_GROUPMAINSEC& GetMapNodeGroupMainSec()=0;

	virtual int GetCurUserID()=0;

	virtual void SetMultiVideoWindowBkColor(Uint8 r,Uint8 g,Uint8 b)=0;

	virtual void SetMultiVideoWindowScale(float fScale)=0;

	virtual void AdjustMultiVideoWindowSize(int nWidth,int nHeight)=0;

	virtual void SetMultiVideoFramesBg()=0;

	virtual void ResetRibbonBar()=0;
};