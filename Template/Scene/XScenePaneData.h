#pragma once

class XScene;

class XScenePaneData
{
public:
	XScenePaneData();
	~XScenePaneData();

public:

	//��ȡ����
	static void GetData(XScene* pPane,CArchive& arch);

	//��������
	static void SaveData(XScene* pPane,CArchive& arch);

};

