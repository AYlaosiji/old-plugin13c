#include"pch.h"

#ifdef MODULES_32KLIFEFIX

static BOOL m_StatFunctions_32klimitIsOn = FALSE;

void m_StatFunctions_Stat32klimit_ASM();

void m_32KLifeFix_LoadCfg()
{
	m_StatFunctions_32klimitIsOn = cfgload::GetModuleCfgBool("32HP MANA STAMINA Fix", "IsOn");
}

void m_32KLifeFix_Install()
{
	DWORD offset = 0;

	if (m_StatFunctions_32klimitIsOn)
	{
#ifdef D2SERVER
		offset = D2Game::GetAddress(0x8B81B);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xf, 0x20);

		offset = D2Game::GetAddress(0x8B82D);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xf, 0x20);

		offset = D2Game::GetAddress(0x8B83F);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xf, 0x20);
#endif

		offset = D2Client::GetAddress(0xAC1CF);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xf, 0x20);

		offset = D2Client::GetAddress(0xAC1DB);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xf, 0x20);

		offset = D2Client::GetAddress(0xAC1EB);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xf, 0x20);

#ifdef D2SERVER
		offset = D2Game::GetAddress(0x8B8A8);
		Memory::SetCursor(offset);
		Memory::ChangeCallC((DWORD)D2Game::VD2SendPacketToClient, (DWORD)m_StatFunctions_Stat32klimit_ASM);
#endif

		offset = D2Client::GetAddress(0x6FB5EBFE - 0x6FAB0000);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x0f, 0xEB);
		Memory::ChangeByte(0xb7, 0x37);
		Memory::ChangeByte(0x7c, 0x90);
		Memory::ChangeByte(0x24, 0x90);
		Memory::ChangeByte(0x09, 0x90);
	}
}

void m_32KLifeFix_UnInstall()
{

}

#ifdef D2SERVER
void __fastcall m_StatFunctions_Stat32klimit(DWORD len, BYTE* packet, UnitAny* pPlayer, DWORD hp, DWORD mana, DWORD naili)
{
	if (pPlayer && pPlayer->nUnitType == 1)
	{
		DWORD V = 1;
	}
	D2Game::D2SendPacketToClient(pPlayer->ptPlayerData->ptNetClient, packet, len);//13->21∂‡¡À8
	updateClient(pPlayer, UC_UPDATEBASESTAT, hp, mana, naili);
	return;
}

__declspec(naked) void m_StatFunctions_Stat32klimit_ASM()
{
	__asm
	{
		pushad
		mov ecx, [esp + 0x8 + 0x20]
		mov edx, [esp + 0x4 + 0x20]
		push[esp + 0x60]
		push[esp + 0x60]
		push[esp + 0x60]
		push esi
		call m_StatFunctions_Stat32klimit
		popad

		RETN 0X8
	}
}
#endif


void m_32KLifeFix_ClientChangehpmanasta(DWORD hp, DWORD mana, DWORD naili)
{
	if (m_StatFunctions_32klimitIsOn)
	{
		UnitAny* pPlayer = *D2Client::ptPlayerClient;
		if (!pPlayer)return;
		D2Common::D2SetUnitStat2(pPlayer, 6, hp * 256, 0);
		D2Common::D2SetUnitStat2(pPlayer, 8, mana * 256, 0);
		D2Common::D2SetUnitStat2(pPlayer, 10, naili * 256, 0);
	}
}

#endif // MODULES_32KLIFEFIX


