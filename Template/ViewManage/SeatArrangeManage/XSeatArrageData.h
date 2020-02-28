#pragma once

class XSeatArrageManage;
class XPage;

class XSeatArrageData
{
public:
	~XSeatArrageData();
private:
	XSeatArrageData();

public:

	static XSeatArrageData* GetInstance();

	static void Release();

public:

	//��ȡ����
	void GetData(XSeatArrageManage* pManage,CArchive& arch);

	void GetSeatData(XPage* p,CArchive& arch);


public:

	//��������
	void SaveData(XSeatArrageManage* pManage,CArchive& arch);

	void SaveSeatData(XPage* p,CArchive& arch);


private:

	static XSeatArrageData* m_pSeatData;

};