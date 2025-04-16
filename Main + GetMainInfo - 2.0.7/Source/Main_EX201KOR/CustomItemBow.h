// CustomItemBow.h: interface for the CCustomItemBow class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_ITEM_BOW 200

struct CUSTOM_ITEM_BOW_INFO
{
	int Index;
	int ItemIndex;
	int Number;
	int Effect;
	int ColorR;
	int ColorG;
	int ColorB;
	char ModelName[32];
};

class CCustomItemBow
{
public:
	CCustomItemBow();
	virtual ~CCustomItemBow();
	void Init();
	void Load(CUSTOM_ITEM_BOW_INFO* info);
	void SetInfo(CUSTOM_ITEM_BOW_INFO info);
	CUSTOM_ITEM_BOW_INFO* GetInfo(int index);
	CUSTOM_ITEM_BOW_INFO* GetInfoByItem(int ItemIndex);
	BOOL GetCustomItemBowColor(int ItemIndex,float* ItemColor);
	int GetCustomItemBowEffect(int ItemIndex);
	int CheckCustomItemBow(int ItemIndex,int Type);
public:
	CUSTOM_ITEM_BOW_INFO m_CustomItemBowInfo[MAX_CUSTOM_ITEM_BOW];
};

extern CCustomItemBow gCustomItemBow;