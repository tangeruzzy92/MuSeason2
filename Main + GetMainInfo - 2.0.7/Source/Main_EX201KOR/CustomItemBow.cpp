// CustomItemBow.cpp: implementation of the CCustomItemBow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomItemBow.h"
#include "Util.h"

CCustomItemBow gCustomItemBow;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomItemBow::CCustomItemBow() // OK
{
	this->Init();
}

CCustomItemBow::~CCustomItemBow() // OK
{

}

void CCustomItemBow::Init() // OK
{
	for(int n=0;n<MAX_CUSTOM_ITEM_BOW;n++)
	{
		this->m_CustomItemBowInfo[n].Index = -1;
	}
}

void CCustomItemBow::Load(CUSTOM_ITEM_BOW_INFO* info) // OK
{
	for(int n=0;n<MAX_CUSTOM_ITEM_BOW;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomItemBow::SetInfo(CUSTOM_ITEM_BOW_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_ITEM_BOW)
	{
		return;
	}

	this->m_CustomItemBowInfo[info.Index] = info;
}

CUSTOM_ITEM_BOW_INFO* CCustomItemBow::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_ITEM_BOW)
	{
		return 0;
	}

	if(this->m_CustomItemBowInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomItemBowInfo[index];
}

CUSTOM_ITEM_BOW_INFO* CCustomItemBow::GetInfoByItem(int ItemIndex) // OK
{
	for(int n=0;n<MAX_CUSTOM_ITEM_BOW;n++)
	{
		CUSTOM_ITEM_BOW_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->ItemIndex == ItemIndex)
		{
			return lpInfo;
		}
	}

	return 0;
}

BOOL CCustomItemBow::GetCustomItemBowColor(int ItemIndex, float* ItemColor) // OK
{
	CUSTOM_ITEM_BOW_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	ItemColor[0] = (float)(lpInfo->ColorR/255.0f);
	ItemColor[1] = (float)(lpInfo->ColorG/255.0f);
	ItemColor[2] = (float)(lpInfo->ColorB/255.0f);

	return 1;
}

int CCustomItemBow::GetCustomItemBowEffect(int ItemIndex)
{
	CUSTOM_ITEM_BOW_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return -1;
	}

	return lpInfo->Effect;
}

int CCustomItemBow::CheckCustomItemBow(int ItemIndex,int Type)
{
	CUSTOM_ITEM_BOW_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0 || lpInfo->Number != Type)
	{
		return 0;
	}

	return 1;
}