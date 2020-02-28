
// TemplateView.h : CTemplateView 类的接口
//

#pragma once

class CTemplateDoc;
class XDelegateView;
class XBaseViewManage;

class CTemplateView : public CScrollView
{
protected: // 仅从序列化创建
	CTemplateView();
	DECLARE_DYNCREATE(CTemplateView)

// 特性
public:
	CTemplateDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTemplateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT fFlags, short zDelta, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()


public:

	//初始化
	void Init();

	//设置委托
	void SetDelegate();

	//重设视图大小
	void ResetSize();

	void SetBaseViewManage(XBaseViewManage* p);

	inline XBaseViewManage* GetBaseViewManage(){return m_pBaseManage;}

private:

	//委托
	XDelegateView* m_pDelegate;

	//鼠标离开标识
	BOOL m_bMouseLeave;

	XBaseViewManage* m_pBaseManage;

	
};

#ifndef _DEBUG  // TemplateView.cpp 中的调试版本
inline CTemplateDoc* CTemplateView::GetDocument() const
   { return reinterpret_cast<CTemplateDoc*>(m_pDocument); }
#endif

