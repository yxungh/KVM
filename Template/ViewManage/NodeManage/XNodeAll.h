#pragma once
class XNodeAll
{
public:
	XNodeAll(void);
	~XNodeAll(void);

public:

	inline void SetRealID(CString szID){m_szRealID=szID;}
	inline CString GetRealID(){return m_szRealID;}

	inline void SetNodeName(CString szName){m_szNodeName=szName;}
	inline CString GetNodeName(){return m_szNodeName;}

	inline void SetCreateTime(time_t time){m_tConnectTime=time;}
	inline time_t GetCreateTime(){return m_tConnectTime;}

	inline void SetGroup(int nGroup){m_nGroup=nGroup;}
	inline int GetGroup(){return m_nGroup;}

	inline void SetMaster(int n){m_nMaster=n;}
	inline int GetMaster(){return m_nMaster;}

	inline void SetControl(int n){m_nControl=n;}
	inline int GetControl(){return m_nControl;}

	inline void SetNodeID(int n){m_nNodeID=n;}
	inline int GetNodeID(){return m_nNodeID;}

	inline void SetNodeType(int n){m_nNodeType=n;}
	inline int GetNodeType(){return m_nNodeType;}

private:
	//真实ID
	CString m_szRealID=_T("");
	//节点名称
	CString m_szNodeName=_T("");
	//连接时间
	time_t m_tConnectTime=0;
	//组
	int m_nGroup=0;
	//主
	int m_nMaster=0;
	//控制
	int m_nControl=0;
	//ID的编号
	int m_nNodeID=0;
	//类型
	int m_nNodeType=0;
};

