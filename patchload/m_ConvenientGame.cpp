#include"pch.h"
#ifdef MODULES_CONVENIENTGAME
static BOOL m_ConvenientGame_AllWaypointIsOn = FALSE;

void m_ConvenientGame_AllWp_ASM();

void m_ConvenientGame_LoadCfg()
{
	m_ConvenientGame_AllWaypointIsOn = cfgload::GetModuleCfgBool("Convenient Game", "All Waypoint");
}

void m_ConvenientGame_Install()
{
#ifdef D2SERVER

	DWORD Offset;
	if (m_ConvenientGame_AllWaypointIsOn)
	{
		Offset = D2Common::GetAddress(0x67C69);
		Memory::SetCursor(Offset);
		Memory::ChangeByte(0x0F, 0xE9);
		Memory::ChangeCallA(0xE0C1C0B7, (DWORD)m_ConvenientGame_AllWp_ASM);
		Memory::ChangeByte(0x02, 0x90);
		Memory::ChangeByte(0x0f, 0x90);
	}

#endif
}

void m_ConvenientGame_UnInstall()
{

}

#ifdef D2SERVER
void __declspec(naked) m_ConvenientGame_AllWp_ASM()
{
	__asm
	{
		xor eax, eax
		dec eax
		mov[ecx + 0x2], ax
		mov[ecx + 0x4], eax
		mov[ecx + 0x8], eax
		mov[ecx + 0xc], eax
		ret 0x8
	}
}
#endif
#endif