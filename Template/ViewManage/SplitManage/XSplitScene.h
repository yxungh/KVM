#pragma once


class XSplitScene
{
public:
	XSplitScene();

	virtual ~XSplitScene();

public:
	
	inline void SetSceneName(CString szName){m_szSceneName=szName;}
	inline CString GetSceneName(){return m_szSceneName;}
	inline std::vector<CString>& GetVecWallList(){return m_VecWallList;}


public:

	CString m_szSceneName=_T("");
	CString m_szSceneGroup=_T("");
	HTREEITEM m_hItem=NULL;
	std::vector<CString> m_VecWallList;

};

