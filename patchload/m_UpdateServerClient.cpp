#include "pch.h"

#ifdef MODULES_UPDATESERVERCLIENT
void caller_handleClientUpdate_111();
void caller_handleServerUpdate();

void m_UpdateServerClient_LoadCfg()
{

}

void m_UpdateServerClient_Install()
{

	DWORD offset = 0;
	offset = D2Client::GetAddress(0xAE896);
	Memory::SetCursor(offset);
	Memory::ChangeCallA(0x000000CF, (DWORD)caller_handleClientUpdate_111);

#ifdef D2SERVER
	offset = D2Game::GetAddress(0xCC983);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0xC1, 0X57);
	Memory::ChangeByte(0xEE, 0XE8);
	Memory::ChangeCallA(0xF88B5708, (DWORD)caller_handleServerUpdate);
#endif
}

void m_UpdateServerClient_UnInstall()
{
}

DWORD __fastcall handleClientUpdate(DataPacket* packet)
{
	switch (packet->mFunc)
	{
#ifdef MODULES_MULTIPAGES
	case UC_SELECT_STASH:	 setSelectedStashClient(packet->mParam1, packet->mParam2, packet->mParam3, (packet->mParam2 & 8) == 8); return 1;
	case UC_SHARED_GOLD:	 /*updateSharedGold(packet->mParam1);*/ return 1;
	case UC_PAGE_NAME:		 renameCurrentStash(*D2Client::ptPlayerClient, (char*)&packet->mItemID); return 1;
#endif
	case UC_DMG:
#ifdef MODULES_DAMAAGESHOW
		m_DamageShow_ShowDamageClient(packet->mParam1, packet->mParam2, packet->mParam3);
#endif
#ifdef MODULES_WORLDMONSTER
		WorldMonsterInteract::WorldMonsterShow::GetPacket(packet->mParam1, packet->mParam2, packet->mParam3);
#endif
		return 1;




#ifdef MODULES_32KLIFEFIX
	case UC_UPDATEBASESTAT:
		m_32KLifeFix_ClientChangehpmanasta(packet->mParam1, packet->mParam2, packet->mParam3);
		return 1;
#endif // MODULES_32KLIFEFIX

	default: return 0;
	}
}

void __declspec(naked) caller_handleClientUpdate_111()
{
	__asm
	{
		LEA ECX, DWORD PTR SS : [ESP + 8]
		CALL handleClientUpdate
		POP EDI
		POP ESI
		MOV ESP, EBP
		POP EBP
		RETN
	}
}

#ifdef D2SERVER

static int renameIndex = 0;
static char renameString[16];
static DWORD PageSwap;

static DWORD Param1 = 0;
static DWORD Param2 = 0;
static DWORD Param3 = 0;

int __stdcall handleServerUpdate(UnitAny* ptChar, WORD param)
{
	int type = param & 0xFF;
	DWORD arg = (param & 0xFF00) >> 8;
	switch (type)
	{
#ifdef MODULES_MULTIPAGES
	case US_SET_INDEX:				setCurrentStashIndex(ptChar, 1); return 1;
	case US_SET_MAIN_INDEX:			setCurrentStashIndex(ptChar, 2); return 1;
	case US_RESET_INDEX:			setCurrentStashIndex(ptChar, 0); return 1;
	case US_SELECT_PREVIOUS:		selectPreviousStash(ptChar); return 1;
	case US_SELECT_NEXT:			selectNextStash(ptChar); return 1;
	case US_SELECT_SELF:			/*if (active_sharedStash) toggleToSelfStash(ptChar);*/ return 1;
	case US_SELECT_SHARED:			/*if (active_sharedStash) toggleToSharedStash(ptChar); */return 1;
	case US_SELECT_PREVIOUS_INDEX:	selectPreviousIndexStash(ptChar); return 1;
	case US_SELECT_NEXT_INDEX:		selectNextIndexStash(ptChar); return 1;
	case US_SELECT_PREVIOUS2:		selectPrevious2Stash(ptChar); return 1;
	case US_SELECT_NEXT2:			selectNext2Stash(ptChar); return 1;
	case US_SELECT_PREVIOUS_INDEX2:	selectPreviousIndex2Stash(ptChar); return 1;
	case US_SELECT_NEXT_INDEX2:	selectNextIndex2Stash(ptChar); return 1;
	case US_INSERT_PAGE:			insertStash(ptChar); selectNextStash(ptChar); return 1;
	case US_DELETE_PAGE:			deleteStash(ptChar, false); return 1;

	case US_SAVE:					D2Game::D2SaveGame(ptChar->ptGame); return 1;

	case US_MAXGOLD:				/*maxGold(ptChar); */return 1;
	case US_PUTGOLD:				/*putGold(ptChar, 0); */return 1;
	case US_TAKEGOLD:				/*takeGold(ptChar, 0); */return 1;
	case US_SWAP3:					PageSwap = arg << 24; return 1;
	case US_SWAP2:					PageSwap |= arg << 16; return 1;
	case US_SWAP1:					PageSwap |= arg << 8; return 1;
	case US_SWAP0:					swapStash(ptChar, PageSwap | arg, false); PageSwap = 0; return 1;
	case US_SWAP0_TOGGLE:			swapStash(ptChar, PageSwap | arg, true); PageSwap = 0; return 1;
	case US_RENAME:
		if (renameIndex == 0)
			for (int i = 0; i < 16; i++)
				renameString[i] = 0;
		renameString[renameIndex++] = (char)arg;
		if (arg == 0)
		{
			renameIndex = 0;
			//LogMsg("Rename on Server : %s -> %s\n", ptChar->ptPlayerData->name, renameString);
			strcpy(ptChar->ptPlayerData->name, renameString);
			strcpy(ptChar->ptPlayerData->ptNetClient->name, renameString);
		}
		return 1;
	case US_PAGENAME:
		if(Param1)
		if (renameIndex == 0)
			for (int i = 0; i < 16; i++)
				renameString[i] = 0;
		renameString[renameIndex++] = (char)arg;
		if (arg == 0)
		{
			renameIndex = 0;
			renameCurrentStash(ptChar, renameString);
		}
		return 1;
#endif
	default:
		return 0;
	}
}

void __declspec(naked) caller_handleServerUpdate()
{
	__asm
	{
		PUSH ESI
		PUSH EBX
		CALL handleServerUpdate
		TEST EAX, EAX
		JNZ END_RCM
		MOV EAX, ESI
		AND EAX, 0xFF
		SHR ESI, 8
		MOV EDI, EAX
		RETN
		END_RCM :
		ADD ESP, 4
			POP EDI
			POP ESI
			XOR EAX, EAX
			POP EBX
			RETN 8
	}
}



void updateClient(UnitAny* ptChar, DWORD mFunc, DWORD p1, DWORD p2, DWORD p3)
{
	NetClient* ptNetClient;
	DataPacket packet;

	// Intialize the packet to send to client
	ZeroMemory(&packet, sizeof(DataPacket));
	packet.mType = 0x9D;
	packet.mFunc = (BYTE)mFunc;
	packet.mSize = sizeof(DataPacket);
	packet.mPlayerID = ptChar->nMemoryPool;
	packet.mParam1 = p1;
	packet.mParam2 = p2;
	packet.mParam3 = p3;

	ptNetClient = D2Common::D2GetPlayerData(ptChar)->ptNetClient;

	// Send packet to client for remove placed skills
	D2Game::D2SendPacketToClient(ptNetClient, &packet, sizeof(DataPacket));
}

void updateClient(UnitAny* ptChar, DWORD mFunc, char* msg)
{
	NetClient* ptNetClient;
	DataPacket packet;

	// Intialize the packet to send to client
	ZeroMemory(&packet, sizeof(DataPacket));
	packet.mType = 0x9D;
	packet.mFunc = (BYTE)mFunc;
	packet.mSize = sizeof(DataPacket);
	packet.mPlayerID = ptChar->nMemoryPool;
	if (msg != NULL && strlen(msg) >= 20)
		return;
	if (msg != NULL)
		strcpy((char*)&packet.mItemID, msg);

	ptNetClient = D2Common::D2GetPlayerData(ptChar)->ptNetClient;

	// Send packet to client for remove placed skills
	D2Game::D2SendPacketToClient(ptNetClient, &packet, sizeof(DataPacket));
}

void updateAllClient(GameStruct* pGame, DWORD mFunc, DWORD p1, DWORD p2, DWORD p3)
{
	if (!pGame)return;

	NetClient* pClient = pGame->ptClientLastJoined;
	while (pClient)
	{
		DataPacket packet;

		// Intialize the packet to send to client
		ZeroMemory(&packet, sizeof(DataPacket));
		packet.mType = 0x9D;
		packet.mFunc = (BYTE)mFunc;
		packet.mSize = sizeof(DataPacket);
		packet.mPlayerID = pClient->clientID;
		packet.mParam1 = p1;
		packet.mParam2 = p2;
		packet.mParam3 = p3;

		// Send packet to client for remove placed skills
		D2Game::D2SendPacketToClient(pClient, &packet, sizeof(DataPacket));
		pClient = pClient->pNext;
	}


}

#endif // D2SERVE
#endif // MODULES_UPDATESERVERCLIENT
