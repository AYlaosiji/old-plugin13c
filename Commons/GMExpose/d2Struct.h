#define D2TXTCODE(x) ( ((x)&0xff)<<24 | ((x)>>8&0xff)<<16 | ((x)>>16&0xff)<<8 | ((x)>>24&0xff) )

struct UnitAny;
struct GameStruct;
struct Room;

struct D2Coord
{
	int nX;
	int nY;
};

struct Grid
{
	BYTE cellx;
	BYTE celly;
	WORD _1;
	DWORD Left;
	DWORD Right;
	DWORD Up;
	DWORD Bottom;
	BYTE BoxPerWidth;//29
	BYTE BoxPerHeight;//29
};

struct PetUnit 
{
	DWORD	dwTxtFileNo;		//+00 对应monstats.tx的hcidx
	DWORD	dwPetType;			//+04 对应pettype.txt
	DWORD	dwUnitId;			//+08
	DWORD	dwOwnerId;			//+0C 主人GUID
	DWORD	dwFlag1;			//+10
	DWORD	dwOffsetX;			//+14 不确定
	DWORD	dwOffsetY;			//+18 不确定
	DWORD	dwHpPercent;		//+1C
	DWORD	dwOwerType;			//+20  
	DWORD	dwInitSeed;			//+24  雇佣时生成，不再变化
	WORD	wLocaleTxtNo;		//+28  名字索引 for pet
	BYTE	_1[6];				//+2A
	PetUnit* pNext;				//+30
};

#pragma pack(1)
struct sWinMessage
{
	void*	msg;
	DWORD	type;
	DWORD	uk1;
	WORD	x;
	WORD	y;
	DWORD	uk3;
	DWORD	uk4;
	DWORD	managed;
	DWORD	unmanaged;	
};
#pragma pack()

struct GfxCell 
{
	DWORD	dwFlags;	//+00
	DWORD	dwWidth;	//+04
	DWORD	dwHeight;	//+08
	DWORD	dwXoffs;	//+0c
	DWORD	dwYoffs;	//+10
	DWORD	_2;
	DWORD	dwParent;	//+18
	DWORD	dwLength;	//+1c
	BYTE	nCols[1];	//+20
};

struct CellFile 
{
	DWORD	dwVersion;		//+00
	struct
	{
		WORD dwFlags;
		BYTE mylastcol;
		BYTE mytabno : 1;
	};						//+04
	DWORD	eFormat;		//+08
	DWORD	dwTermination;	//+0C
	DWORD	dwNumdirs;		//+10
	DWORD	dwNumCells;		//+14
	GfxCell* pCells[1];		//+18
};

struct sDrawImageInfo//size = 0x48
{
		DWORD		dwCellNo;		//+00
		DWORD		dwDirNo;		//+04  (0-63, other values asplode even when file has more dirs) 
		DWORD		dwDirection;	//+08
		DWORD		_1[10];			//+0C
		CellFile* pCellFile;			//+34
		char*		_2;						//+3C 一定要凑足0x48的长度，不然初始化错误
		char*		_3;			//+40 一定要凑足0x48的长度，不然初始化错误
		DWORD		_4;			//+44 一定要凑足0x48的长度，不然初始化错误
};


struct saveBitField
{
	BYTE*	data;
	DWORD	maxBits;
	DWORD	currentByte;
	DWORD	currentBit;
	DWORD	overflaw;
};

struct BINField
{
   char*	fieldName;  
   int		type;  
   DWORD	strLength;  
   DWORD	offset;  
   void*	lookup; 
};

struct ItemGenerationData //size=0x84
{
	UnitAny*	ptMonster;		//+00
	BYTE	uk1[0x04];		//+04
	GameStruct*	ptGame;			//+08
	DWORD	ilvl;			//+0C
	BYTE	uk2[0x04];		//+10
	DWORD	dwTxtFileNo;		//+14
	DWORD	unknow1;		//+18
	DWORD	x;				//+1C
	DWORD	y;				//+20
	Room*	ptRoom;			//+24
	WORD	unknow2;		//+28
	WORD	gameUnknown2;	//+2A
	BYTE	uk3[0x04];		//+2C
	DWORD	quality;		//+30
	BYTE	uk4[0x34];		//+34
	int		prefixID[3];	//+68 (-1: no prefix; 0:random prefix)
	int		suffixID[3];	//+74 (-1: no suffix; 0:random suffix)
	union {					//+80
		DWORD	flags;
		struct {
			DWORD	fuk1:5;		//0x0000001F
			DWORD	unknow3:1;	//0x00000020
		};
	};
};
