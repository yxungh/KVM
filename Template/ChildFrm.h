
// ChildFrm.h : CChildFrame 类的接口
//

#pragma once

class XInternalManage;
class XBaseViewManage;

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 特性
public:

// 操作
public:

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:

	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()

public:

	inline void SetBaseViewManage(XBaseViewManage* p){m_pBaseManage=p;}
	inline void SetInternalManage(XInternalManage* p){m_pInternalManage=p;}

	void DestroyMDI();

private:

	XInternalManage* m_pInternalManage;
	XBaseViewManage* m_pBaseManage;
};
