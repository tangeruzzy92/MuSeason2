#include "stdafx.h"
#include "Map.h"
#include "CustomMap.h"
#include "Offset.h"
#include "Util.h"

void InitMap()  // OK
{
	SetByte(0x00650E1E,0xEB); // Fix Check .map files

	SetByte(0x00650E23,0xEB); // Fix Check .map files

	SetByte(0x00650F28,0xEB); // Fix Check .att files

	SetByte(0x00650F2D,0xEB); // Fix Check .att files

	SetByte(0x00650F98,0xEB); // Fix Check .obj files

	SetByte(0x00650F9D,0xEB); // Fix Check .obj files

	SetCompleteHook(0xE8,0x004DF29D,&LoadMapName);

	SetCompleteHook(0xE8,0x004E23C6,&LoadMapName);

	SetCompleteHook(0xE8,0x00621AB9,&LoadMapName);

	SetCompleteHook(0xE8,0x00699953,&LoadMapTitle);
}

char* LoadMapName(int index) //OK
{	
	CUSTOM_MAP_INFO* lpInfo = gCustomMap.GetInfoByNumber(index);

	if(lpInfo != 0)
	{
		return lpInfo->MapName;
	}

	return ((char*(*)(int))0x00621720)(index);
}

int LoadMapTitle(char* path,int index,int c,int d,int e,int f) // OK
{
	CUSTOM_MAP_INFO* lpInfo = gCustomMap.GetInfoByNumber(*(DWORD*)MAIN_CURRENT_MAP);

	if(lpInfo != 0)
	{
		path = lpInfo->TitlePath;
	}

	return ((int(__cdecl*)(char*,int,int,int,int,int))0x00673C20)(path,index,c,d,e,f);
}