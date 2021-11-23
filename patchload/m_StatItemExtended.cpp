#include"pch.h"
#ifdef MODULE_STATITEMEXTENDED
#define MAX_STATITEMEXTENDED_TYPES 50
DWORD m_StatItemExtended_UpdateItemType[MAX_STATITEMEXTENDED_TYPES] = { 0 };
void m_StatItemExtended_ModifyItem_ASM();

void m_StatItemExtended_LoadCfg()
{
	cJSON* pObject = cfgload::GetModuleCfg("Stat Item Extended", "Item Update Type");
	if (pObject && pObject->type == cJSON_Array)
	{
		int size=cJSON_GetArraySize(pObject);
		for (int i = 0; i < min(size, MAX_STATITEMEXTENDED_TYPES); i++)
		{
			cJSON* pObject2 = cJSON_GetArrayItem(pObject, i);
			if (pObject2 && pObject2->type == cJSON_Number)
			{
				m_StatItemExtended_UpdateItemType[i] = pObject2->valueint;
			}
		}
	}
}


BOOL m_StatItemExtended_CheckItemNeedUpdate(DWORD dwTxtFileNo)
{
	DWORD ItemType = D2Common::D2GetItemType(dwTxtFileNo);

	for (int i = 0; i <= MAX_STATITEMEXTENDED_TYPES; i++)
	{
		if (m_StatItemExtended_UpdateItemType[i] && ItemType == m_StatItemExtended_UpdateItemType[i])
			return TRUE;
	}
	return FALSE;
}

void m_StatItemExtended_Install()
{
	DWORD m_StatItemExtended_Offset=0;
	//客户端接受到更改属性的时候
	m_StatItemExtended_Offset = D2Client::GetAddress(0x859DD);
	Memory::SetCursor(m_StatItemExtended_Offset);
	Memory::ChangeByte(0x81, 0xE8);
	Memory::ChangeCallA(0x0000CCFB, (DWORD)m_StatItemExtended_ModifyItem_ASM);
	Memory::ChangeByte(0x00, 0x90);
}

void m_StatItemExtended_UnInstall()
{

}

static void __fastcall m_MagicBag_ModifyItem(UnitAny* pItem, DWORD statID, DWORD statvalue)
{
	if (
		pItem && D2Common::D2GetItemType(pItem->dwTxtFileNo)&& 
		m_StatItemExtended_CheckItemNeedUpdate(pItem->dwTxtFileNo)
		)
	{
		StatsList* plist = D2Common::D2GetStatsFromListflag(pItem, 0x40);
		StatEx* pStatEx = plist->ptBaseStatsTable;
		for (size_t i = 0; i < plist->nbBaseStats; i++)
		{
			StatEx temp = pStatEx[i];
			if (temp.id == statID)
			{
				pStatEx[i].value = statvalue;
				return;
			}
		}
	}
	return;
}

__declspec(naked) void m_StatItemExtended_ModifyItem_ASM()
{
	__asm
	{
		push ebx//是ID号,保存
		push ecx//保存ecx
		push edx//保存edx
		push edi//保存edi
		mov ecx, esi
		mov edx, ebx
		push edi //属性值
		call m_MagicBag_ModifyItem
		pop edi
		pop edx
		pop ecx
		pop ebx
		cmp ebx, 0xCC
		ret
	}
}

#endif