#include"pch.h"
#ifdef MODULES_MULTIPAGES
#define STASH_TAG 0x5453			//"ST"
#define JM_TAG 0x4D4A 				//"JM"
#define EXSTASH_TAG 0x4E4E			//"NN"//用来保存其他的物品
#define EXPET_TAG 0x4D4D			//"MM"//用来保存PET
#define CURSOR_TAG 0x4A4A 				//"JJ"

typedef int (*TchangeToSelectedStash)(UnitAny* ptChar, Stash* newStash, DWORD bOnlyItems, DWORD bIsClient);

BOOL m_isLoadExStash = FALSE;
BOOL m_isSaveExStash = FALSE;

UnitAny* firstClassicStashItem(UnitAny* ptChar)
{
	UnitAny* ptItem = D2Common::D2GetFirstInventoryItem(ptChar->ptInventory);
	while (ptItem)
	{
		if (D2Common::D2GetItemPage(D2Common::D2UnitIsItem(ptItem)) == 4)
			return ptItem;
		ptItem = D2Common::D2GetNextInventoryItem(ptItem);
	}
	return NULL;
}

DWORD endStashList(UnitAny* ptChar, Stash* ptStash)//WORKS
{
	Stash* stash = ptStash;

	while (stash)
	{
		if (stash->ptListItem || ((stash == PCPY->currentStash) && firstClassicStashItem(ptChar))) return 0;
		if (stash->isIndex || (stash->name != NULL && stash->name[0])) return 0;
		stash = stash->nextStash;
	}
	return 1;
}

//bool isInList(Stash* list, Stash* pStash)
//{
//	Stash* ptStash = list;
//	while(ptStash)
//	{
//		if (ptStash->id == pStash->id) return true;
//		ptStash = ptStash->nextStash;
//	}
//	return false;
//}


Stash* getLastStash(Stash* ptStash)//WORKS
{
	Stash* stash = ptStash;

	if (!stash) return NULL;
	while (stash->nextStash)
		stash = stash->nextStash;

	return stash;
}

Stash* newStash(DWORD id)
{
	Fog::D2Assert(id == 0xFFFFFFFF, "Too much stash", __FILE__, __LINE__);

	Stash* stash = (Stash*)malloc(sizeof(Stash));//D2AllocMem(memPool, sizeof(Stash),__FILE__,__LINE__,0);
	Fog::D2Assert(!stash, "Error on stash allocation.", __FILE__, __LINE__);
	ZeroMemory(stash, sizeof(Stash));
	stash->id = id;

	return stash;
}

Stash* addStash(UnitAny* ptChar, bool isShared)
{
	Stash* previous;
	Stash* stash;
	//	DWORD memPool = PCGame ? PCGame->memoryPool :0;
	if (isShared)
	{
		previous = getLastStash(PCPY->sharedStash);
		stash = newStash(PCPY->nbSharedPages++);
	}
	else {
		previous = getLastStash(PCPY->selfStash);
		stash = newStash(PCPY->nbSelfPages++);
	}

	stash->isShared = isShared;
	stash->previousStash = previous;
	if (previous)
		previous->nextStash = stash;
	else if (isShared)
		PCPY->sharedStash = stash;
	else
		PCPY->selfStash = stash;

	//LogMsg("AddStash: stash->id=%d\tstash->isShared=%d\tstash->previous=%08X\tnbSelf=%d\tnbShared=%d\n",
	//	stash->id, stash->isShared, stash->previousStash, PCPY->nbSelfPages, PCPY->nbSharedPages);

	return stash;
}

Stash* getStash(UnitAny* ptChar, DWORD isShared, DWORD id)//WORKS
{
	Stash* ptStash = isShared ? PCPY->sharedStash : PCPY->selfStash;

	while (ptStash)
	{
		if (ptStash->id == id) return ptStash;
		ptStash = ptStash->nextStash;
	}

	return NULL;
}

int changeToSelectedStash_10(UnitAny* ptChar, Stash* newStash, DWORD bOnlyItems, DWORD bIsClient)
{
	if (!newStash) return 0;

	//LogMsg("changeToSelectedStash ID:%d\tshared:%d\tonlyItems:%d\tclient:%d\n", newStash->id, newStash->isShared, bOnlyItems, bIsClient);

	Stash* currentStash = PCPY->currentStash;
	if (currentStash == newStash) return 0;

	Fog::D2Assert(currentStash && currentStash->ptListItem, "ERROR : currentStash isn't empty (ptListItem != NULL)", __FILE__, __LINE__);

	// Remove items from current page
	UnitAny* ptNextItem;
	UnitAny* ptItem = D2Common::D2GetFirstInventoryItem(ptChar->ptInventory);
	while (ptItem)
	{
		ptNextItem = D2Common::D2GetNextInventoryItem(ptItem);
		if (D2Common::D2GetItemPage(ptItem) == 4)
		{
			BYTE tmp = ptItem->ptItemData->ItemData2;
			ptItem = D2Common::D2InvRemoveItem(ptChar->ptInventory, ptItem);
			ptItem->ptItemData->ItemData2 = tmp;
			if (currentStash)
			{
				ptItem->ptItemData->ptNextItem = currentStash->ptListItem;
				currentStash->ptListItem = ptItem;
			}
		}
		ptItem = ptNextItem;
	}

	// add items of new stash
	ptItem = newStash->ptListItem;
	while (ptItem)
	{
		D2Common::D2InvAddItem(ptChar->ptInventory, ptItem, ptItem->pItemPath->dwPosX, ptItem->pItemPath->dwPosY, 0xC, bIsClient, 4);
		ptItem = D2Common::D2GetNextInventoryItem(ptItem);
	}
	if (bOnlyItems)
		newStash->ptListItem = PCPY->currentStash->ptListItem;
	else
		PCPY->currentStash = newStash;
	PCPY->currentStash->ptListItem = NULL;

	return 1;
}

TchangeToSelectedStash changeToSelectedStash=(TchangeToSelectedStash)changeToSelectedStash_10;

DWORD GetStatshErrorOffset(BYTE *ppp, DWORD dwMaxOffset)
{
#ifndef SKIP_ERROR
    return 0;
#else
    WORD *pwTemp = (WORD *)ppp;
    DWORD dwOffset = 1;

    while ( dwOffset < dwMaxOffset - 2 )
    {
        pwTemp = (WORD *)(ppp + dwOffset);
        if ( *pwTemp == EXSTASH_TAG || *pwTemp == EXPET_TAG || *pwTemp == CURSOR_TAG || *pwTemp == STASH_TAG )
        {
            return dwOffset;
        }
        dwOffset++;
    }

    return dwMaxOffset;
#endif
}

DWORD loadStash(UnitAny* ptChar, Stash* ptStash, BYTE data[], DWORD startSize, DWORD maxSize, DWORD* retSize)
{
	DWORD curSize = startSize;
	DWORD nbBytesRead;

	*retSize = curSize;
	if (*(WORD*)&data[curSize] != STASH_TAG)//"ST"
	{
		D2String::LogMsg("loadStash -> Bad tag of stash of character %s : %04X", ptChar->ptPlayerData->name, *(WORD*)&data[curSize]);
		return 0x7;//Unable to enter game. Bad inventory data
	}
	curSize += 2;

	// Read flags.
	int len = strlen((char*)&data[curSize]);
	if (*(WORD*)&data[curSize + len + 1] != JM_TAG)
	{
		ptStash->flags = *(DWORD*)&data[curSize];
		curSize += 4;
	}
	// Read Name
//	if (strlen((char *)&data[curSize]) > 0xF)
//		*(char *)&data[curSize+0xF] = NULL;
	if (strlen((char*)&data[curSize]))
		ptStash->name = (char*)malloc(strlen((char*)&data[curSize]));//D2AllocMem(PCGame->memoryPool, strlen((char *)&data[curSize]),__FILE__,__LINE__,0);
	if (ptStash->name)
		strcpy(ptStash->name, (char*)&data[curSize]);
	curSize += strlen((char*)&data[curSize]) + 1;
	UnitAny* pCursorItem1 = D2Common::D2GetCursorItem(ptChar->ptInventory);
	// Read inventory.
	DWORD ret = D2Game::D2LoadInventory(ptChar->ptGame, ptChar, (saveBitField*)&data[curSize], 0x60, maxSize - curSize, 0, &nbBytesRead);
	if (ret)
	{
		D2String::LogMsg("loadStash -> D2LoadInventory failed");
		nbBytesRead = GetStatshErrorOffset(&data[curSize], maxSize - curSize);
#ifdef SKIP_ERROR
        ret = 0;
#endif
	}

	//LogMsg("Stash loaded (%d : %s)\n", ptStash->id, ptStash->name);
	UnitAny* pCursorItem2 = D2Common::D2GetCursorItem(ptChar->ptInventory);
	//if (pCursorItem2 == NULL && pCursorItem1)
	//{
	//	//DWORD Z = D2Common::D2InventoryAddToContainer(ptChar->ptInventory, pCursorItem1);
	//	//DWORD A=D2Common::D2InvAddItem(ptChar->ptInventory, pCursorItem1, pCursorItem1->pItemPath->dwPosX, pCursorItem1->pItemPath->dwPosY, 0xC, 0, 0);
	//	//DWORD B = D2Common::D2InvAddItem(ptChar->ptInventory, pCursorItem1, pCursorItem1->pItemPath->dwPosX, pCursorItem1->pItemPath->dwPosY, 0xC, 1, 0);
	//	ptChar->ptInventory->inventory1 = pCursorItem1;
	//	pCursorItem1->ptItemData->ptInventory = ptChar->ptInventory;
	//	DWORD C = 1;
	//}
	
	pCursorItem2 = D2Common::D2GetCursorItem(ptChar->ptInventory);
	*retSize = curSize + nbBytesRead;
	return ret;
}

DWORD loadStashList(UnitAny* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize, bool isShared)//WORKS
{
	DWORD curStash = 0;
	Stash* newStash;

	DWORD nbStash = *(DWORD*)&data[*curSize];
	*curSize += 4;

	while (curStash < nbStash)
	{
		newStash = addStash(ptChar, isShared);
		changeToSelectedStash(ptChar, newStash, 0, false);
		DWORD ret = loadStash(ptChar, newStash, data, *curSize, 10000000, curSize);
#ifndef SKIP_ERROR
        //为了能够加载4bit存档，丢弃背包物品
		if (ret) break;
#else
		if (ret) return ret;
#endif
		curStash++;
	}

	if (!isShared && !PCPY->selfStash)
	{
		newStash = addStash(ptChar, isShared);
		PCPY->currentStash = newStash;
	}

	if (isShared && !PCPY->sharedStash)
	{
		newStash = addStash(ptChar, isShared);
		if (!PCPY->currentStash)
			PCPY->currentStash = newStash;
	}

	return 0;
}

DWORD loadExStash(UnitAny* ptChar, BYTE data[], DWORD maxSize, DWORD& curSize)
{
	DWORD nbBytesRead;

	if (*(WORD*)&data[curSize] != EXSTASH_TAG)//
	{
		return 0x7; //Unable to enter game. Bad inventory data
	}
	curSize += 2;

	// Read flags
	int len = strlen((char*)&data[curSize]);
	if (*(WORD*)&data[(curSize) + len + 1] != JM_TAG)
	{
		//LogMsg("[loadStash] Bad tag of Inventory of character %s : %04X\n", data[curSize + len + 1]);
		curSize += 4;
	}
	saveBitField* ppp = (saveBitField*)&data[curSize];
	// Read inventory

	m_isLoadExStash = TRUE;
	DWORD ret = D2Game::D2LoadInventory(ptChar->ptGame, ptChar, ppp, 0x60, maxSize - curSize, 0, &nbBytesRead);
	m_isLoadExStash = FALSE;
	if (ret)
	{
	    nbBytesRead = GetStatshErrorOffset((BYTE *)ppp, maxSize - curSize);
	}
	//if (ret)
	//	LogMsg("加载其他所有的物品失败");

	curSize = curSize + nbBytesRead;
	return 0;
}

DWORD loadExPet(UnitAny* ptChar, BYTE data[], DWORD maxSize, DWORD& curSize)
{
	DWORD nbBytesRead;

	if (*(WORD*)&data[curSize] != EXPET_TAG)//
	{
		return 0x7; //Unable to enter game. Bad inventory data
	}
	curSize += 2;



	// Read flags
	DWORD FinalSize = curSize;
	int len = strlen((char*)&data[curSize]);
	if (*(WORD*)&data[(curSize)+len + 1] != JM_TAG)
	{
		//LogMsg("[loadStash] Bad tag of Inventory of character %s : %04X\n", data[curSize + len + 1]);
		FinalSize += 4;
		curSize += 4;
		//BYTE INFO[500] = { 0 };
		//memcpy(INFO, &data[curSize], 500);
		//DWORD DASD = 1;
	}
	

	saveBitField* ppp = (saveBitField*)&data[curSize];
	// Read inventory

	UnitAny* pPet = D2Game::D2GetPlayerPet(ptChar, 7, 1, ptChar->ptGame);
	if (pPet)
	{
		DWORD ret = D2Game::D2LoadInventory(pPet->ptGame, pPet, ppp, 0x60, maxSize - curSize, 0, &nbBytesRead);
		if (ret)
    	{
		    nbBytesRead = GetStatshErrorOffset((BYTE *)ppp, maxSize - curSize);
    	}
	//if (ret)
		//	LogMsg("加载其他pet的物品失败");
	}
	else
	{
		nbBytesRead = 4;
	}

	curSize = curSize + nbBytesRead;
	return 0;

}

DWORD loadExCursor(UnitAny* ptChar, BYTE data[], DWORD maxSize, DWORD& curSize)
{
	DWORD nbBytesRead;
	if (*(WORD*)&data[curSize] != CURSOR_TAG)//
	{
		return 0x7; //Unable to enter game. Bad inventory data
	}
	curSize += 2;

	// Read flags
	DWORD FinalSize = curSize;
	int len = strlen((char*)&data[curSize]);
	if (*(WORD*)&data[(curSize)+len + 1] != JM_TAG)
	{
		//LogMsg("[loadStash] Bad tag of Inventory of character %s : %04X\n", data[curSize + len + 1]);
		FinalSize += 4;
		curSize += 4;
	}
	saveBitField* ppp = (saveBitField*)&data[curSize];
	// Read inventory

	DWORD ret = D2Game::D2LoadInventory(ptChar->ptGame, ptChar, ppp, 0x60, maxSize - curSize, 0, &nbBytesRead);
	if (ret)
	{
		nbBytesRead = GetStatshErrorOffset((BYTE *)ppp, maxSize - curSize);
	}
//if (ret)
	//	LogMsg("加载其他所有的物品失败");

	curSize = curSize + nbBytesRead;
	return 0;
}
#define DATA (*data + *curSize)
#define ADDDATA(T)		(T*)DATA;		*curSize += sizeof(T)
#define SETDATA(T,V)	*(T*)DATA = V;	*curSize += sizeof(T)

void saveStash(UnitAny* ptChar, Stash* ptStash, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	//write "ST"
	SETDATA(WORD, STASH_TAG);

	//Write flags.
	SETDATA(DWORD, ptStash->flags);

	//save name
	if (ptStash->name)
	{
		int size = strlen(ptStash->name);
		if (size > 15) size = 15;
		strncpy((char*)DATA, ptStash->name, size);
		*curSize += size;
	}
	SETDATA(char, NULL);

	//Write "JM" of inventory
	SETDATA(WORD, JM_TAG);

	//Get position of counter of items in inventory
	WORD* ptNBItem = ADDDATA(WORD);
	*ptNBItem = 0;

	//Get first item
	UnitAny* ptItem;
	if ((ptStash->id == PCPY->currentStash->id) && (ptStash->isShared == PCPY->currentStash->isShared))
		ptItem = D2Common::D2GetFirstInventoryItem(ptChar->ptInventory);
	else
		ptItem = ptStash->ptListItem;

	//Write all items
	while (ptItem)
	{
		if (D2Common::D2GetItemPage(D2Common::D2UnitIsItem(ptItem)) == 4)
		{
			int nbBytes = D2Common::D2SaveItem(D2Common::D2UnitIsItem(ptItem), (saveBitField*)DATA, *maxSize - *curSize, 1, 1, 0);
			Fog::D2Assert(!nbBytes, "!\"Character has too many items\"", __FILE__, __LINE__);
			*curSize += nbBytes;
			(*ptNBItem)++;
		}
		ptItem = D2Common::D2GetNextInventoryItem(ptItem);
	}
}

void saveExStash(UnitAny* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	//write "箱子的标志"
	SETDATA(WORD, EXSTASH_TAG);

	//Write flags.
	SETDATA(DWORD, 0x0);

	//Write "JT" of inventory
	SETDATA(WORD, JM_TAG);

	//Get position of counter of items in inventory
	WORD* ptNBItem = ADDDATA(WORD);
	*ptNBItem = 0;

	//Get first item
	UnitAny* ptItem = D2Common::D2GetFirstInventoryItem(ptChar->ptInventory);
	DWORD cccc = D2Common::D2GetItemPage(D2Common::D2UnitIsItem(ptItem));
	//Write all items
	while (ptItem)
	{
		if (D2Common::D2GetItemPage(D2Common::D2UnitIsItem(ptItem)) != 4
			&& D2Common::D2GetItemPage(D2Common::D2UnitIsItem(ptItem)) != 2
			)
		{
        	m_isSaveExStash = TRUE;
			int nbBytes = D2Common::D2SaveItem(D2Common::D2UnitIsItem(ptItem), (saveBitField*)DATA, *maxSize - *curSize, 1, 1, 0);
	        m_isSaveExStash = FALSE;
			Fog::D2Assert(!nbBytes, "!\"Character has too many items\"", __FILE__, __LINE__);
			*curSize += nbBytes;
			(*ptNBItem)++;
		}
		ptItem = D2Common::D2GetNextInventoryItem(ptItem);
	}
}

void saveExPet(UnitAny* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	//write "箱子的标志"
	SETDATA(WORD, EXPET_TAG);

	//Write flags.
	SETDATA(DWORD, 0x0);

	//Write "JT" of inventory
	SETDATA(WORD, JM_TAG);

	//Get position of counter of items in inventory
	WORD* ptNBItem = ADDDATA(WORD);
	*ptNBItem = 0;

	UnitAny* petunit = D2Game::D2GetPlayerPet(ptChar, 7, 1, ptChar->ptGame);

	if (petunit == NULL)return;

	//Get first item
	UnitAny* ptItem = D2Common::D2GetFirstInventoryItem(petunit->ptInventory);

	//Write all items
	while (ptItem)
	{
		if (D2Common::D2UnitIsItem(ptItem))
		{
			int nbBytes = D2Common::D2SaveItem(D2Common::D2UnitIsItem(ptItem), (saveBitField*)DATA, *maxSize - *curSize, 1, 1, 0);

			Fog::D2Assert(!nbBytes, "!\"Character has too many items\"", __FILE__, __LINE__);
			*curSize += nbBytes;
			(*ptNBItem)++;
		}
		ptItem = D2Common::D2GetNextInventoryItem(ptItem);
	}
}

void saveExCursor(UnitAny* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	//write "箱子的标志"
	SETDATA(WORD, CURSOR_TAG);

	//Write flags.
	SETDATA(DWORD, 0x0);

	//Write "JT" of inventory
	SETDATA(WORD, JM_TAG);

	//Get position of counter of items in inventory
	WORD* ptNBItem = ADDDATA(WORD);
	*ptNBItem = 0;

	UnitAny* pCursorItem = D2Common::D2GetCursorItem(ptChar->ptInventory);

	if (pCursorItem)
	{
		int nbBytes = D2Common::D2SaveItem(D2Common::D2UnitIsItem(pCursorItem), (saveBitField*)DATA, *maxSize - *curSize, 1, 1, 0);
		Fog::D2Assert(!nbBytes, "!\"Character has too many items\"", __FILE__, __LINE__);
		*curSize += nbBytes;
		(*ptNBItem)++;
	}
}

void saveStashList(UnitAny* ptChar, Stash* ptStash, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	DWORD curSizeNbStash = *curSize;
	*curSize += sizeof(DWORD);

	DWORD nbStash = 0;

	while (ptStash)
	{
		if (*curSize + 0x2000 > * maxSize)
		{
			BYTE* oldData = *data;
			*maxSize *= 2;
			*data = (BYTE*)Fog::D2AllocMem(ptChar->ptGame->memoryPool, *maxSize, __FILE__, __LINE__, 0);
			Fog::D2Assert(!*data, "Error : Memory allocation", __FILE__, __LINE__);
			CopyMemory(*data, oldData, *curSize);
			Fog::D2FreeMem(ptChar->ptGame->memoryPool, oldData, __FILE__, __LINE__, 0);
		}
		saveStash(ptChar, ptStash, data, maxSize, curSize);
		nbStash++;
		ptStash = endStashList(ptChar, ptStash->nextStash) ? NULL : ptStash->nextStash;
	}
	*(DWORD*)(*data + curSizeNbStash) = nbStash;
}

/////// client
void updateSelectedStashClient(UnitAny* ptChar)//WORKS
{
	Stash* newStash = PCPY->currentStash;
	if (!newStash)
		return;
	updateClient(ptChar, UC_SELECT_STASH, newStash->id, newStash->flags, PCPY->flags);
	updateClient(ptChar, UC_PAGE_NAME, newStash->name);
}

void setSelectedStashClient(DWORD stashId, DWORD stashFlags, DWORD flags, bool bOnlyItems)//WORKS
{
	UnitAny* ptChar = *D2Client::ptPlayerClient;
	Stash* newStash = getStash(ptChar, (stashFlags & 1) == 1, stashId);
	if (!newStash) do
		newStash = addStash(ptChar, (stashFlags & 1) == 1);
	while (newStash->id < stashId);
	newStash->flags = stashFlags;
	changeToSelectedStash(ptChar, newStash, bOnlyItems, 1);
	PCPY->flags = flags;
}


void selectStash(UnitAny* ptChar, Stash* newStash)
{
	if (!newStash)
		return;
	changeToSelectedStash(ptChar, newStash, 0, 0);
	updateSelectedStashClient(ptChar);
}

///// public functions
void toggleToSelfStash(UnitAny* ptChar)
{
	Stash* selStash = PCPY->selfStash;
	if (selStash && (selStash != PCPY->currentStash))
	{
		PCPY->showSharedStash = false;
		selectStash(ptChar, selStash);
	}
}

void toggleToSharedStash(UnitAny* ptChar)
{
	Stash* selStash = PCPY->sharedStash;
	if (selStash && (selStash != PCPY->currentStash))
	{
		PCPY->showSharedStash = true;
		selectStash(ptChar, selStash);
	}
}

void swapStash(UnitAny* ptChar, Stash* curStash, Stash* swpStash)
{
	if (!ptChar || !curStash || !swpStash || curStash == swpStash)
		return;
	changeToSelectedStash(ptChar, swpStash, 1, 0);
	updateClient(ptChar, UC_SELECT_STASH, swpStash->id, swpStash->flags | 8, PCPY->flags);
}

void toggleStash(UnitAny* ptChar, DWORD page)
{
	Stash* curStash = PCPY->currentStash;
	Stash* swpStash = curStash->isShared ? PCPY->selfStash : PCPY->sharedStash;
	swapStash(ptChar, curStash, swpStash);
}

void swapStash(UnitAny* ptChar, DWORD page, bool toggle)
{
	Stash* curStash = PCPY->currentStash;
	Stash* swpStash = curStash->isShared == toggle ? PCPY->selfStash : PCPY->sharedStash;
	for (DWORD i = 0; i < page; i++)
	{
		if (curStash->nextStash == NULL)
			addStash(ptChar, swpStash->isShared);
		swpStash = swpStash->nextStash;
	}
	swapStash(ptChar, curStash, swpStash);
}

void insertStash(UnitAny* ptChar)
{
	Stash* curStash = PCPY->currentStash;
	Stash* stash = addStash(ptChar, curStash->isShared);
	while (stash->previousStash != curStash)
	{
		stash->flags = stash->previousStash->flags;
		stash->name = stash->previousStash->name;
		stash->ptListItem = stash->previousStash->ptListItem;
		stash = stash->previousStash;
	}
	stash->isIndex = 0;
	stash->isMainIndex = 0;
	stash->name = NULL;
	stash->ptListItem = NULL;
}

bool deleteStash(UnitAny* ptChar, bool isClient)
{
	if (firstClassicStashItem(ptChar) != NULL)
		return false;
	//if (D2Common::D2GetFirstInventoryItem())
	Stash* stash = PCPY->currentStash;
	if (stash->nextStash == NULL)
	{
		stash->isIndex = 0;
		stash->isMainIndex = 0;
		stash->name = NULL;
		return true;
	}
	stash->flags = stash->nextStash->flags;
	stash->name = stash->nextStash->name;
	if (stash->nextStash->ptListItem != NULL)
		changeToSelectedStash(ptChar, stash->nextStash, 1, isClient);
	stash = stash->nextStash;
	while (stash->nextStash)
	{
		stash->flags = stash->nextStash->flags;
		stash->name = stash->nextStash->name;
		stash->ptListItem = stash->nextStash->ptListItem;
		stash = stash->nextStash;
	}
	stash->isIndex = 0;
	stash->isMainIndex = 0;
	stash->name = NULL;
	stash->ptListItem = NULL;
	return true;
}


void renameCurrentStash(UnitAny* ptChar, char* name)
{
	//LogMsg("renameCurrentStash : %08X, %s\n", ptChar, name);
	Stash* stash = PCPY->currentStash;
	int len = 0;
	if (name != NULL)
		len = strlen(name);
	if (stash->name)
		Fog::D2FogMemDeAlloc(stash->name, __FILE__, __LINE__, 0);
	if (len > 0)
	{
		stash->name = (char*)malloc(len);//D2FogMemAlloc(len,__FILE__,__LINE__,0);
		strcpy(stash->name, name);
	}
	else
		stash->name = NULL;
}


void setCurrentStashIndex(UnitAny* ptChar, int index)
{
	if (!PCPY->currentStash)
		return;
	PCPY->currentStash->isIndex = index >= 1;
	PCPY->currentStash->isMainIndex = index == 2;
	updateSelectedStashClient(ptChar);
}


void selectPreviousStash(UnitAny* ptChar)
{
	Stash* selStash = PCPY->currentStash->previousStash;
	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}


void selectPrevious2Stash(UnitAny* ptChar)// Select first stash
{
	Stash* selStash = PCPY->showSharedStash ? PCPY->sharedStash : PCPY->selfStash;
	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

void selectNextStash(UnitAny* ptChar)
{
	Stash* selStash = PCPY->currentStash;
	if (!selStash->isShared && (selStash->id >= maxSelfPages))	return;
	//if (selStash->isShared && (selStash->id >= maxSharedPages)) return;

	selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, PCPY->showSharedStash);

	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}


void selectNext2Stash(UnitAny* ptChar)//select last stash
{
	Stash* selStash = PCPY->showSharedStash ? PCPY->sharedStash : PCPY->selfStash;//PCPY->currentStash;
	Stash* lastStash = NULL;
	UnitAny* currentStashItem = firstClassicStashItem(ptChar);
	while (selStash)
	{
		if (selStash->ptListItem || (selStash == PCPY->currentStash) && currentStashItem) lastStash = selStash;
		selStash = selStash->nextStash;
	}
	if (!lastStash)
		lastStash = PCPY->showSharedStash ? PCPY->sharedStash : PCPY->selfStash;
	if (lastStash != PCPY->currentStash)
		selectStash(ptChar, lastStash);
}

void selectPreviousIndexStash(UnitAny* ptChar)
{
	selectPreviousStash(ptChar);
	Stash* selStash = PCPY->currentStash;
	while (selStash && !selStash->isIndex)
		selStash = selStash->previousStash;

	if (selStash == NULL)
	{
		selStash = PCPY->currentStash;
		while (selStash->previousStash && ((selStash->id + 1) % nbPagesPerIndex != 0))
			selStash = selStash->previousStash;
	}

	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

void selectPreviousIndex2Stash(UnitAny* ptChar)
{
	selectPreviousStash(ptChar);
	Stash* selStash = PCPY->currentStash;
	while (selStash && !selStash->isMainIndex)
		selStash = selStash->previousStash;

	if (selStash == NULL)
	{
		selStash = PCPY->currentStash;
		while (selStash->previousStash && ((selStash->id + 1) % nbPagesPerIndex2 != 0))
			selStash = selStash->previousStash;
	}

	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

void selectNextIndexStash(UnitAny* ptChar)
{
	selectNextStash(ptChar);
	Stash* selStash = PCPY->currentStash;
	while (selStash && !selStash->isIndex)
		selStash = selStash->nextStash;

	if (selStash == NULL)
	{
		selStash = PCPY->currentStash;
		while ((selStash->id + 1) % nbPagesPerIndex != 0)
		{
			if (!selStash->isShared && (selStash->id >= maxSelfPages))	break;
			//if (selStash->isShared && (selStash->id >= maxSharedPages)) break;
			selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, PCPY->showSharedStash);;
		}
	}
	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

void selectNextIndex2Stash(UnitAny* ptChar)
{
	selectNextStash(ptChar);
	Stash* selStash = PCPY->currentStash;
	while (selStash && !selStash->isMainIndex)
		selStash = selStash->nextStash;

	if (selStash == NULL)
	{
		selStash = PCPY->currentStash;
		while ((selStash->id + 1) % nbPagesPerIndex2 != 0)
		{
			if (!selStash->isShared && (selStash->id >= maxSelfPages))	break;
			//if (selStash->isShared && (selStash->id >= maxSharedPages)) break;
			selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, PCPY->showSharedStash);;
		}
	}
	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

//////////////////////////////////////////////////////////////////////
Stash* curStash2;
DWORD currentSawStash2;

UnitAny* __stdcall getNextItem(UnitAny* ptChar, UnitAny* ptItem)
{
	UnitAny* item = D2Common::D2GetNextInventoryItem(ptItem);
	if (item) return item;

	if (!curStash2)
	{
		switch (currentSawStash2)
		{
		case 0: curStash2 = PCPY->selfStash;
			currentSawStash2 = 1;
			break;
		case 1: curStash2 = PCPY->sharedStash;
			currentSawStash2 = 2;
			break;
		default: return NULL;//case 2:
		}
	}
	else {
		curStash2 = curStash2->nextStash;
	}
	if (curStash2)
	{
		item = curStash2->ptListItem;
		if (item) return item;
	}
	return getNextItem(ptChar, item);
}

UnitAny* __stdcall initGetNextItem(UnitAny* ptChar, UnitAny* ptItem)
{
	if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
	if (!PCPY) return NULL;

	curStash2 = NULL;
	currentSawStash2 = 0;
	if (ptItem) return ptItem;
	return getNextItem(ptChar, ptItem);
}

__declspec(naked) void caller_initGetNextItem()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 0x20]
		PUSH DWORD PTR SS : [ESP + 0xC]
		CALL initGetNextItem
		MOV EDI, EAX
		TEST EDI, EDI
		RETN
	}
}


__declspec(naked) void caller_getNextItem()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 4]
		PUSH DWORD PTR SS : [ESP + 0x10]
		CALL getNextItem
		RETN 4
	}
}


DWORD __stdcall carry1Limit(UnitAny* ptChar, UnitAny* ptItemParam, DWORD itemNum, BYTE page)
{
	if (!ptChar) return 0;
	UnitAny* ptItem = ptItemParam ? ptItemParam : D2Game::D2GameGetObject(ptChar->ptGame, UNIT_ITEM, itemNum);
	if ((page != 4) && (D2Common::D2GetItemQuality(ptItem) == 7) && ptChar)
	{
		int uniqueID = D2Common::D2GetUniqueID(ptItem);
		if ((uniqueID >= 0) && (uniqueID < (int)(*D2Common::SgptDataTables)->nbUniqueItems))
		{
			UniqueItemsBIN* uniqueItems = (*D2Common::SgptDataTables)->uniqueItems + uniqueID;
			if (uniqueItems && (uniqueItems->carry1 == 1))
			{
				ItemBIN* ptItemsBin = D2Common::D2GetItemTxt(ptItem->dwTxtFileNo);
				UnitAny* ptFirstItem = D2Common::D2GetFirstInventoryItem(ptChar->ptInventory);
				if (ptItemsBin && ptFirstItem)
					return D2Game::D2VerifIfNotCarry1(ptItem, ptItemsBin, ptFirstItem);
				//return TRUE;
			}
		}
	}
	return 0;
}

__declspec(naked) void caller_carry1Limit_111()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 0x08]//page
		PUSH 0//EDI
		PUSH DWORD PTR SS : [ESP + 0x0C]
		PUSH ESI//ptChar
		CALL carry1Limit
		TEST EAX, EAX
		JNZ	end_carry1Limit
		JMP D2Common::D2SetItemPage
		end_carry1Limit :
		ADD ESP, 0xC
			XOR EAX, EAX
			POP EDI
			POP EBX
			POP ESI
			POP EBP
			RETN 8
	}
}

__declspec(naked) void caller_carry1Limit()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 0x08]//page
		PUSH 0//EBP
		PUSH DWORD PTR SS : [ESP + 0x0C]
		PUSH DWORD PTR SS : [ESP + 0x28]//ptChar
		CALL carry1Limit
		TEST EAX, EAX
		JNZ	end_carry1Limit
		JMP D2Common::D2SetItemPage
		end_carry1Limit :
		ADD ESP, 0xC
			POP EDI
			POP ESI
			POP EBP
			XOR EAX, EAX
			POP EBX
			ADD ESP, 0x24
			RETN 8
	}
}

__declspec(naked) void caller_carry1LimitSwap_112()
{
	__asm
	{
		PUSH EAX
		PUSH DWORD PTR SS : [ESP + 0x1C]
		PUSH 0
		PUSH ESI//ptChar
		CALL carry1Limit
		TEST EAX, EAX
		JNZ	end_carry1Limit
		JMP D2Common::D2GetItemPage
		end_carry1Limit :
		ADD ESP, 8
			XOR EAX, EAX
			POP EDI
			POP EBP
			POP ESI
			POP EBX
			POP ECX
			RETN 8
	}
}

__declspec(naked) void caller_carry1LimitWhenDrop_111()
{
	__asm
	{
		PUSH 0
		PUSH 0
		PUSH DWORD PTR SS : [ESP + 0x10] //ptItem
		PUSH ESI //ptChar
		CALL carry1Limit
		TEST EAX, EAX
		JNZ	end_carry1Limit
		JMP D2Common::D2CanPutItemInInv
		end_carry1Limit :
		XOR EAX, EAX
			RETN 0x1C
}}

__declspec(naked) void caller_carry1OutOfStash_111()
{
	__asm
	{
		PUSH EDI
		CALL D2Common::D2GetItemPage
		CMP AL, 4
		JNZ continue_carry1OutOfStash
		ADD DWORD PTR SS : [ESP] , 0x17C
		RETN
		continue_carry1OutOfStash :
		MOV ESI, DWORD PTR SS : [ESP + 0x10]
			TEST ESI, ESI
			RETN
	}
}


void Install_MultiPageStash()
{
#ifdef D2SERVER
	DWORD offset;

	offset = D2Game::GetAddress(0xCF1E3);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Common::D2SetItemPage, (DWORD)caller_carry1Limit_111);


	offset = D2Game::GetAddress(0xD10C8);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Common::D2GetItemPage, (DWORD)caller_carry1LimitSwap_112);


	offset = D2Game::GetAddress(0xD7B75);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Common::D2CanPutItemInInv, (DWORD)caller_carry1LimitWhenDrop_111);


	offset = D2Game::GetAddress(0xD211B);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE8);
	Memory::ChangeCallA(0x850C2474, (DWORD)caller_carry1OutOfStash_111);
	Memory::ChangeByte(0xF6, 0x90);
#endif // D2SERVER

}
#endif