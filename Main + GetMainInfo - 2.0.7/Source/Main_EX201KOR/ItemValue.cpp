// ItemValue.cpp: implementation of the CItemValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemValue.h"
#include "CustomJewel.h"
#include "ItemStack.h"
#include "Offset.h"
#include "Util.h"

CItemValue gItemValue;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemValue::CItemValue() // OK
{
	this->Init();
}

CItemValue::~CItemValue() // OK
{

}

void CItemValue::Init() // OK
{
	for(int n=0;n<MAX_ITEM_VALUE_INFO;n++)
	{
		this->m_ItemValueInfo[n].Index=-1;
	}
}

void CItemValue::Load(ITEM_VALUE_INFO* info) // OK
{
	for(int n=0;n<MAX_ITEM_VALUE_INFO;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CItemValue::SetInfo(ITEM_VALUE_INFO info) // OK
{
	if(info.Index<0 || info.Index >= MAX_ITEM_VALUE_INFO)
	{
		return;
	}

	this->m_ItemValueInfo[info.Index]=info;
}

ITEM_VALUE_INFO* CItemValue::GetInfo(int index) // OK
{
	if(index<0 || index >= MAX_ITEM_VALUE_INFO)
	{
		return 0;
	}

	if(this->m_ItemValueInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_ItemValueInfo[index];
}

bool CItemValue::GetItemValue(DWORD address,int* value) // OK
{
	if(gCustomJewel.CheckCustomJewelByItem(*(WORD*)(address+0x00))!=0)
	{
		(*value) = gCustomJewel.GetCustomJewelSalePrice(*(WORD*)(address+0x00));
		return 1;
	}

	for(int n=0;n<MAX_ITEM_VALUE_INFO;n++)
	{
		ITEM_VALUE_INFO* lpInfo=this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->ItemIndex == *(WORD*)(address+0x00))
		{
			if(lpInfo->Level == -1 || lpInfo->Level == GET_ITEM_OPT_LEVEL(*(DWORD*)(address+0x04)))
			{
				if(lpInfo->Grade == -1 || lpInfo->Grade == GET_ITEM_OPT_EXC(*(BYTE*)(address+0x1B)))
				{
					if(gItemStack.GetItemMaxStack(lpInfo->ItemIndex,lpInfo->Level) == 0 || lpInfo->ItemIndex == GET_ITEM(4,7) || lpInfo->ItemIndex == GET_ITEM(4,15))
					{
						(*value) = lpInfo->Value;
						return 1;
					}
					else
					{
						(*value) = (int)(lpInfo->Value**(BYTE*)(address+0x1A));
						return 1;
					}
				}
			}
		}
	}

	return 0;
}
