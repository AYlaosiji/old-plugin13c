#include "pch.h"
#ifdef MODULES_NEWSTATSHOW

#define STR_PREVIOUS_PAGE L"上一页"
#define STR_NEXT_PAGE L"下一页"

#define	getXCloseBtn()			360
#define	getLCloseBtn()			32
#define	getYCloseBtn()			(D2Client::ptScreenSize->y - 60)
#define	getHCloseBtn()			32
#define isOnCloseBtn(x,y) isOnRect(x, y, getXCloseBtn(), getYCloseBtn(), getLCloseBtn(), getHCloseBtn())

#define	getXPreviousPageBtn()		RX(0x19)//0x70
#define	getLPreviousPageBtn()		32
#define	getYPreviousPageBtn()		RY(0x40)
#define	getHPreviousPageBtn()		32
#define isOnPreviousPageBtn(x,y)	isOnRect(x, y, getXPreviousPageBtn(), getYPreviousPageBtn(), getLPreviousPageBtn(), getHPreviousPageBtn())

#define	getXNextPageBtn()		RX(D2Gfx::D2GetResolution()?0x43:0x8A)
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		RY(D2Gfx::D2GetResolution()?0x40:0x70)
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())

/*
#define	getXNextPageBtn()		120
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		(ResolutionY - 60)
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())
*/


#define	getLAssignBtn()			32
#define	getHAssignBtn()			32

#define	getXAssSTRBtn()			0x7D+35
#define	getYAssSTRBtn()			0x6A
#define isOnAssSTRBtn(x,y) isOnRect(x, y, getXAssSTRBtn(), getYAssSTRBtn(), getLAssignBtn(), getHAssignBtn())

#define	getXAssDEXBtn()			0x7D+35
#define	getYAssDEXBtn()			0xA8
#define isOnAssDEXBtn(x,y) isOnRect(x, y, getXAssDEXBtn(), getYAssDEXBtn(), getLAssignBtn(), getHAssignBtn())

#define	getXAssVITBtn()			0x7D+35
#define	getYAssVITBtn()			0xFE
#define isOnAssVITBtn(x,y) isOnRect(x, y, getXAssVITBtn(), getYAssVITBtn(), getLAssignBtn(), getHAssignBtn())

#define	getXAssENEBtn()			0x7D+35
#define	getYAssENEBtn()			0x13C
#define isOnAssENEBtn(x,y) isOnRect(x, y, getXAssENEBtn(), getYAssENEBtn(), getLAssignBtn(), getHAssignBtn())


#define	getLUnassignBtn()		32
#define	getHUnassignBtn()		32

#define	getXUnaSTRBtn()			0x7D
#define	getYUnaSTRBtn()			getYAssSTRBtn()
#define isOnUnaSTRBtn(x,y) isOnRect(x, y, getXUnaSTRBtn(), getYUnaSTRBtn(), getLUnassignBtn(), getHUnassignBtn())

#define	getXUnaDEXBtn()			0x7D
#define	getYUnaDEXBtn()			getYAssDEXBtn()
#define isOnUnaDEXBtn(x,y) isOnRect(x, y, getXUnaDEXBtn(), getYUnaDEXBtn(), getLUnassignBtn(), getHUnassignBtn())

#define	getXUnaVITBtn()			0x7D
#define	getYUnaVITBtn()			getYAssVITBtn()
#define isOnUnaVITBtn(x,y) isOnRect(x, y, getXUnaVITBtn(), getYUnaVITBtn(), getLUnassignBtn(), getHUnassignBtn())

#define	getXUnaENEBtn()			0x7D
#define	getYUnaENEBtn()			getYAssENEBtn()
#define isOnUnaENEBtn(x,y) isOnRect(x, y, getXUnaENEBtn(), getYUnaENEBtn(), getLUnassignBtn(), getHUnassignBtn())



void** ptD2RemainingStatsPointsBoxImages = (void**)0x6FBB5E50;
#define D2RemainingStatsPointsBoxImages (*ptD2RemainingStatsPointsBoxImages)

void** ptD2AssignStatsPointsBoxImages = (void**)0x6FBB5BB8;
#define D2AssignStatsPointsBoxImages (*ptD2AssignStatsPointsBoxImages)

void** ptD2AssignStatsPointsBtnImages = (void**)0x6FBB5BB4;
#define D2AssignStatsPointsBtnImages (*ptD2AssignStatsPointsBtnImages)



static struct
{
	union {
		DWORD all;
		struct {
			DWORD close : 1;
			DWORD AssSTR : 1;
			DWORD AssDEX : 1;
			DWORD AssVIT : 1;
			DWORD AssENE : 1;
			DWORD UnaSTR : 1;
			DWORD UnaDEX : 1;
			DWORD UnaVIT : 1;
			DWORD UnaENE : 1;
			DWORD previousPage : 1;
			DWORD nextPage : 1;
		};
	};
} isDownBtn;


void print2Lines(WORD id, LPWSTR lpText, DWORD x, DWORD l, DWORD y)
{
	wcsncpy(lpText, D2Lang::D2GetStringFromIndex(id), 0x63);
	lpText[0x64] = L'\0';

	LPWSTR lptmp = lpText;
	while (*lptmp)
	{
		if (*lptmp == L'\n')
		{
			*lptmp = L'\0';
			if (*(++lptmp))
			{
				DWORD nbPixel = D2Win::D2GetPixelLen(lpText);
				D2Win::D2PrintString(lpText, MILIEU(x, l, nbPixel), y - 4, WHITE, 0);
				nbPixel = D2Win::D2GetPixelLen(lptmp);
				D2Win::D2PrintString(lptmp, MILIEU(x, l, nbPixel), y + 4, WHITE, 0);
				return;
			}
			break;
		}
		lptmp++;
	}
	DWORD nbPixel = D2Win::D2GetPixelLen(lpText);
	D2Win::D2PrintString(lpText, MILIEU(x, l, nbPixel), y, WHITE, 0);
}


#define BUFSIZE 0x80
void __stdcall printNewStatsPage()
{
	if (!D2Gfx::D2GetResolution()) return D2Client::D2PrintStatsPage();

	WCHAR text[BUFSIZE];
	LPWSTR lpText;
	DWORD nbPixel;
	DWORD curValue, baseValue, color;
	DWORD reset = 0;
	bDontPrintBorder = true;

	UnitAny* ptChar = *D2Client::ptPlayerClient;

	Fog::D2Assert(!ptChar, "Printing stats page : no character selected", __FILE__, __LINE__);
	Fog::D2Assert(ptChar->nUnitType != UNIT_PLAYER, "Printing stats page : bad unit type", __FILE__, __LINE__);

	//print background
	D2Gfx::D2FillArea(0, 0, 400, 552, 0, 5);

	sDrawImageInfo data;
	ZeroMemory(&data, sizeof(data));

	//print button close
	data.pCellFile = D2Client::D2LoadBuySelBtn();
	data.dwCellNo = 10 + isDownBtn.close;
	D2Gfx::D2DrawImage(&data, getXCloseBtn(), getYCloseBtn(), -1, 5, 0);

	//print previous page button
	data.dwCellNo = 12 + isDownBtn.previousPage;
	D2Gfx::D2DrawImage(&data, getXPreviousPageBtn(), getYPreviousPageBtn(), -1, 5, 0);

	//print next page button
	data.dwCellNo = 14 + isDownBtn.nextPage;
	D2Gfx::D2DrawImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);

	CharStatsBIN* charStats = D2Common::D2GetCharStatsBIN(ptChar->nPlayerClass);
	//print fixed text
	D2Win::D2SetFontSize(6);
	print2Lines(0xFD9, text, 0x0B, 0x29, 0x2C); //level					//0x34-0xB
	print2Lines(0xFDA, text, 0x41, 0x73, 0x2C); //Experience				//0xB4-0x41
	print2Lines(0xFDB, text, 0xC1, 0x73, 0x2C); //Next Level				//0x134-0xC1
	print2Lines(0xFDC, text, 0x0A, 0x3F, 0x61); //Strengh				//0x49-0xA
	print2Lines(0xFDE, text, 0x0A, 0x3F, 0xA0); //Dexterity				//0x49-0xA
	print2Lines(0xFE0, text, 0xAE, 0x5E, 0xCF); //Defence				//0x10C-0xAE
	print2Lines(0xFE2, text, 0x0A, 0x3F, 0xF5); //Vitality				//0x49-0xA
	print2Lines(0xFE3, text, 0xAE, 0x36, 0xF5); //Stamina				//0xE4-0xAE
	print2Lines(0xFE4, text, 0xAE, 0x36, 0x10D);//Life					//0xE4-0xAE
	print2Lines(0xFE5, text, 0x0A, 0x3F, 0x133);//Energy					//0x49-0xA
	print2Lines(0xFE6, text, 0xAE, 0x36, 0x133);//Mana					//0xE4-0xAE
	print2Lines(0xFE7, text, 0xBE, 0x4E, 0x15A);//Fire.Resistance		//0x10C-0xBE
	print2Lines(0xFE8, text, 0xBE, 0x4E, 0x172);//Cold.Resistance		//0x10C-0xBE
	print2Lines(0xFE9, text, 0xBE, 0x4E, 0x18B);//Lightning.Resistance	//0x10C-0xBE
	print2Lines(0xFEA, text, 0xBE, 0x4E, 0x1A3);//Poison.Resistance		//0x10C-0xBE

	// print class
	D2Win::D2SetFontSize(1);
	lpText = charStats->nameU;
	nbPixel = D2Win::D2GetPixelLen(lpText);
	D2Win::D2PrintString(lpText, MILIEU(0xC1, 0x76, nbPixel), 0x19, WHITE, 0);

	// print name
	char* string = ptChar->ptPlayerData->name;
	int usize = strlen(string);
	if (usize > 9)
		D2Win::D2SetFontSize(usize < 12 ? 0 : 6);
	mbstowcs(text, string, BUFSIZE);
	nbPixel = D2Win::D2GetPixelLen(text);
	D2Win::D2PrintString(text, MILIEU(0xD, 0x94, nbPixel), 0x19, WHITE, 0);

	D2Win::D2SetFontSize(1);

	// print level value
	curValue = D2Common::D2GetUnitStat(ptChar, STATS_LEVEL, 0);
	baseValue = D2Common::D2GetUnitBaseStat(ptChar, STATS_LEVEL, 0);
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color = WHITE;
	swprintf(text, L"%ld", curValue);
	nbPixel = D2Win::D2GetPixelLen(text);
	D2Win::D2PrintString(text, MILIEU(0xD, 0x29, nbPixel), 0x3B, color, 0);//ESI,EBX,EDI


	//////////////////// POPUP PRINTING ////////////////////
		//set MouseX & MouseY
	DWORD x = *D2Client::ptMouseX;
	DWORD y = *D2Client::ptMouseY;


	if (isOnCloseBtn(x, y))			// print popup "close"
	{
		D2Win::D2PrintPopup(D2Lang::D2GetStringFromIndex(0x1030), getXCloseBtn() + getLCloseBtn() / 2, getYCloseBtn() - getHCloseBtn(), WHITE, 1);
	}
	else if (isOnPreviousPageBtn(x, y))	//print popup "previous page"
	{
		D2Win::D2PrintPopup(STR_PREVIOUS_PAGE, getXPreviousPageBtn() + getLPreviousPageBtn() / 2, getYPreviousPageBtn() - getHPreviousPageBtn(), WHITE, 1);
	}
	else if (isOnNextPageBtn(x, y))	//print popup "next page"
	{
		D2Win::D2PrintPopup(STR_NEXT_PAGE, getXNextPageBtn() + getLNextPageBtn() / 2, getYNextPageBtn() - getHNextPageBtn(), WHITE, 1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

DWORD __stdcall mouseNewStatsPageLeftDown(sWinMessage* msg)
{
	if (!D2Gfx::D2GetResolution()) return -1;

	if (!isOnStatsPage(msg->x, msg->y)) return 1;

	UnitAny* ptChar = *D2Client::ptPlayerClient;

	if (isOnCloseBtn(msg->x, msg->y))
	{
		isDownBtn.close = 1;
		D2Client::D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnPreviousPageBtn(msg->x, msg->y))
	{
		isDownBtn.previousPage = 1;
		D2Client::D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnNextPageBtn(msg->x, msg->y))
	{
		isDownBtn.nextPage = 1;
		D2Client::D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (D2Common::D2GetUnitBaseStat(ptChar, 4, 0))
	{
		if (isOnAssSTRBtn(msg->x, msg->y))
		{
			isDownBtn.AssSTR = 1;
			D2Client::D2PlaySound(5, 0, 0, 0, 0);
		}
		else if (isOnAssDEXBtn(msg->x, msg->y))
		{
			isDownBtn.AssDEX = 1;
			D2Client::D2PlaySound(5, 0, 0, 0, 0);
		}
		else if (isOnAssVITBtn(msg->x, msg->y))
		{
			isDownBtn.AssVIT = 1;
			D2Client::D2PlaySound(5, 0, 0, 0, 0);
		}
		else if (isOnAssENEBtn(msg->x, msg->y))
		{

			isDownBtn.AssENE = 1;
			D2Client::D2PlaySound(5, 0, 0, 0, 0);
		}
	}

	Storm::D2FreeMessage(msg);
	return 0;
}

DWORD __stdcall mouseNewStatsPageLeftUp(sWinMessage* msg)
{
	if (!D2Gfx::D2GetResolution()) return -1;

	if (!isOnStatsPage(msg->x, msg->y)) return 1;

	UnitAny* ptChar = *D2Client::ptPlayerClient;
	DWORD nbStatPointsRemaining = D2Common::D2GetUnitBaseStat(ptChar, 4, 0);

	if (isOnCloseBtn(msg->x, msg->y))
	{
		if (isDownBtn.close)
			D2Client::D2TogglePage(2, 1, 0);
	}
	else if (isOnPreviousPageBtn(msg->x, msg->y))
	{
		if (isDownBtn.previousPage)
		{
			GoStatPage(GetCurrentPage() - 1);
		}
	}
	else if (isOnNextPageBtn(msg->x, msg->y))
	{
		if (isDownBtn.nextPage)
		{
			GoNextStatPage();
		}
	}

	D2Client::D2CleanStatMouseUp();
	Storm::D2FreeMessage(msg);
	isDownBtn.all = 0;
	return 0;
}
#endif // MODULES_NEWSTATSHOW
