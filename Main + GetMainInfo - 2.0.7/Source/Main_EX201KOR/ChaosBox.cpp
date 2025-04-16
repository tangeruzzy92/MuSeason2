#include "stdafx.h"
#include "ChaosBox.h"
#include "Offset.h"
#include "Protocol.h"
#include "Util.h"

DWORD MixRate = 0;
DWORD MixMoney = 0;
DWORD MixTax = 0;

void InitChaosBox() // OK
{
	SetCompleteHook(0xE8,0x0063096D,&PrintPlayerChaosRate);

	SetCompleteHook(0xE8,0x00630BFD,&PrintPlayerChaosRate);

	SetCompleteHook(0xE8,0x00630C67,&PrintPlayerChaosMoney);

	SetCompleteHook(0xE8,0x00630C88,&PrintPlayerChaosMoney);

	SetCompleteHook(0xE8,0x0069265E,&PrintPlayerRefineryRate);
}

void ChaosBoxMainProc() // OK
{
	if(pCheckWindow(WINDOWS_REFINERY) != 0)
	{
		PMSG_CHAOS_MIX_RATE_SEND pMsg;

		pMsg.header.set(0x88,sizeof(pMsg));

		pMsg.type = CHAOS_MIX_JEWEL_OF_HARMONY_ITEM_PURITY;

		DataSend((BYTE*)&pMsg,pMsg.header.size);
	}
	else if(ChaosBoxMixCheck() != 0)
	{
		PMSG_CHAOS_MIX_RATE_SEND pMsg;

		pMsg.header.set(0x88,sizeof(pMsg));

		pMsg.type = pChaosMixIndex;

		DataSend((BYTE*)&pMsg,pMsg.header.size);
	}
}

bool ChaosBoxMixCheck() // OK
{
	switch(pChaosMixIndex)
	{
		case CHAOS_MIX_CHAOS_ITEM:
		case CHAOS_MIX_DEVIL_SQUARE:
		case CHAOS_MIX_PLUS_ITEM_LEVEL1:
		case CHAOS_MIX_PLUS_ITEM_LEVEL2:
		case CHAOS_MIX_DINORANT:
		case CHAOS_MIX_FRUIT:
		case CHAOS_MIX_WING1:
		case CHAOS_MIX_BLOOD_CASTLE:
		case CHAOS_MIX_WING2:
		case CHAOS_MIX_PET1:
		case CHAOS_MIX_PET2:
		case CHAOS_MIX_PLUS_ITEM_LEVEL3:
		case CHAOS_MIX_PLUS_ITEM_LEVEL4:
		case CHAOS_MIX_WING3:
		case CHAOS_MIX_PIECE_OF_HORN:
		case CHAOS_MIX_BROKEN_HORN:
		case CHAOS_MIX_HORN_OF_FENRIR:
		case CHAOS_MIX_HORN_OF_FENRIR_UPGRADE:
		case CHAOS_MIX_SHIELD_POTION1:
		case CHAOS_MIX_SHIELD_POTION2:
		case CHAOS_MIX_SHIELD_POTION3:
		case CHAOS_MIX_ITEM_380:
			return 1;
	}

	return 0;
}

void ChaosBoxConvertMoney(int money,char* target) // OK
{
	if(money >= 1000000000)
	{
		wsprintf(target,"%d,%03d,%03d,%03d",money/1000000000,money%1000000000/1000000,money%1000000/1000,money%1000);
	}
	else if(money >= 1000000)
	{
		wsprintf(target,"%d,%03d,%03d",money%1000000000/1000000,money%1000000/1000,money%1000);
	}
	else if(money > 1000)
	{
		wsprintf(target,"%d,%03d",money%1000000/1000,money%1000);
	}
	else
	{
		wsprintf(target,"%d",money%1000);
	}
}

void PrintPlayerChaosRate(char* a,char* b,char* c,int d) // OK
{
	if(ChaosBoxMixCheck() != 0)
	{
		d = MixRate;
	}

	wsprintf(a,b,c,d);
}

void PrintPlayerChaosMoney(char* a,char* b,char* c,char* d) // OK
{
	if(ChaosBoxMixCheck() != 0)
	{
		ChaosBoxConvertMoney(MixMoney,c);

		ChaosBoxConvertMoney((MixMoney+MixTax),d);
	}

	wsprintf(a,b,c,d);
}

void PrintPlayerRefineryRate(char* a,char* b,char* c,char* d,int e) // OK
{
	e = MixRate;

	wsprintf(a,b,c,d,e);
}

void GCChaosMixRateRecv(PMSG_CHAOS_MIX_RATE_RECV* lpMsg) // OK
{
	MixRate = lpMsg->rate;

	MixMoney = lpMsg->money;

	MixTax = lpMsg->tax;
}