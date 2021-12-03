#include "d2hd_license.h"
#include"pch.h"
#ifdef MODULES_HIGHRESOLUTION
__declspec(naked) void D2HD::Draw::determineVideoOptionTextInterception()
{
	__asm
	{
		//push edx
		//sub esp, 4
		//lea edx, dword ptr[esp]
		//mov ecx, dword ptr[eax + ecx * 4 + 0x540]
		//pushad
		//push ecx
		//push esi
		//push eax
		//push edx//out
		//call determineVideoOptionText
		//popad
		//mov ecx, dword ptr[edx]
		//add esp, 4
		//pop edx
		//ret

		MOV ECX, [EAX + ECX * 4 + 0x00000540]
		PUSH EAX
		PUSH EBX
		PUSH EDX
		PUSH ESI
		PUSH EDI
		//MOV assetValueA, EAX
		//MOV assetValueB, ESI
		//MOV assetValueC, ECX
		MOV EDX,ESI
		PUSH EAX
		CALL determineVideoOptionText2
		MOV ECX, EAX
		POP EDI
		POP ESI
		POP EDX
		POP EBX
		POP EAX
		RET
	}
}

__declspec(naked) void D2HD::Draw::drawControlPanel800ForegroundInterception()
{
	__asm
	{

		pushad
		call drawControlPanel800Foreground
		popad
		ret
	}
}

__declspec(naked) void D2HD::Draw::drawControlPanelBackgroundInterception()
{
	__asm
	{

		pushad
		call drawControlPanelBackground
		popad

		//Original code
		mov ecx, 18
		ret
	}
}

__declspec(naked) void D2HD::Draw::drawPanelBackgroundInterception()
{
	__asm
	{

		pushad
		call drawPanelBackground
		popad

		//Original code
		add esp, 0x128
		ret
	}
}

__declspec(naked) void D2HD::Draw::drawActiveStatsButtonInterception()
{
	__asm
	{

		pushad
		call drawActiveStatsButton
		popad
		ret
	}
}

__declspec(naked) void D2HD::Draw::drawInactiveStatsButtonInterception()
{
	__asm
	{

		pushad
		call drawInactiveStatsButton
		popad
		ret
	}
}

__declspec(naked) void D2HD::Draw::drawStatsButtonTextInterception()
{
	__asm
	{

		pushad
		call drawStatsButtonText
		popad
		ret
	}
}

__declspec(naked) void D2HD::Draw::drawActiveSkillButtonInterception()
{
	__asm
	{

		pushad
		call drawActiveSkillButton
		popad
		ret
	}
}

__declspec(naked) void D2HD::Draw::drawInactiveSkillButtonInterception()
{
	__asm
	{

		pushad
		call drawInactiveSkillButton
		popad
		ret
	}
}

__declspec(naked) void D2HD::Draw::drawSkillButtonTextInterception()
{
	__asm
	{

		pushad
		call drawSkillButtonText
		popad
		ret
	}
}

__declspec(naked) void D2HD::Draw::unloadCellFilesInterception()
{
	__asm
	{

		sub esp, 4
		lea esi, dword ptr[esp]
		pushad
		push esi
		call unloadCellFiles
		popad
		mov esi, dword ptr[esi]
		add esp, 4
		ret
	}
}
#endif