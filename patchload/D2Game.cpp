#include"pch.h"
__declspec (naked) void D2GameASM_D2GetFreeCoords()
{
	__asm
	{
		push esi
		push[esp + 0x0C]
		push[esp + 0x0C]
		push ecx
		mov esi, edx
		call D2Game::VD2GetFreeCoords
		pop esi
		retn 0x08
	}
}

__declspec (naked) void D2GameASM_D2CreateUnit()
{
	__asm
	{
		push[esp + 0x1C]
		push[esp + 0x1C]
		push[esp + 0x1C]
		push edx
		push ecx
		push[esp + 0x24]
		push[esp + 0x24]
		mov edx, [esp + 0x20]
		mov ecx, [esp + 0x24]
		call D2Game::VD2CreateUnit
		retn 0x1C
	}
}

__declspec (naked) void D2GameASM_D2SpawnMonster()
{
	__asm
	{
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH EDX
		PUSH ECX
		MOV EAX, DWORD PTR SS : [ESP + 0x18]
		MOV EDX, DWORD PTR SS : [ESP + 0x2C]
		MOV ECX, DWORD PTR SS : [ESP + 0x28]//superuniqueID
		CALL D2Game::VD2SpawnMonster
		RETN 0x18
	}
}

__declspec (naked) void D2GameASM_D2DropTreasureClass()
{
	__asm
	{
		pushad
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		mov edi, ecx
		mov esi, edx
		CALL D2Game::VD2DropTreasureClass//D2Game 12D60
		popad
		retn 0x20
	}
}

__declspec (naked) void D2GameASM_D2SendPacketToClient()
{
	__asm
	{
		POP EAX
		PUSH EDX
		PUSH EAX
		MOV EAX, ECX
		JMP D2Game::VD2SendPacketToClient
	}
}

__declspec (naked) void D2GameASM_D2GetPlayerPet()
{
	__asm
	{
		//pushad
		push ebp
		push ebx
		push edi
		push esi
		mov edi, [esp + 0x18]//第四个参数
		mov ebx, [esp + 0x14]//第三个参数
		mov esi, edx
		mov eax, ecx
		call D2Game::VD2GetPlayerPet
		pop esi
		pop edi
		pop ebx
		pop ebp
		retn 8
	}
}

__declspec (naked) void D2GameASM_D2GetPlayerFromPet()
{
	__asm
	{
		PUSH EDI
		PUSH EBX
		MOV EBX, [ESP + 0xC]
		PUSH EDX
		PUSH ECX
		CALL D2Game::VD2GetPlayerFromPet
		POP EBX
		POP EDI
		RETN
	}
}

__declspec (naked) void D2GameASM_D2StartActPlayerStats()
{
	__asm
	{
		MOVZx eax, byte ptr[ESP + 0x04]	// nAct
		PUSH ECX			// pGame  arg1 to func
		MOV ECX, EDX			// pPlayer
		CALL D2Game::VD2StartActPlayerStats		// pointer to 6FD0DD8
		RETN 4
	}
}

__declspec (naked) void D2GameASM_D2DeleteItem()
{
	__asm
	{
		push ecx
		mov ecx, edx
		mov eax, [esp + 0x08]
		call D2Game::VD2DeleteItem
		retn 0x04
	}
}

__declspec (naked) void D2GameASM_D2UpdateClientItemStat()
{
	_asm
	{
		push[esp + 0x0C] //nValue
		push[esp + 0x0C] //ptItem
		push[esp + 0x0C] //bool
		push ecx //unk1
		mov eax, edx //pClient
		call D2Game::VD2UpdateClientItemStat
		retn 0x0C
	}
}

__declspec (naked) void D2GameASM_D2SpawnItem()
{
	__asm
	{
		push[esp + 0x10]
		push[esp + 0x10]
		push ecx
		mov ecx, [esp + 0x10]
		mov eax, [esp + 0x14]
		call D2Game::VD2SpawnItem
		retn 0x10
	}
}

__declspec (naked) void D2GameASM_D2LoadInventory()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [ESP + 4]
		MOV DWORD PTR SS : [ESP + 4] , EDX
		JMP D2Game::VD2LoadInventory
	}
}

__declspec (naked) void D2GameASM_D2GameGetObject()
{
	__asm
	{
		MOV EAX, EDX
		MOV EDX, DWORD PTR SS : [ESP + 4]
		CALL D2Game::VD2GameGetObject
		RETN 4
	}
}

__declspec (naked) void D2GameASM_D2VerifIfNotCarry()
{
	__asm
	{
		PUSH EBX
		//PUSHAD
		PUSH ECX
		MOV EBX, EDX
		MOV EAX, DWORD PTR SS : [ESP + 0xC]
		CALL D2Game::VD2VerifIfNotCarry1
		POP EBX
		//POPAD
		RETN 4
	}
}

__declspec (naked) void D2GameASM_D2SendPacket21ToUpdateSkills()
{
	__asm
	{
		PUSHAD
		mov ebx, [esp + 0x8 + 0x1C]
		push[esp + 0x10 + 0x1C]
		push[esp + 0x10 + 0x1C]
		mov eax, ecx
		mov esi, edx
		CALL D2Game::VD2SendPacket21ToUpdateSkills
		POPAD
		RETN 0xC
	}
}

D2Game::TD2GetSpace D2Game::D2GetSpace;
D2Game::TD2GetFreeCoords D2Game::VD2GetFreeCoords;
D2Game::TD2GetFreeCoords D2Game::D2GetFreeCoords;
D2Game::TD2CreateUnit D2Game::VD2CreateUnit;
D2Game::TD2CreateUnit D2Game::D2CreateUnit;
D2Game::TD2SpawnMonster D2Game::VD2SpawnMonster;
D2Game::TD2SpawnMonster D2Game::D2SpawnMonster;
D2Game::TD2SpawnSuperUniqueMonster D2Game::D2SpawnSuperUniqueMonster;
D2Game::TD2DropTreasureClass D2Game::VD2DropTreasureClass;
D2Game::TD2DropTreasureClass D2Game::D2DropTreasureClass;
D2Game::TD2SendPacketToClient D2Game::VD2SendPacketToClient;
D2Game::TD2SendPacketToClient D2Game::D2SendPacketToClient;
D2Game::TD2CreateLinkedPortalInLevel D2Game::D2CreateLinkedPortalInLevel;
D2Game::TD2StartActPlayerStats D2Game::VD2StartActPlayerStats;
D2Game::TD2StartActPlayerStats D2Game::D2StartActPlayerStats;
D2Game::TD2ApplyDamage D2Game::VD2ApplyDamage;
D2Game::TD2DeleteItem D2Game::VD2DeleteItem;
D2Game::TD2DeleteItem D2Game::D2DeleteItem;
D2Game::TD2UpdateClientItemStat D2Game::VD2UpdateClientItemStat;
D2Game::TD2UpdateClientItemStat D2Game::D2UpdateClientItemStat;
D2Game::TD2SpawnItem  D2Game::VD2SpawnItem;
D2Game::TD2SpawnItem  D2Game::D2SpawnItem;
D2Game::TD2LoadInventory D2Game::VD2LoadInventory;
D2Game::TD2LoadInventory D2Game::D2LoadInventory;
D2Game::TD2SavePlayerServer D2Game::D2SavePlayerServer;
D2Game::TD2SaveGame D2Game::D2SaveGame;
D2Game::TD2GameGetObject D2Game::VD2GameGetObject;
D2Game::TD2GameGetObject D2Game::D2GameGetObject;
D2Game::TD2VerifIfNotCarry1 D2Game::VD2VerifIfNotCarry1;
D2Game::TD2VerifIfNotCarry1 D2Game::D2VerifIfNotCarry1;
D2Game::TD2SendPacket21ToUpdateSkills D2Game::VD2SendPacket21ToUpdateSkills;
D2Game::TD2SendPacket21ToUpdateSkills D2Game::D2SendPacket21ToUpdateSkills;
D2Game::TD2ProduceCubeItem D2Game::VD2ProduceCubeItem;
D2Game::TD2SaveItemToStream D2Game::VD2SaveItemToStream;
D2Game::TD2SaveUnitToStream D2Game::VD2SaveUnitToStream;
D2Game::TD2GetPlayerPet D2Game::VD2GetPlayerPet;
D2Game::TD2GetPlayerPet D2Game::D2GetPlayerPet;
D2Game::TD2GetPlayerFromPet D2Game::VD2GetPlayerFromPet;
D2Game::TD2GetPlayerFromPet D2Game::D2GetPlayerFromPet;
D2Game::TD2CheckTwoUnitIsFriendly D2Game::VD2CheckTwoUnitIsFriendly;

NetClient** D2Game::ptClientTable;
DWORD** D2Game::ADDR06820;
DWORD** D2Game::ADDR53260;

void D2Game::Init()
{
	Name = "D2Game.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Game::SetFunctions()
{
	D2GetSpace=(TD2GetSpace)GetAddress(0x34130);
	VD2GetFreeCoords = (TD2GetFreeCoords)GetAddress(0x6FC2E930 - 0x6FC20000);
	D2GetFreeCoords = (TD2GetFreeCoords)D2GameASM_D2GetFreeCoords;
	VD2CreateUnit = (TD2CreateUnit)GetAddress(0x6FD01D90 - 0x6FC20000);
	D2CreateUnit = (TD2CreateUnit)D2GameASM_D2CreateUnit;
	VD2SpawnMonster=(TD2SpawnMonster)GetAddress(0x24950);
	D2SpawnMonster = (TD2SpawnMonster)D2GameASM_D2SpawnMonster;
	D2SpawnSuperUniqueMonster=(TD2SpawnSuperUniqueMonster)GetAddress(0x251F0);
	VD2DropTreasureClass= (TD2DropTreasureClass)GetAddress(0x12D60);
	D2DropTreasureClass = (TD2DropTreasureClass)D2GameASM_D2DropTreasureClass;
	VD2SendPacketToClient = (TD2SendPacketToClient)GetAddress(0x8A3E0);
	D2SendPacketToClient = (TD2SendPacketToClient)D2GameASM_D2SendPacketToClient;
	D2CreateLinkedPortalInLevel = (TD2CreateLinkedPortalInLevel)GetAddress(0xA22E0);
	VD2StartActPlayerStats=(TD2StartActPlayerStats)GetAddress(0x6FD0B2C0- 0x6FC20000);
	D2StartActPlayerStats = (TD2StartActPlayerStats)D2GameASM_D2StartActPlayerStats;
	VD2ApplyDamage=(TD2ApplyDamage)GetAddress(0x37030);
	VD2DeleteItem = (TD2DeleteItem)GetAddress(0x6FCF39B0 - 0x6FC20000);
	D2DeleteItem= (TD2DeleteItem)D2GameASM_D2DeleteItem;
	VD2UpdateClientItemStat = (TD2UpdateClientItemStat)GetAddress(0x8B010);
	D2UpdateClientItemStat = (TD2UpdateClientItemStat)D2GameASM_D2UpdateClientItemStat;
	VD2SpawnItem = (TD2SpawnItem)GetAddress(0x36470);
	D2SpawnItem = (TD2SpawnItem)D2GameASM_D2SpawnItem;
	VD2LoadInventory=(TD2LoadInventory)GetAddress(0x54810);
	D2LoadInventory = (TD2LoadInventory)D2GameASM_D2LoadInventory;
	D2SavePlayerServer=(TD2SavePlayerServer)GetAddress(0x54000);
	D2SaveGame= (TD2SaveGame)GetAddress(0x2C830);
	VD2GameGetObject = (TD2GameGetObject)GetAddress(0xE03A0);
	D2GameGetObject = (TD2GameGetObject)D2GameASM_D2GameGetObject;
	VD2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)GetAddress(0xD2070);
	D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)D2GameASM_D2VerifIfNotCarry;
	VD2SendPacket21ToUpdateSkills = (TD2SendPacket21ToUpdateSkills)GetAddress(0x8D5F0);
	D2SendPacket21ToUpdateSkills = (TD2SendPacket21ToUpdateSkills)D2GameASM_D2SendPacket21ToUpdateSkills;
	VD2ProduceCubeItem=(TD2ProduceCubeItem)GetAddress(0x72220);
	VD2SaveItemToStream =(TD2SaveItemToStream)GetAddress(0x53470);
	VD2SaveUnitToStream=(TD2SaveUnitToStream)GetAddress(0x537D0);
	VD2GetPlayerPet=(TD2GetPlayerPet)GetAddress(0x96A40);
	D2GetPlayerPet = (TD2GetPlayerPet)D2GameASM_D2GetPlayerPet;
	VD2GetPlayerFromPet=(TD2GetPlayerFromPet)GetAddress(0xDB5E0);
	D2GetPlayerFromPet = (TD2GetPlayerFromPet)D2GameASM_D2GetPlayerFromPet;
	VD2CheckTwoUnitIsFriendly=(TD2CheckTwoUnitIsFriendly)GetAddress(0xe0a60);

	ptClientTable=(NetClient**)GetAddress(0x1107B8);
	ADDR06820=(DWORD**)GetAddress(0x6820);
	ADDR53260 = (DWORD**)GetAddress(0x53260);
}