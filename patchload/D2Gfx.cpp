#include"pch.h"

void D2Gfx::Init()
{
	Name = "D2gfx.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Gfx::SetFunctions()
{
	D2GetResolution = (TD2GetResolution)D2Gfx::GetAddressByOrdinal(10031);
	D2DrawLine = (TD2DrawLine)D2Gfx::GetAddressByOrdinal(10010);
	D2FillArea = (TD2FillArea)D2Gfx::GetAddressByOrdinal(10014);
	D2DrawImage = (TD2DrawImage)D2Gfx::GetAddressByOrdinal(10041);
	D2DrawVerticalCropImage = (TD2DrawVerticalCropImage)D2Gfx::GetAddressByOrdinal(10074);
	D2GetRenderMode=(TD2GetRenderMode)D2Gfx::GetAddressByOrdinal(10078);

	WindowWidth = (DWORD*)GetAddress(0x1477C);
	WindowHeight= (DWORD*)GetAddress(0x14780);
}

D2Gfx::TD2GetResolution D2Gfx::D2GetResolution;
D2Gfx::TD2DrawLine D2Gfx::D2DrawLine;
D2Gfx::TD2FillArea D2Gfx::D2FillArea;
D2Gfx::TD2DrawImage D2Gfx::D2DrawImage;
D2Gfx::TD2DrawVerticalCropImage D2Gfx::D2DrawVerticalCropImage;
D2Gfx::TD2GetRenderMode D2Gfx::D2GetRenderMode;

DWORD* D2Gfx::WindowWidth;
DWORD* D2Gfx::WindowHeight;