#include "stdafx.h"
#include "ServerList.h"
#include "Offset.h"
#include "Util.h"

int ServerCode = -1;
char ServerName[32][400];

__declspec(naked) void PrintServerCode()
{
	static DWORD PrintServerCodeAddress1 = 0x0067E26E;

	_asm
	{
		Movzx Ecx, Word Ptr Ds:[Edi-2]
		Push Edx
		Push Eax
		Jmp[PrintServerCodeAddress1]
	}
}

void InitServerList() // OK
{
	MemorySet(0x0067E19F,0x90,8);

	SetCompleteHook(0xE9,0x0067E269,&PrintServerCode);

	SetCompleteHook(0xE8,0x0067E27C,&PrintServerName1); // ServerList

	SetCompleteHook(0xE8,0x0067A345,&PrintServerName2); // LoginBox

	SetCompleteHook(0xE8,0x0061E4EB,&PrintServerName2); // CharInfo

	SetCompleteHook(0xE8,0x0047A455,&PrintServerName3); // Friend
}

void PrintServerName1(char* a,char* b,char* c,DWORD d) // OK
{
	wsprintf(a,"%s",ServerName[d]);
}

void PrintServerName2(char* a,char* b,char* c,DWORD d) // OK
{
	wsprintf(a,"%s",ServerName[ServerCode]);
}

void PrintServerName3(char* a,char* b,DWORD c) // OK
{
	wsprintf(a,"%s",ServerName[c-1]);
}