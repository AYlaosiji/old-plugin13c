#include"pch.h"
#ifdef MODULES_MULTIPAGES

void __stdcall SaveSPPlayerCustomData(UnitAny* ptChar)
{
	Fog::D2Assert(ptChar == NULL, "ptChar==NULL", __FILE__, __LINE__);

	if (PCPY->selfStashIsOpened)
	{
		DWORD curSizeExt = 0;
		DWORD maxSizeExt = MAX_SAVEFILESIZE;
		BYTE* dataExt = (BYTE*)Fog::D2AllocMem(ptChar->ptGame->memoryPool, maxSizeExt, __FILE__, __LINE__, 0);
		Fog::D2Assert(!dataExt, "Error : Memory allocation Extended SaveFile", __FILE__, __LINE__);
		saveExtendedSaveFile(ptChar, &dataExt, &maxSizeExt, &curSizeExt);
		writeExtendedSaveFile(ptChar->ptPlayerData->name, dataExt, curSizeExt);
		Fog::D2FreeMem(ptChar->ptGame->memoryPool, dataExt, __FILE__, __LINE__, 0);
	}

	//if (active_sharedStash && PCPY->sharedStashIsOpened)
	//{
	//	DWORD curSizeShr = 0;
	//	DWORD maxSizeShr = MAX_SAVEFILESIZE;
	//	BYTE* dataShr = (BYTE*)Fog::D2AllocMem(ptChar->ptGame->memoryPool, maxSizeShr, __FILE__, __LINE__, 0);
	//	Fog::D2Assert(!dataShr, "Error : Memory allocation Shared SaveFile", __FILE__, __LINE__);
	//	saveSharedSaveFile(ptChar, &dataShr, &maxSizeShr, &curSizeShr);

	//	NetClient* ptClient = ptChar->ptPlayerData->ptNetClient;
	//	writeSharedSaveFile(ptChar->ptPlayerData->name, dataShr, curSizeShr, ptClient->isHardCoreGame);
	//	Fog::D2FreeMem(ptChar->ptGame->memoryPool, dataShr, __FILE__, __LINE__, 0);
	//}
}


__declspec(naked) void caller_SaveSPPlayerCustomData_111()
{
	__asm
	{
		CALL Fog::D2FogGetSavePath
		PUSH DWORD PTR SS : [ESP + 0x2608]
		CALL SaveSPPlayerCustomData
		RETN
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

#define TC_SAVE_PERSONAL 0
#define TC_SAVE_SHARED 1

#pragma pack(1)
typedef struct {
	BYTE	packID;
	BYTE	packSize;
	BYTE	init;
	DWORD	finalSize : 31;
	DWORD	isCustom : 1;
	BYTE	type;
	BYTE	data[0xFF];
} t_rcvMsg;
#pragma pack()

struct s_MPSaveFile
{
	int		sizeExtended;
	int		curExtended;
	BYTE* dataExtended;
	int		sizeShared;
	int		curShared;
	BYTE* dataShared;
};
static s_MPSaveFile receivedSaveFiles;
static BYTE customPackID = 0xB2;
//static s_MPSaveFile* receivedSaveFiles = NULL;


struct s_dataToSend
{
	s_dataToSend* next;
	int		clientID;
	int		sizeExtended;
	int		curExtended;
	BYTE* dataExtended;
	int		sizeShared;
	int		curShared;
	BYTE* dataShared;
	bool	init;
};
s_dataToSend* ptDataToSend = NULL;

void __stdcall SendSaveFilesToSave(UnitAny* ptChar)
{
	DWORD curSizeExt = 0;
	BYTE* dataExt = NULL;
	DWORD curSizeShr = 0;
	BYTE* dataShr = NULL;

	if (PCPY->selfStashIsOpened)
	{
		DWORD maxSizeExt = MAX_SAVEFILESIZE;
		dataExt = (BYTE*)Fog::D2AllocMem(ptChar->ptGame->memoryPool, maxSizeExt, __FILE__, __LINE__, 0);
		Fog::D2Assert(!dataExt, "Error : Memory allocation Extended SaveFile", __FILE__, __LINE__);
		saveExtendedSaveFile(ptChar, &dataExt, &maxSizeExt, &curSizeExt);
	}

	//if (active_sharedStash && PCPY->sharedStashIsOpened)
	//{
	//	DWORD maxSizeShr = MAX_SAVEFILESIZE;
	//	dataShr = (BYTE*)Fog::D2AllocMem(ptChar->ptGame->memoryPool, maxSizeShr, __FILE__, __LINE__, 0);
	//	Fog::D2Assert(!dataShr, "Error : Memory allocation Shared SaveFile", __FILE__, __LINE__);
	//	saveSharedSaveFile(ptChar, &dataShr, &maxSizeShr, &curSizeShr);
	//}

	NetClient* ptClient = ptChar->ptPlayerData->ptNetClient;
	s_dataToSend* dataToSend = ptDataToSend;
	while (dataToSend && (dataToSend->clientID != ptClient->clientID))
		dataToSend = dataToSend->next;
	if (!dataToSend)
	{
		dataToSend = (s_dataToSend*)Fog::D2AllocMem(ptChar->ptGame->memoryPool, sizeof(s_dataToSend), __FILE__, __LINE__, 0);
		ZeroMemory(dataToSend, sizeof(s_dataToSend));
		dataToSend->next = ptDataToSend;
		ptDataToSend = dataToSend;
	}

	//Sending savefiles
	dataToSend->clientID = ptClient->clientID;
	dataToSend->init = 1;
	dataToSend->sizeExtended = curSizeExt;
	dataToSend->curExtended = 0;
	dataToSend->dataExtended = dataExt;
	dataToSend->sizeShared = curSizeShr;
	dataToSend->curShared = 0;
	dataToSend->dataShared = dataShr;
	//LogMsg("clientID=%d\t init=%d\t sizeExtended=%X\t curExtended=%X\t dataExtended=%X\t sizeShared=%X\t curShared=%X\t dataShared=%08X\n",
		//dataToSend->clientID, dataToSend->init, dataToSend->sizeExtended, dataToSend->curExtended, dataToSend->dataExtended, dataToSend->sizeShared, dataToSend->curShared, dataToSend->dataShared);

	/*	NetClient* ptClient = D2GetClient(ptChar,__FILE__,__LINE__);
		if (dataExt)
		{
			sendDataToSave(ptClient->clientID, dataExt, curSizeExt, false);
			Fog::D2FreeMem(ptChar->ptGame->memoryPool, dataExt,__FILE__,__LINE__,0);
		}
		if (dataShr)
		{
			sendDataToSave(ptClient->clientID, dataShr, curSizeShr, true);
			Fog::D2FreeMem(ptChar->ptGame->memoryPool, dataShr,__FILE__,__LINE__,0);
		}
	*/
	//LogMsg("End SendSaveFilesToSave.\n\n");
}


DWORD __stdcall ManageNextPacketToSend(NetClient* ptClient)
{
	//LogMsg("ManageNextPacketToSend: ");
	s_dataToSend* dataToSend = ptDataToSend;
	while (dataToSend && (dataToSend->clientID != ptClient->clientID))
		dataToSend = dataToSend->next;
	if (!dataToSend) return 1;

	//LogMsg("clientID=%d\t init=%d\t sizeExtended=%X\t curExtended=%X\t dataExtended=%X\t sizeShared=%X\t curShared=%X\t dataShared=%08X\n",
		//dataToSend->clientID, dataToSend->init, dataToSend->sizeExtended, dataToSend->curExtended, dataToSend->dataExtended, dataToSend->sizeShared, dataToSend->curShared, dataToSend->dataShared);

	if (dataToSend->sizeExtended && dataToSend->dataExtended && (dataToSend->curExtended < dataToSend->sizeExtended))
	{
		DWORD remainingData = dataToSend->sizeExtended - dataToSend->curExtended;
		t_rcvMsg* msg = (t_rcvMsg*)Fog::D2AllocMem(ptClient->ptGame->memoryPool, sizeof(t_rcvMsg), __FILE__, __LINE__, 0);
		msg->packID = customPackID;
		msg->init = dataToSend->init;
		msg->finalSize = dataToSend->sizeExtended;
		msg->type = TC_SAVE_PERSONAL;
		msg->isCustom = true;
		msg->packSize = remainingData > 0xFE ? 0xFF : (BYTE)remainingData + 1;
		CopyMemory(msg->data, &dataToSend->dataExtended[dataToSend->curExtended], msg->packSize);
		//LogMsg("Saving Send Packet: type=%X\t init=%d\t finalSize=%X\t packSize=%02X\t data=%08X\n", msg->type, msg->init, msg->finalSize, msg->packSize, msg->data);
		D2Net::D2NetSendPacketToClient(0, dataToSend->clientID, msg, msg->packSize + 7);
		dataToSend->init = false;
		dataToSend->curExtended += msg->packSize - 1;
		Fog::D2FreeMem(ptClient->ptGame->memoryPool, msg, __FILE__, __LINE__, 0);
		if (dataToSend->curExtended == dataToSend->sizeExtended)
		{
			dataToSend->sizeExtended = 0;
			dataToSend->curExtended = 0;
			Fog::D2FreeMem(ptClient->ptGame->memoryPool, dataToSend->dataExtended, __FILE__, __LINE__, 0);
			dataToSend->dataExtended = NULL;
		}
		return 0;//ManageNextPacketToSend(ptClient);//return 0;
	}

	if (dataToSend->sizeShared && dataToSend->dataShared && (dataToSend->curShared < dataToSend->sizeShared))
	{
		DWORD remainingData = dataToSend->sizeShared - dataToSend->curShared;
		t_rcvMsg* msg = (t_rcvMsg*)Fog::D2AllocMem(ptClient->ptGame->memoryPool, sizeof(t_rcvMsg), __FILE__, __LINE__, 0);
		msg->packID = customPackID;
		msg->init = dataToSend->init;
		msg->finalSize = dataToSend->sizeShared;
		msg->type = TC_SAVE_SHARED;
		msg->isCustom = true;
		msg->packSize = remainingData > 0xFE ? 0xFF : (BYTE)remainingData + 1;
		CopyMemory(msg->data, &dataToSend->dataShared[dataToSend->curShared], msg->packSize);
		D2Net::D2NetSendPacketToClient(0, dataToSend->clientID, msg, msg->packSize + 7);
		dataToSend->init = false;
		dataToSend->curShared += msg->packSize - 1;
		Fog::D2FreeMem(ptClient->ptGame->memoryPool, msg, __FILE__, __LINE__, 0);
		if (dataToSend->curShared == dataToSend->sizeShared)
		{
			dataToSend->sizeShared = 0;
			dataToSend->curShared = 0;
			Fog::D2FreeMem(ptClient->ptGame->memoryPool, dataToSend->dataShared, __FILE__, __LINE__, 0);
			dataToSend->dataShared = NULL;
		}
		return 0;//ManageNextPacketToSend(ptClient);//return 0;
	}

	return 1;
}


DWORD __stdcall ReceiveSaveFilesToSave(t_rcvMsg* msg)
{
	if ((msg->packID != customPackID) || !msg->isCustom) return 0;

	bool isShared;

	if (msg->type == TC_SAVE_PERSONAL)
		isShared = false;
	else if (msg->type == TC_SAVE_SHARED)
		isShared = true;
	else return 0;


	if (msg->init)
	{
		Fog::D2FogMemDeAlloc(receivedSaveFiles.dataExtended, __FILE__, __LINE__, 0);
		Fog::D2FogMemDeAlloc(receivedSaveFiles.dataShared, __FILE__, __LINE__, 0);
		ZeroMemory(&receivedSaveFiles, sizeof(receivedSaveFiles));//TODO
	}

	//LogMsg("receivedSaveFiles: sizeExtended=%d\t curExtended=%d\t dataExtended=%08X\t sizeShared=%d\t curShared=%d\t dataShared=%08X\n", receivedSaveFiles.sizeExtended, receivedSaveFiles.curExtended, receivedSaveFiles.dataExtended, receivedSaveFiles.sizeShared, receivedSaveFiles.curShared, receivedSaveFiles.dataShared);

	DWORD size = msg->packSize - 1;
	if (isShared)
	{
		if (receivedSaveFiles.sizeShared == 0)
			receivedSaveFiles.sizeShared = msg->finalSize;
		//		Fog::D2Assert(receivedSaveFiles.sizeShared != msg->finalSize, "Size of shared file has change", __FILE__, __LINE__);

		if (!receivedSaveFiles.dataShared)
			receivedSaveFiles.dataShared = (BYTE*)Fog::D2FogMemAlloc(receivedSaveFiles.sizeShared, __FILE__, __LINE__, 0);

		CopyMemory(&receivedSaveFiles.dataShared[receivedSaveFiles.curShared], msg->data, size);
		receivedSaveFiles.curShared += size;

	}
	else {

		if (receivedSaveFiles.sizeExtended == 0)
			receivedSaveFiles.sizeExtended = msg->finalSize;
		//		Fog::D2Assert(receivedSaveFiles.sizeExtended != msg->finalSize, "Size of extented file has change", __FILE__, __LINE__);

		if (!receivedSaveFiles.dataExtended)
			receivedSaveFiles.dataExtended = (BYTE*)Fog::D2FogMemAlloc(receivedSaveFiles.sizeExtended, __FILE__, __LINE__, 0);

		CopyMemory(&receivedSaveFiles.dataExtended[receivedSaveFiles.curExtended], msg->data, size);
		receivedSaveFiles.curExtended += size;
	}
	return 1;
}


void __stdcall SaveMPPlayerCustomData(UnitAny* ptChar)
{
	if (PCPY->selfStashIsOpened)
	{
		DWORD curSizeExt = 0;
		DWORD maxSizeExt = MAX_SAVEFILESIZE;
		BYTE* dataExt = (BYTE*)Fog::D2AllocMem(ptChar->ptGame->memoryPool, maxSizeExt, __FILE__, __LINE__, 0);
		Fog::D2Assert(!dataExt, "Error : Memory allocation Extended SaveFile", __FILE__, __LINE__);
		saveExtendedSaveFile(ptChar, &dataExt, &maxSizeExt, &curSizeExt);
		writeExtendedSaveFile(ptChar->ptPlayerData->name, dataExt, curSizeExt);
		Fog::D2FreeMem(ptChar->ptGame->memoryPool, dataExt, __FILE__, __LINE__, 0);
	}

	//if (active_sharedStash && PCPY->sharedStashIsOpened)
	//{
	//	DWORD curSizeShr = 0;
	//	DWORD maxSizeShr = MAX_SAVEFILESIZE;
	//	BYTE* dataShr = (BYTE*)Fog::D2AllocMem(ptChar->ptGame->memoryPool, maxSizeShr, __FILE__, __LINE__, 0);
	//	Fog::D2Assert(!dataShr, "Error : Memory allocation Shared SaveFile", __FILE__, __LINE__);
	//	saveSharedSaveFile(ptChar, &dataShr, &maxSizeShr, &curSizeShr);
	//	writeSharedSaveFile(ptChar->ptPlayerData->name, dataShr, curSizeShr, ptChar->ptPlayerData->ptNetClient->isHardCoreGame);
	//	Fog::D2FreeMem(ptChar->ptGame->memoryPool, dataShr, __FILE__, __LINE__, 0);
	//}

}


__declspec(naked) void caller_ManageNextPacketToSend()
{
	_asm
	{
		PUSH ESI
		CALL ManageNextPacketToSend
		TEST EAX, EAX
		JNZ end_caller_ManageNextPacketToSend
		XOR ECX, ECX
		RETN
		end_caller_ManageNextPacketToSend :
		MOV ECX, DWORD PTR DS : [ESI + 0x17C]
			RETN
	}
}

__declspec(naked) void caller_SendSaveFilesToSave_111()
{
	_asm
	{
		PUSH DWORD PTR SS : [ESP + 0x2014]
		CALL SendSaveFilesToSave
		MOV EAX, DWORD PTR SS : [ESP + 0x8]
		TEST EAX, EAX
		RETN
	}
}

__declspec(naked) void caller_ReceivedSaveFilesToSave_111()
{
	__asm
	{
		LEA EAX, DWORD PTR SS : [ESP + 0x10]
		PUSH EAX
		CALL ReceiveSaveFilesToSave
		TEST EAX, EAX
		JE continue_rcvFct
		ADD DWORD PTR SS : [ESP] , 0x3D
		RETN
		continue_rcvFct :
		MOVZX EAX, BYTE PTR SS : [ESP + 0x10]
			RETN
	}
}

void __fastcall D2SavePlayerServerPre(DWORD UNK_Zero_1, UnitAny* pChar, GameStruct* pGame,char* playername, char* accname, DWORD UNK_ONE_1, DWORD UNK_ONE_2, DWORD UNK_Zero_2)
{
	SaveMPPlayerCustomData(pChar);
	return;
}
__declspec(naked) void caller_SavePlayerServer()
{
	__asm
	{
		PUSHAD//0x20
		PUSH DWORD PTR SS : [ESP+0x38]
		PUSH DWORD PTR SS : [ESP + 0x38]
		PUSH DWORD PTR SS : [ESP + 0x38]
		PUSH DWORD PTR SS : [ESP + 0x38]
		PUSH DWORD PTR SS : [ESP + 0x38]
		PUSH DWORD PTR SS : [ESP + 0x38]
		//这里ecx跟edx是继承的
		call D2SavePlayerServerPre
		POPAD
		JMP D2Game::D2SavePlayerServer
	}
}

BOOL __fastcall NopSavePlayer(UnitAny* pItem)
{
	if (pItem && pItem->ptItemData && pItem->ptItemData->playerID != 0xFFFFFFFF)//说明
		return TRUE;//不保存
	return FALSE;//保存
}

__declspec(naked) void caller_NopSavePlayer()
{
	__asm
	{
		mov ecx, dword ptr ds : [eax + 0xC8]
		shr ecx, 0xF
		and ecx, 0x1
		mov dword ptr ss : [esp+4] , ecx
		pushad
		mov ecx,eax
		call NopSavePlayer
		test eax,eax
		jnz mark1
		popad
		retn//正常走
		mark1:
popad
		mov ecx,1
		retn//这样直接结束不保存
	}
}

BOOL __fastcall NopSavePlayer2(UnitAny* pItem)
{
	if (pItem && pItem->ptItemData && pItem->ptItemData->ptInventory)
	{
		UnitAny * pCursorItem=D2Common::D2GetCursorItem(pItem->ptItemData->ptInventory);
		if (pCursorItem == pItem)
		{
			//LogMsg(
			//	"通过手上物品:%d,获得page:%d,指针equipLoc：%d page:%d ItemData2:%d ItemData3:%d", pItem->dwTxtFileNo, D2Common::D2GetItemPage(D2Common::D2UnitIsItem(pItem)), pItem->ptItemData->equipLoc,
			//	pItem->ptItemData->page, pItem->ptItemData->ItemData2, pItem->ptItemData->ItemData3
			//);
			return TRUE;
		}
	}
	return FALSE;
}
__declspec(naked) void caller_NopSavePlayer2()
{
	__asm
	{
		pushad
		mov ecx,eax
		call NopSavePlayer2
		test eax,eax
		jz mark1
		popad
		jmp D2Game::VD2SaveItemToStream
mark1:
		popad
		xor eax,eax
		retn 4
	}
}

__declspec(naked) void SaveCharAllToStream_ASM()
{
	__asm
	{
		mov eax, 0x201C
		call D2Game::ADDR06820
		push ebx
		mov ebx, dword ptr ss : [esp + 0x202C]
		cmp ebx, 0x2
		push ebp
		push esi
		mov esi, ecx
		mov ebp, esi
		push edi
		mov edi, edx
		mov dword ptr ss : [esp + 0x14] , ebp
		jge MARK024C3803
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 0x201C
		retn 0x18
MARK024C3803:
		mov word ptr ds : [esi] , 0x4D4A
		mov eax, edi
		add esi, 0x2
		call D2Game::ADDR53260
		mov ecx, eax
		mov eax, esi;  user32.GetDC
		sub eax, ebp
		lea edx, dword ptr ds : [eax + 0x2]
		cmp ebx, edx
		mov dword ptr ss : [esp + 0x10] , ecx
		jl MARK024C3B32
		mov dword ptr ss : [esp + 0x24] , esi;  user32.GetDC
		mov word ptr ds : [esi] , cx
		add esi, 0x2
		test edi, edi
		jnz MARK024C3846
		pop edi
		mov eax, esi
		pop esi
		sub eax, ebp
		pop ebp
		pop ebx
		add esp, 0x201C
		retn 0x18
MARK024C3846:
		push edi
		call D2Common::ADDD10061
		push 0x4
		push edi
		mov dword ptr ss : [esp + 0x24] , eax
		call D2Common::D2GetItemByBodyLoc
		push 0x5
		mov ebx, eax
		push edi
		mov dword ptr ss : [esp + 0x30] , ebx
		call D2Common::D2GetItemByBodyLoc
		mov ebp, eax
		push edi
		mov dword ptr ss : [esp + 0x1C] , ebp
		call D2Common::D2GetCursorItem
		mov dword ptr ss : [esp + 0x20] , eax
		mov eax, dword ptr ss : [esp + 0x1C]
		test eax, eax
		je MARK024C38F4
		cmp ebx, eax
		push 0x0
		push 0x1
		push 0x1
		push 0x2000
		jnz MARK024C38B7
		lea eax, dword ptr ss : [esp + 0x3C]
		push eax
		push ebx
		call D2Common::D2SaveItem
		test eax, eax
		jl MARK024C38E4
		test ebp, ebp
		je MARK024C3930
		push 0x0
		push 0x1
		push 0x1
		push 0x2000
		lea ecx, dword ptr ss : [esp + 0x3C]
		push ecx
		push ebp
		jmp MARK024C38DB
MARK024C38B7:
		lea edx, dword ptr ss : [esp + 0x3C]
		push edx
		push ebp
		call D2Common::D2SaveItem
		test eax, eax
		jl MARK024C38E4
		test ebx, ebx
		je MARK024C3930
		push 0x0
		push 0x1
		push 0x1
		push 0x2000
		lea eax, dword ptr ss : [esp + 0x3C]
		push eax
		push ebx
MARK024C38DB:
		call D2Common::D2SaveItem
		test eax, eax
		jge MARK024C3930
MARK024C38E4:
		pop edi;  0019FE5C
		pop esi;  0019FE5C
		pop ebp;  0019FE5C
		or eax, -0x1
		pop ebx;  0019FE5C
		add esp, 0x201C
		retn 0x18
MARK024C38F4:
		test ebx, ebx
		je MARK024C3930
		push 0x0
		push 0x1
		push 0x1
		push 0x2000
		lea ecx, dword ptr ss : [esp + 0x3C]
		push ecx
		push ebx
		call D2Common::D2SaveItem
		test eax, eax
		jl MARK024C38E4
		test ebp, ebp
		je MARK024C3930
		push 0x0
		push 0x1
		push 0x1
		push 0x2000
		lea edx, dword ptr ss : [esp + 0x3C]
		push edx
		push ebp
		call D2Common::D2SaveItem
		test eax, eax
		jl MARK024C38E4
MARK024C3930:
		push edi
		call D2Common::D2GetFirstInventoryItem
		mov ebp, eax
		test ebp, ebp
		je MARK024C39A9
		lea esp, dword ptr ss : [esp]
MARK024C3940:
		push ebp
		call D2Common::D2UnitIsItem
		mov edi, eax
		push edi
		call D2Common::D2GetBodyloc
		push ebp
		mov bl, al
		call D2Common::D2GetItemNodePage
		cmp eax, 0x3
		jnz MARK024C3965
		cmp bl, 0x4
		je MARK024C3999
		cmp bl, 0x5
		je MARK024C3999
MARK024C3965:
		mov edx, dword ptr ss : [esp + 0x14]
		mov eax, dword ptr ss : [esp + 0x2038]
		sub edx, esi;  user32.GetDC
		add edx, eax
		push esi;  user32.GetDC
		mov eax, edi
		call caller_NopSavePlayer2
		test eax, eax
		jl MARK024C38E4
		add esi, eax
		test eax, eax
		jnz MARK024C3999
		cmp word ptr ss : [esp + 0x10] , ax
		jbe MARK024C3999
		add dword ptr ss : [esp + 0x10] , 0xFFFF
MARK024C3999:
		push ebp
		call D2Common::D2GetNextInventoryItem
		mov ebp, eax
		test ebp, ebp
		jnz MARK024C3940
		mov ebx, dword ptr ss : [esp + 0x28]
MARK024C39A9:
		mov eax, dword ptr ss : [esp + 0x1C]
		test eax, eax
		je MARK024C3A72
		cmp ebx, eax
		push esi;  user32.GetDC
		jnz MARK024C3A2D
		mov edx, dword ptr ss : [esp + 0x18]
		mov ebp, dword ptr ss : [esp + 0x203C]
		sub edx, esi;  user32.GetDC
		add edx, ebp
		mov eax, ebx
		call caller_NopSavePlayer2;  PET保存的函数 人物保存也在这走
		test eax, eax
		jl MARK024C38E4
		mov edi, dword ptr ss : [esp + 0x10]
		add esi, eax
		test eax, eax
		jnz MARK024C39ED
		test di, di
		jbe MARK024C39ED
		add edi, 0xFFFF
MARK024C39ED:
		mov eax, dword ptr ss : [esp + 0x18]
		test eax, eax
		je MARK024C3AE8
		mov edx, dword ptr ss : [esp + 0x14]
		sub edx, esi;  user32.GetDC
		add edx, ebp
		push esi;  user32.GetDC
		call caller_NopSavePlayer2;  ESP + 10是player
		test eax, eax
		jl MARK024C38E4
		add esi, eax
		test eax, eax
		jnz MARK024C3AE8
		test di, di
		jbe MARK024C3AE8
		add edi, 0xFFFF
		jmp MARK024C3AE8
MARK024C3A2D:
		mov ebp, dword ptr ss : [esp + 0x18]
		mov edi, dword ptr ss : [esp + 0x203C]
		mov eax, dword ptr ss : [esp + 0x1C]
		mov edx, ebp
		sub edx, esi
		add edx, edi
		call caller_NopSavePlayer2
		test eax, eax
		jl MARK024C38E4
		add esi, eax
		test eax, eax
		jnz MARK024C3A64
		cmp word ptr ss : [esp + 0x10] , ax
		jbe MARK024C3A64
		add dword ptr ss : [esp + 0x10] , 0xFFFF
MARK024C3A64:
		test ebx, ebx
		je MARK024C3AE4
		mov edx, ebp
		sub edx, esi;  user32.GetDC
		add edx, edi
		mov eax, ebx
		jmp MARK24C3AC1
MARK024C3A72:
		test ebx, ebx
		je MARK024C3AAA
		mov edx, dword ptr ss : [esp + 0x14]
		mov ebp, dword ptr ss : [esp + 0x2038]
		sub edx, esi;  user32.GetDC
		add edx, ebp
		push esi;  user32.GetDC
		mov eax, ebx
		call caller_NopSavePlayer2
		test eax, eax
		jl MARK024C38E4
		add esi, eax
		test eax, eax
		jnz MARK024C3AAA
		cmp word ptr ss : [esp + 0x10] , ax
		jbe MARK024C3AAA
		add dword ptr ss : [esp + 0x10] , 0xFFFF
MARK024C3AAA:
		mov eax, dword ptr ss : [esp + 0x18]
		test eax, eax
		je MARK024C3AE4
		mov edx, dword ptr ss : [esp + 0x14]
		mov ebx, dword ptr ss : [esp + 0x2038]
		sub edx, esi
		add edx, ebx
MARK24C3AC1:
		push esi
		call caller_NopSavePlayer2
		test eax, eax
		jl MARK024C38E4
		add esi, eax
		test eax, eax
		jnz MARK024C3AE4
		cmp word ptr ss : [esp + 0x10] , ax
		jbe MARK024C3AE4
		add dword ptr ss : [esp + 0x10] , 0xFFFF
MARK024C3AE4:
		mov edi, dword ptr ss : [esp + 0x10]
MARK024C3AE8:
		mov eax, dword ptr ss : [esp + 0x20] ;  ntdll.778F216C
		test eax, eax
		je MARK024C3B23
		cmp dword ptr ds : [eax] , 0x4
		jnz MARK024C3B23
		mov edx, dword ptr ss : [esp + 0x14]
		mov ebp, dword ptr ss : [esp + 0x2038]
		sub edx, esi;  user32.GetDC
		add edx, ebp
		push esi
		call caller_NopSavePlayer2
		test eax, eax
		jl MARK024C38E4
		add esi, eax
		test eax, eax
		jnz MARK024C3B23
		test di, di
		jbe MARK024C3B23
		add edi, 0xFFFF
MARK024C3B23:
		mov eax, dword ptr ss : [esp + 0x24]
		mov ecx, dword ptr ss : [esp + 0x14]
		mov word ptr ds : [eax] , di
		mov eax, esi;  user32.GetDC
		sub eax, ecx
MARK024C3B32:
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x201C
		retn 0x18


	}
}
void Install_SavePlayerData()
{

	DWORD offset = 0;
#ifdef D2SERVER
	//不要产生尸体
	offset = D2Game::GetAddress(0x79210);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x83, 0x31);
	Memory::ChangeDword(0x555318EC, 0x0014C2C0);

	//Save single player custom data.
	offset = D2Game::GetAddress(0x53F35);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)Fog::D2FogGetSavePath, (DWORD)caller_SaveSPPlayerCustomData_111);

	//Send SaveFiles
	offset = D2Game::GetAddress(0x53EAB);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0x90);
	Memory::ChangeByte(0x44, 0xE8);
	Memory::ChangeCallA(0xC0850424, (DWORD)caller_SendSaveFilesToSave_111);
	offset = D2Game::GetAddress(0x2D173);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0x90);
	Memory::ChangeByte(0x8E, 0xE8);
	Memory::ChangeCallA(0x0000017C, (DWORD)caller_ManageNextPacketToSend);

	// Save multiplayer player custom data.
	offset = D2Game::GetAddress(0x543B3);
	Memory::SetCursor(offset);
	Memory::ChangeCallC((DWORD)D2Game::D2SavePlayerServer, (DWORD)caller_SavePlayerServer);

	//将保存物品的函数NOP掉
	//if (GetModuleHandle("d2server"))
	//{
		//offset = D2Game::GetAddress(0x53471);
		//Memory::SetCursor(offset);
		//Memory::ChangeByte( 0x85,0x33);
	//}

	//if (GetModuleHandle("d2server"))
	{
		//offset = D2Game::GetAddress(0x53475);
		//Memory::SetCursor(offset);
		//Memory::ChangeByte(0x8B, 0x90);
		//Memory::ChangeByte(0x88, 0xE8);
		//Memory::ChangeCallA(0xC8, (DWORD)caller_NopSavePlayer);
		//Memory::ChangeDword(0x830fe9c1, 0x90909090);
		//Memory::ChangeDword(0x0c8901e1, 0x90909090);
		//Memory::ChangeByte(0x24, 0x90);
	}

	{
		//offset = D2Game::GetAddress(0x53978);
		//Memory::SetCursor(offset);
		//Memory::ChangeCallC((DWORD)D2Game::VD2SaveItemToStream, (DWORD)caller_NopSavePlayer2);//交易的时候立马执行

		//offset = D2Game::GetAddress(0x539CC);
		//Memory::SetCursor(offset);
		//Memory::ChangeCallC((DWORD)D2Game::VD2SaveItemToStream, (DWORD)caller_NopSavePlayer2);//交易的时候立马执行

		//offset = D2Game::GetAddress(0x53A03);
		//Memory::SetCursor(offset);
		//Memory::ChangeCallC((DWORD)D2Game::VD2SaveItemToStream, (DWORD)caller_NopSavePlayer2);

		//offset = D2Game::GetAddress(0x53A43);
		//Memory::SetCursor(offset);
		//Memory::ChangeCallC((DWORD)D2Game::VD2SaveItemToStream, (DWORD)caller_NopSavePlayer2);

		//offset = D2Game::GetAddress(0x53A89);
		//Memory::SetCursor(offset);
		//Memory::ChangeCallC((DWORD)D2Game::VD2SaveItemToStream, (DWORD)caller_NopSavePlayer2);

		//offset = D2Game::GetAddress(0x53AC3);
		//Memory::SetCursor(offset);
		//Memory::ChangeCallC((DWORD)D2Game::VD2SaveItemToStream, (DWORD)caller_NopSavePlayer2);

		//offset = D2Game::GetAddress(0x53B06);
		//Memory::SetCursor(offset);
		//Memory::ChangeCallC((DWORD)D2Game::VD2SaveItemToStream, (DWORD)caller_NopSavePlayer2);

		//offset = D2Game::GetAddress(0xEC0B8);
		//Memory::SetCursor(offset);
		//Memory::ChangeCallC((DWORD)D2Game::VD2SaveItemToStream, (DWORD)caller_NopSavePlayer2);
	}
	offset = D2Game::GetAddress(0x53BA4);
	Memory::SetCursor(offset);
	Memory::ChangeCallC((DWORD)D2Game::VD2SaveUnitToStream, (DWORD)SaveCharAllToStream_ASM);

	offset = D2Game::GetAddress(0xEC230);
	Memory::SetCursor(offset);
	Memory::ChangeCallC((DWORD)D2Game::VD2SaveUnitToStream, (DWORD)SaveCharAllToStream_ASM);

#endif // D2SERVER

	offset = D2Client::GetAddress(0x43946);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x0F, 0xE8);
	Memory::ChangeCallA(0x0C2444B6, (DWORD)caller_ReceivedSaveFilesToSave_111);
	//Received SaveFiles

	customPackID++;

}

//+537D0实际上是一个写进流的函数
//+ 7100E CALL到537D0 是交易写进流
//+ 53BA3 CALL到537D0是退出时写进流
//+ EC22F CALL到537D0很有可能是保存pet
/*================================= END OF FILE =================================*/
#endif