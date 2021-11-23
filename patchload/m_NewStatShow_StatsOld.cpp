#include "pch.h"
#ifdef MODULES_NEWSTATSHOW
#define STR_PREVIOUS_PAGE L"上一页"
#define STR_NEXT_PAGE L"下一页"
static struct
{
	union {
		DWORD all;
		struct {
			DWORD previousPage : 1;
			DWORD nextPage : 1;
		};
	};
} isDownBtn;

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



void __stdcall printStatsPageBtns()
{
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;



	if (D2Gfx::D2GetResolution())
	{
		statsBackgroundImages.setFrame(1);
		statsBackgroundImages.draw(getXPreviousPageBtn() - 7, getYPreviousPageBtn() + 8, -1, 5, 0);
	}

	sDrawImageInfo data;
	ZeroMemory(&data, sizeof(data));
	data.pCellFile = D2Client::D2LoadBuySelBtn();

	if (D2Gfx::D2GetResolution())
	{
		data.dwCellNo = 12 + isDownBtn.previousPage;
		D2Gfx::D2DrawImage(&data, getXPreviousPageBtn(), getYPreviousPageBtn(), -1, 5, 0);
	}

	data.dwCellNo = 14 + isDownBtn.nextPage;
	D2Gfx::D2DrawImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);

	D2Win::D2SetFontSize(1);
	if (D2Gfx::D2GetResolution() && isOnPreviousPageBtn(mx, my))	//print popup "previous page"
	{
		D2Win::D2PrintPopup(STR_PREVIOUS_PAGE, getXPreviousPageBtn() + getLPreviousPageBtn() / 2, getYPreviousPageBtn() - getHPreviousPageBtn(), WHITE, 1);
	}
	else if (isOnNextPageBtn(mx, my))
	{
		D2Win::D2PrintPopup(STR_NEXT_PAGE, getXNextPageBtn() + getLNextPageBtn() / 2, getYNextPageBtn() - getHNextPageBtn(), WHITE, 1);
	}
}

UnitAny* __stdcall statsPageMouseDown(sWinMessage* msg)
{
	UnitAny* ptChar = *D2Client::ptPlayerClient;


	if (D2Gfx::D2GetResolution() && isOnPreviousPageBtn(msg->x, msg->y))
	{
		isDownBtn.previousPage = 1;
		D2Client::D2PlaySound(4, 0, 0, 0, 0);
		Storm::D2FreeMessage(msg);
		return NULL;
	}
	else if (isOnNextPageBtn(msg->x, msg->y))
	{
		isDownBtn.nextPage = 1;
		D2Client::D2PlaySound(4, 0, 0, 0, 0);
		Storm::D2FreeMessage(msg);
		return NULL;
	}
	return ptChar;
}

UnitAny* __stdcall statsPageMouseUp(sWinMessage* msg)
{
	UnitAny* ptChar = *D2Client::ptPlayerClient;

	if (D2Gfx::D2GetResolution() && isOnPreviousPageBtn(msg->x, msg->y))
	{
		if (isDownBtn.previousPage)
		{
			GoPreviousStatPage();
			isDownBtn.all = 0;
			Storm::D2FreeMessage(msg);
			return NULL;
		}
	}
	else if (isOnNextPageBtn(msg->x, msg->y))
	{
		//LogMsg("push up left button next page\n");
		if (isDownBtn.nextPage)
		{
			GoNextStatPage();
			isDownBtn.all = 0;
			Storm::D2FreeMessage(msg);
			return NULL;
		}
	}

	isDownBtn.all = 0;
	return ptChar;
}

__declspec(naked) void caller_printStatsPageBtns_111()
{
	__asm
	{
		CALL printStatsPageBtns
		POP EDI
		POP ESI
		POP EBP
		POP EBX
		ADD ESP, 0x370
		RETN
	}
}

__declspec(naked) void caller_statsPageMouseDown()
{
	_asm
	{
		PUSH DWORD PTR SS : [ESP + 0x18]
		CALL statsPageMouseDown
		TEST EAX, EAX
		JE fin_statsPageMouseDown
		RETN
		fin_statsPageMouseDown :
		ADD ESP, 4
			POP EDI
			POP ESI
			POP EBP
			POP EBX
			RETN 4
	}
}

__declspec(naked) void caller_statsPageMouseUp()
{
	__asm
	{
		PUSH EBP
		CALL statsPageMouseUp
		TEST EAX, EAX
		JE fin_statsPageMouseUp
		RETN
		fin_statsPageMouseUp :
		ADD ESP, 4
			POP EDI
			POP ESI
			POP EBP
			POP EBX
			ADD ESP, 8
			RETN 4
	}
}

#endif