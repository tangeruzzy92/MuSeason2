// AccountManager.h: interface for the CAllowableIpList class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CriticalSection.h"

#define MAX_ACCOUNT 10000

struct ACCOUNT_INFO
{
	char Account[11];
	char IpAddress[16];
	WORD UserIndex;
	WORD GameServerCode;
	bool MapServerMove;
	DWORD MapServerMoveTime;
	WORD LastServerCode;
	WORD NextServerCode;
	WORD Map;
	BYTE X;
	BYTE Y;
	DWORD AuthCode1;
	DWORD AuthCode2;
	DWORD AuthCode3;
	DWORD AuthCode4;
};

class CAccountManager
{
public:
	CAccountManager();
	virtual ~CAccountManager();
	void DisconnectProc();
	void ClearServerAccountInfo(WORD ServerCode);
	bool GetAccountInfo(ACCOUNT_INFO* lpAccountInfo,char* account);
	void InsertAccountInfo(ACCOUNT_INFO AccountInfo);
	void RemoveAccountInfo(ACCOUNT_INFO AccountInfo);
	long GetAccountCount();
private:
	CCriticalSection m_critical;
	std::map<std::string,ACCOUNT_INFO> m_AccountInfo;
};

extern CAccountManager gAccountManager;

static const int gJoinServerMaxAccount[5] = { 20,200,500,MAX_ACCOUNT,MAX_ACCOUNT };