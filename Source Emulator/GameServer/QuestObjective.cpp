// QuestObjective.cpp: implementation of the CQuestObjective class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuestObjective.h"
#include "DSProtocol.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "Monster.h"
#include "Notice.h"
#include "Party.h"
#include "Quest.h"
#include "ServerInfo.h"
#include "Util.h"

CQuestObjective gQuestObjective;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuestObjective::CQuestObjective() // OK
{
	this->m_count = 0;
}

CQuestObjective::~CQuestObjective() // OK
{

}

void CQuestObjective::Load(char* path) // OK
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

	this->m_count = 0;

	try
	{
		while (true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			QUEST_OBJECTIVE_INFO info;

			memset(&info,0,sizeof(info));

			info.Number = lpMemScript->GetNumber();

			info.Type = lpMemScript->GetAsNumber();

			info.Index = (info.Type == QUEST_OBJECTIVE_ITEM) ? SafeGetItem(GET_ITEM(lpMemScript->GetAsNumber(), lpMemScript->GetAsNumber())) : lpMemScript->GetAsNumber();

			info.Value = lpMemScript->GetAsNumber();

			info.Level = lpMemScript->GetAsNumber();

			info.MapNumber = lpMemScript->GetAsNumber();

			info.MonsterClass = lpMemScript->GetAsNumber();

			info.MonsterLevelMin = lpMemScript->GetAsNumber();

			info.MonsterLevelMax = lpMemScript->GetAsNumber();

			info.DropRate = lpMemScript->GetAsNumber();

			info.RequireIndex = lpMemScript->GetAsNumber();

			info.RequireState = lpMemScript->GetAsNumber();

			for(int n = 0; n < MAX_CLASS; n++) { info.RequireClass[n] = lpMemScript->GetAsNumber(); }

			this->SetInfo(info);

			if(info.Type == QUEST_OBJECTIVE_ITEM && IsValidItem(info.Index) == 0){Console(LOG_RED,"[%02d-%03d] Invalid ItemIndex. [%s]",info.Index/MAX_ITEM_TYPE,info.Index%MAX_ITEM_TYPE,path);}

			if(info.Type == QUEST_OBJECTIVE_MONSTER && IsValidMonster(info.MonsterClass) == 0){Console(LOG_RED,"[%d] Invalid MonsterIndex. [%s]",info.MonsterClass,path);}
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CQuestObjective::SetInfo(QUEST_OBJECTIVE_INFO info) // OK
{
	if(this->m_count < 0 || this->m_count >= MAX_QUEST_OBJECTIVE)
	{
		return;
	}

	this->m_QuestObjectiveInfo[this->m_count++] = info;
}

QUEST_OBJECTIVE_INFO* CQuestObjective::GetInfo(int index) // OK
{
	if(index < 0 || index >= this->m_count)
	{
		return 0;
	}

	return &this->m_QuestObjectiveInfo[index];
}

int CQuestObjective::GetQuestObjectiveCount(LPOBJ lpObj,QUEST_OBJECTIVE_INFO* lpInfo) // OK
{
	if(lpInfo->Type == QUEST_OBJECTIVE_NONE)
	{
		return 0;
	}

	if(lpInfo->Type == QUEST_OBJECTIVE_ITEM)
	{
		return gItemManager.GetInventoryItemCount(lpObj,lpInfo->Index,lpInfo->Level);
	}

	if(lpInfo->Type == QUEST_OBJECTIVE_MONEY)
	{
		return lpObj->Money;
	}

	#if(GAMESERVER_UPDATE>=301)
	
	if(lpInfo->Type == QUEST_OBJECTIVE_MONSTER)
	{
		return this->GetQuestObjectiveKillCount(lpObj,lpInfo);
	}

	#endif

	return 0;
}

int CQuestObjective::GetQuestObjectiveKillCount(LPOBJ lpObj,QUEST_OBJECTIVE_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=301)

	if(lpObj->QuestKillCountIndex != lpInfo->RequireIndex)
	{
		return 0;
	}

	if(lpObj->QuestKillCount[lpInfo->Number].MonsterClass != lpInfo->Index)
	{
		return 0;
	}

	return lpObj->QuestKillCount[lpInfo->Number].KillCount;

	#else

	return 0;

	#endif
}

bool CQuestObjective::CheckQuestObjectiveRequisite(LPOBJ lpObj,QUEST_OBJECTIVE_INFO* lpInfo) // OK
{
	if(lpInfo->RequireIndex != -1 && gQuest.CheckQuestListState(lpObj,lpInfo->RequireIndex,lpInfo->RequireState) == 0)
	{
		return 0;
	}

	if(lpInfo->RequireClass[lpObj->Class] == 0 || lpInfo->RequireClass[lpObj->Class] > (lpObj->ChangeUp+1))
	{
		return 0;
	}

	return 1;
}

bool CQuestObjective::CheckQuestObjective(LPOBJ lpObj,int QuestIndex) // OK
{
	for(int n = 0; n < this->m_count; n++)
	{
		QUEST_OBJECTIVE_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->RequireIndex != QuestIndex)
		{
			continue;
		}

		if(this->CheckQuestObjectiveRequisite(lpObj,lpInfo) == 0)
		{
			continue;
		}

		if(this->GetQuestObjectiveCount(lpObj,lpInfo) < lpInfo->Value)
		{
			return 0;
		}
	}

	return 1;
}

bool CQuestObjective::CheckQuestObjectiveItemCount(LPOBJ lpObj,int ItemIndex,int ItemLevel) // OK
{
	for(int n = 0; n < this->m_count; n++)
	{
		QUEST_OBJECTIVE_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(this->CheckQuestObjectiveRequisite(lpObj,lpInfo) == 0)
		{
			continue;
		}

		if(lpInfo->Type != QUEST_OBJECTIVE_ITEM)
		{
			continue;
		}

		if(lpInfo->Index == ItemIndex && lpInfo->Level == ItemLevel && lpInfo->Value <= this->GetQuestObjectiveCount(lpObj,lpInfo))
		{
			return 0;
		}
	}

	return 1;
}

void CQuestObjective::AddQuestObjectiveKillCount(LPOBJ lpObj,QUEST_OBJECTIVE_INFO* lpInfo) // OK
{
	#if(GAMESERVER_UPDATE>=301)

	if(lpObj->QuestKillCountIndex != lpInfo->RequireIndex)
	{
		return;
	}

	if(lpObj->QuestKillCount[lpInfo->Number].MonsterClass != lpInfo->Index)
	{
		return;
	}

	lpObj->QuestKillCount[lpInfo->Number].KillCount++;

	#endif
}

void CQuestObjective::InitQuestObjectiveKillCount(LPOBJ lpObj,int QuestIndex) // OK
{
	#if(GAMESERVER_UPDATE>=301)

	for(int n = 0; n < this->m_count; n++)
	{
		QUEST_OBJECTIVE_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->RequireIndex != QuestIndex)
		{
			continue;
		}

		if(this->CheckQuestObjectiveRequisite(lpObj,lpInfo) == 0)
		{
			continue;
		}

		if(lpInfo->Type != QUEST_OBJECTIVE_MONSTER)
		{
			continue;
		}

		lpObj->QuestKillCountIndex = QuestIndex;

		lpObj->QuestKillCount[lpInfo->Number].MonsterClass = lpInfo->Index;

		lpObj->QuestKillCount[lpInfo->Number].KillCount = 0;
	}

	#endif
}

void CQuestObjective::RemoveQuestObjective(LPOBJ lpObj,int QuestIndex) // OK
{
	for(int n = 0; n < this->m_count; n++)
	{
		QUEST_OBJECTIVE_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->RequireIndex != QuestIndex)
		{
			continue;
		}

		if(this->CheckQuestObjectiveRequisite(lpObj,lpInfo) == 0)
		{
			continue;
		}

		if(lpInfo->Type == QUEST_OBJECTIVE_NONE)
		{
			continue;
		}

		if(lpInfo->Type == QUEST_OBJECTIVE_ITEM)
		{
			gItemManager.DeleteInventoryItemCount(lpObj,lpInfo->Index,lpInfo->Level,lpInfo->Value);
			continue;
		}

		if(lpInfo->Type == QUEST_OBJECTIVE_MONEY)
		{
			lpObj->Money = (((lpObj->Money - lpInfo->Value)<0) ? 0 : (lpObj->Money - lpInfo->Value));
			GCMoneySend(lpObj->Index,lpObj->Money);
			continue;
		}

		#if(GAMESERVER_UPDATE>=301)
		
		if(lpInfo->Type == QUEST_OBJECTIVE_MONSTER)
		{
			lpObj->QuestKillCountIndex = -1;
			lpObj->QuestKillCount[lpInfo->Number].MonsterClass = -1;
			lpObj->QuestKillCount[lpInfo->Number].KillCount = 0;
			continue;
		}

		#endif
	}
}

bool CQuestObjective::MonsterItemDrop(LPOBJ lpMonster) // OK
{
	int aIndex = gObjMonsterGetTopHitDamageUser(lpMonster);

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return 0;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(OBJECT_RANGE(lpObj->PartyNumber) != 0 && gServerInfo.m_QuestMonsterItemDropParty != 0)
	{
		return this->MonsterItemDropParty(lpMonster,lpObj->PartyNumber);
	}

	for(int n = 0; n < this->m_count; n++)
	{
		QUEST_OBJECTIVE_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(this->CheckQuestObjectiveRequisite(lpObj,lpInfo) == 0)
		{
			continue;
		}

		if(lpInfo->Type != QUEST_OBJECTIVE_ITEM)
		{
			continue;
		}

		if(lpInfo->MapNumber != -1 && lpInfo->MapNumber != lpMonster->Map)
		{
			continue;
		}

		if(lpInfo->MonsterClass != -1 && lpInfo->MonsterClass != lpMonster->Class)
		{
			continue;
		}

		if(lpInfo->MonsterLevelMin != -1 && lpInfo->MonsterLevelMin > lpMonster->Level)
		{
			continue;
		}

		if(lpInfo->MonsterLevelMax != -1 && lpInfo->MonsterLevelMax < lpMonster->Level)
		{
			continue;
		}

		if(lpInfo->DropRate >(GetLargeRand() % 1000000) && lpInfo->Value > this->GetQuestObjectiveCount(lpObj,lpInfo))
		{
			GDCreateItemSend(aIndex,lpMonster->Map,(BYTE)lpMonster->X,(BYTE)lpMonster->Y,lpInfo->Index,lpInfo->Level,0,0,0,0,aIndex,0,0,0,0,0,0xFF,0);
			return 1;
		}
	}

	return 0;
}

bool CQuestObjective::MonsterItemDropParty(LPOBJ lpMonster,int PartyNumber) // OK
{
	for(int n = 0; n < MAX_PARTY_USER; n++)
	{
		int aIndex = gParty.m_PartyInfo[PartyNumber].Index[n];

		if(OBJECT_RANGE(aIndex) == 0)
		{
			continue;
		}

		LPOBJ lpObj = &gObj[aIndex];

		for(int i = 0; i < this->m_count; i++)
		{
			QUEST_OBJECTIVE_INFO* lpInfo = this->GetInfo(i);

			if(lpInfo == 0)
			{
				continue;
			}

			if(this->CheckQuestObjectiveRequisite(lpObj,lpInfo) == 0)
			{
				continue;
			}

			if(lpInfo->Type != QUEST_OBJECTIVE_ITEM)
			{
				continue;
			}

			if(lpInfo->MapNumber != -1 && lpInfo->MapNumber != lpMonster->Map)
			{
				continue;
			}

			if(lpInfo->MonsterClass != -1 && lpInfo->MonsterClass != lpMonster->Class)
			{
				continue;
			}

			if(lpInfo->MonsterLevelMin != -1 && lpInfo->MonsterLevelMin > lpMonster->Level)
			{
				continue;
			}

			if(lpInfo->MonsterLevelMax != -1 && lpInfo->MonsterLevelMax < lpMonster->Level)
			{
				continue;
			}

			if(lpInfo->DropRate >(GetLargeRand() % 1000000) && lpInfo->Value > this->GetQuestObjectiveCount(lpObj,lpInfo))
			{
				GDCreateItemSend(aIndex,lpMonster->Map,(BYTE)lpMonster->X,(BYTE)lpMonster->Y,lpInfo->Index,lpInfo->Level,0,0,0,0,aIndex,0,0,0,0,0,0xFF,0);
				return 1;
			}
		}
	}

	return 0;
}

void CQuestObjective::MonsterKill(LPOBJ lpMonster) // OK
{
	int aIndex = gObjMonsterGetTopHitDamageUser(lpMonster);

	if(OBJECT_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(OBJECT_RANGE(lpObj->PartyNumber) != 0 && gServerInfo.m_QuestMonsterKillParty != 0)
	{
		return this->MonsterKillParty(lpMonster,lpObj->PartyNumber);
	}

	for(int n = 0; n < this->m_count; n++)
	{
		QUEST_OBJECTIVE_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(this->CheckQuestObjectiveRequisite(lpObj,lpInfo) == 0)
		{
			continue;
		}

		if(lpInfo->Type != QUEST_OBJECTIVE_MONSTER)
		{
			continue;
		}

		if(lpInfo->MapNumber != -1 && lpInfo->MapNumber != lpMonster->Map)
		{
			continue;
		}

		#if(GAMESERVER_UPDATE>=301)
		
		if(lpInfo->Index == lpMonster->Class && lpInfo->Value > this->GetQuestObjectiveCount(lpObj,lpInfo))
		{
			this->AddQuestObjectiveKillCount(lpObj,lpInfo);
			gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,"%s %d/%d",lpMonster->MonsterName,this->GetQuestObjectiveCount(lpObj,lpInfo),lpInfo->Value);
			return;
		}

		#endif
	}
}

void CQuestObjective::MonsterKillParty(LPOBJ lpMonster,int PartyNumber) // OK
{
	for(int n = 0; n < MAX_PARTY_USER; n++)
	{
		int aIndex = gParty.m_PartyInfo[PartyNumber].Index[n];

		if(OBJECT_RANGE(aIndex) == 0)
		{
			continue;
		}

		LPOBJ lpObj = &gObj[aIndex];

		for(int i = 0; i < this->m_count; i++)
		{
			QUEST_OBJECTIVE_INFO* lpInfo = this->GetInfo(i);

			if(lpInfo == 0)
			{
				continue;
			}

			if(this->CheckQuestObjectiveRequisite(lpObj,lpInfo) == 0)
			{
				continue;
			}

			if(lpInfo->Type != QUEST_OBJECTIVE_MONSTER)
			{
				continue;
			}

			if(lpInfo->MapNumber != -1 && lpInfo->MapNumber != lpMonster->Map)
			{
				continue;
			}

			#if(GAMESERVER_UPDATE>=301)

			if(lpInfo->Index == lpMonster->Class && lpInfo->Value > this->GetQuestObjectiveCount(lpObj,lpInfo))
			{
				this->AddQuestObjectiveKillCount(lpObj,lpInfo);
				gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,"%s %d/%d",lpMonster->MonsterName,this->GetQuestObjectiveCount(lpObj,lpInfo),lpInfo->Value);
				return;
			}

			#endif
		}
	}
}