#include"pch.h"
#ifdef MODULES_MULTIPAGES
DWORD __stdcall LoadSPCustomData(UnitAny* ptChar)
{
	DWORD size = 0;
	BYTE* data;

	Fog::D2Assert(ptChar == NULL, "ptChar == NULL", __FILE__, __LINE__);
	Fog::D2Assert(ptChar->nUnitType != UNIT_PLAYER, " ptChar->nUnitType != UNIT_PLAYER", __FILE__, __LINE__);
	Fog::D2Assert(!ptChar->ptPlayerData, "ptPlayerData==NULL", __FILE__, __LINE__);
	Fog::D2Assert(!ptChar->ptGame, "ptGame==NULL", __FILE__, __LINE__);

	DWORD ret = 0;
	if (ptChar->ptGame->isLODGame)
	{
		data = readExtendedSaveFile(ptChar->ptPlayerData->name, &size);
		ret = loadExtendedSaveFile(ptChar, data, size);
		Fog::D2FogMemDeAlloc(data, __FILE__, __LINE__, 0);
	}
	return ret;
}

__declspec(naked) void caller_LoadSPPlayerCustomData()
{
	_asm
	{
		MOV ESI, EAX
		TEST ESI, ESI
		JNZ JMP_LoadSPPlayerCustomData
		PUSH DWORD PTR SS : [ESP + 0x14]
		CALL LoadSPCustomData
		MOV ESI, EAX
		TEST ESI, ESI
		JNZ JMP_LoadSPPlayerCustomData
		RETN
		JMP_LoadSPPlayerCustomData :
		ADD DWORD PTR SS : [ESP] , 0x17
			RETN
	}
}

/*
return value :
0:ok
1:Unable to enter game. Bad character version
2:Unable to enter game. Bad character quest data
3:Unable to enter game. Bad character waypoint data
4:Unable to enter game. Bad character stats data
5:Unable to enter game. Bad character skills data
6:Unable to enter game
7:Unable to enter game. Bad inventory data
8:Unable to enter game. Bad dead bodies
9:Unable to enter game. Bad header
0A:Unable to enter game. bad hireables
0B:Unable to enter game, bad intro data
0C:Unable to enter game. bad item
0D:Unable to enter game, bad dead body item
0E:Unable to enter game, generic bad file
0F:GameStruct is full
10:Version do not match....
11:Unable to enter game,Your character must kill Baal to play nightmare game
12:Unable to enter game,Your character must kill Baal in nightmare difficulty to play hell game
13:Unable to enter game, a normal character cannot join a game create an harcore character.
14:Unable to enter game, an harcore character cannot join a game create by a normal character.
15:A dead character cannot join or create any game
16:unknow failure
17:Unable to enter game. A D2 Character cannot join an expansion character
18:Expansion cannot join D2
19:Failures to join game
1A:Unable to enter game
1B:unknow failure
*/

enum 
{
	TS_SAVE_PERSONAL = 0,
	TS_SAVE_SHARED,
	TS_PUTGOLD,
	TS_TAKEGOLD
};

#pragma pack(1)
typedef struct {
	BYTE	packID;
	BYTE	packSize;
	DWORD	finalSize : 31;
	DWORD	isCustom : 1;
	BYTE	type;
	BYTE	data[0xFF];
} t_rcvMsg;
#pragma pack()

struct s_MPSaveFile
{
	DWORD clientID;
	int sizeExtended;
	int curExtended;
	BYTE* dataExtended;
	int sizeShared;
	int curShared;
	BYTE* dataShared;
	s_MPSaveFile* prev;
	s_MPSaveFile* next;
	bool completed;
};

static BYTE customPackID = 0x6C;
static s_MPSaveFile* receivedSaveFiles = NULL;

void freeCurrentCF(DWORD memoryPool, s_MPSaveFile** curSF)
{
	if (*curSF == NULL) return;
	Fog::Fog::D2FreeMem(memoryPool, (*curSF)->dataExtended, __FILE__, __LINE__, 0);
	Fog::D2FreeMem(memoryPool, (*curSF)->dataShared, __FILE__, __LINE__, 0);
	if ((*curSF)->next)
		(*curSF)->next->prev = (*curSF)->prev;
	if ((*curSF)->prev)
		(*curSF)->prev->next = (*curSF)->next;
	else
		receivedSaveFiles = (*curSF)->next;
	Fog::D2FreeMem(memoryPool, *curSF, __FILE__, __LINE__, 0);
	*curSF = NULL;
}

void sendData(BYTE* data, DWORD size, bool isShared)
{
	t_rcvMsg pack;
	//	Fog::D2Assert(size >= 0x40000000, "size of file > 0x40000000", __FILE__, __LINE__);

	pack.packID = customPackID;
	pack.finalSize = size;
	pack.isCustom = true;
	pack.type = isShared ? TS_SAVE_SHARED : TS_SAVE_PERSONAL;
	//LogMsg("Make Send Packet: \ttype=%X\t finalSize=%X\t packSize=%02X\t data=%08X\n", pack.type, pack.finalSize, pack.packSize, pack.data);

	DWORD sended = 0;
	while (sended < size)
	{
		pack.packSize = (BYTE)(size - sended > 0xFE ? 0xFF : size - sended + 1);
		CopyMemory(pack.data, &data[sended], pack.packSize);
		//LogMsg("Loading Send Packet: \ttype=%X\t finalSize=%X\t packSize=%02X\t data=%08X\n", pack.type, pack.finalSize, pack.packSize, pack.data);
		D2Net::D2SendToServer(pack.packSize + 7, 0, &pack);
		sended += pack.packSize - 1;
	}
}

static DWORD	sizeExtended;
static BYTE* dataExtended;
static DWORD	sizeShared;
static BYTE* dataShared;

void __fastcall SendSaveFiles(char* ptPath, DWORD maxsize, char* name)
{
	//	DWORD size;
	//	BYTE* data;

	Fog::D2FogGetSavePath(ptPath, maxsize);

	// Send Extended Save File
	dataExtended = readExtendedSaveFile(name, &sizeExtended);
	sendData(dataExtended, sizeExtended, false);
	Fog::D2FogMemDeAlloc(dataExtended, __FILE__, __LINE__, 0);

	// Send Shared Save File
	//dataShared = readSharedSaveFile(name, &sizeShared);
	//sendData(dataShared, sizeShared, true);
	//Fog::D2FogMemDeAlloc(dataShared, __FILE__, __LINE__, 0);
}

DWORD __stdcall ReceiveSaveFiles(DWORD clientID, t_rcvMsg* msg)
{
	//LogMsg("Loading Receive Packet: packid=%d(%d)\t clientID=%d\t type=%X\t finalSize=%X\t packSize=%02X\t data=%08X\n", msg->packID, customPackID, clientID, msg->type, msg->finalSize, msg->packSize, msg->data);

	if ((msg->packID != customPackID) || !msg->isCustom) return msg->packID;

	//LogMsg("Loading Receive Packet: clientID=%d\t type=%X\t finalSize=%X\t packSize=%02X\t data=%08X\n", clientID, msg->type, msg->finalSize, msg->packSize, msg->data);

	bool isShared;

	switch (msg->type)
	{
	case TS_SAVE_PERSONAL:	isShared = false; break;
	case TS_SAVE_SHARED:	isShared = true; break;
		//	case TS_PUTGOLD :		putGold(ptChar, (DWORD)msg->data); return 0;
		//	case TS_TAKEGOLD :		takeGold(ptChar, (DWORD)msg->data); return 0;
	default: return 0;//return msg->packID;
	}

	NetClient* ptClient = D2Game::ptClientTable[clientID & 0xFF];

	s_MPSaveFile* curSF = receivedSaveFiles;
	while (curSF && (clientID != curSF->clientID))
		curSF = curSF->next;

	if (curSF && curSF->completed)
		freeCurrentCF(0 * ptClient->ptGame->memoryPool, &curSF);


	if (!curSF)
	{
		curSF = (s_MPSaveFile*)Fog::D2AllocMem(0 * ptClient->ptGame->memoryPool, sizeof(s_MPSaveFile), __FILE__, __LINE__, 0);
		ZeroMemory(curSF, sizeof(s_MPSaveFile));
		curSF->clientID = clientID;
		curSF->next = receivedSaveFiles;
		if (receivedSaveFiles) receivedSaveFiles->prev = curSF;
		receivedSaveFiles = curSF;
	}

	//LogMsg("curSF = %08X\tcurSF->completed = %d\n", curSF, curSF->completed);


	DWORD size = msg->packSize - 1;
	if (isShared)
	{
		if (curSF->sizeShared == 0)
			curSF->sizeShared = msg->finalSize;
		Fog::D2Assert(curSF->sizeShared != msg->finalSize, "Size of shared file has change", __FILE__, __LINE__);

		if (!curSF->dataShared)
			curSF->dataShared = (BYTE*)Fog::D2AllocMem(0 * ptClient->ptGame->memoryPool, curSF->sizeShared, __FILE__, __LINE__, 0);//		Fog::D2Assert(!curSF->dataShared, "Can't malloc data", __FILE__, __LINE__);

		CopyMemory(&curSF->dataShared[curSF->curShared], msg->data, size);
		curSF->curShared += size;

	}
	else {

		if (curSF->sizeExtended == 0)
			curSF->sizeExtended = msg->finalSize;
		Fog::D2Assert(curSF->sizeExtended != msg->finalSize, "Size of extented file has change", __FILE__, __LINE__);

		if (!curSF->dataExtended)
			curSF->dataExtended = (BYTE*)Fog::D2AllocMem(0 * ptClient->ptGame->memoryPool, curSF->sizeExtended, __FILE__, __LINE__, 0);//		Fog::D2Assert(!curSF->dataExtended, "Can't malloc data", __FILE__, __LINE__);

		CopyMemory(&curSF->dataExtended[curSF->curExtended], msg->data, size);
		curSF->curExtended += size;
	}

	if (curSF->sizeExtended && (curSF->sizeExtended == curSF->curExtended) && curSF->sizeShared && (curSF->sizeShared == curSF->curShared))
	{
		curSF->completed = true;
		//LogMsg("ReceiveSaveFiles completed.\n");
	}
	//LogMsg("End Load Receive Packet\n");

	return msg->packID + 10;
}

DWORD __stdcall LoadMPCustomData(UnitAny* ptChar)
{
	Fog::D2Assert(ptChar == NULL, "ptChar == NULL", __FILE__, __LINE__);
	Fog::D2Assert(ptChar->nUnitType != UNIT_PLAYER, " ptChar->nUnitType != UNIT_PLAYER", __FILE__, __LINE__);
	Fog::D2Assert(!ptChar->ptPlayerData, "ptPlayerData==NULL", __FILE__, __LINE__);

	NetClient* ptClient = ptChar->ptPlayerData->ptNetClient;

	DWORD ret = 0;
	DWORD size = 0;
	BYTE* data;

	if (ptChar->ptGame->isLODGame)
	{
		data = readExtendedSaveFile(ptChar->ptPlayerData->name, &size);
		ret = loadExtendedSaveFile(ptChar, data, size);
		Fog::D2FogMemDeAlloc(data, __FILE__, __LINE__, 0);
	}

	return ret;
}



__declspec(naked) void caller_LoadMPPlayerCustomData_111()
{
	__asm
	{
		PUSH DWORD PTR SS : [EBX]
		CALL LoadMPCustomData
		TEST EAX, EAX
		JNZ JMP_LoadMPlayerCustomData
		CMP DWORD PTR DS : [EBX] , 0
		JNZ Continue_LoadMP
		ADD DWORD PTR SS : [ESP] , 0x21
		Continue_LoadMP :
		RETN
		JMP_LoadMPlayerCustomData :
		SUB DWORD PTR SS : [ESP] , 0x12
			RETN
	}
}


__declspec(naked) void caller_SendSaveFiles_111()
{
	__asm
	{
		POP EAX
		PUSH DWORD PTR CS : [EAX + 0x01] //"name"
		PUSH EAX
		JMP SendSaveFiles
	}
}




__declspec(naked) void caller_ReceiveSaveFiles_111()
{
	__asm
	{
		PUSH ECX
		PUSH EDX
		LEA EBX, DWORD PTR DS : [EBP + 4]
		PUSH EBX		//Message
		MOV EBX, DWORD PTR SS : [EBP]
		PUSH EBX		//ID client
		CALL ReceiveSaveFiles
		POP EDX
		POP ECX
		RETN
	}
}


void Install_LoadPlayerData()
{
#ifdef D2SERVER

	DWORD offset;

	offset = D2Game::GetAddress(0x5638D);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE8);
	Memory::ChangeCallA(0x75F685F0, (DWORD)caller_LoadSPPlayerCustomData);
	Memory::ChangeByte(0x16, 0x90);

	// Load MP player custom data.
	offset = D2Game::GetAddress(0x56217);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x83, 0xE8);
	Memory::ChangeCallA(0x2174003B, (DWORD)caller_LoadMPPlayerCustomData_111);

	// Receive save files from client.
	offset = D2Game::GetAddress(0xCAF39);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x8B, 0xE8);
	Memory::ChangeCallA(0xB60F005D, (DWORD)caller_ReceiveSaveFiles_111);
	Memory::ChangeByte(0x45, 0x90);
	Memory::ChangeByte(0x04, 0x90);

#endif // #ifdef D2SERVER
	
	// Send save files to Server.
	offset = D2Client::GetAddress(0x1457C);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)Fog::D2FogGetSavePath, (DWORD)caller_SendSaveFiles_111);

}
#endif