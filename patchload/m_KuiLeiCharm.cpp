#include "pch.h"
#ifdef MODULES_KUILEICHARM

BOOL m_KuiLeiCharm_IsOn = FALSE;
DWORD m_KuiLeiCharm_ItemKuiLeiStat = 0;

void m_KuiLeiCharm_LoadCfg()
{
	m_KuiLeiCharm_IsOn=cfgload::GetModuleCfgBool("Kui Lei Charm", "IsOn");
	m_KuiLeiCharm_ItemKuiLeiStat = cfgload::GetModuleCfgInt("Kui Lei Charm", "Item Kui Lei Stat");
}

void m_KuiLeiCharm_Install()
{

}

void m_KuiLeiCharm_UnInstall()
{

}
#ifdef D2SERVER
void DecreaseItemKuiLeiDeath(GameStruct* pDmg, UnitAny* pPlayer, DWORD StatID, int Param)
{
	for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(pPlayer->ptInventory); pItem = D2Common::D2GetNextInventoryItem(pItem); pItem)
	{
		if (D2Common::D2GetItemPage(pItem) != 0)continue;
		if (D2Common::D2CheckItemRequirements(pItem, pPlayer, FALSE, NULL, NULL, NULL) == FALSE)continue;
		DWORD Count = D2Common::GetItemStatFromFlag0x40(pItem, StatID, Param);
		if (Count == 1)
		{
			D2Game::D2DeleteItem(pDmg, pPlayer, pItem);
		}
		else if (Count > 1)
		{
			D2Common::SetItemStatFromFlag0x40(pItem, StatID, Count - 1, Param, pPlayer->ptPlayerData->ptNetClient);
		}
	}
}

void m_KuiLeiCharm_DoKuiLeiCharmLastHit(GameStruct* pDmg, UnitAny* Killed, void* unk, int nDamage, UnitAny* Killer, DamageData* pdmg)
{
	if (m_KuiLeiCharm_IsOn)
	{
		if (Killed && Killed->nUnitType == UNIT_PLAYER)
			DecreaseItemKuiLeiDeath(pDmg, Killed, m_KuiLeiCharm_ItemKuiLeiStat, 0);
	}
}

#endif

#endif