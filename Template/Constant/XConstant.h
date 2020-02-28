#pragma once

//�ͷ�
#define RELEASE(X) if(NULL!=X){delete X;X=NULL;}

extern const CString APP_NAME;
extern const CString APP_VERSION;
extern const CString APP_REGISTRYKEY;

extern const CString APP_ININAME;
extern const CString APP_DATAFILENAME;
extern const CString APP_FONT;
extern const CString FILTER_PHOTO;
extern const Color g_Color[40];


//��Ϣ�¼�
extern const UINT MSG_UDP;
extern const UINT MSG_ADDDOCUMENT;
extern const UINT MSG_BTN_LCLICK;
extern const UINT MSG_TCP;


constexpr auto DRAWDISTANCE_X                              =50;
constexpr auto DRAWDISTANCE_Y                              =50;
//ÿ�нڵ����
constexpr auto NODECOUNT_H                                 =12;
//�ڵ���
constexpr auto NODE_WIDTH                                  =100;
constexpr auto NODE_HEIGHT                                 =80;
//�ڵ�������
constexpr auto DISTANCE                                    =10;
constexpr auto DISTANCE_V                                  =20;
//�ڵ�����߶�
constexpr auto TEXT_HEIGHT                                 =20;
//��άͼƬ���
constexpr auto PIC_WIDTH                                   =1350;
constexpr auto PIC_HEIGHT                                  =800;
//��ϯ����
constexpr auto PAGE_WIDTH                                  =800;
constexpr auto PAGE_HEIGHT                                 =810;
constexpr auto SCREEN_H                                    =160;
constexpr auto SCREEN_V                                    =90;
//ͨ������ͼ���
constexpr auto CHANNEL_W                                   =25;
constexpr auto CHANNEL_H                                   =14;

//��ʱ��										    
constexpr auto TIMERID_HEART                               =1;
constexpr auto TIMESPACE_HEART                             =2000;

constexpr auto TIMERID_SYSTEM                              =2;
constexpr auto TIMERSPACE_SYSTEM                           =3000;

constexpr auto TIMERID_CLICK                               =3;
constexpr auto TIMERSPACE_CLICK                            =1000;



//Ȩ�޷�������
constexpr auto POWER_REDATA_LIST                           =_T("LIST");
constexpr auto POWER_REDATA_QUERY                          =_T("QUERY");
constexpr auto POWER_REDATA_ADD                            =_T("ADD");
constexpr auto POWER_REDATA_DEL                            =_T("DEL");
constexpr auto POWER_REDATA_UPDATE                         =_T("UPDATE");

constexpr auto STORE_REDATA_QUERY                          =_T("QUERY");
constexpr auto STORE_REDATA_ADD                            =_T("ADD");
constexpr auto STORE_REDATA_DEL                            =_T("DEL");

//�Զ���Json ʶ���ֶ�
//constexpr auto BLINK_FLAG                                  =_T("BLINK");



//��־�¼�
#define PAGELISTCOUNT          23

#define EVENT_START            _T("start")
#define EVENT_CPU_EVENT        _T("CPU event")
#define EVENT_MATRIX_EVENT     _T("matrix event")
#define EVENT_USER_LOGIN       _T("user login")
#define EVENT_USER_LOGOUT      _T("user logout")
#define EVENT_TERM_LOGIN       _T("term login")
#define EVENT_TERM_LOGOUT      _T("term logout")
#define EVENT_CREATE_USER      _T("create user")
#define EVENT_DELETE_USER      _T("delete user")
#define EVENT_MODIFY_USER      _T("modify user")
#define EVENT_REMOVE_CTRL      _T("remote ctrl")
#define EVENT_REMOVE_VIEW      _T("remote view")
#define EVENT_CTRL             _T("ctrl")
#define EVENT_VIEW             _T("view")
#define EVENT_PUSH             _T("push")
#define EVENT_TERM_CONNECT     _T("term connect")
#define EVENT_TERM_DISCON      _T("term discon")
#define EVENT_TERM_SET_ID      _T("term set id")
#define EVENT_TERM_RENAME      _T("term rename")
#define EVENT_TERM_CREATE      _T("term create")
#define EVENT_TERM_DELETE      _T("term delete")
#define EVENT_TERM_MODIFY      _T("term modify")
//#define EVENT_TERM_MODIFY      _T("term modify")


//������Ϣ
constexpr auto KVM_DATABASE_DONE                           =101;
constexpr auto KVM_ERR_NONE                                =0;
												           
constexpr auto KVM_ERR_DEFAULT                             =-100;
constexpr auto KVM_ERR_PARAM                               =-101;
constexpr auto KVM_ERR_PREMISSION_DENIED                   =-102;
constexpr auto KVM_ERR_PRIVILEGE_DENIED                    =-103;
constexpr auto KVM_ERR_USER_NOT_FOUND                      =-104;
constexpr auto KVM_ERR_PASSWORD_MISMATCH                   =-105;
constexpr auto KVM_ERR_USER_ALREADY_LOGIN                  =-106;
constexpr auto KVM_ERR_USER_ALREADY_LOGIN_OTHER_IP         =-107;
constexpr auto KVM_ERR_USER_ALREADY_LOGIN_OTHER_TERM       =-108;
constexpr auto KVM_ERR_TERM_ALREADY_LOGIN                  =-109;

constexpr auto KVM_ERR_TERM_NOT_FOUND                      =-110;
constexpr auto KVM_ERR_TERM_ID_ERR                         =-111;
constexpr auto KVM_ERR_TERM_NOT_CONNECT                    =-112;
constexpr auto KVM_ERR_USER_FAV_GET_FAIL                   =-113;
constexpr auto KVM_ERR_HARDWARE_CHANNEL_ERR                =-114;
constexpr auto KVM_ERR_TERM_NOT_LOGIN                      =-115;
constexpr auto KVM_ERR_TERM_TYPE_ERR                       =-116;
constexpr auto KVM_ERR_TERM_IS_CTRL_EXCLUSIVE              =-117;
												           
constexpr auto KVM_ERR_USER_ALREADY_EXIST                  =-118;
constexpr auto KVM_ERR_DATABASE                            =-119;
constexpr auto KVM_ERR_PRIVILEGE                           =-120;
constexpr auto KVM_ERR_PRIVILEGE_TYPE                      =-121;
constexpr auto KVM_ERR_FAV_TERM_ALREADY_EXIST              =-122;
constexpr auto KVM_ERR_FAV_TERM_NOT_FOUND                  =-123;
												           
constexpr auto KVM_ERR_DB_COLUMN                           =-201;


//��ԴID
constexpr auto ID_BEGIN                          =35000;
constexpr auto ID_ADDINPUTSIGNALEXPAND           =(ID_BEGIN+100);
constexpr auto IDC_STATIC_MESSAGEBOXDLG_TEXT     =(ID_BEGIN+101);
constexpr auto IDC_BTN_MESSAGEBOXDLG_1           =(ID_BEGIN+102);
constexpr auto IDC_BTN_MESSAGEBOXDLG_2	         =(ID_BEGIN+103);
constexpr auto IDC_BTN_MESSAGEBOXDLG_3	         =(ID_BEGIN+104);
constexpr auto IDC_COMBO_LANGUAGE                =(ID_BEGIN+105);
constexpr auto IDC_COMBO_SCALE                   =(ID_BEGIN+106);
constexpr auto IDC_EDIT_DEVICEIP                 =(ID_BEGIN+107);
constexpr auto IDC_EDIT_DEVICEPORT               =(ID_BEGIN+108);
constexpr auto IDC_BTN_OPENNET                   =(ID_BEGIN+109);
constexpr auto IDC_BTN_CLOSENET                  =(ID_BEGIN+110);
constexpr auto IDC_INPUTSIGNALPANE               =(ID_BEGIN+111);
constexpr auto IDC_BTN_LOGIN                     =(ID_BEGIN+112);
constexpr auto IDC_BTN_LOGINOUT                  =(ID_BEGIN+123);
constexpr auto IDC_BTN_POWER			         =(ID_BEGIN+124);
constexpr auto ID_PROPERTIESWND                  =(ID_BEGIN+125);
constexpr auto ID_LEFTTREE				         =(ID_BEGIN+126);
constexpr auto ID_LEFTPANE				         =(ID_BEGIN+127);
constexpr auto ID_MENUIN				         =(ID_BEGIN+128);
constexpr auto ID_MENUOUTOFLOGOUT		         =(ID_BEGIN+129);
constexpr auto ID_BTN_OSDIMAGE			         =(ID_BEGIN+130);
constexpr auto ID_BTN_FRONT				         =(ID_BEGIN+131);
constexpr auto ID_BTN_BACK				         =(ID_BEGIN+132);
constexpr auto IDC_BTN_SEATSCALE		         =(ID_BEGIN+133);
constexpr auto IDC_EDIT_SEATROW			         =(ID_BEGIN+134);
constexpr auto IDC_EDIT_SEATCOLUMN		         =(ID_BEGIN+135);
constexpr auto ID_SEATARRAGETREE		         =(ID_BEGIN+136);
constexpr auto ID_BTN_SAVESEAT			         =(ID_BEGIN+137);
constexpr auto ID_BTN_SENDSEAT			         =(ID_BEGIN+138);
constexpr auto ID_GROUPDEL				         =(ID_BEGIN+139);
constexpr auto ID_GROUPRENAME			         =(ID_BEGIN+140);
constexpr auto ID_SEATDEL				         =(ID_BEGIN+141);
constexpr auto ID_BTN_CLEARSEAT			         =(ID_BEGIN+142);
constexpr auto ID_SEATRENAME			         =(ID_BEGIN+143);
constexpr auto ID_COMBO_THEME			         =(ID_BEGIN+144);
constexpr auto ID_BTN_THEME  			         =(ID_BEGIN+145);
constexpr auto ID_BTN_LANGUAGE  		         =(ID_BEGIN+146);
constexpr auto ID_BTN_SCALE  			         =(ID_BEGIN+147);
constexpr auto ID_BTN_ABOUT				         =(ID_BEGIN+148);
constexpr auto IDC_EDIT_SECONDDEVICEIP           =(ID_BEGIN+149);
constexpr auto IDC_EDIT_SECONDDEVICEPORT         =(ID_BEGIN+150);
constexpr auto ID_STATUSBAR_USER		         =(ID_BEGIN+151);
constexpr auto ID_STATUSBAR_DEVICE1		         =(ID_BEGIN+152);
constexpr auto ID_STATUSBAR_DEVICE2		         =(ID_BEGIN+153);
constexpr auto ID_BTN_BG				         =(ID_BEGIN+154);
constexpr auto ID_BTN_SEAT				         =(ID_BEGIN+155);
constexpr auto ID_BTN_ALIGN				         =(ID_BEGIN+156);
constexpr auto IDC_BTN_DEVICENET		         =(ID_BEGIN+157);
constexpr auto ID_BTN_MENU				         =(ID_BEGIN+158);
constexpr auto ID_MENU_PIC				         =(ID_BEGIN+159);
constexpr auto ID_TREE  				         =(ID_BEGIN+160);
constexpr auto ID_MENU_DELGROUP                  =(ID_BEGIN+161);
constexpr auto ID_MENU_ALTERGROUP                =(ID_BEGIN+162);
constexpr auto ID_MENU_ALTERNODE                 =(ID_BEGIN+163);
constexpr auto ID_MENU_REMOVENODE                =(ID_BEGIN+164);
constexpr auto ID_MENU_ADDGROUP                  =(ID_BEGIN+165);
constexpr auto ID_BTN_ARRAY                      =(ID_BEGIN+166);
constexpr auto ID_MENU_MAINSECOND                =(ID_BEGIN+167);
constexpr auto ID_BTN_CONTROL                    =(ID_BEGIN+168);
constexpr auto ID_SCENETREE                      =(ID_BEGIN+169);
constexpr auto ID_BTN_SAVESCENE                  =(ID_BEGIN+170);
constexpr auto ID_SCENEPANE                      =(ID_BEGIN+171);
constexpr auto ID_ALTERSCENE                     =(ID_BEGIN+172);
constexpr auto ID_DELSCENE                       =(ID_BEGIN+173);
constexpr auto ID_REMOVE                         =(ID_BEGIN+174);
constexpr auto ID_BTN_LOG                        =(ID_BEGIN+175);
constexpr auto ID_BTN_MATRIXARRAY                =(ID_BEGIN+176);
constexpr auto ID_BTN_MATRIXSCALE                =(ID_BEGIN+177);
constexpr auto ID_BTN_UPDATE                     =(ID_BEGIN+177);
constexpr auto ID_BTN_FOLDER                     =(ID_BEGIN+178);
constexpr auto ID_BTN_ADDSPLIT                   =(ID_BEGIN+179);
constexpr auto ID_BTN_SPLITSCALE                 =(ID_BEGIN+180);
constexpr auto ID_MENU_UP                        =(ID_BEGIN+181);
constexpr auto ID_MENU_DOWN                      =(ID_BEGIN+182);
constexpr auto ID_MENU_TOP                       =(ID_BEGIN+183);
constexpr auto ID_MENU_BOTTOM                    =(ID_BEGIN+184);
constexpr auto ID_BTN_CLEARSIGNAL                =(ID_BEGIN+185);
constexpr auto ID_BTN_ADDMODEL                   =(ID_BEGIN+186);
constexpr auto ID_BTN_LIMITMODEL                 =(ID_BEGIN+187);
constexpr auto ID_MENU_PROPERTY                  =(ID_BEGIN+188);
constexpr auto ID_MENU_QUICKTOP                  =(ID_BEGIN+189);
constexpr auto ID_MENU_FULLSCREEN                =(ID_BEGIN+190);
constexpr auto ID_MENU_RESTORE                   =(ID_BEGIN+191);
constexpr auto ID_MENU_EXTEND                    =(ID_BEGIN+192);
constexpr auto ID_MENU_CLOSESIGNAL               =(ID_BEGIN+193);
constexpr auto ID_MENU_SAVESCENE                 =(ID_BEGIN+194);
constexpr auto ID_DELSPLITSCENE                  =(ID_BEGIN+195);
constexpr auto ID_ALTERSPLITSCENE                =(ID_BEGIN+196);
constexpr auto ID_REMOVEFROMSGROUP               =(ID_BEGIN+197);
constexpr auto ID_ALTERSPLITGROUP                =(ID_BEGIN+198);
constexpr auto ID_DELSPLITGROUP                  =(ID_BEGIN+199);




constexpr auto ID_NODEID                         =(ID_BEGIN+200);
constexpr auto ID_NODENAME                       =(ID_BEGIN+201);
constexpr auto ID_NODECHANNEL					 =(ID_BEGIN+202);
constexpr auto ID_NODETYPE						 =(ID_BEGIN+203);
constexpr auto ID_NODEGROUP					     =(ID_BEGIN+204);
constexpr auto ID_NODEMASTER					 =(ID_BEGIN+205);
constexpr auto ID_NODECONTROL					 =(ID_BEGIN+206);
constexpr auto ID_NODENO						 =(ID_BEGIN+207);
constexpr auto ID_NODELOGIN					     =(ID_BEGIN+208);
constexpr auto ID_NODELOGINUSER				     =(ID_BEGIN+209);
constexpr auto ID_LOGINIP						 =(ID_BEGIN+210);
constexpr auto ID_LOGINPORT					     =(ID_BEGIN+211);
constexpr auto ID_TAKEOVERMODEL				     =(ID_BEGIN+212);
constexpr auto ID_TAKEOVERNODE					 =(ID_BEGIN+213);
constexpr auto ID_TARGETNODE					 =(ID_BEGIN+214);
constexpr auto ID_PREVIEW						 =(ID_BEGIN+215);
constexpr auto ID_PREVIEWTARGET				     =(ID_BEGIN+216);
constexpr auto ID_NODEINHASSIGNAL				 =(ID_BEGIN+217);
constexpr auto ID_AUDIOMODEL					 =(ID_BEGIN+218);
constexpr auto ID_RESOLUATION					 =(ID_BEGIN+219);
constexpr auto ID_OUTMODEL						 =(ID_BEGIN+220);
constexpr auto ID_MATRIX						 =(ID_BEGIN+221);
constexpr auto ID_OSDIMAGE						 =(ID_BEGIN+222);
constexpr auto ID_SEATNAME                       =(ID_BEGIN+223);
constexpr auto ID_SEATROW                        =(ID_BEGIN+224);
constexpr auto ID_SEATCOLUMN                     =(ID_BEGIN+225);
constexpr auto ID_SEATMODEL                      =(ID_BEGIN+226);
constexpr auto ID_SEATCOLOR                      =(ID_BEGIN+227);
constexpr auto ID_SEATBG                         =(ID_BEGIN+228);
constexpr auto ID_SEATPIC                        =(ID_BEGIN+229);
constexpr auto ID_SEATRECTX                      =(ID_BEGIN+230);
constexpr auto ID_SEATRECTY                      =(ID_BEGIN+231);
constexpr auto ID_SEATRECTW                      =(ID_BEGIN+232);
constexpr auto ID_SEATRECTH                      =(ID_BEGIN+233);
constexpr auto ID_SEATTRANS                      =(ID_BEGIN+234);
constexpr auto ID_HIDMODEL                       =(ID_BEGIN+235);
constexpr auto ID_SPLITSCREEN                    =(ID_BEGIN+236);
constexpr auto ID_AUDIOSRC                       =(ID_BEGIN+237);
constexpr auto ID_BINDCFG                        =(ID_BEGIN+238);
constexpr auto ID_BINDNODEID                     =(ID_BEGIN+239);
constexpr auto ID_HOTKEY1                        =(ID_BEGIN+240);
constexpr auto ID_HOTKEY2                        =(ID_BEGIN+241);
constexpr auto ID_HOTKEY3                        =(ID_BEGIN+242);
constexpr auto ID_HOTKEY4                        =(ID_BEGIN+243);
constexpr auto ID_FUNCTION1                      =(ID_BEGIN+244);
constexpr auto ID_VALUE1                         =(ID_BEGIN+245);
constexpr auto ID_FUNCTION2                      =(ID_BEGIN+246);
constexpr auto ID_VALUE2                         =(ID_BEGIN+247);
constexpr auto ID_FUNCTION3                      =(ID_BEGIN+248);
constexpr auto ID_VALUE3                         =(ID_BEGIN+249);
constexpr auto ID_ENABLE1                        =(ID_BEGIN+250);
constexpr auto ID_ENABLE2                        =(ID_BEGIN+251);
constexpr auto ID_ENABLE3                        =(ID_BEGIN+252);
constexpr auto ID_RECOVER                        =(ID_BEGIN+253);




																
constexpr auto ID_NODEGROUPID					 =(ID_BEGIN+300);
constexpr auto ID_NODEGROUPNAME				     =(ID_BEGIN+301);
constexpr auto ID_NODEGROUPMASTER				 =(ID_BEGIN+302);
constexpr auto ID_NODEGROUPMATRIX				 =(ID_BEGIN+303);
constexpr auto ID_NODEGROUPCREATOR				 =(ID_BEGIN+304);

constexpr auto ID_MAINSECGROUPNAME               =(ID_BEGIN+305);
constexpr auto ID_MAINSECGROUPID                 =(ID_BEGIN+306);
constexpr auto ID_MAINSECGROUPMASTER             =(ID_BEGIN+307);
constexpr auto ID_MAINSECGROUPMATRIX             =(ID_BEGIN+308);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
typedef enum class chart:char
{
	CHART_CLOUMN_NODE,//����ͼ
	CHART_CLOUMN_USER,
	CHART_CLOUMN_GROUP,
	CHART_CLOUMN_SYSTEM,
	CHART_PROGRESS,//������
	CHART_PIE,//��ͼ
	CHART_PERCENTAGE,//�ٷֱ�
	CHART_STRING,
	CHART_INSTRUMENT,

	CHART_NULL
}CHART;

typedef enum class string:char
{   //��ά������������
	STRING_TITLE,//��������
	STRING_ITEM,
	STRING_INFO,
	STRING_INDEX,

	STRING_NULL
}STRING;

enum LANGUAGETYPE//��������
{
	LANGUAGETYPE_ZH_CN,
	LANGUAGETYPE_ZH_TW,
	LANGUAGETYPE_EN,

	LANGUAGETYPE_NULL
};

enum CURSORTYPE//�������
{
	CURSORTYPE_NORMAL,//��ͨ
	CURSORTYPE_HAND,//����
	CURSORTYPE_MOVE,//�ƶ�
	CURSORTYPE_NESW,//˫��ͷָ�򶫱�������
	CURSORTYPE_NS,//˫��ͷָ���ϱ�
	CURSORTYPE_NWSE,//˫��ͷָ�������Ͷ���
	CURSORTYPE_WE,//˫��ͷָ����
	CURSORTYPE_DRAW,//ʮ��

	CURSORTYPE_SIZE,
	CURSORTYPE_NULL,
};

enum POSITIONTYPE//λ������
{
	POSITIONTYPE_LT,
	POSITIONTYPE_RT,
	POSITIONTYPE_LB,
	POSITIONTYPE_RB,
	POSITIONTYPE_L,
	POSITIONTYPE_R,
	POSITIONTYPE_T,
	POSITIONTYPE_B,

	POSITIONTYPE_NULL,
};

enum XDATATYPE//�ؼ�����
{
	XDATATYPE_ALL,

	XDATATYPE_LANGUAGENAME,//��������
	XDATATYPE_THEME,//����
	XDATATYPE_SCALE,//��ʾ����
	XDATATYPE_SEATSCALE,//��ϯ����
	XDATATYPE_DEVICEIP,//�豸IP
	XDATATYPE_DEVICEPORT,//�豸Port
	XDATATYPE_SECONDDEVICEIP,//�豸IP
	XDATATYPE_SECONDDEVICEPORT,//�豸Port

	XDATATYPE_LOGIN,
	XDATATYPE_LOGINOUT,

	XDATATYPE_SEATROW,//seat row
	XDATATYPE_SEATCOLUMN,

	XDATATYPE_NULL
};


enum OPERATETYPE//��������
{
	OPERATETYPE_RELOADINTERFACE=1,//���ؽ���
	OPERATETYPE_ABOUT,//����

	OPERATETYPE_OPENNET,//������
	OPERATETYPE_CLOSENET,//�ر�����
	OPERATETYPE_UPDATE,//����
	OPERATETYPE_FOLDER,//�ļ���
	OPERATETYPE_REROOTFOLDER,//�����ļ���

	OPERATETYPE_LOGIN,//��¼
	OPERATETYPE_LOGINOUT,//ע��

	OPERATETYPE_POWER,//Ȩ��
	OPERATETYPE_REPOWER,

	OPERATETYPE_RELOGIN,//��¼
	OPERATETYPE_RELOGINOUT,

	OPERATETYPE_HEART,//����
	OPERATETYPE_REHEART,

	OPERATETYPE_REUSERLIST,//�����û��б�
	OPERATETYPE_RESTORELIST,//�����ղ��б�

	OPERATETYPE_DEVICEINFO,//��ȡ�豸ͨ����
	OPERATETYPE_REDEVICEINFO,
	OPERATETYPE_ALLNODE,//��ȡȫ���ڵ��б�

	OPERATETYPE_ADDSEAT,//�����ϯ


	OPERATETYPE_GETNODECHANNEL,//��ȡ�ڵ�����״̬
	OPERATETYPE_RENODECHANNEL,

	OPERATETYPE_RENODEINFO,//���ؽڵ㲿����Ϣ
	OPERATETYPE_RENODEDETAILINFO,//������ϸ��Ϣ
	OPERATETYPE_RENODESTATUS,//���ؽڵ�״̬

	OPERATETYPE_GETLOGINUSER,//��ȡ��¼�û�����
	OPERATETYPE_RELOGINUSER,
	OPERATETYPE_RELOGINUSERSTATUS,

	OPERATETYPE_RENODELOGIN,//�ڵ��¼
	OPERATETYPE_RENODELOGOUT,//�˳�

	OPERATETYPE_RETAKEOVER,//�ӹ�
	OPERATETYPE_RETAKEOVERCANCEL,//ȡ���ӹ�

	OPERATETYPE_PREVIEW,//Ԥ��

	OPERATETYPE_ALTERNODENAME,//���Ľڵ�����

	OPERATETYPE_MENUOUTOFLOGOUT,//����˵�

	OPERATETYPE_MATRIXSTATUS,//�����л�״̬
	OPERATETYPE_REMATRIXSTATUS,
	OPERATETYPE_REMATRIX,//�����л�

	OPERATETYPE_OSDIMAGE,//osd��ͼ
	OPERATETYPE_REOSDIMAGE,
	OPERATETYPE_REHIDEOSDIMAGE,//����osd��ͼ

	OPERATETYPE_CONTROL,//�п�
	OPERATETYPE_SAVESCENE,//����ӹܳ���
	OPERATETYPE_INITSCENE,//��ʼ��������
	OPERATETYPE_LOG,//��־
	OPERATETYPE_RELOG,
	OPERATETYPE_INITMATRIXARRAY,//��ʼ������������Ļ

	OPERATETYPE_SAVESEAT,//������ϯ
	OPERATETYPE_SENDSEAT,//����
	OPERATETYPE_CLEARSEAT,//���

	OPERATETYPE_INITAPPDATA,//��ʼ�������ļ�
	OPERATETYPE_GETAPPDATA,

	OPERATETYPE_READNODEGROUP,//��ȡȫ���ڵ���
	OPERATETYPE_READONLINENODEGROUP,//��ȡ���߽ڵ���
	OPERATETYPE_REREADNODEGROUP,
	OPERATETYPE_RENODEGROUPINFO,

	OPERATETYPE_REREFREASGGROUP,//�������Ա��Ϣ

	OPERATETYPE_SCREENARRAY,//��ϯ��Ļ����

	OPERATETYPE_NODECOLUMNDATA,//�ڵ�����ͼ����
	OPERATETYPE_CLEARCOLUMNDATA,//��������ͼ����

	OPERATETYPE_SYSTEMSTATUS,//�豸�������
	OPERATETYPE_RESYSTEMSTATUS,

	OPERATETYPE_REMAINANDSECOND,//������
	OPERATETYPE_REMAINANDSECONDLIST,
	OPERATETYPE_GETMAINANDSECOND,//��ȡ������

	OPERATETYPE_RENETCONFIG,//��������
	OPERATETYPE_STATUSTIME,//״̬��ʱ��

	OPERATETYPE_GETSPLITWALL,//��ȡƴ��ǽ
	OPERATETYPE_REGETSPLITWALL,

	OPERATETYPE_GETSPLITWINDOW,//ƴ�Ӵ���
	OPERATETYPE_REGETSPLITWINDOW,

	OPERATETYPE_CLEARSPLITVIEW,
	OPERATETYPE_SPLITSCENE,//��ȡƴ�ӳ���
	OPERATETYPE_RESPLITSCENE,


	OPERATETYPE_OPENTAKEOVERSCENE,//���ýӹܳ���
	OPERATETYPE_OPENSPLITSCENE,//����ƴ�ӳ���
	OPERATETYPE_OPENSPLITSCENEONE,//��������һ��
	//////////////////////////////////////////////////////////////////////////
	//�����������˵������ڱ��������ui����һ�£�
	OPERATETYPE_THEMEWIN7=200,
	OPERATETYPE_THEMEBLUE,
	OPERATETYPE_THEMEBLACK,
	OPERATETYPE_THEMESLIVER,
	OPERATETYPE_THEMEAQUE,

	OPERATETYPE_LANGUAGEZN,
	OPERATETYPE_LANGUAGETW,
	OPERATETYPE_LANGUAGEEN,

	OPERATETYPE_SCALE200,
	OPERATETYPE_SCALE175,
	OPERATETYPE_SCALE150,
	OPERATETYPE_SCALE125,
	OPERATETYPE_SCALE100,
	OPERATETYPE_SCALE75,
	OPERATETYPE_SCALE50,

	OPERATETYPE_BG,
	OPERATETYPE_SEAT,
	//////////////////////////////////////////////////////////////////////////
	OPERATETYPE_ALIGNLEFT,
	OPERATETYPE_ALIGNHORIZON,
	OPERATETYPE_ALIGNRIGHT,
	OPERATETYPE_ALIGNUP,
	OPERATETYPE_ALIGNDOWN,
	OPERATETYPE_ALIGNVERTICAL,
	OPERATETYPE_ALIGNSAME,

	OPERATETYPE_ALIGNHSAME,
	OPERATETYPE_ALIGNVSAME,
	OPERATETYPE_ALIGNWIDTH,
	OPERATETYPE_ALIGNHEIGHT,

	OPERATETYPE_DEVICENET,
	OPERATETYPE_MATRIXARRAY,

	OPERATETYPE_ADDSPLIT,
	OPERATETYPE_SPLITSCALE,

	OPERATETYPE_CLEARSIGNAL,

	OPERATETYPE_MENUUP,
	OPERATETYPE_MENUDOWN,
	OPERATETYPE_MENUTOP,
	OPERATETYPE_MENUBOTTOM,

	OPERATETYPE_LIMIT,
	OPERATETYPE_DELTOP,
	OPERATETYPE_DELBOTTOM,


	OPERATETYPE_ADDDEFAULT,
	OPERATETYPE_FULLSCREEN,

	OPERATETYPE_QUICKTOP,

	OPERATETYPE_SAVESPLITSCENE,

	OPERATETYPE_NULL
};

enum CMDUITYPE
{
	CMDUITYPE_OPENNET=1,
	CMDUITYPE_CLOSENET,
	CMDUITYPE_LOGIN,//��½
	CMDUITYPE_LOGINOUT,//ע��
	CMDUITYPE_USERMANAGE,//�û�����
	CMDUITYPE_POWER,//Ȩ�޹���
	CMDUITYPE_INPUTCOUNT,//�������
	CMDUITYPE_OUTPUTCOUNTH,//ˮƽ�������
	CMDUITYPE_OUTPUTCOUNTV,//��ֱ�������
	CMDUITYPE_DEVICEIP,//�豸IP
	CMDUITYPE_DEVICEPORT,//�豸Port
	CMDUITYPE_DELETEALLSIGNAL,//ɾ�������ź�
	CMDUITYPE_OSDIMAGE,//osd��ͼ
	CMDUITYPE_CONTROL,//�п�
	CMDUITYPE_SAVESCENE,//�ӹ�Ԥ��

	CMDUITYPE_SAVESEAT,//������ϯ
	CMDUITYPE_SENDSEAT,//����
	CMDUITYPE_CLEARSEAT,//���
	CMDUITYPE_LOG,//��־
	CMDUITYPE_UPDATE,//����
	CMDUITYPE_FOLDER,//�ļ���

	CMDUITYPE_ADDMODEL=150,//�������ģʽ //���ܱ�
	
	CMDUITYPE_LIMITNMODEL,
	CMDUITYPE_LIMIT,
	CMDUITYPE_DELTOP,
	CMDUITYPE_DELBOTTOM,

	CMDUITYPE_ADDDEFAULT,
	CMDUITYPE_FULLSCREEN,

	CMDUITYPE_QUICKTOP,
	CMDUITYPE_SAVESPLITSCENE,

	//////////////////////////////////////////////////////////////////////////
	//�������������һ��
	CMDUITYPE_THEMEWIN7=200,
	CMDUITYPE_THEMEBLUE,
	CMDUITYPE_THEMEBLACK,
	CMDUITYPE_THEMESLIVER,
	CMDUITYPE_THEMEAQUE,

	CMDUITYPE_LANGUAGEZN,
	CMDUITYPE_LANGUAGETW,
	CMDUITYPE_LANGUAGEEN,

	CMDUITYPE_SCALE200,
	CMDUITYPE_SCALE175,
	CMDUITYPE_SCALE150,
	CMDUITYPE_SCALE125,
	CMDUITYPE_SCALE100,
	CMDUITYPE_SCALE75,
	CMDUITYPE_SCALE50,
	//////////////////////////////////////////////////////////////////////////
	CMDUITYPE_SEAT,
	CMDUITYPE_ALIEN,
	//////////////////////////////////////////////////////////////////////////
	CMDUITYPE_ALIGNLEFT,
	CMDUITYPE_ALIGNHORIZON,
	CMDUITYPE_ALIGNRIGHT,
	CMDUITYPE_ALIGNUP,
	CMDUITYPE_ALIGNDOWN,
	CMDUITYPE_ALIGNVERTICAL,
	CMDUITYPE_ALIGNSAME,
	CMDUITYPE_ALIGNHSAME,
	CMDUITYPE_ALIGNVSAME,
	CMDUITYPE_ALIGNWIDTH,
	CMDUITYPE_ALIGNHEIGHT,
	//////////////////////////////////////////////////////////////////////////
	CMDUITYPE_MATRIXARRAY,

	CMDUITYPE_STATUSNET,

	CMDUITYPE_ADDSPLIT,
	CMDUITYPE_SPLITSCALE,

	CMDUITYPE_CLEARSIGNAL,

	CMDUITYPE_NULL
};

//�û�Ȩ��
enum USERPOWER
{
	USERPOWER_ADMIN=0,
	USERPOWER_NORMAL=1,

	USERPOWER_NULL=-1
};

//�û��������
enum USEROPERATE
{
	USEROPERATE_ADD,
	USEROPERATE_DEL,
	USEROPERATE_ALTER,

	USEROPERATE_NULL
};

//��ͷ
typedef enum
{
	PACKETHEAD_FULL,
	PACKETHEAD_PART,

	PACKETHEAD_NULL
}PACKERHEAD;

//Э������
typedef enum
{
	PROTOCOLTYPE_USERLIST,//�û��б�(���ڲ�ȫ)
	PROTOCOLTYPE_LOGIN,//��¼
	PROTOCOLTYPE_LOGINOUT,//ע��
	PACKERHEAD_HEART,//����
	PROTOCOLTYPE_OBTAINPOWER,//��ȡ�û�Ȩ��
	PROTOCOLTYPE_OBTAINUSERLIST,//��ȡ�û��б�
	PROTOCOLTYPE_OBTAINSTORE,//��ȡ�ղ��б�
	PROTOCOLTYPE_DELSTORELIST,//ɾ���ղ�
	PROTOCOLTYPE_ADDSTORELIST,
	PROTOCOLTYPE_GETALLNODE,//��ȡȫ���ڵ�
	PROTOCOLTYPE_GETDEVICEINFO,//��ȡ�豸��Ϣ
	PROTOCOLTYPE_GETNODE,//��ȡ���ӽڵ�״̬��ͨ���ţ�
	PROTOCOLTYPE_GETNODEINFO,//��ȡ�ڵ㲿����Ϣ
	PROTOCOLTYPE_GETNODEDETAILINFO,//��ȡ�ڵ���ϸ��Ϣ
	PROTOCOLTYPE_GETNODEALLDETAILINFO,//��ȡ���нڵ���ϸ��Ϣ
	PROTOCOLTYPE_GETLOGINUSER,//��ȡ��¼�û�
	PROTOCOLTYPE_GETLOGINUSERSTATUS,//��ȡ��¼�û�״̬
	PROTOCOLTYPE_NODELOGIN,//�ڵ��¼
	PROTOCOLTYPE_NODELOGOUT,//�ڵ��˳�
	PROTOCOLTYPE_TAKEOVER,//�ӹ�
	PROTOCOLTYPE_TAKEOVERCANCEL,//ȡ���ӹ�
	PROTOCOLTYPE_PREVIEW,//Ԥ��
	PROTOCOLTYPE_GETNODESTATUS,//��ѯ�ڵ�״̬
	PROTOCOLTYPE_ALTERNODENAME,//���Ľڵ�����
	PROTOCOLTYPE_ALTERAUDIOMODEL,//������Ƶģʽ
	PROTOCOLTYPE_ALTERAUDIOSRC,//������ƵԴ
	PROTOCOLTYPE_ALTERHIDMODEL,
	PROTOCOLTYPE_ALTERSCREENMODEL,//����ģʽ
	PROTOCOLTYPE_ALTERRESOLUATIONINDEX,//��������ֱ�����Ϣ
	PROTOCOLTYPE_ALTEROUTMODEL,//�������ģʽ
	PROTOCOLTYPE_MATRIXSTATUS,//��ȡ�����л�״̬
	PROTOCOLTYPE_MATRIX,//�����л�
	PROTOCOLTYPE_OSDIMAGE,//����OSD��ͼ
	PROTOCOLTYPE_ALTERBINDCFG,
	PROTOCOLTYPE_ALTERBINDNODEID,
	PROTOCOLTYPE_ALTERHOTKEY,//�ȼ�

	PROTOCOLTYPE_HIDEOSDIMAGE,//����OSD��ͼ
	PROTOCOLTYPE_READNODEGROUP,//��ȡ�ڵ���
	PROTOCOLTYPE_NODEGROUPINFO,//�ڵ���ϸ��Ϣ
	PROTOCOLTYPE_SYSTEMSTATUS,//��ȡ�豸״̬
	PROTOCOLTYPE_NODEBLINK,//�ڵ����˸

	PROTOCOLTYPE_MAINANDSECOND,//���������
	PROTOCOLTYPE_QUERYMAINANDSECOND,//��ѯ
	PROTOCOLTYPE_MAINANDSECONDLIST,//�������б�
	PROTOCOLTYPE_DELGROUPMAINSECOND,//ɾ��������
	PROTOCOLTYPE_UPDATAMASTERNAME,//��������������
	PROTOCOLTYPE_UPDATAMASTERSEATARRAGE,//��������ϯ

	PROTOCOLTYPE_NETCONFIG,//��ѯ��������
	PROTOCOLTYPE_LIGHTCONTROL,//�ƿ���
	PROTOCOLTYPE_LOG,//��־

	PROTOCOLTYPE_RTC,//RTCʱ��
	PROTOCOLTYPE_NOTIFY,//֪ͨ����

	PROTOCOLTYPE_ROOTFOLDER,//��ȡ��Ŀ¼
	PROTOCOLTYPE_SUBFOLDER,

	PROTOCOLTYPE_OBTIANSPLIT,//��ȡƴ��ǽ
	PROTOCOLTYPE_OBTIANSPLITWINDOW,
	PROTOCOLTYPE_SPLITSCENE,

	PROTOCOLTYPE_NULL

}PROTOCOLTYPE;

//�ڵ����ͣ����룬����������ղ��б�
typedef enum
{
	NODETYPE_IN,
	NODETYPE_OUT,

	NODETYPE_NULL
	
}NODETYPE;

//�ڵ����ͣ����룬��������ڹ���
typedef enum 
{
	TERM_IN=0,
	TERM_IN_GROUP,
	TERM_OUT,
	TERM_OUT_GROUP,

	TERM_ALL,
	TERM_NULL

}TERMTYPE;

//������οؼ��������
typedef enum
{
	ITEMDATA_USER,
	ITEMDATA_USERGROUP,

	ITEMDATA_NODEIN,
	ITEMDATA_NODEOUT,
	ITEMDATA_NODE,
	ITEMDATA_MATRIXNODE,
	ITEMDATA_MATRIXNODEIN,

	ITEMDATA_NODEGROUPIN,
	ITEMDATA_NODEGROUPOUT,

	ITEMDATA_NODEGROUPIN_M,
	ITEMDATA_NODEGROUPIN_G,


	ITEMDATA_SPLITNODEIN,
	ITEMDATA_SPLITNODE,


	ITEMDATA_NULL
}ITEMDATA;

//����ڵ�״̬
typedef enum 
{
	TERM_IN_NONE=0,
	TERM_IN_BE_CTRL_SHARE,
	TERM_IN_BE_CTRL_EXCLUSIVE,
}TERM_IN_STA;

//����ڵ�״̬
typedef enum 
{
	TERM_OUT_NONE=0,//unlogin
	TERM_OUT_LOG,
	TERM_OUT_CTRL,
	TERM_OUT_VIEW,
	TERM_OUT_GCTRL,
}TERM_OUT_STA;

//��ϯ������
typedef enum
{
	SEATARRAGE_GROUP,
	SEATARRAGE_SEAT,

}SEATARRAGE;

typedef enum
{
	SCENETYPE_SCENE=1,
	SCENETYPE_GROUP,
	SCENETYPE_SPLIT,
	SCENETYPE_SPLITGROUP,
	SCENETYPE_SPLITWALL,


	SCENETYPE_NULL,

}SCENETYPE;

//�������ͣ��ֶ���"update mark"��
typedef enum
{
	UPDATAMAKE_GROUP=1,
	UPDATAMAKE_GROUP_DELFROMGROUP,

	UPDATAMAKE_MASTER,
	UPDATAMAKE_CONTROL,

	//������ϯ
	UPDATAMAKE_GROUPNAME,
	UPDATAMAKE_MASTERNAME,
	UPDATAMAKE_GROUPARRAGE,
	UPDATAMAKE_MASTERARRAGE,
	UPDATAMAKE_GROUPMASTER,
	UPDATAMAKE_DELSEAT,
	UPDATAMAKE_DELNODEFROMGROUP,


	UPDATAMAKE_NULL

}UPDATAMAKE;

//�ڵ�����ӷ�ʽ
typedef enum
{
	CREATEMODE_ARRAGE=1,
	CREATEMODE_DRAG,
}CREATEMODE;


typedef enum
{
	ALIGN_LEFT=1,
	ALIGN_HORIZON,
	ALIGN_RIGHT,
	ALIGN_TOP,
	ALIGN_VERTICAL,
	ALIGN_BOTTOM,

	ALIGN_NULL
}ALIGN;

//�ڵ��飨���ڻ�ȡ��������
typedef enum
{
	NODEGROUP_ONLINE,
	NODEGROUP_OUTLINE,
	NODEGROUP_IN,
	NODEGROUP_OUT,
	NODEGROUP_ALL,
	NODEGROUP_MAINSEC,
	NODEGROUP_GROUP,
	NODEGROUP_NULL

}NODEGROUP;
//�û���¼��������ڻ�ȡ�û���¼�����
typedef enum
{
	USERLOGIN_NODE,
	USERLOGIN_NET,
	USERLOGIN_ALL,

	USERLOGIN_NULL
}USERLOGIN;

//�ղ���������
typedef enum 
{
	STORE_IN,
	STORE_OUT,
	STORE_NODE,
	STORE_GROUP,

	STORE_NULL,
}STORENODE;

//�ļ�������
typedef enum
{
	FOLDERTYPE_ROOT,//���ļ���
	FOLDERTYPE_CHILD,//���ļ���
	FOLDERTYPE_NODE,//�ڵ�
	FOLDERTYPE_IN,
	FOLDERTYPE_OUT,

	FOLDERTYPE_NULL
}FOLDERTYPE;



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define RECTF	Gdiplus::RectF
#define POINTF  Gdiplus::PointF
#define SIZEF   Gdiplus::SizeF

//��ͼ�༯��
class XBaseViewManage;
typedef std::map<int,XBaseViewManage*> MAP_BASEVIEW;

//�û�Ȩ��
class XPower;
typedef std::map<CString,XPower*> MAP_POWER;
typedef std::vector<int> VEC_USERALL;
typedef std::vector<int> VEC_USERIDALL;

//#define MAP_TEMP unordered_map<int,int>

//����Ȩ��
typedef std::vector<int> VEC_PRIVILEGE;

//Ȩ�ޣ�32λ��
class XPowerListInfo;
typedef std::map<int,XPowerListInfo*> MAP_USERPOWER;

//ѡ���û�Ȩ���б���
class XPowerSelectInfo;
typedef std::map<int,XPowerSelectInfo*> MAP_SELECT;

typedef std::vector<CString> VEC_SUBSELECT;


//�����û��б�
class XSubUserInfo;
typedef std::map<CString,XSubUserInfo*> MAP_SUBUSER;

//�û��ղ��б�
class XStoreListInfo;
typedef std::map<int,XStoreListInfo*> MAP_STORE;

//�ְ�����
class XData;
typedef std::map<int,XData*> MAP_DATA;

//ͨ������״̬
typedef std::map<int,BOOL> MAP_CHANNEL;

//�ڵ㼯��
class XNode;
typedef std::map<int,XNode*> MAP_NODE;
typedef std::map<int,HTREEITEM> MAP_NODEMAINSEC;

typedef std::vector<int> VEC_NODELIST;
typedef std::vector<int> VEC_NODEID;

class XPrivilege;
typedef std::map<int,XPrivilege*> MAP_CTRLPRIVILEGE;



class XNodeAll;
typedef std::map<int,XNodeAll*> MAP_NODEALL;
//�ڵ�����
typedef std::vector<int> VEC_CONNECT;

//��ҳ��ѯ����
typedef std::vector<int> VEC_PART;

//�û���¼״̬
class XUserLogStatus;
typedef std::map<int,XUserLogStatus*> MAP_USERLOGINSTATUS;

//����ڵ�ֱ�����Ϣ
class XOutResoluation;
typedef std::map<int,XOutResoluation*> MAP_RESULATIONINFO;

//�����л���ϵ
typedef std::map<int,int> MAP_MATRIX;

//��ͼ
typedef std::map<int,CString> MAP_IMAGE;

//����ϯ
typedef std::vector<int> VEC_SUBSEAT;

//��ϯ
class XSeat;
typedef std::vector<XSeat*> VEC_SEAT;
//#define MAP_SEAT std::map<int,XSeat*>

//����
class XScreen;
typedef std::vector<XScreen*> VEC_SCREEN;


//��ϯ�����������
typedef std::map<int,int> MAP_INDEX;
typedef std::vector<int> VEC_INDEX;
typedef std::vector<int> VEC_ROW;
typedef std::vector<int> VEC_COLUMN;

//�ڵ���
class XNodeGroupInfo;
typedef std::map<CString,XNodeGroupInfo*> MAP_NODEGROUP;
typedef std::map<CString,XNodeGroupInfo*> MAP_GROUPMAINSEC;

//���Ա����
typedef std::vector<std::vector<int>> VEC_ARRAGE;
typedef std::vector<CString> VEC_STRING;
typedef std::vector<int> VEC_DEL;
typedef std::vector<int> VEC_DRAG;
typedef std::map<int,int> MAP_DRAG;

//��ϯҳ��
class XPage;
typedef std::map<int,XPage*> MAP_PAGE;

class XMultiVideoWindowFrame;
typedef std::map<int,XMultiVideoWindowFrame*> MAP_TEMPFRAME;

class XBaseWnd;
typedef std::map<int,XBaseWnd*> MAP_ALIGN;
typedef std::vector<XBaseWnd*> VEC_DRAWSEAT;

class XScreenInfo;
typedef std::vector<XScreenInfo*> VEC_SCREENINFO;

class XChannel;
typedef std::vector<XChannel*> VEC_CHANNEL;

typedef std::map<CString,int> MAP_COLUMN;
typedef std::map<CString,Color> MAP_KEYCOLOR;

//��������
class XNetConfig;
typedef std::vector<XNetConfig*> VEC_NETCONFIG;

//�ӹ��������
class XTakeOver;
typedef std::map<int,XTakeOver*> MAP_TAKEOVER;

//����������
class XSceneInfo;
typedef std::map<CString,XSceneInfo*> MAP_SCENE;
typedef std::map<CString,HTREEITEM> MAP_HTREEITEM;
//������
class XSceneGroupInfo;
typedef std::map<CString,XSceneGroupInfo*> MAP_SCENEGROUP;

//������Ļ
class XMatrixScreen;
typedef std::vector<XMatrixScreen*> VEC_MATRIXSCREEN;

//��־����
class XLogInfo;
typedef std::vector<XLogInfo*> VEC_LOG;

//���̼�ֵ
typedef std::map<CString,int> MAP_KEYVALUE;

typedef std::vector<int> VEC_HOTKEY;

class XKeyValue;
typedef std::map<int,XKeyValue*> MAP_HOTKEY;

//ƴ����Ļ����
class XSplitScreen;
typedef std::vector<XSplitScreen*> VEC_SPLITSCREEN;

//�����ź�
class XSignal;
typedef std::vector<XSignal*> VEC_SIGNAL;

//ƴ���ź�
class XSplitSignal;
typedef std::vector<XSplitSignal*> VEC_SPLITSIGNAL;

//ƴ�ӳ���
class XSplitScene;
typedef std::map<CString,XSplitScene*> MAP_SPLITSCENE;

//class XSplitSceneGroup;
typedef std::map<CString,HTREEITEM> MAP_SPLITSCENEGROUP;

//�ļ���
//��Ŀ¼
class XFolderInfo;
typedef std::map<int,XFolderInfo*> MAP_ROOTFOLDER;

typedef std::map<int,HTREEITEM> MAP_USERLIST;
typedef std::map<int,HTREEITEM> MAP_TERMLIST;

class XSubFolder;
typedef std::map<int,XSubFolder*> MAP_SUBFOLDERLIST;

typedef std::map<int,XSubFolder*> MAP_SUBFOLDER;

typedef std::map<int,CString> MAP_TEMPSUBFOLDER;