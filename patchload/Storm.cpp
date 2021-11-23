#include"pch.h"
void Storm::Init()
{
	Name = "Storm.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void Storm::SetFunctions()
{
	D2StormMPQOpenFile = (TD2StormMPQOpenFile)GetAddressByOrdinal(268);
	D2Storm503 = (TD2Storm503)GetAddressByOrdinal(503);
	D2FreeWinMessage = (TD2FreeWinMessage)GetAddressByOrdinal(511);
}

Storm::TD2StormMPQOpenFile Storm::D2StormMPQOpenFile;
Storm::TD2Storm503 Storm::D2Storm503;
Storm::TD2FreeWinMessage Storm::D2FreeWinMessage;

void Storm::D2FreeMessage(sWinMessage* msg)
{
	msg->managed = 1;
	msg->unmanaged = 0;
	Storm::D2FreeWinMessage(msg);
}