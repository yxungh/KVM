#include "Stdafx.h"
#include "XDrawNodeManage.h"
#include "XNodeManage.h"
#include "XCaculateNodeManage.h"
#include "XNode.h"
#include "HandlePath.h"
#include "XTranslationManage.h"
#include "XConstantData.h"
#include "XTranslationManage.h"
#include "XChannel.h"
#include "XChart.h"
#include "XSystemStatus.h"


CRect XDrawNodeManage::m_rectTextIn;
CRect XDrawNodeManage::m_rectTextOut;
XDrawNodeManage::XDrawNodeManage()
{

}

XDrawNodeManage::~XDrawNodeManage()
{

}

void XDrawNodeManage::RectScale(RECTF& rect,float dwScale)
{
	rect.X*=dwScale;
	rect.Y*=dwScale;
	rect.Width*=dwScale;
	rect.Height*=dwScale;
}

void XDrawNodeManage::ViewDraw(CDC* pDC,CRect rect,int noffsetX,int noffsetY,XNodeManage* pNodeManage)
{
	//long dwBegin=GetTickCount();
	//TRACE(_T("begin=%d\n"),dwBegin);

	float dwScale=pNodeManage->GetScale();	
	CSize size=pNodeManage->ViewGetSize();

	int nWidth=rect.Width();
	int nHeight=rect.Height();

	HDC hdc=pDC->GetSafeHdc();
	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);

	XCaculateNodeManage::SetViewPortOrg(rect,noffsetX,noffsetY,size,dwScale,tempDC);

	HDC hMemdc=tempDC.GetSafeHdc();
	HBITMAP hMembmp=CreateCompatibleBitmap(hdc,nWidth,nHeight);
	HBITMAP hOldbmp=(HBITMAP)SelectObject(hMemdc,hMembmp);
	Graphics graphics(hMemdc);

	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.Clear(pNodeManage->GetViewColor());
	//////////////////////////////////////////////////////////////////////////
	//����ͼƬ
	DrawOperationPic(graphics,pNodeManage);
	//���ƽڵ�
	SetNodeIndexAndRect(pNodeManage);
	DrawNode(graphics,pNodeManage);
	if(pNodeManage->GetCreateDragRect())
	{
		DrawDrag(graphics,pNodeManage);
	}
	//////////////////////////////////////////////////////////////////////////
	BitBlt(hdc,noffsetX,noffsetY,nWidth,nHeight,hMemdc,0,0,SRCCOPY);
	graphics.ReleaseHDC(hMemdc);
	SelectObject(hMemdc,hOldbmp);
	tempDC.DeleteDC();
	DeleteObject(hMembmp);

	//long dwEnd=GetTickCount();
	//TRACE(_T("end=%d\n"),dwEnd);
}

void XDrawNodeManage::DrawOperationPic(Graphics& graphics,XNodeManage* pNodeManage)
{
	float dwScale=pNodeManage->GetScale();
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font1(&fontfamily,16*dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::Font font2(&fontfamily,12*dwScale,FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrushTitle(Color(255,234,234,234));

	Gdiplus::StringFormat stringForamtCenter;
	stringForamtCenter.SetAlignment(StringAlignmentCenter);
	stringForamtCenter.SetLineAlignment(StringAlignmentCenter);

	if(pNodeManage->GetLogin())
	{
		CString szPath=HandlePath::GetPhotoPath(_T("timg.jpg"));
		//Gdiplus::Image* pImage=Gdiplus::Image::FromFile(szPath);


		Image image(szPath);
		//����ͼƬ
		RECTF drawRect(0,0,PIC_WIDTH*dwScale,PIC_HEIGHT*dwScale);
		graphics.DrawImage(&image,drawRect,0.0f,0.0f,(Gdiplus::REAL)image.GetWidth(),(Gdiplus::REAL)image.GetHeight(),Gdiplus::UnitPixel,NULL,NULL,NULL);

		RECTF text1(544,10,240,30);
		RectScale(text1,dwScale);
		graphics.DrawString(_C(_T("201"),_T("�豸��άƽ̨")),-1,&font1,text1,&stringForamtCenter,&textbrushTitle);

		RECTF text2(610,505,130,25);
		RectScale(text2,dwScale);
		graphics.DrawString(_C(_T("202"),_T("ϵͳ�������")),-1,&font2,text2,&stringForamtCenter,&textbrushTitle);

		//����ͨ�����
		DrawDevicePlate(graphics,pNodeManage);
		//�����û���
		DrawUserPlate(graphics,pNodeManage);
		//���ƽڵ���
		DrawNodePlate(graphics,pNodeManage);
		//���ƽڵ�����
		DrawNodeGroupPlate(graphics,pNodeManage);
		//�����м�
		DrawCentreRectangle(graphics,pNodeManage);
		//������Ϣ��Ϣ
		DrawSystemStatus(graphics,pNodeManage);
	}
}

void XDrawNodeManage::DrawDevicePlate(Graphics& graphics,XNodeManage* pNodeManage)
{
	float dwScale=pNodeManage->GetScale();

	Gdiplus::SolidBrush brushIn(Gdiplus::Color(255,0,139,0));
	Gdiplus::SolidBrush brushOut(Gdiplus::Color(255,176,48,96));

	Gdiplus::Pen pen(Gdiplus::Color(255,49,92,126));
	Gdiplus::Pen penIn(Gdiplus::Color(255,0,139,0));
	Gdiplus::Pen penOut(Gdiplus::Color(255,176,48,96));

	//�����豸
	RECTF devide(178,45,80,20);
	RectScale(devide,dwScale);
	XChart* pString=XChart::Get(CHART::CHART_STRING);
	if(!pString)
		return;
	pString->SetScale(dwScale);
	pString->SetRect(devide);
	pString->SetDrawType(STRING::STRING_TITLE);
	pString->SetDrawInfo(_C(_T("181"),_T("�豸")));
	pString->Draw(graphics);

	//��������(65,90) 
	RECTF rectBase(65,90,200,20);
	//оƬ����
	RECTF rectChip=rectBase;
	RectScale(rectChip,dwScale);
	pString->SetRect(rectChip);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("182"),_T("�豸����"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectChipInfo=rectChip;
	rectChipInfo.X+=65*dwScale;
	//CString szMatrixType=pNodeManage->GetMatrixType();
	int nMChannel=pNodeManage->GetHardWareChannel();
	CString szMatrixType;
	szMatrixType.Format(_T("%d%s-%d%s"),
						nMChannel,
						_C(_T("228"),_T("��")),
						nMChannel,
						_C(_T("229"),_T("��")));

	if(szMatrixType!=_T(""))
	{
		pString->SetRect(rectChipInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szMatrixType);
		pString->Draw(graphics);
	}

	//�豸ͨ��
	RECTF rectChannel=rectBase;
	rectChannel.Y+=25;
	RectScale(rectChannel,dwScale);
	pString->SetRect(rectChannel);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("183"),_T("�豸ͨ��"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectChennalInfo=rectChannel;
	rectChennalInfo.X+=65*dwScale;
	int nMatrixChannel=pNodeManage->GetHardWareChannel();
	if(nMatrixChannel!=-1)
	{
		CString szChannel;
		szChannel.Format(_T("%d"),nMatrixChannel);
		pString->SetRect(rectChennalInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szChannel);
		pString->Draw(graphics);
	}
	//����ͨ��
	RECTF rectConnChe=rectBase;
	rectConnChe.X+=200;
	rectConnChe.Y+=25;
	RectScale(rectConnChe,dwScale);
	pString->SetRect(rectConnChe);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("184"),_T("����ͨ��"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectConnCheInfo=rectConnChe;
	rectConnCheInfo.X+=65*dwScale;
	int nConnect=pNodeManage->GetChannelConnect();
	if(nConnect!=-1)
	{
		CString szConnect;
		szConnect.Format(_T("%d"),nConnect);
		pString->SetRect(rectConnCheInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szConnect);
		pString->Draw(graphics);
	}
	//������
	RECTF rectPro=rectBase;
	rectPro.Y+=50;
	rectPro.Width=300;
	RectScale(rectPro,dwScale);
	XChart* pChart=XChart::Get(CHART::CHART_PROGRESS);
	if(!pChart)
		return;
	pChart->SetRect(rectPro);
	pChart->SetScale(dwScale);
	pChart->SetWidth(nMatrixChannel,nConnect);
	pChart->SetColor(Color(255,79,243,180),Color(255,49,92,126));
	pChart->Draw(graphics);

	//ͨ��
	RECTF rectChe=rectBase;
	rectChe.Y+=80;
	RectScale(rectChe,dwScale);
	pString->SetRect(rectChe);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("185"),_T("ͨ��"))+_T(":"));
	pString->Draw(graphics);

	//����
	RECTF rectCheInfoIn=rectChe;
	rectCheInfoIn.X+=130*dwScale;
	pString->SetRect(rectCheInfoIn);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("62"),_T("����"))+_T(":"));
	pString->Draw(graphics);
	//ͼ��
	RECTF rectCheIn=rectChe;
	rectCheIn.X+=173*dwScale;
	rectCheIn.Y+=3*dwScale;
	rectCheIn.Width=30*dwScale;
	rectCheIn.Height=12*dwScale;
	graphics.FillRectangle(&brushIn,rectCheIn);
	graphics.DrawRectangle(&penIn,rectCheIn);
	//���
	RECTF rectCheInfoOut=rectChe;
	rectCheInfoOut.X+=220*dwScale;
	pString->SetRect(rectCheInfoOut);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("63"),_T("���"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectCheOut=rectCheIn;
	rectCheOut.X+=98*dwScale;
	graphics.FillRectangle(&brushOut,rectCheOut);
	graphics.DrawRectangle(&penOut,rectCheOut);

	//ͨ������
	RECTF rectAbrridge=rectBase;
	rectAbrridge.Y+=105;
	rectAbrridge.Width=300;
	rectAbrridge.Height=224;
	RectScale(rectAbrridge,dwScale);

	//�������Ҫ������
	int nColumn=12;
	int nRow=nMatrixChannel/nColumn;
	int nWidth=CHANNEL_W;
	int nHeight=CHANNEL_H;

	rectAbrridge.Height=nRow*nHeight*dwScale;
	graphics.DrawRectangle(&pen,rectAbrridge);

	float nLeft=rectAbrridge.X;
	float nTop=rectAbrridge.Y+nHeight*dwScale;
	for(int i=0;i<nRow;i++)
	{
		graphics.DrawLine(&pen,(float)nLeft,(float)nTop,(float)rectAbrridge.GetRight(),(float)nTop);
		nTop+=nHeight*dwScale;
	}

	nLeft=rectAbrridge.X+nWidth*dwScale;
	nTop=rectAbrridge.Y;
	for(int j=0;j<nColumn-1;j++)
	{
		graphics.DrawLine(&pen,(float)nLeft,(float)nTop,(float)nLeft,(float)rectAbrridge.GetBottom());
		nLeft+=nWidth*dwScale;
	}
	//��ʼ������
	pNodeManage->InitVecChannelAbridge(nRow,nColumn,POINTF(rectBase.X,rectBase.Y+105));
	VEC_CHANNEL VecCheBridge=pNodeManage->GetVecCheBridge();

	//��������ͨ��
	for(auto iter=VecCheBridge.begin();iter!=VecCheBridge.end();++iter)
	{
		XChannel* pChe=*iter;
		int nIndex=pChe->GetIndex();
		XNode* pNode=pNodeManage->GetNodeByChannel(nIndex);
		if(!pNode)
			continue;

		RECTF rect=pChe->GetRect();
		RectScale(rect,dwScale);
		if(pNode->GetNodeType()==TERM_IN)
		{
			graphics.FillRectangle(&brushIn,rect);
		}
		else if(pNode->GetNodeType()==TERM_OUT)
		{
			graphics.FillRectangle(&brushOut,rect);
		}
	}

	//�������
	for(auto iter=VecCheBridge.begin();iter!=VecCheBridge.end();++iter)
	{
		XChannel* pChe=*iter;
		int nIndex=pChe->GetIndex();
		RECTF rect=pChe->GetRect();
		RectScale(rect,dwScale);

		CString szIndex;
		szIndex.Format(_T("%d"),nIndex);
		pString->SetRect(rect);
		pString->SetDrawType(STRING::STRING_INDEX);
		pString->SetDrawInfo(szIndex);
		pString->Draw(graphics);
	}
}

void XDrawNodeManage::DrawNodePlate(Graphics& graphics,XNodeManage* pNodeManage)
{
	float dwScale=pNodeManage->GetScale();
	//�ڵ�
	RECTF rectNode(178,480,80,20);
	RectScale(rectNode,dwScale);
	XChart* pString=XChart::Get(CHART::CHART_STRING);
	if(!pString)
		return;
	pString->SetRect(rectNode);
	pString->SetScale(dwScale);
	pString->SetDrawType(STRING::STRING_TITLE);
	pString->SetDrawInfo(_C(_T("95"),_T("�ڵ�")));
	pString->Draw(graphics);

	//��������(65,535)
	RECTF rectBase(65,525,65,20);
	//�ܽڵ���
	RECTF rectTotalNode=rectBase;
	RectScale(rectTotalNode,dwScale);
	pString->SetRect(rectTotalNode);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("192"),_T("�ܽ����"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectTotalNodeInfo=rectTotalNode;
	rectTotalNodeInfo.X+=65*dwScale;
	int nNodeAll=pNodeManage->GetNodeAll();
	if(nNodeAll!=-1)
	{
		CString szNodeAll;
		szNodeAll.Format(_T("%d"),nNodeAll);
		pString->SetRect(rectTotalNodeInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeAll);
		pString->Draw(graphics);
	}
	//�ڵ�����
	RECTF rectNodeOnline=rectBase;
	rectNodeOnline.X+=200;
	RectScale(rectNodeOnline,dwScale);
	pString->SetRect(rectNodeOnline);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("193"),_T("���߽ڵ�"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectNodeOnlineInfo=rectNodeOnline;
	rectNodeOnlineInfo.X+=65*dwScale;
	int nNode=pNodeManage->GetNodeOnline(TERM_ALL);
	if(nNode!=-1)
	{
		CString szNode;
		szNode.Format(_T("%d"),nNode);
		pString->SetRect(rectNodeOnlineInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNode);
		pString->Draw(graphics);
	}
	//����ڵ�
	RECTF rectNodeInput=rectBase;
	rectNodeInput.Y+=25;
	RectScale(rectNodeInput,dwScale);
	pString->SetRect(rectNodeInput);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("194"),_T("����ڵ�"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectNodeInputInfo=rectNodeInput;
	rectNodeInputInfo.X+=65*dwScale;
	int nNodeIn=pNodeManage->GetNodeOnline(TERM_IN);
	if(nNodeIn!=-1)
	{
		CString szNodeIn;
		szNodeIn.Format(_T("%d"),nNodeIn);
		pString->SetRect(rectNodeInputInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeIn);
		pString->Draw(graphics);
	}
	//������
	RECTF rectNodeInputPro=rectBase;
	rectNodeInputPro.Y+=50;
	rectNodeInputPro.Width=300;
	RectScale(rectNodeInputPro,dwScale);
	XChart* pChart=XChart::Get(CHART::CHART_PROGRESS);
	if(!pChart)
		return;
	pChart->SetRect(rectNodeInputPro);
	pChart->SetScale(dwScale);
	pChart->SetWidth(nNode,nNodeIn);
	pChart->SetColor(Color(255,176,46,217),Color(255,49,92,126));
	pChart->Draw(graphics);
	//����ڵ� 
	RECTF rectNodeOutput=rectBase;
	rectNodeOutput.Y+=80;
	RectScale(rectNodeOutput,dwScale);
	pString->SetRect(rectNodeOutput);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("195"),_T("����ڵ�"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectNodeOutputInfo=rectNodeOutput;
	rectNodeOutputInfo.X+=65*dwScale;
	int nNodeOut=pNodeManage->GetNodeOnline(TERM_OUT);
	if(nNodeOut!=-1)
	{
		CString szNodeOut;
		szNodeOut.Format(_T("%d"),nNodeOut);
		pString->SetRect(rectNodeOutputInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeOut);
		pString->Draw(graphics);
	}
	//������
	RECTF rectNodeOutputPro=rectBase;
	rectNodeOutputPro.Y+=105;
	rectNodeOutputPro.Width=300;
	RectScale(rectNodeOutputPro,dwScale);
	pChart->SetRect(rectNodeOutputPro);
	pChart->SetWidth(nNode,nNodeOut);
	pChart->Draw(graphics);

	//��������ͼ
	RECTF rectColumnText=rectBase;
	rectColumnText.Y+=135;
	rectColumnText.Width=300;
	rectColumnText.Height=20;
	RectScale(rectColumnText,dwScale);
	pString->SetRect(rectColumnText);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("207"),_T("����ӹܲ���"))+_T(":")+_T(" ")+_T("(N/CH)"));
	pString->Draw(graphics);

	RECTF rectColumn=rectBase;
	rectColumn.Y+=165;
	rectColumn.Width=300;
	rectColumn.Height=60;
	XChart* pChartColumn=XChart::Get(CHART::CHART_CLOUMN_NODE);
	if(!pChartColumn)
		return;
	pChartColumn->SetRect(rectColumn);
	pChartColumn->SetScale(dwScale);
	pChartColumn->Draw(graphics);
}

void XDrawNodeManage::DrawUserPlate(Graphics& graphics,XNodeManage* pNodeManage)
{
	float dwScale=pNodeManage->GetScale();
	//�û�
	RECTF user(1095,45,80,20);
	RectScale(user,dwScale);
	XChart* pString=XChart::Get(CHART::CHART_STRING);
	if(!pString)
		return;
	pString->SetScale(dwScale);
	pString->SetRect(user);
	pString->SetDrawInfo(_C(_T("68"),_T("�û�")));
	pString->SetDrawType(STRING::STRING_TITLE);
	pString->Draw(graphics);
	//�������꣨982,100��
	RECTF rectBase(982,90,65,20);
	//���û�����
	RECTF rectUser=rectBase;
	RectScale(rectUser,dwScale);
	pString->SetRect(rectUser);
	pString->SetDrawInfo(_C(_T("186"),_T("���û���"))+_T(":"));
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->Draw(graphics);

	RECTF rectUserInfo=rectUser;
	rectUserInfo.X+=65*dwScale;
	int nAllUser=pNodeManage->GetAllUserCount();
	if(nAllUser!=-1)
	{
		CString szAllUser;
		szAllUser.Format(_T("%d"),nAllUser);
		pString->SetRect(rectUserInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szAllUser);
		pString->Draw(graphics);
	}
	//��ǰ�û�
	RECTF rectCurUser=rectBase;
	rectCurUser.Y+=25;
	RectScale(rectCurUser,dwScale);
	pString->SetRect(rectCurUser);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("187"),_T("��ǰ�û�"))+_T(":"));
	pString->Draw(graphics);
	RECTF rectCurUserInfo=rectCurUser;
	rectCurUserInfo.X+=65*dwScale;
	CString szCurUser=pNodeManage->GetCurUser();
	if(szCurUser!=_T(""))
	{
		pString->SetRect(rectCurUserInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szCurUser);
		pString->Draw(graphics);
	}
	//���û�
	RECTF rectSub=rectBase;
	rectSub.Y+=50;
	RectScale(rectSub,dwScale);
	pString->SetRect(rectSub);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("188"),_T("���û���"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectSubInfo=rectSub;
	rectSubInfo.X+=65*dwScale;
	int nCount=pNodeManage->GetUserCount();
	if(nCount!=-1)
	{
		CString szCount;
		szCount.Format(_T("%d"),nCount);
		pString->SetRect(rectSubInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szCount);
		pString->Draw(graphics);
	}
	//��¼�û�
	RECTF rectLogin=rectBase;
	rectLogin.X+=200;
	rectLogin.Y+=50;
	RectScale(rectLogin,dwScale);
	pString->SetRect(rectLogin);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("189"),_T("��¼�û�"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectLoginInfo=rectLogin;
	rectLoginInfo.X+=65*dwScale;
	int nLoginUser=pNodeManage->GetLoginUser(USERLOGIN_ALL);
	if(nLoginUser!=-1)
	{
		CString szLoginUser;
		szLoginUser.Format(_T("%d"),nLoginUser);
		pString->SetRect(rectLoginInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szLoginUser);
		pString->Draw(graphics);
	}
	//���ƽ�����
	RECTF LoginPro=rectBase;
	LoginPro.Y+=75;
	LoginPro.Width=300;
	RectScale(LoginPro,dwScale);
	XChart* pChart=XChart::Get(CHART::CHART_PROGRESS);
	if(!pChart)
		return;
	pChart->SetRect(LoginPro);
	pChart->SetScale(dwScale);
	pChart->SetWidth(nCount,nLoginUser);
	pChart->SetColor(Color(255,239,104,36),Color(255,49,92,126));
	pChart->Draw(graphics);
	//�����¼
	RECTF rectNetLogin=rectBase;
	rectNetLogin.Y+=105;
	RectScale(rectNetLogin,dwScale);
	pString->SetRect(rectNetLogin);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("190"),_T("�����¼"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectNetLoginInfo=rectNetLogin;
	rectNetLoginInfo.X+=65*dwScale;
	int nNetLogin=pNodeManage->GetLoginUser(USERLOGIN_NET);
	if(nNetLogin!=-1)
	{
		CString szNetLogin;
		szNetLogin.Format(_T("%d"),nNetLogin);
		pString->SetRect(rectNetLoginInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNetLogin);
		pString->Draw(graphics);
	}
	//������
	RECTF rectNetLoginPro=rectBase;
	rectNetLoginPro.Y+=130;
	rectNetLoginPro.Width=300;
	RectScale(rectNetLoginPro,dwScale);
	pChart->SetRect(rectNetLoginPro);
	pChart->SetWidth(nLoginUser,nNetLogin);
	pChart->Draw(graphics);
	//�ڵ��¼
	RECTF rectNodeLogin=rectBase;
	rectNodeLogin.Y+=160;
	RectScale(rectNodeLogin,dwScale);
	pString->SetRect(rectNodeLogin);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("191"),_T("�ڵ��¼"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectNodeLoginInfo=rectNodeLogin;
	rectNodeLoginInfo.X+=65*dwScale;
	int nNodeLogin=pNodeManage->GetLoginUser(USERLOGIN_NODE);
	if(nNodeLogin!=-1)
	{
		CString szNodeLogin;
		szNodeLogin.Format(_T("%d"),nNodeLogin);
		pString->SetRect(rectNodeLoginInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeLogin);
		pString->Draw(graphics);
	}
	//������
	RECTF rectNodeLoginPro=rectBase;
	rectNodeLoginPro.Y+=185;
	rectNodeLoginPro.Width=300;
	RectScale(rectNodeLoginPro,dwScale);
	pChart->SetRect(rectNodeLoginPro);
	pChart->SetWidth(nLoginUser,nNodeLogin);
	pChart->Draw(graphics);

	//��������ͼ
	//RECTF rectColumn=rectBase;
	//rectColumn.Y+=240;
	//rectColumn.Width=300;
	//rectColumn.Height=70;
	//XChart* pChartColumn=XChart::Get(CHART::CHART_CLOUMN_USER);
	//if(!pChartColumn)
	//	return;
	//pChartColumn->SetRect(rectColumn);
	//pChartColumn->SetScale(dwScale);
	//pChartColumn->Draw(graphics);
}

void XDrawNodeManage::DrawNodeGroupPlate(Graphics& graphics,XNodeManage* pNodeManage)
{
	float dwScale=pNodeManage->GetScale();

	//�ڵ���
	RECTF group(1060,480,140,25);
	RectScale(group,dwScale);
	XChart* pString=XChart::Get(CHART::CHART_STRING);
	if(!pString)
		return;
	pString->SetScale(dwScale);
	pString->SetRect(group);
	pString->SetDrawType(STRING::STRING_TITLE);
	pString->SetDrawInfo(_C(_T("196"),_T("�ڵ���")));
	pString->Draw(graphics);

	//�������꣨��
	RECTF rectBase(982,525,65,20);
	//�ڵ���
	RECTF rectNodeGroup=rectBase;
	RectScale(rectNodeGroup,dwScale);
	pString->SetRect(rectNodeGroup);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("197"),_T("�ڵ�����"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectNodeGroupInfo=rectNodeGroup;
	rectNodeGroupInfo.X+=65*dwScale;
	int nNodeGroup=pNodeManage->GetNodeGroupByType(NODEGROUP_ALL);
	if(nNodeGroup!=-1)
	{
		CString szNodeGroup;
		szNodeGroup.Format(_T("%d"),nNodeGroup);
		pString->SetRect(rectNodeGroupInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeGroup);
		pString->Draw(graphics);
	}
	//������
	RECTF rectGroupMain=rectBase;
	rectGroupMain.X+=130;
	RectScale(rectGroupMain,dwScale);
	pString->SetRect(rectGroupMain);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("219"),_T("������"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectGroupMainInfo=rectGroupMain;
	rectGroupMainInfo.X+=50*dwScale;
	int nNodeGroupMain=pNodeManage->GetNodeGroupByType(NODEGROUP_MAINSEC);
	if(nNodeGroupMain!=-1)
	{
		CString szNodeGroupMain;
		szNodeGroupMain.Format(_T("%d"),nNodeGroupMain);
		pString->SetRect(rectGroupMainInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeGroupMain);
		pString->Draw(graphics);
	}

	//��ͨ��
	RECTF rectGroupOnline=rectBase;
	rectGroupOnline.X+=230;
	RectScale(rectGroupOnline,dwScale);
	pString->SetRect(rectGroupOnline);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("222"),_T("��ͨ��"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectGroupOnlineInfo=rectGroupOnline;
	rectGroupOnlineInfo.X+=50*dwScale;
	int nNodeGroupOnline=pNodeManage->GetNodeGroupByType(NODEGROUP_GROUP);
	if(nNodeGroupOnline!=-1)
	{
		CString szNodeGroupOnline;
		szNodeGroupOnline.Format(_T("%d"),nNodeGroupOnline);
		pString->SetRect(rectGroupOnlineInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeGroupOnline);
		pString->Draw(graphics);
	}
	//������
	RECTF rectGroupIn=rectBase;
	rectGroupIn.Y+=25;
	RectScale(rectGroupIn,dwScale);
	pString->SetRect(rectGroupIn);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("199"),_T("��������"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectGroupInInfo=rectGroupIn;
	rectGroupInInfo.X+=65*dwScale;
	int nNodeGroupIn=pNodeManage->GetNodeGroupByType(NODEGROUP_IN);
	if(nNodeGroupIn!=-1)
	{
		CString szNodeGroupIn;
		szNodeGroupIn.Format(_T("%d"),nNodeGroupIn);
		pString->SetRect(rectGroupInInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeGroupIn);
		pString->Draw(graphics);
	}
	//������
	RECTF rectGroupInPro=rectBase;
	rectGroupInPro.Y+=50;
	rectGroupInPro.Width=300;
	RectScale(rectGroupInPro,dwScale);
	XChart* pChart=XChart::Get(CHART::CHART_PROGRESS);
	if(!pChart)
		return;
	pChart->SetRect(rectGroupInPro);
	pChart->SetScale(dwScale);
	pChart->SetWidth(nNodeGroupOnline,nNodeGroupIn);
	pChart->SetColor(Color(255,33,139,225),Color(255,49,92,126));
	pChart->Draw(graphics);
	//�����
	RECTF rectGroupOut=rectBase;
	rectGroupOut.Y+=80;
	RectScale(rectGroupOut,dwScale);
	pString->SetRect(rectGroupOut);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("200"),_T("�������"))+_T(":"));
	pString->Draw(graphics);

	RECTF rectGroupOutInfo=rectGroupOut;
	rectGroupOutInfo.X+=65*dwScale;
	int nNodeGroupOut=pNodeManage->GetNodeGroupByType(NODEGROUP_OUT);
	if(nNodeGroupOut!=-1)
	{
		CString szNodeGroupOut;
		szNodeGroupOut.Format(_T("%d"),nNodeGroupOut);
		pString->SetRect(rectGroupOutInfo);
		pString->SetDrawType(STRING::STRING_INFO);
		pString->SetDrawInfo(szNodeGroupOut);
		pString->Draw(graphics);
	}
	//������
	RECTF rectGroupOutPro=rectBase;
	rectGroupOutPro.Y+=105;
	rectGroupOutPro.Width=300;
	RectScale(rectGroupOutPro,dwScale);
	pChart->SetRect(rectGroupOutPro);
	pChart->SetWidth(nNodeGroupOnline,nNodeGroupOut);
	pChart->Draw(graphics);

	//����ͼ
	RECTF rectColumnText=rectBase;
	rectColumnText.Y+=135;
	rectColumnText.Width=300;
	rectColumnText.Height=20;
	RectScale(rectColumnText,dwScale);
	pString->SetRect(rectColumnText);
	pString->SetDrawType(STRING::STRING_ITEM);
	pString->SetDrawInfo(_C(_T("213"),_T("�������Ա����"))+_T(":")+_T(" ")+_T("(N/ID)"));
	pString->Draw(graphics);

	RECTF rectColumn=rectBase;
	rectColumn.Y+=165;
	rectColumn.Width=300;
	rectColumn.Height=60;
	XChart* pChartColumn=XChart::Get(CHART::CHART_CLOUMN_GROUP);
	if(!pChartColumn)
		return;
	pChartColumn->SetRect(rectColumn);
	pChartColumn->SetScale(dwScale);
	pChartColumn->Draw(graphics);
}

void XDrawNodeManage::DrawCentreRectangle(Graphics& graphics,XNodeManage* pNodeManage)
{
	float dwData=pNodeManage->GetScale();

	RECTF interRect(440,70,470,420);
	RECTF rect(500,130,300,300);
	XChart* pChart=XChart::Get(CHART::CHART_PIE);
	if(!pChart)
		return;

	pChart->SetScale(dwData);
	pChart->SetInterRect(interRect);
	pChart->SetRect(rect);
	pChart->Draw(graphics);
}

void XDrawNodeManage::DrawSystemStatus(Graphics& graphics,XNodeManage* pNodeManage)
{
	XSystemStatus* pSystem=XSystemStatus::GetInstance();
	CString szCpuUse=pSystem->m_szCpuUse;
	CString szMemUse=pSystem->m_szMemUse;
	int nCpuTemper=pSystem->m_nCpuTemp;
	int nMatrixTemper=pSystem->m_nMatrixTemp;
	//////////////////////////////////////////////////////////////////////////
	float dwData=pNodeManage->GetScale();
	
	//�������ڴ�ռ��
	RECTF rect1(686,560,80,80);//470,560,80,80
	XChart* pChar=XChart::Get(CHART::CHART_PERCENTAGE);
	if(!pChar)
		return;
	pChar->SetScale(dwData);
	pChar->SetRect(rect1);
	pChar->SetCurRate(szMemUse);
	pChar->SetTitlt(_C(_T("203"),_T("�豸�ڴ�")));
	pChar->SetPrecentageColor(Color(255,51,204,51),Color(255,255,0,51),
							  Color(255,49,92,126),Color(255,8,16,39));
	pChar->Draw(graphics);

	//������cpuռ��
	RECTF rect3(466,560,80,80);//690,560,80,80
	pChar->SetRect(rect3);
	pChar->SetCurRate(szCpuUse);
	pChar->SetTitlt(_C(_T("204"),_T("�豸CPU")));
	pChar->Draw(graphics);

	//����оƬ�¶�
	RECTF rect4(786,630,100,100);
	XChart* pInstrument=XChart::Get(CHART::CHART_INSTRUMENT);
	if(!pInstrument)
		return;
	pInstrument->SetScale(dwData);
	pInstrument->SetRect(rect4);
	pInstrument->SetDegress(nMatrixTemper);
	pInstrument->SetTitlt(_C(_T("206"),_T("����оƬ")));
	pInstrument->SetInstrumentColor(Color(255,51,204,51),Color(255,255,0,51),
							  Color(255,49,92,126),Color(255,8,16,39));
	pInstrument->Draw(graphics);

	//CPU�¶�
	RECTF rect2(566,630,100,100);
	pInstrument->SetRect(rect2);
	pInstrument->SetDegress(nCpuTemper);
	pInstrument->SetTitlt(_C(_T("205"),_T("CPU�¶�")));
	pInstrument->SetInstrumentColor(Color(255,51,204,51),Color(255,255,0,51),
									Color(255,49,92,126),Color(255,8,16,39));
	pInstrument->Draw(graphics);
}

void XDrawNodeManage::SetNodeIndexAndRect(XNodeManage* pNodeManage)
{
	//�������,��Ϊ�������
	int nIndexIn=1;
	MAP_NODE& MapNode=pNodeManage->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_IN)
		{
			pNode->SetIndex(nIndexIn);
			nIndexIn++;
		}
	}

	int nIndexOut=1;
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			pNode->SetIndex(nIndexOut);
			nIndexOut++;
		}
	}

	//��������,��Ϊ�������
	//////////////////////////////////////////////////////////////////////////
	//����
	//��������
	int nTextHeight=TEXT_HEIGHT;
	
	//int nTextWidth=50;
	//************************
	int nWidth=NODE_WIDTH;
	int nHeight=NODE_HEIGHT;

	int nLeft=0;
	int nX=nLeft;
	int nY=nTextHeight/*+5*/;
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_IN)
		{
			int nIndex=pNode->GetIndex();

			CRect rect(nX,nY,nX+nWidth,nY+nHeight);
			int nTop=rect.bottom-TEXT_HEIGHT;
			CRect TextRect(rect.left,nTop,rect.right,rect.bottom);

			rect.bottom-=TEXT_HEIGHT;
			pNode->SetRect(rect);
			pNode->SetTextRect(TextRect);

			if((nIndex%NODECOUNT_H)==0)
			{
				nX=nLeft;
				nY=nY+nHeight;
			}
			else
			{
				nX=nX+nWidth+DISTANCE;
			}
		}
	}

	//******************************************
	//������������߶�
	int nNodeInHeight=pNodeManage->GetHightOfNodeIn();
	
	nX=nLeft;
	nY=nTextHeight+nNodeInHeight+DISTANCE/*+5*/;

	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		if(pNode->GetNodeType()==TERM_OUT)
		{
			int nIndex=pNode->GetIndex();

			CRect rect(nX,nY,nX+nWidth,nY+nHeight);
			int nTop=rect.bottom-TEXT_HEIGHT;
			CRect TextRect(rect.left,nTop,rect.right,rect.bottom);

			rect.bottom-=TEXT_HEIGHT;
			pNode->SetRect(rect);
			pNode->SetTextRect(TextRect);

			if((nIndex%NODECOUNT_H)==0)
			{
				nX=nLeft;
				nY=nY+nHeight;
			}
			else
			{
				nX=nX+nWidth+DISTANCE;
			}
		}
	}

	int nTextWidth=(pNodeManage->GetWidthOfNodeIn()>=pNodeManage->GetWidthOfNodeOut())?pNodeManage->GetWidthOfNodeIn():pNodeManage->GetWidthOfNodeOut();
	//int nTextWidth=45;
	nX=0;
	nY=0;
	m_rectTextIn.SetRect(nX,nY,nX+nTextWidth,nY+nTextHeight);

	nY=nNodeInHeight+DISTANCE;
	m_rectTextOut.SetRect(nX,nY,nX+nTextWidth,nY+nTextHeight);
}

void XDrawNodeManage::DrawNode(Graphics& graphics,XNodeManage* pNodeManage)
{
	float dwScale=pNodeManage->GetScale();

	CString szPath=HandlePath::GetPhotoPath(_T("node.png"));
	Gdiplus::Image* pImage=Gdiplus::Image::FromFile(szPath);

	Gdiplus::Pen pen(Gdiplus::Color(255,255,255,255),1.5f);//ֱ�߻���
	Gdiplus::Pen penLine(Gdiplus::Color(255,0,0,0),1.0f);//ֱ�߻���
	Gdiplus::Pen penSelect(Gdiplus::Color(255,255,0,0),1.5f);//ֱ�߻���
	Gdiplus::SolidBrush brush(Gdiplus::Color(255,41,57,85));//������ɫ

	float dwTextSize=10*dwScale;
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily, dwTextSize, FontStyleRegular,UnitPoint);
	Gdiplus::SolidBrush textbrush(Color(255,40,40,40));
	Gdiplus::SolidBrush namebrush(Color(255,91,155,213));

	Gdiplus::StringFormat stringForamt;
	stringForamt.SetAlignment(StringAlignmentCenter);
	stringForamt.SetLineAlignment(StringAlignmentCenter);

	Gdiplus::StringFormat stringForamtTitle;
	stringForamtTitle.SetAlignment(StringAlignmentNear);
	stringForamtTitle.SetLineAlignment(StringAlignmentNear);

	graphics.SetTextRenderingHint(TextRenderingHintSystemDefault);  

	//���ƽڵ�
	MAP_NODE& MapNode=pNodeManage->GetMapNode();
	for(auto iter=MapNode.begin();iter!=MapNode.end();++iter)
	{
		XNode* pNode=iter->second;
		int nID=pNode->GetNodeID();
		int nChannel=pNode->GetChannel();
		BOOL bSelected=pNode->GetSelected();
		CRect rect=pNode->GetRect();
		
		RECTF drawRect(rect.left*dwScale,rect.top*dwScale,rect.Width()*dwScale,rect.Height()*dwScale);
		drawRect.Y+=PIC_HEIGHT*dwScale+DISTANCE_V;
		//����ͼƬ
		//graphics.DrawImage(pImage,drawRect,0.0f,0.0f,(Gdiplus::REAL)pImage->GetWidth(),(Gdiplus::REAL)pImage->GetHeight(),Gdiplus::UnitPixel,NULL,NULL,NULL);
		//������ɫ
		graphics.FillRectangle(&brush,drawRect.X,drawRect.Y,drawRect.Width,drawRect.Height);
		//��������
		CString szName=pNode->GetNodeName();
		graphics.DrawString(szName,-1,&font,drawRect,&stringForamt,&namebrush);

		//���Ʊ߿�
		graphics.DrawRectangle(&pen,drawRect.X,drawRect.Y,drawRect.Width,drawRect.Height);

		//ѡ��
		if(bSelected)
			graphics.DrawRectangle(&penSelect,drawRect.X,drawRect.Y,drawRect.Width,drawRect.Height);

		//��������
		CRect rectTect=pNode->GetTextRect();
		RECTF drawTextRect(rectTect.left*dwScale,rectTect.top*dwScale,rectTect.Width()*dwScale,rectTect.Height()*dwScale);
		drawTextRect.Y+=PIC_HEIGHT*dwScale+DISTANCE_V;
		//graphics.FillRectangle(&brush, drawTextRect.X, drawTextRect.Y, drawTextRect.Width, drawTextRect.Height);

		//CString szText=pNode->GetNodeName();
		CString szText;
		szText.Format(_T("CH:%d"),nChannel);
		graphics.DrawString(szText,-1,&font,drawTextRect,&stringForamt,&textbrush);
	}
	//////////////////////////////////////////////////////////////////////////
	//���롢���
	if(MapNode.size()!=0)
	{
		//��������
		RECTF drawTextRectIn(m_rectTextIn.left*dwScale,m_rectTextIn.top*dwScale,m_rectTextIn.Width()*dwScale,m_rectTextIn.Height()*dwScale);
		drawTextRectIn.Y+=PIC_HEIGHT*dwScale+DISTANCE_V;
		graphics.DrawString(XTranslationManage::GetInstance()->_C(_T("759"),_T("����")),-1,&font,drawTextRectIn,&stringForamtTitle,&textbrush);
		//graphics.DrawLine(&penLine,drawTextRectIn.X,drawTextRectIn.GetBottom(),drawTextRectIn.X+drawTextRectIn.Width,drawTextRectIn.GetBottom());

		RECTF drawTextRectOut(m_rectTextOut.left*dwScale,m_rectTextOut.top*dwScale,m_rectTextOut.Width()*dwScale,m_rectTextOut.Height()*dwScale);
		drawTextRectOut.Y+=PIC_HEIGHT*dwScale+DISTANCE_V;
		graphics.DrawString(XTranslationManage::GetInstance()->_C(_T("760"),_T("���")),-1,&font,drawTextRectOut,&stringForamtTitle,&textbrush);
		//graphics.DrawLine(&penLine,drawTextRectOut.X,drawTextRectOut.GetBottom(),drawTextRectOut.X+drawTextRectOut.Width,drawTextRectOut.GetBottom());
	}
}

void XDrawNodeManage::DrawDrag(Graphics& graphics,XNodeManage* pNodeManage)
{
	float dwScale=pNodeManage->GetScale();
	RECTF rect=pNodeManage->GetDragRect();

	graphics.SetTextRenderingHint(TextRenderingHintSystemDefault);  
	Gdiplus::SolidBrush brush(Gdiplus::Color(255,198,198,198));
	Gdiplus::Pen pen(Gdiplus::Color(255,0,0,0),1.0f);
	Gdiplus::SolidBrush textbrush(Color(255,0,0,0));

	float dwTextSize=10*dwScale;
	Gdiplus::FontFamily fontfamily(APP_FONT);
	Gdiplus::Font font(&fontfamily,dwTextSize,FontStyleRegular,UnitPoint);
	
	Gdiplus::StringFormat stringForamt;
	stringForamt.SetAlignment(StringAlignmentCenter);
	stringForamt.SetLineAlignment(StringAlignmentCenter);
	
	RECTF drawRect(rect.X*dwScale,rect.Y*dwScale,rect.Width*dwScale,rect.Height*dwScale);

	graphics.FillRectangle(&brush,drawRect);
	graphics.DrawRectangle(&pen,drawRect);
	//////////////////////////////////////////////////////////////////////////
	//����
	int nNodeType=XConstantData::GetInstance()->GetNodeType();
	//int nNodeID=XConstantData::GetInstance()->GetNodeID();
	int nChannel=XConstantData::GetInstance()->GetNodeChannel();
	CString szText=_T("");
	if(nNodeType==TERM_OUT)
	{
		szText.Format(_T("%s%d"),XTranslationManage::GetInstance()->_C(_T("63"),_T("���")),nChannel);
	}
	else if(nNodeType==TERM_IN)
	{
		szText.Format(_T("%s%d"),XTranslationManage::GetInstance()->_C(_T("62"),_T("����")),nChannel);
	}

	graphics.DrawString(szText,-1,&font,drawRect,&stringForamt,&textbrush);
}