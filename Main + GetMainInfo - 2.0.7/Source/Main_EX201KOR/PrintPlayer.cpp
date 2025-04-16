#include "stdafx.h"
#include "PrintPlayer.h"
#include "Offset.h"
#include "Protect.h"
#include "Reconnect.h"
#include "Util.h"

DWORD ViewIndex = 0;
DWORD ViewLevel = 0;
DWORD ViewReset = 0;
DWORD ViewPoint = 0;
DWORD ViewCurHP = 0;
DWORD ViewMaxHP = 0;
DWORD ViewCurMP = 0;
DWORD ViewMaxMP = 0;
DWORD ViewCurBP = 0;
DWORD ViewMaxBP = 0;
DWORD ViewCurSD = 0;
DWORD ViewMaxSD = 0;
DWORD ViewDamageHP = 0;
DWORD ViewDamageSD = 0;
DWORD ViewExperience = 0;
DWORD ViewNextExperience = 0;
DWORD ViewStrength = 0;
DWORD ViewDexterity = 0;
DWORD ViewVitality = 0;
DWORD ViewEnergy = 0;
DWORD ViewLeadership = 0;
DWORD ViewAddStrength = 0;
DWORD ViewAddDexterity = 0;
DWORD ViewAddVitality = 0;
DWORD ViewAddEnergy = 0;
DWORD ViewAddLeadership = 0;
DWORD ViewPhysiSpeed = 0;
DWORD ViewMagicSpeed = 0;

void InitPrintPlayer() // OK
{
	SetCompleteHook(0xE8,0x005D454A,&PrintDrawCircleHPMP);

	SetCompleteHook(0xE8,0x005D4610,&PrintDrawCircleHPMP);

	SetCompleteHook(0xE8,0x005D3800,&PrintDrawCircleSDBP);

	SetCompleteHook(0xE8,0x005D3B90,&PrintDrawCircleSDBP);

	SetCompleteHook(0xE8,0x005D6EE3,&PrintBarExperience1);

	SetCompleteHook(0xE8,0x005D6F20,&PrintBarExperience2);

	SetCompleteHook(0xE8,0x00415CB2,&PrintPlayerViewHP1);

	SetCompleteHook(0xE8,0x005D45A3,&PrintPlayerViewHP1);

	SetCompleteHook(0xE8,0x00620D6E,&PrintPlayerViewHP1);

	SetCompleteHook(0xE8,0x005D532C,&PrintPlayerViewHP2);

	SetCompleteHook(0xE8,0x005D4669,&PrintPlayerViewMP1);

	SetCompleteHook(0xE8,0x00620E81,&PrintPlayerViewMP1);

	SetCompleteHook(0xE8,0x005D5353,&PrintPlayerViewMP2);

	SetCompleteHook(0xE8,0x005D3862,&PrintPlayerViewBP1);

	SetCompleteHook(0xE8,0x005D381A,&PrintPlayerViewBP2);

	SetCompleteHook(0xE8,0x005D3BF2,&PrintPlayerViewSD1);

	SetCompleteHook(0xE8,0x005D3BAA,&PrintPlayerViewSD2);

	SetCompleteHook(0xE8,0x006212E7,&PrintPlayerViewLevelUp);

	SetCompleteHook(0xE8,0x0061EE53,&PrintPlayerViewStrength);

	SetCompleteHook(0xE8,0x006205DB,&PrintPlayerViewDexterity);

	SetCompleteHook(0xE8,0x00620CEE,&PrintPlayerViewVitality);

	SetCompleteHook(0xE8,0x00620E07,&PrintPlayerViewEnergy);

	SetCompleteHook(0xE8,0x006216C7,&PrintPlayerViewLeadership);

	SetCompleteHook(0xE8,0x00620A60,&PrintPlayerViewAttackSpeed);

	SetCompleteHook(0xE9,0x0057629C,&PrintPlayerSetAttackSpeed);

	SetCompleteHook(0xE8,0x004E5D5B,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004E5E6A,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004E5EBC,&PrintDamageOnScreenSD);
	
	SetCompleteHook(0xE8,0x004E6A57,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004E6AA7,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004E6B2E,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004E6B7E,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004E6B9B,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004E6BEC,&PrintDamageOnScreenSD);
	
	SetCompleteHook(0xE8,0x004EACEC,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004EB64A,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004EB67F,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004EC12C,&PrintDamageOnScreenHP);
	
	SetCompleteHook(0xE8,0x004EC161,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x004DF2B2,&PrintPlayerMapName);

	SetCompleteHook(0xE8,0x004E23DB,&PrintPlayerMapName);
}

void PrintDamageOnScreenHP(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageHP;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x0056F060)(a,b,c,d,e);
}

void PrintDamageOnScreenSD(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageSD;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x0056F060)(a,b,c,d,e);
}

void PrintPlayerMapName(char* a, char* b, char* c, char* d) // OK
{
	wsprintf(a,b,d,c);
}

void PrintDrawCircleHPMP(DWORD a,float b,float c,float d,float e,float f,float g,float h,float i,int j,int k,GLfloat l) // OK
{
	float HP = (float)(ViewMaxHP-ViewCurHP)/(float)ViewMaxHP;
	float MP = (float)(ViewMaxMP-ViewCurMP)/(float)ViewMaxMP;

	c = ((a==0xEB)?MP:HP)*48.0f+432.0f;
    e = 48.0f-((a==0xEB)?MP:HP)*48.0f;
    g = ((a==0xEB)?MP:HP)*48.0f/64.0f;
    i = (1.0f-((a==0xEB)?MP:HP))*48.0f/64.0f;

	return pDrawImage(a,b,c,d,e,f,g,h,i,j,k,l);
}

void PrintDrawCircleSDBP(DWORD a,float b,float c,float d,float e,float f,float g,float h,float i,int j,int k,GLfloat l) // OK
{
	float SD = (float)(ViewMaxSD-ViewCurSD)/(float)ViewMaxSD;
	float BP = (float)(ViewMaxBP-ViewCurBP)/(float)ViewMaxBP;

	c = ((a==0x101)?BP:SD)*36.0f+438.0f;
    e = 36.0f-((a==0x101)?BP:SD)*36.0f;
	g = ((a==0x101)?BP:SD)*36.0f/64.0f;
    i = (1.0f-((a==0x101)?BP:SD))*36.0f/64.0f;

	return pDrawImage(a,b,c,d,e,f,g,h,i,j,k,l);
}

void PrintBarExperience1(float a,float b,float c,float d,float e,int f) // OK
{
	float TotalBarValue = 1782.0f*((float)(gLevelExperience[ViewLevel]-ViewExperience)/(float)(gLevelExperience[ViewLevel]-gLevelExperience[ViewLevel-1]));
	float BarSplit = TotalBarValue/198.0f;
	float Modf[2];

	Modf[0] = modf(BarSplit,&Modf[1]);

	pDrawBarForm(a,b,(Modf[0]==0)?0:(198.0f-(Modf[0]*198.0f)),d,e,f);
}

void PrintBarExperience2(float a,float b,DWORD c,float d,float e) // OK
{
	float TotalBarValue = 1782.0f*((float)(gLevelExperience[ViewLevel]-ViewExperience)/(float)(gLevelExperience[ViewLevel]-gLevelExperience[ViewLevel-1]));
	float BarSplit = TotalBarValue/198.0f;
	float Modf[2];

	Modf[0] = modf(BarSplit,&Modf[1]);

	pDrawBigText(a,b,((DWORD)(9-Modf[1])>9)?9:(DWORD)(9-Modf[1]),d,e);
}

void PrintPlayerViewHP1(char* a,char* b) // OK
{
	wsprintf(a,b,ViewCurHP,ViewMaxHP);
}

void PrintPlayerViewHP2(float a,float b,DWORD c,float d,float e) // OK
{
	PrintFixStatPoint();

	pDrawBigText(a+6,b,ViewCurHP,d,e);
}

void PrintPlayerViewMP1(char* a,char* b) // OK
{
	wsprintf(a,b,ViewCurMP,ViewMaxMP);
}

void PrintPlayerViewMP2(float a,float b,DWORD c,float d,float e) // OK
{
	pDrawBigText(a-20,b,ViewCurMP,d,e);
}

void PrintPlayerViewBP1(char* a,char* b) // OK
{
	wsprintf(a,b,ViewCurBP,ViewMaxBP);
}

void PrintPlayerViewBP2(float a,float b,DWORD c,float d,float e) // OK
{
	pDrawBigText(a,b,ViewCurBP,d,e);
}

void PrintPlayerViewSD1(char* a,char* b) // OK
{
	wsprintf(a,b,ViewCurSD,ViewMaxSD);
}

void PrintPlayerViewSD2(float a,float b,DWORD c,float d,float e) // OK
{
	pDrawBigText(a,b,ViewCurSD,d,e);
}

void PrintPlayerViewLevelUp(char* a,char* b) // OK
{
	wsprintf(a,b,ViewPoint);
}

void PrintPlayerViewStrength(char* a,char* b) // OK
{
	wsprintf(a,b,ViewStrength+ViewAddStrength);
}

void PrintPlayerViewDexterity(char* a,char* b) // OK
{
	wsprintf(a,b,ViewDexterity+ViewAddDexterity);
}

void PrintPlayerViewVitality(char* a,char* b) // OK
{
	wsprintf(a,b,ViewVitality+ViewAddVitality);
}

void PrintPlayerViewEnergy(char* a,char* b) // OK
{
	wsprintf(a,b,ViewEnergy+ViewAddEnergy);
}

void PrintPlayerViewLeadership(char* a,char* b) // OK
{
	wsprintf(a,b,ViewLeadership+ViewAddLeadership);
}

void PrintPlayerViewAttackSpeed(char* a,char* b) // OK
{
	if(((*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B)) & 7) == 0)
	{
		wsprintf(a,b,ViewMagicSpeed);
	}
	else
	{
		wsprintf(a,b,ViewPhysiSpeed);
	}
}

void PrintFixStatPoint() // OK
{
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x18) = GET_MAX_WORD_VALUE(ViewStrength);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x32) = GET_MAX_WORD_VALUE(ViewAddStrength);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1A) = GET_MAX_WORD_VALUE(ViewDexterity);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x34) = GET_MAX_WORD_VALUE(ViewAddDexterity);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1C) = GET_MAX_WORD_VALUE(ViewVitality);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x36) = GET_MAX_WORD_VALUE(ViewAddVitality);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1E) = GET_MAX_WORD_VALUE(ViewEnergy);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x38) = GET_MAX_WORD_VALUE(ViewAddEnergy);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x20) = GET_MAX_WORD_VALUE(ViewLeadership);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x3E) = GET_MAX_WORD_VALUE(ViewAddLeadership);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0E) = GET_MAX_WORD_VALUE(ViewLevel);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x70) = GET_MAX_WORD_VALUE(ViewPoint);

	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10) = (ViewExperience > ViewNextExperience) ? ViewNextExperience : ViewExperience;

	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x14) = ViewNextExperience;
}

__declspec(naked) void PrintPlayerSetAttackSpeed()
{
	static DWORD PrintPlayerSetAttackSpeedAddress1 = 0x0057636B;

	_asm
	{
		Mov Edx,ViewPhysiSpeed
		Mov Eax,Dword Ptr Ds:[gProtect.m_MainInfo.MaxAttackSpeed+Ecx*4]
		And Eax,0xFFFF
		Cmp Edx,Eax
		Jle NEXT1
		Mov Edx,Eax
		NEXT1:
		Lea Ebx,[Esi+0x54]
		Mov Dword Ptr[Ebp-0xC],Ebx
		Mov	[Ebx],Dx
		Mov Edx,ViewMagicSpeed
		Mov Eax,Dword Ptr Ds:[gProtect.m_MainInfo.MaxAttackSpeed+Ecx*4]
		And Eax,0xFFFF
		Cmp Edx,Eax
		Jle NEXT2
		Mov Edx,Eax
		NEXT2:
		Lea	Eax,[Esi+0x60]
		Mov	[Ebp-0x10],Eax
		Mov	[Eax],Dx
		Jmp [PrintPlayerSetAttackSpeedAddress1]
	}
}