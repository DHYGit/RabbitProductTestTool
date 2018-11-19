#pragma once
#include "Ssh2.h"
#include "afxcmn.h"
#include "RabbitProductTestToolDlg.h"

// UpgradeDlg 对话框

class UpgradeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpgradeDlg)

public:
	UpgradeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UpgradeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };
public:
	CString m_FileName;
	Channel* SSHChannel;
	CButton *m_OpenConsole;
	CString hostIP;
	string ip;
	string user;
	string pass;
	string fileName;
	int UploadStatus;
	CRabbitProductTestToolDlg *pDlg;
	bool open_flag, over_flag;
	HANDLE TarAndUpgradeThread;
	DWORD TarAndUpgradeThreadID;
    
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonUpload();
	afx_msg void OnBnClickedButtonTar();
	CRichEditCtrl m_RichEditCtrl_Upgrade;
	afx_msg void OnBnClickedButtonClearlog();
	afx_msg void OnClose();
};
