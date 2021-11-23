#include "pch.h"
void D2Cmp::SetFunctions()
{
	VD2FreeImage = (TD2FreeImage)GetAddressByOrdinal(10065);
}

void D2Cmp::Init()
{
	Name = "D2Cmp.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

D2Cmp::TD2FreeImage D2Cmp::VD2FreeImage;