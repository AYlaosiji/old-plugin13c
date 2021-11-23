#include"pch.h"
void D2Net::SetFunctions()
{
	D2NetSendPacketToClient = (TD2NetSendPacketToClient)GetAddressByOrdinal(10002);
	D2SendToServer = (TD2SendToServer)GetAddressByOrdinal(10024);
}

void D2Net::Init()
	{
		Name = "D2Net.dll";
		Offset = LoadDiabloLibrary();
		SetFunctions();
	}

D2Net::TD2NetSendPacketToClient D2Net::D2NetSendPacketToClient;
D2Net::TD2SendToServer D2Net::D2SendToServer;