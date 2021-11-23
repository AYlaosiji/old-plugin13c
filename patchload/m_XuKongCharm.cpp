#include"pch.h"
#ifdef MODULES_XUKONGCHARM
#define STR_LEFTTIME L"$$8有效剩余时间"
#define STR_LEFTMONTH L"月"
#define STR_LEFTDAY L"天"
#define STR_LEFTHOUR L"时"
#define STR_LEFTMIN L"分"
#define STR_LEFTSEC L"秒"
BOOL m_XuKongCharm_IsOn = FALSE;
static DWORD m_XuKongCharm_ItemTimeLimitStat;

void m_XuKongCharm_LoadCfg()
{
	m_XuKongCharm_IsOn = cfgload::GetModuleCfgBool("Xu Kong Charm", "IsOn");
	m_XuKongCharm_ItemTimeLimitStat = cfgload::GetModuleCfgInt("Xu Kong Charm", "Item Time Limit Stat");
}

void m_XuKongCharm_Install()
{

}

void m_XuKongCharm_UnInstall()
{

}

void m_XuKongCharm_XuKongLoop(GameStruct* pGame, UnitAny* pUnit, DWORD Frame, DWORD Type)
{
	if (m_XuKongCharm_IsOn && pUnit && pUnit->ptInventory && pUnit->ptPlayerData && Frame % 25 == 0)
	{
		for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(pUnit->ptInventory); pItem; pItem = D2Common::D2GetNextInventoryItem(pItem))
		{
			if (D2Common::D2GetItemPage(pItem) != 0)continue;
			if (D2Common::D2CheckItemRequirements(pItem, pUnit, FALSE, NULL, NULL, NULL) == FALSE)continue;
			DWORD value = D2Common::GetItemStatFromFlag0x40(pItem, m_XuKongCharm_ItemTimeLimitStat, 0);
			if (value > 1)
			{
				//D2Common::D2AddUnitStat(pItem, m_XuKongCharm_ItemTimeLimitStat, -1, 0);
				D2Common::SetItemStatFromFlag0x40(pItem, m_XuKongCharm_ItemTimeLimitStat, value - 1, 0, pUnit->ptPlayerData->ptNetClient);
				//if (value % 32 == 0)//除以32木有余数 就去更新客户端
				D2Game::D2UpdateClientItemStat(pUnit->ptPlayerData->ptNetClient, pItem, TRUE, m_XuKongCharm_ItemTimeLimitStat, value - 1);
			}
			else if (value == 1)
			{
				D2Game::D2DeleteItem(pGame, pUnit, pItem);
			}
		}
	}
}

BOOL m_XuKongCharm_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue)
{
	if (m_XuKongCharm_IsOn && statID == m_XuKongCharm_ItemTimeLimitStat)
	{
		DWORD timeleft0 = D2Common::GetItemStatFromFlag0x40(pItem, statID, 0);
		DWORD timeleft = timeleft0;
		DWORD sec = timeleft % 60;
		DWORD min = (timeleft / 60) % 60;
		DWORD hour = (timeleft / 60 / 60) % 24;
		DWORD day = timeleft / 60 / 60 / 24;
		if (day)
		{
			swprintf(wszchar, L"%s : $$9%02d%s%02d%s%02d%s%02d%s",
				STR_LEFTTIME,
				day, STR_LEFTDAY,
				hour, STR_LEFTHOUR,
				min, STR_LEFTMIN,
				sec, STR_LEFTSEC);
		}
		else
		{
			swprintf(wszchar, L"%s : $$9%02d%s%02d%s%02d%s",
				STR_LEFTTIME,
				hour, STR_LEFTHOUR,
				min, STR_LEFTMIN,
				sec, STR_LEFTSEC);
		}
		D2String::ReplaceColorSpecs(wszchar);
		return TRUE;
	}
	return FALSE;
}

#endif