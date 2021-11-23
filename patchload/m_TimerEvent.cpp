#include "pch.h"
#ifdef MODULES_TIMEREVENT
void m_TimeEvent_ASM();

void m_TimerEvent_LoadCfg()
{

}

void m_TimerEvent_Install()
{
#ifdef D2SERVER

        DWORD TimeEventOffset = D2Game::GetAddress(0x8EA81);
        Memory::SetCursor(TimeEventOffset);
        Memory::ChangeByte(0x8B, 0xE8);
        Memory::ChangeCallA(0x8308245C, (DWORD)m_TimeEvent_ASM);
        Memory::ChangeByte(0xFB, 0x90);
        Memory::ChangeByte(0x0F, 0x90);
#endif

}

void m_TimerEvent_UnInstall()
{
}


void __fastcall MyTimeEvent(GameStruct* pGame, UnitAny* pUnit, DWORD Frame, DWORD Type)
{
#ifdef D2SERVER
	if (Frame < 5* 25)//5ÃëÄÚÎÞÐ§
		return;
#ifdef MODULES_XUKONGCHARM
	m_XuKongCharm_XuKongLoop(pGame, pUnit, Frame, Type);
#endif

#ifdef MODULES_WORLDMONSTER
	WorldMonsterInteract::SendPlayerItem(pGame, pUnit, Frame, Type);
#endif
#endif
}

__declspec(naked) void m_TimeEvent_ASM()
{
	__asm
	{
		push ecx
		push edx
		push dword ptr ss : [esp + 0x14]
		push dword ptr ss : [esp + 0x1C]
		call MyTimeEvent
		pop edx
		pop ecx
		mov ebx, dword ptr ss : [esp + 0xC]
		cmp ebx, 0xF
		ret
	}
}

#endif // MODULES_TIMEREVENT
