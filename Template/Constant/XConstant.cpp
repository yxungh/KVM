#include "stdafx.h"
#include "XConstant.h"


const CString APP_NAME=_T("KVM Manage");
const CString APP_VERSION=_T("4.11.0");
const CString APP_REGISTRYKEY=APP_NAME+APP_VERSION;

const CString APP_ININAME=_T("App.ini");
const CString APP_DATAFILENAME=_T("App");
const CString APP_FONT=_T("Î¢ÈíÑÅºÚ");
const CString FILTER_PHOTO=_T("(*.jpg)(*.png)(*.bmp)(*.gif)|*.jpg;*.png;*.bmp;*.gif||");
const Color g_Color[40]={Color(255,185,0),Color(255,140,0),Color(247,99,12),Color(202,80,16),
                         Color(210,57,1),Color(239,105,80),Color(209,52,56),Color(209,52,56),
						 Color(231,72,86),Color(232,17,35),Color(234,0,94),Color(195,0,82),
						 Color(227,0,140),Color(191,0,119),Color(194,57,179),Color(154,0,137),
						 Color(0,120,215),Color(0,99,177),Color(142,140,216),Color(107,105,214),
						 Color(135,100,184),Color(116,77,169),Color(177,70,194),Color(136,23,152),
						 Color(0,153,188),Color(43,121,149),Color(0,168,179),Color(3,117,120),
	                     Color(0,178,148),Color(1,133,116),Color(0,204,106),Color(16,137,62),
						 Color(122,117,116),Color(93,90,88),Color(104,118,138),Color(81,92,107),
	                     Color(86,124,115),Color(72,104,96),Color(73,130,5),Color(16,124,16)};



//ÏûÏ¢ID
const UINT MSG_BEGIN						=WM_USER+1;
const UINT MSG_UDP							=(MSG_BEGIN+1);
const UINT MSG_ADDDOCUMENT                  =(MSG_BEGIN+2);
const UINT MSG_BTN_LCLICK					=(MSG_BEGIN+3);
const UINT MSG_TCP                          =(MSG_BEGIN+4);