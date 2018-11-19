
// RabbitProductTestToolDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CRabbitProductTestToolDlg �Ի���



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


// CRabbitProductTestToolDlg ��Ϣ�������

BOOL CRabbitProductTestToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRabbitProductTestToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRabbitProductTestToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRabbitProductTestToolDlg::OnBnClickedCheckVersion()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	this->GetDlgItem(IDC_BUTTON_Connect)->GetWindowText(str);
	if(str == "����"){
		this->GetDlgItem(IDC_EDIT_IP)->GetWindowText(hostIP);
		if(hostIP == ""){
			MessageBox(_T("������IP"));
			return;
		}
		//MessageBox(_T(hostIP));
		this->GetDlgItem(IDC_EDIT_User)->GetWindowText(username);
		if(username == ""){
			MessageBox(_T("�������û���"));
			return;
		}
		this->GetDlgItem(IDC_EDIT_Password)->GetWindowText(password);
		if(password == ""){
			MessageBox(_T("����������"));
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
		    this->GetDlgItem(IDC_BUTTON_Connect)->SetWindowText("�Ͽ�");
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
			MessageBox(_T("����ʧ��"));
		}
	}else if(str == "�Ͽ�"){
		ConnectStatus = 0;
	    ssh->Disconnect();
		this->GetDlgItem(IDC_BUTTON_Connect)->SetWindowText("����");
		this->GetDlgItem(IDC_BUTTON_LED_Red)->SetWindowText("�򿪺��");
		red_flag = false;
		this->GetDlgItem(IDC_BUTTON_LED_Green)->SetWindowText("���̵�");
		green_flag = false;
		this->GetDlgItem(IDC_BUTTON_LED_Blue)->SetWindowText("������");
		blue_flag = false;
		this->GetDlgItem(IDC_BUTTON_PlayAudio)->SetWindowText("��������");
		motor_flag = false;
		this->GetDlgItem(IDC_BUTTON_MotorControl)->SetWindowText("�������");
		stream_flag = false;
		this->GetDlgItem(IDC_BUTTON_GasControl)->SetWindowText("��������");
		gas_flag = false;
		this->GetDlgItem(IDC_BUTTON_RotateMotorControl)->SetWindowText("��ת�������");
		rotate_flag = false;
		this->GetDlgItem(IDC_BUTTON_Distance)->SetWindowText("�������");
		distance_flag = false;
		this->GetDlgItem(IDC_BUTTON_Uart1)->SetWindowText("����1����");
		uart1_flag = false;
		this->GetDlgItem(IDC_BUTTON_Uart2)->SetWindowText("����2����");
		uart2_flag = false;
		this->GetDlgItem(IDC_BUTTON_Record_Start)->SetWindowText("��ʼ¼��");
		record_flag = false;
		this->GetDlgItem(IDC_BUTTON_Record_Play)->SetWindowText("����¼��");
		play_record_flag = false;
		this->GetDlgItem(IDC_BUTTON_PlayAudio)->SetWindowTextA("��������");
		play_audio_flag  = false;
		this->GetDlgItem(IDC_BUTTON_LeftChannel)->SetWindowTextA("������");
		play_left_channel_flag = false;
		this->GetDlgItem(IDC_BUTTON_RightChannel)->SetWindowTextA("������");
		play_right_channel_flag = false;
		this->GetDlgItem(IDC_BUTTON_Pir)->SetWindowTextA("�����Ӧ����");
		test_pir_flag = false;
		this->GetDlgItem(IDC_BUTTON_GetPressure)->SetWindowTextA("��ȡѹ��ֵ");
		get_pressure_flag = false;
		this->GetDlgItem(IDC_BUTTON_Camera0)->SetWindowTextA("Camera0����");
		camera0_flag = false;
		this->GetDlgItem(IDC_BUTTON_Camera1)->SetWindowTextA("Camera1����");
		camera1_flag = false;
		this->GetDlgItem(IDC_BUTTON_Camera2)->SetWindowTextA("Camera2����");
		camera2_flag = false;
		this->GetDlgItem(IDC_BUTTON_Camera3)->SetWindowTextA("Camera3����");
		camera3_flag = false;
		this->GetDlgItem(IDC_BUTTON_FanControl)->SetWindowTextA("�򿪷���");
		open_fan_flag = false;
		this->GetDlgItem(IDC_BUTTON_CloseFan)->SetWindowTextA("�رշ���");
		close_fan_flag = false;
		this->m_CheckVersion.EnableWindow(true);
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonExcute()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(&red_flag);
	if(ret != 0){
		return;
	}
	CString str_red;
	this->GetDlgItem(IDC_BUTTON_LED_Red)->GetWindowText(str_red);
	if(str_red == "�򿪺��")
	{
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_RED_28);
		}
		else{
			BaseExcute(SSHChannel, LED_RGB_RED);
		}
		red_flag = true;
	    this->GetDlgItem(IDC_BUTTON_LED_Red)->SetWindowText("�رպ��");
	}else if(str_red == "�رպ��"){
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_OFF_28);
		}
		else{
			BaseExcute(SSHChannel, LED_RGB_OFF);
		}
		red_flag = false;
	    this->GetDlgItem(IDC_BUTTON_LED_Red)->SetWindowText("�򿪺��");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedGreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(&green_flag);
	if(ret != 0){
		return;
	}
	CString str_green;
	this->GetDlgItem(IDC_BUTTON_LED_Green)->GetWindowText(str_green);
	if(str_green == "���̵�")
	{
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_GREEN_28);
		}
		else{
			BaseExcute(SSHChannel, LED_RGB_GREEN);
		}
		green_flag = true;
	    this->GetDlgItem(IDC_BUTTON_LED_Green)->SetWindowText("�ر��̵�");
	}else if(str_green == "�ر��̵�"){
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_OFF_28);
		}
		else{
			BaseExcute(SSHChannel, LED_RGB_OFF);
		}
		green_flag = false;
	    this->GetDlgItem(IDC_BUTTON_LED_Green)->SetWindowText("���̵�");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedBlue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(&blue_flag);
	if(ret != 0){
		return;
	}
	CString str_blue;
	this->GetDlgItem(IDC_BUTTON_LED_Blue)->GetWindowText(str_blue);
	if(str_blue == "������")
	{
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_BLUE_28);
		}else{
			BaseExcute(SSHChannel, LED_RGB_BLUE);
		}
		blue_flag = true;
	    this->GetDlgItem(IDC_BUTTON_LED_Blue)->SetWindowText("�ر�����");
	}else if(str_blue == "�ر�����"){
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(SSHChannel, LED_RGB_OFF_28);
		}else{
			BaseExcute(SSHChannel, LED_RGB_OFF);
		}
		blue_flag = false;
	    this->GetDlgItem(IDC_BUTTON_LED_Blue)->SetWindowText("������");
	}
}
//��������
void CRabbitProductTestToolDlg::OnBnClickedButtonGascontrol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_GasControl)->GetWindowText(str);
	if(str == "��������"){
		GasChannel = ssh->CreateChannel();
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(GasChannel, GAS_MOTOR_28);
		}else{
			BaseExcute(GasChannel, GAS_MOTOR);
		}
		gas_flag = true;
		this->GetDlgItem(IDC_BUTTON_GasControl)->SetWindowText("�رտ���");
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
		this->GetDlgItem(IDC_BUTTON_GasControl)->SetWindowText("��������");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonGasopen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
	MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	if(!gas_flag){
		MessageBox(_T("���Ƚ������ģʽ"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	if(!gas_flag){
		MessageBox(_T("���Ƚ������ģʽ"));
		return;
	}
	string str;
	GasChannel->Write("stop\n");
	if(m_OpenConsole.GetCheck()){
		str = GasChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}

//���ȿ���
void CRabbitProductTestToolDlg::OnBnClickedButtonFancontrol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	SafeFun(&open_fan_flag);
	CString str;
	this->GetDlgItem(IDC_BUTTON_FanControl)->GetWindowText(str);
	if(str == "�򿪷���"){ 
		HANDLE FanThread;
	    DWORD FanThreadID;
		FanThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)OpenFanFun, this, 0, &FanThreadID);
		if(NULL == FanThread){
			MessageBox(_T("create FanThread  failed"));
			return;
		};
	    open_fan_flag = true;
		
		this->GetDlgItem(IDC_BUTTON_FanControl)->SetWindowText("ֹͣ����");
	}else if(str == "ֹͣ����"){
		open_fan_flag = false;
		SSHChannel->Write("killall Test_fan_by_tx1_uart2\n");
		if(m_OpenConsole.GetCheck()){
			string str = MotorChannel->Read();
			cprintf("%s \n", str.c_str());
		}
		this->GetDlgItem(IDC_BUTTON_FanControl)->SetWindowText("�򿪷���");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonClosefan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	SafeFun(&close_fan_flag);
	CString str;
	this->GetDlgItem(IDC_BUTTON_CloseFan)->GetWindowText(str);
	if(str == "�رշ���"){ 
		HANDLE FanThread;
	    DWORD FanThreadID;
		FanThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)CloseFanFun, this, 0, &FanThreadID);
		if(NULL == FanThread){
			MessageBox(_T("create FanThread  failed"));
			return;
		};
	    close_fan_flag = true;
		this->GetDlgItem(IDC_BUTTON_CloseFan)->SetWindowText("ֹͣ����");
	}else if(str == "ֹͣ����"){
		close_fan_flag = false;
		SSHChannel->Write("killall Test_fan_by_tx1_uart2\n");
		if(m_OpenConsole.GetCheck()){
			string str = MotorChannel->Read();
			cprintf("%s \n", str.c_str());
		}
		this->GetDlgItem(IDC_BUTTON_CloseFan)->SetWindowText("�رշ���");
	}
}

//�������
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorcontrol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ�������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_MotorControl)->GetWindowText(str);
	if(str == "�������"){
		MotorChannel = ssh->CreateChannel();
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(MotorChannel, MOTOR_CONTROL_28);
		}else{
		    BaseExcute(MotorChannel, MOTOR_CONTROL);
		}
		motor_flag = true;
		this->GetDlgItem(IDC_BUTTON_MotorControl)->SetWindowText("�رտ���");
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
		this->GetDlgItem(IDC_BUTTON_MotorControl)->SetWindowText("�������");
	}
}

//�������
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorleft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	if(!motor_flag){
		MessageBox(_T("���Ƚ�����Ƶ��ģʽ"));
		return;
	}
	string str;
	MotorChannel->Write("1\n");
	if(m_OpenConsole.GetCheck()){
		str = MotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}
//�������
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorright()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	if(!motor_flag){
		MessageBox(_T("���Ƚ�����Ƶ��ģʽ"));
		return;
	}
	string str;
	MotorChannel->Write("2\n");
	if(m_OpenConsole.GetCheck()){
		str = MotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}
//ֹͣ�ƶ�
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	if(!motor_flag){
		MessageBox(_T("���Ƚ�����Ƶ��ģʽ"));
		return;
	}
	string str;
	MotorChannel->Write("stop\n");
	if(m_OpenConsole.GetCheck()){
		str = MotorChannel->Read();
		cprintf("%s \n", str.c_str());
	}
}
//����Զ�����
void CRabbitProductTestToolDlg::OnBnClickedButtonMotorcircletest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	
	this->GetDlgItem(IDC_BUTTON_MotorCircleTest)->GetWindowText(str);
	if(str == "����Զ�����"){	
		Channel *channel = ssh->CreateChannel();
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(channel, MOTOR_AUTO_28);
		}else{
		    BaseExcute(channel, MOTOR_AUTO);
		}
		this->GetDlgItem(IDC_BUTTON_MotorCircleTest)->SetWindowText("ֹͣ����");
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
		this->GetDlgItem(IDC_BUTTON_MotorCircleTest)->SetWindowText("����Զ�����");
	}
}
//��ת�������
void CRabbitProductTestToolDlg::OnBnClickedButtonRotatemotorcontrol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_RotateMotorControl)->GetWindowText(str);
	if(str == "��ת�������"){
		RotateMotorChannel = ssh->CreateChannel();
		if(this->m_CheckVersion.GetCheck()){
			BaseExcute(RotateMotorChannel, ATT_MOTOR_28);
		}else{
			BaseExcute(RotateMotorChannel, ATT_MOTOR);
		}
		rotate_flag = true;
		this->GetDlgItem(IDC_BUTTON_RotateMotorControl)->SetWindowText("�رտ���");
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
		this->GetDlgItem(IDC_BUTTON_RotateMotorControl)->SetWindowText("��ת�������");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonRotateleft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	if(!rotate_flag){
		MessageBox(_T("���Ƚ��������ת���ģʽ"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	if(!rotate_flag){
		MessageBox(_T("���Ƚ��������ת���ģʽ"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(ConnectStatus == 0){
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return;
	}
	if(!rotate_flag){
		MessageBox(_T("���Ƚ��������ת���ģʽ"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(stream_flag){
		//ͣ����ˮ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(stream_flag){
		//ͣ����ˮ��
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
//��ˮ��
void CRabbitProductTestToolDlg::OnBnClickedButtonLedStream()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(stream_flag){
		//ͣ����ˮ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	if(stream_flag){
		//ͣ����ˮ��
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
//ִ�������ű�
void CRabbitProductTestToolDlg::OnBnClickedButtonUpgradesh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//��������
void CRabbitProductTestToolDlg::OnBnClickedButtonSoundOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	BaseExcute(SSHChannel, "amixer -c 1 set Master 0%\n");
}

void CRabbitProductTestToolDlg::OnBnClickedButtonVolumeDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	BaseExcute(SSHChannel, "amixer -c 1 set Master 5%-\n");
}

void CRabbitProductTestToolDlg::OnBnClickedButtonVolumeMax()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	BaseExcute(SSHChannel, "amixer -c 1 set Master 5%+\n");
}
//¼��
void CRabbitProductTestToolDlg::OnBnClickedButtonRecordStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	this->GetDlgItem(IDC_BUTTON_Record_Start)->GetWindowText(str);
	if(str == "��ʼ¼��"){
        RecordThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)RecordFun, this, 0, &RecordThreadID);
		if(NULL == RecordThread){
			MessageBox(_T("create RecordThread  failed"));
			return;
		}
		record_flag = true;
		this->GetDlgItem(IDC_BUTTON_Record_Start)->SetWindowText("ֹͣ¼��");
		
	}else{
		SSHChannel->Write("killall Test_Record_demo\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		record_flag = false;
		this->GetDlgItem(IDC_BUTTON_Record_Start)->SetWindowText("��ʼ¼��");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonRecordPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	this->GetDlgItem(IDC_BUTTON_Record_Play)->GetWindowText(str);
	if(str == "����¼��"){
        PlayRecordThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayRecordFun, this, 0, &PlayRecordThreadID);
		if(NULL == PlayRecordThread){
			MessageBox(_T("create PlayRecordThread  failed"));
			return;
		}
		play_record_flag = true;
		this->GetDlgItem(IDC_BUTTON_Record_Play)->SetWindowText("ֹͣ����");
		
	}else{
		SSHChannel->Write("pkill -9 aplay\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		play_record_flag = false;
		this->GetDlgItem(IDC_BUTTON_Record_Play)->SetWindowText("����¼��");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonPlayaudio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_PlayAudio)->GetWindowText(str);
	if(str == "��������"){
		//���������߳�		
		PlayAudioThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayAudioFun, this, 0, &PlayAudioThreadID);
		if(NULL == PlayAudioThread){
			MessageBox(_T("create PlayAudioThread  failed"));
			return;
		}
		play_audio_flag = true;
		this->GetDlgItem(IDC_BUTTON_PlayAudio)->SetWindowText("ֹͣ����");
	}else{
		SSHChannel->Write("pkill -9 mpg123\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		play_audio_flag = false;
		this->GetDlgItem(IDC_BUTTON_PlayAudio)->SetWindowText("��������");
	}
}
void CRabbitProductTestToolDlg::OnBnClickedButtonLeftchannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_LeftChannel)->GetWindowText(str);
	if(str == "������"){
		PlayLeftChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayLeftChannelFun, this, 0, &PlayLeftChannelThreadID);
		if(NULL == PlayLeftChannelThread){
			MessageBox(_T("create PlayLeftChannelThread  failed"));
			return;
		}
		play_left_channel_flag = true;
		this->GetDlgItem(IDC_BUTTON_LeftChannel)->SetWindowText("�ر�");
	}else{
		SSHChannel->Write("pkill -9 aplay\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		play_left_channel_flag = false;
		this->GetDlgItem(IDC_BUTTON_LeftChannel)->SetWindowText("������");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonRightchannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_RightChannel)->GetWindowText(str);
	if(str == "������"){
		PlayRightChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayRightChannelFun, this, 0, &PlayRightChannelThreadID);
		if(NULL == PlayRightChannelThread){
			MessageBox(_T("create PlayLeftChannelThread  failed"));
			return;
		}
		play_right_channel_flag = true;
		this->GetDlgItem(IDC_BUTTON_RightChannel)->SetWindowText("�ر�");
	}else{
		SSHChannel->Write("pkill -9 aplay\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		play_right_channel_flag = false;
		this->GetDlgItem(IDC_BUTTON_RightChannel)->SetWindowText("������");
	}
}
//��ֱ��
void CRabbitProductTestToolDlg::OnBnClickedButtonCameraplay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("δ�����豸,�޷�ִ��"));
		return -1;
	}
	if(flag != &red_flag && red_flag){
		MessageBox("���ȹرպ�ƣ�������ܻ�Ӱ����Խ��");
		return -2;
	}
	if(flag != &green_flag && green_flag){
		MessageBox("���ȹر��̵ƣ�������ܻ�Ӱ����Խ��");
		return -3;
	}
	if(flag != &blue_flag && blue_flag){
		MessageBox("���ȹر����ƣ�������ܻ�Ӱ����Խ��");
		return -4;
	}
	if(flag != &camera0_flag && camera0_flag){
		MessageBox("���ڲ���Camera0,���Ե�");
		return -5;
	}
	if(flag != &camera1_flag && camera1_flag){
		MessageBox("���ڲ���Camera1,���Ե�");
		return -5;
	}
    if(flag != &camera2_flag && camera2_flag){
		MessageBox("���ڲ���Camera2,���Ե�");
		return -5;
	}
	if(flag != &camera3_flag && camera3_flag){
		MessageBox("���ڲ���Camera3,���Ե�");
		return -5;
	}
	if(flag != &open_fan_flag && open_fan_flag){
		MessageBox("���ڲ��Դ򿪷���,���Ե�");
		return -5;
	}
	if(flag != &close_fan_flag && close_fan_flag){
		MessageBox("���ڲ��Թرշ���,���Ե�");
		return -5;
	}
	return 0;
}

//�����־
void CRabbitProductTestToolDlg::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RichEditCtrl_Log.SetSel(0, -1);
	m_RichEditCtrl_Log.SetWindowText("");
}

//�������
void CRabbitProductTestToolDlg::OnBnClickedButtonDistance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Distance)->GetWindowText(str);
	if(str == "�������"){
		distance_flag = true;
		DistanceChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)DistanceTestFun, this, 0, &DistanceChannelThreadID);
		if(NULL == DistanceChannelThread){
			MessageBox(_T("create DistanceChannelThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Distance)->SetWindowText("ֹͣ����");
	}else{
		distance_flag = false;
		SSHChannel->Write("killall Test_read_range\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Distance)->SetWindowText("�������");
		this->GetDlgItem(IDC_STATIC_DistanceLeft)->SetWindowTextA("0");
		this->GetDlgItem(IDC_STATIC_DistanceRight)->SetWindowTextA("0");
	}
}

//����1����
void CRabbitProductTestToolDlg::OnBnClickedButtonUart1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Uart1)->GetWindowText(str);
	if(str == "����1����"){
		uart1_flag = true;
		Uart1ChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Uart1TestFun, this, 0, &Uart1ChannelThreadID);
		if(NULL == Uart1ChannelThread){
			MessageBox(_T("create Uart1ChannelThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Uart1)->SetWindowText("ֹͣ����");
	}else{
		uart1_flag = false;
		SSHChannel->Write("killall Test_STM32_UART_BY_TX1\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Uart1)->SetWindowText("����1����");
	}
}

//����2����
void CRabbitProductTestToolDlg::OnBnClickedButtonUart2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Uart2)->GetWindowText(str);
	if(str == "����2����"){
		uart2_flag = true;
		Uart2ChannelThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Uart2TestFun, this, 0, &Uart2ChannelThreadID);
		if(NULL == Uart2ChannelThread){
			MessageBox(_T("create Uart1ChannelThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Uart2)->SetWindowText("ֹͣ����");
	}else{
		uart2_flag = false;
		SSHChannel->Write("killall Test_STM32_UART_BY_TX1\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Uart2)->SetWindowText("����2����");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLightsensor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("��ȡ����ʧ�ܣ�������"));
		return;
	}
	string tmpStr0 = str.substr(pos1, str.length() - pos1);
	pos1 = tmpStr0.find("\n");
	if(pos1 == string::npos){
		MessageBox(_T("��ȡ����ʧ�ܣ�������"));
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
		MessageBox(_T("û�л�ȡ������ֵ��������"));
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonPir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Pir)->GetWindowText(str);
	if(str == "�����Ӧ����"){
		test_pir_flag = true;
		TestPirThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)TestPirFun, this, 0, &TestPirThreadID);
		if(NULL == TestPirThread){
			MessageBox(_T("create TestPirThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Pir)->SetWindowText("ֹͣ����");
	}else{
		test_pir_flag = false;
		SSHChannel->Write("killall test_pir\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Pir)->SetWindowText("�����Ӧ����");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonGetpressure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_GetPressure)->GetWindowText(str);
	if(str == "��ȡѹ��ֵ"){
		get_pressure_flag = true;
		GetPressureThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)GetPRessureFun, this, 0, &GetPressureThreadID);
		if(NULL == GetPressureThread){
			MessageBox(_T("create GetPressureThread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_GetPressure)->SetWindowText("ֹͣ����");
	}else{
		get_pressure_flag = false;
		SSHChannel->Write("killall Test_Get_Pressure_diff\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_GetPressure)->SetWindowText("��ȡѹ��ֵ");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonCamera0()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int ret = SafeFun(&camera0_flag);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Camera0)->GetWindowText(str);
	if(str == "Camera0����"){
		camera0_flag = true;
		Camera0Thread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Camera0TestFun, this, 0, &Camera0ThreadID);
		if(NULL == Camera0Thread){
			MessageBox(_T("create Camera0Thread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Camera0)->SetWindowText("ֹͣ����");
	}else{
		camera0_flag = false;
		SSHChannel->Write("killall save_raw_image\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Camera0)->SetWindowText("Camera0����");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonCamera1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(&camera1_flag);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Camera1)->GetWindowText(str);
	if(str == "Camera1����"){
		camera1_flag = true;
		Camera1Thread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Camera1TestFun, this, 0, &Camera1ThreadID);
		if(NULL == Camera1Thread){
			MessageBox(_T("create Camera1Thread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Camera1)->SetWindowText("ֹͣ����");
	}else{
		camera1_flag = false;
		SSHChannel->Write("killall save_raw_image\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Camera1)->SetWindowText("Camera1����");
	}
}


void CRabbitProductTestToolDlg::OnBnClickedButtonCamera2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(&camera2_flag);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Camera2)->GetWindowText(str);
	if(str == "Camera2����"){
		camera2_flag = true;
		Camera2Thread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Camera2TestFun, this, 0, &Camera2ThreadID);
		if(NULL == Camera2Thread){
			MessageBox(_T("create Camera2Thread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Camera2)->SetWindowText("ֹͣ����");
	}else{
		camera2_flag = false;
		SSHChannel->Write("killall save_raw_image\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Camera2)->SetWindowText("Camera2����");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonCamera3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = SafeFun(&camera3_flag);
	if(ret != 0){
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Camera3)->GetWindowText(str);
	if(str == "Camera3����"){
		camera3_flag = true;
		Camera3Thread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Camera3TestFun, this, 0, &Camera3ThreadID);
		if(NULL == Camera3Thread){
			MessageBox(_T("create Camera3Thread  failed"));
			return;
		}
		this->GetDlgItem(IDC_BUTTON_Camera3)->SetWindowText("ֹͣ����");
	}else{
		camera3_flag = false;
		SSHChannel->Write("killall save_raw_image\n"); 
		if(m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
		}
		this->GetDlgItem(IDC_BUTTON_Camera3)->SetWindowText("Camera3����");
	}
}

void CRabbitProductTestToolDlg::OnBnClickedButtonLedAllNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
