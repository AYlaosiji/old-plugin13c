#include"pch.h"
#ifdef MODULES_NEWSTATDESC

void m_NewStatDescInstead_ASM();
void caller_displayItemlevel_113();
void caller_displayItemlevelSet_111();

void m_NewStatDesc_LoadCfg()
{
}

void m_NewStatDesc_Install()
{
	DWORD offset;

	offset = D2Client::GetAddress(0x6FB05D9E - 0x6FAB0000);
	Memory::SetCursor(offset);
	Memory::ChangeCallA(0xFFFFF06E,(DWORD)m_NewStatDescInstead_ASM);

	offset = D2Client::GetAddress(0x941C0);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x68, 0xE8);
	Memory::ChangeCallA(0x100, (DWORD)caller_displayItemlevel_113);

	offset = D2Client::GetAddress(0x92FE3);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x68, 0xE8);
	Memory::ChangeCallA(0x100, (DWORD)caller_displayItemlevelSet_111);

}

void m_NewStatDesc_UnInstall()
{

}

BOOL __fastcall m_NewStatDescInstead(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue)
{
#ifdef MODULES_MAGICBAG
	if (m_MagicBag_NewStatDesc(wszchar, statID, pItem, statvalue))return TRUE;
#endif

#ifdef MODULES_PLAYERDEATHKILLCOUNT
	if (m_PlayerDeathKillCount_NewStatDesc(wszchar, statID, pItem, statvalue))return TRUE;
#endif

#ifdef MODULES_SOULSKILLS
	if(m_SoulSkills_NewStatDesc(wszchar, statID, pItem, statvalue))return TRUE;
#endif

#ifdef MODULES_XUKONGCHARM
	if (m_XuKongCharm_NewStatDesc(wszchar, statID, pItem, statvalue))return TRUE;
#endif 

#ifdef MODULES_MULTIFLAGSTATSHOW
	if (m_MultiFlagStatShow_NewStatDesc(wszchar, statID, pItem, statvalue))return TRUE;
#endif

	return FALSE;//正常走
}

__declspec(naked) void m_NewStatDescInstead_ASM()
{
	__asm
	{
		//eax是属性
		//esp+14是显示的属性文本
		//esp+4是item
		//esp+C是statvalue
		//esp+10是value
		PUSH EAX
		PUSH ESI
		PUSH ECX
		PUSH EDX
		MOV ECX, ESI
		MOV EDX, EAX
		PUSH DWORD PTR SS : [ESP + 0x20]
		PUSH DWORD PTR SS : [ESP + 0x12F8]
		CALL m_NewStatDescInstead
		TEST EAX, EAX
		JNZ mark1
		POP EDX
		POP ECX
		POP ESI
		POP EAX
		jmp D2Client::VD2PrintStat
mark1:
		POP EDX
		POP ECX
		POP ESI
		POP EAX
		MOV EAX ,1
		retn 0x10
	}
}

void __stdcall displayItemlevel(LPWSTR popup, UnitAny* ptItem)
{
#ifdef MODULES_STATFUNCTIONS
	m_StatFunctions_hint(popup, ptItem);
#endif

}

__declspec(naked) void caller_displayItemlevel_113()
{
	__asm
	{
		PUSH ECX
		PUSH EAX
		PUSH EAX
		LEA EAX, DWORD PTR SS : [ESP + 0x1E70]
		PUSH EAX
		CALL displayItemlevel
		POP EAX
		POP ECX
		POP EDX
		PUSH 0x100
		JMP EDX
	}
}

__declspec(naked) void caller_displayItemlevelSet_111()
{
	__asm
	{
		PUSH ECX
		PUSH EDX
		PUSH ECX
		LEA EAX, DWORD PTR SS : [ESP + 0x1958]
		PUSH EAX
		CALL displayItemlevel
		POP EDX
		POP ECX
		POP EAX
		PUSH 0x100
		JMP EAX
	}
}

#endif
