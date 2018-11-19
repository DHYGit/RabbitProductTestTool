#include "ProThreadFun.h"
#include "ProTestSHName.h"
#include "RabbitProductTestTool.h"
#include "RabbitProductTestToolDlg.h"
#include "CameraPlayerDlg.h"
#include "UpgradeDlg.h"
#include <iostream>
#include <queue>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <direct.h>
#include <fstream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 

using namespace std;
using namespace cv;

int ExcuteFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	CString commond;
	pDlg->GetDlgItem(IDC_EDIT_Commond)->GetWindowText(commond);
	string commond_str = CString2stringMultibyte(commond);
	string t = "\n";
	commond_str += t;
	pDlg->ExcuteChannel->Write(commond_str); 
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", pDlg->ExcuteChannel->Read().c_str());
	}
	bool flag = true;
	while(flag){
		string str = pDlg->ExcuteChannel->Read();

		if((str.length() >= 2 ) && (str.at(str.length() - 2) == '#')){	
	        flag = false;		
		}
		if((str.length() >= 1)&& (str.at(str.length() - 1) == '\n')){
			flag = false;
		}
		if(str == ""){
			flag = false;
		}
		//str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	//pDlg->MessageBoxA(_T("执行完毕"));
	return 0;
}

int LEDStreamFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*StreamChannel = ssh->CreateChannel();
	//pDlg->BaseExcute(StreamChannel, "/home/ubuntu/hardware_test/28_Test_single_led.sh\n");
	if(pDlg->m_CheckVersion.GetCheck()){
		pDlg->BaseExcute(StreamChannel, STREAM_LED_28);
	}
	else{
		pDlg->BaseExcute(StreamChannel, STREAM_LED);
	}
	Sleep(10);
	while(pDlg->stream_flag){
		Sleep(1);
		string str = StreamChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	ssh->Disconnect();
	return 0;
}

int UpgradeSHFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	if(pDlg->m_CheckVersion.GetCheck()){
		pDlg->BaseExcute(SSHChannel, UPGRADE_SH_28);
	}else{
		pDlg->BaseExcute(SSHChannel, UPGRADE_SH);
	}
	Sleep(10);
	while(1){
		string str = SSHChannel->Read();
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if(str.find("password for") != string::npos){
			SSHChannel->Write("ubuntu\n"); 
		}
		string lastStr = "/hardware_test$ \n";
		if(str.size() > lastStr.size()){
			string stri = str.substr(str.size() - lastStr.size());
			if(stri.find("/hardware_test$") != string::npos){
				Sleep(100);
				SSHChannel->Write("sudo reboot\n");
				break;
			}
		}
	}
	ssh->Disconnect();
	pDlg->OnBnClickedButtonConnect();
	pDlg->MessageBox(_T("升级完毕"));
	return 0;
}

int TarAndUpgradeFun(LPVOID pM){
	UpgradeDlg *pDlg = (UpgradeDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	//解压
	if(pDlg->open_flag){
		string commond;
		if(pDlg->pDlg->m_CheckVersion.GetCheck()){
			SSHChannel->Write("cd /home/nvidia/\n");
			if(pDlg->m_OpenConsole->GetCheck()){
				cprintf("%s \n", SSHChannel->Read().c_str());
			}
			commond = "sudo tar zxvf /home/nvidia/";
			commond += pDlg->fileName;
			SSHChannel->Write(commond);
			if(pDlg->pDlg->m_OpenConsole.GetCheck()){
				cprintf("%s \n", SSHChannel->Read().c_str());
			}
			SSHChannel->Write("nvidia\n"); 
			if(pDlg->pDlg->m_OpenConsole.GetCheck()){
				cprintf("%s \n", SSHChannel->Read().c_str());
				cprintf("%s \n", commond);
			}
		}else{
			SSHChannel->Write("cd /home/ubuntu/ \n"); 
			commond = "tar zxvf /home/ubuntu/";
			commond += pDlg->fileName;
			SSHChannel->Write(commond); 
		}
		if(pDlg->m_OpenConsole->GetCheck()){
			cprintf("%s \n", commond);
		}
		Sleep(10);
	}
	while(pDlg->open_flag){
		string str = SSHChannel->Read();
		if(pDlg->pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Upgrade.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Upgrade.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Upgrade.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if(str.find("/wenbie_right.wav") != string::npos){
			break;
		}
	}
	Sleep(300);
	if(pDlg->open_flag){
		string dirName;
		string commond;
		int pos = pDlg->fileName.find(".tar");
		if(pos != std::string::npos){
		    dirName = pDlg->fileName.substr(0, pos - 1);
		}else{
			dirName = "hardware_test";
		}
		if(pDlg->pDlg->m_CheckVersion.GetCheck()){
			commond += "mv /home/nvidia/hardware_test /home/nvidia/";
			commond += dirName;
			SSHChannel->Write(commond); 
		}else{
			commond += "mv /home/ubuntu/hardware_test /home/ubuntu/";
			commond += dirName;
			SSHChannel->Write(commond);
		}
		//升级
		if(pDlg->pDlg->m_CheckVersion.GetCheck()){
			pDlg->pDlg->BaseExcute(SSHChannel, UPGRADE_SH_28);
		}else{
			pDlg->pDlg->BaseExcute(SSHChannel, UPGRADE_SH);
		}
	}
	while(pDlg->open_flag){
		string str = SSHChannel->Read();
		str += "\n";
		pDlg->m_RichEditCtrl_Upgrade.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Upgrade.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Upgrade.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if(str.find("password for") != string::npos){
			if(pDlg->pDlg->m_CheckVersion.GetCheck()){
				SSHChannel->Write("nvidia\n"); 
			}else{
			    SSHChannel->Write("ubuntu\n"); 
			}
		}
		string lastStr = "/hardware_test$ \n";
		if(str.size() > lastStr.size()){
			string stri = str.substr(str.size() - lastStr.size());
			if(stri.find("/hardware_test$") != string::npos){
				Sleep(100);
				SSHChannel->Write("sudo reboot\n");
				break;
			}
		}
	}
	ssh->Disconnect();
	if(pDlg->open_flag){
		pDlg->pDlg->OnBnClickedButtonConnect();
		pDlg->MessageBox(_T("升级完毕"));
		Sleep(100);
	}
	pDlg->over_flag = true;
	return 0;
}

int PlayAudioFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n");
	}else{
	    SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n");
	}
	string str;
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(PLAY_AUDIO_28);
	}else{
	    SSHChannel->Write(PLAY_AUDIO);
	}
	 
	Sleep(10);
	while(pDlg->play_audio_flag){
		string str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	SSHChannel->Write("ubuntu\n"); 
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int PlayLeftChannelFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n");
	}else{
	    SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n");
	} 
	string str;
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){		
		cprintf("%s \n", str.c_str());
	}
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(PLAY_LEFT_CHANNEL_28);
	}else{
	    SSHChannel->Write(PLAY_LEFT_CHANNEL);
	}
	Sleep(10);
	string lastStr = "";
	while(pDlg->play_left_channel_flag){
		string str = SSHChannel->Read();
		if('$' == str[str.length() - 2]){
			pDlg->play_left_channel_flag = false;
			pDlg->GetDlgItem(IDC_BUTTON_LeftChannel)->SetWindowText("左声道");
		}
		if(str.c_str() == lastStr.c_str()){
			continue;
		}else{
			lastStr = str;
		}
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if(lastStr.c_str() == ""){
			lastStr = str;
		}
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int PlayRightChannelFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n");
	}else{
	    SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n");
	} 
	string str;
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(PLAY_RIGHT_CHANNEL_28);
	}else{
	    SSHChannel->Write(PLAY_RIGHT_CHANNEL);
	}
	Sleep(10);
	while(pDlg->play_right_channel_flag){
		string str = SSHChannel->Read();
		if('$' == str[str.length() - 2]){
			pDlg->play_right_channel_flag = false;
			pDlg->GetDlgItem(IDC_BUTTON_RightChannel)->SetWindowText("右声道");
		}
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int RecordFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n");
	}else{
	    SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n");
	}
	string str;
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(RECORD_28);
	}else{
	    SSHChannel->Write(RECORD);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("nvidia\n");
	}else{
	    SSHChannel->Write("ubuntu\n");
	}
	Sleep(10);
	while(pDlg->record_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int PlayRecordFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n");
	}else{
	    SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n");
	}
	string str;
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	SSHChannel->Write("aplay -r 16000 -f S16_LE -c 2 Sound_Pi_0.pcm\n");
	Sleep(10);
	while(pDlg->play_record_flag){
		str = SSHChannel->Read();
		if('$' == str[str.length() - 2]){
			pDlg->play_record_flag = false;
			pDlg->GetDlgItem(IDC_BUTTON_Record_Play)->SetWindowText("播放录音");
		}
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int DistanceTestFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(HARDWARE_TEST_PATH_28);
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(DISTANCE_TEST_28);
	}else{
		SSHChannel->Write(HARDWARE_TEST_PATH);
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(DISTANCE_TEST);
	}
	while(pDlg->distance_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		if(str.length() > 10){
			int pos1_left = str.find("tmp1");
			int pos1_right = str.find(",temp2");
			if(pos1_left > 0 && pos1_right > pos1_left){
				string tmp1 = str.substr(pos1_left, pos1_right - pos1_left);
				int pos1 = tmp1.find("=");
				string distance1 = tmp1.substr(pos1+1, tmp1.length() - pos1 - 1);
				string tmp2 = str.substr(pos1_right + 1, str.length() - pos1_right - 1);
				int pos2 = tmp2.find("=");
				string distance2 = tmp2.substr(pos2 + 1, tmp2.length() - pos2 - 1);
				if(distance2.at(distance2.length() - 1) == '\n'){
					distance2 = distance2.substr(0, distance2.length() - 2);
					if(distance2.at(distance2.length() - 1) == '\r'){
						distance2 = distance2.substr(0, distance2.length() - 2);
					}
				}
				if(pDlg->AllisNum(distance1) && pDlg->AllisNum(distance2)){
					pDlg->GetDlgItem(IDC_STATIC_DistanceLeft)->SetWindowTextA(distance1.c_str());
					pDlg->GetDlgItem(IDC_STATIC_DistanceRight)->SetWindowTextA(distance2.c_str());
				}
			}
		
		}
	}
	ssh->Disconnect();
	return 0;
}

int Uart1TestFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(UART1_TEST_28);
	}else{
		SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(UART1_TEST);
	}
	while(pDlg->uart1_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int Uart2TestFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(UART2_TEST_28);
	}else{
		SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(UART2_TEST);
	}
	while(pDlg->uart2_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int TestPirFun(LPVOID pM){
    CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(HARDWARE_TEST_PATH_28);
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(TEST_PIR_28);
	}else{
		SSHChannel->Write(HARDWARE_TEST_PATH);
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(TEST_PIR);
	}
	
	while(pDlg->test_pir_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int GetPRessureFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(HARDWARE_TEST_PATH_28); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(GET_PRESSURE_28);
	}else{
		SSHChannel->Write(HARDWARE_TEST_PATH); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(GET_PRESSURE);
	}
	while(pDlg->get_pressure_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	ssh->Disconnect();
	return 0;
}

int Camera0TestFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	//删除本地的照片
	char *camera_jpg = "camera_0.jpg";
	fstream f;
	f.open(camera_jpg);
	if(f){
		f.close();
		if(remove(camera_jpg) != 0){
			pDlg->MessageBox(_T("删除本地camera_0.jpg失败，请先手动删除"));
			return -1;
		}
	}
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n"); 
	    str = SSHChannel->Read();
	    if(pDlg->m_OpenConsole.GetCheck()){
		    cprintf("%s \n", str.c_str());
	    }
		SSHChannel->Write(SAVE_RAW_IMAGE_0_28);
	}else{
		SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n"); 
	    str = SSHChannel->Read();
	    if(pDlg->m_OpenConsole.GetCheck()){
		    cprintf("%s \n", str.c_str());
	    }
		SSHChannel->Write(SAVE_RAW_IMAGE_0);
	}
	while(pDlg->camera0_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if('$' == str[str.length() - 3]){
			break;
		}
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	//将照片拷贝到本地
	Sleep(10);
	//获取当前运行路径
	char currentPath[MAX_PATH];
	getcwd(currentPath, MAX_PATH);
	cprintf( "The   current   directory   is:   %s \n",   currentPath);
	string commond =  currentPath;
	string ip = CString2stringMultibyte(pDlg->hostIP);
	if(pDlg->m_CheckVersion.GetCheck()){
		commond += "\\PSCP.EXE -l nvidia -pw \"nvidia\" ";
		commond += " nvidia@";
		commond += ip;
		commond += ":/home/nvidia/hardware_test/camera_0.jpg .";
	}else{
		SSHChannel->Write("sudo chmod 777 /home/ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		SSHChannel->Write("ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		commond += "\\PSCP.EXE -l ubuntu -pw \"ubuntu\" ";
		commond += " ubuntu@";
		commond += ip;
		commond += ":/home/ubuntu/hardware_test/camera_0.jpg .";
	}
	cprintf( "commond  is:   %s \n", commond.c_str());
	//将图片拷贝到本地
	int n = system(commond.c_str());
	if(n == 0)
	{
		cprintf("copy camera_0.jpg success \n");
	}
	if(!pDlg->m_CheckVersion.GetCheck()){
	    SSHChannel->Write("sudo chmod 755 /home/ubuntu\n"); 
	    if(pDlg->m_OpenConsole.GetCheck()){
	        cprintf("%s \n", SSHChannel->Read().c_str());
	    }
	}
	ssh->Disconnect();
	//显示照片
	IplImage *img = cvLoadImage("camera_0.jpg");
	if(img == NULL){
		pDlg->MessageBox(_T("camera_0.jpg图片不存在"));
		goto end;
	}
	cvNamedWindow("camera_0.jpg",CV_WINDOW_NORMAL);
	cvShowImage("camera_0.jpg", img);
	cvWaitKey(0);
	cvReleaseImage(&img);  
    cvDestroyAllWindows();
end:
	pDlg->camera0_flag = false;
	pDlg->GetDlgItem(IDC_BUTTON_Camera0)->SetWindowText("Camera0测试");
	return 0;
}

int Camera1TestFun(LPVOID pM)
{
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	//删除本地的照片
	char *camera_jpg = "camera_1.jpg";
	fstream f;
	f.open(camera_jpg);
	if(f){
		f.close();
		if(remove(camera_jpg) != 0){
			pDlg->MessageBox(_T("删除本地camera_1.jpg失败，请先手动删除"));
			return -1;
		}
	}
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n"); 
		str = SSHChannel->Read();
	    if(pDlg->m_OpenConsole.GetCheck()){
		    cprintf("%s \n", str.c_str());
	    }
	    SSHChannel->Write(SAVE_RAW_IMAGE_1_28);
	}else{
		SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n"); 
		str = SSHChannel->Read();
	    if(pDlg->m_OpenConsole.GetCheck()){
		    cprintf("%s \n", str.c_str());
	    }
	    SSHChannel->Write(SAVE_RAW_IMAGE_1);
	}
	while(pDlg->camera1_flag){
		str = SSHChannel->Read();	
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if('$' == str[str.length() - 3]){
			break;
		}
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	
	//将照片拷贝到本地
	Sleep(10);
	//获取当前运行路径
	char currentPath[MAX_PATH];
	getcwd(currentPath, MAX_PATH);
	cprintf( "The   current   directory   is:   %s \n",   currentPath);
	string commond =  currentPath;
	string ip = CString2stringMultibyte(pDlg->hostIP);
	if(pDlg->m_CheckVersion.GetCheck()){
		commond += "\\PSCP.EXE -l nvidia -pw \"nvidia\" ";
	    commond += " nvidia@";
	    commond += ip;
	    commond += ":/home/nvidia/hardware_test/camera_1.jpg .";
	}else{
		SSHChannel->Write("sudo chmod 777 /home/ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		SSHChannel->Write("ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		commond += "\\PSCP.EXE -l ubuntu -pw \"ubuntu\" ";
	    commond += " ubuntu@";
	    commond += ip;
	    commond += ":/home/ubuntu/hardware_test/camera_1.jpg .";
	}
	cprintf( "commond  is:   %s \n", commond.c_str());
	//将图片拷贝到本地
	int n = system(commond.c_str());
	if(n == 0)
	{
		cprintf("copy camera_1.jpg success \n");
	}
	if(!pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("sudo chmod 755 /home/ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
	}
	ssh->Disconnect();
	//显示照片
	IplImage *img = cvLoadImage("camera_1.jpg");
	if(img == NULL){
		pDlg->MessageBox(_T("camera_1.jpg图片不存在"));
		goto end;
	}
	cvNamedWindow("camera_1.jpg",CV_WINDOW_NORMAL);
	cvShowImage("camera_1.jpg", img);
	cvWaitKey(0);
	cvReleaseImage(&img);  
    cvDestroyAllWindows();
end:
	pDlg->camera1_flag = false;
	pDlg->GetDlgItem(IDC_BUTTON_Camera1)->SetWindowText("Camera1测试");
	return 0;
}

int Camera2TestFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	//删除本地的照片
	char *camera_jpg = "camera_2.jpg";
	fstream f;
	f.open(camera_jpg);
	if(f){
		f.close();
		if(remove(camera_jpg) != 0){
			pDlg->MessageBox(_T("删除本地camera_2.jpg失败，请先手动删除"));
			return -1;
		}
	}
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	string str;
	Channel*SSHChannel = ssh->CreateChannel();
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(SAVE_RAW_IMAGE_2_28);
	}else{
		SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(SAVE_RAW_IMAGE_2);
	}
	while(pDlg->camera2_flag){
		str = SSHChannel->Read();	
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if('$' == str[str.length() - 3]){
			break;
		}
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	
	//获取当前运行路径
	char currentPath[MAX_PATH];
	getcwd(currentPath, MAX_PATH);
	cprintf( "The   current   directory   is:   %s \n",   currentPath);
	string commond =  currentPath;
	string ip = CString2stringMultibyte(pDlg->hostIP);
	//将照片拷贝到本地
	Sleep(10);
	if(pDlg->m_CheckVersion.GetCheck()){
		commond += "\\PSCP.EXE -l nvidia -pw \"nvidia\" ";
		commond += " nvidia@";
		commond += ip;
		commond += ":/home/nvidia/hardware_test/camera_2.jpg .";
	}else{
		SSHChannel->Write("sudo chmod 777 /home/ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		SSHChannel->Write("ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		commond += "\\PSCP.EXE -l ubuntu -pw \"ubuntu\" ";
		commond += " ubuntu@";
		commond += ip;
		commond += ":/home/ubuntu/hardware_test/camera_2.jpg .";
	}
	cprintf( "commond  is:   %s \n", commond.c_str());
	//将图片拷贝到本地
	int n = system(commond.c_str());
	if(n == 0)
	{
		cprintf("copy camera_2.jpg success \n");
	}
	if(!pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("sudo chmod 755 /home/ubuntu\n");

		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
	}
	ssh->Disconnect();
	//显示照片
	IplImage *img = cvLoadImage("camera_2.jpg");
	if(img == NULL){
		pDlg->MessageBox(_T("camera_2.jpg图片不存在"));
		goto end;
	}
	cvNamedWindow("camera_2.jpg",CV_WINDOW_NORMAL);
	cvShowImage("camera_2.jpg", img);
	cvWaitKey(0);
	cvReleaseImage(&img);  
    cvDestroyAllWindows();
end:
	pDlg->camera2_flag = false;
	pDlg->GetDlgItem(IDC_BUTTON_Camera2)->SetWindowText("Camera2测试");
	return 0;
}

int Camera3TestFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	//删除本地的照片
	char *camera_jpg = "camera_3.jpg";
	fstream f;
	f.open(camera_jpg);
	if(f){
		f.close();
		if(remove(camera_jpg) != 0){
			pDlg->MessageBox(_T("删除本地camera_3.jpg失败，请先手动删除"));
			return -1;
		}
	}
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(SAVE_RAW_IMAGE_3_28);
	}else{
		SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(SAVE_RAW_IMAGE_3);
	}
	while(pDlg->camera3_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if('$' == str[str.length() - 3]){
			break;
		}
	}
	str = SSHChannel->Read();
	if(pDlg->m_OpenConsole.GetCheck()){
		cprintf("%s \n", str.c_str());
	}
	str += "\n";
	pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
	pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
	pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	//获取当前运行路径
	char currentPath[MAX_PATH];
	getcwd(currentPath, MAX_PATH);
	cprintf( "The current directory is: %s \n", currentPath);
	string commond = currentPath;
	string ip = CString2stringMultibyte(pDlg->hostIP);
	//将照片拷贝到本地
	Sleep(10);
	if(pDlg->m_CheckVersion.GetCheck()){
		commond += "\\PSCP.EXE -l nvidia -pw \"nvidia\" ";
	    commond += " nvidia@";
	    commond += ip;
	    commond += ":/home/nvidia/hardware_test/camera_3.jpg .";
	}else{
		SSHChannel->Write("sudo chmod 777 /home/ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		SSHChannel->Write("ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
		commond += "\\PSCP.EXE -l ubuntu -pw \"ubuntu\" ";
	    commond += " ubuntu@";
	    commond += ip;
	    commond += ":/home/ubuntu/hardware_test/camera_3.jpg .";
	}
	cprintf( "commond  is:   %s \n", commond.c_str());
	//将图片拷贝到本地
	int n = system(commond.c_str());
	if(n == 0)
	{
		cprintf("copy camera_3.jpg success \n");
	}
	if(!pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("sudo chmod 755 /home/ubuntu\n"); 
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", SSHChannel->Read().c_str());
		}
	}
	//断开ssh
	ssh->Disconnect();
	//显示照片
	IplImage *img = cvLoadImage("camera_3.jpg");
	if(img == NULL){
		pDlg->MessageBox(_T("camera_3.jpg图片不存在"));
		goto end;
	}
	cvNamedWindow("camera_3.jpg",CV_WINDOW_NORMAL);
	cvShowImage("camera_3.jpg", img);
	cvWaitKey(0);
	cvReleaseImage(&img);  
    cvDestroyAllWindows();
end:
	pDlg->camera3_flag = false;
	pDlg->GetDlgItem(IDC_BUTTON_Camera3)->SetWindowText("Camera3测试");
	return 0;
}

int CameraPlayFun(LPVOID pM)
{
	CameraPlayerDlg *pDlg = (CameraPlayerDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write("cd /home/nvidia/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
	}else{
		SSHChannel->Write("cd /home/ubuntu/hardware_test/ \n"); 
		str = SSHChannel->Read();
		if(pDlg->pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
	}
	if(pDlg->play_cam_num == 0){
		if(pDlg->pDlg->m_CheckVersion.GetCheck()){
			SSHChannel->Write(Play_Camera_0_28);
		}else{
			SSHChannel->Write(Play_Camera_0);
		}
	}else if(pDlg->play_cam_num == 1){
		if(pDlg->pDlg->m_CheckVersion.GetCheck()){
			SSHChannel->Write(Play_Camera_1_28);
		}else{
			SSHChannel->Write(Play_Camera_1);
		}
	}else if(pDlg->play_cam_num == 2){
		if(pDlg->pDlg->m_CheckVersion.GetCheck()){
			SSHChannel->Write(Play_Camera_2_28);
		}else{
			SSHChannel->Write(Play_Camera_2);
		}
	}else if(pDlg->play_cam_num == 3){
		if(pDlg->pDlg->m_CheckVersion.GetCheck()){
			SSHChannel->Write(Play_Camera_3_28);
		}else{
			SSHChannel->Write(Play_Camera_3);
		}
	}else if(pDlg->play_cam_num == 4){
		if(pDlg->pDlg->m_CheckVersion.GetCheck()){
			SSHChannel->Write(STITCH_LIVE_28);
		}else{
			SSHChannel->Write(STITCH_LIVE);
		}
	}
	while(pDlg->play_flag0 || pDlg->play_flag1 || pDlg->play_flag2 ||pDlg->play_flag3 || pDlg->play_flag_stitch){
		str = SSHChannel->Read();
		if(pDlg->pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		if(str.size() > 0){
		    str += "\n";
		}
		pDlg->pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		Sleep(1);
	}
	Sleep(100);
	ssh->Disconnect();
	return 0;
}

#define CACHELENGTH 10

uint8_t buff[150000];
struct RTPDataStruct{
	uint8_t *data;
	int len;
	int flag;
	int frameNumber;
};

RTPDataStruct RTPCacheBuff[CACHELENGTH];

//queue<RTPDataStruct> rtpQueue;

byte startRtpData[] = {0xa0, 0x09, 0xe1, 0x01, 0x01, 0xb6, 0xa6, 0x1b, 0x03};

//FILE * poutfile;
//char *fileName = "recv.264";

int ReceiveUDPDataAndPlayWithoutCache(LPVOID pM){
	CameraPlayerDlg *pDlg = (CameraPlayerDlg*)pM;
	int n = 0;
	pDlg->currentLostNum = 0;
	pDlg->lostPacketNum = 0;
	int frame_number = 0;
	Sleep(100);
	int recvLen = 0;
	int lastNum = 0;
	struct sockaddr_in peeraddr;
	//sendto(pDlg->myUDP.sockClient, (char*)startRtpData, 9, 0, (SOCKADDR*)&pDlg->myUDP.addrSrv, sizeof(SOCKADDR));
	while(pDlg->play_flag0 || pDlg->play_flag1 || pDlg->play_flag2 ||pDlg->play_flag3 || pDlg->play_flag_stitch){
		memset(buff, 0, sizeof(buff));
		n = recv(pDlg->myUDP.sockServer, (char*)buff, sizeof(buff), 0);
		if(n <= 0){
			Sleep(1);
			pDlg->get_data = false;
			int m = sendto(pDlg->myUDP.sockClient, (char*)startRtpData, 9, 0, (SOCKADDR*)&pDlg->myUDP.addrSrv, sizeof(SOCKADDR));
			if (m > 0) {
				printf("send startRtpData success\n");
			}
			else {
				printf("send startRtpData failed\n");
			}
			continue;
		}
		pDlg->get_data = true;
		printf("receive data size %d bytes \n", n);
		int num1 = buff[0];
		int num2 = buff[1];
		if(num1 < num2 && num1 == 1){//第一包
			recvLen = 0;
			memset(pDlg->ffmpeg->packetData, 0, BUFFLENGTH);
			memcpy(pDlg->ffmpeg->packetData + recvLen, buff + 2, n-2);
			recvLen += n - 2;
		}else if(num1 < num2 && num1 > 1){//中间包
			memcpy(pDlg->ffmpeg->packetData + recvLen,buff + 2, n-2);
			recvLen += n - 2;
		}else if(num1 == num2 && num2 > 1){//最后一包
			memcpy(pDlg->ffmpeg->packetData + recvLen, buff + 2, n-2);
			recvLen += n - 2;
			lastNum = 0;
			if(pDlg->play_cam_num == 4){
				pDlg->ffmpeg_stitch->packet->data = pDlg->ffmpeg->packetData;
			    pDlg->ffmpeg_stitch->FFmeg_PlayPacket(pDlg->ffmpeg_stitch->packet);
			}
			else{
			    pDlg->ffmpeg->packet->data = pDlg->ffmpeg->packetData;
			    pDlg->ffmpeg->FFmeg_PlayPacket(pDlg->ffmpeg->packet);
			}
		}
		if(num1 == num2 && num2 == 1){
			recvLen = 0;
			memset(pDlg->ffmpeg->packetData, 0, BUFFLENGTH);
			memcpy(pDlg->ffmpeg->packetData + recvLen,buff + 2, n-2);
			recvLen += n - 2;
			lastNum = 0;
			//播放
			if(pDlg->play_cam_num == 4){
				pDlg->ffmpeg_stitch->packet->data = pDlg->ffmpeg->packetData;
			    pDlg->ffmpeg_stitch->FFmeg_PlayPacket(pDlg->ffmpeg_stitch->packet);
			}
			else{
			    pDlg->ffmpeg->packet->data = pDlg->ffmpeg->packetData;
			    pDlg->ffmpeg->FFmeg_PlayPacket(pDlg->ffmpeg->packet);
			}
		}
		Sleep(1);
	}
	
	memset(pDlg->ffmpeg->packetData, 0, BUFFLENGTH);
	return 0;
}

int OpenFanFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(HARDWARE_TEST_PATH_28);
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(FAN_SET_9000_28);
	}else{
		SSHChannel->Write(HARDWARE_TEST_PATH);
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(FAN_SET_9000);
	}
	Sleep(100);
	bool result = false;
	while(pDlg->open_fan_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if(str.find("true") != string::npos){
			result = true;
			break;
		}else if(str.find("false") != string::npos){
			result = false;
			break;
		}
	}
	if(pDlg->open_fan_flag){
		pDlg->GetDlgItem(IDC_BUTTON_FanControl)->SetWindowTextA("打开风扇");
		if(result){
			pDlg->MessageBox(_T("测试成功"));
		}else{
			pDlg->MessageBox(_T("测试失败"));
		}
		pDlg->open_fan_flag = false;
	}
	return 0;
}

int CloseFanFun(LPVOID pM){
	CRabbitProductTestToolDlg *pDlg = (CRabbitProductTestToolDlg*)pM;
	Ssh2 *ssh = new Ssh2(pDlg->ip);
	bool ret = ssh->Connect(pDlg->user, pDlg->pass);
	if(!ret){
		pDlg->MessageBox(_T("连接失败"));
		return -1;
	}
	Channel*SSHChannel = ssh->CreateChannel();
	string str;
	if(pDlg->m_CheckVersion.GetCheck()){
		SSHChannel->Write(HARDWARE_TEST_PATH_28); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(FAN_SET_4000_28);
	}else{
		SSHChannel->Write(HARDWARE_TEST_PATH); 
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		SSHChannel->Write(FAN_SET_4000);
	}
	Sleep(100);
	bool result = false;
	while(pDlg->close_fan_flag){
		str = SSHChannel->Read();
		if(pDlg->m_OpenConsole.GetCheck()){
			cprintf("%s \n", str.c_str());
		}
		str += "\n";
		pDlg->m_RichEditCtrl_Log.SetSel(-1, -1);
		pDlg->m_RichEditCtrl_Log.ReplaceSel(str.c_str());
		pDlg->m_RichEditCtrl_Log.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
		if(str.find("true") != string::npos){
			result = true;
			break;
		}else if(str.find("false") != string::npos){
			result = false;
			break;
		}
	}
	if(pDlg->close_fan_flag){
		pDlg->GetDlgItem(IDC_BUTTON_CloseFan)->SetWindowTextA("关闭风扇");
		if(result){
			pDlg->MessageBox(_T("测试成功"));
		}else{
			pDlg->MessageBox(_T("测试失败"));
		}
		pDlg->close_fan_flag = false;
	}
	return 0;
}