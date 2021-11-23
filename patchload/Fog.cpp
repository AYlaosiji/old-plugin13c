#include"pch.h"
void Fog::Init()
{
	Name = "Fog.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void Fog::SetFunctions()
{
	D2FogAssert = (TD2FogAssert)GetAddressByOrdinal(10024);
	D2FogMemAlloc = (TD2FogMemAlloc)GetAddressByOrdinal(10042);
	D2FogMemDeAlloc = (TD2FogMemDeAlloc)GetAddressByOrdinal(10043);
	D2AllocMem = (TD2AllocMem)GetAddressByOrdinal(10045);
	D2FreeMem = (TD2FreeMem)GetAddressByOrdinal(10046);
	D2FogGetSavePath = (TD2FogGetSavePath)GetAddressByOrdinal(10115);
	D2EncodeValue = (TD2EncodeValue)GetAddressByOrdinal(10128);
	D2DecodeValue = (TD2DecodeValue)GetAddressByOrdinal(10130);
	D2Fog10212 = (TD2Fog10212)GetAddressByOrdinal(10212);
	D2GetInstructionPointer = (TD2GetInstructionPointer)GetAddressByOrdinal(10265);

}

Fog::TD2FogAssert Fog::D2FogAssert;
Fog::TD2FogMemAlloc Fog::D2FogMemAlloc;
Fog::TD2FogMemDeAlloc Fog::D2FogMemDeAlloc;
Fog::TD2AllocMem Fog::D2AllocMem;
Fog::TD2FreeMem Fog::D2FreeMem;
Fog::TD2FogGetSavePath Fog::D2FogGetSavePath;
Fog::TD2EncodeValue Fog::D2EncodeValue;
Fog::TD2DecodeValue Fog::D2DecodeValue;
Fog::TD2Fog10212 Fog::D2Fog10212;
Fog::TD2GetInstructionPointer Fog::D2GetInstructionPointer;

void  Fog::D2Assert(BOOL pCondition, CHAR* pMessage, CHAR* file, DWORD pLineNbr)
{
	if (pCondition)
	{
		char info[MAX_PATH];
		sprintf(info, "%s\n%d\n%s", file, pLineNbr, pMessage);
		MessageBox(NULL, info, "Assert Error", MB_OK | MB_ICONEXCLAMATION);
		exit(1);
	}
 }
