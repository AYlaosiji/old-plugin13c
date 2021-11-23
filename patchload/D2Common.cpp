#include"pch.h"

void __declspec(naked) D2CommonASM_D2GetCharStatsBIN()
{
	__asm
	{
		MOV EAX, ECX
		JMP D2Common::VD2GetCharStatsBIN
	}
}

void __declspec(naked) D2CommonASM_D2GetItemStatCostBIN()
{
	__asm
	{
		MOV EAX, ECX
		JMP D2Common::VD2GetItemStatCostBIN
	}
}

void __declspec(naked) D2CommonASM_D2GetLevelTxt()
{
	__asm {
		mov eax, ecx
		mov ecx, [D2Common::SgptDataTables]
		mov ecx, [ecx]
		cmp eax, dword ptr[ecx + 0xC5C]
		jge unkret
		mov edx, dword ptr[ecx + 0xC58]
		imul eax, 0x220
		add eax, edx
		ret
		unkret :
		xor eax, eax
			ret
	}
}

void __declspec(naked) D2CommonASM_D2GetSkillsTxt(DWORD dwIdx)
{
	__asm {
		mov eax, ecx
		mov ecx, [D2Common::SgptDataTables]
		mov ecx, [ecx]
		cmp eax, dword ptr[ecx + 0xBA0]
		jge unkret
		mov edx, dword ptr[ecx + 0xB98]
		imul eax, 0x23C
		add eax, edx
		ret
		unkret :
		xor eax, eax
			ret
	}
}

void __declspec(naked) D2CommonASM_D2GetItemTypeBin(DWORD dwIdx)
{
	__asm {
		mov eax, ecx
		mov ecx, [D2Common::SgptDataTables]
		mov ecx, [ecx]
		cmp eax, dword ptr[ecx + 0xBFC]
		jge unkret
		mov edx, dword ptr[ecx + 0xBF8]
		imul eax, 0xE4
		add eax, edx
		ret
		unkret :
		xor eax, eax
			ret
	}
}

void D2Common::Init()
{
	Name = "D2Common.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Common::SetFunctions()
{
	D2SetItemPage=(TD2SetItemPage)D2Common::GetAddressByOrdinal(10012);
	D2GetItemPage = (TD2GetItemPage)D2Common::GetAddressByOrdinal(10020);
	D2GetClassSkillID=(TD2GetClassSkillID)D2Common::GetAddressByOrdinal(10044);
	D2InventoryAddToContainer=(TD2InventoryAddToContainer)D2Common::GetAddressByOrdinal(10050);
	ADDD10061= (DWORD**)D2Common::GetAddressByOrdinal(10061);
	D2GetItemType = (TD2GetItemType)D2Common::GetAddressByOrdinal(10082);
	D2GetItemLevel = (TD2GetItemLevel)D2Common::GetAddressByOrdinal(10086);
	D2GetItemQuality = (TD2GetItemQuality)D2Common::GetAddressByOrdinal(10106);
	D2GetItemSize=(TD2GetItemSize)D2Common::GetAddressByOrdinal(10114);
	D2CanPutItemInInv=(TD2CanPutItemInInv)D2Common::GetAddressByOrdinal(10133);
	D2GetUnitXY=(TD2GetUnitXY)D2Common::GetAddressByOrdinal(10141);
	D2SetUnitStat = (TD2SetUnitStat)D2Common::GetAddressByOrdinal(10188);
	D2GetStatsFromListflag = (TD2GetStatsFromListflag)D2Common::GetAddressByOrdinal(10195);
	D2CheckItemFlag=(TD2CheckItemFlag)D2Common::GetAddressByOrdinal(10202);
	D2GetDifficultyLevelsBIN = (TD2GetDifficultyLevelsBIN)D2Common::GetAddressByOrdinal(10218);
	D2CheckItemRequirements=(TD2CheckItemRequirements)D2Common::GetAddressByOrdinal(10244);
	D2GetSkillLevel=(TD2GetSkillLevel)D2Common::GetAddressByOrdinal(10306);
	D2GetRoomFromUnit=(TD2GetRoomFromUnit)D2Common::GetAddressByOrdinal(10331);
	D2UpdateRoomFlags = (TD2UpdateRoomFlags)D2Common::GetAddressByOrdinal(10346);
	D2GetItemSockets=(TD2GetItemSockets)D2Common::GetAddressByOrdinal(10366);
	D2GetBodyloc=(TD2GetBodyloc)D2Common::GetAddressByOrdinal(10417);
	D2UpdateSkills=(TD2UpdateSkills)D2Common::GetAddressByOrdinal(10418);
	D2EvalItemCalc=(TD2EvalItemCalc)D2Common::GetAddressByOrdinal(10428);
	D2GetActFromLevel=(TD2GetActFromLevel)D2Common::GetAddressByOrdinal(10459);
	D2GetFirstInventoryItem = (TD2GetFirstInventoryItem)D2Common::GetAddressByOrdinal(10460);
	D2GetNextInventoryItem = (TD2GetNextInventoryItem)D2Common::GetAddressByOrdinal(10464);
	D2GetUnitState = (TD2GetUnitState)D2Common::GetAddressByOrdinal(10494);
	D2InitializeSkillList=(TD2InitializeSkillList)D2Common::GetAddressByOrdinal(10506);
	D2AddUnitStat = (TD2AddUnitStat)D2Common::GetAddressByOrdinal(10551);
	D2GetUnitBaseStat = (TD2GetUnitBaseStat)D2Common::GetAddressByOrdinal(10587);
	D2GetUniqueID=(TD2GetUniqueID)D2Common::GetAddressByOrdinal(10620);
	D2GetSkill=(TD2GetSkill)D2Common::GetAddressByOrdinal(10630);
	D2InvRemoveItem = (TD2InvRemoveItem)D2Common::GetAddressByOrdinal(10646);
	D2GetFreeCoords=(TD2GetFreeCoords)D2Common::GetAddressByOrdinal(10654);
	D2GetItemTxt = (TD2GetItemTxt)D2Common::GetAddressByOrdinal(10695);
	D2GetItemNodePage=(TD2GetItemNodePage)D2Common::GetAddressByOrdinal(10698);
	D2CheckItemType=(TD2CheckItemType)D2Common::GetAddressByOrdinal(10744);
	D2GetUnitPosXFromPath = (TD2GetUnitPosXFromPath)D2Common::GetAddressByOrdinal(10750);
	D2GetItemIndexFromCode =(TD2GetItemIndexFromCode)D2Common::GetAddressByOrdinal(10814);
	D2GetLevelNoFromRoom = (TD2GetLevelNoFromRoom)D2Common::GetAddressByOrdinal(10826);
	D2GetItemFlags = (TD2GetItemFlags)D2Common::GetAddressByOrdinal(10838);
	D2CompileTxtFile = (TD2CompileTxtFile)D2Common::GetAddressByOrdinal(10849);
	D2GetUnitPosYFromPath = (TD2GetUnitPosYFromPath)D2Common::GetAddressByOrdinal(10867);
	D2SetUnitStat2 = (TD2SetUnitStat2)D2Common::GetAddressByOrdinal(10887);
	D2GetPlayerData=(TD2GetPlayerData)D2Common::GetAddressByOrdinal(10920);
	D2GetUnitStat = (TD2GetUnitStat)D2Common::GetAddressByOrdinal(10973);
	D2SaveItem=(TD2SaveItem)D2Common::GetAddressByOrdinal(10987);
	D2GetCursorItem=(TD2GetCursorItem)D2Common::GetAddressByOrdinal(11017);
	D2GetUnitPosX = (TD2GetUnitPosX)D2Common::GetAddressByOrdinal(11080);
	D2MapToAbsScreen = (TD2MapToAbsScreen)D2Common::GetAddressByOrdinal(11087);
	D2SetAnimMode = (TD2SetAnimMode)D2Common::GetAddressByOrdinal(11090);
	D2InvAddItem=(TD2InvAddItem)D2Common::GetAddressByOrdinal(11107);
	D2GetClassSkillCount=(TD2GetClassSkillCount)D2Common::GetAddressByOrdinal(11120);
	D2GetItemByBodyLoc=(TD2GetItemByBodyLoc)D2Common::GetAddressByOrdinal(11139);
	D2UnitIsItem = (TD2UnitIsItem)D2Common::GetAddressByOrdinal(11147);
	D2GetUnitPosY = (TD2GetUnitPosY)D2Common::GetAddressByOrdinal(11168);

	VD2GetCharStatsBIN = (TD2GetCharStatsBIN)D2Common::GetAddress(0x12D0);
	D2GetCharStatsBIN = (TD2GetCharStatsBIN)D2CommonASM_D2GetCharStatsBIN;
	VD2GetItemStatCostBIN = (TD2GetItemStatCostBIN)D2Common::GetAddress(0x17A0);
	D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)D2CommonASM_D2GetItemStatCostBIN;
	D2GetLevelTxt = (TD2GetLevelTxt)D2CommonASM_D2GetLevelTxt;
	D2GetSkillsTxt=(TD2GetSkillsTxt)D2CommonASM_D2GetSkillsTxt;
	D2GetItemTypeBin = (TD2GetItemTypeBin)D2CommonASM_D2GetItemTypeBin;

	//变量
	nWeaponsTxt = (DWORD*)D2Common::GetAddress(0x9FBA0);
	nArmorTxt = (DWORD*)D2Common::GetAddress(0x9FBA8);
	pInventoryTxt = (InventoryTxt**)D2Common::GetAddress(0x9fa5c);
	SgptDataTables = (DataTables**)D2Common::GetAddress(0x99E1C);
	
}

D2Common::TD2SetItemPage D2Common::D2SetItemPage;
D2Common::TD2GetItemPage D2Common::D2GetItemPage;
D2Common::TD2GetClassSkillID D2Common::D2GetClassSkillID;
D2Common::TD2InventoryAddToContainer D2Common::D2InventoryAddToContainer;
DWORD** D2Common::ADDD10061;
D2Common::TD2GetItemType D2Common::D2GetItemType;
D2Common::TD2GetItemLevel D2Common::D2GetItemLevel;
D2Common::TD2GetItemQuality D2Common::D2GetItemQuality;
D2Common::TD2GetItemSize D2Common::D2GetItemSize;
D2Common::TD2CanPutItemInInv D2Common::D2CanPutItemInInv;
D2Common::TD2GetUnitXY D2Common::D2GetUnitXY;
D2Common::TD2SetUnitStat D2Common::D2SetUnitStat;
D2Common::TD2GetStatsFromListflag D2Common::D2GetStatsFromListflag;
D2Common::TD2CheckItemFlag D2Common::D2CheckItemFlag;
D2Common::TD2GetDifficultyLevelsBIN D2Common::D2GetDifficultyLevelsBIN;
D2Common::TD2CheckItemRequirements D2Common::D2CheckItemRequirements;
D2Common::TD2GetSkillLevel D2Common::D2GetSkillLevel;
D2Common::TD2GetRoomFromUnit D2Common::D2GetRoomFromUnit;
D2Common::TD2UpdateRoomFlags D2Common::D2UpdateRoomFlags;
D2Common::TD2GetItemSockets D2Common::D2GetItemSockets;
D2Common::TD2GetBodyloc D2Common::D2GetBodyloc;
D2Common::TD2UpdateSkills D2Common::D2UpdateSkills;
D2Common::TD2EvalItemCalc D2Common::D2EvalItemCalc;
D2Common::TD2GetActFromLevel D2Common::D2GetActFromLevel;
D2Common::TD2GetFirstInventoryItem D2Common::D2GetFirstInventoryItem;
D2Common::TD2GetNextInventoryItem D2Common::D2GetNextInventoryItem;
D2Common::TD2GetUnitState D2Common::D2GetUnitState;
D2Common::TD2InitializeSkillList D2Common::D2InitializeSkillList;
D2Common::TD2AddUnitStat D2Common::D2AddUnitStat;
D2Common::TD2GetUnitBaseStat D2Common::D2GetUnitBaseStat;
D2Common::TD2GetUniqueID D2Common::D2GetUniqueID;
D2Common::TD2GetSkill D2Common::D2GetSkill;
D2Common::TD2InvRemoveItem D2Common::D2InvRemoveItem;
D2Common::TD2GetFreeCoords D2Common::D2GetFreeCoords;
D2Common::TD2GetItemTxt D2Common::D2GetItemTxt;
D2Common::TD2GetItemNodePage D2Common::D2GetItemNodePage;
D2Common::TD2CheckItemType D2Common::D2CheckItemType;
D2Common::TD2GetUnitPosXFromPath D2Common::D2GetUnitPosXFromPath;
D2Common::TD2GetItemIndexFromCode D2Common::D2GetItemIndexFromCode;
D2Common::TD2GetLevelNoFromRoom D2Common::D2GetLevelNoFromRoom;
D2Common::TD2GetItemFlags D2Common::D2GetItemFlags;
D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFile;
D2Common::TD2GetUnitPosYFromPath D2Common::D2GetUnitPosYFromPath;
D2Common::TD2SetUnitStat2 D2Common::D2SetUnitStat2;
D2Common::TD2GetPlayerData D2Common::D2GetPlayerData;
D2Common::TD2GetUnitStat D2Common::D2GetUnitStat;
D2Common::TD2SaveItem D2Common::D2SaveItem;
D2Common::TD2GetCursorItem D2Common::D2GetCursorItem;
D2Common::TD2GetUnitPosX D2Common::D2GetUnitPosX;
D2Common::TD2MapToAbsScreen D2Common::D2MapToAbsScreen;
D2Common::TD2SetAnimMode D2Common::D2SetAnimMode;
D2Common::TD2InvAddItem D2Common::D2InvAddItem;
D2Common::TD2GetClassSkillCount D2Common::D2GetClassSkillCount;
D2Common::TD2GetItemByBodyLoc D2Common::D2GetItemByBodyLoc;
D2Common::TD2UnitIsItem D2Common::D2UnitIsItem;
D2Common::TD2GetUnitPosY D2Common::D2GetUnitPosY;

D2Common::TD2GetCharStatsBIN D2Common::VD2GetCharStatsBIN;
D2Common::TD2GetCharStatsBIN D2Common::D2GetCharStatsBIN;
D2Common::TD2GetItemStatCostBIN D2Common::VD2GetItemStatCostBIN;
D2Common::TD2GetItemStatCostBIN D2Common::D2GetItemStatCostBIN;
D2Common::TD2GetLevelTxt D2Common::D2GetLevelTxt;
D2Common::TD2GetSkillsTxt D2Common::D2GetSkillsTxt;
D2Common::TD2GetItemTypeBin D2Common::D2GetItemTypeBin;

DWORD* D2Common::nWeaponsTxt;
DWORD* D2Common::nArmorTxt;
InventoryTxt** D2Common::pInventoryTxt;
DataTables** D2Common::SgptDataTables;

DWORD __stdcall D2Common::GetItemStatFromFlag0x40(UnitAny* ptUnit, DWORD StatID, int Param)
{
	if (ptUnit && ptUnit->ptStats)
	{
		WORD sizestat = 0;
		StatEx* anstat = NULL;
		StatsList* pp = ptUnit->ptStats;
		if (ptUnit->nUnitType == UNIT_ITEM)StatsList* pp = D2Common::D2GetStatsFromListflag(ptUnit, 0x40);
		if (pp->ptAffixStats)//下一状态有指针有值,获得最后一次的属性列表指针
		{
			pp = pp->ptAffixStats;
			sizestat = pp->nbBaseStats;
			anstat = pp->ptBaseStatsTable;
		}
		else
		{
			anstat = pp->ptStatsTable;
			sizestat = pp->sizeOfStatsTable;
		}

		for (size_t i = 0; i < sizestat; i++)
		{
			if (anstat[i].id == StatID && anstat[i].index == Param)
			{
				return anstat[i].value;
			}
		}
	}
	return 0;
}

void __stdcall D2Common::SetItemStatFromFlag0x40(UnitAny* ptUnit, DWORD StatID, DWORD Value, int Param, NetClient* pClient)
{
	if (pClient == NULL)return;

	StatsList* pItem1StatsList = D2Common::D2GetStatsFromListflag(ptUnit, 0x40);

	if (pItem1StatsList == NULL)return;
	for (size_t i = 0; i < pItem1StatsList->nbBaseStats; i++)
	{
		if (pItem1StatsList->ptBaseStatsTable[i].id == StatID && pItem1StatsList->ptBaseStatsTable[i].index == Param)
		{
			pItem1StatsList->ptBaseStatsTable[i].value = Value;
			D2Game::D2UpdateClientItemStat(pClient, ptUnit, TRUE, StatID, Value);
		}
	}
}
