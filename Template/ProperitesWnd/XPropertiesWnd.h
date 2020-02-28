#pragma once
#include "XPropertyGridCtrl.h"

class XDelegateProperitiesWnd;
class XNode;
class XNodeGroupInfo;
class XSeat;

class XPropertiesWnd : public CDockablePane
{
	// 构造
public:
	virtual ~XPropertiesWnd();
private:
	XPropertiesWnd();

	virtual BOOL CanBeClosed()const{return FALSE;}
	virtual BOOL FloatPane(CRect rectFloat,AFX_DOCK_METHOD dockMethod=DM_UNKNOWN,bool bShow=true){return FALSE;}
	//virtual void SetCaptionButtons(){ RemoveCaptionButtons();};


	// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnPropertyChanged (WPARAM,LPARAM);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

protected:

	void InitPropList();

	void SetPropListFont();

	void AdjustLayout();

public:

	inline void SetDelegate(XDelegateProperitiesWnd* p){m_pDelegate=p;}

	inline CMFCPropertyGridCtrl& GetPropertyGridCtrl(){return m_wndPropList;}

	inline void SetNode(XNode* pNode){m_pNode=pNode;}

	inline void SetNodeGroup(XNodeGroupInfo* pInfo){m_pNodeGroup=pInfo;}

	inline void SetSeat(XSeat* p){m_pSeat=p;}

public:

	static XPropertiesWnd* GetInstance();

	static void Release();

	void Init();

	void CreatePropertiesWnd();

	void ReloadInterface();

public:

	XDelegateProperitiesWnd* m_pDelegate=NULL;
	CFont m_fntPropList;
	XPropertyGridCtrl m_wndPropList;

private:

	static XPropertiesWnd* m_pPropertiesWnd;

	XNode* m_pNode=NULL;
	XNodeGroupInfo* m_pNodeGroup=NULL;
	XSeat* m_pSeat=NULL;
};

