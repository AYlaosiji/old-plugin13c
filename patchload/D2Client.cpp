#include"pch.h"

__declspec(naked) void  D2ClientASM_D2GetUIToggle()
{
	__asm {
		mov eax, ecx
		call D2Client::VD2GetUIToggle
		ret
	}
}

__declspec(naked) void   D2ClientASM_D2PrintStat()
{
	__asm
	{
		PUSH ESI
		MOV ESI, DWORD PTR SS : [ESP + 0x14]
		MOV EAX, DWORD PTR SS : [ESP + 0x08]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH EDX
		PUSH ECX
		CALL D2Client::VD2PrintStat
		POP ESI
		RETN 0x10
	}
}

__declspec(naked) void   D2ClientASM_D2PlaySound()
{
	__asm
	{
		PUSH EBX
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH EDX
		MOV EBX, ECX
		CALL D2Client::VD2PlaySound
		POP EBX
		RETN 0xC
	}
}

__declspec(naked) void   D2ClientASM_D2SetColorPopup()
{
	__asm {

		PUSH EDI
		PUSH EDX
		MOV EDI, ECX
		CALL D2Client::VD2SetColorPopup
		POP EDI
		RETN
	}
}

__declspec(naked) void   D2ClientASM_D2LoadImage()
{
	__asm
	{
		PUSH EDX
		MOV EAX, ECX
		CALL D2Client::VD2LoadImage
		RETN
	}
}

__declspec(naked) void  D2ClientASM_D2SendToServer3()
{
	__asm
	{
		PUSH EBX
		PUSH ECX
		MOV BYTE PTR SS : [ESP] , CL
		MOV WORD PTR SS : [ESP + 1] , DX
		MOV EBX, 3
		LEA EDX, DWORD PTR SS : [ESP]
		PUSH EDX
		CALL D2Client::VD2SendToServer3
		POP ECX
		POP EBX
		RETN
	}
}

__declspec(naked) void  D2ClientASM_DisplaySocketSingleItem()
{
	__asm
	{
		pushad
		MOV EBX, [ESP + 0X24]
		MOV ESI, EDX
		PUSH EBX
		PUSH ESI
		MOV EBX, ECX
		CALL D2Client::VD2DisplaySocketSingleItem
		popad
		RETN 4
	}
}

void __fastcall D2Client::D2CleanStatMouseUp()
{
	*StatMouse1 = *StatMouse2 = *StatMouse3 = *StatMouse4 = 0;
}

void D2Client::Init()
{
	Name = "D2Client.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Client::SetFunctions()
{
	VD2SendPacket26ToServer = (TD2SendPacket26ToServer)GetAddress(0x7F780);
	D2GetClientUnitFromGUID = (TD2GetClientUnitFromGUID)GetAddress(0xA5B40);//6FB55B40
	D2GetPlayerXOffest = (TD2GetPlayerXOffest)GetAddress(0x3F6C0);//6FAEF6C0
	D2GetPlayerYOffest = (TD2GetPlayerXOffest)GetAddress(0x3F6D0);//6FAEF6D0
	VD2GetUIToggle = (TD2GetUIToggle)GetAddress(0x6FB6E400 - 0x6FAB0000);
	D2GetUIToggle = (TD2GetUIToggle)D2ClientASM_D2GetUIToggle;
	D2SetUIToggle = (TD2SetUIToggle)GetAddress(0x6FB72790 - 0x6FAB0000);
	VD2PrintStat = (TD2PrintStat)GetAddress(0x54E10);
	D2PrintStat = (TD2PrintStat)D2ClientASM_D2PrintStat;
	D2PrintStatsPage = (TD2PrintStatsPage)GetAddress(0xBCEA0);
	VD2LoadImage = (TD2LoadImage)GetAddress(0x2B420);
	D2LoadImage = (TD2LoadImage)D2ClientASM_D2LoadImage;
	D2LoadBuySelBtn = (TD2LoadBuySelBtn)GetAddress(0xBEAF0);
	VD2PlaySound = (TD2PlaySound)GetAddress(0x88A70);
	D2PlaySound = (TD2PlaySound)D2ClientASM_D2PlaySound;
	D2TogglePage = (TD2TogglePage)GetAddress(0xC2790);
	VD2SetColorPopup = (TD2SetColorPopup)GetAddress(0xBF5F0);
	D2SetColorPopup = (TD2SetColorPopup)D2ClientASM_D2SetColorPopup;
	D2ClientMsgTop = (TD2ClientMsgTop)GetAddress(0x6FB2D850 - 0x6FAB0000);
	D2ClientMsgBottom = (TD2ClientMsgBottom)GetAddress(0x6FB2D610 - 0x6FAB0000);
	D2GetSelectedUnit = (TD2GetSelectedUnit)GetAddress(0x6FB01A80 - 0x6FAB0000);
	VD2SendToServer3 = (TD2SendToServer3)GetAddress(0x143E0);
	D2SendToServer3 = (TD2SendToServer3)D2ClientASM_D2SendToServer3;
	D2ClickOnStashButton = (TD2ClickOnStashButton)GetAddress(0x8CD00);
	D2DisplaySocketImage=(TD2DisplaySocketImage)GetAddress(0x95140);
	VD2DisplaySocketSingleItem=(TD2DisplaySocketSingleItem)GetAddress(0x6B5A0);
	D2DisplaySocketSingleItem = (TD2DisplaySocketSingleItem)D2ClientASM_DisplaySocketSingleItem;

	ptDifficulty = (BYTE*)GetAddress(0x6FBCC390 - 0x6FAB0000);
	ptPlayerClient = (UnitAny**)GetAddress(0x6FBCBBFC - 0x6FAB0000);
	ptDrawClient6FAD7290 = (DWORD*)GetAddress(0x6FAD7290 - 0x6FAB0000);
	ptAutomapOn = (DWORD*)GetAddress(0x6FBAADA8 - 0x6FAB0000);
	ptDivisor = (long*)GetAddress(0xF16B0);
	ptOffset = (POINT*)GetAddress(0x11C1F8);
	ptAutomapPos = (POINT*)GetAddress(0x6FBCC1E8 - 0x6FAB0000);
	ptAutoMapSize = (POINT*)GetAddress(0x6FBCC230 - 0x6FAB0000);
	ptMinmapType = (DWORD*)GetAddress(0x6FBCC1B0 - 0x6FAB0000);
	ptMinimapOffset = (POINT*)GetAddress(0x6FBCC228 - 0x6FAB0000);
	ptScreenSize = (POINT*)GetAddress(0xDBC48);
	WindowWidth= (DWORD*)GetAddress(0xDBC48);
	WindowHeight = (DWORD*)GetAddress(0xDBC4C);
	ptNegWindowStartY = (DWORD*)GetAddress(0x11B9A4);
	ptWindowStartX = (DWORD*)GetAddress(0x11B9A0);
	ptMouseX = (DWORD*)GetAddress(0x11B828);
	ptMouseY = (DWORD*)GetAddress(0x11B824);
	StatMouse1 = (DWORD*)GetAddress(0x11C3DC);
	StatMouse2 = (DWORD*)GetAddress(0x11C3E0);
	StatMouse3 = (DWORD*)GetAddress(0x11C3F8);
	StatMouse4 = (DWORD*)GetAddress(0x11C3FC);
	InventoryArrangeMode= (DWORD*)GetAddress(0x11B99C);
	VideoOptionCellFileStart = (DWORD*)GetAddress(0xEA568);
	PanelOpenMode= (DWORD*)GetAddress(0x11C414);
	EscMenuOpened=(BOOL*)GetAddress(0xFADA4);
	PanelBorderImage = (CellFile**)GetAddress(0x11A77C);

	InvGrid = (Grid*)GetAddress(0x6FBBB3E0 - 0x6FAB0000);
	CubeGrid = (Grid*)GetAddress(0x6FBBB3C8 - 0x6FAB0000);
	StashGrid = (Grid*)GetAddress(0x6FBBB2D0 - 0x6FAB0000);
	PetUnitList = (PetUnit**)GetAddress(0x6FBCC4D4 - 0x6FAB0000);

}

D2Client::TD2SendPacket26ToServer D2Client::VD2SendPacket26ToServer;
D2Client::TD2GetClientUnitFromGUID D2Client::D2GetClientUnitFromGUID;
D2Client::TD2GetPlayerXOffest D2Client::D2GetPlayerXOffest;
D2Client::TD2GetPlayerYOffest D2Client::D2GetPlayerYOffest;
D2Client::TD2GetUIToggle D2Client::VD2GetUIToggle;
D2Client::TD2GetUIToggle D2Client::D2GetUIToggle;
D2Client::TD2SetUIToggle D2Client::D2SetUIToggle;
D2Client::TD2PrintStat D2Client::VD2PrintStat;
D2Client::TD2PrintStat D2Client::D2PrintStat;
D2Client::TD2PrintStatsPage D2Client::D2PrintStatsPage;
D2Client::TD2LoadBuySelBtn D2Client::D2LoadBuySelBtn;
D2Client::TD2PlaySound D2Client::VD2PlaySound;
D2Client::TD2PlaySound D2Client::D2PlaySound;
D2Client::TD2TogglePage D2Client::D2TogglePage;
D2Client::TD2SetColorPopup D2Client::VD2SetColorPopup;
D2Client::TD2SetColorPopup D2Client::D2SetColorPopup;
D2Client::TD2ClientMsgTop D2Client::D2ClientMsgTop;
D2Client::TD2ClientMsgBottom D2Client::D2ClientMsgBottom;
D2Client::TD2GetSelectedUnit D2Client::D2GetSelectedUnit;
D2Client::TD2LoadImage D2Client::VD2LoadImage;
D2Client::TD2LoadImage D2Client::D2LoadImage;
D2Client::TD2SendToServer3 D2Client::VD2SendToServer3;
D2Client::TD2SendToServer3 D2Client::D2SendToServer3;
D2Client::TD2ClickOnStashButton D2Client::D2ClickOnStashButton;
D2Client::TD2DisplaySocketImage D2Client::D2DisplaySocketImage;
D2Client::TD2DisplaySocketSingleItem D2Client::VD2DisplaySocketSingleItem;
D2Client::TD2DisplaySocketSingleItem D2Client::D2DisplaySocketSingleItem;

BYTE* D2Client::ptDifficulty;
UnitAny** D2Client::ptPlayerClient;
DWORD* D2Client::ptDrawClient6FAD7290;
DWORD* D2Client::ptAutomapOn;//小地图是否打开
long* D2Client::ptDivisor;
POINT* D2Client::ptOffset;
POINT* D2Client::ptAutomapPos;
POINT* D2Client::ptAutoMapSize;//地图大小
DWORD* D2Client::ptMinmapType;// 1小地图 0 大地图
POINT* D2Client::ptMinimapOffset;//小地图边缘地址 ，大地图为 -16*-16
POINT* D2Client::ptScreenSize;
DWORD* D2Client::WindowWidth;
DWORD* D2Client::WindowHeight;
DWORD* D2Client::ptNegWindowStartY;
DWORD* D2Client::ptWindowStartX;
DWORD* D2Client::ptMouseX;
DWORD* D2Client::ptMouseY;
DWORD* D2Client::StatMouse1;
DWORD* D2Client::StatMouse2;
DWORD* D2Client::StatMouse3;
DWORD* D2Client::StatMouse4;
DWORD* D2Client::InventoryArrangeMode;
DWORD* D2Client::VideoOptionCellFileStart;
DWORD* D2Client::PanelOpenMode;
BOOL* D2Client::EscMenuOpened;
CellFile** D2Client::PanelBorderImage;

Grid* D2Client::InvGrid;
Grid* D2Client::CubeGrid;
Grid* D2Client::StashGrid;
PetUnit** D2Client::PetUnitList;
