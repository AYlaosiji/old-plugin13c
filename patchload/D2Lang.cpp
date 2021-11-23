#include "pch.h"

void D2Lang::Init()
{
	Name = "D2Lang.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Lang::SetFunctions()
{
	D2GetStringFromIndex = (TD2GetStringFromIndex)GetAddressByOrdinal(10003);
}

D2Lang::TD2GetStringFromIndex D2Lang::D2GetStringFromIndex;