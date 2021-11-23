#include"pch.h"

void D2Gdi::SetFunctions()
{
	ForegroundRenderWidth= (int*)GetAddress(0xCA9C);
}

void D2Gdi::Init()
{
	Name = "D2Gdi.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

int* D2Gdi::ForegroundRenderWidth;