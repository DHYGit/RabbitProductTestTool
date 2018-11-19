#pragma once

// MyUDP.h : header file

#include <Winsock2.h>

/////////////////////////////////////////////////////////////////////////////
// CMyUDP command target

class CMyUDP
{
public:
	CMyUDP();           // protected constructor used by dynamic creation
	virtual ~CMyUDP();
	// Attributes
public:
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKET sockClient;
	SOCKET sockServer;
	SOCKADDR_IN addrSrv;
	int m_Quit;
	int m_Type;
	void Quit();
	void Init(char dstIP[], int localport, int dstPort);

	void SendData(unsigned char *buf, int len);
	void Revdata(byte *buf, int len);
	// Operations
protected:
	HANDLE hThread;
	DWORD ThreadID;
};
