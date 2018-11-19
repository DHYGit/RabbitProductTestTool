// UpgradeDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "RabbitProductTestTool.h"
#include "UpgradeDlg.h"
#include "ProThreadFun.h"
#include "afxdialogex.h"
#include "Ssh2.h"
#include <conio.h>
#include <direct.h>
#include <iostream>
#include <string.h>

using namespace std;

// UpgradeDlg �Ի���

IMPLEMENT_DYNAMIC(UpgradeDlg, CDialogEx)

UpgradeDlg::UpgradeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(UpgradeDlg::IDD, pParent)
{
	UploadStatus = 0;
}

UpgradeDlg::~UpgradeDlg()
{

}

void UpgradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditCtrl_Upgrade);
}

BEGIN_MESSAGE_MAP(UpgradeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Open, &UpgradeDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_Upload, &UpgradeDlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_Tar, &UpgradeDlg::OnBnClickedButtonTar)
	ON_BN_CLICKED(IDC_BUTTON_ClearLog, &UpgradeDlg::OnBnClickedButtonClearlog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
// UpgradeDlg ��Ϣ�������
void UpgradeDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString szFilter = _T("All Files (*.*)|*.*|avi Files (*.avi)|*.avi|rmvb Files (*.rmvb)|*.rmvb|3gp Files (*.3gp)|*.3gp|mp3 Files (*.mp3)|*.mp3|mp4 Files (*.mp4)|*.mp4|mpeg Files (*.ts)|*.ts|flv Files (*.flv)|*.flv|mov Files (*.mov)|*.mov||");
	CFileDialog OpenDlg(TRUE,NULL ,NULL,OFN_PATHMUSTEXIST|OFN_HIDEREADONLY ,szFilter,NULL); 
	if(IDOK == OpenDlg.DoModal()){
		//����Դ�ļ�
		m_FileName = OpenDlg.GetPathName();		
		//�༭����ʾ�ļ�·��
		this->GetDlgItem(IDC_EDIT_UpgradeFile)->SetWindowText(this->m_FileName);
		UploadStatus = 0;
		UpdateData(FALSE);
	}
}

void UpgradeDlg::OnBnClickedButtonUpload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_FileName == ""){
		MessageBox(_T("���Ҫ�ϴ����ļ�"));
		return;
	}
	//��ȡ��ǰ����·��
	char currentPath[MAX_PATH];
	getcwd(currentPath, MAX_PATH);
	cprintf( "The   current   directory   is:   %s \n",   currentPath);
	string commond =  currentPath;
	string ip = CString2stringMultibyte(hostIP);
	string filePath = CString2stringMultibyte(m_FileName);
	int pos = filePath.find("hardware_test");
	if(pos != std::string::npos){
		fileName = filePath.substr(pos, filePath.length() - pos);
	}else{
		fileName = "hardware_test.tar.gz";
	}
	if(pDlg->m_CheckVersion.GetCheck()){
		commond += "\\PSCP.EXE -l nvidia -pw \"nvidia\" ";
	    commond += filePath;
	    commond += " nvidia@";
	    commond += ip;
	    commond += ":/home/nvidia/";
		commond += fileName;
	}else{
		SSHChannel->Write("sudo chmod 777 /home/ubuntu\n"); 
		if(m_OpenConsole->GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		SSHChannel->Write("ubuntu\n"); 
		if(m_OpenConsole->GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		commond += "\\PSCP.EXE -l ubuntu -pw \"ubuntu\" ";
	    commond += filePath;
	    commond += " ubuntu@";
	    commond += ip;
	    commond += ":/home/ubuntu/";
	    commond += fileName;
	}
	cprintf( "commond  is:   %s \n", commond.c_str());
	//�ϴ��ļ���/home/ubuntu/
	int n = system(commond.c_str());
	if(n == 0){
		UploadStatus = 1;
	}
	if(!pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("sudo chmod 755 /home/ubuntu\n"); 
		
	}
	if(m_OpenConsole->GetCheck()){
		cprintf("%s \n", SSHChannel->Read().c_str());
	}
}

void UpgradeDlg::OnBnClickedButtonTar()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(UploadStatus != 1){
		MessageBox(_T("�����ϴ��������ļ�"));
		return;
	}
	CString str;
	this->GetDlgItem(IDC_BUTTON_Tar)->GetWindowText(str);
	if("��ѹ����" == str){
	    this->over_flag = false;
		this->open_flag = true;
	    TarAndUpgradeThread = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)TarAndUpgradeFun, this, 0, &TarAndUpgradeThreadID);
	    if(NULL == TarAndUpgradeThread){
		    MessageBox(_T("create TarAndUpgradeThread  failed"));
		    return;
	    }
		this->GetDlgItem(IDC_BUTTON_Tar)->SetWindowText("ֹͣ");
	}else{
		this->over_flag = true;
		this->open_flag = false;
		this->GetDlgItem(IDC_BUTTON_Tar)->SetWindowText("��ѹ����");
	}
}

void UpgradeDlg::OnBnClickedButtonClearlog()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RichEditCtrl_Upgrade.SetSel(0, -1);
	m_RichEditCtrl_Upgrade.SetWindowText("");
}

void UpgradeDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	open_flag = false;
	if(!over_flag){
		return ;
	}
	CDialogEx::OnClose();
}
