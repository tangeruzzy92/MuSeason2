// ItemBag.h: interface for the CItemBag class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Item.h"
#include "ItemBagEx.h"
#include "User.h"

#define MAX_BAG_ITEM 500

struct ITEM_BAG_INFO
{
	int ItemIndex;
	int MinLevel;
	int MaxLevel;
	int Option1;
	int Option2;
	int Option3;
	int NewOption;
	int SetOption;
	int SocketOption;
};

class CItemBag
{
public:
	CItemBag();
	virtual ~CItemBag();
	void Init();
	void Load(char* path);
	void SetInfo(ITEM_BAG_INFO info);
	ITEM_BAG_INFO* GetInfo(int index);
	bool GetItem(LPOBJ lpObj,CItem* lpItem);
	bool DropItem(LPOBJ lpObj,int map,int x,int y);
private:
	char m_EventName[32];
	int m_DropZen;
	int m_ItemDropRate;
	int m_MinItemDropCount;
	int m_MaxItemDropCount;
	int m_SetItemDropRate;
	int m_ItemDropType;
	int m_BagUseEffect;
	ITEM_BAG_INFO m_BagInfo[MAX_BAG_ITEM];
	int m_count;
	CItemBagEx m_ItemBagEx;
};
