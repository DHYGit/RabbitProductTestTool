
// RabbitProductTestToolDlg.h : 头文件
//

#pragma once

#include "Ssh2.h"
#include "afxwin.h"
#include "afxcmn.h"

// CRabbitProductTestToolDlg 对话框
class CRabbitProductTestToolDlg : public CDialogEx
{
// 构造
public:
	CRabbitProductTestToolDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_RABBITPRODUCTTESTTOOL_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	CString hostIP;
	CString username;
	CString password;
	string ip;
	string user;
	string pass;
	Ssh2 *ssh;
	Channel *SSHChannel;
	Channel *MotorChannel;
	Channel *RotateMotorChannel;
	Channel *GasChannel;
	Channel *Uart1Channel;
	Channel *Uart2Channel;
	Channel *ExcuteChannel;

	int ConnectStatus;
 
	bool red_flag, blue_flag, green_flag;
	bool motor_flag, rotate_flag, stream_flag, gas_flag, open_fan_flag, close_fan_flag;
	bool distance_flag, uart1_flag, uart2_flag;
	bool record_flag, play_record_flag;
	bool play_audio_flag, play_left_channel_flag, play_right_channel_flag;
	bool test_pir_flag, get_pressure_flag;
	bool camera0_flag, camera1_flag, camera2_flag, camera3_flag;

	HANDLE ExcuteThread;
	DWORD ExcuteThreadID;

	HANDLE LEDStreamThread;
	DWORD LEDStreamThreadID;

	HANDLE UpgradeSHThread;
	DWORD UpgradeSHThreadID;

	HANDLE PlayAudioThread;
	DWORD PlayAudioThreadID;
	
	HANDLE PlayLeftChannelThread;
	DWORD PlayLeftChannelThreadID;

	HANDLE PlayRightChannelThread;
	DWORD PlayRightChannelThreadID;

	HANDLE RecordThread;
	DWORD RecordThreadID;

	HANDLE PlayRecordThread;
	DWORD PlayRecordThreadID;

	HANDLE DistanceChannelThread;
	DWORD DistanceChannelThreadID;

	HANDLE Uart1ChannelThread;
	DWORD Uart1ChannelThreadID;

	HANDLE Uart2ChannelThread;
	DWORD Uart2ChannelThreadID;

	HANDLE TestPirThread;
	DWORD TestPirThreadID;

	HANDLE GetPressureThread;
	DWORD GetPressureThreadID;

	HANDLE Camera0Thread;
	DWORD Camera0ThreadID;

	HANDLE Camera1Thread;
	DWORD Camera1ThreadID;

	HANDLE Camera2Thread;
	DWORD Camera2ThreadID;

	HANDLE Camera3Thread;
	DWORD Camera3ThreadID;

	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool AllisNum(string str);

	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonExcute();
	afx_msg void OnBnClickedButtonLecWarm();
	afx_msg void OnBnClickedButtonLedCool();
	afx_msg void OnBnClickedButtonLedOff();
	afx_msg void OnBnClickedButtonPlayaudio();
	afx_msg void OnBnClickedButtonUpgrade();
	afx_msg void OnBnClickedCheckOpenconsole();
	CButton m_OpenConsole;
	afx_msg void OnBnClickedButtonLedRed();
	void BaseExcute(Channel *channel, string commond);
	int SafeFun(bool *flag);
	afx_msg void OnBnClickedButtonLedGreen();
	afx_msg void OnBnClickedButtonLedBlue();
	afx_msg void OnBnClickedButtonLeftchannel();
	afx_msg void OnBnClickedButtonRightchannel();
	afx_msg void OnBnClickedButtonLedAll();

	afx_msg void OnBnClickedButtonSoundOff();
	afx_msg void OnBnClickedButtonVolumeDown();
	afx_msg void OnBnClickedButtonVolumeUp();
	afx_msg void OnBnClickedButtonVolumeMax();
	afx_msg void OnBnClickedButtonMotorcontrol();
	afx_msg void OnBnClickedButtonMotorleft();
	afx_msg void OnBnClickedButtonMotorright();
	afx_msg void OnBnClickedButtonMotorstop();
	afx_msg void OnBnClickedButtonLedStream();
	afx_msg void OnBnClickedButtonGascontrol();
	afx_msg void OnBnClickedButtonGasopen();
	afx_msg void OnBnClickedButtonGasclose();
	afx_msg void OnBnClickedButtonFancontrol();
	afx_msg void OnBnClickedButtonRotatemotorcontrol();
	afx_msg void OnBnClickedButtonRotateleft();
	afx_msg void OnBnClickedButtonRotateright();
	afx_msg void OnBnClickedButtonRotatestop();
	afx_msg void OnBnClickedButtonRecordStart();
	afx_msg void OnBnClickedButtonRecordPlay();
	afx_msg void OnBnClickedButtonClear();
	CRichEditCtrl m_RichEditCtrl_Log;
	afx_msg void OnBnClickedButtonDistance();
	afx_msg void OnBnClickedButtonUart1();
	afx_msg void OnBnClickedButtonUart2();
	afx_msg void OnBnClickedButtonUpgradesh();
	afx_msg void OnBnClickedButtonLightsensor();
	afx_msg void OnBnClickedButtonPir();
	afx_msg void OnBnClickedButtonGetpressure();
	afx_msg void OnBnClickedButtonCamera0();
	afx_msg void OnBnClickedButtonCamera1();
	afx_msg void OnBnClickedButtonCamera2();
	afx_msg void OnBnClickedButtonCamera3();
	afx_msg void OnBnClickedButtonMotorcircletest();
	afx_msg void OnBnClickedButtonLedAllNew();
	afx_msg void OnBnClickedButtonCameraplay();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButtonClosefan();
	CButton m_CheckVersion;
	afx_msg void OnBnClickedCheckVersion();
};
