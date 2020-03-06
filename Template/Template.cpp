
// Template.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Template.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "TemplateDoc.h"
#include "TemplateView.h"
#include "HandlePath.h"
#include "XConstant.h"
#include "CatchError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTemplateApp

BEGIN_MESSAGE_MAP(CTemplateApp,CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT,&CTemplateApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW,&CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN,&CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP,&CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CTemplateApp ����

CTemplateApp::CTemplateApp()
{
	m_bHiColorIcons=TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags=AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Template.AppID.NoVersion"));

	m_TokenGdi=0;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

CTemplateApp::~CTemplateApp()
{
	GdiplusShutdown(m_TokenGdi);
}

// Ψһ��һ�� CTemplateApp ����

CTemplateApp theApp;


// CTemplateApp ��ʼ��

BOOL CTemplateApp::InitInstance()
{
	//�ڴ�й©���
	//_CrtSetBreakAlloc(80501);

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize=sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC=ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	//GDI+��ʼ��
	Gdiplus::GdiplusStartupInput input=0;
	Gdiplus::GdiplusStartup(&m_TokenGdi,&input,0);

	//·����ʼ��
	HandlePath::Init();

	//Dump��ʼ��
	CatchError::SetCatchError(HandlePath::GetDumpFolderPath());

	//�����ʼ��
	AfxSocketInit();

	srand((unsigned)time(NULL));

	// ��ʼ�� OLE ��
	if(!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	//����������ͼ
	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ���
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(APP_REGISTRYKEY);
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme=TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
												 RUNTIME_CLASS(CMFCToolTipCtrl),&ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate=new CMultiDocTemplate(IDR_TemplateTYPE,
									   RUNTIME_CLASS(CTemplateDoc),
									   RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
									   RUNTIME_CLASS(CTemplateView));
	if(!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame=new CMainFrame;
	if(!pMainFrame||!pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd=pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if(!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	//////////////////////////////////////////////////////////////////////////
	::PostMessage(m_pMainWnd->GetSafeHwnd(),MSG_ADDDOCUMENT,NULL,NULL);


	return TRUE;
}

int CTemplateApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CTemplateApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg: public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD=IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg():CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg,CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CTemplateApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CTemplateApp �Զ������/���淽��

void CTemplateApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid=strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName,IDR_POPUP_EDIT);
	bNameValid=strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName,IDR_POPUP_EXPLORER);
}

void CTemplateApp::LoadCustomState()
{
}

void CTemplateApp::SaveCustomState()
{
}

// CTemplateApp ��Ϣ�������



