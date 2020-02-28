#pragma once

//释放
#define RELEASE(X) if(NULL!=X){delete X;X=NULL;}

extern const CString APP_NAME;
extern const CString APP_VERSION;
extern const CString APP_REGISTRYKEY;

extern const CString APP_ININAME;
extern const CString APP_DATAFILENAME;
extern const CString APP_FONT;
extern const CString FILTER_PHOTO;
extern const Color g_Color[40];


//消息事件
extern const UINT MSG_UDP;
extern const UINT MSG_ADDDOCUMENT;
extern const UINT MSG_BTN_LCLICK;
extern const UINT MSG_TCP;


constexpr auto DRAWDISTANCE_X                              =50;
constexpr auto DRAWDISTANCE_Y                              =50;
//每行节点个数
constexpr auto NODECOUNT_H                                 =12;
//节点宽高
constexpr auto NODE_WIDTH                                  =100;
constexpr auto NODE_HEIGHT                                 =80;
//节点横向距离
constexpr auto DISTANCE                                    =10;
constexpr auto DISTANCE_V                                  =20;
//节点字体高度
constexpr auto TEXT_HEIGHT                                 =20;
//运维图片宽高
constexpr auto PIC_WIDTH                                   =1350;
constexpr auto PIC_HEIGHT                                  =800;
//坐席编排
constexpr auto PAGE_WIDTH                                  =800;
constexpr auto PAGE_HEIGHT                                 =810;
constexpr auto SCREEN_H                                    =160;
constexpr auto SCREEN_V                                    =90;
//通道缩略图宽高
constexpr auto CHANNEL_W                                   =25;
constexpr auto CHANNEL_H                                   =14;

//定时器										    
constexpr auto TIMERID_HEART                               =1;
constexpr auto TIMESPACE_HEART                             =2000;

constexpr auto TIMERID_SYSTEM                              =2;
constexpr auto TIMERSPACE_SYSTEM                           =3000;

constexpr auto TIMERID_CLICK                               =3;
constexpr auto TIMERSPACE_CLICK                            =1000;



//权限返回类型
constexpr auto POWER_REDATA_LIST                           =_T("LIST");
constexpr auto POWER_REDATA_QUERY                          =_T("QUERY");
constexpr auto POWER_REDATA_ADD                            =_T("ADD");
constexpr auto POWER_REDATA_DEL                            =_T("DEL");
constexpr auto POWER_REDATA_UPDATE                         =_T("UPDATE");

constexpr auto STORE_REDATA_QUERY                          =_T("QUERY");
constexpr auto STORE_REDATA_ADD                            =_T("ADD");
constexpr auto STORE_REDATA_DEL                            =_T("DEL");

//自定义Json 识别字段
//constexpr auto BLINK_FLAG                                  =_T("BLINK");



//日志事件
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


//错误信息
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


//资源ID
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
	CHART_CLOUMN_NODE,//柱形图
	CHART_CLOUMN_USER,
	CHART_CLOUMN_GROUP,
	CHART_CLOUMN_SYSTEM,
	CHART_PROGRESS,//进度条
	CHART_PIE,//饼图
	CHART_PERCENTAGE,//百分比
	CHART_STRING,
	CHART_INSTRUMENT,

	CHART_NULL
}CHART;

typedef enum class string:char
{   //运维界面字体类型
	STRING_TITLE,//标题字体
	STRING_ITEM,
	STRING_INFO,
	STRING_INDEX,

	STRING_NULL
}STRING;

enum LANGUAGETYPE//语言类型
{
	LANGUAGETYPE_ZH_CN,
	LANGUAGETYPE_ZH_TW,
	LANGUAGETYPE_EN,

	LANGUAGETYPE_NULL
};

enum CURSORTYPE//鼠标类型
{
	CURSORTYPE_NORMAL,//普通
	CURSORTYPE_HAND,//手型
	CURSORTYPE_MOVE,//移动
	CURSORTYPE_NESW,//双箭头指向东北和西南
	CURSORTYPE_NS,//双箭头指向南北
	CURSORTYPE_NWSE,//双箭头指向西北和东南
	CURSORTYPE_WE,//双箭头指向东西
	CURSORTYPE_DRAW,//十字

	CURSORTYPE_SIZE,
	CURSORTYPE_NULL,
};

enum POSITIONTYPE//位置类型
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

enum XDATATYPE//控件类型
{
	XDATATYPE_ALL,

	XDATATYPE_LANGUAGENAME,//语言名称
	XDATATYPE_THEME,//主题
	XDATATYPE_SCALE,//显示比例
	XDATATYPE_SEATSCALE,//坐席比例
	XDATATYPE_DEVICEIP,//设备IP
	XDATATYPE_DEVICEPORT,//设备Port
	XDATATYPE_SECONDDEVICEIP,//设备IP
	XDATATYPE_SECONDDEVICEPORT,//设备Port

	XDATATYPE_LOGIN,
	XDATATYPE_LOGINOUT,

	XDATATYPE_SEATROW,//seat row
	XDATATYPE_SEATCOLUMN,

	XDATATYPE_NULL
};


enum OPERATETYPE//操作类型
{
	OPERATETYPE_RELOADINTERFACE=1,//重载界面
	OPERATETYPE_ABOUT,//关于

	OPERATETYPE_OPENNET,//打开网络
	OPERATETYPE_CLOSENET,//关闭网络
	OPERATETYPE_UPDATE,//升级
	OPERATETYPE_FOLDER,//文件夹
	OPERATETYPE_REROOTFOLDER,//返回文件夹

	OPERATETYPE_LOGIN,//登录
	OPERATETYPE_LOGINOUT,//注销

	OPERATETYPE_POWER,//权限
	OPERATETYPE_REPOWER,

	OPERATETYPE_RELOGIN,//登录
	OPERATETYPE_RELOGINOUT,

	OPERATETYPE_HEART,//心跳
	OPERATETYPE_REHEART,

	OPERATETYPE_REUSERLIST,//返回用户列表
	OPERATETYPE_RESTORELIST,//返回收藏列表

	OPERATETYPE_DEVICEINFO,//获取设备通道数
	OPERATETYPE_REDEVICEINFO,
	OPERATETYPE_ALLNODE,//获取全部节点列表

	OPERATETYPE_ADDSEAT,//添加坐席


	OPERATETYPE_GETNODECHANNEL,//获取节点连接状态
	OPERATETYPE_RENODECHANNEL,

	OPERATETYPE_RENODEINFO,//返回节点部分信息
	OPERATETYPE_RENODEDETAILINFO,//返回详细信息
	OPERATETYPE_RENODESTATUS,//返回节点状态

	OPERATETYPE_GETLOGINUSER,//获取登录用户个数
	OPERATETYPE_RELOGINUSER,
	OPERATETYPE_RELOGINUSERSTATUS,

	OPERATETYPE_RENODELOGIN,//节点登录
	OPERATETYPE_RENODELOGOUT,//退出

	OPERATETYPE_RETAKEOVER,//接管
	OPERATETYPE_RETAKEOVERCANCEL,//取消接管

	OPERATETYPE_PREVIEW,//预览

	OPERATETYPE_ALTERNODENAME,//更改节点名称

	OPERATETYPE_MENUOUTOFLOGOUT,//输出菜单

	OPERATETYPE_MATRIXSTATUS,//矩阵切换状态
	OPERATETYPE_REMATRIXSTATUS,
	OPERATETYPE_REMATRIX,//矩阵切换

	OPERATETYPE_OSDIMAGE,//osd底图
	OPERATETYPE_REOSDIMAGE,
	OPERATETYPE_REHIDEOSDIMAGE,//隐藏osd底图

	OPERATETYPE_CONTROL,//中控
	OPERATETYPE_SAVESCENE,//保存接管场景
	OPERATETYPE_INITSCENE,//初始化场景树
	OPERATETYPE_LOG,//日志
	OPERATETYPE_RELOG,
	OPERATETYPE_INITMATRIXARRAY,//初始化矩阵排列屏幕

	OPERATETYPE_SAVESEAT,//保存坐席
	OPERATETYPE_SENDSEAT,//发送
	OPERATETYPE_CLEARSEAT,//清空

	OPERATETYPE_INITAPPDATA,//初始化数据文件
	OPERATETYPE_GETAPPDATA,

	OPERATETYPE_READNODEGROUP,//读取全部节点组
	OPERATETYPE_READONLINENODEGROUP,//读取在线节点组
	OPERATETYPE_REREADNODEGROUP,
	OPERATETYPE_RENODEGROUPINFO,

	OPERATETYPE_REREFREASGGROUP,//更新组成员信息

	OPERATETYPE_SCREENARRAY,//坐席屏幕排列

	OPERATETYPE_NODECOLUMNDATA,//节点柱形图数据
	OPERATETYPE_CLEARCOLUMNDATA,//清理柱形图数据

	OPERATETYPE_SYSTEMSTATUS,//设备运行情况
	OPERATETYPE_RESYSTEMSTATUS,

	OPERATETYPE_REMAINANDSECOND,//主副屏
	OPERATETYPE_REMAINANDSECONDLIST,
	OPERATETYPE_GETMAINANDSECOND,//读取主副屏

	OPERATETYPE_RENETCONFIG,//网络配置
	OPERATETYPE_STATUSTIME,//状态栏时间

	OPERATETYPE_GETSPLITWALL,//获取拼接墙
	OPERATETYPE_REGETSPLITWALL,

	OPERATETYPE_GETSPLITWINDOW,//拼接窗口
	OPERATETYPE_REGETSPLITWINDOW,

	OPERATETYPE_CLEARSPLITVIEW,
	OPERATETYPE_SPLITSCENE,//获取拼接场景
	OPERATETYPE_RESPLITSCENE,


	OPERATETYPE_OPENTAKEOVERSCENE,//调用接管场景
	OPERATETYPE_OPENSPLITSCENE,//调用拼接场景
	OPERATETYPE_OPENSPLITSCENEONE,//调用其中一个
	//////////////////////////////////////////////////////////////////////////
	//工具栏下来菜单（现在必须与更改ui保持一致）
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
	CMDUITYPE_LOGIN,//登陆
	CMDUITYPE_LOGINOUT,//注销
	CMDUITYPE_USERMANAGE,//用户管理
	CMDUITYPE_POWER,//权限管理
	CMDUITYPE_INPUTCOUNT,//输入个数
	CMDUITYPE_OUTPUTCOUNTH,//水平输出个数
	CMDUITYPE_OUTPUTCOUNTV,//垂直输出个数
	CMDUITYPE_DEVICEIP,//设备IP
	CMDUITYPE_DEVICEPORT,//设备Port
	CMDUITYPE_DELETEALLSIGNAL,//删除所有信号
	CMDUITYPE_OSDIMAGE,//osd底图
	CMDUITYPE_CONTROL,//中控
	CMDUITYPE_SAVESCENE,//接管预案

	CMDUITYPE_SAVESEAT,//保存坐席
	CMDUITYPE_SENDSEAT,//发送
	CMDUITYPE_CLEARSEAT,//清空
	CMDUITYPE_LOG,//日志
	CMDUITYPE_UPDATE,//升级
	CMDUITYPE_FOLDER,//文件夹

	CMDUITYPE_ADDMODEL=150,//开窗添加模式 //不能变
	
	CMDUITYPE_LIMITNMODEL,
	CMDUITYPE_LIMIT,
	CMDUITYPE_DELTOP,
	CMDUITYPE_DELBOTTOM,

	CMDUITYPE_ADDDEFAULT,
	CMDUITYPE_FULLSCREEN,

	CMDUITYPE_QUICKTOP,
	CMDUITYPE_SAVESPLITSCENE,

	//////////////////////////////////////////////////////////////////////////
	//必须与操作保持一致
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

//用户权限
enum USERPOWER
{
	USERPOWER_ADMIN=0,
	USERPOWER_NORMAL=1,

	USERPOWER_NULL=-1
};

//用户管理操作
enum USEROPERATE
{
	USEROPERATE_ADD,
	USEROPERATE_DEL,
	USEROPERATE_ALTER,

	USEROPERATE_NULL
};

//包头
typedef enum
{
	PACKETHEAD_FULL,
	PACKETHEAD_PART,

	PACKETHEAD_NULL
}PACKERHEAD;

//协议类型
typedef enum
{
	PROTOCOLTYPE_USERLIST,//用户列表(用于补全)
	PROTOCOLTYPE_LOGIN,//登录
	PROTOCOLTYPE_LOGINOUT,//注销
	PACKERHEAD_HEART,//心跳
	PROTOCOLTYPE_OBTAINPOWER,//获取用户权限
	PROTOCOLTYPE_OBTAINUSERLIST,//获取用户列表
	PROTOCOLTYPE_OBTAINSTORE,//获取收藏列表
	PROTOCOLTYPE_DELSTORELIST,//删除收藏
	PROTOCOLTYPE_ADDSTORELIST,
	PROTOCOLTYPE_GETALLNODE,//获取全部节点
	PROTOCOLTYPE_GETDEVICEINFO,//获取设备信息
	PROTOCOLTYPE_GETNODE,//获取连接节点状态（通道号）
	PROTOCOLTYPE_GETNODEINFO,//获取节点部分信息
	PROTOCOLTYPE_GETNODEDETAILINFO,//获取节点详细信息
	PROTOCOLTYPE_GETNODEALLDETAILINFO,//获取所有节点详细信息
	PROTOCOLTYPE_GETLOGINUSER,//获取登录用户
	PROTOCOLTYPE_GETLOGINUSERSTATUS,//获取登录用户状态
	PROTOCOLTYPE_NODELOGIN,//节点登录
	PROTOCOLTYPE_NODELOGOUT,//节点退出
	PROTOCOLTYPE_TAKEOVER,//接管
	PROTOCOLTYPE_TAKEOVERCANCEL,//取消接管
	PROTOCOLTYPE_PREVIEW,//预览
	PROTOCOLTYPE_GETNODESTATUS,//查询节点状态
	PROTOCOLTYPE_ALTERNODENAME,//更改节点名称
	PROTOCOLTYPE_ALTERAUDIOMODEL,//设置音频模式
	PROTOCOLTYPE_ALTERAUDIOSRC,//更改音频源
	PROTOCOLTYPE_ALTERHIDMODEL,
	PROTOCOLTYPE_ALTERSCREENMODEL,//分屏模式
	PROTOCOLTYPE_ALTERRESOLUATIONINDEX,//设置输出分辨率信息
	PROTOCOLTYPE_ALTEROUTMODEL,//设置输出模式
	PROTOCOLTYPE_MATRIXSTATUS,//获取矩阵切换状态
	PROTOCOLTYPE_MATRIX,//矩阵切换
	PROTOCOLTYPE_OSDIMAGE,//发送OSD底图
	PROTOCOLTYPE_ALTERBINDCFG,
	PROTOCOLTYPE_ALTERBINDNODEID,
	PROTOCOLTYPE_ALTERHOTKEY,//热键

	PROTOCOLTYPE_HIDEOSDIMAGE,//隐藏OSD底图
	PROTOCOLTYPE_READNODEGROUP,//读取节点组
	PROTOCOLTYPE_NODEGROUPINFO,//节点详细信息
	PROTOCOLTYPE_SYSTEMSTATUS,//获取设备状态
	PROTOCOLTYPE_NODEBLINK,//节点灯闪烁

	PROTOCOLTYPE_MAINANDSECOND,//主副屏添加
	PROTOCOLTYPE_QUERYMAINANDSECOND,//查询
	PROTOCOLTYPE_MAINANDSECONDLIST,//主副屏列表
	PROTOCOLTYPE_DELGROUPMAINSECOND,//删除主副屏
	PROTOCOLTYPE_UPDATAMASTERNAME,//更新主副屏名称
	PROTOCOLTYPE_UPDATAMASTERSEATARRAGE,//主副屏坐席

	PROTOCOLTYPE_NETCONFIG,//查询网络配置
	PROTOCOLTYPE_LIGHTCONTROL,//灯控制
	PROTOCOLTYPE_LOG,//日志

	PROTOCOLTYPE_RTC,//RTC时间
	PROTOCOLTYPE_NOTIFY,//通知监听

	PROTOCOLTYPE_ROOTFOLDER,//获取根目录
	PROTOCOLTYPE_SUBFOLDER,

	PROTOCOLTYPE_OBTIANSPLIT,//获取拼接墙
	PROTOCOLTYPE_OBTIANSPLITWINDOW,
	PROTOCOLTYPE_SPLITSCENE,

	PROTOCOLTYPE_NULL

}PROTOCOLTYPE;

//节点类型（输入，输出）用于收藏列表
typedef enum
{
	NODETYPE_IN,
	NODETYPE_OUT,

	NODETYPE_NULL
	
}NODETYPE;

//节点类型（输入，输出）用于管理
typedef enum 
{
	TERM_IN=0,
	TERM_IN_GROUP,
	TERM_OUT,
	TERM_OUT_GROUP,

	TERM_ALL,
	TERM_NULL

}TERMTYPE;

//左侧树形控件项绑定数据
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

//输入节点状态
typedef enum 
{
	TERM_IN_NONE=0,
	TERM_IN_BE_CTRL_SHARE,
	TERM_IN_BE_CTRL_EXCLUSIVE,
}TERM_IN_STA;

//输出节点状态
typedef enum 
{
	TERM_OUT_NONE=0,//unlogin
	TERM_OUT_LOG,
	TERM_OUT_CTRL,
	TERM_OUT_VIEW,
	TERM_OUT_GCTRL,
}TERM_OUT_STA;

//坐席树类型
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

//更新类型（字段名"update mark"）
typedef enum
{
	UPDATAMAKE_GROUP=1,
	UPDATAMAKE_GROUP_DELFROMGROUP,

	UPDATAMAKE_MASTER,
	UPDATAMAKE_CONTROL,

	//更新坐席
	UPDATAMAKE_GROUPNAME,
	UPDATAMAKE_MASTERNAME,
	UPDATAMAKE_GROUPARRAGE,
	UPDATAMAKE_MASTERARRAGE,
	UPDATAMAKE_GROUPMASTER,
	UPDATAMAKE_DELSEAT,
	UPDATAMAKE_DELNODEFROMGROUP,


	UPDATAMAKE_NULL

}UPDATAMAKE;

//节点组添加方式
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

//节点组（用于获取组数量）
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
//用户登录情况（用于获取用户登录情况）
typedef enum
{
	USERLOGIN_NODE,
	USERLOGIN_NET,
	USERLOGIN_ALL,

	USERLOGIN_NULL
}USERLOGIN;

//收藏树绑定数据
typedef enum 
{
	STORE_IN,
	STORE_OUT,
	STORE_NODE,
	STORE_GROUP,

	STORE_NULL,
}STORENODE;

//文件夹数据
typedef enum
{
	FOLDERTYPE_ROOT,//根文件夹
	FOLDERTYPE_CHILD,//子文件夹
	FOLDERTYPE_NODE,//节点
	FOLDERTYPE_IN,
	FOLDERTYPE_OUT,

	FOLDERTYPE_NULL
}FOLDERTYPE;



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define RECTF	Gdiplus::RectF
#define POINTF  Gdiplus::PointF
#define SIZEF   Gdiplus::SizeF

//视图类集合
class XBaseViewManage;
typedef std::map<int,XBaseViewManage*> MAP_BASEVIEW;

//用户权限
class XPower;
typedef std::map<CString,XPower*> MAP_POWER;
typedef std::vector<int> VEC_USERALL;
typedef std::vector<int> VEC_USERIDALL;

//#define MAP_TEMP unordered_map<int,int>

//控制权限
typedef std::vector<int> VEC_PRIVILEGE;

//权限（32位）
class XPowerListInfo;
typedef std::map<int,XPowerListInfo*> MAP_USERPOWER;

//选中用户权限列表项
class XPowerSelectInfo;
typedef std::map<int,XPowerSelectInfo*> MAP_SELECT;

typedef std::vector<CString> VEC_SUBSELECT;


//创建用户列表
class XSubUserInfo;
typedef std::map<CString,XSubUserInfo*> MAP_SUBUSER;

//用户收藏列表
class XStoreListInfo;
typedef std::map<int,XStoreListInfo*> MAP_STORE;

//分包数据
class XData;
typedef std::map<int,XData*> MAP_DATA;

//通道连接状态
typedef std::map<int,BOOL> MAP_CHANNEL;

//节点集合
class XNode;
typedef std::map<int,XNode*> MAP_NODE;
typedef std::map<int,HTREEITEM> MAP_NODEMAINSEC;

typedef std::vector<int> VEC_NODELIST;
typedef std::vector<int> VEC_NODEID;

class XPrivilege;
typedef std::map<int,XPrivilege*> MAP_CTRLPRIVILEGE;



class XNodeAll;
typedef std::map<int,XNodeAll*> MAP_NODEALL;
//节点连接
typedef std::vector<int> VEC_CONNECT;

//分页查询集合
typedef std::vector<int> VEC_PART;

//用户登录状态
class XUserLogStatus;
typedef std::map<int,XUserLogStatus*> MAP_USERLOGINSTATUS;

//输出节点分辨率信息
class XOutResoluation;
typedef std::map<int,XOutResoluation*> MAP_RESULATIONINFO;

//矩阵切换关系
typedef std::map<int,int> MAP_MATRIX;

//底图
typedef std::map<int,CString> MAP_IMAGE;

//子坐席
typedef std::vector<int> VEC_SUBSEAT;

//坐席
class XSeat;
typedef std::vector<XSeat*> VEC_SEAT;
//#define MAP_SEAT std::map<int,XSeat*>

//编排
class XScreen;
typedef std::vector<XScreen*> VEC_SCREEN;


//坐席四周区域序号
typedef std::map<int,int> MAP_INDEX;
typedef std::vector<int> VEC_INDEX;
typedef std::vector<int> VEC_ROW;
typedef std::vector<int> VEC_COLUMN;

//节点组
class XNodeGroupInfo;
typedef std::map<CString,XNodeGroupInfo*> MAP_NODEGROUP;
typedef std::map<CString,XNodeGroupInfo*> MAP_GROUPMAINSEC;

//组成员编排
typedef std::vector<std::vector<int>> VEC_ARRAGE;
typedef std::vector<CString> VEC_STRING;
typedef std::vector<int> VEC_DEL;
typedef std::vector<int> VEC_DRAG;
typedef std::map<int,int> MAP_DRAG;

//坐席页面
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

//网络配置
class XNetConfig;
typedef std::vector<XNetConfig*> VEC_NETCONFIG;

//接管情况集合
class XTakeOver;
typedef std::map<int,XTakeOver*> MAP_TAKEOVER;

//场景树集合
class XSceneInfo;
typedef std::map<CString,XSceneInfo*> MAP_SCENE;
typedef std::map<CString,HTREEITEM> MAP_HTREEITEM;
//场景组
class XSceneGroupInfo;
typedef std::map<CString,XSceneGroupInfo*> MAP_SCENEGROUP;

//矩阵屏幕
class XMatrixScreen;
typedef std::vector<XMatrixScreen*> VEC_MATRIXSCREEN;

//日志集合
class XLogInfo;
typedef std::vector<XLogInfo*> VEC_LOG;

//键盘键值
typedef std::map<CString,int> MAP_KEYVALUE;

typedef std::vector<int> VEC_HOTKEY;

class XKeyValue;
typedef std::map<int,XKeyValue*> MAP_HOTKEY;

//拼接屏幕集合
class XSplitScreen;
typedef std::vector<XSplitScreen*> VEC_SPLITSCREEN;

//整个信号
class XSignal;
typedef std::vector<XSignal*> VEC_SIGNAL;

//拼接信号
class XSplitSignal;
typedef std::vector<XSplitSignal*> VEC_SPLITSIGNAL;

//拼接场景
class XSplitScene;
typedef std::map<CString,XSplitScene*> MAP_SPLITSCENE;

//class XSplitSceneGroup;
typedef std::map<CString,HTREEITEM> MAP_SPLITSCENEGROUP;

//文件夹
//根目录
class XFolderInfo;
typedef std::map<int,XFolderInfo*> MAP_ROOTFOLDER;

typedef std::map<int,HTREEITEM> MAP_USERLIST;
typedef std::map<int,HTREEITEM> MAP_TERMLIST;

class XSubFolder;
typedef std::map<int,XSubFolder*> MAP_SUBFOLDERLIST;

typedef std::map<int,XSubFolder*> MAP_SUBFOLDER;

typedef std::map<int,CString> MAP_TEMPSUBFOLDER;