// CLanguage.cpp: implementation of the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Language.h"
#include "Util.h"

char lang[4],filename[11][MAX_PATH];

void InitLanguage() // OK
{
	HKEY key;

	if(RegOpenKeyEx(HKEY_CURRENT_USER,"SOFTWARE\\Webzen\\Mu\\Config",0,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
	{
		DWORD type=REG_SZ,size=sizeof(lang);

		if(RegQueryValueEx(key,"LangSelection",0,&type,(BYTE*)lang,&size) != ERROR_SUCCESS)
		{
			strcpy_s(lang,"Eng");
		}

		RegCloseKey(key);
	}

	if(_stricmp(lang,"Eng") != 0 && _stricmp(lang,"Por") != 0 && _stricmp(lang,"Spn") != 0)
	{
		strcpy_s(lang,"Eng");
	}

	wsprintf(filename[0],"Data\\Local\\%s\\Dialog_%s.bmd",lang,lang);
	wsprintf(filename[1],"Data\\Local\\%s\\Item_%s.bmd",lang,lang);
	wsprintf(filename[2],"Data\\Local\\%s\\ItemSetOption_%s.bmd",lang,lang);
	wsprintf(filename[3],"Data\\Local\\%s\\JewelOfHarmonyOption_%s.bmd",lang,lang);
	wsprintf(filename[4],"Data\\Local\\%s\\JewelOfHarmonySmelt_%s.bmd",lang,lang);
	wsprintf(filename[5],"Data\\Local\\%s\\Movereq_%s.bmd",lang,lang);
	wsprintf(filename[6],"Data\\Local\\%s\\NpcName_%s.txt",lang,lang);
	wsprintf(filename[7],"Data\\Local\\%s\\Quest_%s.bmd",lang,lang);
	wsprintf(filename[8],"Data\\Local\\%s\\Skill_%s.bmd",lang,lang);
	wsprintf(filename[9],"Data\\Local\\%s\\Slide_%s.bmd",lang,lang);
	wsprintf(filename[10],"Data\\Local\\%s\\Text_%s.bmd",lang,lang);

	SetDword(0x006555EC,(DWORD)&filename[0]);
	SetDword(0x006554D4,(DWORD)&filename[1]);
	SetDword(0x006555BA,(DWORD)&filename[1]);
	SetDword(0x0040D5A8,(DWORD)&filename[2]);
	SetDword(0x0068FD7F,(DWORD)&filename[3]);
	SetDword(0x0068FD92,(DWORD)&filename[3]);
	SetDword(0x0068FDEC,(DWORD)&filename[4]);
	SetDword(0x0068FE01,(DWORD)&filename[4]);
	SetDword(0x00655615,(DWORD)&filename[5]);
	SetDword(0x006556ED,(DWORD)&filename[5]);
	SetDword(0x0065577B,(DWORD)&filename[6]);
	SetDword(0x006555FF,(DWORD)&filename[7]);
	SetDword(0x00655504,(DWORD)&filename[8]);
	SetDword(0x006555C4,(DWORD)&filename[8]);
	SetDword(0x0065579B,(DWORD)&filename[9]);
	SetDword(0x006558E9,(DWORD)&filename[10]);
	SetDword(0x00655907,(DWORD)&filename[10]);
}