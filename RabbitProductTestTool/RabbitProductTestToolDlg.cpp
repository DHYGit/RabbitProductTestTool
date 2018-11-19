
// RabbitProductTestToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "CameraPlayerDlg.h"
#include "RabbitProductTestTool.h"
#include "RabbitProductTestToolDlg.h"
#include "UpgradeDlg.h"
#include "afxdialogex.h"
#include "ProThreadFun.h"
#include "ProTestSHName.h"
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRabbitProductTestToolDlg 对话框



CRabbitProductTestToolDlg::CRabbitProductTestToolDlg(CWnd* pParent /*=NULL*/)

	: CDialogEx(CRabbitProductTestToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRabbitProductTestToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_OpenConsole, m_OpenConsole);
	DDX_Control(pDX, IDC_RICHEDIT2_Log, m_RichEditCtrl_Log);
	DDX_Control(pDX, IDC_CHECK_Version, m_CheckVersion);
}

BEGIN_MESSAGE_MAP(CRabbitProductTestToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Connect, &CRabbitProductTestToolDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_Excute, &CRabbitProductTestToolDlg::OnBnClickedButtonExcute)
	ON_BN_CLICKED(IDC_BUTTON_LEC_Warm, &CRabbitProductTestToolDlg::OnBnClickedButtonLecWarm)
	ON_BN_CLICKED(IDC_BUTTON_LED_Cool, &CRabbitProductTestToolDlg::OnBnClickedButtonLedCool)
	ON_BN_CLICKED(IDC_BUTTON_LED_OFF, &CRabbitProductTestToolDlg::OnBnClickedButtonLedOff)
	ON_BN_CLICKED(IDC_BUTTON_PlayAudio, &CRabbitProductTestToolDlg::OnBnClickedButtonPlayaudio)
	ON_BN_CLICKED(IDC_BUTTON_Upgrade, &CRabbitProductTestToolDlg::OnBnClickedButtonUpgrade)
	ON_BN_CLICKED(IDC_CHECK_OpenConsole, &CRabbitProductTestToolDlg::OnBnClickedCheckOpenconsole)
	ON_BN_CLICKED(IDC_BUTTON_LED_Red, &CRabbitProductTestToolDlg::OnBnClickedButtonLedRed)
	ON_BN_CLICKED(IDC_BUTTON_LED_Green, &CRabbitProductTestToolDlg::OnBnClickedButtonLedGreen)
	ON_BN_CLICKED(IDC_BUTTON_LED_Blue, &CRabbitProductTestToolDlg::OnBnClickedButtonLedBlue)
	ON_BN_CLICKED(IDC_BUTTON_LeftChannel, &CRabbitProductTestToolDlg::OnBnClickedButtonLeftchannel)
	ON_BN_CLICKED(IDC_BUTTON_RightChannel, &CRabbitProductTestToolDlg::OnBnClickedButtonRightchannel)
	ON_BN_CLICKED(IDC_BUTTON_LED_ALL, &CRabbitProductTestToolDlg::OnBnClickedButtonLedAll)
	ON_BN_CLICKED(IDC_BUTTON_Sound_OFF, &CRabbitProductTestToolDlg::OnBnClickedButtonSoundOff)
	ON_BN_CLICKED(IDC_BUTTON_Volume_Down, &CRabbitProductTestToolDlg::OnBnClickedButtonVolumeDown)
	ON_BN_CLICKED(IDC_BUTTON_Volume_Up, &CRabbitProductTestToolDlg::OnBnClickedButtonVolumeUp)
	ON_BN_CLICKED(IDC_BUTTON_Volume_Max, &CRabbitProductTestToolDlg::OnBnClickedButtonVolumeMax)
	ON_BN_CLICKED(IDC_BUTTON_MotorControl, &CRabbitProductTestToolDlg::OnBnClickedButtonMotorcontrol)
	ON_BN_CLICKED(IDC_BUTTON_MotorLeft, &CRabbitProductTestToolDlg::OnBnClickedButtonMotorleft)
	ON_BN_CLICKED(IDC_BUTTON_MotorRight, &CRabbitProductTestToolDlg::OnBnClickedButtonMotorright)
	ON_BN_CLICKED(IDC_BUTTON_MotorStop, &CRabbitProductTestToolDlg::OnBnClickedButtonMotorstop)
	ON_BN_CLICKED(IDC_BUTTON_LED_Stream, &CRabbitProductTestToolDlg::OnBnClickedButtonLedStream)
	ON_BN_CLICKED(IDC_BUTTON_GasControl, &CRabbitProductTestToolDlg::OnBnClickedButtonGascontrol)
	ON_BN_CLICKED(IDC_BUTTON_GasOpen, &CRabbitProductTestToolDlg::OnBnClickedButtonGasopen)
	ON_BN_CLICKED(IDC_BUTTON_GasClose, &CRabbitProductTestToolDlg::OnBnClickedButtonGasclose)
	ON_BN_CLICKED(IDC_BUTTON_FanControl, &CRabbitProductTestToolDlg::OnBnClickedButtonFancontrol)
	ON_BN_CLICKED(IDC_BUTTON_RotateMotorControl, &CRabbitProductTestToolDlg::OnBnClickedButtonRotatemotorcontrol)
	ON_BN_CLICKED(IDC_BUTTON_RotateLeft, &CRabbitProductTestToolDlg::OnBnClickedButtonRotateleft)
	ON_BN_CLICKED(IDC_BUTTON_RotateRight, &CRabbitProductTestToolDlg::OnBnClickedButtonRotateright)
	ON_BN_CLICKED(IDC_BUTTON_RotateStop, &CRabbitProductTestToolDlg::OnBnClickedButtonRotatestop)
	ON_BN_CLICKED(IDC_BUTTON_Record_Start, &CRabbitProductTestToolDlg::OnBnClickedButtonRecordStart)
	ON_BN_CLICKED(IDC_BUTTON_Record_Play, &CRabbitProductTestToolDlg::OnBnClickedButtonRecordPlay)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CRabbitProductTestToolDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_Distance, &CRabbitProductTestToolDlg::OnBnClickedButtonDistance)
	ON_BN_CLICKED(IDC_BUTTON_Uart1, &CRabbitProductTestToolDlg::OnBnClickedButtonUart1)
	ON_BN_CLICKED(IDC_BUTTON_Uart2, &CRabbitProductTestToolDlg::OnBnClickedButtonUart2)
	ON_BN_CLICKED(IDC_BUTTON_UpgradeSH, &CRabbitProductTestToolDlg::OnBnClickedButtonUpgradesh)
	ON_BN_CLICKED(IDC_BUTTON_LightSensor, &CRabbitProductTestToolDlg::OnBnClickedButtonLightsensor)
	ON_BN_CLICKED(IDC_BUTTON_Pir, &CRabbitProductTestToolDlg::OnBnClickedButtonPir)
	ON_BN_CLICKED(IDC_BUTTON_GetPressure, &CRabbitProductTestToolDlg::OnBnClickedButtonGetpressure)
	ON_BN_CLICKED(IDC_BUTTON_Camera0, &CRabbitProductTestToolDlg::OnBnClickedButtonCamera0)
	ON_BN_CLICKED(IDC_BUTTON_Camera1, &CRabbitProductTestToolDlg::OnBnClickedButtonCamera1)
	ON_BN_CLICKED(IDC_BUTTON_Camera2, &CRabbitProductTestToolDlg::OnBnClickedButtonCamera2)
	ON_BN_CLICKED(IDC_BUTTON_Camera3, &CRabbitProductTestToolDlg::OnBnClickedButtonCamera3)
	ON_BN_CLICKED(IDC_BUTTON_MotorCircleTest, &CRabbitProductTestToolDlg::OnBnClickedButtonMotorcircletest)
	ON_BN_CLICKED(IDC_BUTTON_LED_All_NEW, &CRabbitProductTestToolDlg::OnBnClickedButtonLedAllNew)
	ON_BN_CLICKED(IDC_BUTTON_CameraPlay, &CRabbitProductTestToolDlg::OnBnClickedButtonCameraplay)
	ON_BN_CLICKED(IDC_BUTTON_CloseFan, &CRabbitProductTestToolDlg::OnBnClickedButtonClosefan)
	ON_BN_CLICKED(IDC_CHECK_Version, &CRabbitProductTestToolDlg::OnBnClickedCheckVersion)
END_MESSAGE_MAP()


// CRabbitProductTestToolDlg 消息处理程序

BOOL CRabbitProductTestToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	ConnectStatus = 0;
	this->GetDlgItem(IDC_EDIT_IP)->SetWindowText("192.168.1.144");
	this->GetDlgItem(IDC_EDIT_User)->SetWindowText("ubuntu");
	this->GetDlgItem(IDC_EDIT_Password)->SetWindowText("ubuntu");
	red_flag = false;
	blue_flag = false;
	green_flag = false;
	motor_flag = false;
	rotate_flag = false;
	gas_flag = false;
	stream_flag = false;
	distance_flag = false;
	uart1_flag = false;
	uart2_flag = false;
	record_flag = false;
	play_record_flag = false;
	play_audio_flag = false;
	play_left_channel_flag = false;
	play_right_channel_flag = false;
	test_pir_flag = false;
	get_pressure_flag = false;
	camera0_flag = false;
	camera1_flag = false;
	camera2_flag = false;
	camera3_flag = false;
	open_fan_flag = false;
	close_fan_flag = false;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRabbitProductTestToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRabbitProductTestToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRabbitProductTestToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRabbitProductTestToolDlg::OnBnClickedCheckVersion()
{
	// TODO: 在此添加控件通知处理程序代码
	if(this->m_CheckVersion.GetCheck()){
		this->GetDlgItem(IDC_EDIT_User)->SetWindowText("nvidia");
	    this->GetDlgItem(IDC_EDIT_Password)->SetWindowText("nvidia");
	}else{
		this->GetDlgItem(IDC_EDIT_User)->SetWindowText("ubuntu");
	    this->GetDlgItem(IDC_EDIT_Password)->SetWindowText("ubuntu");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	this->GetDlgItem(IDC_BUTTON_Connect)->GetWindowText(str);
	if(str == "连接"){
		this->GetDlgItem(IDC_EDIT_IP)->GetWindowText(hostIP);
		if(hostIP == ""){
			MessageBox(_T("请输入IP"));
			return;
		}
		//MessageBox(_T(hostIP));
		this->GetDlgItem(IDC_EDIT_User)->GetWindowText(username);
		if(username == ""){
			MessageBox(_T("请输入用户名"));
			return;
		}
		this->GetDlgItem(IDC_EDIT_Password)->GetWindowText(password);
		if(password == ""){
			MessageBox(_T("请输入密码"));
			return;
		}
		ip = CString2stringMultibyte(hostIP);
        ssh = new Ssh2(ip);
		user = CString2stringMultibyte(username);
		pass = CString2stringMultibyte(password);
		bool ret = ssh->Connect(user, pass);
		if(ret){
			SSHChannel = ssh->CreateChannel();
			ExcuteChannel = ssh->CreateChannel();
			ConnectStatus = 1;
		    this->GetDlgItem(IDC_BUTTON_Connect)->SetWindowText("断开");
			this->m_CheckVersion.EnableWindow(FALSE);
			if(m_CheckVersion.GetCheck()){
				SSHChannel->Write("sudo chmod 777 /dev/*\n"); 
				if(m_OpenConsole.GetCheck()){
					cprintf("%s \n", SSHChannel->Read().c_str());
				}
				SSHChannel->Write("nvidia\n"); 
				if(m_OpenConsole.GetCheck()){
					cprintf("%s \n", SSHChannel->Read().c_str());
				}
			}
		}else{
			MessageBox(_T("连接失败"));
		}
	}else if(str == "断开"){
		ConnectStatus = 0;
	    ssh->Disconnect();
		this->GetDlgItem(IDC_BUTTON_Connect)->SetWindowText("连接");
		this->GetDlgItem(IDC_BUTTON_LED_Red)->SetWindowText("打开红灯");
		red_flag = false;
		this->GetDlgItem(IDC_BUTTON_LED_Green)->SetWindowText("打开绿灯");
		green_flag = false;
		this->GetDlgItem(IDC_BUTTON_LED_Blue)->SetWindowText("打开蓝灯");
		blue_flag = false;
		this->GetDlgItem(IDC_BUTTON_PlayAudio)->SetWindowText("播放音乐");
		motor_flag = false;
		this->GetDlgItem(IDC_BUTTON_MotorControl)->SetWindowText("电机控制");
		stream_flag = false;
		this->GetDlgItem(IDC_BUTTON_GasControl)->SetWindowText("充气控制");
		gas_flag = false;
		this->GetDlgItem(IDC_BUTTON_RotateMotorControl)->SetWindowText("旋转电机控制");
		rotate_flag = false;
		this->GetDlgItem(IDC_BUTTON_Distance)->SetWindowText("距离测试");
		distance_flag = false;
		this->GetDlgItem(IDC_BUTTON_Uart1)->SetWindowText("串口1测试");
		uart1_flag = false;
		this->GetDlgItem(IDC_BUTTON_Uart2)->SetWindowText("串口2测试");
		uart2_flag = false;
		this->GetDlgItem(IDC_BUTTON_Record_Start)->SetWindowText("开始录音");
		record_flag = false;
		this->GetDlgItem(IDC_BUTTON_Record_Play)->SetWindowText("播放录音");
		play_record_flag = false;
		this->GetDlgItem(IDC_BUTTON_PlayAudio)->SetWindowTextA("播放音乐");
		play_audio_flag  = false;
		this->GetDlgItem(IDC_BUTTON_LeftChannel)->SetWindowTextA("左声道");
		play_left_channel_flag = false;
		this->GetDlgItem(IDC_BUTTON_RightChannel)->SetWindowTextA("右声道");
		play_right_channel_flag = false;
		this->GetDlgItem(IDC_BUTTON_Pir)->SetWindowTextA("人体感应测试");
		test_pir_flag = false;
		this->GetDlgItem(IDC_BUTTON_GetPressure)->SetWindowTextA("获取压力值");
		get_pressure_flag = false;
		this->GetDlgItem(IDC_BUTTON_Camera0)->SetWindowTextA("Camera0测试");
		camera0_flag = false;
		this->GetDlgItem(IDC_BUTTON_Camera1)->SetWindowTextA("Camera1测试");
		camera1_flag = false;
		this->GetDlgItem(IDC_BUTTON_Camera2)->SetWindowTextA("Camera2测试");
		camera2_flag = false;
		this->GetDlgItem(IDC_BUTTON_Camera3)->SetWindowTextA("Camera3测试");
		camera3_flag = false;
		this->GetDlgItem(IDC_BUTTON_FanControl)->SetWindowTextA("打开风扇");
		open_fan_flag = false;
		this->GetDlgItem(IDC_BUTTON_CloseFan)->SetWindowTextA("关闭风扇");
		close_fan_flag = false;
		this->m_CheckVersion.EnableWindow(true);
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonExcute()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	ExcuteThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)ExcuteFun, this, 0, &ExcuteThreadID);
	if(NULL == ExcuteThread){
		MessageBox(_T("create ExcuteThread  failed"));
		return;
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedRed()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&red_flag);
	if(ret != 0){
		return;
	}
	CString str_red;
	this->GetDlgItem(IDC_BUTTON_LED_Red)->GetWindowText(str_red);
	if(str_red == "打开红灯")
	{
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_RED_28);
		}
		else{
			BaseExcute(SSHChannel, LED_RGB_RED);
		}
		red_flag = true;
	    this->GetDlgItem(IDC_BUTTON_LED_Red)->SetWindowText("关闭红灯");
	}else if(str_red == "关闭红灯"){
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_OFF_28);
		}
		else{
			BaseExcute(SSHChannel, LED_RGB_OFF);
		}
		red_flag = false;
	    this->GetDlgItem(IDC_BUTTON_LED_Red)->SetWindowText("打开红灯");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedGreen()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&green_flag);
	if(ret != 0){
		return;
	}
	CString str_green;
	this->GetDlgItem(IDC_BUTTON_LED_Green)->GetWindowText(str_green);
	if(str_green == "打开绿灯")
	{
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_GREEN_28);
		}
		else{
			BaseExcute(SSHChannel, LED_RGB_GREEN);
		}
		green_flag = true;
	    this->GetDlgItem(IDC_BUTTON_LED_Green)->SetWindowText("关闭绿灯");
	}else if(str_green == "关闭绿灯"){
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_OFF_28);
		}
		else{
			BaseExcute(SSHChannel, LED_RGB_OFF);
		}
		green_flag = false;
	    this->GetDlgItem(IDC_BUTTON_LED_Green)->SetWindowText("打开绿灯");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedBlue()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&blue_flag);
	if(ret != 0){
		return;
	}
	CString str_blue;
	this->GetDlgItem(IDC_BUTTON_LED_Blue)->GetWindowText(str_blue);
	if(str_blue == "打开蓝灯")
	{
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_BLUE_28);
		}else{
			BaseExcute(SSHChannel, LED_RGB_BLUE);
		}
		blue_flag = true;
	    this->GetDlgItem(IDC_BUTTON_LED_Blue)->SetWindowText("关闭蓝灯");
	}else if(str_blue == "关闭蓝灯"){
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_OFF_28);
		}else{
			BaseExcute(SSHChannel, LED_RGB_OFF);
		}
		blue_flag = false;
	    this->GetDlgItem(IDC_BUTTON_LED_Blue)->SetWindowText("打开蓝灯");
	}
}
//充气控制
void CRabbitProductTestToolDlg::OnBnClickedButtonGascontrol()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_GasControl)->GetWindowText(str);
	if(str == "充气控制"){
		GasChannel = ssh->CreateChannel();
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(GasChannel, GAS_MOTOR_28);
		}else{
			BaseExcute(GasChannel, GAS_MOTOR);
		}
		gas_flag = true;
		this->GetDlgItem(IDC_BUTTON_GasControl)->SetWindowText("关闭控制");
	}else{
		GasChannel->Write("stop\n");
	    if(m_OpenConsole.GetCheck()){
		    string str = GasChannel->Read();
		    cprintf("%s \n", str.c_str());
	    }
		Sleep(100);
		SSHChannel->Write("killall Test_gasmotor_by_tx1_uart1\n");
		if(m_OpenConsole.GetCheck()){
			string str = GasChannel->Read();
			cprintf("%s \n", str.c_str());
		}
		gas_flag = false;
		this->GetDlgItem(IDC_BUTTON_GasControl)->SetWindowText("充气控制");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonGasopen()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
	MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	if(!gas_flag){
		MessageBox(_T("请先进入充气模式"));
		return;
	}
	string str;
	GasChannel->Write("1\n");
	if(m_OpenConsole.GetCheck()){
		str = GasChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}


void CRabbitProductTestToolDlg::OnBnClickedButtonGasclose()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	if(!gas_flag){
		MessageBox(_T("请先进入充气模式"));
		return;
	}
	string str;
	GasChannel->Write("stop\n");
	if(m_OpenConsole.GetCheck()){
		str = GasChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}

//风扇控制
void CRabbitProductTestToolDlg::OnBnClickedButtonFancontrol()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	SafeFun(&open_fan_flag);
	CString str;
	this->GetDlgItem(IDC_BUTTON_FanControl)->GetWindowText(str);
	if(str == "打开风扇"){ 
		HANDLE FanThread;
	    DWORD FanThreadID;
		FanThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)OpenFanFun, this, 0, &FanThreadID);
		if(NULL == FanThread){
			MessageBox(_T("create FanThread  failed"));
			return;
		};
	    open_fan_flag = true;
		
		this->GetDlgItem(IDC_BUTTON_FanControl)->SetWindowText("停止测试");
	}else if(str == "停止测试"){
		open_fan_flag = false;
		SSHChannel->Write("killall Test_fan_by_tx1_uart2\n");
		if(m_OpenConsole.GetCheck()){
			string str = MotorChannel->Read();
			cprintf("%s \n", str.c_str());
		}
		this->GetDlgItem(IDC_BUTTON_FanControl)->SetWindowText("打开风扇");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonClosefan()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	SafeFun(&close_fan_flag);
	CString str;
	this->GetDlgItem(IDC_BUTTON_CloseFan)->GetWindowText(str);
	if(str == "关闭风扇"){ 
		HANDLE FanThread;
	    DWORD FanThreadID;
		FanThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)CloseFanFun, this, 0, &FanThreadID);
		if(NULL == FanThread){
			MessageBox(_T("create FanThread  failed"));
			return;
		};
	    close_fan_flag = true;
		this->GetDlgItem(IDC_BUTTON_CloseFan)->SetWindowText("停止测试");
	}else if(str == "停止测试"){
		close_fan_flag = false;
		SSHChannel->Write("killall Test_fan_by_tx1_uart2\n");
		if(m_OpenConsole.GetCheck()){
			string str = MotorChannel->Read();
			cprintf("%s \n", str.c_str());
		}
		this->GetDlgItem(IDC_BUTTON_CloseFan)->SetWindowText("关闭风扇");
	}
}

//电机控制
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorcontrol()
{
	// TODO: 在此添加控件通知处理程序
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_MotorControl)->GetWindowText(str);
	if(str == "电机控制"){
		MotorChannel = ssh->CreateChannel();
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(MotorChannel, MOTOR_CONTROL_28);
		}else{
		    BaseExcute(MotorChannel, MOTOR_CONTROL);
		}
		motor_flag = true;
		this->GetDlgItem(IDC_BUTTON_MotorControl)->SetWindowText("关闭控制");
	}else{
		MotorChannel->Write("stop\n");
	    if(m_OpenConsole.GetCheck()){
		    string str = MotorChannel->Read();
		    cprintf("%s \n", str.c_str());
	    }
		Sleep(500);
		SSHChannel->Write("killall Test_motor_by_tx1_uart1\n");
		if(m_OpenConsole.GetCheck()){
			string str = MotorChannel->Read();
			cprintf("%s \n", str.c_str());
		}
		motor_flag = false;
		this->GetDlgItem(IDC_BUTTON_MotorControl)->SetWindowText("电机控制");
	}
}

//电机左移
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorleft()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	if(!motor_flag){
		MessageBox(_T("请先进入控制电机模式"));
		return;
	}
	string str;
	MotorChannel->Write("1\n");
	if(m_OpenConsole.GetCheck()){
		str = MotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}
//电机右移
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorright()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	if(!motor_flag){
		MessageBox(_T("请先进入控制电机模式"));
		return;
	}
	string str;
	MotorChannel->Write("2\n");
	if(m_OpenConsole.GetCheck()){
		str = MotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}
//停止移动
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorstop()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	if(!motor_flag){
		MessageBox(_T("请先进入控制电机模式"));
		return;
	}
	string str;
	MotorChannel->Write("stop\n");
	if(m_OpenConsole.GetCheck()){
		str = MotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}
//电机自动测试
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorcircletest()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	
	this->GetDlgItem(IDC_BUTTON_MotorCircleTest)->GetWindowText(str);
	if(str == "电机自动测试"){	
		Channel *channel = ssh->CreateChannel();
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(channel, MOTOR_AUTO_28);
		}else{
		    BaseExcute(channel, MOTOR_AUTO);
		}
		this->GetDlgItem(IDC_BUTTON_MotorCircleTest)->SetWindowText("停止测试");
	}else{
		Sleep(100);
		SSHChannel->Write("killall Test_motor_by_tx1_uart1_auto\n");
		if(m_OpenConsole.GetCheck()){
			string str = RotateMotorChannel->Read();
			cprintf("%s \n", str.c_str());
		}
		Sleep(100);
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, MOTOR_AUDO_STOP_28);
		}else{
			BaseExcute(SSHChannel, MOTOR_AUDO_STOP);
		}
		this->GetDlgItem(IDC_BUTTON_MotorCircleTest)->SetWindowText("电机自动测试");
	}
}
//旋转电机控制
void CRabbitProductTestToolDlg::OnBnClickedButtonRotatemotorcontrol()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_RotateMotorControl)->GetWindowText(str);
	if(str == "旋转电机控制"){
		RotateMotorChannel = ssh->CreateChannel();
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(RotateMotorChannel, ATT_MOTOR_28);
		}else{
			BaseExcute(RotateMotorChannel, ATT_MOTOR);
		}
		rotate_flag = true;
		this->GetDlgItem(IDC_BUTTON_RotateMotorControl)->SetWindowText("关闭控制");
	}else{
		RotateMotorChannel->Write("stop\n");
	    if(m_OpenConsole.GetCheck()){
		    string str = RotateMotorChannel->Read();
		    cprintf("%s \n", str.c_str());
	    }
		Sleep(500);
		SSHChannel->Write("killall Test_attmotor_by_tx1_uart1\n");
		if(m_OpenConsole.GetCheck()){
			string str = RotateMotorChannel->Read();
			cprintf("%s \n", str.c_str());
		}
		rotate_flag = false;
		this->GetDlgItem(IDC_BUTTON_RotateMotorControl)->SetWindowText("旋转电机控制");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonRotateleft()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	if(!rotate_flag){
		MessageBox(_T("请先进入控制旋转电机模式"));
		return;
	}
	string str;
	RotateMotorChannel->Write("1\n");
	if(m_OpenConsole.GetCheck()){
		str = RotateMotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonRotateright()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	if(!rotate_flag){
		MessageBox(_T("请先进入控制旋转电机模式"));
		return;
	}
	string str;
	RotateMotorChannel->Write("2\n");
	if(m_OpenConsole.GetCheck()){
		str = RotateMotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonRotatestop()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return;
	}
	if(!rotate_flag){
		MessageBox(_T("请先进入控制旋转电机模式"));
		return;
	}
	string str;
	RotateMotorChannel->Write("stop\n");
	if(m_OpenConsole.GetCheck()){
		str = RotateMotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedAll()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(stream_flag){
		//停掉流水灯
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, STOP_STREAM_LED_28);
		}else{
		    BaseExcute(SSHChannel, STOP_STREAM_LED);
		}
		stream_flag = false;
	}
	if(this->m_CheckVersion.GetCheck()){
		BaseExcute(SSHChannel, ALL_LED_28);
	}else{
	    BaseExcute(SSHChannel, ALL_LED);
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLecWarm()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(stream_flag){
		//停掉流水灯
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, STOP_STREAM_LED_28);
		}else{
		    BaseExcute(SSHChannel, STOP_STREAM_LED);
		}
		stream_flag = false;
	}
	if(this->m_CheckVersion.GetCheck()){
		BaseExcute(SSHChannel, LED_WARM_28);
	}else{
		BaseExcute(SSHChannel, LED_WARM);
	}
}
//流水灯
void CRabbitProductTestToolDlg::OnBnClickedButtonLedStream()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	LEDStreamThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)LEDStreamFun, this, 0, &LEDStreamThreadID);
	if(NULL == LEDStreamThread){
		MessageBox(_T("create LEDStreamThread  failed"));
		return;
	}
	stream_flag = true;
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedCool()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(stream_flag){
		//停掉流水灯
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, STOP_STREAM_LED_28);
		}else{
		    BaseExcute(SSHChannel, STOP_STREAM_LED);
		}
		stream_flag = false;
	}
	if(this->m_CheckVersion.GetCheck()){
		BaseExcute(SSHChannel, LED_COOL_28);
	}else{
		BaseExcute(SSHChannel, LED_COOL);
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedOff()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(stream_flag){
		//停掉流水灯
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, STOP_STREAM_LED_28);
		}else{
		    BaseExcute(SSHChannel, STOP_STREAM_LED);
		}
		stream_flag = false;
	}
	if(this->m_CheckVersion.GetCheck()){
		BaseExcute(SSHChannel, LED_OFF_28);
	}else{
		BaseExcute(SSHChannel, LED_OFF);
	}
}
//执行升级脚本
void CRabbitProductTestToolDlg::OnBnClickedButtonUpgradesh()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	UpgradeSHThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)UpgradeSHFun, this, 0, &UpgradeSHThreadID);
	if(NULL == UpgradeSHThread){
		MessageBox(_T("create UpgradeSHThread  failed"));
		return;
	}
}
//音量调节
void CRabbitProductTestToolDlg::OnBnClickedButtonSoundOff()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	BaseExcute(SSHChannel, "amixer -c 1 set Master 0%\n");
}

void CRabbitProductTestToolDlg::OnBnClickedButtonVolumeDown()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	BaseExcute(SSHChannel, "amixer -c 1 set Master 5%-\n");
}

void CRabbitProductTestToolDlg::OnBnClickedButtonVolumeMax()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(this->m_CheckVersion.GetCheck()){
	    BaseExcute(SSHChannel, SOUND_MAX_28);
	}else{
	    BaseExcute(SSHChannel, SOUND_MAX);
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonVolumeUp()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	BaseExcute(SSHChannel, "amixer -c 1 set Master 5%+\n");
}
//录音
void CRabbitProductTestToolDlg::OnBnClickedButtonRecordStart()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	this->GetDlgItem(IDC_BUTTON_Record_Start)->GetWindowText(str);
	if(str == "开始录音"){
        RecordThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)RecordFun, this, 0, &RecordThreadID);
		if(NULL == RecordThread){
			MessageBox(_T("create RecordThread  failed"));
			return;
		}
		record_flag = true;
		this->GetDlgItem(IDC_BUTTON_Record_Start)->SetWindowText("停止录音");
		
	}else{
		SSHChannel->Write("killall Test_Record_demo\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		record_flag = false;
		this->GetDlgItem(IDC_BUTTON_Record_Start)->SetWindowText("开始录音");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonRecordPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	this->GetDlgItem(IDC_BUTTON_Record_Play)->GetWindowText(str);
	if(str == "播放录音"){
        PlayRecordThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayRecordFun, this, 0, &PlayRecordThreadID);
		if(NULL == PlayRecordThread){
			MessageBox(_T("create PlayRecordThread  failed"));
			return;
		}
		play_record_flag = true;
		this->GetDlgItem(IDC_BUTTON_Record_Play)->SetWindowText("停止播放");
		
	}else{
		SSHChannel->Write("pkill -9 aplay\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		play_record_flag = false;
		this->GetDlgItem(IDC_BUTTON_Record_Play)->SetWindowText("播放录音");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonPlayaudio()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_PlayAudio)->GetWindowText(str);
	if(str == "播放音乐"){
		//创建播放线程		
		PlayAudioThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayAudioFun, this, 0, &PlayAudioThreadID);
		if(NULL == PlayAudioThread){
			MessageBox(_T("create PlayAudioThread  failed"));
			return;
		}
		play_audio_flag = true;
		this->GetDlgItem(IDC_BUTTON_PlayAudio)->SetWindowText("停止播放");
	}else{
		SSHChannel->Write("pkill -9 mpg123\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		play_audio_flag = false;
		this->GetDlgItem(IDC_BUTTON_PlayAudio)->SetWindowText("播放音乐");
	}
}
void CRabbitProductTestToolDlg::OnBnClickedButtonLeftchannel()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_LeftChannel)->GetWindowText(str);
	if(str == "左声道"){
		PlayLeftChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayLeftChannelFun, this, 0, &PlayLeftChannelThreadID);
		if(NULL == PlayLeftChannelThread){
			MessageBox(_T("create PlayLeftChannelThread  failed"));
			return;
		}
		play_left_channel_flag = true;
		this->GetDlgItem(IDC_BUTTON_LeftChannel)->SetWindowText("关闭");
	}else{
		SSHChannel->Write("pkill -9 aplay\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		play_left_channel_flag = false;
		this->GetDlgItem(IDC_BUTTON_LeftChannel)->SetWindowText("左声道");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonRightchannel()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_RightChannel)->GetWindowText(str);
	if(str == "右声道"){
		PlayRightChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayRightChannelFun, this, 0, &PlayRightChannelThreadID);
		if(NULL == PlayRightChannelThread){
			MessageBox(_T("create PlayLeftChannelThread  failed"));
			return;
		}
		play_right_channel_flag = true;
		this->GetDlgItem(IDC_BUTTON_RightChannel)->SetWindowText("关闭");
	}else{
		SSHChannel->Write("pkill -9 aplay\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		play_right_channel_flag = false;
		this->GetDlgItem(IDC_BUTTON_RightChannel)->SetWindowText("右声道");
	}
}
//看直播
void CRabbitProductTestToolDlg::OnBnClickedButtonCameraplay()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CameraPlayerDlg *cameraPlayer = new CameraPlayerDlg();
	this->GetDlgItem(IDC_EDIT_IP)->GetWindowTextA(cameraPlayer->dstIP);
	cameraPlayer->ip = CString2stringMultibyte(hostIP);
	cameraPlayer->user = CString2stringMultibyte(username);
	cameraPlayer->pass = CString2stringMultibyte(password);
	cameraPlayer->pDlg = this;
	cameraPlayer->DoModal();
}

void CRabbitProductTestToolDlg::OnBnClickedButtonUpgrade()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	UpgradeDlg upgradeDlg;
	upgradeDlg.SSHChannel = SSHChannel;
	upgradeDlg.hostIP = hostIP;
	upgradeDlg.m_OpenConsole = &m_OpenConsole;
	upgradeDlg.pDlg = this;
	upgradeDlg.open_flag = true;
	upgradeDlg.over_flag = true;
	upgradeDlg.ip = ip;
	upgradeDlg.user = user;
	upgradeDlg.pass = pass;
	upgradeDlg.DoModal();
}

void CRabbitProductTestToolDlg::OnBnClickedCheckOpenconsole()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_OpenConsole.GetCheck()){
		AllocConsole();
	}else{
		FreeConsole();
	}
}

void CRabbitProductTestToolDlg::BaseExcute(Channel *channel, string commond){

	channel->Write("cd /home/ubuntu/hardware_test/ \n");
	string str;
	if(m_OpenConsole.GetCheck()){
		str = channel->Read();
		cprintf("%s \n", str.c_str());
	}
	channel->Write(commond);
	if(m_OpenConsole.GetCheck()){
		str = channel->Read();
		cprintf("%s \n", str.c_str());
	}
}

int CRabbitProductTestToolDlg::SafeFun(bool *flag){
	if(ConnectStatus == 0){
		MessageBox(_T("未连接设备,无法执行"));
		return -1;
	}
	if(flag != &red_flag && red_flag){
		MessageBox("请先关闭红灯，否则可能会影响测试结果");
		return -2;
	}
	if(flag != &green_flag && green_flag){
		MessageBox("请先关闭绿灯，否则可能会影响测试结果");
		return -3;
	}
	if(flag != &blue_flag && blue_flag){
		MessageBox("请先关闭蓝灯，否则可能会影响测试结果");
		return -4;
	}
	if(flag != &camera0_flag && camera0_flag){
		MessageBox("正在测试Camera0,请稍等");
		return -5;
	}
	if(flag != &camera1_flag && camera1_flag){
		MessageBox("正在测试Camera1,请稍等");
		return -5;
	}
    if(flag != &camera2_flag && camera2_flag){
		MessageBox("正在测试Camera2,请稍等");
		return -5;
	}
	if(flag != &camera3_flag && camera3_flag){
		MessageBox("正在测试Camera3,请稍等");
		return -5;
	}
	if(flag != &open_fan_flag && open_fan_flag){
		MessageBox("正在测试打开风扇,请稍等");
		return -5;
	}
	if(flag != &close_fan_flag && close_fan_flag){
		MessageBox("正在测试关闭风扇,请稍等");
		return -5;
	}
	return 0;
}

//清空日志
void CRabbitProductTestToolDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEditCtrl_Log.SetSel(0, -1);
	m_RichEditCtrl_Log.SetWindowText("");
}

//距离测试
void CRabbitProductTestToolDlg::OnBnClickedButtonDistance()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Distance)->GetWindowText(str);
	if(str == "距离测试"){
		distance_flag = true;
		DistanceChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)DistanceTestFun, this, 0, &DistanceChannelThreadID);
		if(NULL == DistanceChannelThread){
			MessageBox(_T("create DistanceChannelThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Distance)->SetWindowText("停止测试");
	}else{
		distance_flag = false;
		SSHChannel->Write("killall Test_read_range\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Distance)->SetWindowText("距离测试");
		this->GetDlgItem(IDC_STATIC_DistanceLeft)->SetWindowTextA("0");
		this->GetDlgItem(IDC_STATIC_DistanceRight)->SetWindowTextA("0");
	}
}

//串口1测试
void CRabbitProductTestToolDlg::OnBnClickedButtonUart1()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Uart1)->GetWindowText(str);
	if(str == "串口1测试"){
		uart1_flag = true;
		Uart1ChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Uart1TestFun, this, 0, &Uart1ChannelThreadID);
		if(NULL == Uart1ChannelThread){
			MessageBox(_T("create Uart1ChannelThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Uart1)->SetWindowText("停止测试");
	}else{
		uart1_flag = false;
		SSHChannel->Write("killall Test_STM32_UART_BY_TX1\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Uart1)->SetWindowText("串口1测试");
	}
}

//串口2测试
void CRabbitProductTestToolDlg::OnBnClickedButtonUart2()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Uart2)->GetWindowText(str);
	if(str == "串口2测试"){
		uart2_flag = true;
		Uart2ChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Uart2TestFun, this, 0, &Uart2ChannelThreadID);
		if(NULL == Uart2ChannelThread){
			MessageBox(_T("create Uart1ChannelThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Uart2)->SetWindowText("停止测试");
	}else{
		uart2_flag = false;
		SSHChannel->Write("killall Test_STM32_UART_BY_TX1\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Uart2)->SetWindowText("串口2测试");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLightsensor()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	Channel *channel = ssh->CreateChannel();
	string str;
	if(this->m_CheckVersion.GetCheck()){
		channel->Write("cd /home/nvidia/hardware_test/ \n");
		str = channel->Read();
		if(m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		channel->Write(LIGHT_SENSOR_28);
	}else{
		channel->Write("cd /home/ubuntu/hardware_test/ \n");
		str = channel->Read();
		if(m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		channel->Write(LIGHT_SENSOR);
	}
	str = channel->Read();
	if(m_OpenConsole.GetCheck()){	
		cprintf("%s \n", str.c_str());
	}
	int pos1 = str.find("sh");
	if(pos1 == string::npos){
		MessageBox(_T("获取亮度失败，请重试"));
		return;
	}
	string tmpStr0 = str.substr(pos1, str.length() - pos1);
	pos1 = tmpStr0.find("\n");
	if(pos1 == string::npos){
		MessageBox(_T("获取亮度失败，请重试"));
		return;
	}
	string tmpStr = tmpStr0.substr(pos1+1, tmpStr.length() - pos1 - 1);
	int pos_light1 = tmpStr.find("\n");
	string light1, light2;
	if(tmpStr.at(pos_light1 - 1) == '\r'){
		light1 = tmpStr.substr(0, pos_light1 - 1);
	}else{
		light1 = tmpStr.substr(0, pos_light1);
	}
	string tmpStr2 = tmpStr.substr(pos_light1 + 1, tmpStr.length() - pos_light1 - 1);
	int pos_light2 = tmpStr2.find("\n");
	if(tmpStr2.at(pos_light2 - 1) == '\r'){
		light2 = tmpStr2.substr(0, pos_light2 - 1);
	}else{
		light2 = tmpStr.substr(0, pos_light2);
	}
	
	if(AllisNum(light1) && AllisNum(light2)){
        this->GetDlgItem(IDC_STATIC_Light1)->SetWindowText(light1.c_str());
		this->GetDlgItem(IDC_STATIC_Light2)->SetWindowText(light2.c_str());
	}else{
		MessageBox(_T("没有获取到亮度值，请重试"));
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonPir()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Pir)->GetWindowText(str);
	if(str == "人体感应测试"){
		test_pir_flag = true;
		TestPirThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)TestPirFun, this, 0, &TestPirThreadID);
		if(NULL == TestPirThread){
			MessageBox(_T("create TestPirThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Pir)->SetWindowText("停止测试");
	}else{
		test_pir_flag = false;
		SSHChannel->Write("killall test_pir\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Pir)->SetWindowText("人体感应测试");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonGetpressure()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_GetPressure)->GetWindowText(str);
	if(str == "获取压力值"){
		get_pressure_flag = true;
		GetPressureThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)GetPRessureFun, this, 0, &GetPressureThreadID);
		if(NULL == GetPressureThread){
			MessageBox(_T("create GetPressureThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_GetPressure)->SetWindowText("停止测试");
	}else{
		get_pressure_flag = false;
		SSHChannel->Write("killall Test_Get_Pressure_diff\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_GetPressure)->SetWindowText("获取压力值");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonCamera0()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int ret = SafeFun(&camera0_flag);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Camera0)->GetWindowText(str);
	if(str == "Camera0测试"){
		camera0_flag = true;
		Camera0Thread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Camera0TestFun, this, 0, &Camera0ThreadID);
		if(NULL == Camera0Thread){
			MessageBox(_T("create Camera0Thread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Camera0)->SetWindowText("停止测试");
	}else{
		camera0_flag = false;
		SSHChannel->Write("killall save_raw_image\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Camera0)->SetWindowText("Camera0测试");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonCamera1()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&camera1_flag);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Camera1)->GetWindowText(str);
	if(str == "Camera1测试"){
		camera1_flag = true;
		Camera1Thread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Camera1TestFun, this, 0, &Camera1ThreadID);
		if(NULL == Camera1Thread){
			MessageBox(_T("create Camera1Thread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Camera1)->SetWindowText("停止测试");
	}else{
		camera1_flag = false;
		SSHChannel->Write("killall save_raw_image\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Camera1)->SetWindowText("Camera1测试");
	}
}


void CRabbitProductTestToolDlg::OnBnClickedButtonCamera2()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&camera2_flag);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Camera2)->GetWindowText(str);
	if(str == "Camera2测试"){
		camera2_flag = true;
		Camera2Thread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Camera2TestFun, this, 0, &Camera2ThreadID);
		if(NULL == Camera2Thread){
			MessageBox(_T("create Camera2Thread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Camera2)->SetWindowText("停止测试");
	}else{
		camera2_flag = false;
		SSHChannel->Write("killall save_raw_image\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Camera2)->SetWindowText("Camera2测试");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonCamera3()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&camera3_flag);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Camera3)->GetWindowText(str);
	if(str == "Camera3测试"){
		camera3_flag = true;
		Camera3Thread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Camera3TestFun, this, 0, &Camera3ThreadID);
		if(NULL == Camera3Thread){
			MessageBox(_T("create Camera3Thread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Camera3)->SetWindowText("停止测试");
	}else{
		camera3_flag = false;
		SSHChannel->Write("killall save_raw_image\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Camera3)->SetWindowText("Camera3测试");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedAllNew()
{
	// TODO: 在此添加控件通知处理程序代码
}

bool CRabbitProductTestToolDlg::AllisNum(string str){
	for (int i = 0; i < str.size(); i++)
	{
		int tmp = (int)str[i];
		if (tmp >= 48 && tmp <= 57)
		{
			continue;
		}
		else
		{
			return false;
		}
	} 
	return true;
}
