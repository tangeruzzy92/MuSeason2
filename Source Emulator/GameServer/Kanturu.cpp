// Kanturu.cpp: implementation of the CKanturu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Kanturu.h"
#include "KanturuBattleUserMng.h"
#include "KanturuMonsterMng.h"
#include "KanturuUtil.h"
#include "MemScript.h"
#include "Monster.h"
#include "Path.h"
#include "ServerInfo.h"
#include "User.h"
#include "Util.h"

CKanturu gKanturu;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKanturu::CKanturu() // OK
{
	this->SetKanturuEnable(0);

	this->SetKanturuState(KANTURU_STATE_NONE);

	this->SetEnableCheckMoonStone(0);

	this->ResetAllData();
}

CKanturu::~CKanturu() // OK
{

}

void CKanturu::ResetAllData() // OK
{
	for(int n=0;n < KANTURU_STATE_MAX;n++)
	{
		this->m_StateInfo[n].ResetTimeInfo();
	}

	this->m_StateInfoCount = 0;
}

void CKanturu::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->ResetAllData();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					int state = lpMemScript->GetNumber();

					int condition = lpMemScript->GetAsNumber();

					int value = lpMemScript->GetAsNumber();

					this->m_StateInfo[this->m_StateInfoCount].SetStateInfo(state);

					this->m_StateInfo[this->m_StateInfoCount].SetCondition(condition);

					this->m_StateInfo[this->m_StateInfoCount].SetValue(((condition==1)?(value*1000):value));

					this->m_StateInfoCount++;
				}
				else if(section == 10)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->SetEnableCheckMoonStone(lpMemScript->GetNumber());
				}
				else
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	this->m_BattleStanby.Load(path);

	this->m_BattleOfMaya.Load(path);

	this->m_BattleOfNightmare.Load(path);

	this->m_TowerOfRefinement.Load(path);

	delete lpMemScript;
}

void CKanturu::MainProc() // OK
{
	if(gServerInfo.m_KanturuEvent == 0)
	{
		return;
	}

	this->CheckStateTime();

	switch(this->m_KanturuState)
	{
		case KANTURU_STATE_NONE:
			this->ProcState_NONE();
			break;
		case KANTURU_STATE_BATTLE_STANDBY:
			this->ProcState_BATTLE_STANDBY();
			break;
		case KANTURU_STATE_BATTLE_OF_MAYA:
			this->ProcState_BATTLE_OF_MAYA();
			break;
		case KANTURU_STATE_BATTLE_OF_NIGHTMARE:
			this->ProcState_BATTLE_OF_NIGHTMARE();
			break;
		case KANTURU_STATE_TOWER_OF_REFINEMENT:
			this->ProcState_TOWER_OF_REFINEMENT();
			break;
		case KANTURU_STATE_END:
			this->ProcState_END();
			break;
	}
}

void CKanturu::ProcState_NONE() // OK
{
	this->SetState(KANTURU_STATE_BATTLE_STANDBY);
}

void CKanturu::ProcState_BATTLE_STANDBY() // OK
{
	if(this->m_BattleStanby.GetBattleStanbyState() == KANTURU_STANBY_END)
	{
		this->m_BattleStanby.SetState_NONE();
		this->SetState(KANTURU_STATE_BATTLE_OF_MAYA);
		return;
	}

	this->m_BattleStanby.MainProc();
}

void CKanturu::ProcState_BATTLE_OF_MAYA() // OK
{
	if(this->m_BattleOfMaya.GetBattleOfMayaState() == KANTURU_MAYA_ENDCYCLE)
	{
		this->m_BattleOfMaya.SetState_NONE();
		this->SetState(((this->m_BattleOfMaya.GetSuccessValue()==0)?KANTURU_STATE_END:KANTURU_STATE_BATTLE_OF_NIGHTMARE));
		return;
	}

	this->m_BattleOfMaya.MainProc();
}

void CKanturu::ProcState_BATTLE_OF_NIGHTMARE() // OK
{
	if(this->m_BattleOfNightmare.GetBattleOfNightmareState() == KANTURU_NIGHTMARE_ENDCYCLE)
	{
		this->m_BattleOfNightmare.SetState_NONE();
		this->SetState(((this->m_BattleOfNightmare.GetSuccessValue()==0)?KANTURU_STATE_END:KANTURU_STATE_TOWER_OF_REFINEMENT));
		return;
	}

	this->m_BattleOfNightmare.MainProc();
}

void CKanturu::ProcState_TOWER_OF_REFINEMENT() // OK
{
	if(this->m_TowerOfRefinement.GetTowerOfRefinementState() == KANTURU_TOWER_OF_REFINEMENT_END)
	{
		this->m_TowerOfRefinement.SetState_NONE();
		this->SetState(KANTURU_STATE_END);
		return;
	}

	this->m_TowerOfRefinement.MainProc();
}

void CKanturu::ProcState_END() // OK
{
	this->SetState(KANTURU_STATE_NONE);
}

void CKanturu::SetState(int state) // OK
{
	this->m_StateInfo[state].SetConditionAppliedTime();

	gKanturuMonsterMng.ResetRegenMonsterObjData();

	this->SetKanturuMapAttr(0);

	switch(state)
	{
		case KANTURU_STATE_NONE:
			this->SetState_NONE();
			break;
		case KANTURU_STATE_BATTLE_STANDBY:
			this->SetState_BATTLE_STANDBY();
			break;
		case KANTURU_STATE_BATTLE_OF_MAYA:
			this->SetState_BATTLE_OF_MAYA();
			break;
		case KANTURU_STATE_BATTLE_OF_NIGHTMARE:
			this->SetState_BATTLE_OF_NIGHTMARE();
			break;
		case KANTURU_STATE_TOWER_OF_REFINEMENT:
			this->SetState_TOWER_OF_REFINEMENT();
			break;
		case KANTURU_STATE_END:
			this->SetState_END();
			break;
	}
}

void CKanturu::SetState_NONE() // OK
{
	this->SetKanturuState(KANTURU_STATE_NONE);
}

void CKanturu::SetState_BATTLE_STANDBY() // OK
{
	LogAdd(LOG_CIAN,"[Kanturu] SetState STAND");

	gKanturuBattleUserMng.ResetAllData();

	this->SetKanturuState(KANTURU_STATE_BATTLE_STANDBY);

	this->m_BattleStanby.SetState(KANTURU_STANBY_START);
}

void CKanturu::SetState_BATTLE_OF_MAYA() // OK
{
	this->SetKanturuState(KANTURU_STATE_BATTLE_OF_MAYA);

	this->m_BattleOfMaya.SetState(KANTURU_MAYA_STANDBY_1);
}

void CKanturu::SetState_BATTLE_OF_NIGHTMARE() // OK
{
	this->SetKanturuState(KANTURU_STATE_BATTLE_OF_NIGHTMARE);

	this->m_BattleOfNightmare.SetState(KANTURU_NIGHTMARE_IDLE);
}

void CKanturu::SetState_TOWER_OF_REFINEMENT() // OK
{
	this->SetKanturuState(KANTURU_STATE_TOWER_OF_REFINEMENT);

	this->m_TowerOfRefinement.SetState(KANTURU_TOWER_OF_REFINEMENT_REVITALIZATION);

	this->SetKanturuMapAttr(1);
}

void CKanturu::SetState_END() // OK
{
	LogAdd(LOG_CIAN,"[Kanturu] SetState END");

	this->SetKanturuState(KANTURU_STATE_END);

	gKanturuBattleUserMng.ResetAllData();
}

void CKanturu::CheckStateTime() // OK
{
	if(this->GetKanturuState() != KANTURU_STATE_NONE && this->m_StateInfo[this->GetKanturuState()].GetCondition() == 1 && this->m_StateInfo[this->GetKanturuState()].IsTimeOut() != 0)
	{
		this->SetState(((this->GetKanturuState()==KANTURU_STATE_END)?KANTURU_STATE_NONE:(this->GetKanturuState()+1)));
	}
}

bool CKanturu::CheckEnterKanturu(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return 0;
	}

	if(lpObj->Map != MAP_KANTURU2)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,4);
		return 0;
	}

	if(this->GetKanturuState() != KANTURU_STATE_BATTLE_OF_MAYA)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,3);
		return 0;
	}

	if(this->m_BattleOfMaya.GetEntrancePermit() == 0)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,3);
		return 0;
	}

	if(gKanturuBattleUserMng.IsOverMaxUser() != 0)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,1);
		return 0;
	}

	if(this->CheckEquipmentMoonStone(aIndex) == 0)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,2);
		return 0;
	}

	if(lpObj->Inventory[INVENTORY_SLOT_HELPER].m_Index == GET_ITEM(13,2))
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,5);
		return 0;
	}

	if(lpObj->Change >= 0)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,6);
		return 0;
	}

	if(lpObj->Inventory[INVENTORY_SLOT_WING].IsItem() == 0 && lpObj->Inventory[INVENTORY_SLOT_HELPER].m_Index != GET_ITEM(13,3) && lpObj->Inventory[INVENTORY_SLOT_HELPER].m_Index != GET_ITEM(13,37))
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,7);
		return 0;
	}

	return 1;
}

bool CKanturu::CheckEnterKanturuRefinery(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return 0;
	}

	if(lpObj->Map != MAP_KANTURU2)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,4);
		return 0;
	}

	if(this->GetKanturuState() != KANTURU_STATE_TOWER_OF_REFINEMENT)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,3);
		return 0;
	}

	if(this->m_TowerOfRefinement.GetEntrancePermit() == 0)
	{
		gKanturuUtil.NotifyKanturuEnter(aIndex,3);
		return 0;
	}

	return 1;
}

bool CKanturu::CheckCanEnterKanturuBattle() // OK
{
	if(this->GetKanturuState() == KANTURU_STATE_BATTLE_OF_MAYA && this->m_BattleOfMaya.GetEntrancePermit() != 0)
	{
		return 1;
	}

	if(this->GetKanturuState() == KANTURU_STATE_TOWER_OF_REFINEMENT && this->m_TowerOfRefinement.GetEntrancePermit() != 0 && this->m_TowerOfRefinement.GetUseTowerOfRefinement() != 0)
	{
		return 1;
	}

	return 0;
}

bool CKanturu::CheckEquipmentMoonStone(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if(this->GetEnableCheckMoonStone() == 0)
	{
		return 1;
	}

	if(lpObj->Inventory[INVENTORY_SLOT_RING1].IsItem() != 0 && lpObj->Inventory[INVENTORY_SLOT_RING1].m_Index == GET_ITEM(13,38) && lpObj->Inventory[INVENTORY_SLOT_RING1].m_Durability > 0)
	{
		return 1;
	}

	if(lpObj->Inventory[INVENTORY_SLOT_RING2].IsItem() != 0 && lpObj->Inventory[INVENTORY_SLOT_RING2].m_Index == GET_ITEM(13,38) && lpObj->Inventory[INVENTORY_SLOT_RING2].m_Durability > 0)
	{
		return 1;
	}

	return 0;
}

void CKanturu::KanturuMonsterDieProc(LPOBJ lpObj,LPOBJ lpTarget) // OK
{
	int aIndex = gObjMonsterGetTopHitDamageUser(lpObj);

	if(OBJECT_RANGE(aIndex) != 0)
	{
		lpTarget = &gObj[aIndex];
	}

	gKanturuMonsterMng.MonsterDie(lpObj->Index);
}

void CKanturu::LoadKanturuMapAttr(char* path,int level) // OK
{
	if(level < 0 || level >= MAX_KANTURU_MAP_LEVEL)
	{
		return;
	}

	this->m_KanturuMap[level].Load(path,MAP_KANTURU3);
}

void CKanturu::SetKanturuMapAttr(int level) // OK
{
	if(level < 0 || level >= MAX_KANTURU_MAP_LEVEL)
	{
		return;
	}

	memcpy(gMap[MAP_KANTURU3].m_MapAttr,this->m_KanturuMap[level].m_MapAttr,(this->m_KanturuMap[level].m_width*this->m_KanturuMap[level].m_height));
}

void CKanturu::SetKanturuEnable(int enable) // OK
{
	this->m_KanturuEnable = enable;
}

void CKanturu::SetKanturuState(int state) // OK
{
	this->m_KanturuState = state;
}

void CKanturu::SetEnableCheckMoonStone(int enable) // OK
{
	this->m_EnableCheckMoonStone = enable;
}

int CKanturu::GetKanturuEnable() // OK
{
	return this->m_KanturuEnable;
}

int CKanturu::GetKanturuState() // OK
{
	return this->m_KanturuState;
}

int CKanturu::GetKanturuDetailState() // OK
{
	switch(this->GetKanturuState())
	{
		case KANTURU_STATE_BATTLE_STANDBY:
			return this->m_BattleStanby.GetBattleStanbyState();
			break;
		case KANTURU_STATE_BATTLE_OF_MAYA:
			return this->m_BattleOfMaya.GetBattleOfMayaState();
			break;
		case KANTURU_STATE_BATTLE_OF_NIGHTMARE:
			return this->m_BattleOfNightmare.GetBattleOfNightmareState();
			break;
		case KANTURU_STATE_TOWER_OF_REFINEMENT:
			return this->m_TowerOfRefinement.GetTowerOfRefinementState();
			break;
	}

	return KANTURU_STATE_NONE;
}

int CKanturu::GetRemainTime() // OK
{
	switch(this->GetKanturuState())
	{
		case KANTURU_STATE_BATTLE_STANDBY:
			return this->m_BattleStanby.GetRemainTime();
			break;
		case KANTURU_STATE_BATTLE_OF_MAYA:
			return this->m_BattleOfMaya.GetRemainTime();
			break;
		case KANTURU_STATE_BATTLE_OF_NIGHTMARE:
			return this->m_BattleOfNightmare.GetRemainTime();
			break;
		case KANTURU_STATE_TOWER_OF_REFINEMENT:
			return this->m_TowerOfRefinement.GetRemainTime();
			break;
	}

	return 0;
}

int CKanturu::GetEnableCheckMoonStone() // OK
{
	return this->m_EnableCheckMoonStone;
}

bool CKanturu::CheckInEvent() // OK
{
	switch(this->GetKanturuState())
	{
		case KANTURU_STATE_BATTLE_OF_MAYA:
		{
			switch (this->GetKanturuDetailState())
			{
				case KANTURU_MAYA_START_1:
				case KANTURU_MAYA_1:
				case KANTURU_MAYA_START_2:
				case KANTURU_MAYA_2:
				case KANTURU_MAYA_START_3:
				case KANTURU_MAYA_3:
					return 1;
			}
		}
		break;
		case KANTURU_STATE_BATTLE_OF_NIGHTMARE:
		{
			if(this->GetKanturuDetailState() == KANTURU_NIGHTMARE_START)
			{
				return 1;
			}
		}
		break;
	}

	return 0;
}
