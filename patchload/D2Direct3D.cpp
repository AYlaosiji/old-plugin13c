#include "pch.h"

void D2Direct3D::SetFunctions()
{
	WindowWidth = (int*)GetAddress(0x1AB44);
	WindowHeight = (int*)GetAddress(0x1AFD4);
}

void D2Direct3D::Init()
{
	Name = "D2Direct3D.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}


int* D2Direct3D::WindowWidth;
int* D2Direct3D::WindowHeight;