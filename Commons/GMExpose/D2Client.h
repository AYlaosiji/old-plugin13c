#define RX(v) (*D2Client::ptWindowStartX+(v))
#define RY(v) (D2Client::ptScreenSize->y+*D2Client::ptNegWindowStartY-(v))
BOOL inline isOnRect(DWORD x, DWORD y, DWORD x0, DWORD y0, DWORD l, DWORD h) { return (x >= x0) && (x < x0 + l) && (y > y0 - h) && (y <= y0); }

 class PATCHLOAD_API D2Client : public Library<D2Client>
{

	static void SetFunctions();

public:
	static void Init();

public:
	typedef void(__stdcall* TD2SendPacket26ToServer) (BYTE* Packet26);
	//文本的长度为502
	static TD2SendPacket26ToServer VD2SendPacket26ToServer;
	
	typedef UnitAny* (__fastcall* TD2GetClientUnitFromGUID)(DWORD UniqueID, int UnitType);
	static TD2GetClientUnitFromGUID D2GetClientUnitFromGUID;

	typedef long(__stdcall* TD2GetPlayerXOffest) ();
	static TD2GetPlayerXOffest D2GetPlayerXOffest;

	typedef long(__stdcall* TD2GetPlayerYOffest) ();
	static TD2GetPlayerYOffest D2GetPlayerYOffest;

	typedef DWORD(__fastcall* TD2GetUIToggle)(int nToggle);
	static TD2GetUIToggle VD2GetUIToggle;
	static TD2GetUIToggle D2GetUIToggle;

	typedef DWORD(__fastcall* TD2SetUIToggle)(int Toggle, BOOL bState, BOOL bUnk);
	static TD2SetUIToggle D2SetUIToggle;

	typedef DWORD(__fastcall* TD2PrintStat)(UnitAny* ptItem, StatsList* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText);
	static TD2PrintStat VD2PrintStat;
	static TD2PrintStat D2PrintStat;

	typedef void(__stdcall* TD2PrintStatsPage)();
	static TD2PrintStatsPage D2PrintStatsPage;

	typedef CellFile* (__stdcall* TD2LoadBuySelBtn) ();
	static TD2LoadBuySelBtn D2LoadBuySelBtn;

	typedef DWORD(__fastcall* TD2PlaySound) (DWORD id, DWORD, DWORD, DWORD, DWORD);
	static TD2PlaySound VD2PlaySound;
	static TD2PlaySound D2PlaySound;

	typedef void(__fastcall* TD2TogglePage)  (DWORD a, DWORD b, DWORD c);
	static TD2TogglePage D2TogglePage;

	typedef LPWSTR(__fastcall* TD2SetColorPopup)  (LPWSTR popupText, DWORD color);
	static TD2SetColorPopup VD2SetColorPopup;
	static TD2SetColorPopup D2SetColorPopup;

	typedef void(__stdcall* TD2ClientMsgTop)(wchar_t* pText, int nColour);
	static TD2ClientMsgTop D2ClientMsgTop;

	typedef void(__stdcall* TD2ClientMsgBottom)(wchar_t* szText, int nColour);
	static TD2ClientMsgBottom D2ClientMsgBottom;

	typedef UnitAny* (__stdcall* TD2GetSelectedUnit) ();
	static TD2GetSelectedUnit D2GetSelectedUnit;

	typedef void* (__fastcall* TD2LoadImage) (const char* filename, DWORD filetype);
	static TD2LoadImage VD2LoadImage;
	static TD2LoadImage D2LoadImage;

	typedef void(__fastcall* TD2SendToServer3) (BYTE nMsgNum, WORD nEncodedMsg);
	static TD2SendToServer3 VD2SendToServer3;
	static TD2SendToServer3 D2SendToServer3;

	typedef void(__fastcall* TD2ClickOnStashButton) (DWORD x, DWORD y);
	static TD2ClickOnStashButton D2ClickOnStashButton;

	typedef void(__fastcall* TD2DisplaySocketImage) (UnitAny* pItem,DWORD Unk,int  x,int y);
	static TD2DisplaySocketImage D2DisplaySocketImage;

	typedef void(__fastcall* TD2DisplaySocketSingleItem) (UnitAny* pItem,int x,int y);
	static TD2DisplaySocketSingleItem VD2DisplaySocketSingleItem;
	static TD2DisplaySocketSingleItem D2DisplaySocketSingleItem;

	static BYTE* ptDifficulty;
	static UnitAny** ptPlayerClient;
	static DWORD* ptDrawClient6FAD7290;
	static DWORD* ptAutomapOn;//小地图是否打开
	static long* ptDivisor;
	static POINT* ptOffset;
	static POINT* ptAutomapPos;
	static POINT* ptAutoMapSize;//地图大小
	static DWORD* ptMinmapType;// 1小地图 0 大地图
	static POINT* ptMinimapOffset;//小地图边缘地址 ，大地图为 -16*-16
	static POINT* ptScreenSize;
	static DWORD* WindowWidth;
	static DWORD* WindowHeight;
	static DWORD* ptNegWindowStartY;
	static DWORD* ptWindowStartX;
	static DWORD* ptMouseX;
	static DWORD* ptMouseY;
	static DWORD* StatMouse1;
	static DWORD* StatMouse2;
	static DWORD* StatMouse3;
	static DWORD* StatMouse4;
	static DWORD* InventoryArrangeMode;
	static DWORD* VideoOptionCellFileStart;
	static DWORD* PanelOpenMode;
	static BOOL* EscMenuOpened;
	static CellFile** PanelBorderImage;

	static Grid* InvGrid;
	static Grid* CubeGrid;
	static Grid* StashGrid;
	static PetUnit** PetUnitList;

	static void __fastcall D2CleanStatMouseUp();
};
