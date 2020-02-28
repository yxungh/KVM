// XPropertyGridCtrl.cpp: 实现文件
//

#include "stdafx.h"
#include "XPropertyGridCtrl.h"
#include "XPropertiesWnd.h"
#include "XConstant.h"


// XPropertyGridCtrl

IMPLEMENT_DYNAMIC(XPropertyGridCtrl, CMFCPropertyGridCtrl)

XPropertyGridCtrl::XPropertyGridCtrl()
{

}

XPropertyGridCtrl::~XPropertyGridCtrl()
{
}


BEGIN_MESSAGE_MAP(XPropertyGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()



// XPropertyGridCtrl 消息处理程序


//BOOL XPropertyGridCtrl::PreTranslateMessage(MSG* pMsg)
//{
//	//处理键盘键值
//	CMFCPropertyGridProperty* pTemp=XPropertiesWnd::GetInstance()->GetPropertyGridCtrl().GetCurSel();
//	if(NULL==pTemp)
//		return __super::PreTranslateMessage(pMsg);
//	int nData=pTemp->GetData();
//	if(nData==ID_HOTKEY1||nData==ID_HOTKEY2||nData==ID_HOTKEY3)
//	{
//		//TRACE(_T("OK\n"));
//		if(HIBYTE(::GetKeyState(VK_MENU))&&WM_SYSKEYDOWN==pMsg->message)
//		{
//			KeyValue(pTemp,(int)VK_MENU,(char)pMsg->wParam);
//			return TRUE;
//		}
//		else if(HIBYTE(::GetKeyState(VK_SHIFT))&&WM_KEYDOWN==pMsg->message)
//		{		
//			KeyValue(pTemp,(int)VK_SHIFT,(char)pMsg->wParam);
//			return TRUE;
//		}
//		else if(HIBYTE(::GetKeyState(VK_CONTROL))&&WM_KEYDOWN==pMsg->message)
//		{		
//			KeyValue(pTemp,(int)VK_CONTROL,(char)pMsg->wParam);
//			return TRUE;
//		}
//		else if(HIBYTE(::GetKeyState(VK_LWIN))&&WM_KEYDOWN==pMsg->message)
//		{		
//			KeyValue(pTemp,(int)VK_LWIN,(char)pMsg->wParam);
//			return TRUE;
//		}
//		else if(HIBYTE(::GetKeyState(VK_BACK))&&WM_KEYDOWN==pMsg->message)
//		{		
//			pTemp->SetValue(_T(""));
//			return TRUE;
//		}
//	}
//	return __super::PreTranslateMessage(pMsg);
//}
//
//void XPropertyGridCtrl::KeyValue(CMFCPropertyGridProperty* pTemp,int nValue,char c)
//{
//	CString szFront;
//	switch(nValue)
//	{
//		case VK_MENU:
//			szFront=_T("Alt");
//			break;
//		case VK_SHIFT:
//			szFront=_T("Shift");
//			break;
//		case VK_CONTROL:
//			szFront=_T("Ctl");
//			break;
//		case VK_LWIN:
//			szFront=_T("Win");
//			break;
//		default:
//			break;
//	}
//
//	CString szKey;
//	switch(c)
//	{
//		case 'A':
//			{
//				szKey.Format(_T("%s+A"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'B':
//			{
//				szKey.Format(_T("%s+B"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'C':
//			{
//				szKey.Format(_T("%s+C"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'D':
//			{
//				szKey.Format(_T("%s+D"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'E':
//			{
//				szKey.Format(_T("%s+E"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'F':
//			{
//				szKey.Format(_T("%s+F"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'G':
//			{
//				szKey.Format(_T("%s+G"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'H':
//			{
//				szKey.Format(_T("%s+H"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'I':
//			{
//				szKey.Format(_T("%s+I"),szFront);
//				pTemp->SetValue(szKey);
//				TRACE(_T("+I\n"));
//				//发送
//			}
//			break;
//		case 'J':
//			{
//				szKey.Format(_T("%s+J"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'K':
//			{
//				szKey.Format(_T("%s+K"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'L':
//			{
//				szKey.Format(_T("%s+L"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'M':
//			{
//				szKey.Format(_T("%s+M"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'N':
//			{
//				szKey.Format(_T("%s+N"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'O':
//			{
//				szKey.Format(_T("%s+O"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'P':
//			{
//				szKey.Format(_T("%s+P"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'Q':
//			{
//				szKey.Format(_T("%s+Q"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'R':
//			{
//				szKey.Format(_T("%s+R"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'S':
//			{
//				szKey.Format(_T("%s+S"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'T':
//			{
//				szKey.Format(_T("%s+T"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'U':
//			{
//				szKey.Format(_T("%s+U"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'V':
//			{
//				szKey.Format(_T("%s+V"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'W':
//			{
//				szKey.Format(_T("%s+W"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'X':
//			{
//				szKey.Format(_T("%s+X"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'Y':
//			{
//				szKey.Format(_T("%s+Y"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case 'Z':
//			{
//				szKey.Format(_T("%s+Z"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F1:
//			{
//				szKey.Format(_T("%s+F1"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F2:
//			{
//				szKey.Format(_T("%s+F2"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F3:
//			{
//				szKey.Format(_T("%s+F3"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F4:
//			{
//				szKey.Format(_T("%s+F4"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F5:
//			{
//				szKey.Format(_T("%s+F5"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F6:
//			{
//				szKey.Format(_T("%s+F6"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F7:
//			{
//				szKey.Format(_T("%s+F7"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F8:
//			{
//				szKey.Format(_T("%s+F8"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F9:
//			{
//				szKey.Format(_T("%s+F9"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F10:
//			{
//				szKey.Format(_T("%s+F10"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F11:
//			{
//				szKey.Format(_T("%s+F11"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_F12:
//			{
//				szKey.Format(_T("%s+F12"),szFront);
//				pTemp->SetValue(szKey);
//			}
//			break;
//		case VK_MENU:
//			{
//				DbClick(pTemp,szFront);
//			}
//			break;
//		case VK_CONTROL:
//			{
//				DbClick(pTemp,szFront);
//			}
//			break;
//		case VK_LWIN:
//			{
//				DbClick(pTemp,szFront);
//			}
//			break;
//		case VK_SHIFT:
//			{
//				DbClick(pTemp,szFront);
//			}
//			break;
//		default:
//			break;
//	}
//
//}
//
//void XPropertyGridCtrl::DbClick(CMFCPropertyGridProperty* pTemp,CString szFront)
//{
//	TRACE(_T("down\n"));
//
//	static DWORD dwPreTime=0;
//	DWORD dwTime=GetCurrentTime();
//	if(dwTime-dwPreTime<500)
//	{
//		CString szKey;
//		szKey.Format(_T("%s%s"),szFront,_T("双击"));
//		pTemp->SetValue(szKey);
//		dwPreTime=0;
//	}
//	else
//	{
//		dwPreTime=dwTime;
//	}
//}
