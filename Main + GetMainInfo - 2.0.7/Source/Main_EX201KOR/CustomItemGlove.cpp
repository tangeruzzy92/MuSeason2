// CustomItemGlove.cpp: implementation of the CCustomItemGlove class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomItemGlove.h"
#include "Util.h"

CCustomItemGlove gCustomItemGlove;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomItemGlove::CCustomItemGlove() // OK
{
	this->Init();
}

CCustomItemGlove::~CCustomItemGlove() // OK
{

}

void CCustomItemGlove::Init() // OK
{
	for(int n=0;n<MAX_CUSTOM_ITEM_GLOVE;n++)
	{
		this->m_CustomItemGloveInfo[n].Index = -1;
	}
}

void CCustomItemGlove::Load(CUSTOM_ITEM_GLOVE_INFO* info) // OK
{
	for(int n=0;n<MAX_CUSTOM_ITEM_GLOVE;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomItemGlove::SetInfo(CUSTOM_ITEM_GLOVE_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_ITEM_GLOVE)
	{
		return;
	}

	this->m_CustomItemGloveInfo[info.Index] = info;
}

CUSTOM_ITEM_GLOVE_INFO* CCustomItemGlove::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_ITEM_GLOVE)
	{
		return 0;
	}

	if(this->m_CustomItemGloveInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomItemGloveInfo[index];
}

CUSTOM_ITEM_GLOVE_INFO* CCustomItemGlove::GetInfoByItem(int ItemIndex) // OK
{
	for(int n=0;n<MAX_CUSTOM_ITEM_GLOVE;n++)
	{
		CUSTOM_ITEM_GLOVE_INFO* lpInfo = this->GetInfo(n);

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

BOOL CCustomItemGlove::GetCustomItemGloveColor(int ItemIndex, float* ItemColor) // OK
{
	CUSTOM_ITEM_GLOVE_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	ItemColor[0] = (float)(lpInfo->ColorR/255.0f);
	ItemColor[1] = (float)(lpInfo->ColorG/255.0f);
	ItemColor[2] = (float)(lpInfo->ColorB/255.0f);

	return 1;
}

int CCustomItemGlove::CheckCustomItemGlove(int ItemIndex) // OK
{
	CUSTOM_ITEM_GLOVE_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	return 1;
}