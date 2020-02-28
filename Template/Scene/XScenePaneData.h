#pragma once

class XScene;

class XScenePaneData
{
public:
	XScenePaneData();
	~XScenePaneData();

public:

	//获取数据
	static void GetData(XScene* pPane,CArchive& arch);

	//保存数据
	static void SaveData(XScene* pPane,CArchive& arch);

};

