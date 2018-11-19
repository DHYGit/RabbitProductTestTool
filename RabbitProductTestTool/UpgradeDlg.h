#pragma once
#include "Ssh2.h"
#include "afxcmn.h"
#include "RabbitProductTestToolDlg.h"

// UpgradeDlg �Ի���

class UpgradeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpgradeDlg)

public:
	UpgradeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~UpgradeDlg();

// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonUpload();
	afx_msg void OnBnClickedButtonTar();
	CRichEditCtrl m_RichEditCtrl_Upgrade;
	afx_msg void OnBnClickedButtonClearlog();
	afx_msg void OnClose();
};
