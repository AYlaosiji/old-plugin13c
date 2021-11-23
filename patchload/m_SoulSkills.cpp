#include "pch.h"
#ifdef MODULES_SOULSKILLS

#define STR_NOT_ENOUGH_SOUL "没有足够的灵魂，需要剩余："
#define STR_SOUL L"灵魂："
#define STR_SOUL_COUNTER L"当前物品储存灵魂："
#define STR_MAXSOUL_COUNTER L"所有物品储存灵魂："

BOOL m_SoulSkills_IsOn = FALSE;
DWORD m_SoulSkills_SoulSrvDoFunc = 0;

DWORD m_SoulSkills_SoulStat = 0;
DWORD m_SoulSkills_SoulMaxStat = 0;

DWORD m_SoulSkills_AddSoulPspell = 0;


void m_SoulSkills_D2SkillSrvDoFuncJMP();


BOOL __fastcall m_SoulSkills_PspellAddSoul(GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem1, UnitAny* pItem2, DWORD it, DWORD flag1, DWORD flag2);

void m_SoulSkills_LoadCfg()
{
	m_SoulSkills_IsOn = cfgload::GetModuleCfgBool("Soul Skills", "IsOn");
	m_SoulSkills_SoulSrvDoFunc= cfgload::GetModuleCfgInt("Soul Skills", "Soul SrvDoFunc");
	
	m_SoulSkills_SoulStat= cfgload::GetModuleCfgInt("Soul Skills", "Soul Stat");
	m_SoulSkills_SoulMaxStat= cfgload::GetModuleCfgInt("Soul Skills", "Soul Max Stat");
	
	m_SoulSkills_AddSoulPspell= cfgload::GetModuleCfgInt("Soul Skills", "Add Soul Pspell");
}

void m_SoulSkills_Install()
{
	if (m_SoulSkills_IsOn == FALSE)return;
	
#ifdef D2SERVER
	if (m_SoulSkills_SoulStat == NULL || m_SoulSkills_SoulMaxStat == NULL)return;

	DWORD offset = 0;

	if (m_SoulSkills_SoulSrvDoFunc)
	{
		offset = D2Game::GetAddress(0x1074A8 + m_SoulSkills_SoulSrvDoFunc * 4);
		Memory::SetCursor(offset);
		Memory::ChangeDword(0, (DWORD)m_SoulSkills_D2SkillSrvDoFuncJMP);
	}

	if (m_SoulSkills_AddSoulPspell)
	{
		offset = D2Game::GetAddress(0x10723C + 8 * m_SoulSkills_AddSoulPspell);
		Memory::SetCursor(offset);
		Memory::ChangeDword(0x00000000, (DWORD)m_SoulSkills_PspellAddSoul);
	}

#endif
}

void m_SoulSkills_UnInstall()
{

}

#ifdef D2SERVER

DWORD GetPlayerTotalSouls(UnitAny* pUnit, DWORD StatID, int Param)
{
	DWORD Total = 0;
	for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(pUnit->ptInventory); pItem = D2Common::D2GetNextInventoryItem(pItem); pItem)
	{
		if (pItem == NULL || pItem->ptItemData == NULL || pItem->ptItemData->page != NULL)continue;
		if (D2Common::D2CheckItemRequirements(pItem, pUnit, FALSE, NULL, NULL, NULL) == FALSE)continue;
		DWORD Souls = D2Common::GetItemStatFromFlag0x40(pItem, StatID, Param);
		if (Souls && Souls != (WORD)-1)
		{
			Total += Souls;
		}
	}
	return Total;
}

BOOL AddSoulToItem(NetClient* pClient, UnitAny* pPlayer, UnitAny* pItem, DWORD m_SoulSkills_SoulStat, DWORD m_SoulSkills_SoulMaxStat, DWORD AddSoul)
{
	if (D2Common::D2CheckItemRequirements(pItem, pPlayer, FALSE, NULL, NULL, NULL) == FALSE)return FALSE;

	DWORD Count = D2Common::GetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulStat, 0);
	if (Count)
	{
		DWORD MaxSoulCountItem = D2Common::GetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulMaxStat, 0);
		if (MaxSoulCountItem == (WORD)-1 || MaxSoulCountItem == 0)return FALSE;
		if (Count == (WORD)-1 && AddSoul <= MaxSoulCountItem)
		{
			D2Common::SetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulStat, AddSoul, 0, pClient);
			return TRUE;
		}
		else if (Count + AddSoul <= MaxSoulCountItem)
		{
			D2Common::SetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulStat, Count + AddSoul, 0, pClient);
			return TRUE;
		}
	}
	return FALSE;
}


DWORD __fastcall m_SoulSkills_D2SkillSrvDoFunc_t(GameStruct* pGame, UnitAny* pUnit, int nSkill, int nSkillLevel)
{
	SkillsBIN* pSkillbin = D2Common::D2GetSkillsTxt(nSkill);
	if (pSkillbin)
	{
		//消耗的灵魂数用cost mult存，本身的SrvDoFun用cost add存
		DWORD CostSoul = pSkillbin->dwCostMult;
		if (CostSoul)
		{
			DWORD NowSoulCount = GetPlayerTotalSouls(pUnit, m_SoulSkills_SoulStat, 0);
			//一共人物有多少灵魂（真实数据）
			if (NowSoulCount)
			{
				if (CostSoul <= NowSoulCount)//可以释放
				{
					for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(pUnit->ptInventory); pItem = D2Common::D2GetNextInventoryItem(pItem); pItem)
					{
						if (pItem == NULL || pItem->ptItemData == NULL || pItem->ptItemData->page != NULL)continue;
						if (CostSoul == 0)break;
						DWORD Souls = D2Common::GetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulStat, 0);
						if (Souls&& Souls != (WORD)-1)
						{
							if (CostSoul < Souls)
							{
								D2Common::SetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulStat, Souls - CostSoul, 0, pUnit->ptPlayerData->ptNetClient);
								CostSoul = 0;
							}
							else
							{
								D2Common::SetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulStat, (WORD)-1, 0, pUnit->ptPlayerData->ptNetClient);
								CostSoul -= Souls;
							}
						}
					}
					return D2Game::GetAddress(0x1074A8 + pSkillbin->dwCostAdd * 4);
				}
			}
			CHAR szchar[50] = "";
			sprintf(szchar, "%s%d", STR_NOT_ENOUGH_SOUL, CostSoul - NowSoulCount);
			D2String::SendClientMessage(pUnit->ptPlayerData->ptNetClient, CHAT_PLAYERMESSAGE, "Info", szchar);
		}
		else
		{
			//不需要消耗灵魂就直接释放
			return D2Game::GetAddress(0x1074A8 + pSkillbin->dwCostMult * 4);
		}
	}
	return 0;
}

void __declspec(naked) m_SoulSkills_D2SkillSrvDoFuncJMP()
{
	__asm
	{
		push ecx
		push edx
		push DWORD PTR SS : [esp + 0x10]
		push DWORD PTR SS : [esp + 0x10]
		call m_SoulSkills_D2SkillSrvDoFunc_t
		pop edx
		pop ecx
		test eax, eax
		jz mark1
		jmp DWORD PTR SS : [eax]
		mark1 :
		retn 8
	}
}

BOOL __fastcall m_SoulSkills_PspellAddSoul(GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem1, UnitAny* pItem2, DWORD it, DWORD flag1, DWORD flag2)
{
	ItemBIN* pItemtxt = D2Common::D2GetItemTxt(pItem1->dwTxtFileNo);
	if (pItemtxt && pItemtxt->GambleCost)
	{
		DWORD NeedAddSoul = pItemtxt->GambleCost;
		for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(pPlayer->ptInventory); pItem = D2Common::D2GetNextInventoryItem(pItem); pItem)
		{
			if (NeedAddSoul == NULL)break;
			if (pItem == NULL || pItem->ptItemData == NULL || pItem->ptItemData->page != NULL)continue;
			DWORD MaxSoulCanStored= D2Common::GetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulMaxStat, 0);
			DWORD NowSoul= D2Common::GetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulStat, 0);
			if ( NowSoul==(WORD)-1)
			{
				if (NeedAddSoul < MaxSoulCanStored)//没了
				{
					AddSoulToItem(pPlayer->ptPlayerData->ptNetClient, pPlayer, pItem, m_SoulSkills_SoulStat, m_SoulSkills_SoulMaxStat, NeedAddSoul);
					return TRUE;
				}
				else
				{
					AddSoulToItem(pPlayer->ptPlayerData->ptNetClient, pPlayer, pItem, m_SoulSkills_SoulStat, m_SoulSkills_SoulMaxStat, MaxSoulCanStored);
					NeedAddSoul -= MaxSoulCanStored;
				}
			}
			else if(NowSoul < MaxSoulCanStored)
			{
				if (NeedAddSoul < MaxSoulCanStored- NowSoul)//没了
				{
					AddSoulToItem(pPlayer->ptPlayerData->ptNetClient, pPlayer, pItem, m_SoulSkills_SoulStat, m_SoulSkills_SoulMaxStat, NeedAddSoul);
					return TRUE;
				}
				else
				{
					AddSoulToItem(pPlayer->ptPlayerData->ptNetClient, pPlayer, pItem, m_SoulSkills_SoulStat, m_SoulSkills_SoulMaxStat, MaxSoulCanStored - NowSoul);
					NeedAddSoul -= (MaxSoulCanStored - NowSoul);
				}
			}
		}
	}
	return TRUE;
}
#endif

void m_SoulSkills_Draw()
{
	UnitAny* pPlayer = *D2Client::ptPlayerClient;
	if (pPlayer == NULL)return;
	DWORD MaxSoul = GetPlayerTotalSouls(pPlayer, m_SoulSkills_SoulMaxStat, 0);
	if (MaxSoul == 0)return;
	DWORD NewSoul = GetPlayerTotalSouls(pPlayer, m_SoulSkills_SoulStat, 0);

	int startx = (*D2Client::ptScreenSize).x / 2 - 146;
	int starty = (*D2Client::ptScreenSize).y - 33;
	int lengthMaXx = 122;
	int nowLength = NewSoul * lengthMaXx / MaxSoul;
	int lengthy = 4;
	int mousex = *D2Client::ptMouseX;
	int mousey = *D2Client::ptMouseY;
	//D2FillRect(startx, starty, nowLength, lengthy, 0x20, 5);
	D2Gfx::D2FillArea(startx, starty, startx+nowLength, starty+lengthy, 0x20, 5);
	if (mousex >= startx && mousey >= starty && mousex <= startx + lengthMaXx && mousey <= starty + lengthy)
	{
		WCHAR text1[0x50];
		_snwprintf(text1, sizeof(text1), L"%s %u / %u"
			, STR_SOUL, NewSoul, MaxSoul
		);
		D2Win::D2PrintPopup(text1, startx + 30, starty - 16, D2Color::WHITE, TRUE);
	}
}

BOOL m_SoulSkills_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue)
{
	if (m_SoulSkills_SoulStat && statID == m_SoulSkills_SoulStat && m_SoulSkills_SoulMaxStat)
	{
		DWORD TotalSoul = GetPlayerTotalSouls(*D2Client::ptPlayerClient, m_SoulSkills_SoulStat, 0);
		DWORD TotalMaxSoul = GetPlayerTotalSouls(*D2Client::ptPlayerClient, m_SoulSkills_SoulMaxStat, 0);
		DWORD ItemSoul = D2Common::GetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulStat, 0);
		DWORD ItemMaxSoul = D2Common::GetItemStatFromFlag0x40(pItem, m_SoulSkills_SoulMaxStat, 0);
		if (ItemSoul == (WORD)-1)ItemSoul = 0;//修正
		if (ItemMaxSoul == (WORD)-1)ItemMaxSoul = 0;
		swprintf(wszchar, L"( %s %d / %d )\n%s %d / %d", STR_MAXSOUL_COUNTER, TotalSoul, TotalMaxSoul
			, STR_SOUL_COUNTER, ItemSoul, ItemMaxSoul);
		return TRUE;
	}
	return FALSE;
}

BOOL m_SoulSkills_CheckTypeUpdate(DWORD type)
{

}

void ClearPlayerSouls(UnitAny* pUnit, DWORD StatID, int Param)
{
	for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(pUnit->ptInventory); pItem = D2Common::D2GetNextInventoryItem(pItem); pItem)
	{
		if (pItem == NULL || pItem->ptItemData == NULL || pItem->ptItemData->page != NULL)continue;
		if (D2Common::D2CheckItemRequirements(pItem, pUnit, FALSE, NULL, NULL, NULL) == FALSE)continue;
		DWORD Souls = D2Common::GetItemStatFromFlag0x40(pItem, StatID, Param);
		if (Souls && Souls != (WORD)-1)
		{
			D2Common::SetItemStatFromFlag0x40(pItem, StatID, (WORD)-1, Param, pUnit->ptPlayerData->ptNetClient);
		}
	}
}


void m_SoulSkills_ClearSoulsLastHit(GameStruct* pDmg, UnitAny* Killed, void* unk, int nDamage, UnitAny* Killer, DamageData* pdmg)
{
	if (Killed && Killed->nUnitType == UNIT_PLAYER)
	{
		if (m_SoulSkills_SoulStat)
			ClearPlayerSouls(Killed, m_SoulSkills_SoulStat, 0);
	}
}

void m_SoulSkills_AddPlayerSoul(NetClient* pClient, UnitAny* pPlayer, DWORD unkexp)
{
	if (m_SoulSkills_SoulStat && m_SoulSkills_SoulMaxStat)
	{
		PlayerData* pPlayerdata = pPlayer->ptPlayerData;

		BOOL ret = FALSE;
		if (pPlayer->ptGame->difficultyLevel == 2)//地狱
		{
			ret = TRUE;
		}

		if (pPlayer->ptGame->difficultyLevel == 1)//噩梦
		{
			if (pPlayerdata && pPlayerdata->ptQuest[2]->pBuffer && *pPlayerdata->ptQuest[2]->pBuffer == NULL)
				ret = TRUE;
		}

		if (pPlayer->ptGame->difficultyLevel == 0)//普通
		{
			if (pPlayerdata && pPlayerdata->ptQuest[1]->pBuffer && *pPlayerdata->ptQuest[1]->pBuffer == NULL)
				ret = TRUE;
		}

		if (ret)
		{
			for (UnitAny* pItem = D2Common::D2GetFirstInventoryItem(pPlayer->ptInventory); pItem = D2Common::D2GetNextInventoryItem(pItem); pItem)
			{
				if (pItem == NULL || pItem->ptItemData == NULL || pItem->ptItemData->page != NULL)continue;
				if (AddSoulToItem(pPlayer->ptPlayerData->ptNetClient, pPlayer, pItem, m_SoulSkills_SoulStat, m_SoulSkills_SoulMaxStat, 1))
					break;
			}
		}
	}
}
#endif
