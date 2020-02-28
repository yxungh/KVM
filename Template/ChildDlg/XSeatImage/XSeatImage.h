#pragma once
#include "..\resource.h"
#include "XBaseDialog.h"

class XDelegateSeatImage;
class XSeat;

class XSeatImage : public XBaseDialog
{
	DECLARE_DYNAMIC(XSeatImage)

public:
	XSeatImage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XSeatImage();

	virtual BOOL OnInitDialog();

	// 对话框数据
	enum { IDD = IDD_DIALOG_BG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBtnOk();
	afx_msg void OnBtnSel();

	DECLARE_MESSAGE_MAP()

public:

	inline CString GetPhotoName(){return m_szPhotoName;}
	inline int GetComboIndex(){return m_nComboIndex;}
	inline COLORREF GetColor(){return m_BgColor;}
	inline void SetDelegate(XDelegateSeatImage* p){m_pDelegate=p;}
	inline void SetSeat(XSeat* p){m_pSeat=p;}

private:

	void Init();
	void InitCombo();
	void InitData();
	void ReLoadInterface();
	BOOL OpenSelectPhotoFileDialog(CString& szFileName, CString& szFilePath);
	void SavePhotoName(CString szPhotoName);
	

private:

	XDelegateSeatImage* m_pDelegate;
	XSeat* m_pSeat;

	CString m_szFilePath;
	CString m_szPhotoName;

	CComboBox m_Combox;
	CMFCColorButton m_Color;

	COLORREF m_BgColor;

	int m_nComboIndex;

	XThemeText m_TextModel;
	XThemeText m_TextColor;
	XThemeText m_TextImage;
	XThemeText m_TextTip;
	XThemeBtn m_BtnSel;
};
