#include "pch.h"
#ifdef MODULES_NEWSTATSHOW
#define STR_PREVIOUS_PAGE L"上一页"
#define STR_NEXT_PAGE L"下一页"

#define	getXCloseBtn()			RX(0x110)
#define	getLCloseBtn()			32
#define	getYCloseBtn()			RY(0x40)
#define	getHCloseBtn()			32
#define isOnCloseBtn(x,y) isOnRect(x, y, getXCloseBtn(), getYCloseBtn(), getLCloseBtn(), getHCloseBtn())

#define	getXPreviousPageBtn()		RX(D2Gfx::D2GetResolution()?0x19:0x77)//0x70
#define	getLPreviousPageBtn()		32
#define	getYPreviousPageBtn()		RY(0x40)
#define	getHPreviousPageBtn()		32
#define isOnPreviousPageBtn(x,y)	isOnRect(x, y, getXPreviousPageBtn(), getYPreviousPageBtn(), getLPreviousPageBtn(), getHPreviousPageBtn())

#define	getXNextPageBtn()		RX(D2Gfx::D2GetResolution()?0x43:0xA1)//0x70
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		RY(0x40)
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())


#define BUFSIZE 0x80


static struct
{
	union {
		DWORD all;
		struct {
			DWORD close : 1;
			DWORD previousPage : 1;
			DWORD nextPage : 1;
		};
	};
} isDownBtn;







void printStat(UnitAny* ptChar, DWORD statID, DWORD x, DWORD y, DWORD color, LPWSTR lpText)
{
	LPWSTR text;
	switch (statID)
	{
	case STATS_FIRERESIST:
	case STATS_COLDRESIST:
	case STATS_LIGHTRESIST:
	case STATS_POISONRESIST:
		text = D2Lang::D2GetStringFromIndex(D2Common::D2GetItemStatCostBIN(statID)->descstrpos);
		if (wcslen(text) > 50) return;
		swprintf(lpText, L"%s +%i%%", text, D2Common::D2GetUnitStat(ptChar, statID, 0));
		break;
	default:
		D2Client::D2PrintStat(ptChar, NULL, statID, 0, D2Common::D2GetUnitStat(ptChar, statID, 0), lpText);//param2=ptChar->ptStats->ptItemStats
	}
	//	D2SetFont(1);
	//	if (D2GetPixelLen(lpText)>0x110)
	//		D2SetFont(6);
	D2Win::D2PrintString(lpText, x, y, color, 0);
}

void manageStatLine(UnitAny* ptChar, statsInterfaceBIN* statLine, int currentPage, LPWSTR lpText)
{
	if (!statLine->enabled)
		return;

	if (statLine->page != currentPage)
		return;

	if (statLine->font)
		D2Win::D2SetFontSize(statLine->font);

	printStat(ptChar, statLine->statsID, RX(statLine->x), RY(statLine->y), statLine->color, lpText);
}

void __stdcall printNewStatsPageTwo(int currentPage)
{
	
	WCHAR text[BUFSIZE];
	bDontPrintBorder = false;

	UnitAny* ptChar = *D2Client::ptPlayerClient;

	Fog::D2Assert(!ptChar, "Printing stats page : no character selected", __FILE__, __LINE__);
	Fog::D2Assert(ptChar->nUnitType != UNIT_PLAYER, "Printing stats page : bad unit type", __FILE__, __LINE__);

	//Init data for print image
	sDrawImageInfo data;
	ZeroMemory(&data, sizeof(data));

	//print background
	D2Gfx::D2FillArea(RX(0), RY(480), RX(0) + 320, RY(480) + 432, 0, 5);

	newStatsInterfaceImages.setFrame(0);
	newStatsInterfaceImages.draw(RX(0), RY(226), -1, 5, 0);
	newStatsInterfaceImages.setFrame(1);
	newStatsInterfaceImages.draw(RX(256), RY(226), -1, 5, 0);
	newStatsInterfaceImages.setFrame(2);
	newStatsInterfaceImages.draw(RX(0), RY(50), -1, 5, 0);
	newStatsInterfaceImages.setFrame(3);
	newStatsInterfaceImages.draw(RX(256), RY(50), -1, 5, 0);

	D2Win::D2SetFontSize(1);
	for (int i = 0; i < nbStatsInterface; i++)
	{
		manageStatLine(ptChar, &statsInterface[i], currentPage, text);
	}

	//print background previous/next page buttons
	statsBackgroundImages.setFrame(D2Gfx::D2GetResolution() ? 1 : 0);
	statsBackgroundImages.draw(getXPreviousPageBtn() - 7, getYPreviousPageBtn() + 8, -1, 5, 0);

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


	//////////////////// POPUP PRINTING ////////////////////
		//set MouseX & MouseY
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;

	D2Win::D2SetFontSize(1);

	if (isOnCloseBtn(mx, my))			// print popup "close"
	{
		D2Win::D2PrintPopup(D2Lang::D2GetStringFromIndex(0x1030), getXCloseBtn() + getLCloseBtn() / 2, getYCloseBtn() - getHCloseBtn(), WHITE, 1);
	}
	else if (isOnPreviousPageBtn(mx, my))	//print popup "previous page"
	{
		D2Win::D2PrintPopup(STR_PREVIOUS_PAGE, getXPreviousPageBtn() + getLPreviousPageBtn() / 2, getYPreviousPageBtn() - getHPreviousPageBtn(), WHITE, 1);
	}
	else if (isOnNextPageBtn(mx, my))	//print popup "next page"
	{
		D2Win::D2PrintPopup(STR_NEXT_PAGE, getXNextPageBtn() + getLNextPageBtn() / 2, getYNextPageBtn() - getHNextPageBtn(), WHITE, 1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

DWORD __stdcall mouseNewStatsPageTwoLeftDown(sWinMessage* msg)
{
	DWORD x = *D2Client::ptMouseX;
	DWORD y = *D2Client::ptMouseY;
	if (!isOnStatsPage(x, y)) return 1;

	if (isOnCloseBtn(x, y))
	{
		isDownBtn.close = 1;
		D2Client::D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnPreviousPageBtn(x, y))
	{
		isDownBtn.previousPage = 1;
		D2Client::D2PlaySound(4, 0, 0, 0, 0);
	}
	else if (isOnNextPageBtn(x, y))
	{
		isDownBtn.nextPage = 1;
		D2Client::D2PlaySound(4, 0, 0, 0, 0);
	}

	Storm::D2FreeMessage(msg);
	return 0;
}

DWORD __stdcall mouseNewStatsPageTwoLeftUp(sWinMessage* msg)
{
	DWORD x = *D2Client::ptMouseX;
	DWORD y = *D2Client::ptMouseY;
	if (!isOnStatsPage(x, y)) 
		return 1;

	if (isOnCloseBtn(x, y))
	{
		if (isDownBtn.close)
			D2Client::D2TogglePage(2, 1, 0);
	}
	else if (isOnPreviousPageBtn(x, y))
	{
		if (isDownBtn.previousPage)
			GoPreviousStatPage();
	}
	else if (isOnNextPageBtn(x, y))
	{
		if (isDownBtn.nextPage)
			GoNextStatPage();
	}
	D2Client::D2CleanStatMouseUp();
	Storm::D2FreeMessage(msg);
	isDownBtn.all = 0;
	return 0;
}

#endif