// MyUDP.cpp : implementation file
//

#include "stdafx.h"

#include "MyUDP.h"

/////////////////////////////////////////////////////////////////////////////
// CMyUDP

CMyUDP::CMyUDP()
{
	m_Quit =0;
}

CMyUDP::~CMyUDP()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMyUDP message handlers

void CMyUDP::Init(char dstIP[], int localport, int dstPort)
{
	wVersionRequested = MAKEWORD( 1, 1 );
	int  err = WSAStartup( wVersionRequested, &wsaData );
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) {
		WSACleanup( );
		return; 
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(6000); ///监听端口
	local.sin_addr.s_addr = INADDR_ANY; ///本机

	sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	int nNetTimeout = 100;//1秒

	setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
	bind(sockClient, (struct sockaddr*)&local, sizeof(local));

	struct sockaddr_in localServer;
	localServer.sin_family = AF_INET;
	localServer.sin_port = htons(localport); ///监听端口
	localServer.sin_addr.s_addr = INADDR_ANY; ///本机

	sockServer = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(sockServer, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
	int nRecvBuf=64*1024*1024;//设置为64M
    setsockopt(sockServer,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
	bind(sockServer, (struct sockaddr*)&localServer, sizeof(localServer));
   

	addrSrv.sin_addr.S_un.S_addr = inet_addr(dstIP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(dstPort);
}
void CMyUDP::Quit(){
	closesocket(sockServer);
	closesocket(sockClient);
}
void CMyUDP::SendData( unsigned char *buf,int len)
{
	sendto(sockClient,(char*)(buf),len,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
}