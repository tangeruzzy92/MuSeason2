#include "stdafx.h"
#include "MiniMap.h"
#include "Offset.h"
#include "Util.h"

bool MiniMapTable[MAX_MINI_MAP];

void InitMiniMap() // OK
{
	memset(MiniMapTable,0,sizeof(MiniMapTable));

	SetCompleteHook(0xFF,0x00650D62,&MiniMapCore);

	SetCompleteHook(0xE8,0x0064DCE0,&MiniMapLoad);

	SetCompleteHook(0xFF,0x005D41F0,&MiniMapCheck);
}

void MiniMapCore() // OK
{
	((void(*)())0x00432DC0)();

	MiniMapLoad();
}

void MiniMapLoad() // OK
{
	char buff[64];

	wsprintf(buff,"World%d\\Map1.jpg",(*(DWORD*)MAIN_CURRENT_MAP)+1);

	if(MiniMapFileCheck(*(DWORD*)MAIN_CURRENT_MAP) != 0)
	{
		MiniMapTable[*(DWORD*)MAIN_CURRENT_MAP] = 1;
		((int(__cdecl*)(char*,int,int,int,int,int))0x00673790)(buff,0x69F,0x2601,0x2900,0,1);
	}
}

void MiniMapCheck() // OK
{
	if(MiniMapTable[*(DWORD*)MAIN_CURRENT_MAP] != 0)
	{
		SetByte(0x00413206,0xEB);
	}
	else
	{
		SetByte(0x00413206,0x74);
	}
}

bool MiniMapFileCheck(int map) // OK
{
	char buff[64];

	wsprintf(buff,".\\Data\\World%d\\Map1.ozj",(map+1));

	FILE* file;

	if(fopen_s(&file,buff,"r") != 0)
	{
		return 0;
	}
	else
	{
		fclose(file);
		return 1;
	}
}
