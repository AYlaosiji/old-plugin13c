#include"pch.h"
#ifdef MODULES_DRAWFUNCTIONS

void D2DrawFuns_ClientDraw_ASM();
void caller_loadCustomImages();
void caller_loadCustomImages2();
void caller_freeCustomImages();
void caller_freeCustomImages2();
void D2DrawFuns_LifeBar_ASM();

void m_DrawFunctions_LoadCfg()
{
}

void m_DrawFunctions_Install()
{
	DWORD D2DrawFuns_OffSet;

	D2DrawFuns_OffSet = D2Client::GetAddress(0x29295);
	Memory::SetCursor(D2DrawFuns_OffSet);
	Memory::ChangeCallA(0xFFFFDFF7, (DWORD)D2DrawFuns_ClientDraw_ASM);

	//D2DrawFuns_OffSet = D2Client::GetAddress(0x27EAE);
	//Memory::SetCursor(D2DrawFuns_OffSet);
	//Memory::ChangeByte(0xB9, 0XE8);
	//Memory::ChangeCallA(0x0000000C, (DWORD)caller_loadCustomImages);

	D2DrawFuns_OffSet = D2Client::GetAddress(0x27EE2);
	Memory::SetCursor(D2DrawFuns_OffSet);
	Memory::ChangeByte(0xC3, 0XE9);
	Memory::ChangeCallA(0xcccccccC, (DWORD)caller_loadCustomImages2);

	//D2DrawFuns_OffSet = D2Client::GetAddress(0x26F8D);
	//Memory::SetCursor(D2DrawFuns_OffSet);
	//Memory::ChangeByte(0xB9, 0XE8);
	//Memory::ChangeCallA(0x0000000C, (DWORD)caller_freeCustomImages);

		D2DrawFuns_OffSet = D2Client::GetAddress(0x26F9B);
	Memory::SetCursor(D2DrawFuns_OffSet);
	Memory::ChangeByte(0x5F, 0XE9);
	Memory::ChangeCallA(0xCCCCC35E, (DWORD)caller_freeCustomImages2);


	D2DrawFuns_OffSet = D2Win::GetAddress(0x134EF);
	Memory::SetCursor(D2DrawFuns_OffSet);
	Memory::ChangeCallB((DWORD)D2Gfx::D2FillArea, (DWORD)D2DrawFuns_LifeBar_ASM);
}


void m_DrawFunctions_UnInstall()
{
	
}


static void D2DrawFuns_MyDrawFunction()
{
#ifdef MODULES_DAMAAGESHOW
	m_DamageShow_Draw();
#endif

#ifdef MODULES_SOULSKILLS
	m_SoulSkills_Draw();
#endif
}


void __stdcall loadCustomImages()
{
#ifdef MODULES_MULTIPAGES
	m_MultiPages_LoadImage();
#endif

#ifdef MODULES_NEWSTATSHOW
	m_NewStatShow_LoadImage();
#endif

#ifdef MODULES_DYNAMICORBS
	m_DynamicOrbs_LoadImage();
#endif
}

void __stdcall freeCustomImages()
{
#ifdef MODULES_MULTIPAGES
	m_MultiPages_FreeImage();
#endif

#ifdef MODULES_NEWSTATSHOW
	m_NewStatShow_FreeImage();
#endif

#ifdef MODULES_DYNAMICORBS
	m_DynamicOrbs_FreeImage();
#endif
}

void __stdcall MonsterLifeBarShow(DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl)
{
#ifdef	MODULES_WORLDMONSTER
	WorldMonsterInteract::WorldMonsterShow::Show(x1, y1, x2, y2, color, transTbl);
#endif
}

__declspec(naked) void D2DrawFuns_ClientDraw_ASM()
{
	__asm
	{
		call D2Client::ptDrawClient6FAD7290;
		push ebx
			call D2DrawFuns_MyDrawFunction
			pop ebx
			ret;
	}
}

__declspec(naked) void caller_loadCustomImages()
{
	__asm
	{
		pushad
		CALL loadCustomImages
		popad
		RETN
	}
}

__declspec(naked) void caller_loadCustomImages2()
{
	__asm
	{
		CALL loadCustomImages
		MOV ECX, 0x0C
		RETN
	}
}

__declspec(naked) void caller_freeCustomImages()
{
	__asm
	{
		CALL freeCustomImages
		MOV ECX, 0x0C
		RETN
	}
}

__declspec(naked) void caller_freeCustomImages2()
{
	__asm
	{
		pushad
		CALL freeCustomImages
		popad
		pop edi 
		pop esi
		RETN
	}
}

__declspec(naked) void D2DrawFuns_LifeBar_ASM()
{
	__asm
	{
		pushad
		push[esp+0x38]
		push[esp + 0x38]
		push[esp + 0x38]
		push[esp + 0x38]
		push[esp + 0x38]
		push[esp + 0x38]
		call MonsterLifeBarShow
		popad
		JMP D2Gfx::D2FillArea
	}
}
#endif // MODULES_DRAWFUNCTIONS

