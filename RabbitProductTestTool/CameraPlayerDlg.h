#pragma once
#include "FFmpegTool.h"
#include "MyUDP.h"
#include "RabbitProductTestToolDlg.h"
#include "afxwin.h"

// CameraPlayerDlg 对话框

class CameraPlayerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CameraPlayerDlg)

public:
	CameraPlayerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CameraPlayerDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

public:
	CRabbitProductTestToolDlg *pDlg;
	FFmpegClass *ffmpeg;
	FFmpegClass *ffmpeg_stitch;
	CMyUDP myUDP;
	string ip;
	int sec_num;
	int restart_num;
	bool get_data;
	int restart_step;
	string user;
	string pass;
	int static_width;
	int static_height;
    CString dstIP;
	bool play_flag0, play_flag1, play_flag2, play_flag3, play_flag_stitch;
	int lostPacketNum;
	int currentLostNum;
	int play_cam_num;
	int InitFFmpeg();
	int InitSDL();
	int CloseCamera();
	void InitUDP();
	int  SafeFun(bool *flag);
	int Excute();
	int timerFun();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Static_player;
	afx_msg void OnBnClickedButtonCamera0play();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonCamera1play();
	afx_msg void OnBnClickedButtonCamera2play();
	afx_msg void OnBnClickedButtonCamera3play();
	afx_msg void OnBnClickedButtonStitch();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
