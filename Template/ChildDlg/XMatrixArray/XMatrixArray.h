#pragma once


// XMatrixArray 对话框

class XMatrixArray : public CDialogEx
{
	DECLARE_DYNAMIC(XMatrixArray)

public:
	XMatrixArray(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~XMatrixArray();

	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum{IDD=IDD_DIALOG_MATRIXARRAY};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()




private:



};
