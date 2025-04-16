#include "stdafx.h"
#include "Shop.h"
#include "CustomJewel.h"
#include "ItemValue.h"
#include "Offset.h"
#include "Util.h"

void InitShop() // OK
{
	SetCompleteHook(0xE8,0x005DDE27,&GetBuyPrice);

	SetCompleteHook(0xE8,0x005DDF00,&GetBuyPrice);

	SetCompleteHook(0xE8,0x005DDF4A,&GetSellPrice);
}

int GetBuyPrice(DWORD address) // OK
{
	int value = 0;

	if(gItemValue.GetItemValue(address,&value) != 0)
	{
		value = ((value>=100)?((value/10)*10):value);

		value = ((value>=1000)?((value/100)*100):value);

		return value;
	}

	return ((int(*)(DWORD,int))0x00573340)(address,0);
}

int GetSellPrice(DWORD address) // OK
{
	int value = 0;

	if(gItemValue.GetItemValue(address,&value) != 0)
	{
		value = (value/3);

		value = ((value>=100)?((value/10)*10):value);

		value = ((value>=1000)?((value/100)*100):value);

		return value;
	}

	return ((int(*)(DWORD,int))0x00573340)(address,1);
}