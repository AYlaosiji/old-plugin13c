#include"pch.h"

void D2Launch::Init()
{
	Name = "D2Launch.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}


void D2Launch::SetFunctions()
{
}


