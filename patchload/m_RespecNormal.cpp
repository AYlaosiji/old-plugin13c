#include"pch.h"
#ifdef MODULES_RESPECNORMAL

BOOL m_RespecNormal_IsOn = FALSE;
DWORD m_RespecNormal_Pspell = 0;
static BOOL m_RespecNormal_ChangeSkillPerLevelUp = FALSE;
static DWORD m_RespecNormal_SkillPerLevelUp;

static BOOL __fastcall m_RespecNormal_pSpellFuction(GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem1, UnitAny* pItem2, DWORD it, DWORD flag1, DWORD flag2);
void m_RespecNormal_changeSkillPerLevelUp();

void m_RespecNormal_LoadCfg()
{
	m_RespecNormal_IsOn= cfgload::GetModuleCfgBool("Respec Normal", "Pspell Respec Normal IsOn");
	m_RespecNormal_Pspell= cfgload::GetModuleCfgInt("Respec Normal", "Pspell Respec Normal Pspell");

	m_RespecNormal_ChangeSkillPerLevelUp = cfgload::GetModuleCfgBool("Respec Normal", "Change Skill Per Level Up IsOn");
	m_RespecNormal_SkillPerLevelUp = cfgload::GetModuleCfgInt("Respec Normal", "Skill Per Level Up Value");
}

void m_RespecNormal_Install()
{
	//È¡ÎïÆ·
#ifdef D2SERVER
	DWORD offset = 0;
	if (m_RespecNormal_IsOn)
	{
		offset= D2Game::GetAddress(0x10723C + 8 * m_RespecNormal_Pspell);
		Memory::SetCursor(offset);
		Memory::ChangeDword(0x00000000, (DWORD)m_RespecNormal_pSpellFuction);
	}

	if (m_RespecNormal_ChangeSkillPerLevelUp)
	{
		offset = D2Game::GetAddress(0xEB1E5);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Common::D2AddUnitStat, (DWORD)m_RespecNormal_changeSkillPerLevelUp);
	}
#endif
}

void m_RespecNormal_UnInstall()
{

}

#ifdef D2SERVER
void __fastcall ResetPlayerAllQuestFlags(UnitAny* pPlayer)
{
	PlayerData* pPlayerData = pPlayer->ptPlayerData;
	int diff = 3;
	do
	{
		QuestInfo* pQuestFlags = pPlayerData->ptQuest[--diff];
		memset(pQuestFlags->pBuffer, 0, 0x60);
	} while (diff);
}

void __fastcall ResetPlayerAllWaypoints(UnitAny* pPlayer)
{
	PlayerData* pPlayerData = pPlayer->ptPlayerData;
	int diff = 3;
	do
	{
		Waypoint* pWaypoint = pPlayerData->pWaypoints[--diff];
		memset(pWaypoint, 0, sizeof(pWaypoint));
	} while (diff);
}

void NormalResetSkills(UnitAny* pPlayer)
{
	DWORD SkillCount = D2Common::D2GetClassSkillCount(pPlayer->nPlayerClass);
	if (!SkillCount)return;
	for (DWORD i = 0; i < SkillCount; i++)
	{
		DWORD skillid = D2Common::D2GetClassSkillID(pPlayer->nPlayerClass, i);
		Skill* kkkp = D2Common::D2GetSkill(pPlayer, skillid);
		if (kkkp)
		{
			DWORD skilllv = D2Common::D2GetSkillLevel(pPlayer, kkkp, FALSE);
			DWORD total = 0;
			if (skilllv > 40)
			{
				total = total + (skilllv - 40) * 3;
				skilllv = 40;
			}
			if (skilllv > 20)
			{
				total = total + (skilllv - 20) * 2;
				skilllv =20;
			}
			if (skilllv > 0)
			{
				total = total + skilllv;
				skilllv = 0;
			}
			D2Common::D2AddUnitStat(pPlayer, STATS_NEWSKILLS, total, 0x0);
			kkkp->slvl = 0;
			D2Game::D2SendPacket21ToUpdateSkills(pPlayer->ptPlayerData->ptNetClient, pPlayer, skillid, 0, 1);
		}
	}
	return;
}

void UnassignStr(UnitAny* ptChar, int nb)
{
	int currentStr, removePtsNb;
	CharStatsBIN* charStats = D2Common::D2GetCharStatsBIN(ptChar->nPlayerClass);

	currentStr = D2Common::D2GetUnitBaseStat(ptChar, STATS_STRENGTH, 0);
	if (currentStr <= charStats->baseSTR) return;
	removePtsNb = currentStr - charStats->baseSTR >= nb ? nb : currentStr - charStats->baseSTR;
	if (currentStr - removePtsNb < 1) removePtsNb = currentStr - 1;

	//LogMsg("Start Unassign Strengh (cur %d, base %d, rem %d)\n", currentStr, charStats->baseSTR, removePtsNb);
	D2Common::D2AddUnitStat(ptChar, STATS_STRENGTH, -removePtsNb, 0);
	D2Common::D2AddUnitStat(ptChar, STATS_STATPTS, removePtsNb, 0);
}

void UnassignDex(UnitAny* ptChar, int nb)
{
	int currentDex, removePtsNb;
	CharStatsBIN* charStats = D2Common::D2GetCharStatsBIN(ptChar->nPlayerClass);

	currentDex = D2Common::D2GetUnitBaseStat(ptChar, STATS_DEXTERITY, 0);
	if (currentDex <= charStats->baseDEX) return;
	removePtsNb = currentDex - charStats->baseDEX >= nb ? nb : currentDex - charStats->baseDEX;
	if (currentDex - removePtsNb < 1) removePtsNb = currentDex - 1;

	D2Common::D2AddUnitStat(ptChar, STATS_DEXTERITY, -removePtsNb, 0);
	D2Common::D2AddUnitStat(ptChar, STATS_STATPTS, removePtsNb, 0);
}

void UnassignVit(UnitAny* ptChar, int nb)
{

	int currentVit, removePtsNb, removeVitNb, removeStaNb;
	CharStatsBIN* charStats = D2Common::D2GetCharStatsBIN(ptChar->nPlayerClass);

	currentVit = D2Common::D2GetUnitBaseStat(ptChar, STATS_VITALITY, 0);
	if (currentVit <= charStats->baseVIT) return;
	removePtsNb = currentVit - charStats->baseVIT >= nb ? nb : currentVit - charStats->baseVIT;
	if (currentVit - removePtsNb < 1) removePtsNb = currentVit - 1;
	removeVitNb = removePtsNb * (charStats->lifePerVitality << 6);
	removeStaNb = removePtsNb * (charStats->staminaPerVitality << 6);

	D2Common::D2AddUnitStat(ptChar, STATS_VITALITY, -removePtsNb, 0);
	D2Common::D2AddUnitStat(ptChar, STATS_MAXHP, -removeVitNb, 0);
	D2Common::D2AddUnitStat(ptChar, STATS_MAXSTAMINA, -removeStaNb, 0);
	D2Common::D2AddUnitStat(ptChar, STATS_STATPTS, removePtsNb, 0);
}

void UnassignEne(UnitAny* ptChar, int nb)
{
	int currentEne, removePtsNb, removeManNb;
	CharStatsBIN* charStats = D2Common::D2GetCharStatsBIN(ptChar->nPlayerClass);

	currentEne = D2Common::D2GetUnitBaseStat(ptChar, STATS_ENERGY, 0);
	if (currentEne <= charStats->baseENE) return;
	removePtsNb = currentEne - charStats->baseENE >= nb ? nb : currentEne - charStats->baseENE;
	if (currentEne - removePtsNb < 1) removePtsNb = currentEne - 1;
	removeManNb = removePtsNb * (charStats->manaPerMagic << 6);

	D2Common::D2AddUnitStat(ptChar, STATS_ENERGY, -removePtsNb, 0);
	D2Common::D2AddUnitStat(ptChar, STATS_MAXMANA, -removeManNb, 0);
	D2Common::D2AddUnitStat(ptChar, STATS_STATPTS, removePtsNb, 0);
}

static BOOL __fastcall m_RespecNormal_pSpellFuction(GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem1, UnitAny* pItem2, DWORD it, DWORD flag1, DWORD flag2)
{
	if (pPlayer)
	{
		NormalResetSkills(pPlayer);
		UnassignStr(pPlayer, 65535);
		UnassignDex(pPlayer, 65535);
		UnassignVit(pPlayer, 65535);
		UnassignEne(pPlayer, 65535);
		return TRUE;
	}
	return FALSE;
}

__declspec(naked) void m_RespecNormal_changeSkillPerLevelUp()
{
	__asm
	{
		MOV EAX, m_RespecNormal_SkillPerLevelUp
		IMUL EAX, EBX
		MOV DWORD PTR SS : [ESP + 0xC] , EAX
		JMP D2Common::D2AddUnitStat
	}
}

#endif
#endif 
