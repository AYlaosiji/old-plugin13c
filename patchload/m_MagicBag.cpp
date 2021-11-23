#include"pch.h"
#ifdef MODULES_MAGICBAG
#define STR_NOTHING L"空行"
#define STR_UNKNOWN L"错误"
//除了该文件，还需要在m_StatItemExtended中更新物品，m_NewStatDesc中显示物品 联动两个
static BOOL m_MagicBag_IsOn=FALSE;
static DWORD m_MagicBag_BagItemType;
static DWORD m_MagicBag_StartStat;
static DWORD m_MagicBag_totalcount;
static DWORD m_MagicBag_pSpell;
static BOOL m_MagicBag_bSuperMode;

static DWORD m_MagicBag_BACK_InteractInOffSet;
static DWORD m_MagicBag_BACK_InteractSwapOffSet;


void m_MagicBag_InteractItem_ASM();
static BOOL __fastcall m_MagicBag_TakeItem(GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem1, UnitAny* pItem2, DWORD it, DWORD flag1, DWORD flag2);

void m_MagicBag_LoadCfg()
{
    m_MagicBag_IsOn = cfgload::GetModuleCfgBool("Magic Bag", "IsOn");
    m_MagicBag_BagItemType = cfgload::GetModuleCfgInt("Magic Bag", "Bag Item Type Line");
    m_MagicBag_StartStat = cfgload::GetModuleCfgInt("Magic Bag", "Start Stat");
    m_MagicBag_totalcount = cfgload::GetModuleCfgInt("Magic Bag", "Stat Total Count");
    m_MagicBag_pSpell = cfgload::GetModuleCfgInt("Magic Bag", "pSpell");
    m_MagicBag_bSuperMode = cfgload::GetModuleCfgBool("Magic Bag", "Super Mode");
}

void m_MagicBag_Install()
{
	if (m_MagicBag_IsOn == FALSE)return;
#ifdef D2SERVER

	DWORD offset;
	//Swap Sth
	m_MagicBag_BACK_InteractInOffSet = D2Game::GetAddress(0xD73C6);
	m_MagicBag_BACK_InteractSwapOffSet = D2Game::GetAddress(0xD768D);

	offset = D2Game::GetAddress(0xD73C1);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x0F, 0xE9);
	Memory::ChangeCallA(0x0002C685, (DWORD)m_MagicBag_InteractItem_ASM);
	Memory::ChangeByte(0x00, 0x90);

	//取物品
	offset = D2Game::GetAddress(0x10723C + 8 * m_MagicBag_pSpell);
	Memory::SetCursor(offset);
	Memory::ChangeDword(0x00000000, (DWORD)m_MagicBag_TakeItem);

#endif // D2SERVER
}

void m_MagicBag_UnInstall()
{

}

#ifdef D2SERVER
static BOOL _fastcall m_MagicBag_MyInsertItem(UnitAny* pItem1, UnitAny* pItem2, UnitAny* pPlayer)//第一个是esi,第二个是edi
{
	if (D2Common::D2GetItemType(pItem1->dwTxtFileNo) != m_MagicBag_BagItemType)
		return TRUE;//如果txtnum不对，直接return

	if (D2Common::D2GetItemQuality(pItem2) != ITEMQUALITY_NORMAL)
		return TRUE;

	ItemBIN* pItemtxt = D2Common::D2GetItemTxt(pItem2->dwTxtFileNo);
	if (!pItemtxt)
		return TRUE;

	//选择BaseItemCode与数量
	DWORD dwBaseItemCode = pItemtxt->ItemCode;

	StatsList* ppp = D2Common::D2GetStatsFromListflag(pItem1, 0x40);//这时候ebx=ppp以后可能会用
	StatEx* pStatEx = ppp->ptBaseStatsTable;
	for (size_t i = 0; i < ppp->nbBaseStats; i++)
	{
		//枚举如果有匹配的属性
		//如果属性不在定义的区间里，就继续枚举
		if (
			ppp->ptBaseStatsTable[i].id > m_MagicBag_StartStat + m_MagicBag_totalcount//360+8(361-368)
			|| ppp->ptBaseStatsTable[i].id < m_MagicBag_StartStat + 1
			)
			continue;

		StatEx temp = pStatEx[i];
		DWORD ItemTN = temp.value & 0x0000FFFF;
		DWORD amount = (temp.value & 0xFFFF0000) >> 16;
		DWORD ItemCode = D2Common::D2GetItemTxt(ItemTN)? D2Common::D2GetItemTxt(ItemTN)->ItemCode:0;
		if (ItemTN == 0xFFFF)//表示这个位置为空
			continue;

		else if (ItemCode == dwBaseItemCode)
		{
			if (amount < 0xFFFF )
			{
				pStatEx[i].value += 0x10000;
				D2Game::D2DeleteItem(pPlayer->ptGame, pPlayer, pItem2);
				D2Game::D2UpdateClientItemStat(pPlayer->ptPlayerData->ptNetClient, pItem1, 1, pStatEx[i].id, pStatEx[i].value);
				return FALSE;
			}
			else return TRUE;
		}
	}
	for (size_t i = 0; i < ppp->nbBaseStats; i++)
	{
		//枚举没有匹配的属性
		//如果属性不在定义的区间里，就继续枚举
		if (
			ppp->ptBaseStatsTable[i].id > m_MagicBag_StartStat + m_MagicBag_totalcount//360+8(361-368)
			|| ppp->ptBaseStatsTable[i].id < m_MagicBag_StartStat + 1
			)
			continue;
		//找一个可存的位置
		StatEx temp = pStatEx[i];
		DWORD ItemTN = temp.value & 0x0000FFFF;
		DWORD NewTN = D2Common::D2GetItemIndexFromCode(dwBaseItemCode);
		if (ItemTN == 0xFFFF && NewTN != 0xFFFF)
		{
			pStatEx[i].value = pStatEx[i].value - 0xFFFF + NewTN + 0x10000;//改写并存入
			D2Game::D2DeleteItem(pPlayer->ptGame, pPlayer, pItem2);
			D2Game::D2UpdateClientItemStat(pPlayer->ptPlayerData->ptNetClient, pItem1, 1, pStatEx[i].id, pStatEx[i].value);
			return FALSE;
		}
	}
	return TRUE;
}

void __declspec(naked) m_MagicBag_InteractItem_ASM()
{
	__asm
	{
		push esi
		mov ecx, ebp
		mov edx, ebx
		call m_MagicBag_MyInsertItem
		test eax, eax
		je markA
		jmp m_MagicBag_BACK_InteractInOffSet//能点进去 不备份
		markA :
		push esi//不能交互
			call D2Common::D2GetItemPage
			jmp m_MagicBag_BACK_InteractSwapOffSet//做交换 备份 
	}
}

static WORD m_MagicBag_GetBagTNfromStat(UnitAny* pBag, DWORD itstat)
{
	StatsList* pItem1StatsList = D2Common::D2GetStatsFromListflag(pBag, 0x40);
	for (size_t i = 0; i < pItem1StatsList->nbBaseStats; i++)
	{
		if (pItem1StatsList->ptBaseStatsTable[i].id == itstat)
		{
			return (WORD)(pItem1StatsList->ptBaseStatsTable[i].value & 0x0000FFFF);
		}
	}
	return 0;
}

static WORD m_MagicBag_GetBagAmountfromStat(UnitAny* pBag, DWORD itstat)
{
	StatsList* pItem1StatsList = D2Common::D2GetStatsFromListflag(pBag, 0x40);
	for (size_t i = 0; i < pItem1StatsList->nbBaseStats; i++)
	{
		if (pItem1StatsList->ptBaseStatsTable[i].id == itstat)
		{
			return (WORD)((pItem1StatsList->ptBaseStatsTable[i].value & 0xFFFF0000) >> 16);
		}
	}
	return 0;
}

static DWORD m_MagicBag_BagDecrease(UnitAny* pBag, DWORD itstat, DWORD doit)
{
	if (doit == 0)return NULL;
	StatsList* pItem1StatsList = D2Common::D2GetStatsFromListflag(pBag, 0x40);
	for (size_t i = 0; i < pItem1StatsList->nbBaseStats; i++)
	{
		if (pItem1StatsList->ptBaseStatsTable[i].id == itstat)
		{
			DWORD TN = pItem1StatsList->ptBaseStatsTable[i].value & 0x0000FFFF;
			DWORD AMOUNT = (pItem1StatsList->ptBaseStatsTable[i].value & 0xFFFF0000) >> 16;
			if (TN == 0xFFFF || AMOUNT == 0)return NULL;//没东西
			else if (AMOUNT > doit)//直接拿
			{
				pItem1StatsList->ptBaseStatsTable[i].value -= 0x10000 * doit;
				if (m_MagicBag_bSuperMode)
				{
					pItem1StatsList->ptBaseStatsTable[i].value = pItem1StatsList->ptBaseStatsTable[i].value | 0xFFF00000;
				}
				return pItem1StatsList->ptBaseStatsTable[i].value;
			}
			else if (AMOUNT == doit)
			{
				pItem1StatsList->ptBaseStatsTable[i].value = 0x0000FFFF;
				if (m_MagicBag_bSuperMode)
				{
					pItem1StatsList->ptBaseStatsTable[i].value = pItem1StatsList->ptBaseStatsTable[i].value | 0xFFF00000;
				}
				return pItem1StatsList->ptBaseStatsTable[i].value;
			}
		}
	}
	return NULL;
}

static BOOL __fastcall m_MagicBag_TakeItem(GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem1, UnitAny* pItem2, DWORD it, DWORD flag1, DWORD flag2)
{

	if (pItem1->nUnitType != UNIT_ITEM|| !pItem1->pItemPath)return FALSE;
	if (!pPlayer || !pPlayer->ptPlayerData)return FALSE;

	DWORD xp = pItem1->pItemPath->dwPosX;
	DWORD yp = pItem1->pItemPath->dwPosY;
	DWORD itstat = yp * 2 + xp%2 + m_MagicBag_StartStat + 1;

	if (
		itstat > m_MagicBag_StartStat + m_MagicBag_totalcount//360+8(361-368)
		|| itstat< m_MagicBag_StartStat+1
		)
		return FALSE;//比如361-368 那么大于368就不行

	WORD itTN = m_MagicBag_GetBagTNfromStat(pItem1, itstat);
	WORD itAMOUNT = m_MagicBag_GetBagAmountfromStat(pItem1, itstat);

	if (itTN == 0xFFFF || itAMOUNT == 0)return FALSE;//没有东西

	DWORD ItemCode = D2Common::D2GetItemTxt(itTN) ? D2Common::D2GetItemTxt(itTN)->ItemCode : 0;

	if (ItemCode)
	{
		if (itAMOUNT > 0)
		{
			D2Game::D2SpawnItem(pGame, pPlayer, ItemCode, 1, ITEMQUALITY_NORMAL, TRUE);
			
			DWORD value = m_MagicBag_BagDecrease(pItem1, itstat, 1);
			D2Game::D2UpdateClientItemStat(pPlayer->ptPlayerData->ptNetClient, pItem1, 1, itstat, value);
		}
	}
	return FALSE;
}

#endif

BOOL m_MagicBag_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue)
{
	if (m_MagicBag_StartStat && m_MagicBag_totalcount
		&& statID < m_MagicBag_StartStat + m_MagicBag_totalcount + 1//360+8(361-368)
		&& statID > m_MagicBag_StartStat)
	{
		DWORD TN = statvalue & 0x0000FFFF;
		DWORD Amount = statvalue & 0xFFFF0000;
		wchar_t* Name;
		if (TN == 0xFFFF)
		{
			//没有储存
			Name = STR_NOTHING;
		}
		else
		{
			ItemBIN* ptxt = D2Common::D2GetItemTxt(TN);
			if (ptxt)
			{
				Name = D2Lang::D2GetStringFromIndex(ptxt->NameStr);
			}
			else
			{
				Name = STR_UNKNOWN;
			}
		}
		//D2Win::D2SetFontSize
		if (TN == 0xFFFF)swprintf(wszchar, L"$$;%d:  $$$%s  $$3%d", statID - m_MagicBag_StartStat, Name, Amount >> 16);
		else swprintf(wszchar, L"$$;%d:  $$$%s  $$3%d", statID - m_MagicBag_StartStat, Name, Amount >> 16);
		D2String::ReplaceColorSpecs(wszchar);
		return TRUE;
	}
	return FALSE;
}

#endif // MODULES_MAGICBAG
