#include "stdafx.h"
#include "XThemeColor.h"


const Color m_BgColor[5]={Color(223,233,245),Color(191,219,255),Color(58,57,58),Color(208,212,221),Color(196,202,217)};
const Color m_BtnColor[5][3]={Color(0,190,169),Color(61,250,230),Color(7,230,216),
							  Color(4,181,207),Color(64,221,249),Color(64,221,249),
							  Color(76,76,76),Color(122,121,122),Color(31,30,31),
							  Color(165,165,165),Color(189,189,189),Color(170,170,171),
							  Color(165,165,165),Color(189,189,189),Color(170,170,171)};
const Color m_TextColor[5]={Color(0,0,0),Color(21,66,139),Color(255,255,255),Color(35,38,42),Color(0,21,110)};


XThemeColor::XThemeColor()
{

}

XThemeColor::~XThemeColor()
{

}

XThemeColor* XThemeColor::GetInstance()
{
	static XThemeColor theme;
	return &theme;
}