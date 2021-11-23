#include "pch.h"
#ifdef MODULES_STATFUNCTIONS
#define STR_ITEM_NOTINCHARMZONE L"需放入右侧护符区域生效"

static BOOL m_StatFunctions_FixStatScreenNagtiveShow = FALSE;

static BOOL m_StatFunctions_StatLimit_IsOn = FALSE;
static BOOL m_StatFunctions_StatLimit_NewShow_IsOn = FALSE;
static WORD m_StatFunctions_StatA;
static WORD m_StatFunctions_Stat1;
static WORD m_StatFunctions_StatB;
static WORD m_StatFunctions_Stat2;
static WORD m_StatFunctions_StatC;
static WORD m_StatFunctions_Stat3;
static WORD m_StatFunctions_StatD;
static WORD m_StatFunctions_Stat4;
static WORD m_StatFunctions_StatE;
static WORD m_StatFunctions_Stat5;
static WORD m_StatFunctions_StatF;
static WORD m_StatFunctions_Stat6;

static BOOL m_StatFunctions_CharmZone_IsOn = FALSE;
static BOOL m_StatFunctions_CharmZone_NewShow_IsOn = FALSE;
static BYTE m_StatFunctions_CharmZoneTop;
static BYTE m_StatFunctions_CharmZoneLeft;
static BYTE m_StatFunctions_CharmZoneBottom;
static BYTE m_StatFunctions_CharmZoneRight;
#define MAXCHARMZONECODE 255
static DWORD m_StatFunctions_CharmZoneCode[MAXCHARMZONECODE] = {NULL};


void FixStatScreenNagtiveShow();
void m_StatFunctions_RandomStat_ASM();
void m_StatFunctions_StatLimit_ASM();



void m_StatFunctions_LoadCfg()
{
	m_StatFunctions_FixStatScreenNagtiveShow= cfgload::GetModuleCfgBool("Stat Functions", "Fix Stat Screen Nagtive Show");
	m_StatFunctions_StatLimit_IsOn = cfgload::GetModuleCfgBool("Stat Functions", "Stat Limit IsOn");
	m_StatFunctions_StatLimit_NewShow_IsOn= cfgload::GetModuleCfgBool("Stat Functions", "Stat Limit Show IsOn");

	m_StatFunctions_StatA = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit StatA");
	m_StatFunctions_Stat1 = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit Stat1");
	m_StatFunctions_StatB = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit StatB");
	m_StatFunctions_Stat2 = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit Stat2");
	m_StatFunctions_StatC = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit StatC");
	m_StatFunctions_Stat3 = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit Stat3");
	m_StatFunctions_StatD = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit StatD");
	m_StatFunctions_Stat4 = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit Stat4");
	m_StatFunctions_StatE = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit StatE");
	m_StatFunctions_Stat5 = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit Stat5");
	m_StatFunctions_StatF = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit StatF");
	m_StatFunctions_Stat6 = cfgload::GetModuleCfgInt("Stat Functions", "Stat Limit Stat6");

	m_StatFunctions_CharmZone_IsOn= cfgload::GetModuleCfgBool("Stat Functions", "Charm Zone IsOn");
	m_StatFunctions_CharmZone_NewShow_IsOn= cfgload::GetModuleCfgBool("Stat Functions", "Charm Zone New Show IsOn");
	m_StatFunctions_CharmZoneTop= cfgload::GetModuleCfgInt("Stat Functions", "Charm Zone Top");
	m_StatFunctions_CharmZoneLeft= cfgload::GetModuleCfgInt("Stat Functions", "Charm Zone Left");
	m_StatFunctions_CharmZoneBottom= cfgload::GetModuleCfgInt("Stat Functions", "Charm Zone Bottom");
	m_StatFunctions_CharmZoneRight= cfgload::GetModuleCfgInt("Stat Functions", "Charm Zone Right");
	cJSON* Vec[MAXCHARMZONECODE] = {0};
	cfgload::GetModuleMapValues("Stat Functions", "Charm Zone Code", Vec, MAXCHARMZONECODE);
	for (size_t i = 0; i < MAXCHARMZONECODE; i++)
	{
		if (Vec[i] && Vec[i]->type == cJSON_String)memcpy(&m_StatFunctions_CharmZoneCode[i], Vec[i]->valuestring, sizeof(DWORD));
	}
}

void m_StatFunctions_Install()
{
		DWORD offset;
		if (m_StatFunctions_FixStatScreenNagtiveShow)
		{
			offset = D2Client::GetAddress(0xBD929);
			Memory::SetCursor(offset);
			Memory::ChangeByte(0x83, 0xE8);
			Memory::ChangeCallA(0x057F9CFE, (DWORD)FixStatScreenNagtiveShow);
			Memory::ChangeByte(0xBE, 0x90);
			Memory::ChangeDword(0xFFFFFF9C, 0x90909090);
		}

		if (m_StatFunctions_StatLimit_IsOn|| m_StatFunctions_CharmZone_IsOn)
		{
			offset = D2Common::GetAddress(0x2706D);
			Memory::SetCursor(offset);
			Memory::ChangeByte(0x83, 0xE9);
			Memory::ChangeCallA(0x18C220C4, (DWORD)m_StatFunctions_StatLimit_ASM);
			Memory::ChangeByte(0x00, 0x90);
		}


	
}

void m_StatFunctions_UnInstall()
{

}

static BOOL  __fastcall m_StatFunctions_StatLimit(UnitAny* pPlayer, UnitAny* pItem)
{
	if (pPlayer && pItem)
	{
		if (m_StatFunctions_StatLimit_IsOn)
		{
			if (m_StatFunctions_StatA && m_StatFunctions_Stat1)
			{
				if (D2Common::D2GetUnitStat(pPlayer, m_StatFunctions_Stat1, 0) < D2Common::D2GetUnitStat(pItem, m_StatFunctions_StatA, 0))return FALSE;
			}
			if (m_StatFunctions_StatB && m_StatFunctions_Stat2)
			{
				if (D2Common::D2GetUnitStat(pPlayer, m_StatFunctions_Stat2, 0) < D2Common::D2GetUnitStat(pItem, m_StatFunctions_StatB, 0))return FALSE;
			}
			if (m_StatFunctions_StatC && m_StatFunctions_Stat3)
			{
				if (D2Common::D2GetUnitStat(pPlayer, m_StatFunctions_Stat3, 0) < D2Common::D2GetUnitStat(pItem, m_StatFunctions_StatC, 0))return FALSE;
			}
			if (m_StatFunctions_StatD && m_StatFunctions_Stat4)
			{
				if (D2Common::D2GetUnitStat(pPlayer, m_StatFunctions_Stat4, 0) < D2Common::D2GetUnitStat(pItem, m_StatFunctions_StatD, 0))return FALSE;
			}
			if (m_StatFunctions_StatE && m_StatFunctions_Stat5)
			{
				if (D2Common::D2GetUnitStat(pPlayer, m_StatFunctions_Stat5, 0) < D2Common::D2GetUnitStat(pItem, m_StatFunctions_StatE, 0))return FALSE;
			}
			if (m_StatFunctions_StatF && m_StatFunctions_Stat6)
			{
				if (D2Common::D2GetUnitStat(pPlayer, m_StatFunctions_Stat6, 0) < D2Common::D2GetUnitStat(pItem, m_StatFunctions_StatF, 0))return FALSE;
			}
		}
		if (m_StatFunctions_CharmZone_IsOn && pItem->pItemPath && D2Common::D2GetItemPage(pItem) == 0)
		{
			if (pItem->pItemPath->dwPosX< m_StatFunctions_CharmZoneLeft
				|| pItem->pItemPath->dwPosX>m_StatFunctions_CharmZoneRight
				|| pItem->pItemPath->dwPosY < m_StatFunctions_CharmZoneTop
				|| pItem->pItemPath->dwPosY>m_StatFunctions_CharmZoneBottom
				)
			{
				ItemBIN* pItemtxt = D2Common::D2GetItemTxt(pItem->dwTxtFileNo);
				if (pItemtxt->ItemCode)
				{
					for (size_t i = 0; i < MAXCHARMZONECODE; i++)
					{
						if (pItemtxt->ItemCode == m_StatFunctions_CharmZoneCode[i])//需要限制
						{
							return FALSE;
						}
					}
				}
			}
		}
	}
	return TRUE;//返回TRUE 可用 返回FALSE 不可用
}

__declspec(naked) void m_StatFunctions_StatLimit_ASM()
{
	__asm
	{
		push ecx
		push edx
		MOV ECX, dword ptr ss : [esp + 0x30]
		MOV EDX, dword ptr ss : [esp + 0x2C]
		call m_StatFunctions_StatLimit
		pop ecx
		pop edx
		add esp, 0x20
		retn 0x18
	}
}

__declspec(naked) void FixStatScreenNagtiveShow()
{
	__asm
	{
		cmp esi, INT_MIN
		jg mark1
		mov esi, INT_MIN
mark1:
		retn
	}
}

void m_StatFunctions_hint(LPWSTR popup, UnitAny* ptItem)
{
	if (m_StatFunctions_CharmZone_NewShow_IsOn && ptItem->pItemPath && D2Common::D2GetItemPage(ptItem) == 0)
	{
		if (ptItem->pItemPath->dwPosX< m_StatFunctions_CharmZoneLeft
			|| ptItem->pItemPath->dwPosX>m_StatFunctions_CharmZoneRight
			|| ptItem->pItemPath->dwPosY < m_StatFunctions_CharmZoneTop
			|| ptItem->pItemPath->dwPosY>m_StatFunctions_CharmZoneBottom
			)
		{
			ItemBIN* pItemtxt = D2Common::D2GetItemTxt(ptItem->dwTxtFileNo);
			if (pItemtxt->ItemCode)
			{
				for (size_t i = 0; i < MAXCHARMZONECODE; i++)
				{
					if (pItemtxt->ItemCode == m_StatFunctions_CharmZoneCode[i])//需要限制
					{
						WCHAR text[0x50];
						_snwprintf(text, sizeof(text), L"%s\n", STR_ITEM_NOTINCHARMZONE);
						D2Client::D2SetColorPopup(text, D2Color::RED);
						wcscat(popup, text);
					}
				}
			}
		}
	}
}

#endif