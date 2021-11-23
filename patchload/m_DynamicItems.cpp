#include"pch.h"
#ifdef MODULES_DYNAMICITEMS
BYTE m_DynamicItems_IsOn = FALSE;

void m_DynamicItems_ShowItem_ASM();

void m_DynamicItems_LoadCfg()
{
	m_DynamicItems_IsOn = cfgload::GetModuleCfgBool("Dynamic Items","IsOn");
}

void m_DynamicItems_Install()
{
	if (m_DynamicItems_IsOn)
	{
		DWORD DynamicItemsOffset = D2Client::GetAddress(0x6B6B3);
		Memory::SetCursor(DynamicItemsOffset);
		Memory::ChangeCallA(0xFFFA19DF, (DWORD)m_DynamicItems_ShowItem_ASM);
	}
}

void m_DynamicItems_UnInstall()
{

}

__declspec(naked) void m_DynamicItems_ShowItem_ASM()
{
	__asm
	{
		mov ecx, dword ptr ds : [esp+0x5c]
		cmp ecx,1
		je Mark1
		push ecx
		call GetTickCount
		xor edx,edx
		mov edi,0x28
		div edi
		xor edx,edx
		pop ecx
		div ecx
		mov dword ptr ds : [esp+0x2c],edx
		JMP D2Gfx::D2DrawImage
Mark1:
		jmp D2Gfx::D2DrawImage
	}
}

#endif