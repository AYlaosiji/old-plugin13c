class PATCHLOAD_API D2Game : public Library<D2Game>
{
	static void SetFunctions();

public:
	static void Init();

public:
	typedef UnitAny* (__stdcall* TD2GetSpace) (DrlgRoom1* pRoom, D2Coord* pSourceCoord, unsigned int a3, int a4, DrlgRoom1** pLvlRoom, signed int a6);
	static TD2GetSpace D2GetSpace;

	typedef DrlgRoom1* (__fastcall* TD2GetFreeCoords) (DrlgRoom1* pRoom, D2Coord* pSourceCoord, D2Coord* pOutputCoord, BOOL b4);
	static TD2GetFreeCoords VD2GetFreeCoords;
	static TD2GetFreeCoords D2GetFreeCoords;

	typedef UnitAny*(__fastcall* TD2CreateUnit) (GameStruct* pGame, DrlgRoom1* pRoom, int nClass, int nType, int nXpos, int nYpos, int nA7, int nA8, int nA9);
	static TD2CreateUnit VD2CreateUnit;
	static TD2CreateUnit D2CreateUnit;

	typedef DWORD(__fastcall* TD2SpawnMonster) (GameStruct* ptGame, DrlgRoom1* ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2);
	static TD2SpawnMonster VD2SpawnMonster;
	static TD2SpawnMonster D2SpawnMonster;

	typedef UnitAny*(__stdcall* TD2SpawnSuperUniqueMonster) (GameStruct* ptGame, DrlgRoom1* ptRoom, DWORD x, DWORD y,DWORD superuniqueID);
	static TD2SpawnSuperUniqueMonster D2SpawnSuperUniqueMonster;

	typedef BOOL(__fastcall* TD2DropTreasureClass) (GameStruct* pGame, UnitAny* pSource, UnitAny* pKiller, DWORD pTC_D2TCExShortStrc, DWORD nQuality, DWORD nIlvl, DWORD dwZero, DWORD dwZero2, DWORD dwZero3, DWORD dwZero4);
	static TD2DropTreasureClass VD2DropTreasureClass;
	static TD2DropTreasureClass D2DropTreasureClass;

	typedef void (__fastcall* TD2SendPacketToClient) (NetClient* pClient, void* pPacket, size_t nSize);
	static TD2SendPacketToClient VD2SendPacketToClient;
	static TD2SendPacketToClient D2SendPacketToClient;

	typedef UnitAny* (__stdcall* TD2CreateLinkedPortalInLevel) (GameStruct* pGame, UnitAny* pPortal, int nLevel, int nA4);
	static TD2CreateLinkedPortalInLevel D2CreateLinkedPortalInLevel;
	
	typedef void (__fastcall* TD2StartActPlayerStats) (GameStruct* pGame, UnitAny* pPlayer, BYTE nAct);
	static TD2StartActPlayerStats VD2StartActPlayerStats;
	static TD2StartActPlayerStats D2StartActPlayerStats;

	typedef void(__fastcall* TD2ApplyDamage) (DWORD unk1,DWORD unk2,DWORD unk3,DWORD unk4, DWORD unk5, DWORD unk6);
	static TD2ApplyDamage VD2ApplyDamage;

	typedef DWORD(__fastcall* TD2DeleteItem) (GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem);
	static TD2DeleteItem VD2DeleteItem;
	static TD2DeleteItem D2DeleteItem;

	typedef DWORD(__fastcall* TD2UpdateClientItemStat) (NetClient* pClient, UnitAny* pItem, BOOL bSetStat, DWORD nStat, int nValue);
	static TD2UpdateClientItemStat VD2UpdateClientItemStat;
	static TD2UpdateClientItemStat D2UpdateClientItemStat;

	typedef DWORD(__fastcall* TD2SpawnItem) (GameStruct* pGame, UnitAny* pUnit, DWORD dwCode, int nItemLevel, int nQuality, BOOL bDrop);
	static TD2SpawnItem VD2SpawnItem;
	static TD2SpawnItem D2SpawnItem;

	typedef DWORD(__fastcall* TD2LoadInventory) (GameStruct* ptGame, UnitAny* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD* ptNbBytesRead);
	static TD2LoadInventory VD2LoadInventory;
	static TD2LoadInventory D2LoadInventory;

	typedef void(__fastcall* TD2SavePlayerServer)(DWORD UNK_Zero_1,UnitAny* pChar,char* playername,char* accname,DWORD UNK_ONE_1,DWORD UNK_ONE_2, DWORD UNK_Zero_2,GameStruct* pGame);
	static TD2SavePlayerServer D2SavePlayerServer;

	typedef void(__stdcall* TD2SaveGame)(GameStruct* ptGame);
	static TD2SaveGame D2SaveGame;

	typedef UnitAny* (__fastcall* TD2GameGetObject) (GameStruct* ptGame, DWORD type, DWORD itemNum);
	static TD2GameGetObject VD2GameGetObject;
	static TD2GameGetObject D2GameGetObject;

	typedef DWORD(__fastcall* TD2VerifIfNotCarry1) (UnitAny* ptItem, ItemBIN* itemsData, UnitAny* ptFirstItem);
	static TD2VerifIfNotCarry1 VD2VerifIfNotCarry1;
	static TD2VerifIfNotCarry1 D2VerifIfNotCarry1;

	typedef BOOL(__fastcall* TD2SendPacket21ToUpdateSkills) (NetClient* pClient, UnitAny* pPlayer, DWORD SkillID, DWORD dwZero, DWORD dwOne);
	static TD2SendPacket21ToUpdateSkills VD2SendPacket21ToUpdateSkills;
	static TD2SendPacket21ToUpdateSkills D2SendPacket21ToUpdateSkills;

	typedef void(__stdcall* TD2ProduceCubeItem)(GameStruct* ptGame,UnitAny* pPlayer,CubeMainBIN* pCubeMaintxt,DWORD unk);
	static TD2ProduceCubeItem VD2ProduceCubeItem;

	typedef void(__fastcall* TD2SaveItemToStream)(UnitAny* pItem, BYTE* stream);
	static TD2SaveItemToStream VD2SaveItemToStream;

	typedef void(__fastcall* TD2SaveUnitToStream)();//不是对的
	static TD2SaveUnitToStream VD2SaveUnitToStream;

	typedef UnitAny*(__fastcall* TD2GetPlayerPet)(UnitAny* pPlayer,DWORD unk_7,DWORD unk_1, GameStruct* ptGame);
	static TD2GetPlayerPet VD2GetPlayerPet;
	static TD2GetPlayerPet D2GetPlayerPet;

	typedef UnitAny* (__fastcall* TD2GetPlayerFromPet)(GameStruct* ptGame, UnitAny* pMonsterBeHitted,UnitAny* pCheckMonster);
	static TD2GetPlayerFromPet VD2GetPlayerFromPet;
	static TD2GetPlayerFromPet D2GetPlayerFromPet;

	typedef BOOL (__fastcall* TD2CheckTwoUnitIsFriendly)(UnitAny* pMonster1, UnitAny* pMonster2);
	static TD2CheckTwoUnitIsFriendly VD2CheckTwoUnitIsFriendly;

	static NetClient** ptClientTable;
	static DWORD** ADDR06820;
	static DWORD** ADDR53260;
};
