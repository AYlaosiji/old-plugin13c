#include"pch.h"
#ifdef MODULES_MULTIPAGES
bool active_PlayerCustomData = true;
bool openSharedStashOnLoading = false;

Stash* getStashFromItem(UnitAny* ptChar, UnitAny* ptItem)
{
	Stash* curStash = PCPY->selfStash;
	UnitAny* curItem;
	while (curStash)
	{
		if (curStash == PCPY->currentStash)
			curItem = D2Common::D2GetFirstInventoryItem(ptChar->ptInventory);
		else curItem = curStash->ptListItem;
		while (curItem)
		{
			if (D2Common::D2UnitIsItem(curItem) == ptItem) return curStash;
			curItem = D2Common::D2GetNextInventoryItem(curItem);
		}
		curStash = curStash->nextStash;
	}

	curStash = PCPY->sharedStash;
	while (curStash)
	{
		if (curStash == PCPY->currentStash)
			curItem = D2Common::D2GetFirstInventoryItem(ptChar->ptInventory);
		else curItem = curStash->ptListItem;
		while (curItem)
		{
			if (D2Common::D2UnitIsItem(curItem) == ptItem) return curStash;
			curItem = D2Common::D2GetNextInventoryItem(curItem);
		}
		curStash = curStash->nextStash;
	}
	return NULL;
}


UnitAny* __fastcall updateItem(GameStruct* ptGame, DWORD type, DWORD itemNum, UnitAny* ptChar)
{
	UnitAny* ptItem = D2Game::D2GameGetObject(ptGame, type, itemNum);
	if (ptGame->isLODGame && (D2Common::D2GetItemPage(ptItem) == 4))
	{
		Stash* ptStash = getStashFromItem(ptChar, ptItem);
		if (!ptStash) return NULL;
		selectStash(ptChar, ptStash);
	}
	return ptItem;
}


void __stdcall updateClientPlayerOnLoading(UnitAny* ptChar)
{
	if (ptChar->ptGame->isLODGame)
	{
		PCPY->showSharedStash = openSharedStashOnLoading;
		selectStash(ptChar, openSharedStashOnLoading ? PCPY->sharedStash : PCPY->selfStash);
	}
	updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
}

/**************************** INIT CUSTOM DATA ****************************/

PlayerData* __fastcall init_PlayerCustomData(DWORD p1, DWORD size, LPCSTR file, DWORD line, DWORD p5)
{
	PlayerData* playerData = (PlayerData*)Fog::D2AllocMem(p1, size + sizeof(PYPlayerData), file, line, p5);
	ZeroMemory((BYTE*)playerData + 0x16C, sizeof(PYPlayerData));
	return playerData;
}

/**************************** FREE CUSTOM DATA ****************************/


void freeStash(Stash* ptStash)
{
	if (!ptStash) return;
	freeStash(ptStash->nextStash);
	free(ptStash->nextStash);//	D2FogMemDeAlloc(ptStash->nextStash,__FILE__,__LINE__,0);
	if (ptStash->name)
	{
		free(ptStash->name);//D2FogMemDeAlloc(ptStash->name,__FILE__,__LINE__,0);
		ptStash->name = NULL;
	}
	ptStash->nextStash = NULL;
}


void __fastcall free_PlayerCustomData(DWORD p1, PlayerData* playerData, LPCSTR file, DWORD line, DWORD p5)
{
	PYPlayerData* ptPYPlayerData = (PYPlayerData*)((DWORD)playerData + 0x16C);

	freeStash(ptPYPlayerData->selfStash);
	free(ptPYPlayerData->selfStash);//D2FogMemDeAlloc(ptPYPlayerData->selfStash,__FILE__,__LINE__,0);
	ptPYPlayerData->selfStash = NULL;

	freeStash(ptPYPlayerData->sharedStash);
	free(ptPYPlayerData->sharedStash);//D2FogMemDeAlloc(ptPYPlayerData->sharedStash,__FILE__,__LINE__,0);
	ptPYPlayerData->sharedStash = NULL;

	Fog::D2FreeMem(p1, playerData, file, line, p5);
}

UnitAny* __stdcall getNextItemToFree(UnitAny* ptChar, UnitAny* ptItem)
{
	UnitAny* item = D2Common::D2GetNextInventoryItem(ptItem);
	if (item) return item;

	if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
	if (!ptChar->ptPlayerData) return NULL;
	if (!PCPY) return NULL;

	Stash* curStash = PCPY->selfStash;
	while (curStash)
	{
		if (curStash->ptListItem)
		{
			item = curStash->ptListItem;
			curStash->ptListItem = NULL;
			return item;//->nUnitType == 4 ? item : NULL;
		}
		curStash = curStash->nextStash;
	}

	curStash = PCPY->sharedStash;
	while (curStash)
	{
		if (curStash->ptListItem)
		{
			item = curStash->ptListItem;
			curStash->ptListItem = NULL;
			return item->nUnitType == 4 ? item : NULL;
		}
		curStash = curStash->nextStash;
	}

	return NULL;
}


/************************ INSTALL PLAYER CUSTOM DATA ****************************/

void __fastcall updateItem_111(UnitAny* ptItem, UnitAny* ptChar)
{
	if (ptChar->ptGame->isLODGame && (D2Common::D2GetItemPage(ptItem) == 4))
	{
		Stash* ptStash = getStashFromItem(ptChar, ptItem);
		if (ptStash)
			selectStash(ptChar, ptStash);
	}
}

__declspec(naked) void caller_updateItem_111()
{
	__asm
	{
		MOV ECX, ESI
		MOV EDX, EBP
		CALL updateItem_111
		POP EAX
		MOV EDX, DWORD PTR SS : [ESP + 0x18]
		PUSH EDX
		JMP EAX
	}
}

__declspec(naked) void caller_updateItemB_111()
{
	__asm
	{
		MOV EDX, EBP
		CALL updateItem_111
		POP EAX
		MOV EDX, DWORD PTR SS : [ESP + 0x18]
		PUSH EDX
		JMP EAX
	}
}


__declspec(naked) void caller_updateClientPlayerOnLoading()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 0x14]
		CALL updateClientPlayerOnLoading
		POP ECX
		POP EDI
		POP ESI
		POP EBP
		XOR EAX, EAX
		JMP ECX
	}
}

__declspec(naked) void callerServer_getNextItemToFree_111()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 4]
		PUSH DWORD PTR SS : [ESP + 0x30]
		CALL getNextItemToFree
		RETN 4
	}
}

__declspec(naked) void callerClient_getNextItemToFree_111()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 4]
		PUSH EBX
		CALL getNextItemToFree
		RETN 4
	}
}



void Install_PlayerCustomData()
{
	// Initialize custom data.
	DWORD offset = 0;
	offset = D2Common::GetAddress(0x309BE);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)Fog::D2AllocMem, (DWORD)init_PlayerCustomData);
	
#ifdef D2SERVER
	// update item
	offset = D2Game::GetAddress(0x9BB91);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE8);
	Memory::ChangeCallA(0x52182454, (DWORD)caller_updateItem_111);

	offset = D2Game::GetAddress(0x9BBF1);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE8);
	Memory::ChangeCallA(0x52182454, (DWORD)caller_updateItemB_111);

	// Update client on loading
	offset = D2Game::GetAddress(0x4BF12);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x5F, 0xE8);
	Memory::ChangeCallA(0xC0335D5E, (DWORD)caller_updateClientPlayerOnLoading);

	// Free item in Stash (Server-side)
	offset = D2Game::GetAddress(0xE1162);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Common::D2GetNextInventoryItem, (DWORD)callerServer_getNextItemToFree_111);

#endif // D2SERVER

	// Free custom data.
	offset = D2Common::GetAddress(0x3093D);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)Fog::D2FreeMem, (DWORD)free_PlayerCustomData);


	// Free item in Stash (Client-side)
	offset = D2Client::GetAddress(0xA5C94);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Common::D2GetNextInventoryItem, (DWORD)callerClient_getNextItemToFree_111);

		// Test if it's already removed from inventory
	offset = D2Common::GetAddress(0x21B23);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x0D, 0x07);
	
}

/*================================= END OF FILE =================================*/
#endif