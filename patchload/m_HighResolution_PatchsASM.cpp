#include"pch.h"
#ifdef MODULES_HIGHRESOLUTION
__declspec(naked) void D2HD::repositionPanelsInterception()
{
	__asm
	{
		pushad
		call repositionPanels
		popad
		ret
	}
}


__declspec(naked) void D2HD::getPatchedResolutionModeInterception()
{
	__asm
	{

		sub esp, 4
		lea eax, dword ptr[esp]
		pushad
		push eax
		call getPatchedResolutionMode
		popad
		mov eax, dword ptr[eax]
		add esp, 4
		ret

	}
}

__declspec(naked) void D2HD::getModeParamsInterception107()
{
	__asm
	{

		push ecx
		lea ecx, dword ptr[esp + 18]
		sub esp, 4
		lea eax, dword ptr[esp]
		pushad
		push eax
		push ecx
		push ebx
		call getModeParams
		popad
		mov eax, dword ptr[esp]
		add esp, 4
		pop ecx
		ret
	}
}


__declspec(naked) void D2HD::getModeParamsInterception111()
{
	__asm
	{

		pushad
		push eax
		push ecx
		push edx
		call getModeParams
		popad
		ret
	}
}


__declspec(naked) void D2HD::resizeGameLogicResolutionInterception()
{
	__asm
	{

		pushad
		push esi
		call resizeGameLogicResolution
		popad
		ret
	}
}


__declspec(naked) void D2HD::resizeGameWindowResizeWidthInterception()
{
	__asm
	{

		sub esp, 4
		lea edx, [esp]
		pushad
		push edx
		call getGameWindowWidth
		popad
		add esp, 4

		cmp eax, [edx]
		ret
	}
}


__declspec(naked) void D2HD::resizeGameWindowResizeHeightInterception()
{
	__asm
	{

		sub esp, 4
		lea edx, [esp]
		pushad
		push edx
		call getGameWindowHeight
		popad
		add esp, 4

		cmp ecx, [edx]
		ret
	}
}


__declspec(naked) void D2HD::setResolutionModeEAXInterception()
{
	__asm
	{

		sub esp, 4
		lea esi, dword ptr[esp]
		pushad
		push eax
		push esi
		call setResolutionMode
		popad
		mov esi, dword ptr[esi]
		add esp, 4
		ret
	}
}


__declspec(naked) void D2HD::setResolutionModeEDIInterception()
{
	__asm
	{

		sub esp, 4
		lea esi, dword ptr[esp]
		pushad
		push edi
		push esi
		call setResolutionMode
		popad
		mov esi, dword ptr[esi]
		add esp, 4
		ret
	}
}


__declspec(naked) void D2HD::setResolutionModeFromMenuInterception()
{
	__asm
	{

		pushad
		lea ecx, dword ptr[ecx + 0x124]
		push ecx
		call setResolutionModeFromMenu
		popad
		ret
	}
}


__declspec(naked) void D2HD::isMouseOverStatsButtonInterception()
{
	__asm
	{

		sub esp, 4
		lea eax, dword ptr[esp]
		pushad
		push eax
		call isMouseOverStatsButton
		popad
		mov eax, dword ptr[esp]
		add esp, 4
		ret
	}
}


__declspec(naked) void D2HD::isMouseOverSkillButtonInterception()
{
	__asm
	{

		sub esp, 4
		lea eax, dword ptr[esp]
		pushad
		push eax
		call isMouseOverSkillButton
		popad
		mov eax, dword ptr[esp]
		add esp, 4
		ret
	}
}


__declspec(naked) void D2HD::setGDIRenderResolutionInterception()
{
	__asm
	{

		sub esp, 8
		lea esi, dword ptr[esp]
		lea edx, dword ptr[esp + 4]
		pushad
		push edx
		push esi
		push eax
		call getModeParams
		popad
		mov esi, dword ptr[esi]
		mov edx, dword ptr[edx]
		add esp, 8
		ret
	}
}


__declspec(naked) void D2HD::setGDIForegroundRenderWidthInterception()
{
	__asm
	{

		pushad
		push esi
		call setGDIForegroundRenderWidth
		popad
		ret
	}
}


__declspec(naked) void D2HD::setDirectDrawRenderResolutionInterception()
{
	__asm
	{

		sub esp, 8
		lea ecx, dword ptr[esp]
		lea edx, dword ptr[esp + 4]
		pushad
		push edx
		push ecx
		push eax
		call setDirectDrawRenderResolution
		popad
		mov ecx, dword ptr[ecx]
		mov edx, dword ptr[edx]
		add esp, 8
		ret
	}
}

__declspec(naked) void D2HD::setDirect3DRenderResolutionInterception()
{
	__asm
	{

		pushad
		push eax
		call setDirect3DRenderResolution
		popad
		ret
	}
}

__declspec(naked) void D2HD::setGlideRenderResolutionInterception()
{
	__asm
	{

		sub esp, 4
		lea ecx, dword ptr[esp]
		pushad
		push ecx
		push esi
		call setGlideRenderResolution
		popad
		mov ecx, dword ptr[ecx]
		add esp, 4

		// Original code
		xor edx, edx
		mov esi, 1
		ret
	}
}

__declspec(naked) void D2HD::setupGlideWindowSizeInterception()
{
	__asm
	{

		pushad
		push eax
		call setupGlideWindowSize
		popad
		ret
	}
}
#endif