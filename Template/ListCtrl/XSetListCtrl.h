#pragma once

class XSetListCtrl
{
private:
	XSetListCtrl(void);
	~XSetListCtrl(void);

public:

	//��ʼ���б�
	static void InitList(CListCtrl* pListCtrl,int nColumnCount,BOOL bCheckBox,int nColumnWidth=-1);

	//�����б��������
	static void SetColumnText(CListCtrl* pListCtrl,int n,CString s);

	//��ȡ�б�����
	static CString GetColumnText(CListCtrl* pListCtrl,int nItem,int nSubItem);

	//��ȡ�б�ѡ����
	static int GetListCheckCount(CListCtrl* pListCtrl);

	//��ȡ�б�ѡ��
	static int GetListCheckItem(CListCtrl* pListCtrl);

	//�����б�ѡ��
	static void SetListCheckItem(CListCtrl* pListCtrl,int nItem);

	//�����б�ѡ��ȡ��
	static void SetListCheckItemFalse(CListCtrl* pListCtrl,int nItem);

	//�����б���ѡ��
	static void SetListItemSelect(CListCtrl* pListCtrl,int nItem);

	//��ȡ�б�ѡ����
	static int GetListSelectItem(CListCtrl* pListCtrl);

};

