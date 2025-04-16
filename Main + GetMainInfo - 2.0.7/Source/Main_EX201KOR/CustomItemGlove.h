// CustomItemGlove.h: interface for the CCustomItemGlove class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_ITEM_GLOVE 10

struct CUSTOM_ITEM_GLOVE_INFO
{
	int Index;
	int ItemIndex;
	int ItemL;
	int ItemR;
	int ColorR;
	int ColorG;
	int ColorB;
	char ModelName[32];
	char ModelNameL[32];
	char ModelNameR[32];
};

class CCustomItemGlove
{
public:
	CCustomItemGlove();
	virtual ~CCustomItemGlove();
	void Init();
	void Load(CUSTOM_ITEM_GLOVE_INFO* info);
	void SetInfo(CUSTOM_ITEM_GLOVE_INFO info);
	CUSTOM_ITEM_GLOVE_INFO* GetInfo(int index);
	CUSTOM_ITEM_GLOVE_INFO* GetInfoByItem(int ItemIndex);
	BOOL GetCustomItemGloveColor(int ItemIndex,float* ItemColor);
	int CheckCustomItemGlove(int ItemIndex);
public:
	CUSTOM_ITEM_GLOVE_INFO m_CustomItemGloveInfo[MAX_CUSTOM_ITEM_GLOVE];
};

extern CCustomItemGlove gCustomItemGlove;