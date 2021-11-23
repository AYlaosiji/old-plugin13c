class  PATCHLOAD_API D2Common: public Library<D2Common>
{
	static void SetFunctions();

public:
	static void Init();

public:

	typedef void(__stdcall* TD2SetItemPage) (UnitAny* ptItem, BYTE page);
	static TD2SetItemPage D2SetItemPage;

	typedef BYTE(__stdcall* TD2GetItemPage) (UnitAny* ptUnit);
	static TD2GetItemPage D2GetItemPage;

	typedef DWORD(__stdcall* TD2GetClassSkillID)(int nClass, int nPosition);
	static TD2GetClassSkillID D2GetClassSkillID;

	typedef DWORD(__stdcall* TD2InventoryAddToContainer)(UnitInventory* ptInventory, UnitAny* ptItem);
	static TD2InventoryAddToContainer D2InventoryAddToContainer;

	static DWORD** ADDD10061;

	typedef int(__stdcall* TD2GetItemType) (int nItemHcIdx);
	static TD2GetItemType D2GetItemType;

	typedef DWORD(__stdcall* TD2GetItemLevel) (UnitAny* ptItem);
	static TD2GetItemLevel D2GetItemLevel;

	typedef BYTE(__stdcall* TD2GetItemQuality)(UnitAny* pItem);
	static TD2GetItemQuality D2GetItemQuality;

	typedef void(__stdcall* TD2GetItemSize)(UnitAny* pItem,int * x,int* y, char* filename, DWORD lineno);
	static TD2GetItemSize D2GetItemSize;

	typedef UnitAny* (__stdcall* TD2CanPutItemInInv)(UnitInventory* ptInventory, UnitAny* ptItem, DWORD p3, DWORD zero, UnitAny* ptUnit, const char* file, DWORD line);
	static TD2CanPutItemInInv D2CanPutItemInInv;

	typedef void (__stdcall* TD2GetUnitXY)(UnitAny* pUnit, D2Coord* pCoord);
	static TD2GetUnitXY D2GetUnitXY;

	typedef int(__stdcall* TD2SetUnitStat)(StatsList* pStatList, DWORD StatID, int Value, int Param);
	static TD2SetUnitStat D2SetUnitStat;

	typedef StatsList* (__stdcall* TD2GetStatsFromListflag)(UnitAny* pItem, DWORD Listflag);
	static TD2GetStatsFromListflag D2GetStatsFromListflag;

	typedef DWORD(__stdcall* TD2CheckItemFlag)(UnitAny* item, DWORD flagmask, char* filename, DWORD lineno);
	static TD2CheckItemFlag D2CheckItemFlag;

	typedef BOOL (__stdcall* TD2CheckItemRequirements)(UnitAny* pItem, UnitAny* pUnit, BOOL bEquip, BOOL* bStr, BOOL* bDex, BOOL* bLvl);
	static TD2CheckItemRequirements D2CheckItemRequirements;

	typedef int(__stdcall* TD2GetSkillLevel)(UnitAny* pUnit, Skill* pSkill, BOOL bTotal);
	static TD2GetSkillLevel D2GetSkillLevel;

	typedef DifficultyLevelsBIN* (__stdcall* TD2GetDifficultyLevelsBIN)(DWORD difficultyLevel);
	static TD2GetDifficultyLevelsBIN D2GetDifficultyLevelsBIN;

	typedef DrlgRoom1* (__stdcall* TD2GetRoomFromUnit)(UnitAny* pUnit);
	static TD2GetRoomFromUnit D2GetRoomFromUnit;

	typedef void(__stdcall* TD2UpdateRoomFlags)(DrlgRoom1* pRoom, BOOL unk);
	static TD2UpdateRoomFlags D2UpdateRoomFlags;

	typedef DWORD (__stdcall* TD2GetItemSockets)(UnitAny* pItem);
	static TD2GetItemSockets D2GetItemSockets;

	typedef BYTE(__stdcall* TD2GetBodyloc)(UnitAny* pItem);
	static TD2GetBodyloc D2GetBodyloc;

	typedef void (__stdcall* TD2UpdateSkills)(UnitAny* pUnit);
	static TD2UpdateSkills D2UpdateSkills;
	
	typedef int(__stdcall* TD2EvalItemCalc)(UnitAny* pPlayer, UnitAny* pItem, DWORD dwCalc);
	static TD2EvalItemCalc D2EvalItemCalc;

	typedef int (__stdcall* TD2GetActFromLevel)(int nLevel);
	static TD2GetActFromLevel D2GetActFromLevel;

	typedef UnitAny* (__stdcall* TD2GetFirstInventoryItem)(UnitInventory* pInventory);
	static TD2GetFirstInventoryItem D2GetFirstInventoryItem;

	typedef UnitAny* (__stdcall* TD2GetNextInventoryItem)(UnitAny* ptLastItem);
	static TD2GetNextInventoryItem D2GetNextInventoryItem;

	typedef int(__stdcall* TD2GetUnitState)(UnitAny* pUnit, DWORD StateID);
	static TD2GetUnitState D2GetUnitState;

	typedef void (__stdcall* TD2InitializeSkillList)(UnitAny* ptUnit);
	static TD2InitializeSkillList D2InitializeSkillList;
	
	typedef BOOL(__stdcall* TD2AddUnitStat)(UnitAny* pUnit, DWORD StatID, int Value, int Param);
	static TD2AddUnitStat D2AddUnitStat;

	typedef DWORD(__stdcall* TD2GetUnitBaseStat)(UnitAny* pUnit, DWORD StatID, int Param);
	static TD2GetUnitBaseStat D2GetUnitBaseStat;

	typedef int(__stdcall* TD2GetUniqueID) (UnitAny* ptItem);
	static TD2GetUniqueID D2GetUniqueID;

	typedef Skill* (__fastcall* TD2GetSkill)(UnitAny* pPlayer, DWORD nSkillID);
	static TD2GetSkill D2GetSkill;

	typedef UnitAny* (__stdcall* TD2InvRemoveItem)(UnitInventory* ptInventory, UnitAny* ptItem);
	static TD2InvRemoveItem D2InvRemoveItem;

	typedef DrlgRoom1* (__stdcall* TD2GetFreeCoords)(DrlgRoom1*, D2Coord*, D2Coord*, int, int, int, int);
	static TD2GetFreeCoords D2GetFreeCoords;

	typedef ItemBIN* (__stdcall* TD2GetItemTxt)(int ItemId);
	static TD2GetItemTxt D2GetItemTxt;

	typedef int(__stdcall* TD2GetItemNodePage)(UnitAny* pItem);
	static TD2GetItemNodePage D2GetItemNodePage;

	typedef BOOL(__stdcall* TD2CheckItemType)(UnitAny* pItem, int);
	static TD2CheckItemType D2CheckItemType;

	typedef long (__stdcall* TD2GetUnitPosXFromPath)(DynamicPath* pPath);
	static TD2GetUnitPosXFromPath D2GetUnitPosXFromPath;

	typedef DWORD (__stdcall* TD2GetItemIndexFromCode)(DWORD ItemCode);
	static TD2GetItemIndexFromCode D2GetItemIndexFromCode;

	typedef int(__stdcall* TD2GetLevelNoFromRoom)(DrlgRoom1* pRoom);
	static TD2GetLevelNoFromRoom D2GetLevelNoFromRoom;

	typedef DWORD(__stdcall* TD2GetItemFlags)(UnitAny* pItem);
	static TD2GetItemFlags D2GetItemFlags;

	typedef void* (__stdcall* TD2CompileTxtFile)(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);
	static TD2CompileTxtFile D2CompileTxtFile;

	typedef long(__stdcall* TD2GetUnitPosYFromPath)(DynamicPath* pPath);
	static TD2GetUnitPosYFromPath D2GetUnitPosYFromPath;

	typedef void(__stdcall* TD2SetUnitStat2)(UnitAny* Unit, int nStat, int nValue, int nLayer);
	static TD2SetUnitStat2 D2SetUnitStat2;

	typedef PlayerData* (__stdcall* TD2GetPlayerData)(UnitAny* ptChar);
	static TD2GetPlayerData D2GetPlayerData;

	typedef DWORD(__stdcall* TD2GetUnitStat)(UnitAny* pUnit, DWORD StatID, int Param);
	static TD2GetUnitStat D2GetUnitStat;

	typedef DWORD(__stdcall* TD2SaveItem) (UnitAny* ptItem, saveBitField* data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6);
	static TD2SaveItem D2SaveItem;

	typedef UnitAny* (__stdcall* TD2GetCursorItem)(UnitInventory* ptInventory);
	static TD2GetCursorItem D2GetCursorItem;

	typedef DWORD(__stdcall* TD2GetUnitPosX)(UnitAny* pUnit);
	static TD2GetUnitPosX D2GetUnitPosX;

	typedef void(__stdcall* TD2MapToAbsScreen)(long* pX, long* pY);
	static TD2MapToAbsScreen D2MapToAbsScreen;

	typedef void(__stdcall* TD2SetAnimMode)(UnitAny* pUnit, int unk);
	static TD2SetAnimMode D2SetAnimMode;

	typedef DWORD(__stdcall* TD2InvAddItem) (UnitInventory* ptInventory, UnitAny* ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page);
	static TD2InvAddItem D2InvAddItem;

	typedef DWORD(__stdcall* TD2GetClassSkillCount)(int nClass);
	static TD2GetClassSkillCount D2GetClassSkillCount;

	typedef UnitAny* (__stdcall* TD2GetItemByBodyLoc)(UnitInventory* ptInventory, int bodyloc);
	static TD2GetItemByBodyLoc D2GetItemByBodyLoc;

	typedef UnitAny* (__stdcall* TD2UnitIsItem)(UnitAny* pItem);
	static TD2UnitIsItem D2UnitIsItem;

	typedef DWORD(__stdcall* TD2GetUnitPosY)(UnitAny* pUnit);
	static TD2GetUnitPosY D2GetUnitPosY;

	typedef CharStatsBIN* (__fastcall* TD2GetCharStatsBIN)(DWORD dwIdx);
	static TD2GetCharStatsBIN VD2GetCharStatsBIN;
	static TD2GetCharStatsBIN D2GetCharStatsBIN;

	typedef ItemStatCostBIN* (__fastcall* TD2GetItemStatCostBIN)(DWORD dwIdx);
	static TD2GetItemStatCostBIN VD2GetItemStatCostBIN;
	static TD2GetItemStatCostBIN D2GetItemStatCostBIN;

	typedef LevelsBIN* (__fastcall* TD2GetLevelTxt)(DWORD dwIdx);
	static TD2GetLevelTxt D2GetLevelTxt;

	typedef SkillsBIN* (__fastcall* TD2GetSkillsTxt)(DWORD dwIdx);
	static TD2GetSkillsTxt D2GetSkillsTxt;

	typedef ItemTypesBIN* (__fastcall* TD2GetItemTypeBin)(DWORD dwIdx);
	static TD2GetItemTypeBin D2GetItemTypeBin;

	static DWORD* nWeaponsTxt;
	static DWORD* nArmorTxt;
	static InventoryTxt** pInventoryTxt;
	static DataTables** SgptDataTables;

	static DWORD __stdcall GetItemStatFromFlag0x40(UnitAny* ptUnit, DWORD StatID, int Param);

	static void __stdcall SetItemStatFromFlag0x40(UnitAny* ptUnit, DWORD StatID, DWORD Value, int Param, NetClient* pClient);
};