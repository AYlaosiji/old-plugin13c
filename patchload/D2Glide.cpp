#include "pch.h"

void D2Glide::SetFunctions()
{
	WindowWidth = (int*)GetAddress(0x15A68);
	WindowHeight = (int*)GetAddress(0x15B04);
	SpritesInited=(BOOL*)GetAddress(0x17B44);
}

void D2Glide::Init()
{
	Name = "D2Glide.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}


int* D2Glide::WindowWidth;
int* D2Glide::WindowHeight;
BOOL* D2Glide::SpritesInited;