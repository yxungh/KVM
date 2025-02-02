#pragma once

class XSetListCtrl
{
private:
	XSetListCtrl(void);
	~XSetListCtrl(void);

public:

	//初始化列表
	static void InitList(CListCtrl* pListCtrl,int nColumnCount,BOOL bCheckBox,int nColumnWidth=-1);

	//设置列表项的文字
	static void SetColumnText(CListCtrl* pListCtrl,int n,CString s);

	//获取列表文字
	static CString GetColumnText(CListCtrl* pListCtrl,int nItem,int nSubItem);

	//获取列表勾选个数
	static int GetListCheckCount(CListCtrl* pListCtrl);

	//获取列表勾选项
	static int GetListCheckItem(CListCtrl* pListCtrl);

	//设置列表选中
	static void SetListCheckItem(CListCtrl* pListCtrl,int nItem);

	//设置列表选中取消
	static void SetListCheckItemFalse(CListCtrl* pListCtrl,int nItem);

	//设置列表项选中
	static void SetListItemSelect(CListCtrl* pListCtrl,int nItem);

	//获取列表选择项
	static int GetListSelectItem(CListCtrl* pListCtrl);

};

