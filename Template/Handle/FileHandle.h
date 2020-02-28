#pragma once

//文件处理
class FileHandle
{

public:

	//根据路径创建文件夹
	static BOOL	createFolder(CString& path);

	//复制文件
	static BOOL copyFile(CString& szUrl,CString& szNewUrl);

	//删除文件
	static BOOL delFile(CString path);

	//拷贝文件夹
	static BOOL CopyDirectory(CString SrcDirectry,CString DstDirectory);

	//重命名文件
	static BOOL renamefile(CString path,CString name);

private:
	FileHandle(void);
	~FileHandle(void);

};

