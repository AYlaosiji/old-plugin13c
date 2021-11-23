#include"pch.h"
#ifdef MODULES_STATFILTER

void m_StatFilter_LoadCfg()
{
}

void m_StatFunctions_RandomStat_ASM();

static DWORD m_StatFunctions_RandomStatValueJMPBackOffSet;
void m_StatFilter_Install()
{
#ifdef D2SERVER

	m_StatFunctions_RandomStatValueJMPBackOffSet = D2Common::GetAddress(0x38B76);
	DWORD offset = D2Common::GetAddress(0x38B70);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE9);
	Memory::ChangeCallA(0x85042444, (DWORD)m_StatFunctions_RandomStat_ASM);
	Memory::ChangeByte(0xC0, 0x90);

#endif
}

void m_StatFilter_UnInstall()
{

}

#ifdef D2SERVER
static DWORD  __stdcall m_StatFunctions_MyStatFilter(DWORD unk, DWORD statno, UnitAny* unit)
{
	DWORD ret = 0;
#ifdef MODULES_RANDOMSTAT
	ret = m_RamdonStat_Filter(unk, statno, unit); if (ret)return ret;
#endif
	return ret;
}

__declspec(naked) void m_StatFunctions_RandomStat_ASM()
{
	__asm
	{
		mov eax, dword ptr ss : [esp + 0x4]
		push eax
		mov eax, dword ptr ss : [esp + 0xC]
		push eax
		mov eax, dword ptr ss : [esp + 0x14]
		push eax
		call m_StatFunctions_MyStatFilter
		test eax, eax
		jnz Myret
		mov eax, dword ptr ss : [esp + 0x4]
		test eax, eax
		jmp m_StatFunctions_RandomStatValueJMPBackOffSet
		Myret :
		retn 0xC
	}
}

#endif

#endif