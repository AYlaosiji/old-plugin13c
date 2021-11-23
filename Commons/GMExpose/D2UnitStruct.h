#pragma once
struct CBPlayerData;
struct CBItemData;
struct UnitAny;
struct SkillsBIN;
struct Skill;
struct ObjectsBIN;
struct NetClient;
/*=================================================================*/
/*  Skill Structure.                                               */
/*=================================================================*/

struct Skill
{								//Offset from Code. (size = 0x3C or 0x40)
	SkillsBIN*	ptSkillBin;		//+00
	Skill*	ptNextSkill;	//+04
	DWORD	mode;           //+08
	DWORD	uk1[3];         //+0C
	DWORD	targetInfo;     //+18
	DWORD	targetType;     //+1c
	DWORD	targetUNID;     //+20
	DWORD	uk2;            //+24
	DWORD	slvl;           //+28
	DWORD	slvlBonus;      //+2c
	DWORD	uk3;            //+30
	int		state;          //+34 (-1 if index exist)
	DWORD	param1;			//+38 (nb current charge)
	DWORD	param2;			//+3C
};

struct SkillInfo
{								//Offset from Code.
	DWORD		gameRelated;	//+00
	Skill*	ptFirstSkill;	//+04
	Skill*	ptLeftSkill;	//+08
	Skill*	ptRightSkill;	//+0c
    Skill*	ptCurrentSkill;	//+10
};


/*=================================================================*/
/*   UnitAny Data Structure.                                          */
/*=================================================================*/
struct DrlgRoom2;
struct DrlgRoom1;
struct DrlgMisc;
struct DrlgLevel;

struct RoomTile {
	DrlgRoom2* pRoom2;	//+00
	RoomTile* pNext;	//+04
	DWORD	  _1[2];	//+08
	DWORD* pNum;	//+10
};

struct PresetUnit {
	DWORD	_1;			 //+00
	DWORD	dwTxtFileNo; //+04
	DWORD	dwPosX;		 //+08
	PresetUnit* pNext;   //+0C
	DWORD	_2;			 //+10
	DWORD	dwUnitType;  //+14
	DWORD	dwPosY;		 //+18
};

struct DrlgAct {
	DWORD  _1[4];			//+00
	DrlgRoom1* pRoom1;		//+10
	DWORD	dwActNo;		//+14
	DWORD  _2[12];			//+18
	DrlgMisc* pDrlgMisc;	//+48
};

struct DrlgMisc {
	DWORD	_1[37];				//+00
	DWORD	dwStaffTombLvl;		//+94
	DWORD	_2[248];			//+98
	DWORD* pMemPool;			//+478
	DrlgLevel* pLevelFirst;		//+47C
	DWORD	_3;					//+480
	DWORD	dwBossTombLvl;		//+484
};

struct DrlgLevel {
	DWORD	_1[4];			//+00
	DrlgRoom2* pRoom2First; //+10
	DWORD	_2[102];		//+14
	DrlgLevel* pNext;		//+1AC
	DWORD	_3;				//+1B0
	DrlgMisc* pDrlgMisc;	//+1B4 
	DWORD	_4[2];			//+1B8	
	DWORD	dwLvlType;		//+1C0
	DWORD	_5[3];			//+1C4			
	DWORD	dwLevelNo;		//+1D0
};

struct DrlgRoom2 {
	DWORD   _1[2];			 //+00
	DrlgRoom2** paRoomsNear; //+08
	DWORD   _2[5];			 //+0C
	struct {
		DWORD dwDef;
	}	*pLvlPreset;		 //+20
	DrlgRoom2* pNext;		 //+24
	DWORD   dwRoomTiles;	 //+28
	DWORD	dwRoomsNear;	 //+2C
	DrlgRoom1* pRoom1;	     //+30
	DWORD	dwPosX;			 //+34
	DWORD	dwPosY;			 //+38
	DWORD	dwSizeX;		 //+3C
	DWORD	dwSizeY;		 //+40
	DWORD   _4;				 //+44
	DWORD	dwPresetType;	 //+48
	RoomTile* pRoomTiles;	 //+4C
	DWORD   _5[2];			 //+50
	DrlgLevel* pDrlgLevel;	 //+58
	PresetUnit* pPresetUnits;//+5C	
};

struct Act
{
	int ActNum;			                   // 0x00
	DrlgRoom1* ptFirstRoom;		                   // 0x04
	DrlgMisc* ptMisc;			                   // 0x08
	DWORD _1[2];			                   // 0x0C
	BYTE* _2;			                   // 0x14
	//__fastcall int(*pfnRoomCallBack)(DWORD, DWORD);    // 0x18 act callback.
	DWORD pfnActCallBack;                              // 0x18
	DWORD _4[4];                                       // 0x1C
};

struct DrlgRoom1 {
	DrlgRoom1** paRoomsNear; //+00
	DWORD   _1[3];			 //+04				
	DrlgRoom2* pRoom2;		 //+10
	DWORD	_2[4];			 //+14
	DWORD	dwRoomsNear;	 //+24
	UnitAny* _3[19];			 //+28
	UnitAny* pUnitFirst;
	Act* ptAct;			 //+78
	DrlgRoom1* pNext;		 //+7C
};

struct ActMap//ptGame+BC size=0x60
{
	DWORD	isNotManaged;
	DWORD	uk4;
	DWORD	uk8;//size = 0x488
	DrlgRoom1*	ptFirstRoom;
};

struct NetClient;
//ptGame : 04E4007C
struct GameStruct
{                              			//Offset from Code.
	BYTE	uk1[0x18];					//+00
	DWORD	_ptLock;					//+18 Unknown  
	DWORD	memoryPool;					//+1C Memory Pool (??)  
	BYTE	uk2[0x4D];					//+20
	BYTE	difficultyLevel;			//+6D (Difficulty 0,1 or 2)
	WORD	unknown1;					//+6E Cube puts 4 here
	DWORD	isLODGame;					//+70 (D2=0 LOD =1) (DWORD ?)
	BYTE	uk3[0x04];					//+71
	WORD	unknown2;					//+78
	BYTE	uk4[0x0E];					//+7A
	NetClient* ptClientLastJoined;				//+88
	DWORD	nClient;						//+8C
	DWORD	uk90[11];					//+90
	ActMap*	mapAct[5];					//+BC
	BYTE	ukD0[0x1024];				//+D0
	DWORD*	game10F4;					//+10F4
	NetClient** ptClientList;			//+10F8
	BYTE	uk6[0x24];					//+10FC
	UnitAny*	units[0xA00];				//+1120
	UnitAny*	roomtitles[0x200];			//+1B20
};
//class Game
//	+ 0018 - pCriticalSection(see MSDN please)
//	+ 001C - pMemPool - not used, always NULL
//	+ 006A - GameType - whenever this is single player(etc)
//	+ 006D - DifficultyLevel
//	0 = NORMAL
//	1 = NIGHTMARE
//	2 = HELL
//	+ 0070 - bExpansion
//	0 = CLASSIC
//	1 = EXPANSION
//	+ 0074 - GameType - similar to + 06A, this seams to be more related to ladder vs.non ladder(single player is ladder)
//	+ 0078 - ItemFormat(word)
//	0 = LEGACY
//	1 = CLASSIC
//	101 = EXPANSION
//	+ 007C - InitSeed
//	+ 0080 - ObjSeed - seed used for object spawning
//	+ 0084 - InitSeed(another instance, dunno why)
//	+ 0088 - pClientList - (pClient structure of last player that entered the game)
//	+ 008C - nClients
//	+ 0090 - nUnits[eType] - array of 6 counters, one for each unit type, this is the next GUID used too
//	+ 00A8 - GameFrame - the current frame of the game, used for timers(buff duration etc)
//	+ 00B8 - pTimerQueue - a queue of all current active and inactive timers
//	+ 00BC - pDrlgAct[5]
//	+ 00D0 - GameSeed(inlined structure)
//	+ 000 - loSeed
//	+ 004 - hiSeed
//	+ 00D8 - pDrlgRoomList[5]
//	+ 00EC - MonSeed - seed used for monster spawning
//	+ 00F0 - pMonsterRegion[1024] - one pointer for each of the 1024 possible levels
//	+ 10F0 - pObjectControl - a controller holding all object region structs
//	+ 10F4 - pQuestControl - a controller holding all quest info
//	+ 10F8 - pUnitNodes[10] - ten lists of unit node lists, this is used by the AI target seeking code(and other stuff)
//	+ 1120 - pUnitList[eType][128] - 5 lists of 128 lists of units(see pUnit documentation), second index is GUID & 127, BEWARE: since ever, missiles are array #4 and items are array #3 (so type3 = index4 and type4 = index3)
//	+ 1B20 - pTileList - a list for all VisTile units
//	+ 1B24 - UniqueFlags[128] - 128 DWORDS worth of flags that control if a unique item got spawned[room for 4096]
//	+ 1D24 - pNpcControl - a controller holding all npc info(like store inventories, merc list)
//	+ 1D28 - pArenaControl - a controller for arena stuff, functionaland also used in game init
//	+ 00 - nAlternateStartTown
//	+ 08 - dwGameType(when type = 2, use nAlternateStartTown instead of normal town level Id for game start)
//	+ 1D2C - pPartyControl - a controller for all party related stuff
//	+ 1D30 - BossFlags[64] - 64 bytes for handling 512 super unique monsters(if they were spawned etc)
//	+ 1D70 - MonModeData[17] - related to monsters changing mode
//	+ 1DB4 - nMonModeData - counter related to the above
//	+ 1DC4 - nSyncTimer - used to sync events
//	+ 1DE8 - bUberBaal - killed uber baal
//	+ 1DEC - bUberDiablo - killed uber diablo
//	+ 1DF0 - bUberMephisto - killed uber mephisto

struct Path //(8 dword)
{                              			//Offset from Code.		Size: 20
	WORD	wOffsetX;		//+00
	WORD	wPosX;			//+02
	WORD	wOffsetY;		//+04
	WORD	wPosY;			//+06
	DWORD	dwMapPosX;		//+08
	DWORD	dwMapPosY;		//+0C
	WORD	wTargetX;		//+10
	WORD	wTargetY;		//+12
	DWORD	_2[2];			//+14
	DWORD* pRoom1;		//+1C
	DWORD* pRoomUnk;	//+20
	DWORD	_3[3];			//+24
	UnitAny* pUnit;			//+30
	DWORD	dwFlags;		//+34
	DWORD	_4;				//+38
	DWORD	dwPathType;		//+3C
	DWORD	dwPrevPathType;	//+40
	DWORD	dwUnitSize;		//+44
	DWORD	_5[4];			//+48
	UnitAny* pTargetUnit;	//+58
	DWORD	dwTargetType;	//+5C
	DWORD	dwTargetId;		//+60
	BYTE	nDirection;		//+64
};

struct UnitInventory
{                               		//Offset from Code.		Size: 30 ?40
	DWORD	tag;						//+00	= 0x01020304
	BYTE	uk1[0x04];					//+04	=? 0
	UnitAny*	ptChar;						//+08
	UnitAny*	ptItem;						//+0C
	UnitAny* pLastItem;			//+10 
	UnitInventory* pInvInfo;	//+14 list of pointers to equipped gear 
	DWORD	dwInvInfoCount;		//+18 count for above 
	DWORD	dwWeaponId;			//+1C
	UnitAny*	inventory1;					//+20
	BYTE	uk3[0x04];					//+24
	DWORD	currentUsedSocket;			//+28 //Kingpin : a variable to know how many sockets that have added to item
	DWORD	Inventory2C;				//+2C //one value
	DWORD	Inventory30;				//+30
	void*	ptCorpse;					//+34
	BYTE	uk5[0x04];					//+38
	DWORD	nextCorpseId;				//+3C //max = 15
	BYTE	uk6[0x04];					//+40
};

struct StatEx
{
	WORD	index;
	WORD	id;
	int		value;
};

struct StatsList				//sizeof(StatsList)=0x64
{
	DWORD	nMemoryPool;				//+00
	UnitAny*	ptUnit;					//+04
	DWORD	nUnitType;				//+08
	DWORD	nAllocUnitID;				//+0C
	union
	{
		DWORD	flags;				//+10
		struct
		{
			DWORD fuk1:13;			//0x00001FFF
			DWORD isDisabled:1;		//0x00002000
			DWORD fuk2:17;			//0x7FFFC000
			DWORD dontUseBaseValue:1;//0x80000000
		};
	};
	DWORD	id;						//+14
	DWORD	uk18;					//+18
	BYTE	uk2[0x08];				//+1C
	StatEx*	ptBaseStatsTable;		//+24
	WORD	nbBaseStats;			//+28
	WORD	sizeOfBaseStatsTable;	//+2A ??
	StatsList*	ptStats;				//+2C
	StatsList* pNextList;		// 0x30
	StatsList* pPrev;			//+34
	BYTE	uk4[0x04];				//+38
	StatsList*	ptAffixStats;			//+3C
	StatsList*	ptNextStats2;			//+40
	union
	{
		UnitAny*	ptChar;				//+44
		UnitAny*	ptItem;
	};
	StatEx*	ptStatsTable;			//+48
	WORD	nbStats;				//+4C
	WORD	sizeOfStatsTable;		//+4E ??
	BYTE	uk5[0x8];				//+50
	BYTE*	unknow0;				//+58 (sizeof(*unknow0)=0x30 (calculated)
	DWORD	unknow1;				//+5C (=0)
	DWORD	unknow2;				//+60 (=0)
};

struct MonsterData {
	DWORD* pMonsterTxt;	//+00
	BYTE	nComponents[16];	//+04	Order: HD, TR, LG, RA, LA, RH, LH, SH, S1, S2, S3, S4, S5, S6, S7, S8
	WORD	wNameSeed;			//+14;
	union {
		BYTE	bTypeFlags;	//+16
		struct {
			BYTE fOther : 1;		//set for some champs, uniques
			BYTE fUnique : 1;		//super unique
			BYTE fChamp : 1;
			BYTE fBoss : 1;		//unique monster ,usually boss
			BYTE fMinion : 1;
			BYTE fPoss : 1;		//possessed
			BYTE fGhost : 1;		//ghostly
			BYTE fMulti : 1;		//multishotfiring
		}; //+16
	};//+16
	BYTE	nLastMode;			//+17
	DWORD	dwDuriel;			//+18
	BYTE	anEnchants[9];		//+1C
	BYTE	_1;					//+25
	WORD	wUniqueNo;			//+26	hcIdx from superuniques.txt for superuniques 
	void* pAiGeneral;		//+28
	wchar_t* wszMonName;		//+2C	server side is pAiParams
	BYTE	_2[16];				//+30
	DWORD	dwNecroPet;			//+40
	BYTE	_3[16];				//+44
	DWORD	dwAiState;			//+54	this is used to tell monsters what special state has been set, this tells them they just got attacked etc
	DWORD	dwLevelNo;			//+58	the Id from levels.txt of the level they got spawned in 
	BYTE	nSummonerFlags;		//+5C	byte used only by the summoner
};

struct ObjectData
{
	ObjectsBIN*	ptObjectsBIN;
	BYTE		levelID;
};
/*
Kingpin: struct MonsterData   
{  
     BYTE     uk1[0x13];          // +00  
     DWORD     Flags;               // +14  
     DWORD     uk2;               // +18  
     DWORD     MinionOwnerID;     // +1C  
     BYTE     uk3[0x5];          // +20  
     WORD     SuperUniqueID;     // +26 Superunique ID of monster  
     D2Game*     ptGame;               // +28 ptGame  
};
*/

#define F2_ITEM_IS_IDENTIFIED 0x10 //or F_IS_IDENTIFIED ?

struct ItemData//size=0x74
{										//Offset from Code.
	DWORD	quality;					//+00
	DWORD	seedLow;					//+04
	DWORD	seedHi;						//+08
	DWORD	playerID;					//+0C #10734 / #10735 (PCInventory->ptPlayer->0C)
	DWORD	seedStarting;				//+10
	DWORD	flags1;						//+14
	union {
		DWORD	flags2;					//+18
		struct {
			DWORD	fuk1:1;				//0x00000001
			DWORD	isIndentified:1;	//0x00000002
			DWORD	fuk2:2;				//0x0000000C
			DWORD	isUnindentified:1;	//0x00000010
			DWORD	fuk3:3;				//0x000000E0
			DWORD	isBroken:1;			//0x00000100
			DWORD	fuk4:2;				//0x00000600
			DWORD	isSocketed:1;		//0x00000800
			DWORD	fuk5:10;			//0x003FF000
			DWORD	isEtheral:1;		//0x00400000
			DWORD	fuk6:3;				//0x03800000
			DWORD	isRuneword:1;		//0x04000000
			DWORD	fuk7:1;				//0x08000000
			DWORD	isPersonalized:1;	//0x10000000
			DWORD	fuk8:3;				//0xE0000000
		};
	};
/*
ITEMFLAG_NEWITEM               = 0x00000001,  
ITEMFLAG_TAGETING               = 0x00000004,  
ITEMFLAG_UNIDENTIFIED               = 0x00000010,  
ITEMFLAG_QUANTITY               = 0x00000020,  
ITEMFLAG_Durability               = 0x00000100,  
ITEMFLAG_UNKNOWN2               = 0x00000400,  
ITEMFLAG_SOCKETED               = 0x00000800,  
ITEMFLAG_NON_SELLABLE               = 0x00001000,  
ITEMFLAG_NEWITEM2               = 0x00002000,  
ITEMFLAG_UNKNOWN3               = 0x00004000,  
ITEMFLAG_CHECKSECPRICE               = 0x00010000,  
ITEMFLAG_CHECKGAMBLEPRICE          = 0x00020000,  
ITEMFLAG_UNKNOWN4               = 0x00080000,  
ITEMFLAG_INDESTRUCTIBLE(ETHERAL) = 0x00400000,  
ITEMFLAG_UNKNOWN5               = 0x00800000,  
ITEMFLAG_FROMPLAYER               = 0x01000000,  
ITEMFLAG_RUNEWORD               = 0x04000000
*/
	DWORD	guid1;						//+1C Global Unique ID 1  
	DWORD	guid2;						//+20 Global Unique ID 2  
	DWORD	guid3;						//+24 Global Unique ID 3  
	DWORD	uniqueID;					//+28
	BYTE	ilvl;						//+2C
	BYTE	uk1[0x03];					//+2D
	WORD	version;					//+30
	WORD	rarePrefix;					//+32
	WORD	rareSuffix;					//+34
	WORD	autoPref;					//+36
	WORD	prefix[3];					//+38
	WORD	suffix[3];					//+3E
	BYTE	equipLoc;					//+44
    /*	emplacement si Èquip?
	*	00 = noequip/inBelt
	*   01 = head
	*	02 = neck
	*	03 = tors
	*	04 = rarm
	*	05 = larm
	*	06 = lrin
	*	07 = rrin
	*	08 = belt
	*	09 = feet
	*	0A = glov
	*	0B = ralt
	*	0C = lalt
*/
	BYTE	page;						//+45
    /*	page dans laquel se trouve l'item
    *	FF = mouse/equip/onEarth
    *	00 = inventory
    *   01 = cube
    *	04 = stash
    */
	BYTE	uk4[0x01];					//+46
	BYTE	ItemData3;					//+47 //D2Common10854 D2Common10853
	BYTE	pEarLevel;					//+48
	BYTE	varGfx;						//+49
	char	IName[0x12];				//+4A //inscribed/ear name  
	UnitInventory*	ptInventory;			//+5C
	UnitAny*	ptPrevItem;					//+60
	UnitAny*	ptNextItem;					//+64
	BYTE	uk8[0x01];					//+68
	BYTE	ItemData2;					//+69
	BYTE	uk9[0x0A];					//+6A
};

//class ItemData
//	+ 000 - qualityNo;
//0 - QUALITY_INVALID
//1 - QUALITY_LOW
//2 - QUALITY_NORMAL
//3 - QUALITY_SUPERIOR
//4 - QUALITY_MAGIC
//5 - QUALITY_SET
//6 - QUALITY_RARE
//7 - QUALITY_UNIQUE
//8 - QUALITY_CRAFTED
//9 - QUALITY_TAMPERED
//+ 004 - ItemSeed
//+ 000 - LoSeed
//+ 004 - HiSeed
//+ 00C - OwnerGUID(-1 when not owned by player, otherwise equal to player GUID[IIRC])
//+ 010 - FingerPrint - this is the initial spawning seed
//+ 014 - CommandFlags - I've not seen how this is used myself yet
//+ 018 - ItemFlags - for more flags look at the original topic by Kingpin
//0x00000010 - ITEMFLAG_IDENTIFIED
//0x00000800 - ITEMFLAG_SOCKETED
//0x00008000 - ITEMFLAG_NAMED(for ears, personalized items etc)
//0x00020000 - ITEMFLAG_INEXPENSIVE(always costs 1 for repair / sell)
//0x00200000 - ITEMFLAG_COMPACTSAVE
//0x00400000 - ITEMFLAG_ETHEREAL
//0x04000000 - ITEMFLAG_RUNEWORD
//+ 024 - ActionStamp - seams to be changed every time an action is done with the item
//+ 028 - FileIndex - index from data files
//UniqueItems.txt, SetItems.txt, QualityItems.txt, LowQualityItems.txt(etc)
//+ 02C - iLvl
//+ 030 - ItemFormat - read from pGame->ItemFormat(word) on creation
//+ 032 - RarePrefix(word)
//+ 034 - RareSuffix(word)
//+ 036 - AutoPrefix(word)
//+ 038 - MagicPrefix[3](words)
//+ 03E - MagicSuffix[3](words)
//+ 044 - BodyLoc(byte) - Id from BodyLocs.txt, note this field isn't always cleared, use D2Common.#11003 instead of checking this
//+ 045 - InvPage(byte) - set to - 1 when equipped
//0 = INVPAGE_INVENTORY
//3 = INVPAGE_HORADRIC_CUBE
//4 = INVPAGE_STASH
//+ 048 - EarLevel(byte)
//+ 049 - InvGfxIdx(byte) - for itemtypes with VarInvGfx
//+ 04A - szPlayerName[16] - used for Earsand Personalized items
//+ 05C - pNodeOwnerInventory - for socketed items this points to the inventory of the parent item
//+ 064 - pNextSocketedItem - item filling the next socket, if pNodeOwnerInventory is set
//+ 068 - nNodePosition
//+ 069 - nNodePositionOther

//struct D2ClientStrc
//{
//	DWORD dwClientId;						//0x000
//	DWORD dwClientState;					//0x004
//	BYTE __008[2];							//0x008
//	BYTE nFlags;							//0x00A
//	BYTE __00B[2];							//0x00B
//	char szName[16];						//0x00D
//	char szAccount[16];						//0x01D
//	BYTE __01D[319];						//0x02D
//	DWORD dwUnitType;						//0x16C
//	DWORD dwUnitGUID;						//0x170
//	D2UnitStrc* pPlayer;					//0x174
//	DWORD __178[12];						//0x178
//	D2GameStrc* pGame;						//0x1A8
//	DWORD dwAct;							//0x1AC
//	DWORD __1B0;							//0x1B0
//	D2RoomStrc* pRoom;						//0x1B4
//	D2GsPacketStrc* pPacketData[3];			//0x1B8
//	DWORD __1C4[132];						//0x1C4
//	DWORD dwFlags;							//0x3D4
//	DWORD dwLastPacketTick;					//0x3D8
//	D2ClientKeySkillStrc HotkeySkills[16];	//0x3DC
//	WORD nSwitchWeapon;						//0x45C
//	WORD __45E;								//0x45E
//	char szClanTag[4];						//0x460
//	char szClanName[7];						//0x470
//	DWORD dwInactivityTime;					//0x48C
//	WORD nHitpoints;						//0x490
//	WORD nManaPoints;						//0x492
//	WORD nStaminaPoints;					//0x494
//	BYTE nPotionLifePercent;				//0x496
//	BYTE nPotionManaPercent;				//0x497
//	WORD nPosX;								//0x498
//	WORD nPosY;								//0x49A
//	WORD nTargetOffsetX;					//0x49C
//	WORD nTargetOffsetY;					//0x49E
//	DWORD dwBeltGold;						//0x4A0
//	DWORD dwExperience;						//0x4A4
//	D2ClientStrc* pNext;					//0x4A8
//	D2ClientStrc* pListNext;				//0x4AC
//	D2ClientStrc* pNextByName;				//0x4B0
//	DWORD __4B4[19];						//0x4B4
//	DWORD dwSentPings;						//0x500
//	DWORD __504;							//0x504
//	DWORD dwExpLost;						//0x508
//	DWORD dwLangId;							//0x50C
//	DWORD __510[2];							//0x510
//};

struct NetClient
{
	DWORD	clientID;					//+00
	BYTE	uk1[0x06];					//+04
	union {								//+0A
		WORD	flag;
		struct {
			WORD f1 : 1;
			WORD f2 : 1;
			WORD isHardCoreGame : 1;
		};
	};
	BYTE	uk2;						//+0C
	char	name[0x10];					//+0D
	BYTE	uk3[0x15F];					//+1D
	BYTE* savefile;					//+17C
	DWORD	finalSize;					//+180
	DWORD	counter;					//+184
	DWORD	currentSize;				//+188
	BYTE	uk4[0x1C];					//+18C
	GameStruct* ptGame;					//+1A8
	DWORD  unk5[0xBF];					//+1AC
	NetClient* pNext;					//+4A8
	NetClient* pListNext;				//0x4AC
	NetClient* pNextByName;				//0x4B0
	DWORD __4B4[19];						//0x4B4
	DWORD dwSentPings;						//0x500
	DWORD __504;							//0x504
	DWORD dwExpLost;						//0x508
	DWORD dwLangId;							//0x50C
	DWORD __510[2];							//0x510
/*
Kingpin: ptPclient  
+16C is either act or unit type 
+170 Active UniqueID for player 
+174 Active ptPlayer on Client 
+1a8 ptGame 
+1b4 Current or next ptRoom  
*/
};

struct Stash
{
	DWORD id;
	union {
		DWORD flags;
		struct {
			DWORD isShared : 1;	//
			DWORD isIndex : 1;	//
			DWORD isMainIndex : 1;	//
			DWORD isReserved : 1;	// For swap items comand
		};
	};
	char* name;
	UnitAny* ptListItem;
	Stash* previousStash;
	Stash* nextStash;
};

struct PYPlayerData
{
	union {
		DWORD flags;
		struct {
			DWORD selfStashIsOpened : 1;	//
			DWORD sharedStashIsOpened : 1;//
			DWORD showSharedStash : 1;	//
//			DWORD notOnRealm:1;			//set to 1 when the player is load from client or in SP
		};
	};
	DWORD	sharedGold;
	DWORD	nbSelfPages;
	DWORD	nbSharedPages;
	Stash* currentStash;
	Stash* selfStash;
	Stash* sharedStash;
};

struct QuestInfo {
	DWORD* pBuffer;					//0x00
	DWORD _flag;
};

struct Waypoint {
	DWORD flags;					//0x00
};

struct PlayerData
{
	char		name[0x10];				//+00	Player Name  
	QuestInfo* ptQuest[3];				//+10	Quest Pointers for each difficulty  
	Waypoint* pWaypoints[3];				//+1C
	BYTE		uk1[0xC];				//+28		//before : 0x14
	void* ptArenaUnit;			//+34	ptArena for the UnitAny  
	BYTE		uk2[0x4];				//+38		//before : 0x7
	WORD		MPSourcePortalUniqueID;	//+3C	Source Portal Unique_ID  
	BYTE		uk3[0x2];				//+3E
	WORD		MPDestPortalUniqueID;	//+40	Destination Portal Unique_ID  
	BYTE		uk4[0x06];				//+42  
	BYTE		ptObjectUnID;			//+48	Object UniqueID for TownPortals       
	BYTE		uk5[0x53];				//+49  
	NetClient* ptNetClient;			//+9C	ptClient  
	DWORD		unk6[0x33];				//+A0
	PYPlayerData ptPYPlayerData;		//+16C
};

struct StaticPath {
	DWORD* pRoom1;		//+1C
	DWORD	dwMapPosX;		//+04
	DWORD	dwMapPosY;		//+08
	DWORD	dwPosX;			//+0C
	DWORD	dwPosY;			//+10
};

struct DynamicPath {
	WORD	wOffsetX;		//+00
	WORD	wPosX;			//+02
	WORD	wOffsetY;		//+04
	WORD	wPosY;			//+06
	DWORD	dwMapPosX;		//+08
	DWORD	dwMapPosY;		//+0C
	WORD	wTargetX;		//+10
	WORD	wTargetY;		//+12
	DWORD	_2[2];			//+14
	DWORD* pRoom1;		//+1C
	DWORD* pRoomUnk;	//+20
	DWORD	_3[3];			//+24
	UnitAny* pUnit;			//+30
	DWORD	dwFlags;		//+34
	DWORD	_4;				//+38
	DWORD	dwPathType;		//+3C
	DWORD	dwPrevPathType;	//+40
	DWORD	dwUnitSize;		//+44
	DWORD	_5[4];			//+48
	UnitAny* pTargetUnit;	//+58
	DWORD	dwTargetType;	//+5C
	DWORD	dwTargetId;		//+60
	BYTE	nDirection;		//+64
};

#define F1_IS_SPAWNED 0x10 //or F_IS_IDENTIFIED ?
#define F2_IS_LOD 0x2000000
enum PlayerEMode
{
	Death,
	Neutral,
	Walk,
	Run,
	GetHit,
	TownNeutral,
	TownWalk,
	Attack1,
	Attack2,
	Block,
	Cast,
	Throw,
	Kick,
	Skill1,
	Skill2,
	Skill3,
	Skill4,
	Dead,
	Sequence,
	Knockback
};
struct UnitAny
{										//Offset from Code.		Size: 0xF4+4
	DWORD		nUnitType;				//+00
	union{
		DWORD			nPlayerClass;
		DWORD			dwTxtFileNo;         
    };									//+04
	DWORD		nMemoryPool;				//+08
	DWORD		nAllocUnitID;				//+0C
	DWORD		CurrentAnim;			//+10
	union{
		MonsterData*	ptMonsterData;
		ObjectData*		ptObjectData;
		ItemData*		ptItemData;
		PlayerData*		ptPlayerData;
	};									//+14
	BYTE		act;					//+18
	BYTE		uk12[3];				//+19
	void*		ptAct;					//+1C
	DWORD		SeedLow;				//+20
	DWORD		SeedHi;					//+24
	DWORD		SeedStarting;			//+28
	union {
		StaticPath* pItemPath;	//	(Objects, VisTiles, Items) 
		DynamicPath* pMonPath;	//	(Players, Monsters, Missiles) 
	};	//+2C
	BYTE		uk1[0x08];				//+30
	Path*		ptPos;					//+38
	DWORD		animSpeed;				//+3C
	BYTE		uk2[0x04];				//+40
	DWORD		curFrame;				//+44
	DWORD		remainingFrame;			//+48
	WORD		animSpeedW;				//+4C
	BYTE		actionFlag;				//+4E
	BYTE		uk3[0x1];				//+4F
	void*		ptAnimData;				//+50
	BYTE		uk4[0x08];				//+54
	StatsList*		ptStats;				//+5C
	UnitInventory*	ptInventory;		    //+60
	DWORD		uk5[7];				//+64
	GameStruct*		ptGame;					//+80
	DWORD		uk6[4];				//+84
	DWORD	dwOwnerType;	//+94
	DWORD	dwOwnerId;		//+98
	DWORD	_3[3];		//+9C
	SkillInfo*		ptSkills;				//+A8
	void*		ptCombatData;			//+AC
	BYTE		uk7[0x08];				//+B0
	DWORD		itemCode;				//+B8 for an item being dropped by this unit
	BYTE		uk8[0x08];				//+BC
	DWORD		flags1;					//+C4
	union{
		DWORD		flags2;				//+C8	//flags
		struct{
			DWORD	ukf1:25;
			DWORD	isLod:1;
		};
	};
	BYTE		uk9[0x04];				//+CC
	DWORD		clientId;				//+D0
	BYTE		uk10[0x0C];				//+D4
	UnitAny*		ptFirstMonster;			//+E0
	UnitAny*		Unit1;					//+E4
	UnitAny*		Unit2;					//+E8
	BYTE		uk11[0x08];				//+EC
	union{
		CBPlayerData*	ptCBPlayerData;
		CBItemData*		ptCBItemData;
		void*			ptCBData;
	};									//+F4
};



struct DamageData
{
	/*
	0x04
	0x00000001 - HITFLAG_SRCDAMAGE_MISSILE
	0x00000002 - HITFLAG_SUCCESSFUL_CRITICAL_HIT
	0x00000010 - HITFLAG_FRIENDLY_FIRE
	0x00000020 - HITFLAG_SRCDAMAGE_MELEE
	0x00000100 - HITFLAG_BYPASS_UNDEAD
	0x00000200 - HITFLAG_BYPASS_DEMONS
	0x00000400 - HITFLAG_BYPASS_BEASTS
	*/
	DWORD dwHitFlags;			//0x00
	/*
	0x04
	0x00000001 - RESULTFLAG_HIT
	0x00000002 - RESULTFLAG_DEATH
	0x00000004 - RESULTFLAG_GETHIT
	0x00000008 - RESULTFLAG_KNOCKBACK
	0x00000010 - RESULTFLAG_BLOCK
	0x00000020 - RESULTFLAG_DISALLOW_EVENTS
	0x00000100 - RESULTFLAG_DODGE
	0x00000200 - RESULTFLAG_AVOID
	0x00002000 - RESULTFLAG_SOFTHIT
	0x00008000 - RESULTFLAG_WEAPONBLOCK
	*/
	WORD wResultFlags;			//0x04
	WORD fExtra;				//0x06
	LONG dwPhysDamage;			//0x08-ŒÔ¿Ì…À∫¶
	LONG dwEnDmgPct;			//0x0C
	LONG dwFireDamage;			//0x10-ª—Ê…À∫¶
	LONG dwBurnDamage;			//0x14
	LONG dwBurnLen;			//0x18
	LONG dwLtngDamage;			//0x1C-…¡µÁ…À∫¶
	LONG dwMagDamage;			//0x20-ƒß∑®…À∫¶
	LONG dwColdDamage;			//0x24-±˘¿‰…À∫¶
	LONG dwPoisDamage;			//0x28-∂æÀÿ…À∫¶
	DWORD dwPoisLen;			//0x2C
	DWORD dwColdLen;			//0x30
	DWORD dwFrzLen;				//0x34
	DWORD dwLifeLeech;			//0x38
	LONG dwManaLeech;			//0x3C
	DWORD dwStamLeech;			//0x40
	DWORD dwStunLen;			//0x44
	DWORD dwAbsLife;			//0x48
	DWORD dwDmgTotal;			//0x4C
	DWORD unk0x50;				//0x50
	DWORD dwPiercePct;			//0x54
	DWORD dwDamageRate;			//0x58
	DWORD unk0x5C;				//0x5C
	DWORD dwHitClass;			//0x60
	BYTE bHitClassActiveSet;		//0x64
	char nConvType;				//0x65
	BYTE unk0x66[2];			//0x66
	DWORD dwConvPct;			//0x68
	BYTE unk0x6C[4];			//0x6C
};
