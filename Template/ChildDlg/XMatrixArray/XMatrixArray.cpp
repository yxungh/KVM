// XMatrixArray.cpp: 实现文件
//

#include "stdafx.h"
#include "XMatrixArray.h"
#include "afxdialogex.h"
#include "../resource.h"


// XMatrixArray 对话框

IMPLEMENT_DYNAMIC(XMatrixArray, CDialogEx)

XMatrixArray::XMatrixArray(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MATRIXARRAY, pParent)
{

}

XMatrixArray::~XMatrixArray()
{
}

void XMatrixArray::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XMatrixArray, CDialogEx)
END_MESSAGE_MAP()


// XMatrixArray 消息处理程序
BOOL XMatrixArray::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;
}