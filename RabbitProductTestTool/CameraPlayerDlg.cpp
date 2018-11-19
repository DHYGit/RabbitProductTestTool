// CameraPlayerDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "RabbitProductTestTool.h"
#include "CameraPlayerDlg.h"
#include "afxdialogex.h"
#include "ProThreadFun.h"
#include <conio.h>
#define RTPLENGTH 1400

// CameraPlayerDlg 对话框

IMPLEMENT_DYNAMIC(CameraPlayerDlg, CDialogEx)

CameraPlayerDlg::CameraPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CameraPlayerDlg::IDD, pParent)
{
	
}

int CameraPlayerDlg::InitFFmpeg(){
	ffmpeg = new FFmpegClass();
	ffmpeg->FFmpeg_Init();
	ffmpeg_stitch = new FFmpegClass();
	ffmpeg_stitch->FFmpeg_Init();
	return 0;
}

int CameraPlayerDlg::InitSDL(){
	HWND hWnd = m_Static_player.GetSafeHwnd();
	if (hWnd != NULL) {
		char sdl_var[64];
		sprintf_s(sdl_var, "SDL_WINDOWID=%d", hWnd); //这里一定不能有空格SDL_WINDOWID=%d"
		SDL_putenv(sdl_var);
		char *myvalue = SDL_getenv("SDL_WINDOWID");//让SDL获取窗口ID
	}
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("不能初始化SDL--%s\n", SDL_GetError());
		return -1;
	}
	//设置SDL事件状态
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
	SDL_EventState(SDL_USEREVENT, SDL_IGNORE);
	//获取Static控件的宽度和高度
	CRect rect;
	m_Static_player.GetClientRect(&rect);
	static_width = rect.Width();
	static_height = rect.Height();
	ffmpeg->screen = SDL_SetVideoMode(static_width, static_height, 0, 0);
	if (!ffmpeg->screen){
		printf("SDL: could not set video mode -exiting \n");
		return -1;
	}
	ffmpeg_stitch->screen = SDL_SetVideoMode(static_width, static_height, 0, 0);
	if (!ffmpeg->screen){
		printf("SDL: could not set video mode -exiting \n");
		return -1;
	}
	return 0;
}
CameraPlayerDlg::~CameraPlayerDlg()
{
}

void CameraPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Player, m_Static_player);
	InitFFmpeg();
	InitSDL();
	//打开key.h264
	int n = ffmpeg->FFmpeg_openFile("key.h264");
	if(n != 0){
		MessageBox(_T("打开key.h264失败，请重试"));
		return;
	}
	ffmpeg->bmp = SDL_CreateYUVOverlay(ffmpeg->pCodecCtx_In->width, ffmpeg->pCodecCtx_In->height, SDL_YV12_OVERLAY, ffmpeg->screen);
	av_new_packet(ffmpeg->packet, ffmpeg->y_size);	
	n = ffmpeg_stitch->FFmpeg_openFile("stitchkey.h264");
	if(n != 0){
		MessageBox(_T("打开stitchkey.h264失败，请重试"));
		return;
	}
	ffmpeg_stitch->bmp = SDL_CreateYUVOverlay(ffmpeg_stitch->pCodecCtx_In->width, ffmpeg_stitch->pCodecCtx_In->height, SDL_YV12_OVERLAY, ffmpeg_stitch->screen);
	av_new_packet(ffmpeg_stitch->packet, ffmpeg_stitch->y_size);
	play_flag0 = false;
	play_flag1 = false;
	play_flag2 = false;
	play_flag3 = false;
	play_flag_stitch = false;
	get_data = false;
	play_cam_num = -1;
	sec_num = 0;
	restart_num = 0;
	restart_step = 0;
	SetTimer(1, 1000, NULL);
}

BEGIN_MESSAGE_MAP(CameraPlayerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Camera0Play, &CameraPlayerDlg::OnBnClickedButtonCamera0play)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_Camera1Play, &CameraPlayerDlg::OnBnClickedButtonCamera1play)
	ON_BN_CLICKED(IDC_BUTTON_Camera2Play, &CameraPlayerDlg::OnBnClickedButtonCamera2play)
	ON_BN_CLICKED(IDC_BUTTON_Camera3Play, &CameraPlayerDlg::OnBnClickedButtonCamera3play)
	ON_BN_CLICKED(IDC_BUTTON_Stitch, &CameraPlayerDlg::OnBnClickedButtonStitch)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CameraPlayerDlg 消息处理程序

void CameraPlayerDlg::InitUDP() {
	myUDP.Init(dstIP.GetBuffer(dstIP.GetLength()), 7078, 7098);
	this->lostPacketNum = 0;
}

void CameraPlayerDlg::OnBnClickedButtonCamera0play()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&play_flag0);
	if(ret != 0){
		return;
	}
	CString cstr;
	this->GetDlgItem(IDC_BUTTON_Camera0Play)->GetWindowTextA(cstr);
	if(cstr == "Camera0"){
	 	int ret = Excute();
		if(ret != 0){
			return;
		}
		play_cam_num = 0;
		play_flag0 = true;
		this->GetDlgItem(IDC_BUTTON_Camera0Play)->SetWindowTextA("关闭");
	}else{
		play_cam_num = -1;
		play_flag0 = false;
		Sleep(300);
		CloseCamera();
		this->GetDlgItem(IDC_BUTTON_Camera0Play)->SetWindowTextA("Camera0");
	}
}

void CameraPlayerDlg::OnBnClickedButtonCamera1play()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&play_flag1);
	if(ret != 0){
		return;
	}
	CString cstr;
	this->GetDlgItem(IDC_BUTTON_Camera1Play)->GetWindowTextA(cstr);
	if(cstr == "Camera1"){
		int ret = Excute();
		if(ret != 0){
			return ;
		}
		play_cam_num = 1;
		play_flag1 = true;	
		this->GetDlgItem(IDC_BUTTON_Camera1Play)->SetWindowTextA("关闭");
	}else{
		play_cam_num = -1;
		play_flag1 = false;
		Sleep(100);
		CloseCamera();
		this->GetDlgItem(IDC_BUTTON_Camera1Play)->SetWindowTextA("Camera1");
	}
}

void CameraPlayerDlg::OnBnClickedButtonCamera2play()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&play_flag2);
	if(ret != 0){
		return;
	}
	CString cstr;
	this->GetDlgItem(IDC_BUTTON_Camera2Play)->GetWindowTextA(cstr);
	if(cstr == "Camera2"){
		int ret = Excute();
		if(ret != 0){
			return;
		}
		play_cam_num = 2;
		play_flag2 = true;
		this->GetDlgItem(IDC_BUTTON_Camera2Play)->SetWindowTextA("关闭");
	}else{
		play_cam_num = -1;
		play_flag2 = false;
		Sleep(100);
		CloseCamera();
		this->GetDlgItem(IDC_BUTTON_Camera2Play)->SetWindowTextA("Camera2");
	}
}

void CameraPlayerDlg::OnBnClickedButtonCamera3play()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&play_flag3);
	if(ret != 0){
		return;
	}
	CString cstr;
	this->GetDlgItem(IDC_BUTTON_Camera3Play)->GetWindowTextA(cstr);
	if(cstr == "Camera3"){
		int ret = Excute();
		if(ret != 0){
			return;
		}
		play_cam_num = 3;
		play_flag3 = true;
		this->GetDlgItem(IDC_BUTTON_Camera3Play)->SetWindowTextA("关闭");
	}else{
		play_cam_num = -1;
		play_flag3 = false;
		Sleep(100);
		CloseCamera(); 
		this->GetDlgItem(IDC_BUTTON_Camera3Play)->SetWindowTextA("Camera3");
	}
}

void CameraPlayerDlg::OnBnClickedButtonStitch()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = SafeFun(&play_flag_stitch);
	if(ret != 0){
		return;
	}
	CString cstr;
	this->GetDlgItem(IDC_BUTTON_Stitch)->GetWindowTextA(cstr);
	if(cstr == "合成画面"){
		int ret = Excute();
		if(ret != 0){
			return;
		}
		play_cam_num = 4;
		play_flag_stitch = true;
		this->GetDlgItem(IDC_BUTTON_Stitch)->SetWindowTextA("关闭");
	}else{
		play_cam_num = -1;
		play_flag_stitch = false;
		Sleep(100);
		CloseCamera(); 
		this->GetDlgItem(IDC_BUTTON_Stitch)->SetWindowTextA("合成画面");
	}
}

int CameraPlayerDlg::Excute(){
	//InitUDP
	//get_data = false;
	//sec_num = 0;
	InitUDP();
	//创建执行直播脚本并获取日志线程
	HANDLE CameraPlayThread;
	DWORD CameraPlayThreadID;
	CameraPlayThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)CameraPlayFun, this, 0, &CameraPlayThreadID);
	if(NULL == CameraPlayThread){
		MessageBox(_T("create CameraPlayThread  failed"));
		return -1;
	}
	//创建接收数据线程
	HANDLE ReceiveDataThread;
	DWORD ReceiveDataThreadID;

	ReceiveDataThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)ReceiveUDPDataAndPlayWithoutCache, this, 0, &ReceiveDataThreadID);
	if(NULL == ReceiveDataThread){
		MessageBox(_T("create ReceiveDataThread  failed"));
		return -2;
	}
	
	//创建播放线程
	/*
	HANDLE PlayThread;
	DWORD PlayThreadID;
	PlayThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)PlayThreadFun, this, 0, &PlayThreadID);
	if(NULL == PlayThread){
		MessageBox(_T("create PlayThread  failed"));
		return -3;
	}*/
	return 0;
}

int CameraPlayerDlg::CloseCamera(){
	//restart_flag = false;
	get_data = false;
	sec_num = 0;
	Ssh2 *ssh = new Ssh2(ip);
	bool ret = ssh->Connect(user, pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	if(play_cam_num != 4){
	    SSHChannel->Write("killall CameraPlay\n"); 
	}else{
		SSHChannel->Write("killall stitch_live\n");
	}
	Sleep(500);
	ssh->Disconnect();
	myUDP.Quit();
	SDL_Surface *img = SDL_LoadBMP("background.bmp");
	SDL_BlitSurface( img, NULL, ffmpeg->screen, NULL );
	SDL_Flip( ffmpeg->screen);
	SDL_FreeSurface(img);
	return 0;
}


void CameraPlayerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int ret = SafeFun(NULL);
	if(ret != 0){
		return;
	}
	SDL_VideoQuit();
	//SDL_FreeSurface(ffmpeg->screen);
	SDL_Quit();
	myUDP.Quit();
	get_data = false;
	sec_num = 0;
	KillTimer(1);
	CDialogEx::OnClose();
}

int  CameraPlayerDlg::SafeFun(bool *flag){
	if(flag != &play_flag0 && play_flag0){
		MessageBox("请先关闭Camera0");
		return -2;
	}
	if(flag != &play_flag1 && play_flag1){
		MessageBox("请先关闭Camera1");
		return -3;
	}
	if(flag != &play_flag2 && play_flag2){
		MessageBox("请先关闭Camera2");
		return -4;
	}
	if(flag != &play_flag3 && play_flag3){
		MessageBox("请先关闭Camera3");
		return -5;
	}
	if(flag != &play_flag_stitch && play_flag_stitch){
		MessageBox("请先关闭合成画面");
		return -5;
	}

	return  0;
}

void CameraPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(play_cam_num != -1 && play_cam_num != 4){
		if(get_data){
			sec_num = 0;
			restart_num = 0;
			restart_step = 0;
			return;
		}else{
			if(sec_num < 6){
				sec_num++;
			}else if(sec_num >= 6 ){
				sec_num = 0;
				if(restart_step == 0){//重启
					restart_step = 1;
					restart_num++;
				}
			}
			if(restart_step == 1){//关闭当前播放任务
				if(play_cam_num == 0){
					play_flag0 = false;
				}else if(play_cam_num == 1){
					play_flag1 = false;
				}else  if(play_cam_num == 2){
					play_flag2 = false;
			 	}else if(play_cam_num == 3){
					play_flag3 = false;
				}
				CloseCamera();
				restart_step = 2;
			}else if(sec_num >= 4 && restart_step == 2){
				sec_num = 0;
				get_data = false;
				restart_step = 3;
				if(play_cam_num == 0){
					play_flag0 = true;
				}else if(play_cam_num == 1){
					play_flag1 = true;
				}else  if(play_cam_num == 2){
					play_flag2 = true;
				}else if(play_cam_num == 3){
					play_flag3 = true;
				}
				Sleep(100);
				Excute();
				restart_step = 0;
			}
		}
		if(restart_num > 3){
			restart_num = 0;
			play_cam_num = -1;
			if(play_flag0 == true){
				play_flag0 = false;
				this->GetDlgItem(IDC_BUTTON_Camera3Play)->SetWindowTextA("Camera0");
			}else if(play_flag1 == true){
				play_flag1 = false;
				this->GetDlgItem(IDC_BUTTON_Camera3Play)->SetWindowTextA("Camera1");
			}else if(play_flag2 == true){
				play_flag2 = false;
				this->GetDlgItem(IDC_BUTTON_Camera3Play)->SetWindowTextA("Camera2");
			}else if(play_flag3 == true){
				play_flag3 = false;
				this->GetDlgItem(IDC_BUTTON_Camera3Play)->SetWindowTextA("Camera3");
			}
			Sleep(100);
			CloseCamera(); 
			MessageBox(_T("打开摄像头失败"));
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
