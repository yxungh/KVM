#pragma once

class XDelegateRibbonBar;

class XRibbonQuickAccessToolBar: public CMFCRibbonQuickAccessToolBar
{
	friend class XRibbonBar;
};

class XRibbonBar: public CMFCRibbonBar
{
public:
	XRibbonBar(void);
	virtual ~XRibbonBar(void);
	virtual BOOL OnShowRibbonContextMenu(CWnd* pWnd,int x,int y,CMFCRibbonBaseElement* pHit);
	virtual BOOL SetActiveCategory(CMFCRibbonCategory* pCategory,BOOL bForceRestore=FALSE);
	DECLARE_DYNAMIC(XRibbonBar)

protected:

	DECLARE_MESSAGE_MAP()

public:

	//����ί��
	void SetDelegate(XDelegateRibbonBar* p);

private:

	//ί��
	XDelegateRibbonBar* m_pDelegate;
};

