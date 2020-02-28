#pragma once

class XNodeManage;

class XSceneData
{
public:
	XSceneData();
	~XSceneData();

public:
	static BOOL SaveData(XNodeManage* p,CString szPath);
	static void SaveData(XNodeManage* p,CArchive& arch);



	static BOOL GetData(XNodeManage* p,CString szPath);
	static void GetData(XNodeManage* p,CArchive& arch);


};

