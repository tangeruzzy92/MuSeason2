// CustomJewel.h: interface for the CCustomJewel class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_JEWEL 50

struct CUSTOM_JEWEL_INFO
{
	int Index;
	int ItemIndex;
	int EnableSlotWeapon;
	int EnableSlotArmor;
	int EnableSlotWing;
	int SalePrice;
	char ModelName[32];
};

class CCustomJewel
{
public:
	CCustomJewel();
	virtual ~CCustomJewel();
	void Init();
	void Load(CUSTOM_JEWEL_INFO* info);
	void SetInfo(CUSTOM_JEWEL_INFO info);
	CUSTOM_JEWEL_INFO* GetInfo(int index);
	CUSTOM_JEWEL_INFO* GetInfoByItem(int ItemIndex);
	BOOL CheckCustomJewelByItem(int ItemIndex);
	int GetCustomJewelSalePrice(int ItemIndex);
public:
	CUSTOM_JEWEL_INFO m_CustomJewelInfo[MAX_CUSTOM_JEWEL];
};

extern CCustomJewel gCustomJewel;
