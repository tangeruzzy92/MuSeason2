#include "stdafx.h"
#include "Item.h"
#include "CustomEffect.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomTooltip.h"
#include "CustomWing.h"
#include "Offset.h"
#include "Util.h"

void InitItem() // OK
{
	SetCompleteHook(0xE8,0x0065544E,&ItemModelLoad);

	SetCompleteHook(0xE8,0x0065545F,&ItemTextureLoad);

	SetCompleteHook(0xFF,0x0052F199,&GetItemColor);

	SetCompleteHook(0xFF,0x0063EE31,&GetItemColor);

	SetCompleteHook(0xE8,0x0052801F,&GetItemEffect);

	SetCompleteHook(0xE8,0x006415CB,&GetItemEffect);

	SetCompleteHook(0xE9,0x005E0D75,&GetItemToolTip);

	SetCompleteHook(0xE8,0x005F503B,&MoveItem);
}

void InitJewel() // OK
{
	SetCompleteHook(0xE9,0x005F6B74,&JewelCheckApplyItem1);

	SetCompleteHook(0xE9,0x0060789F,&JewelCheckApplyItem2);

	SetCompleteHook(0xE9,0x004ECCDA,&JewelCheckIndex1);

	SetCompleteHook(0xE9,0x0060E5D5,&JewelCheckIndex2);

	SetCompleteHook(0xE9,0x0060ED2B,&JewelCheckIndex3);

	SetCompleteHook(0xE9,0x0063B546,&JewelCheckIndex4);
}

void InitWing() // OK
{
	SetCompleteHook(0xE8,0x004AFE51,&WingMakePreviewCharSet);

	SetCompleteHook(0xE8,0x004DC968,&WingMakePreviewCharSet);
	
	SetCompleteHook(0xE8,0x004E2B07,&WingMakePreviewCharSet);
	
	SetCompleteHook(0xE8,0x004E39A6,&WingMakePreviewCharSet);
	
	SetCompleteHook(0xE8,0x004FE012,&WingMakePreviewCharSet);
	
	SetCompleteHook(0xE8,0x005004E0,&WingMakePreviewCharSet);
}

void ItemModelLoad() // OK
{
	((void(*)())0x00645320)();

	for(int n=0;n<MAX_CUSTOM_JEWEL;n++)
	{
		if(gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemModel((gCustomJewel.m_CustomJewelInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomJewel.m_CustomJewelInfo[n].ModelName);
		}
	}

	for(int n=0;n<MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemModel((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName);
		}
	}

	for(int n=0;n<MAX_CUSTOM_ITEM;n++)
	{
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemModel((gCustomItem.m_CustomItemInfo[n].ItemIndex+ITEM_BASE_MODEL),((gCustomItem.m_CustomItemInfo[n].ItemIndex >= GET_ITEM(7,0) && gCustomItem.m_CustomItemInfo[n].ItemIndex<GET_ITEM(12,0)) ? "Player\\" : "Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName);
		}
	}
}

void ItemTextureLoad() // OK
{
	for(int n=0;n<MAX_CUSTOM_JEWEL;n++)
	{
		if(gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomJewel.m_CustomJewelInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\");
		}
	}

	for(int n=0;n<MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\");
		}
	}

	for(int n=0;n<MAX_CUSTOM_ITEM;n++)
	{
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomItem.m_CustomItemInfo[n].ItemIndex+ITEM_BASE_MODEL),((gCustomItem.m_CustomItemInfo[n].ItemIndex >= GET_ITEM(7,0) && gCustomItem.m_CustomItemInfo[n].ItemIndex<GET_ITEM(12,0)) ? "Player\\" : "Item\\"));
		}
	}

	((void(*)())0x00646DC0)();
}

void LoadItemModel(int index,char* folder,char* name)
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH]={ 0 };

	wsprintf(path,"Data\\%s",folder);

	pLoadItemModel(index,path,name,-1);
}

void LoadItemTexture(int index,char* folder)
{
	pLoadItemTexture(index,folder,GL_REPEAT,GL_NEAREST,GL_TRUE);
}

void GetItemColor(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(gCustomItem.GetCustomItemColor((a-ITEM_BASE_MODEL),(float*)d) == 0)
	{
		((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x0063C030)(a,b,c,d,e);
	}
}

void GetItemEffect(DWORD a,int b,float* c,float d,int e,int f,int g,int h,int i) // OK
{
	for(int n=0;n < MAX_CUSTOM_EFFECT;n++)
	{
		if(gCustomEffect.m_CustomEffectInfo[n].Index != -1)
		{
			if(gCustomEffect.m_CustomEffectInfo[n].ItemIndex != (b-ITEM_BASE_MODEL))
			{
				continue;
			}

			if(gCustomEffect.m_CustomEffectInfo[n].MinItemLevel != -1 && gCustomEffect.m_CustomEffectInfo[n].MinItemLevel > GET_ITEM_OPT_LEVEL(e))
			{
				continue;
			}

			if(gCustomEffect.m_CustomEffectInfo[n].MaxItemLevel != -1 && gCustomEffect.m_CustomEffectInfo[n].MaxItemLevel < GET_ITEM_OPT_LEVEL(e))
			{
				continue;
			}

			if(gCustomEffect.m_CustomEffectInfo[n].MinNewOption != -1 && gCustomEffect.m_CustomEffectInfo[n].MinNewOption > GET_ITEM_OPT_EXC(f))
			{
				continue;
			}

			if(gCustomEffect.m_CustomEffectInfo[n].MaxNewOption != -1 && gCustomEffect.m_CustomEffectInfo[n].MaxNewOption < GET_ITEM_OPT_EXC(f))
			{
				continue;
			}

			DWORD o = 240 * b + *(DWORD*)0x05798D14;

			float ItemColor[3];
			
			float Position[3] = {0.0f,0.0f,0.0f};

			float WorldPosition[3] = {0.0f,0.0f,0.0f};

			ItemColor[0] = (float)(gCustomEffect.m_CustomEffectInfo[n].ColorR/255.0f);
			
			ItemColor[1] = (float)(gCustomEffect.m_CustomEffectInfo[n].ColorG/255.0f);
			
			ItemColor[2] = (float)(gCustomEffect.m_CustomEffectInfo[n].ColorB/255.0f);

			pTransformPosition(o,0x0068E0A58+(48*gCustomEffect.m_CustomEffectInfo[n].EffectValue),Position,WorldPosition,true);

			switch(gCustomEffect.m_CustomEffectInfo[n].EffectType)
			{
				case 0:
					pCreateSprite(gCustomEffect.m_CustomEffectInfo[n].EffectIndex,WorldPosition,gCustomEffect.m_CustomEffectInfo[n].Scale,ItemColor,1,0,gCustomEffect.m_CustomEffectInfo[n].EffectLevel);
					break;
				case 1:
					pCreateParticle(gCustomEffect.m_CustomEffectInfo[n].EffectIndex,WorldPosition,a+28,ItemColor,gCustomEffect.m_CustomEffectInfo[n].EffectLevel,gCustomEffect.m_CustomEffectInfo[n].Scale,1);
					break;
				case 2:
					pCreateEffect(gCustomEffect.m_CustomEffectInfo[n].EffectIndex,WorldPosition,a+28,ItemColor,gCustomEffect.m_CustomEffectInfo[n].EffectLevel,a,0,0,0,0,0);
					break;
			}
		}
	}

	pRenderPartObjectEffect(a,b,c,d,e,f,g,h,i);
}

void DrawItemToolTip(DWORD address) // OK
{
	for(int i=0;i<MAX_CUSTOM_TOOLTIP;i++)
	{
		if(gCustomTooltip.m_CustomTooltipInfo[i].Index != -1 && gCustomTooltip.m_CustomTooltipInfo[i].ItemIndex == *(WORD*)(address+0x00))
		{
			if (gCustomTooltip.m_CustomTooltipInfo[i].ItemLevel == -1 || gCustomTooltip.m_CustomTooltipInfo[i].ItemLevel == GET_ITEM_OPT_LEVEL(*(DWORD*)(address+0x04)))
			{
				*(&*(DWORD*)0x0790DB34 + *(DWORD*)0x0793F648) = gCustomTooltip.m_CustomTooltipInfo[i].FontValue;
				*(&*(DWORD*)0x0793CB18 + *(DWORD*)0x0793F648) = gCustomTooltip.m_CustomTooltipInfo[i].FontColor;

				wsprintf((char*)(0x64 * *(DWORD*)0x0793F648 + 0x0790C998),gCustomTooltip.m_CustomTooltipInfo[i].Text);

				*(DWORD*)0x0793F648 += 1;
			}
		}
	}
}

bool MoveItem(DWORD a,DWORD b,int c,int d,int e) // OK
{
	if (pCheckWindow(WINDOWS_TRADE) != 0)
	{
		return ((bool(*)(DWORD,DWORD,int,int,int))0x005F5FA0)(0x113,0x10F,0x0793CB90,d,4);
	}
	else if (pCheckWindow(WINDOWS_CHAOS_MIX) != 0 || pCheckWindow(WINDOWS_SENIOR_MIX) != 0 || pCheckWindow(WINDOWS_REFINERY) != 0)
	{
		return ((bool(*)(DWORD,DWORD,int,int,int))0x005F5FA0)(0x113,0x6E,0x07DC0EE0,d,4);
	}
	else if (pCheckWindow(WINDOWS_WAREHOUSE) != 0)
	{
		return ((bool(*)(DWORD,DWORD,int,int,int))0x005F5FA0)(a,b,c,d,e);
	}
	
	return 0;
}

void WingMakePreviewCharSet(int a,BYTE* b,int c,int d,int e,int f,int g) // OK
{
	((void(*)(int,BYTE*,int,int,int,int,int))0x00532E20)(a,b,c,d,e,f,g);
	
	DWORD ViewportAddress = pViewportAddress+(a*0x46C);

	if(*(BYTE*)(ViewportAddress) == 0)
	{
		return;
	}

	int Index = ((b[16]>>1)-1);

	if(gCustomWing.CheckCustomWing(Index) != 0)
	{
		int ItemIndex = gCustomWing.GetCustomWingItem(Index);

		if(ItemIndex != 0)
		{
			*(WORD*)(ViewportAddress+0x32C) = (ItemIndex+ITEM_BASE_MODEL);
		}
	}
}

__declspec(naked) void GetItemToolTip() // OK
{
	static DWORD ItemApplyToolTipAddress1 = 0x005E0D7A;

	_asm
	{
		PushAd
		Push Esi
		Call[DrawItemToolTip]
		Add Esp,0x04
		PopAd
		Cmp Word Ptr Ss:[Esi],0x1C0D
		Jmp[ItemApplyToolTipAddress1]
	}
}

__declspec(naked) void JewelCheckApplyItem1()
{
	static DWORD JewelCheckApplyItemAddress1 = 0x005F6B7B;
	static DWORD JewelCheckApplyItemAddress2 = 0x005F6B92;

	_asm
	{
		PushAd
		Cmp Di,0x1C2C
		Jz Exit
		Push Edi
		Lea Ecx,gCustomJewel
		Call[CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Jnz Exit
		PopAd
		Jmp[JewelCheckApplyItemAddress1]
		Exit:
		PopAd
		Jmp[JewelCheckApplyItemAddress2]
	}
}

__declspec(naked) void JewelCheckApplyItem2()
{
	static DWORD JewelCheckApplyItemAddress1 = 0x0060846B;
	static DWORD JewelCheckApplyItemAddress2 = 0x006078AA;

	_asm
	{
		Cmp Di,0x1C2C
		Jz Exit
		Push Edi
		Lea Ecx,gCustomJewel
		Call[CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Jnz Exit
		Jmp[JewelCheckApplyItemAddress1]
		Exit:
		Jmp[JewelCheckApplyItemAddress2]
	}
}

__declspec(naked) void JewelCheckIndex1() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x004ECD2D;
	static DWORD JewelCheckIndexAddress2 = 0x004ECCDF;

	_asm
	{
		PushAd
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		PopAd
		Cmp Eax,0x1C0E
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex2()
{
	static DWORD JewelCheckIndexAddress1 = 0x0060ECDD;
	static DWORD JewelCheckIndexAddress2 = 0x0060E5DA;

	_asm
	{
		Mov Eax,Dword Ptr Ds:[0x0790D550]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ds:[0x0790D550]
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex3() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x0061001C;
	static DWORD JewelCheckIndexAddress2 = 0x0060ED30;

	_asm
	{
		Mov Eax,Dword Ptr Ds:[0x0790D550]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ds:[0x0790D550]
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex4() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x0063B593;
	static DWORD JewelCheckIndexAddress2 = 0x0063B54C;

	_asm
	{
		PushAd
		Push Ebx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		PopAd
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		PopAd
		Cmp Ebx,0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}