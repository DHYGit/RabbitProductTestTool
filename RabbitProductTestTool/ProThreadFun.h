#pragma once
#include "stdafx.h"

int ExcuteFun(LPVOID pM);
int LEDStreamFun(LPVOID pM);
int UpgradeSHFun(LPVOID pM);
int TarAndUpgradeFun(LPVOID pM);
int PlayAudioFun(LPVOID pM);
int PlayLeftChannelFun(LPVOID pM);
int PlayRightChannelFun(LPVOID pM);
int RecordFun(LPVOID pM);
int PlayRecordFun(LPVOID pM);
int DistanceTestFun(LPVOID pM);
int Uart1TestFun(LPVOID pM);
int Uart2TestFun(LPVOID pM);
int TestPirFun(LPVOID pM);
int OpenFanFun(LPVOID pM);
int CloseFanFun(LPVOID pM);
int GetPRessureFun(LPVOID pM);
int Camera0TestFun(LPVOID pM);
int Camera1TestFun(LPVOID pM);
int Camera2TestFun(LPVOID pM);
int Camera3TestFun(LPVOID pM);

int CameraPlayFun(LPVOID pM);

int ReceiveUDPDataAndPlayWithoutCache(LPVOID pM);
