#include "pch.h"

void D2DDraw::SetFunctions()
{
	WindowHeight = (int*)GetAddress(0x101D8);
}

void D2DDraw::Init()
{
	Name = "D2DDraw.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

int* D2DDraw::WindowHeight;
