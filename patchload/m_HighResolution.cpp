#include"pch.h"
#ifdef MODULES_HIGHRESOLUTION
//是否针对暗黑窗口进行修复

#define FIXIMAGE
int** Glide3x::WindowWidthPtr;
int** Glide3x::WindowHeightPtr;

BOOL isFlipD2MRControlPanel = TRUE;
BOOL isEnableD2MRBackgroundRibbon = TRUE;
D2HD::D2HDColor leftPanelBackgroundColor(255, 255, 255, 255);
D2HD::D2HDColor leftPanelBorderColor(255, 255, 255, 255);
D2HD::D2HDColor rightPanelBackgroundColor(255, 255, 255, 255);
D2HD::D2HDColor rightPanelBorderColor(255, 255, 255, 255);
BOOL isEnableD2MRPanelBorderStyle = TRUE;

#define	getXLeftGoldCoinFixBtn()			RX(-24)
#define	getLLeftGoldCoinFixBtn()			16
#define	getYLeftGoldCoinFixBtn()			RY(500)
#define	getHLeftGoldCoinFixBtn()			16
#define isOnLeftGoldCoinFixBtn(x,y) isOnRect(x, y, getXLeftGoldCoinFixBtn(), getYLeftGoldCoinFixBtn(), getLLeftGoldCoinFixBtn(), getHLeftGoldCoinFixBtn())

#define	getXRightGoldCoinFixBtn()			RX(0x2d0-193)
#define	getLRightGoldCoinFixBtn()			16
#define	getYRightGoldCoinFixBtn()			RY(-0x59+32)
#define	getHRightGoldCoinFixBtn()			16
#define isOnRightGoldCoinFixBtn(x,y) isOnRect(x, y, getXRightGoldCoinFixBtn(), getYRightGoldCoinFixBtn(), getLRightGoldCoinFixBtn(), getHRightGoldCoinFixBtn())

#define	getXInvCloseFixBtn()			RX(0x3db - 193)
#define	getLInvCloseFixBtn()			32
#define	getYInvCloseFixBtn()			RY(-0x63+32)
#define	getHInvCloseFixBtn()			32
#define isOnInvCloseFixBtn(x,y) isOnRect(x, y, getXInvCloseFixBtn(), getYInvCloseFixBtn(), getLInvCloseFixBtn(), getHInvCloseFixBtn())

#define	getXCubeCloseFixBtn()			RX(288)
#define	getLCubeCloseFixBtn()			32
#define	getYCubeCloseFixBtn()			RY(5)
#define	getHCubeCloseFixBtn()			32
#define isOnCubeCloseFixBtn(x,y) isOnRect(x, y, getXCubeCloseFixBtn(), getYCubeCloseFixBtn(), getLCubeCloseFixBtn(), getHCubeCloseFixBtn())

#define	getXStashCloseFixBtn()			RX(-193)
#define	getLStashCloseFixBtn()			32
#define	getYStashCloseFixBtn()			RY(488)
#define	getHStashCloseFixBtn()			32
#define isOnStashCloseFixBtn(x,y) isOnRect(x, y, getXStashCloseFixBtn(), getYStashCloseFixBtn(), getLStashCloseFixBtn(), getHStashCloseFixBtn())

#define	getXTransmuteCloseFixBtn()			RX(178)
#define	getLTransmuteCloseFixBtn()			32
#define	getYTransmuteCloseFixBtn()			RY(8)
#define	getHTransmuteCloseFixBtn()			32
#define isOnTransmuteCloseFixBtn(x,y) isOnRect(x, y, getXTransmuteCloseFixBtn(), getYTransmuteCloseFixBtn(), getLTransmuteCloseFixBtn(), getHTransmuteCloseFixBtn())

//char6 fix
void __stdcall m_NewStatShow_Char6Fix(sDrawImageInfo* pData, DWORD* nXpos, DWORD* nYpos, DWORD nGamma, DWORD nDrawType, BYTE pPalette[256][256])
{
	if (pData->dwCellNo == 4)
	{
		*nYpos -= 130;
	}
	else if (pData->dwCellNo == 5)
	{
		*nYpos -= 130;
	}
	else if (pData->dwCellNo == 6)
	{
		*nYpos -= 50;
		pData->dwCellNo = 8;
		D2Gfx::D2DrawImage(pData, *nXpos, *nYpos + 256, -1, 5, 0);//256
		pData->dwCellNo = 6;
	}
	else if (pData->dwCellNo == 7)
	{
		*nYpos -=50;
		pData->dwCellNo = 9;
		D2Gfx::D2DrawImage(pData, *nXpos, *nYpos + 256, -1, 5, 0);//256
		pData->dwCellNo = 7;
	}
}
__declspec(naked) void caller_Char6Fix()
{
	__asm
	{
		PUSHAD
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		push dword ptr ss : [esp + 0x38]
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		call m_NewStatShow_Char6Fix
		POPAD
		JMP D2Gfx::D2DrawImage
	}
}

BOOL __fastcall m_NewStatShow_Leftgoldcoin(DWORD x, DWORD y)
{
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnLeftGoldCoinFixBtn(mx, my))
		return TRUE;
	return FALSE;
}
__declspec(naked) void caller_Leftgoldcoin()
{
	__asm
	{
		push edi
		mov ecx, eax
		mov edx, esi
		call m_NewStatShow_Leftgoldcoin
		pop edi
		retn
	}
}

BOOL __fastcall m_NewStatShow_Rightgoldcoin(DWORD x, DWORD y)
{
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnRightGoldCoinFixBtn(mx, my))
		return TRUE;
	return FALSE;
}
__declspec(naked) void caller_Rightgoldcoin()
{
	__asm
	{
		push ebx
		mov ecx, esi
		mov edx, edi
		call m_NewStatShow_Rightgoldcoin
		pop ebx
		pop esi
		retn
	}
}
void __stdcall m_NewStatShow_goldcoinimg(sDrawImageInfo* pData, LONG* nXpos, LONG* nYpos, DWORD nGamma, DWORD nDrawType, BYTE pPalette[256][256])
{
	if (*nXpos > D2Client::ptScreenSize->x / 2)
	{
		*nXpos = getXRightGoldCoinFixBtn();
		*nYpos = getYRightGoldCoinFixBtn();
	}
	else
	{
		*nXpos = getXLeftGoldCoinFixBtn();
		*nYpos = getYLeftGoldCoinFixBtn();
	}
}
__declspec(naked) void caller_goldcoinimg()
{
	__asm
	{
		PUSHAD
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		push dword ptr ss : [esp + 0x38]
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		call m_NewStatShow_goldcoinimg
		POPAD
		JMP D2Gfx::D2DrawImage
	}
}
DWORD __fastcall m_NewStatShow_goldcointext(LONG x, LONG* y)//返回x坐标
{
	if (x > D2Client::ptScreenSize->x / 2)
	{
		*y = getYRightGoldCoinFixBtn();
		return getXRightGoldCoinFixBtn() + 32;
	}
	else
	{
		*y = getYLeftGoldCoinFixBtn();
		return getXLeftGoldCoinFixBtn() + 32;
	}
	return x;
}
__declspec(naked) void caller_goldcointext()
{
	__asm
	{
		PUSH ECX
		PUSH EDI
		PUSH ESI
		PUSH EAX
		MOV ECX, EDX
		LEA EDX, [ESP + 0X4 + 0X10]
		CALL m_NewStatShow_goldcointext
		MOV EDX, EAX
		POP EAX
		POP ESI
		POP EDI
		POP ECX
		jmp D2Win::D2PrintString;
	}
}

BOOL __fastcall m_NewStatShow_invclose(DWORD x, DWORD y)
{
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnInvCloseFixBtn(mx, my))
		return TRUE;
	return FALSE;
}
__declspec(naked) void caller_invclose()
{
	__asm
	{
		PUSH ESI
		push ebx
		call m_NewStatShow_invclose
		pop ebx
		pop esi
		retn
	}
}
void __stdcall m_NewStatShow_invcloseimg(sDrawImageInfo* pData, DWORD* nXpos, DWORD* nYpos, DWORD nGamma, DWORD nDrawType, BYTE pPalette[256][256])
{
	*nXpos = getXInvCloseFixBtn();
	*nYpos = getYInvCloseFixBtn();
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnInvCloseFixBtn(mx, my))
	{
		D2Win::D2PrintPopup(L"关闭", getXInvCloseFixBtn(), getYInvCloseFixBtn() - getHInvCloseFixBtn(), 0, 0);
	}
}
__declspec(naked) void caller_Invcloseimg()
{
	__asm
	{
		PUSHAD
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		push dword ptr ss : [esp + 0x38]
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		call m_NewStatShow_invcloseimg
		POPAD
		JMP D2Gfx::D2DrawImage
	}
}

BOOL __fastcall m_NewStatShow_Cubeclose(DWORD x, DWORD y)
{
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnCubeCloseFixBtn(mx, my))
		return TRUE;
	return FALSE;
}
__declspec(naked) void caller_Cubeclose()
{
	__asm
	{
		PUSH ESI
		push ebx
		call m_NewStatShow_Cubeclose
		pop ebx
		pop esi
		retn
	}
}
void __stdcall m_NewStatShow_Cubecloseimg(sDrawImageInfo* pData, DWORD* nXpos, DWORD* nYpos, DWORD nGamma, DWORD nDrawType, BYTE pPalette[256][256])
{
	*nXpos = getXCubeCloseFixBtn();
	*nYpos = getYCubeCloseFixBtn();
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnCubeCloseFixBtn(mx, my))
	{
		D2Win::D2PrintPopup(L"关闭", getXCubeCloseFixBtn(), getYCubeCloseFixBtn() - getHCubeCloseFixBtn(), 0, 0);
	}
}
__declspec(naked) void caller_Cubecloseimg()
{
	__asm
	{
		PUSHAD
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		push dword ptr ss : [esp + 0x38]
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		call m_NewStatShow_Cubecloseimg
		POPAD
		JMP D2Gfx::D2DrawImage
	}
}

BOOL __fastcall m_NewStatShow_Stashclose(DWORD x, DWORD y)
{
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnStashCloseFixBtn(mx, my))
		return TRUE;
	return FALSE;
}
__declspec(naked) void caller_Stashclose()
{
	__asm
	{
		PUSH ESI
		push ebx
		call m_NewStatShow_Stashclose
		pop ebx
		pop esi
		retn
	}
}
void __stdcall m_NewStatShow_Stashcloseimg(sDrawImageInfo* pData, DWORD* nXpos, DWORD* nYpos, DWORD nGamma, DWORD nDrawType, BYTE pPalette[256][256])
{
	*nXpos = getXStashCloseFixBtn();
	*nYpos = getYStashCloseFixBtn();
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnStashCloseFixBtn(mx, my))
	{
		D2Win::D2PrintPopup(L"关闭", getXStashCloseFixBtn(), getYStashCloseFixBtn() - getHStashCloseFixBtn(), 0, 0);
	}
}
__declspec(naked) void caller_Stashcloseimg()
{
	__asm
	{
		PUSHAD
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		push dword ptr ss : [esp + 0x38]
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		call m_NewStatShow_Stashcloseimg
		POPAD
		JMP D2Gfx::D2DrawImage
	}
}

BOOL __fastcall m_NewStatShow_Transmuteclose(DWORD x, DWORD y)
{
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnTransmuteCloseFixBtn(mx, my))
		return TRUE;
	return FALSE;
}
__declspec(naked) void caller_Transmuteclose()
{
	__asm
	{
		PUSH ESI
		push ebx
		call m_NewStatShow_Transmuteclose
		pop ebx
		pop esi
		retn
	}
}
void __stdcall m_NewStatShow_Transmutecloseimg(sDrawImageInfo* pData, DWORD* nXpos, DWORD* nYpos, DWORD nGamma, DWORD nDrawType, BYTE pPalette[256][256])
{
	*nXpos = getXTransmuteCloseFixBtn();
	*nYpos = getYTransmuteCloseFixBtn();
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;
	if (isOnTransmuteCloseFixBtn(mx, my))
	{
		D2Win::D2PrintPopup(L"开始转换", getXTransmuteCloseFixBtn(), getYTransmuteCloseFixBtn() - getHTransmuteCloseFixBtn(), 0, 0);
	}
}
__declspec(naked) void caller_Transmutecloseimg()
{
	__asm
	{
		PUSHAD
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		push dword ptr ss : [esp + 0x38]
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		call m_NewStatShow_Transmutecloseimg
		POPAD
		JMP D2Gfx::D2DrawImage
	}
}

//TradeTransmute fix
void __stdcall m_NewStatShow_TradeStashFix(sDrawImageInfo* pData, int* nXpos, int* nYpos, DWORD nGamma, DWORD nDrawType, BYTE pPalette[256][256])
{
	int fixy = 95 - 65 + 10;
	int fixy2 = 15 - 65 + 10;
	int fixx = 195;
	if (pData->dwCellNo == 0)
	{
		*nYpos -= fixy;
		*nXpos -= fixx;
	}
	else if (pData->dwCellNo == 1)
	{
		*nYpos -= fixy;
		*nXpos -= fixx;
	}
	else if (pData->dwCellNo == 2)
	{
		*nYpos -= fixy2;
		*nXpos -= fixx;
	}
	else if (pData->dwCellNo == 3)
	{
		*nYpos -= fixy2;
		*nXpos -= fixx;
	}
}

__declspec(naked) void caller_TradeStashFix()
{
	__asm
	{
		PUSHAD
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		push dword ptr ss : [esp + 0x38]
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		call m_NewStatShow_TradeStashFix
		POPAD
		JMP D2Gfx::D2DrawImage
	}
}

void __stdcall m_NewStatShow_supertransmogrifierFix(sDrawImageInfo* pData, int* nXpos, int* nYpos, DWORD nGamma, DWORD nDrawType, BYTE pPalette[256][256])
{
	int fixy = 95 - 65 + 10;
	int fixy2 = 15 - 65 + 10;
	int fixx = 195;
	if (pData->dwCellNo == 0)
	{
		*nYpos -= fixy;
		*nXpos -= fixx;
	}
	else if (pData->dwCellNo == 1)
	{
		*nYpos -= fixy;
		*nXpos -= fixx;
	}
	else if (pData->dwCellNo == 2)
	{
		*nYpos -= fixy2;
		*nXpos -= fixx;
	}
	else if (pData->dwCellNo == 3)
	{
		*nYpos -= fixy2;
		*nXpos -= fixx;
	}
}

__declspec(naked) void caller_supertransmogrifierFix()
{
	__asm
	{
		PUSHAD
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		push dword ptr ss : [esp + 0x38]
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		lea eax, dword ptr ss : [esp + 0x38]
		push eax
		push dword ptr ss : [esp + 0x38]
		call m_NewStatShow_supertransmogrifierFix
		POPAD
		JMP D2Gfx::D2DrawImage
	}
}

void m_HighResolution_LoadCfg()
{

}

void m_HighResolution_Install()
{
	DWORD offset;
	DWORD offset2;

	// Fix panel positioning
	offset = D2Client::GetAddress(0xC39F6);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x83, 0xE8);//1
	Memory::ChangeCallA(0x167502F8, (DWORD)D2HD::repositionPanelsInterception);//4
	Memory::ChangeByte(0xC7, 0xEB);//1
	Memory::ChangeByte(0x05, 0x20);//1 39-7=32

	// Fix border panel click detection issue for HD mode.
	// Block click for left panel
	offset = D2Client::GetAddress(0xBCB31);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	// Block click for right panel
	offset = D2Client::GetAddress(0x8F881);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	// Resize Game Logic Resolution and FOV
	offset = D2Client::GetAddress(0x10DFD);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE8);//1
	Memory::ChangeCallA(0x00E883C6, (DWORD)D2HD::resizeGameLogicResolutionInterception);//4
	Memory::ChangeByte(0x74, 0xEB);//1
	Memory::ChangeByte(0x25, 69);//1 76-7=69

	// Read From D2HD.ini Instead of Registry
	//省略

	//Interpret Config Resolution Mode and Remove Limit on Config Resolution Mode
	offset = D2Client::GetAddress(0x4446A);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x48, 0xE8);//1
	Memory::ChangeCallA(0x02BE0575, (DWORD)D2HD::setResolutionModeEAXInterception);//4
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1

	offset = D2Client::GetAddress(0x65E5E);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x48, 0xE8);//1
	Memory::ChangeCallA(0x02BE0575, (DWORD)D2HD::setResolutionModeEAXInterception);//4
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1

	offset = D2Client::GetAddress(0x6628E);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x4F, 0xE8);//1
	Memory::ChangeCallA(0x02BE0575, (DWORD)D2HD::setResolutionModeEDIInterception);//4
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1

	offset = D2Client::GetAddress(0xAF968);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x48, 0xE8);//1
	Memory::ChangeCallA(0x02BE0575, (DWORD)D2HD::setResolutionModeEAXInterception);//4
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1

// Write to D2HD.ini Instead of Registry
	//不需要

	// Increase Number of Resolutions in Video Options
	offset = D2Client::GetAddress(0x662C4);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x4F, 0xE8);//1
	Memory::ChangeCallA(0x02BE0575, (DWORD)D2HD::setResolutionModeEDIInterception);//4
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1

	// Modify Resolution Display in Options
	offset = D2Client::GetAddress(0x653FF);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE8);//1
	Memory::ChangeCallA(0x0540888C, (DWORD)D2HD::Draw::determineVideoOptionTextInterception);//4
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1

	 // Modify the value of the registry resolution ID
	offset = D2Client::GetAddress(0x651E0);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0xC7, 0x90);//1
	Memory::ChangeByte(0x81, 0xE8);//1
	Memory::ChangeCallA(0x00000124, (DWORD)D2HD::setResolutionModeFromMenuInterception);//4
	Memory::ChangeDword(0x00000000, 0x90909090);//4

	 // Resize Game Window; D2GFX.Ordinal10025, D2GFX.Ordinal10064
	//1.13c NO PATCH 1
	offset = D2Gfx::GetAddress(0x7FD0);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE9);//1
	Memory::ChangeCallA(0x83042444, (DWORD)D2HD::getModeParams);//4
	Memory::ChangeByte(0xF8, 0x90);//1
	Memory::ChangeByte(0x03, 0x90);//1

	// Correct Resizing of Window from any resolution to a smaller one.
	offset = D2Gfx::GetAddress(0x83F0);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x3D, 0xE8);//1
	Memory::ChangeCallA(0x00000320, (DWORD)D2HD::resizeGameWindowResizeWidthInterception);//4

	offset = D2Gfx::GetAddress(0x8403);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x81, 0x90);//1
	Memory::ChangeByte(0xF9, 0xE8);//1
	Memory::ChangeCallA(0x00000258, (DWORD)D2HD::resizeGameWindowResizeHeightInterception);//4

	if (LoadD2::IsD2GdiLoad)
	{
		offset = D2Gdi::GetAddress(0x6D34);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x85, 0xE8);//1
		Memory::ChangeCallA(0x831D74C0, (DWORD)D2HD::setGDIRenderResolutionInterception);//4
		Memory::ChangeByte(0xF8, 0xEB);//1
		Memory::ChangeByte(0x03, 36);//1 43-7=36

		offset = D2Gdi::GetAddress(0x7049);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x74, 0xE8);//1
		Memory::ChangeCallA(0x03FE831F, (DWORD)D2HD::setGDIForegroundRenderWidthInterception);//4
		Memory::ChangeByte(0x74, 0xEB);//1
		Memory::ChangeByte(0x0D, 26);//1 33-7=36

		offset = D2Gdi::GetAddress(0x706B);
		offset2 = D2Gdi::GetAddress(0x6F87CA9C - 0x6f870000);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xC7, 0x90);//1
		Memory::ChangeByte(0x05, 0x90);//1
		Memory::ChangeDword(offset2, 0x90909090);
		Memory::ChangeDword(0x280, 0x90909090);
	}
	offset = D2DDraw::GetAddress(0x85C2);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x3B, 0xE8);//1
	Memory::ChangeCallA(0xB91175C6, (DWORD)D2HD::setDirectDrawRenderResolutionInterception);//4
	Memory::ChangeByte(0x80, 0xEB);//1
	Memory::ChangeByte(0x02, 36);//43-7=36
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1

	offset = D2DDraw::GetAddress(0x85F9);
	offset2 = D2DDraw::GetAddress(0x6F8CEB70 - 0x6f8c0000);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0x90);//1
	Memory::ChangeByte(0x0C, 0x90);//1
	Memory::ChangeByte(0x85, 0x90);//1
	Memory::ChangeDword(offset2, 0x90909090);//4


	offset = D2Direct3D::GetAddress(0xB9A4);
	offset2 = D2Direct3D::GetAddress(0x1AB44);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x75, 0x90);//1
	Memory::ChangeByte(0x16, 0x90);//1
	Memory::ChangeByte(0xc7, 0x90);//1
	Memory::ChangeByte(0x05, 0xe8);//1
	Memory::ChangeCallA(offset2, (DWORD)D2HD::setDirect3DRenderResolutionInterception);//4
	Memory::ChangeByte(0x80, 0xEB);//1
	Memory::ChangeByte(0x02, 49);//1 59-10=49
	Memory::ChangeByte(0x00, 0x90);//1
	Memory::ChangeByte(0x00, 0x90);//1

	if (LoadD2::IsD2GlideLoad)
	{
		offset = D2Glide::GetAddress(0xDCC6);
		offset2 = D2Glide::GetAddress(0x6F867B00 - 0x6F850000);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x3B, 0xE8);//1
		Memory::ChangeCallA(0x8B2175F3, (DWORD)D2HD::setGlideRenderResolutionInterception);//4
		Memory::ChangeByte(0x15, 0x90);//1
		Memory::ChangeDword(offset2, 0x90909090);//4
		Memory::ChangeByte(0xB9, 0xEB);//1
		Memory::ChangeByte(0x07, 84);//1	96-12=84
		Memory::ChangeByte(0x00, 0x90);//1
		Memory::ChangeByte(0x00, 0x90);//1
		Memory::ChangeByte(0x00, 0x90);//1
	}

	//开始第二部分
	// Draw background and Redraw UI Panel Border Fix
	offset = D2Client::GetAddress(0x271C0);
	Memory::SetCursor(offset);
	Memory::ChangeDword(0x5748ec83, 0x90909090);//4
	Memory::ChangeByte(0x33, 0x90);//1
	Memory::ChangeByte(0xc0, 0x90);//1

	offset = D2Client::GetAddress(0x271CB);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8D, 0xE9);//1
	Memory::ChangeDword(0xF304247C, 0xBB);//4 190
	Memory::ChangeByte(0xAB, 0x90);//1

	offset = D2Client::GetAddress(0x270D0);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xC3);//1
	Memory::ChangeByte(0x15, 0x90);//1

	offset = D2Client::GetAddress(0xBF361);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x81, 0xE9);//1
	Memory::ChangeCallA(0x000128C4, (DWORD)D2HD::Draw::drawPanelBackgroundInterception);//4
	Memory::ChangeByte(0x00, 0x90);//1

	offset = D2Client::GetAddress(0x27297);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0xB9, 0xE8);//1
	Memory::ChangeCallA(0x12, (DWORD)D2HD::Draw::drawControlPanelBackgroundInterception);//4

	offset = D2Client::GetAddress(0x26E1C);
	offset2 = D2Client::GetAddress(0x6FBCA77C - 0x6FAB0000);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0x90);//1
	Memory::ChangeByte(0x35, 0xE8);//1
	Memory::ChangeCallA(offset2, (DWORD)D2HD::Draw::unloadCellFilesInterception);//4



	//开始第3部分
	offset = D2Client::GetAddress(0x506B0);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x506CA);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50760);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x5077E);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50811);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x5082F);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50B71);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50B8F);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x272A3);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50104);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50448);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x504ED);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50564);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x505C9);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50024);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50208);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x502A6);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x5031D);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	offset = D2Client::GetAddress(0x50381);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Gfx::D2GetResolution, (DWORD)D2HD::getPatchedResolutionModeInterception);

	//第四部分
	offset = D2Common::GetAddress(0x13340);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0Xe9);
	Memory::ChangeCallA(0x8B082444, (DWORD)D2HD::Inventory::getBeltPos);//4
	Memory::ChangeByte(0x4C, 0x90);//1
	Memory::ChangeByte(0x24, 0x90);//1
	Memory::ChangeByte(0x04, 0x90);//1

	offset = D2Common::GetAddress(0x132A0);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0Xe9);
	Memory::ChangeCallA(0x8B042444, (DWORD)D2HD::Inventory::getBeltsTxtRecord);//4

	offset = D2Common::GetAddress(0x82030);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0Xe9);
	Memory::ChangeCallA(0x8B082444, (DWORD)D2HD::Inventory::getInventorySize);//4
	Memory::ChangeByte(0x4C, 0x90);//1
	Memory::ChangeByte(0x24, 0x90);//1
	Memory::ChangeByte(0x04, 0x90);//1

	offset = D2Common::GetAddress(0x81FB0);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0Xe9);
	Memory::ChangeCallA(0x8B082444, (DWORD)D2HD::Inventory::getInventoryGrid);//4
	Memory::ChangeByte(0x4C, 0x90);//1
	Memory::ChangeByte(0x24, 0x90);//1
	Memory::ChangeByte(0x04, 0x90);//1

	offset = D2Common::GetAddress(0x81F20);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0Xe9);
	Memory::ChangeCallA(0x8B082444, (DWORD)D2HD::Inventory::getInventoryField);//4
	Memory::ChangeByte(0x4C, 0x90);//1
	Memory::ChangeByte(0x24, 0x90);//1
	Memory::ChangeByte(0x04, 0x90);//1

	//第五部分
	//如果没有glide3x会先加载
	if (LoadD2::IsD2GlideLoad)
	{
		Glide3x::Init();
		Glide3x::HookLibrary();

		offset = Glide3x::GetAddress(0xCA97);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x83, 0Xe8);//1
		Memory::ChangeCallA(0x1B7F0EF8, (DWORD)D2HD::setupGlideWindowSizeInterception);//4
		Memory::ChangeByte(0x0F, 0Xe9);//1
		Memory::ChangeDword(0x0000A284, 0x106);//4
		Memory::ChangeByte(0x00, 0X90);//1

		offset = Glide3x::GetAddress(0xC061);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8b, 0Xeb);//1
		Memory::ChangeByte(0x10, 0X09);//1

	}
#ifdef FIXIMAGE

	//第六部分，修正我们的装备栏
	{
		offset = D2Client::GetAddress(0x99B6C);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_Char6Fix);

		offset = D2Client::GetAddress(0x99BA7);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_Char6Fix);

		offset = D2Client::GetAddress(0x99BE2);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_Char6Fix);

		offset = D2Client::GetAddress(0x99C1C);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_Char6Fix);

		//取消三个关闭按钮的popup,前两个取消为Inv与Stash 第三个为Cube的关闭
		offset = D2Client::GetAddress(0x9386d);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8b, 0x33);
		Memory::ChangeByte(0xc8, 0xC9);
		offset = D2Client::GetAddress(0x9390b);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8b, 0x33);
		Memory::ChangeByte(0xc8, 0xC9);
		//取消cube的popUP
		offset = D2Client::GetAddress(0x99B22);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8b, 0x33);
		Memory::ChangeByte(0xcE, 0xC9);

		//取消提钱的popup

		offset = D2Client::GetAddress(0x8d24d);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8b, 0x33);
		Memory::ChangeByte(0xc8, 0xC9);

		//修正提取金币
		offset = D2Client::GetAddress(0x8b6b0);
		offset2 = D2Client::GetAddress(0x6FBC9854 - 0x6FAB0000);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8b, 0x90);
		Memory::ChangeByte(0x0d, 0xe9);
		Memory::ChangeCallA(offset2, (DWORD)caller_Leftgoldcoin);

		offset = D2Client::GetAddress(0x8D3E5);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xA1, 0xE9);
		Memory::ChangeCallA((DWORD)D2Client::ptNegWindowStartY, (DWORD)caller_Rightgoldcoin);

		offset = D2Client::GetAddress(0x6FB3D2E0 - 0x6FAB0000);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_goldcoinimg);

		offset = D2Client::GetAddress(0x6FB3D267 - 0x6FAB0000);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Win::D2PrintString, (DWORD)caller_goldcointext);

		//修正关闭按钮
		offset = D2Client::GetAddress(0x8BD90);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xA1, 0xE9);
		Memory::ChangeCallA((DWORD)D2Client::ptScreenSize, (DWORD)caller_invclose);

		offset = D2Client::GetAddress(0x6FB4A721 - 0x6FAB0000);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_Invcloseimg);
	}

	//第七部分修正TradeStash
	{
		offset = D2Client::GetAddress(0x99921 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_TradeStashFix);

		offset = D2Client::GetAddress(0x99954 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_TradeStashFix);

		offset = D2Client::GetAddress(0x9997f + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_TradeStashFix);

		offset = D2Client::GetAddress(0x999ad + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_TradeStashFix);
	}

	//第七部分修正超级转换盒
	{
		offset = D2Client::GetAddress(0x99554 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_supertransmogrifierFix);

		offset = D2Client::GetAddress(0x99587 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_supertransmogrifierFix);

		offset = D2Client::GetAddress(0x995B2 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_supertransmogrifierFix);

		offset = D2Client::GetAddress(0x995E0 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_supertransmogrifierFix);
	}

	{
		//修正赫拉迪克方块的关闭按钮的地方
		offset = D2Client::GetAddress(0x8B650);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8B, 0x90);
		Memory::ChangeByte(0x0D, 0xE9);
		Memory::ChangeCallA((DWORD)D2Client::ptWindowStartX, (DWORD)caller_Cubeclose);

		offset = D2Client::GetAddress(0x99652 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_Cubecloseimg);
	}

	{
		//修正仓库关闭按钮的位置
		offset = D2Client::GetAddress(0x8CD00);
		offset2 = D2Client::GetAddress(0x6FBC9854 - 0x6FAB0000);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8B, 0x90);
		Memory::ChangeByte(0x15, 0xE9);
		Memory::ChangeCallA(offset2, (DWORD)caller_Stashclose);

		offset = D2Client::GetAddress(0x99A99 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_Stashcloseimg);
	}

	{
		//修正点击赫拉迪克转换的位置
		offset = D2Client::GetAddress(0x8B600);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x8B, 0x90);
		Memory::ChangeByte(0x0D, 0xE9);
		Memory::ChangeCallA((DWORD)D2Client::ptWindowStartX, (DWORD)caller_Transmuteclose);

		offset = D2Client::GetAddress(0x99694 + 1);
		Memory::SetCursor(offset);
		Memory::ChangeCallB((DWORD)D2Gfx::D2DrawImage, (DWORD)caller_Transmutecloseimg);
	}
#endif // FIXIMAGE
}

void m_HighResolution_UnInstall()
{

}

#endif