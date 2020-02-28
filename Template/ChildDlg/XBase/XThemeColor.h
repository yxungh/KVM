#pragma once


extern const Color m_BgColor[5];
extern const Color m_BtnColor[5][3];
extern const Color m_TextColor[5];


class XThemeColor
{
public:
	XThemeColor();
	~XThemeColor();

public:
	static XThemeColor* GetInstance();
	inline void SetThemeIndex(int n){m_nThemeIndex=n;}
	inline int GetThemeIndex(){return m_nThemeIndex;}

private:
	int m_nThemeIndex=0;
};