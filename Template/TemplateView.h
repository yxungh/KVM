
// TemplateView.h : CTemplateView ��Ľӿ�
//

#pragma once

class CTemplateDoc;
class XDelegateView;
class XBaseViewManage;

class CTemplateView : public CScrollView
{
protected: // �������л�����
	CTemplateView();
	DECLARE_DYNCREATE(CTemplateView)

// ����
public:
	CTemplateDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTemplateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

	//��ʼ��
	void Init();

	//����ί��
	void SetDelegate();

	//������ͼ��С
	void ResetSize();

	void SetBaseViewManage(XBaseViewManage* p);

	inline XBaseViewManage* GetBaseViewManage(){return m_pBaseManage;}

private:

	//ί��
	XDelegateView* m_pDelegate;

	//����뿪��ʶ
	BOOL m_bMouseLeave;

	XBaseViewManage* m_pBaseManage;

	
};

#ifndef _DEBUG  // TemplateView.cpp �еĵ��԰汾
inline CTemplateDoc* CTemplateView::GetDocument() const
   { return reinterpret_cast<CTemplateDoc*>(m_pDocument); }
#endif

