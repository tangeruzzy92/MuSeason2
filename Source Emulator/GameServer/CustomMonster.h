// CustomMonster.h: interface for the CCustomMonster class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"

struct CUSTOM_MONSTER_INFO
{
	int MonsterClass;
	int MapNumber;
	int MaxLife;
	int DamageMin;
	int DamageMax;
	int Defense;
	int AttackRate;
	int DefenseRate;
	int ExperienceRate;
	int KillMessage;
	int RewardMessage;
	int RewardCoin1;
	int RewardCoin2;
	int RewardCoin3;
};

class CCustomMonster
{
public:
	CCustomMonster();
	virtual ~CCustomMonster();
	void Load(char* path);
	void SetCustomMonsterInfo(LPOBJ lpObj);
	void MonsterDieProc(LPOBJ lpObj,LPOBJ lpTarget);
	long GetCustomMonsterExperienceRate(int index,int map);
	long GetCustomMonsterMasterExperienceRate(int index,int map);
	bool GetCustomMonsterInfo(int index,int map,CUSTOM_MONSTER_INFO* lpInfo);
private:
	std::vector<CUSTOM_MONSTER_INFO> m_CustomMonsterInfo;
};

extern CCustomMonster gCustomMonster;
