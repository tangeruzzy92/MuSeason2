// Protect.h: interface for the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CustomEffect.h"
#include "CustomItem.h"
#include "CustomItemBow.h"
#include "CustomItemGlove.h"
#include "CustomJewel.h"
#include "CustomMap.h"
#include "CustomMonster.h"
#include "CustomMonsterSkin.h"
#include "CustomTooltip.h"
#include "CustomWing.h"
#include "ItemStack.h"
#include "ItemValue.h"

struct MAIN_FILE_INFO
{
	char CustomerName[32];
	BYTE LauncherStart;
	char LauncherMutex[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[32];
	char ScreenShotPath[50];
	char ClientName[32];
	DWORD ClientNameCRC;
	char PluginName[3][32];
	DWORD PluginNameCRC[4];
	BYTE HelperActiveAlert;
	BYTE HelperActiveLevel;
	DWORD MaxAttackSpeed[7];
	BYTE AttackAnimationValue[7];
	BYTE KeyCodeHealthBarSwitch;
	BYTE KeyCodeCamera3DSwitch;
	BYTE KeyCodeCamera3DRestore;
	BYTE KeyCodeTrayModeSwitch;
	DWORD ReconnectTime;
	int m_BloodCastleEntryLevelCommon[7][2];
	int m_BloodCastleEntryLevelSpecial[7][2];
	int m_DevilSquareEntryLevelCommon[6][2];
	int m_DevilSquareEntryLevelSpecial[6][2];
	int m_ChaosCastleEntryLevelCommon[6][2];
	int m_ChaosCastleEntryLevelSpecial[6][2];
	int m_KalimaEntryLevelCommon[7][2];
	int m_KalimaEntryLevelSpecial[7][2];
	int m_IllusionTempleEntryLevelMin[5];
	int m_IllusionTempleEntryLevelMax[5];
	CUSTOM_EFFECT_INFO CustomEffectInfo[MAX_CUSTOM_EFFECT];
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_ITEM_BOW_INFO CustomItemBowInfo[MAX_CUSTOM_ITEM_BOW];
	CUSTOM_ITEM_GLOVE_INFO CustomItemGloveInfo[MAX_CUSTOM_ITEM_GLOVE];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_MAP_INFO CustomMapInfo[MAX_CUSTOM_MAP];
	CUSTOM_MONSTER_INFO CustomMonsterInfo[MAX_CUSTOM_MONSTER];
	CUSTOM_MONSTER_SKIN_INFO CustomMonsterSkinInfo[MAX_CUSTOM_MONSTER_SKIN];
	CUSTOM_TOOLTIP_INFO CustomTooltipInfo[MAX_CUSTOM_TOOLTIP];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	ITEM_STACK_INFO ItemStackInfo[MAX_ITEM_STACK_INFO];
	ITEM_VALUE_INFO ItemValueInfo[MAX_ITEM_VALUE_INFO];
};

class CProtect
{
public:
	CProtect();
	virtual ~CProtect();
	bool ReadMainFile(char* name);
	void CheckLauncher();
	void CheckInstance();
	void CheckClientFile();
	void CheckPluginFile();
public:
	MAIN_FILE_INFO m_MainInfo;
	DWORD m_ClientFileCRC;
};

extern CProtect gProtect;