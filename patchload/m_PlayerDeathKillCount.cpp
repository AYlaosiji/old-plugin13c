#include"pch.h"
#ifdef MODULES_PLAYERDEATHKILLCOUNT

#define STR_KILL_COUNTER L"您击杀的怪物个数为："
#define STR_DEATH_COUNTER L"您被怪物击杀的次数为："

BOOL m_PlayerDeathKillCount_DeathStatIsOn = FALSE;
DWORD m_PlayerDeathKillCount_DeathStat = 0;
BOOL m_PlayerDeathKillCount_KillStatIsOn = FALSE;
DWORD m_PlayerDeathKillCount_KillStat = 0;

void m_PlayerDeathKillCount_LoadCfg()
{
	m_PlayerDeathKillCount_DeathStatIsOn= cfgload::GetModuleCfgBool("Player Death Kill Count", "Death Stat IsOn");
	m_PlayerDeathKillCount_DeathStat = cfgload::GetModuleCfgInt("Player Death Kill Count", "Death Stat");
	m_PlayerDeathKillCount_KillStatIsOn = cfgload::GetModuleCfgBool("Player Death Kill Count", "Kills Stat IsOn");
	m_PlayerDeathKillCount_KillStat = cfgload::GetModuleCfgInt("Player Death Kill Count", "Kills Stat");
}

void m_PlayerDeathKillCount_Install()
{

}

void m_PlayerDeathKillCount_UnInstall()
{

}
#ifdef D2SERVER
void m_PlayerDeathKillCount_AddPlayerDeathLastHit(GameStruct* pDmg, UnitAny* Killed, void* unk, int nDamage, UnitAny* Killer, DamageData* pdmg)
{
	if (m_PlayerDeathKillCount_DeathStatIsOn)
	{
		if (Killed && Killed->nUnitType == UNIT_PLAYER)
		{
			for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(Killed->ptInventory); pItem = D2Common::D2GetNextInventoryItem(pItem); pItem)
			{
				DWORD Count = D2Common::GetItemStatFromFlag0x40(pItem, m_PlayerDeathKillCount_DeathStat, 0);
				if (Count && Count != (DWORD)-1)
				{
					D2Common::SetItemStatFromFlag0x40(pItem, m_PlayerDeathKillCount_DeathStat, Count + 1, 0, Killed->ptPlayerData->ptNetClient);
					break;
				}
			}
		}
	}
}

void m_PlayerDeathKillCount_AddPlayerKill(NetClient* pClient, UnitAny* pPlayer, DWORD unkexp)
{
	if (m_PlayerDeathKillCount_KillStatIsOn)
	{
		for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(pPlayer->ptInventory); pItem = D2Common::D2GetNextInventoryItem(pItem); pItem)
		{
			if (pItem == NULL || pItem->ptItemData == NULL || pItem->ptItemData->page != NULL)continue;
			DWORD Count = D2Common::GetItemStatFromFlag0x40(pItem, m_PlayerDeathKillCount_KillStat, 0);
			if (Count && Count != (DWORD)-1)
			{
				D2Common::SetItemStatFromFlag0x40(pItem, m_PlayerDeathKillCount_KillStat, Count + 1, 0, pPlayer->ptPlayerData->ptNetClient);
				break;
			}
		}
	}
}

#endif

BOOL m_PlayerDeathKillCount_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue)
{
	if (m_PlayerDeathKillCount_KillStatIsOn && statID == m_PlayerDeathKillCount_KillStat)
	{
		swprintf(wszchar, L"%s%d", STR_KILL_COUNTER, statvalue - 1);
		return TRUE;
	}
	else if (m_PlayerDeathKillCount_DeathStatIsOn && statID == m_PlayerDeathKillCount_DeathStat)
	{
		swprintf(wszchar, L"%s%d", STR_DEATH_COUNTER, statvalue - 1);
		return TRUE;
	}
	return FALSE;
}


#endif