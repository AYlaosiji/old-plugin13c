#include"pch.h"
#ifdef MODULES_LEVELEXTEND
BOOL m_LevelExtended_IsOn = FALSE;

DWORD LevelExtendedOffset_1;
DWORD LevelExtendedOffset_2;
DWORD LevelExtendedOffset_3;
DWORD LevelExtendedOffset_4;
DWORD LevelExtendedOffset_5;
DWORD LevelExtendedOffset_6;
void NewCommonGetActFromLevel_ASM();
void NewCallCommon_10459_1();
void NewCallCommon_10459_2();
void NewCallCommon_10459_3();
void NewCallCommon_10459_4();
void NewCallCommon_10459_5();
void NewCallCommon_10459_6();

void m_LevelExtended_LoadCfg()
{
	m_LevelExtended_IsOn = cfgload::GetModuleCfgBool("Level Extended", "IsOn");
}

void m_LevelExtended_Install()
{
	DWORD LevelExtendedOffset = 0;

	if (m_LevelExtended_IsOn == FALSE)return;

	//6FB10516                                                     81EC A0100000                SUB ESP, 10A0
	LevelExtendedOffset = D2Client::GetAddress(0x6FB10518 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x000010A0, 0x000001A0);


	//6FB10536                                                     B9 99030000                  MOV ECX, 399
	LevelExtendedOffset = D2Client::GetAddress(0x6FB10537 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00000399, 0x00000063);

	//6FB1054B                                                     68 00100000                  PUSH 1000
	LevelExtendedOffset = D2Client::GetAddress(0x6FB1054C - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00001000, 0x00000190);

	//6FB1055B                                                     817C24 0C 00100000           CMP DWORD PTR SS : [ESP + C] , 1000
	LevelExtendedOffset = D2Client::GetAddress(0x6FB1055B + 0x4 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00001000, 0x00000190);

	//6FB10584                                                     68 00100000                  PUSH 1000
	LevelExtendedOffset = D2Client::GetAddress(0x6FB10584 + 0x1 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00001000, 0x00000190);

	//6FB10619                                                     68 00100000                  PUSH 1000
	LevelExtendedOffset = D2Client::GetAddress(0x6FB10619 + 0x1 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00001000, 0x00000190);

	////no stack restore, as its done via a stack frame...
	//6FB11E76                                                     81EC 4C100000                SUB ESP, 104C
	LevelExtendedOffset = D2Client::GetAddress(0x6FB11E76 + 0x2 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x0000104C, 0x000001D8);

	//6FB11EA9                                                     B9 99030000                  MOV ECX, 399
	LevelExtendedOffset = D2Client::GetAddress(0x6FB11EA9 + 0x1 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00000399, 0x00000063);

	//6FB11EBA                                                     68 00100000                  PUSH 1000
	LevelExtendedOffset = D2Client::GetAddress(0x6FB11EBA + 0x1 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00001000, 0x00000190);

	//6FB11ECE                                                     817C24 10 00100000           CMP DWORD PTR SS : [ESP + 10] , 1000
	LevelExtendedOffset = D2Client::GetAddress(0x6FB11ECE + 0x4 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00001000, 0x00000190);

	//6FB0F2EB                                                     68 00100000                  PUSH 1000
	LevelExtendedOffset = D2Client::GetAddress(0x6FB0F2EB + 0x1 - 0x6FAB0000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeDword(0x00001000, 0x00000190);

	//D2Common:这玩意是内联调用的??NewD2Common_10459_ASM
	LevelExtendedOffset = D2Common::GetAddress(0x2D2C0);
	Memory::SetCursor(LevelExtendedOffset);

	Memory::ChangeByte(0x8B, 0xE9);
	Memory::ChangeCallA(0xB804244C, (DWORD)NewCommonGetActFromLevel_ASM);
	Memory::ChangeDword(1, 0x90909090);

	//第一处
	LevelExtendedOffset = D2Common::GetAddress(0x6FD67196 - 0x6FD50000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeByte(0x3B, 0xE9);
	Memory::ChangeCallA(0x4668850C, (DWORD)NewCallCommon_10459_1);
	LevelExtendedOffset_1 = D2Common::GetAddress(0x6FD671EA - 0x6FD50000);

	//第二处
	LevelExtendedOffset = D2Common::GetAddress(0x6FD878D5 - 0x6FD50000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeByte(0x3B, 0xE9);
	Memory::ChangeCallA(0x4668851C, (DWORD)NewCallCommon_10459_2);
	LevelExtendedOffset_2 = D2Common::GetAddress(0x6FD8790F - 0x6FD50000);

	//第三处
	LevelExtendedOffset = D2Common::GetAddress(0x6FD87AA5 - 0x6FD50000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeByte(0x3B, 0xE9);
	Memory::ChangeCallA(0x4668851C, (DWORD)NewCallCommon_10459_3);
	LevelExtendedOffset_3 = D2Common::GetAddress(0x6FD87ADF - 0x6FD50000);

	//第四处
	LevelExtendedOffset = D2Common::GetAddress(0x6FD87B40 - 0x6FD50000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeByte(0x3B, 0xE9);
	Memory::ChangeCallA(0x4668851C, (DWORD)NewCallCommon_10459_4);
	LevelExtendedOffset_4 = D2Common::GetAddress(0x6FD87B8E - 0x6FD50000);

	//第五处
	LevelExtendedOffset = D2Common::GetAddress(0x6FD93620 - 0x6FD50000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeByte(0x3B, 0xE9);
	Memory::ChangeCallA(0x4668850C, (DWORD)NewCallCommon_10459_5);
	LevelExtendedOffset_5 = D2Common::GetAddress(0x6FD93676 - 0x6FD50000);

	//第六处
	LevelExtendedOffset = D2Common::GetAddress(0x6FD9A696 - 0x6FD50000);
	Memory::SetCursor(LevelExtendedOffset);
	Memory::ChangeByte(0xB8, 0xE9);
	Memory::ChangeCallA(0x00000001, (DWORD)NewCallCommon_10459_6);
	LevelExtendedOffset_6 = D2Common::GetAddress(0x6FD9A6DF - 0x6FD50000);

}

void m_LevelExtended_UnInstall()
{

}

DWORD __stdcall NewCommonGetActFromLevel(DWORD lvl)
{
	LevelsBIN* pLevelBin = D2Common::D2GetLevelTxt(lvl);
	Fog::D2Assert(!pLevelBin, "Cant Get Level Bin", __FILE__, __LINE__);
	return pLevelBin->nAct;
}

__declspec(naked) void NewCommonGetActFromLevel_ASM()
{
	__asm
	{
		push ebx
		push ecx
		push edx
		push ebp
		push esi
		push edi
		push ebx
		push[esp + 0x20]
		call NewCommonGetActFromLevel
		pop ebx
		pop edi
		pop esi
		pop ebp
		pop edx
		pop ecx
		pop ebx
		retn 4
	}
}

__declspec(naked) void NewCallCommon_10459_1()
{
	__asm
	{
		push ecx
		CALL D2Common::D2GetActFromLevel
		INC eax
		JMP LevelExtendedOffset_1
	}
}

__declspec(naked) void NewCallCommon_10459_2()
{
	__asm
	{
		push ebx
		CALL D2Common::D2GetActFromLevel
		INC eax
		JMP LevelExtendedOffset_2
	}
}

__declspec(naked) void NewCallCommon_10459_3()
{
	__asm
	{
		push ebx
		CALL D2Common::D2GetActFromLevel
		INC eax
		JMP LevelExtendedOffset_3
	}
}

__declspec(naked) void NewCallCommon_10459_4()
{
	__asm
	{
		push ebx
		CALL D2Common::D2GetActFromLevel
		INC eax
		JMP LevelExtendedOffset_4
	}
}

__declspec(naked) void NewCallCommon_10459_5()
{
	__asm
	{
		push ecx
		CALL D2Common::D2GetActFromLevel
		INC eax
		JMP LevelExtendedOffset_5
	}
}

__declspec(naked) void NewCallCommon_10459_6()
{
	__asm
	{
		push edx
		CALL D2Common::D2GetActFromLevel
		INC eax
		JMP LevelExtendedOffset_6
	}
}

#endif // MODULES_LEVELEXTEND

