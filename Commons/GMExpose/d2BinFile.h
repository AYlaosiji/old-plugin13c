#pragma once

enum D2CubeItemFlag  
{  
	CUBE_COWPORTAL		=1,
	CUBE_USEITEM		=0xFF,
	CUBE_USETYPE		=0xFE,
	CUBE_TYPE			=0xFD,
	CUBE_ITEM			=0xFC
};

struct CubeOutput//size: 0x54=84
{
	union
	{
		WORD flag;														//+00
		struct 
		{
			WORD	keepModifiers : 1;							//",mod"
			WORD	haveSockets : 1;								//",sock=#nbsocket"
			WORD	isEthereal : 1;									//",eth"
			WORD	isSpecificItem : 1;							//"#itemUniqueName" or "#itemSetName" (set byItemID too)
			WORD	destroysFillers : 1;							//",uns"
			WORD	removeFillers : 1;							//",rem"
			WORD	regeneratesUnique : 1;					//",reg"
			WORD	upgradeToExceptional : 1;				//",exc"
			WORD	upgradeToElite : 1;							//",eli"
			WORD	repair : 1;											//",rep"
			WORD	recharge : 1;										//",rch"
		};
	};
	WORD	ID;															//+02
	WORD	specificID;												//+04
	BYTE	quality;														//+06	1=",low"; 2=",nor"; 3=",hiq"; 4=",mag"; 5=",set"; 6=",rar"; 7=",uni"; 8=",crf"; 9=",tmp"
	BYTE	quantityOrNbSockets;									//+07	",qty=#quantity" Or ",sock=#nbsocket"
	BYTE	outputType;													//+08	02="Pand. Portal" 01="Cow Portal" FF="usetype"; FE="useitem" FC="#item4Code" FD="#type4Code"
	BYTE	lvl;																//+09
	BYTE	plvl;																//+0A
	BYTE	ilvl;																//+0B
	WORD	Prefix;														//+0C
	WORD	PrefixMin;												//+0E (always 0)
	WORD	PrefixMax;												//+10 (always 0)
	WORD	Suffix;														//+12
	WORD	SuffixMin;												//+14 (always 0)
	WORD	SuffixMax;												//+16 (always 0)
	DWORD	mod1;														//+18
	WORD	mod1param;											//+1C
	WORD	mod1min;												//+1E
	WORD	mod1max;												//+20
	BYTE	mod1chance;												//+22	//+6E
	DWORD	mod2;														//+24	//+70
	WORD	mod2param;											//+28	//+74
	WORD	mod2min;												//+2A	//+76
	WORD	mod2max;												//+2C	//+78
	BYTE	mod2chance;												//+2E	//+7A
	DWORD	mod3;														//+30	//+7C
	WORD	mod3param;											//+34	//+80
	WORD	mod3min;												//+36	//+82
	WORD	mod3max;												//+38	//+84
	BYTE	mod3chance;												//+3A	//+86
	DWORD	mod4;														//+3C	//+88
	WORD	mod41param;											//+40	//+8C
	WORD	mod4min;												//+42	//+8E
	WORD	mod4max;												//+44	//+90
	BYTE	mod4chance;												//+46	//+92
	DWORD	mod5;														//+48	//+94
	WORD	mod5param;											//+4C	//+98
	WORD	mod5min;												//+4E	//+9A
	WORD	mod5max;												//+50	//+9C
	BYTE	mod5chance;												//+52	//+9E
};


struct CubeInput//size: 8 (source total : fct of dll)
{
	union {
		WORD flag;			//+00
		struct {
			WORD	byItemID:1;					//"#item4Code" or "any"
			WORD	byItemTypeID:1;				//"#itemType4Code"
			WORD	haveNoSocket:1;				//",nos"
			WORD	haveSockets:1;				//",sock"
			WORD	isEthereal:1;				//",eth"
			WORD	isNotEthereal:1;			//",noe"
			WORD	isSpecificItem:1;			//"#itemUniqueName" or "#itemSetName" (set byItemID too)
			WORD	includeUpgradedVersions:1;	//",upg"
			WORD	isBasic:1;					//",bas"
			WORD	isExceptional:1;			//",exc"
			WORD	isElite:1;					//",eli"
			WORD	isNotRuneword:1;			//",nru"
		};
	};
	WORD	ID;				//+02	FFFF = any items
	WORD	specificID;		//+04
	BYTE	quality;		//+06	1=",low"; 2=",nor"; 3=",hiq"; 4=",mag"; 5=",set"; 6=",rar"; 7=",uni"; 8=",crf"; 9=",tmp"
	BYTE	quantity;		//+07	",qty=#quantity"
};


struct CubeMainBIN//size: 0x148=328  (source total : fct of dll) (total size in LoD1.10 : BDA0)
{
	BYTE		enabled;	//+00
	BYTE		ladder;		//+01
	BYTE		minDiff;	//+02
	BYTE		playerClass;//+03 FF=all classes
	BYTE		op;			//+04
	DWORD		param;		//+08
	DWORD		value;		//+0C
	BYTE		numinputs;	//+10
	WORD		version;	//+12
	CubeInput	input1;		//+14
	CubeInput	input2;		//+1C
	CubeInput	input3;		//+24
	CubeInput	input4;		//+2C
	CubeInput	input5;		//+34
	CubeInput	input6;		//+3C
	CubeInput	input7;		//+44
	CubeOutput	output1;	//+4C
	CubeOutput	output2;	//+A0
	CubeOutput	output3;	//+F4
};

struct TreasureClassBIN
{
	UnitAny* p1;
	UnitAny* p2;
	UnitAny* p3;
	UnitAny* p4;
	UnitAny* p5;
	UnitAny* p6;
	UnitAny* p7;
	UnitAny* p8;
	UnitAny* p9;
	UnitAny* p10;
	UnitAny* p11;
	UnitAny* p12; 
	UnitAny* p13;
	UnitAny* p14;
	UnitAny* p15;
	UnitAny* p16;
	UnitAny* p17;
};

struct ObjectsBIN//size=0x1C0
{
	char	szName[64];			//+00
	wchar_t wszName[64];		//+40
	char	szToken[3];			//+C0
	BYTE	nSpwanMax;			//+C3
	BYTE	nSelectable[8];		//+C4
	WORD	wTrapProp;			//+CC
	BYTE	_1[2];				//+CE
	DWORD	dwSizeX;			//+D0
	DWORD	dwSizeY;			//+D4
	DWORD	dwFrameCnt[8];		//+D8	–Ë“™”““∆8Œª
	WORD	wFrameDelta[8];		//+F8
	BYTE	nCycleAnim[8];		//+108
	BYTE	nLit[8];			//+110
	BYTE	nBlockLight[8];		//+118
	BYTE	nHasCollision[8];	//+120
	BYTE	fAttackable;		//+128
	BYTE	nStrart[8];			//+129
	BYTE	nOrderFlag[8];		//+131
	BYTE	nEnvEffect;			//+139
	BYTE	nIsDoor;			//+13A
	BYTE	nBlocksVis;			//+13B
	BYTE	nOrientation;		//+13C
	BYTE	nPreOperate;		//+13D
	BYTE	nTrans;				//+13E
	BYTE	nMode[8];			//+13F
	BYTE	_2;					//+147
	DWORD	dwXoffset;			//+148
	DWORD	dwYoffset;			//+14C
	BYTE	nDraw;				//+150
	BYTE	nHd;				//+151
	BYTE	nTR;				//+152
	BYTE	nLG;				//+153
	BYTE	nRA;				//+154
	BYTE	nLA;				//+155
	BYTE	nRH;				//+156
	BYTE	nLH;				//+157
	BYTE	nSH;				//+158
	BYTE	nS[8];				//+159	S1-S8
	BYTE	nTotalPieces;		//+161
	BYTE	nXSpace;			//+162
	BYTE	nYSpace;			//+163
	BYTE	nRed;				//+164
	BYTE	nGreen;				//+165
	BYTE	nBlue;				//+166
	BYTE	nSubClass;			//+167
	DWORD	dwNameOffset;		//+168
	BYTE	_3[2];				//+16C
	BYTE	nOperateRange;		//+16E
	BYTE	nShrineFnc;			//+16F
	BYTE	nAct;				//+170
	BYTE	_4[7];				//+171
	DWORD	dwParm[8];			//+178
	BYTE	_5[4];				//+198
	BYTE	nDamage;			//+19C
	BYTE	_6[3];				//+19D
	DWORD	dwLeft;				//+1A0
	DWORD	dwTop;				//+1A4
	DWORD	dwWidth;			//+1A8
	DWORD	dwHeight;			//+1AC
	BYTE	_7;					//+1B0
	BYTE	nInitFn;			//+1B1
	BYTE	nPopulateFn;		//+1B2
	BYTE	nOperateFn;			//+1B3
	BYTE	nClientFn;			//+1B4
	BYTE	_8[7];				//+1B5
	DWORD	nAutoMap;			//+1BC
};

struct LevelsBIN//size=0x220
{
	WORD wLevelNo;						//0x00
	BYTE nPal;							//0x02
	BYTE nAct;							//0x03
	BYTE nTeleport;						//0x04
	BYTE nRain;							//0x05
	BYTE nMud;							//0x06
	BYTE nNoPer;						//0x07
	BYTE nIsInside;						//0x08
	BYTE nDrawEdges;					//0x09
	WORD unk0x0A;						//0x0A
	DWORD dwWarpDist;					//0x0C
	WORD wMonLvl1;						//0x10
	WORD wMonLvl2;						//0x12
	WORD wMonLvl3;						//0x14
	WORD wMonLvl1Ex;					//0x16
	WORD wMonLvl2Ex;					//0x18
	WORD wMonLvl3Ex;					//0x1A
	DWORD dwMonDen[3];					//0x1C
	BYTE nMonUMin[3];					//0x28
	BYTE nMonUMax[3];					//0x2B
	BYTE nMonWndr;						//0x2E
	BYTE nMonSpcWalk;					//0x2F
	BYTE nQuest;						//0x30
	BYTE nRangedSpawn;					//0x31
	DWORD dwNumMon;						//0x32
	WORD wMon[25];						//0x36
	WORD wNMon[25];						//0x68
	WORD wUMon[25];						//0x9A
	WORD wCMon[4];						//0xCC
	WORD wCPct[4];						//0xD4
	WORD wCAmt[4];						//0xDC
	BYTE nWaypoint;						//0xE4
	BYTE nObjGroup[8];					//0xE5
	BYTE nObjPrb[8];					//0xED
	char szLevelName[40];				//0xF5
	char szLevelWarp[40];				//0x11D
	char szEntryFile[41];				//0x145
	wchar_t wszLevelName[40];			//0x16E
	wchar_t wszLevelWarp[41];			//0x1BE
	DWORD dwThemes;						//0x210
	DWORD dwFloorFilter;				//0x214
	DWORD dwBlankScreen;				//0x218
	DWORD dwSoundEnv;					//0x21C
};

struct GemsBIN //size: 0xC0=192 (source : fct of dll)
{
	char	name[0x20];		//+00
	char	letter[6];		//+20
	BYTE	uk1[2];			//+26
	DWORD	code;			//+28
	BYTE	uk2[2];			//+2C
	BYTE	nummods;		//+2E
	BYTE	transform;		//+2F
	int		weaponmod1code;	//+30
	DWORD	weaponmod1param;//+34
	DWORD	weaponmod1min;	//+38
	DWORD	weaponmod1max;	//+3C
	int		weaponmod2code;	//+40
	DWORD	weaponmod2param;//+44
	DWORD	weaponmod2min;	//+48
	DWORD	weaponmod2max;	//+4C
	int		weaponmod3code;	//+50
	DWORD	weaponmod3param;//+54
	DWORD	weaponmod3min;	//+58
	DWORD	weaponmod3max;	//+5C
	int		helmmod1code;	//+60
	DWORD	helmmod1param;	//+64
	DWORD	helmmod1min;	//+68
	DWORD	helmmod1max;	//+6C
	int		helmmod2code;	//+70
	DWORD	helmmod2param;	//+74
	DWORD	helmmod2min;	//+78
	DWORD	helmmod2max;	//+7C
	int		helmmod3code;	//+80
	DWORD	helmmod3param;	//+84
	DWORD	helmmod3min;	//+88
	DWORD	helmmod3max;	//+8C
	int		shieldmod1code;	//+90
	DWORD	shieldmod1param;//+94
	DWORD	shieldmod1min;	//+98
	DWORD	shieldmod1max;	//+9C
	int		shieldmod2code;	//+A0
	DWORD	shieldmod2param;//+A4
	DWORD	shieldmod2min;	//+A8
	DWORD	shieldmod2max;	//+AC
	int		shieldmod3code;	//+B0
	DWORD	shieldmod3param;//+B4
	DWORD	shieldmod3min;	//+B8
	DWORD	shieldmod3max;	//+BC
};

struct ItemBIN //size: 0x1A8=424 (source : fct of dll) (nblines : 134 CA 8B) Gold:20B
{  
	char	FlippyFile[0x20];		//+00  
	char	InvFile[0x20];			//+20  
	char	UniqueInvFile[0x20];	//+40  
	char	SetInvFile[0x20];		//+60  
	DWORD	ItemCode;				//+80  
	DWORD	NormCode;				//+84  
	DWORD	UberCode;				//+88  
	DWORD	HellCode;				//+8C  
	DWORD	AlternateGfx;			//+90  
	DWORD	pSpell;					//+94  
	WORD	State;					//+98  
	WORD	cState1;				//+9A  
	WORD	cState2;				//+9C  
	WORD	Stat1;					//+9E  
	WORD	Stat2;					//+A0  
	WORD	Stat3;					//+A2  
	DWORD	Calc1;					//+A4  
	DWORD	Calc2;					//+A8  
	DWORD	Calc3;					//+AC  
	DWORD	Len;					//+B0  
	WORD	SpellDesc;				//+B4  
	WORD	SpellDescStr;			//+B6  
	DWORD	SpellDescCalc;			//+B8  
	DWORD	BetterGem;				//+BC  
	DWORD	WClass;					//+C0  
	DWORD	TwoHandedWClass;		//+C4  
	DWORD	TMogType;				//+C8  
	DWORD	MinAC;					//+CC  
	DWORD	MaxAC;					//+D0  
	DWORD	GambleCost;				//+D4  
	DWORD	Speed;					//+D8  
	DWORD	BitField;				//+DC  
	DWORD	Cost;					//+E0  
	DWORD	MinStack;				//+E4  
	DWORD	MaxStack;				//+E8  
	DWORD	SpawnStack;				//+EC  
	DWORD	GemOffset;				//+F0  
	WORD	NameStr;				//+F4  
	WORD	Version;				//+F6  
	WORD	AutoPrefix;				//+F8  
	WORD	MissileType;			//+FA  
	BYTE	Rarity;					//+FC  
	BYTE	Level;					//+FD  
	BYTE	MinDam;					//+FE  
	BYTE	MaxDam;					//+FF  
	BYTE	MinMisDam;				//+100  
	BYTE	MaxMisDam;				//+101  
	BYTE	TwoHandMinDam;			//+102  
	BYTE	TwoHandMaxDam;			//+103  
	BYTE	RangeAdder;				//+104  
	BYTE	NotUsed1;				//+105  
	WORD	StrBonus;				//+106  
	WORD	DexBonus;				//+108  
	WORD	RegStr;					//+10A  
	WORD	RegDex;					//+10C  
	BYTE	Absorbs;				//+10E  
	BYTE	InvWidth;				//+10F  
	BYTE	InvHeight;				//+110  
	BYTE	Block;					//+111  
	BYTE	Durability;				//+112  
	BYTE	NoDurability;			//+113
	BYTE	Missile;				//+114  
	BYTE	Component;				//+115  
	BYTE	RArm;					//+116  
	BYTE	LArm;					//+117  
	BYTE	Torso;					//+118  
	BYTE	Legs;					//+119  
	BYTE	RSpad;					//+11A  
	BYTE	LSpad;					//+11B  
	BYTE	TwoHanded;				//+11C  
	BYTE	Usable;					//+11D  
	WORD	Type;					//+11E  
	WORD	Type2;					//+120  
	BYTE	SubType;				//+122  
	BYTE	NotUsed2;				//+123  
	WORD	DropSound;				//+124
	WORD	UseSound;				//+126
	BYTE	DropSfxFrame;			//+128
	BYTE	Unique;					//+129
	BYTE	Quest;					//+12A
	BYTE	QuestDiffCheck;			//+12B  
	BYTE	Transparent;			//+12C  
	BYTE	TransTbl;				//+12D  
	BYTE	NotUsed3;				//+12E  
	BYTE	LightRadius;			//+12F  
	BYTE	Belt;					//+130  
	BYTE	AutoBelt;				//+131  
	BYTE	Stackable;				//+132  
	BYTE	Spawnable;				//+133  
	BYTE	SpellIcon;				//+134  
	BYTE	DurWarning;				//+135  
	BYTE	QntWaning;				//+136  
	BYTE	HasInv;					//+137  
	BYTE	GemSockets;				//+138  
	BYTE	TransmoGrify;			//+139  
	BYTE	TMogMin;				//+13A  
	BYTE	TMogMax;				//+13B  
	BYTE	HitClass;				//+13C  
	BYTE	OneOrTwoHanded;			//+13D  
	BYTE	GemApplyType;			//+13E  
	BYTE	LevelReq;				//+13F  
	BYTE	MagicLvl;				//+140  
	BYTE	Transform;				//+141  
	BYTE	InvTrans;				//+142  
	BYTE	CompactSave;			//+143  
	BYTE	SkipName;				//+144  
	BYTE	NotUsed4;				//+145  
	BYTE	VendorMin[17];			//+146  
	BYTE	VendorMax[17];			//+157  
	BYTE	VendorMagicMin[17];		//+168  
	BYTE	VendorMagicMax[17];		//+179  
	BYTE	VendorMagicLvl[17];		//+18A  
	BYTE	NotUsed5;				//+19B  
	DWORD	NightmareUpgrade;		//+19C  
	DWORD	HellUpgrade;			//+1A0  
	BYTE	PermStoreItem;			//+1A4  
	BYTE	Multibuy;				//+1A5  
	WORD	zeros;					//+1A6
};

struct RunesBIN	//size: 0x120=288 (1.10 ok)
{  
	char	Name[0x40];		//+00
	char	RuneName[0x40];	//+40
	BYTE	Complete;		//+80
	BYTE	Server;			//+81
	WORD	RuneNameID;		//+82
	WORD	zero;			//+84 (=0x0000)
	WORD	Itypes[6];		//+86
	WORD	Etypes[3];		//+92
	int		Runes[6];		//+98
	DWORD	t1code1;		//+B0
	DWORD	t1param1;		//+B4
	DWORD	t1min1;			//+B8
	DWORD	t1max1;			//+BC
	DWORD	t1code2;		//+C0
	DWORD	t1param2;		//+C4
	DWORD	t1min2;			//+C8
	DWORD	t1max2;			//+CC
	DWORD	t1code3;		//+D0
	DWORD	t1param3;		//+D4
	DWORD	t1min3;			//+D8
	DWORD	t1max3;			//+DC
	DWORD	t1code4;		//+E0
	DWORD	t1param4;		//+E4
	DWORD	t1min4;			//+E8
	DWORD	t1max4;			//+EC
	DWORD	t1code5;		//+F0
	DWORD	t1param5;		//+F4
	DWORD	t1min5;			//+F8
	DWORD	t1max5;			//+FC
	DWORD	t1code6;		//+100
	DWORD	t1param6;		//+104
	DWORD	t1min6;			//+108
	DWORD	t1max6;			//+10C
	DWORD	t1code7;		//+110
	DWORD	t1param7;		//+114
	DWORD	t1min7;			//+118
	DWORD	t1max7;			//+11C
};

struct CharStatsBIN //size= 0xC4=196
{
	WCHAR	nameU[0x10];
	char	name[0x10];
	BYTE	baseSTR;	//+20
	BYTE	baseDEX;
	BYTE	baseENE;
	BYTE	baseVIT;
	BYTE	baseStamina;
	BYTE	HPAdd;
	BYTE	percentStr;
	BYTE	percentDex;
	BYTE	percentInt;
	BYTE	percentVit;      
	WORD	manaRegen;
	DWORD	toHitFactor;
	BYTE	walkVelocity;//+30
	BYTE	runVelocity;
	BYTE	runDrain;
	BYTE	lifePerLevel;
	BYTE	staminaPerLevel;
	BYTE	manaPerLevel;
	BYTE	lifePerVitality;
	BYTE	staminaPerVitality;
	BYTE	manaPerMagic;
    BYTE	blockFactor;
	WORD	startSkill;
	DWORD	baseWClass;
	DWORD	unknown1[3];
	DWORD	item1;
	BYTE	item1Loc;
	BYTE	item1Count;
	WORD	item1Unknown;
	DWORD	item2;
	BYTE	item2Loc;
	BYTE	item2Count;
	WORD	item2Unknown;
	DWORD	item3;
	BYTE	item3Loc;
	BYTE	item3Count;
	WORD	item3Unknown;
	DWORD	item4;
	BYTE	item4Loc;
	BYTE	item4Count;
	WORD	item4Unknown;
	DWORD	item5;
	BYTE	item5Loc;
	BYTE	item5Count;
	WORD	item5Unknown;
    DWORD	item6;
	BYTE	item6Loc;
	BYTE	item6Count;
	WORD	item6Unknown;
	DWORD	item7;
	BYTE	item7Loc;
	BYTE	item7Count;
	WORD	item7Unknown;
	DWORD	item8;
	BYTE	item8Loc;
	BYTE	item8Count;
	WORD	item8Unknown;
	DWORD	item9;
	BYTE	item9Loc;
	BYTE	item9Count;
	WORD	item9Unknown;
	DWORD	item10;
	BYTE	item10Loc;
	BYTE	item10Count;
	WORD	item10Unknown;
	BYTE	unknown2[0x18]; 
};

struct UniqueItemsBIN //size=0x14C (332)
{
	WORD	uniqueId;		//+00
	BYTE	uk1[0x20];		//+02
	WORD	uniqueNameId;	//+22
	BYTE	uk2[0x08];		//+24
	union {
		BYTE	flag;		//+2C
		struct {
			BYTE ukf:2;
			BYTE carry1:1;
		};
	};
	BYTE	uk3[0x11F];		//+2D
};

struct SetItemsBIN //size=0x1B8 (source : fct of dll)
{
	WORD	setId;			//+00
	char	index[0x20];	//+02
	BYTE	uk1;			//+04
	WORD	setNameId;		//+24
	BYTE	uk2[0x192];		//+26
};

struct SkillDescBIN //size=0x120=288  (source : fct of dll)
{
	BYTE	uk1[0x08];		//+00
	WORD	strNameID;		//+08
	WORD	strShortID;		//+0A
	WORD	strLongID;		//+0C
	WORD	strAltID;		//+0E
	BYTE	uk2[0x110];		//+10
};

struct SkillsBIN //size=0x23C (572)
{
	DWORD dwSkillId; 					//0x00
	DWORD dwFlags[2];					//0x04
	DWORD dwClassId;					//0x0C
	BYTE nAnim;							//0x10
	BYTE nMonAnim;						//0x11
	BYTE nSeqTrans;						//0x12
	BYTE nSeqNum;						//0x13
	BYTE nRange;						//0x14
	BYTE nSelectProc;					//0x15
	BYTE nSeqInput;						//0x16
	BYTE unk0x17;						//0x17
	WORD wITypeA1;						//0x18
	WORD wITypeA2;						//0x1A
	WORD wITypeA3;						//0x1C
	WORD wITypeB1;						//0x1E
	WORD wITypeB2;						//0x20
	WORD wITypeB3;						//0x22
	WORD wETypeA1;						//0x24
	WORD wETypeA2;						//0x26
	WORD wETypeB1;						//0x28
	WORD wETypeB2;						//0x2A
	WORD wSrvStartFunc;					//0x2C
	WORD wSrvDoFunc;					//0x2E
	WORD wSrvPrgFunc1;					//0x30
	WORD wSrvPrgFunc2;					//0x32
	WORD wSrvPrgFunc3;					//0x34
	WORD unk0x36;						//0x36
	DWORD dwPrgCalc1;					//0x38
	DWORD dwPrgCalc2;					//0x3C
	DWORD dwPrgCalc3;					//0x40
	WORD wPrgDamage;					//0x44
	WORD wSrvMissile;					//0x46
	WORD wSrvMissileA;					//0x48
	WORD wSrvMissileB;					//0x4A
	WORD wSrvMissileC;					//0x4C
	WORD wSrvOverlay;					//0x4E
	DWORD dwAuraFilter;					//0x50
	WORD wAuraStat1;					//0x54
	WORD wAuraStat2;					//0x56
	WORD wAuraStat3;					//0x58
	WORD wAuraStat4;					//0x5A
	WORD wAuraStat5;					//0x5C
	WORD wAuraStat6;					//0x5E
	DWORD dwAuraLenCalc;				//0x60
	DWORD dwAuraRangeCalc;				//0x64
	DWORD dwAuraStatCalc1;				//0x68
	DWORD dwAuraStatCalc2;				//0x6C
	DWORD dwAuraStatCalc3;				//0x70
	DWORD dwAuraStatCalc4;				//0x74
	DWORD dwAuraStatCalc5;				//0x78
	DWORD dwAuraStatCalc6;				//0x7C
	WORD wAuraState;					//0x80
	WORD wAuraTargetState;				//0x82
	WORD wAuraEvent1;					//0x84
	WORD wAuraEvent2;					//0x86
	WORD wAuraEvent3;					//0x88
	WORD wAuraEventFunc1;				//0x8A
	WORD wAuraEventFunc2;				//0x8C
	WORD wAuraEventFunc3;				//0x8E
	WORD wAuraTgtEvent;					//0x90
	WORD wAuraTgtEventFunc;				//0x92
	WORD wPassiveState;					//0x94
	WORD wPassiveIType;					//0x96
	WORD wPassiveStat1;					//0x98
	WORD wPassiveStat2;					//0x9A
	WORD wPassiveStat3;					//0x9C
	WORD wPassiveStat4;					//0x9E
	WORD wPassiveStat5;					//0xA0
	WORD unk0xA2;						//0xA2
	DWORD dwPassiveCalc1;				//0xA4
	DWORD dwPassiveCalc2;				//0xA8
	DWORD dwPassiveCalc3;				//0xAC
	DWORD dwPassiveCalc4;				//0xB0
	DWORD dwPassiveCalc5;				//0xB4
	WORD wPassiveEvent;					//0xB8
	WORD wPassiveEventFunc;				//0xBA
	WORD wSummon;						//0xBC
	BYTE nPetType;						//0xBE
	BYTE nSumMode;						//0xBF
	DWORD dwPetMax;						//0xC0
	WORD wSumSkill1;					//0xC4
	WORD wSumSkill2;					//0xC6
	WORD wSumSkill3;					//0xC8
	WORD wSumSkill4;					//0xCA
	WORD wSumSkill5;					//0xCC
	WORD unk0xCE;						//0xCE
	DWORD dwSumSkCalc1;					//0xD0
	DWORD dwSumSkCalc2;					//0xD4
	DWORD dwSumSkCalc3;					//0xD8
	DWORD dwSumSkCalc4;					//0xDC
	DWORD dwSumSkCalc5;					//0xE0
	WORD wSumUMod;						//0xE4
	WORD wSumOverlay;					//0xE6
	WORD wCltMissile;					//0xE8
	WORD wCltMissileA;					//0xEA
	WORD wCltMissileB;					//0xEC
	WORD wCltMissileC;					//0xEE
	WORD wCltMissileD;					//0xF0
	WORD wCltStFunc;					//0xF2
	WORD wCltDoFunc;					//0xF4
	WORD wCltPrgFunc1;					//0xF6
	WORD wCltPrgFunc2;					//0xF8
	WORD wCltPrgFunc3;					//0xFA
	WORD wStSound;						//0xFC
	WORD unk0xFE;						//0xFE
	WORD wDoSound;						//0x100
	WORD wDoSoundA;						//0x102
	WORD wDoSoundB;						//0x104
	WORD wCastOverlay;					//0x106
	WORD wTgtOverlay;					//0x108
	WORD wTgtSound;						//0x10A
	WORD wPrgOverlay;					//0x10C
	WORD wPrgSound;						//0x10E
	WORD wCltOverlayA;					//0x110
	WORD wCltOverlayB;					//0x112
	DWORD dwCltCalc1;					//0x114
	DWORD dwCltCalc2;					//0x118
	DWORD dwCltCalc3;					//0x11C
	WORD wItemTarget;					//0x120
	WORD wItemCastSound;				//0x122
	DWORD wItemCastOverlay;				//0x124
	DWORD dwPerDelay;					//0x128
	WORD wMaxLvl;						//0x12C
	WORD wResultFlags;					//0x12E
	DWORD dwHitFlags;					//0x130
	DWORD dwHitClass;					//0x134
	DWORD dwCalc1;						//0x138
	DWORD dwCalc2;						//0x13C
	DWORD dwCalc3;						//0x140
	DWORD dwCalc4;						//0x144
	DWORD dwParam1;						//0x148
	DWORD dwParam2;						//0x14C
	DWORD dwParam3;						//0x150
	DWORD dwParam4;						//0x154
	DWORD dwParam5;						//0x158
	DWORD dwParam6;						//0x15C
	DWORD dwParam7;						//0x160
	DWORD dwParam8;						//0x164
	WORD wWeapSel;						//0x168
	WORD wItemEffect;					//0x16A
	DWORD wItemCltEffect;				//0x16C
	DWORD dwSkPoints;					//0x170
	WORD wReqLevel;						//0x174
	WORD wReqStr;						//0x176
	WORD wReqDex;						//0x178
	WORD wReqInt;						//0x17A
	WORD wReqVit;						//0x17C
	WORD wReqSkill1;					//0x17E
	WORD wReqSkill2;					//0x180
	WORD wReqSkill3;					//0x182
	WORD wStartMana;					//0x184
	WORD wMinMana;						//0x186
	WORD wManaShift;					//0x188
	WORD wMana;							//0x18A
	WORD wLevelMana;					//0x18C
	BYTE nAttackRank;					//0x18E
	BYTE nLineOfSight;					//0x18F
	DWORD dwDelay;						//0x190
	DWORD wSkillDesc;					//0x194
	DWORD dwToHit;						//0x198
	DWORD dwLevToHit;					//0x19C
	DWORD dwToHitCalc;					//0x1A0
	BYTE nToHitShift;					//0x1A4
	BYTE nSrcDam;						//0x1A5
	WORD unk0x1A6;						//0x1A6
	DWORD dwMinDam;						//0x1A8
	DWORD dwMaxDam;						//0x1AC
	DWORD dwMinLvlDam1;					//0x1B0
	DWORD dwMinLvlDam2;					//0x1B4
	DWORD dwMinLvlDam3;					//0x1B8
	DWORD dwMinLvlDam4;					//0x1BC
	DWORD dwMinLvlDam5;					//0x1C0
	DWORD dwMaxLvlDam1;					//0x1C4
	DWORD dwMaxLvlDam2;					//0x1C8
	DWORD dwMaxLvlDam3;					//0x1CC
	DWORD dwMaxLvlDam4;					//0x1D0
	DWORD dwMaxLvlDam5;					//0x1D4
	DWORD dwDmgSymPerCalc;				//0x1D8
	WORD wEType;						//0x1DC
	WORD unk0x1DE;						//0x1DE
	DWORD dwEMin;						//0x1E0
	DWORD dwEMax;						//0x1E4
	DWORD dwEMinLev1;					//0x1E8
	DWORD dwEMinLev2;					//0x1EC
	DWORD dwEMinLev3;					//0x1F0
	DWORD dwEMinLev4;					//0x1F4
	DWORD dwEMinLev5;					//0x1F8
	DWORD dwEMaxLev1;					//0x1FC
	DWORD dwEMaxLev2;					//0x200
	DWORD dwEMaxLev3;					//0x204
	DWORD dwEMaxLev4;					//0x208
	DWORD dwEMaxLev5;					//0x20C
	DWORD dwEDmgSymPerCalc;				//0x210
	DWORD dwELen;						//0x214
	DWORD dwELevLen1;					//0x218
	DWORD dwELevLen2;					//0x21C
	DWORD dwELevLen3;					//0x220
	DWORD dwELenSymPerCalc;				//0x224
	WORD wRestrict;						//0x228
	WORD wState1;						//0x22A
	WORD wState2;						//0x22C
	WORD wState3;						//0x22E
	WORD wAiType;						//0x230
	WORD wAiBonus;						//0x232
	DWORD dwCostMult;					//0x234
	DWORD dwCostAdd;					//0x238
};

struct DifficultyLevelsBIN
{
	DWORD	resistPenalty;	//+00
	BYTE	uk1[1];			//+04
};

struct SuperUniqueBIN
{
};

struct MonStatsBIN	//size=0x1A8 (424)
{
	BYTE	uk1[0x6];		//+00
	WORD	monsterNameID;	//+06
	BYTE	uk2[0x1A0];		//+08
};							//+1A8

struct ItemTypesBIN //size=0xE4 (228) (source : fct of dll)
{
	DWORD	code;			//+00
	WORD wEquiv1;						//0x04
	WORD wEquiv2;						//0x06
	BYTE nRepair;						//0x08
	BYTE nBody;							//0x09
	BYTE nBodyLoc1;						//0x0A
	BYTE nBodyLoc2;						//0x0B
	WORD wShoots;						//0x0C
	WORD wQuiver;						//0x0E
	BYTE nThrowable;					//0x10
	BYTE nReload;						//0x11
	BYTE nReEquip;						//0x12
	BYTE nAutoStack;					//0x13
	BYTE nMagic;						//0x14
	BYTE nRare;							//0x15
	BYTE nNormal;						//0x16
	BYTE nCharm;						//0x17
	BYTE nGem;							//0x18
	BYTE nBeltable;						//0x19
	BYTE nMaxSock1;						//0x1A
	BYTE nMaxSock25;					//0x1B
	BYTE nMaxSock40;					//0x1C
	BYTE nTreasureClass;				//0x1D
	BYTE nRarity;						//0x1E
	BYTE nStaffMods;					//0x1F
	BYTE nCostFormula;					//0x20
	BYTE nClass;						//0x21
	BYTE nStorePage;					//0x22
	BYTE nVarInvGfx;					//0x23
	char szInvGfx1[32];					//0x24
	char szInvGfx2[32];					//0x44
	char szInvGfx3[32];					//0x64
	char szInvGfx4[32];					//0x84
	char szInvGfx5[32];					//0xA4
	char szInvGfx6[32];					//0xC4
};							//+E4


struct AffixBIN //size=0x90 (144) (source : fct of dll) magicsuffix + magicprefix + automagic
{
	char	name[0x20];		//+00
	WORD	nameCode;		//+20
	WORD	version;		//+22
	DWORD	mod1code;		//+24
	DWORD	mod1param;		//+28
	DWORD	mod1min;		//+2C
	DWORD	mod1max;		//+30
	DWORD	mod2code;		//+34
	DWORD	mod2param;		//+38
	DWORD	mod2min;		//+3C
	DWORD	mod2max;		//+40
	DWORD	mod3code;		//+44
	DWORD	mod3param;		//+48
	DWORD	mod3min;		//+4C
	DWORD	mod3max;		//+50
	BYTE	spawnable;		//+54
	BYTE	uk1[0x1];		//+55
	WORD	transformcolor;	//+56
	DWORD	level;			//+58
	DWORD	group;			//+5C
	DWORD	maxlevel;		//+60
	BYTE	rare;			//+64
	BYTE	levelreq;		//+65
	BYTE	classspecific;	//+66
	BYTE	classf;			//+67
	BYTE	classlevelreq;	//+68
	BYTE	uk2[0x1];		//+69
	WORD	itype1;			//+6A
	WORD	itype2;			//+6C
	WORD	itype3;			//+6E
	WORD	itype4;			//+70
	WORD	itype5;			//+72
	WORD	itype6;			//+74
	WORD	itype7;			//+76
	WORD	etype1;			//+78
	WORD	etype2;			//+7A
	WORD	etype3;			//+7C
	WORD	etype4;			//+7E
	WORD	etype5;			//+80
	BYTE	frequency;		//+82
	BYTE	uk3[0x1];		//+83
	DWORD	divide;			//+84
	DWORD	multiply;		//+88
	DWORD	add;			//+8C
};

struct PropertiesBIN // size=0x2E (46) (source total : fct of dll)
{
	WORD	modcode;		//+00
	BYTE	set1;			//+02
	BYTE	set2;			//+03
	BYTE	set3;			//+04
	BYTE	set4;			//+05
	BYTE	set5;			//+06
	BYTE	set6;			//+07
	BYTE	set7;			//+08
	BYTE	uk1[0x1];		//+09

	WORD	val1;			//+0A
	WORD	val2;			//+0C
	WORD	val3;			//+0E
	WORD	val4;			//+10
	WORD	val5;			//+12
	WORD	val6;			//+14
	WORD	val7;			//+16

	BYTE	func1;			//+18
	BYTE	func2;			//+19
	BYTE	func3;			//+1A
	BYTE	func4;			//+1B
	BYTE	func5;			//+1C
	BYTE	func6;			//+1D
	BYTE	func7;			//+1E
	BYTE	uk2[0x1];		//+1F

	WORD	stat1;			//+20
	WORD	stat2;			//+22
	WORD	stat3;			//+24
	WORD	stat4;			//+26
	WORD	stat5;			//+28
	WORD	stat6;			//+2A
	WORD	stat7;			//+2C
};

struct ItemStatCostBIN // size=0x144 (324) (source total : fct of dll) maxline = 0x1FF = 511
{
	DWORD	statID;			//+00
	union					//+04
	{
		DWORD	flags;
		struct
		{
			DWORD sendOther:1;			//0x00000001
			DWORD signedf:1;			//0x00000002
			DWORD damagerelated:1;		//0x00000004
			DWORD itemspecific:1;		//0x00000008
			DWORD direct:1;				//0x00000010
			DWORD fuk1:4;				//0x000001E0
			DWORD updateanimrate:1;		//0x00000200
			DWORD fmin:1;				//0x00000400
			DWORD fcallback:1;			//0x00000800
			DWORD saved:1;				//0x00001000
			DWORD cvssigned:1;			//0x00002000
			DWORD fuk2:18;				//0xFFFFC000
		};
	};
	BYTE	sendBits;		//+08
	BYTE	sendParamBits;	//+09
	BYTE	csvbits;		//+0A
	BYTE	csvparam;		//+0B
	DWORD	divide;			//+0C
	DWORD	multiply;		//+10
	DWORD	add;			//+14
	BYTE	valshift;		//+18
	BYTE	saveBits;		//+19
	BYTE	saveBits109;	//+1A	//are only for conversion
	BYTE	uk2[0x1];		//+1B
	DWORD	saveAdd;		//+1C
	DWORD	saveAdd109;		//+20	//are only for conversion
	DWORD	saveParamBits;	//+24
	BYTE	uk3[0x4];		//+28
	DWORD	minaccr;		//+2C
	BYTE	encode;			//+30
	BYTE	uk4[0x1];		//+31
	WORD	maxstat;		//+32
	WORD	descpriority;	//+34
	BYTE	descfunc;		//+36
	BYTE	descval;		//+37
	WORD	descstrpos;		//+38
	WORD	descstrneg;		//+3A
	WORD	descstr2;		//+3C
	WORD	dgrp;			//+3E
	BYTE	dgrpfunc;		//+40
	BYTE	dgrpval;		//+41
	WORD	dgrpstrpos;		//+42
	WORD	dgrpstrneg;		//+44
	WORD	dgrpstr2;		//+46
	WORD	itemevent1;		//+48
	WORD	itemevent2;		//+4A
	WORD	itemeventfunc1;	//+4C
	WORD	itemeventfunc2;	//+4E
	BYTE	keepzero;		//+50
	BYTE	uk5[0x3];		//+51
	BYTE	op;				//+54
	BYTE	opParam;		//+55
	WORD	opStat1;		//+58
	WORD	opStat2;		//+5A
	WORD	opStat3;		//+5C
	BYTE	uk6[0xE2];		//+5E
	DWORD	stuff;			//+140
};

struct InventoryBIN // size=0xF0 (240) (source total : fct of dll)
{
	DWORD	invLeft;		//+00
	DWORD	invRight;		//+04
	DWORD	invTop;			//+08
	DWORD	invBottom;		//+0C
	BYTE	gridX;			//+10
	BYTE	gridY;			//+11
	BYTE	uk1[2];			//+12
	DWORD	gridLeft;		//+14
	DWORD	gridRight;		//+18
	DWORD	gridTop;		//+1C
	DWORD	gridBottom;		//+20
	BYTE	gridBoxWidth;	//+24
	BYTE	gridBoxHeight;	//+25
	BYTE	uk2[2];			//+26
	DWORD	rArmLeft;		//+28
	DWORD	rArmRight;		//+2C
	DWORD	rArmTop;		//+30
	DWORD	rArmBottom;		//+34
	BYTE	rArmWidth;		//+38
	BYTE	rArmHeight;		//+39
	BYTE	uk3[2];			//+3A
	DWORD	torsoLeft;		//+3C
	DWORD	torsoRight;		//+40
	DWORD	torsoTop;		//+44
	DWORD	torsoBottom;	//+48
	BYTE	torsoWidth;		//+4C
	BYTE	torsoHeight;	//+4D
	BYTE	uk4[2];			//+4E
	DWORD	lArmLeft;		//+50
	DWORD	lArmRight;		//+54
	DWORD	lArmTop;		//+58
	DWORD	lArmBottom;		//+5C
	BYTE	lArmWidth;		//+60
	BYTE	lArmHeight;		//+61
	BYTE	uk5[2];			//+62
	DWORD	headLeft;		//+64
	DWORD	headRight;		//+68
	DWORD	headTop;		//+6C
	DWORD	headBottom;		//+70
	BYTE	headWidth;		//+74
	BYTE	headHeight;		//+75
	BYTE	uk6[2];			//+76
	DWORD	neckLeft;		//+78
	DWORD	neckRight;		//+7C
	DWORD	neckTop;		//+80
	DWORD	neckBottom;		//+84
	BYTE	neckWidth;		//+88
	BYTE	neckHeight;		//+89
	BYTE	uk7[2];			//+8A
	DWORD	rHandLeft;		//+8C
	DWORD	rHandRight;		//+90
	DWORD	rHandTop;		//+94
	DWORD	rHandBottom;	//+98
	BYTE	rHandWidth;		//+9C
	BYTE	rHandHeight;	//+9D
	BYTE	uk8[2];			//+9E
	DWORD	lHandLeft;		//+A0
	DWORD	lHandRight;		//+A4
	DWORD	lHandTop;		//+A8
	DWORD	lHandBottom;	//+AC
	BYTE	lHandWidth;		//+B0
	BYTE	lHandHeight;	//+B1
	BYTE	uk9[2];			//+B2
	DWORD	beltLeft;		//+B4
	DWORD	beltRight;		//+B8
	DWORD	beltTop;		//+BC
	DWORD	beltBottom;		//+C0
	BYTE	beltWidth;		//+C4
	BYTE	beltHeight;		//+C5
	BYTE	uk10[2];		//+C6
	DWORD	feetLeft;		//+C8
	DWORD	feetRight;		//+CC
	DWORD	feetTop;		//+D0
	DWORD	feetBottom;		//+D4
	BYTE	feetWidth;		//+D8
	BYTE	feetHeight;		//+D9
	BYTE	uk11[2];		//+DA
	DWORD	glovesLeft;		//+DC
	DWORD	glovesRight;	//+E0
	DWORD	glovesTop;		//+E4
	DWORD	glovesBottom;	//+E8
	BYTE	glovesWidth;	//+EC
	BYTE	glovesHeight;	//+ED
	BYTE	uk12[2];		//+EE
};

struct DataTables//01EE6A20 * 01FDA2D0 //second comments=1.11
{
	DWORD pPlayerClassTxt;//+000 - pPlayerClassTxt
	DWORD pPlayerClassLink;//-4    pPlayerClassLink
	DWORD pBodyLocsTxt;//-8    pBodyLocsTxt
	DWORD pBodyLocsLink;//00C -    pBodyLocsLink
	DWORD pStorePageTxt;//-10    pStorePageTxt
	DWORD pStorePageLink;//-14    pStorePageLink
	DWORD pElemTypesTxt;//-18    pElemTypesTxt
	DWORD pElemTypesLink;//01C -    pElemTypesLink
	DWORD pHitClassTxt;//-20    pHitClassTxt
	DWORD pHitClassLink;//-24    pHitClassLink
	DWORD pMonModeTxt;//-28    pMonModeTxt
	DWORD pMonModeLink;//02C -    pMonModeLink
	DWORD pPlrModeTxt;//-30    pPlrModeTxt
	DWORD pPlrModeLink;//-34    pPlrModeLink
	DWORD pSkillCalcTxt;//-38    pSkillCalcTxt
	DWORD pSkillCalcLink;//03C -    pSkillCalcLink
	DWORD pSkillCalcCache;//-40    pSkillCalcCache
	DWORD nSkillCalcCache;//-44    nSkillCalcCache
	DWORD nSkillCalcCacheDelta;//-48    nSkillCalcCacheDelta
	DWORD pSkillDescCalcCache;//04C -    pSkillDescCalcCache
	DWORD nSkillDescCalcCache;//-50    nSkillDescCalcCache
	DWORD nSkillDescCalcCacheDel;//-54    nSkillDescCalcCacheDel
	DWORD pMissCalcTxt;//-58    pMissCalcTxt
	DWORD pMissCalcLink;//05C -    pMissCalcLink
	DWORD pMissCalcCache;//-60    pMissCalcCache
	DWORD nMissCalcCache;//-64    nMissCalcCache
	DWORD nMissCalcCacheDelta;//-68    nMissCalcCacheDelta
	DWORD pSkillCodesBin ;//06C -    pSkillCodesBin - creat
	DWORD pSkillCodesLink;//-70    pSkillCodesLink
	DWORD pEventsTxt;//-74    pEventsTxt
	DWORD pEventsLink;//-78    pEventsLink
	DWORD pCompCodesTxt;//07C -    pCompCodesTxt
	DWORD pCompCodesLink;//-80    pCompCodesLink
	DWORD nCompCodes;//-84    nCompCodes
	DWORD pMonAiTxt;//-88    pMonAiTxt
	DWORD pMonAiLink;//08C -    pMonAiLink
	DWORD nMonAi;//-90    nMonAi
	DWORD pItemLink ;//-94    pItemLink - the actual
	DWORD pItemCalcCache;//-98    pItemCalcCache
	DWORD nItemCalcCache;//09C -    nItemCalcCache
	DWORD nItemCalcCacheDelta;//0A0 -    nItemCalcCacheDelta
	DWORD pPropertiesTxt;//0A4 -    pPropertiesTxt
	DWORD pPropertiesLink;//0A8 -    pPropertiesLink
	DWORD nProperties;//0AC -    nProperties
	DWORD pRunesLink;//0B0 -    pRunesLink
	DWORD pHireDescTxt;//0B4 -    pHireDescTxt
	DWORD pHireDescLink;//0B8 -    pHireDescLink
	DWORD pStatesTxt;//0BC -    pStatesTxt
	DWORD pStatesLink;//0C0 -    pStatesLink
	DWORD nStates;//0C4 -    nStates
	DWORD pStateMaskFirst;//0C8 -    pStateMaskFirst
	DWORD pStateMaskArray[40];//0CC -    pStateMaskArray[40]
	DWORD pProgressiveStates;//16C -    pProgressiveStates[arr
	DWORD nProgressiveStates;//-170    nProgressiveStates
	DWORD pCurseStates;//-174    pCurseStates[arrSize]
	DWORD nCurseStates;//-178    nCurseStates
	DWORD pTransformStates;//17C -    pTransformStates[arrSi
	DWORD nTransformStates;//-180    nTransformStates
	DWORD pActionStates;//-184    pActionStates[arrSize]
	DWORD nActionStates;//-188    nActionStates
	DWORD pColorStates;//18C -    pColorStates[arrSize]
	DWORD nColorStates;//-190    nColorStates
	DWORD pSoundCodesBin;//-194    pSoundCodesBin - creat
	DWORD pSoundCodesLink;//-198    pSoundCodesLink
	DWORD nSoundCodes;//19C -    nSoundCodes
	DWORD pHirelingsTxt;//1A0 -    pHirelingsTxt
	DWORD nHirelings;//1A4 -    nHirelings
	DWORD HireNameListStart[256];//1A8 -    HireNameListStart[256]
	DWORD HireNameListEnd[256];//5A8 -    HireNameListEnd[256] -
	DWORD pNpcsTxt;//9A8 -    pNpcsTxt
	DWORD nNpcs;//9AC -    nNpcs
	DWORD pColorsTxt;//9B0 -    pColorsTxt
	DWORD pColorsLink;//9B4 -    pColorsLink
	DWORD pTreasureClassExLink;//9B8 -    pTreasureClassExLink
	DWORD pTreasureClassExTxt;//9BC -    pTreasureClassExTxt
	DWORD nTreasureClassEx;//9C0 -    nTreasureClassEx
	DWORD pChestTreasureClassList[45];//9C4 -    pChestTreasureClassLis
	MonStatsBIN*	monStats;			//+A78 //1.11 and 1.10
	BYTE			uk2[0x4];			//+A7C
	DWORD			nbMonStats;			//+A80 //1.11 and 1.10
	BYTE			uk3[0x108];			//+A84
	SkillDescBIN*	skilldesc;			//+B8C
	BYTE			uk4[0x4];			//+B90
	DWORD			nbSkilldesc;		//+B94
	SkillsBIN*		skills;				//+B98
	BYTE			uk5[0x4];			//+B9C
	DWORD			nbSkills;			//+BA0
	int*			nbSkillsPerPlayer;	//+BA4
	int				maxSkillsPerPlayer;	//+BA8
	WORD*			playerSkills;		//+BAC
	BYTE			uk6[0x14];			//+BB0
	CharStatsBIN*	charStats;			//+BC4
	DWORD			nbCharStats;		//+BC8
	ItemStatCostBIN* itemStatCost;		//+BCC
	BYTE			uk7[4];				//+BD0
	DWORD			nbItemStatCosts;	//+BD4
	WORD*			statsDescPriority;	//+BD8
	DWORD			nbStatsDescPriority;//+BDC
	BYTE			uk8[0x18];			//+BE0
	ItemTypesBIN*	itemTypes;			//+BF8
	DWORD			nbItemTypes;		//+BFC
	BYTE			uk9[0x18];			//+C00
	SetItemsBIN*	setItems;			//+C18 //1.11 and 1.10
	DWORD			nbSetItems;			//+C1C //1.11 and 1.10
	BYTE			uk10[0x4];			//+C20
	UniqueItemsBIN*	uniqueItems;		//+C24 //1.11 and 1.10
	DWORD			nbUniqueItems;		//+C28 //1.11 and 1.10
	BYTE			uk11[0x2C];			//+C2C
	LevelsBIN*		levels;				//+C58
	DWORD			nbLevels;			//+C5C
	BYTE			uk12[0x64];			//+C60
	CubeMainBIN*	cubemain;			//+CC4 //14C0 by 148 for 1.11
	DWORD			nbCubemain;			//+CC8 //14C4 for 1.11
	DWORD			nbInventory;		//+CCC
	InventoryBIN*	inventory;			//+CD0
	BYTE			uk13[0x04];			//+CD4
	DWORD			nbItems;			//+CD8
	ItemBIN*		items;				//+CDC
	ItemBIN*		itemsBis;			//+CE0
	BYTE			uk14[0x1F8];		//+CDC
	DWORD			nbRunes;			//+EDC
	RunesBIN*		runes;				//+EE0
};

struct InventoryGrid 
{ // sizeof 0x18
	BYTE nGridX;        //0x00
	BYTE nGridY;        //0x01
	WORD _align;        //0x02
	long int left;      //0x04
	long int right;     //0x08
	long int top;       //0x0C
	long int bottom;        //0x10
	BYTE nGridWidth;    //0x14
	BYTE nGridHeight;   //0x15
	WORD _align2;       //0x16
};

struct InventorySize 
{ // sizeof 0x10
	long int left;      //0x00
	long int right;     //0x04
	long int top;       //0x08
	long int bottom;        //0x0C
};

struct InventoryLayout //sizeof 0x14
{
	long int left;		//0x00
	long int right;		//0x04
	long int top;		//0x08
	long int bottom;		//0x0C
	union
	{
		struct
		{
			BYTE nGridX;		//0x10
			BYTE nGridY;		//0x11
		};
		struct
		{
			BYTE nWidth;	//0x10
			BYTE nHeight;	//0x11
		};
	};
	WORD _align;		//0x12
};

struct InventoryTxt //sizeof 0xF0
{
	InventoryLayout Inventory;		//0x00
	InventoryLayout Grid;			//0x14
	union
	{
		struct
		{
			InventoryLayout RightArm;		//0x28
			InventoryLayout Torso;			//0x3C
			InventoryLayout LeftArm;		//0x50
			InventoryLayout Head;			//0x64
			InventoryLayout Neck;			//0x78
			InventoryLayout RightHand;		//0x8C
			InventoryLayout LeftHand;		//0xA0
			InventoryLayout Belt;			//0xB4
			InventoryLayout Feet;			//0xC8
			InventoryLayout Gloves;			//0xDC
		};
		InventoryLayout hItem[9];
	};
};

struct BeltBox
{
	long int boxLeft;			//0x00
	long int boxRight;			//0x04
	long int boxTop;				//0x08
	long int boxBottom;			//0x0C
};

struct BeltsTxt //sizeof 0x108
{
	DWORD _unusedName;			    //0x00 placeholder for name field
	BYTE dwNumBoxes;               //0x04 uses DWORD space, but interpreted as unsigned byte
	BYTE unknown[3];
	BeltBox hBox[16];				//0x08
};
