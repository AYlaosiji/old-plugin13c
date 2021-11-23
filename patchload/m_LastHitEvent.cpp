#include"pch.h"
#ifdef MODULE_LASTHITEVENT

void m_SoulSkills_ShowDamageEnd_ASM();//ÈËÎïËÀÍö
void m_SoulSkills_ExpUpEnd_ASM();//¹ÖÎïËÀÍö

void m_LastHitEvent_LoadCfg() 
{

}

void m_LastHitEvent_Install()
{
	DWORD offset;
#ifdef D2SERVER
	offset = D2Game::GetAddress(0xDE35A);
	Memory::SetCursor(offset);
	Memory::ChangeCallA(0xFFF58CD2, (DWORD)m_SoulSkills_ShowDamageEnd_ASM);

	offset = D2Game::GetAddress(0xDE74A);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x5B, 0xE9);
	Memory::ChangeCallA(0x000cc25E, (DWORD)m_SoulSkills_ExpUpEnd_ASM);
#endif
}

void m_LastHitEvent_UnInstall()
{

}

#ifdef D2SERVER
void __fastcall m_Damage_DamageHookEnd(GameStruct* pDmg, UnitAny* Killed, void* unk, int nDamage, UnitAny* Killer, DamageData* pdmg)
{
#ifdef MODULES_SOULSKILLS
	m_SoulSkills_ClearSoulsLastHit(pDmg, Killed, unk, nDamage, Killer, pdmg);
#endif

#ifdef MODULES_PLAYERDEATHKILLCOUNT
	m_PlayerDeathKillCount_AddPlayerDeathLastHit(pDmg, Killed, unk, nDamage, Killer, pdmg);
#endif

#ifdef MODULES_KUILEICHARM
	m_KuiLeiCharm_DoKuiLeiCharmLastHit(pDmg, Killed, unk, nDamage, Killer, pdmg);
#endif
}

__declspec(naked) void m_SoulSkills_ShowDamageEnd_ASM()
{
	__asm
	{
		//edi
		//ebx
		//esp+0-10
		pushad
		mov ecx, edi
		mov edx, ebx
		push DWORD PTR SS : [ESP + 0x30]
		push DWORD PTR SS : [ESP + 0x30]
		push DWORD PTR SS : [ESP + 0x30]
		push DWORD PTR SS : [ESP + 0x30]
		call m_Damage_DamageHookEnd
		popad
		jmp D2Game::VD2ApplyDamage
	}
}

void __stdcall m_SoulSkills_ExpUpEnd(NetClient* pClient, UnitAny* pPlayer, DWORD unkexp)
{
	if (pPlayer && pPlayer->ptGame)
	{
#ifdef MODULES_SOULSKILLS
		m_SoulSkills_AddPlayerSoul(pClient, pPlayer, unkexp);
#endif

#ifdef MODULES_PLAYERDEATHKILLCOUNT
		m_PlayerDeathKillCount_AddPlayerKill(pClient, pPlayer, unkexp);
#endif
	}
}

void __declspec(naked) m_SoulSkills_ExpUpEnd_ASM()//stdcall
{
	__asm
	{

		push ecx
		push edx
		push ebp
		push edi
		push ebx

		push edi
		push esi
		push ebp
		call m_SoulSkills_ExpUpEnd

		pop ebx
		pop edi
		pop ebp
		pop edx
		pop ecx

		pop ebx
		pop esi//pPlayer ebp:pClient edi exp 
		retn 0xC
	}
}

#endif

#endif
