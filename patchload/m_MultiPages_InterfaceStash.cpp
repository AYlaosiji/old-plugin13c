#include"pch.h"
#ifdef MODULES_MULTIPAGES

#define STR_SHARED_PAGE_NUMBER L"页数(共享):%d"
#define STR_PERSONAL_PAGE_NUMBER L"页数(个人):%d"
#define STR_STASH_PREVIOUS_INDEX L"前%d页,共%d页"
#define STR_STASH_NEXT_INDEX L"后%d页,共%d页"
#define STR_STASH_PREVIOUS_PAGE L"上一页"
#define STR_STASH_NEXT_PAGE L"下一页"

static struct
{
	union {
		DWORD all;
		struct {
			DWORD previous : 1;
			DWORD next : 1;
			DWORD toggleToSharedStash : 1;
			DWORD previousIndex : 1;
			DWORD nextIndex : 1;
			DWORD putGold : 1;
			DWORD takeGold : 1;
		};
	};
} isDownBtn;


DWORD	getXPreviousBtn() { return RX(posXPreviousBtn); }
#define	getLPreviousBtn()		32
DWORD	getYPreviousBtn() { return RY(posYPreviousBtn); }
#define	getHPreviousBtn()		32

DWORD	getXNextBtn() { return RX(posXNextBtn); }//?169:SEL_X(0x63, 0x63, 0xCF, 0xA0));}
#define	getLNextBtn()			32
DWORD	getYNextBtn() { return RY(posYNextBtn); }
#define	getHNextBtn()			32

//DWORD	getXSharedBtn() { return RX(posXSharedBtn); }//17:SEL_X(0xE3, 0xE3, 0x6F, 0x10));}//0xD8
//#define	getLSharedBtn()			32
//DWORD	getYSharedBtn() { return RY(posYSharedBtn); }
//#define	getHSharedBtn()			32

DWORD	getXPreviousIndexBtn() { return RX(posXPreviousIndexBtn); }//73:SEL_X(0x18, 0x60, 0x8F, 0x60));}
#define	getLPreviousIndexBtn()	32
DWORD	getYPreviousIndexBtn() { return RY(posYPreviousIndexBtn); }
#define	getHPreviousIndexBtn()	32

DWORD	getXNextIndexBtn() { return RX(posXNextIndexBtn); }//217:SEL_X(0x128, 0xC0, 0xEF, 0xC0));}
#define	getLNextIndexBtn()		32
DWORD	getYNextIndexBtn() { return RY(posYNextIndexBtn); }
#define	getHNextIndexBtn()		32


DWORD	getXstashGoldTextShow() { return RX(posXstashGoldTextShow); }
DWORD	getYstashGoldTextShow() { return RY(posYstashGoldTextShow); }

//closeBtn x: D2C=0x113 LOD=0x110(0->0x28)		y: D2C=0x41 LOD=0x40 (-0x23 -> 5)


#define isOnButtonNextStash(x,y) isOnRect(x, y, getXNextBtn(), getYNextBtn(), getLNextBtn(), getHNextBtn())
#define isOnButtonPreviousStash(x,y) isOnRect(x, y, getXPreviousBtn(), getYPreviousBtn(), getLPreviousBtn(), getHPreviousBtn())
#define isOnButtonToggleSharedStash(x,y) isOnRect(x, y, getXSharedBtn(), getYSharedBtn(), getLSharedBtn(), getHSharedBtn())
#define isOnButtonNextIndexStash(x,y) isOnRect(x, y, getXNextIndexBtn(), getYNextIndexBtn(), getLNextIndexBtn(), getHNextIndexBtn())
#define isOnButtonPreviousIndexStash(x,y) isOnRect(x, y, getXPreviousIndexBtn(), getYPreviousIndexBtn(), getLPreviousIndexBtn(), getHPreviousIndexBtn())



void* __stdcall printBtns()
{
	UnitAny* ptChar = *D2Client::ptPlayerClient;


	//sDrawImageInfo data;
	//ZeroMemory(&data, sizeof(data));
	//setImage(&data, stashBtnsImages);

	//setFrame(&data, 0 + isDownBtn.previous);
	//D2Gfx::D2DrawImage(&data, getXPreviousBtn(), getYPreviousBtn(), -1, 5, 0);
	stashBtnsImages.setFrame(0 + isDownBtn.previous);
	stashBtnsImages.draw(getXPreviousBtn(), getYPreviousBtn(), -1, 5, 0);

	//setFrame(&data, 2 + isDownBtn.next);
	//D2Gfx::D2DrawImage(&data, getXNextBtn(), getYNextBtn(), -1, 5, 0);
	stashBtnsImages.setFrame(2 + isDownBtn.next);
	stashBtnsImages.draw(getXNextBtn(), getYNextBtn(), -1, 5, 0);

	//setFrame(&data, 8 + isDownBtn.previousIndex);
	//D2Gfx::D2DrawImage(&data, getXPreviousIndexBtn(), getYPreviousIndexBtn(), -1, 5, 0);
	stashBtnsImages.setFrame(8 + isDownBtn.previousIndex);
	stashBtnsImages.draw(getXPreviousIndexBtn(), getYPreviousIndexBtn(), -1, 5, 0);

	//setFrame(&data, 10 + isDownBtn.nextIndex);
	//D2Gfx::D2DrawImage(&data, getXNextIndexBtn(), getYNextIndexBtn(), -1, 5, 0);
	stashBtnsImages.setFrame(10 + isDownBtn.nextIndex);
	stashBtnsImages.draw(getXNextIndexBtn(), getYNextIndexBtn(), -1, 5, 0);

	//if (active_sharedStash)
	//{
	//	setFrame(&data, 4 + isDownBtn.toggleToSharedStash + (PCPY->showSharedStash ? 2 : 0));
	//	DWORD x = getXSharedBtn();
	//	DWORD y = getYSharedBtn();
	//	D2Gfx::D2DrawImage(&data, getXSharedBtn(), getYSharedBtn(), -1, 5, 0);
	//}

	//if (active_sharedGold)
	//{
	//	setImage(&data, sharedGoldBtnsImages);
	//	setFrame(&data, 0 + isDownBtn.putGold);
	//	D2Gfx::D2DrawImage(&data, getXPutGoldBtn(), getYPutGoldBtn(), -1, 5, 0);

	//	setFrame(&data, 2 + isDownBtn.takeGold);
	//	D2Gfx::D2DrawImage(&data, getXTakeGoldBtn(), getYTakeGoldBtn(), -1, 5, 0);
	//}

	LPWSTR lpText;
	WCHAR text[100];
	DWORD mx = *D2Client::ptMouseX;
	DWORD my = *D2Client::ptMouseY;

	D2Win::D2SetFontSize(1);

	if (isOnButtonPreviousStash(mx, my)) 
	{
		lpText = STR_STASH_PREVIOUS_PAGE;
		D2Win::D2PrintPopup(lpText, getXPreviousBtn() + getLPreviousBtn() / 2, getYPreviousBtn() - getHPreviousBtn(), WHITE, 1);

	}
	else if (isOnButtonNextStash(mx, my)) 
	{
		lpText = STR_STASH_NEXT_PAGE;
		D2Win::D2PrintPopup(lpText, getXNextBtn() + getLNextBtn() / 2, getYNextBtn() - getHNextBtn(), WHITE, 1);

	}
	else if (isOnButtonPreviousIndexStash(mx, my)) 
	{
		_snwprintf(text, sizeof(text), STR_STASH_PREVIOUS_INDEX, nbPagesPerIndex, nbPagesPerIndex2);
		D2Win::D2PrintPopup(text, getXPreviousIndexBtn() + getLPreviousIndexBtn() / 2, getYPreviousIndexBtn() - getHPreviousIndexBtn(), 0, 0);

	}
	else if (isOnButtonNextIndexStash(mx, my)) 
	{
		_snwprintf(text, sizeof(text), STR_STASH_NEXT_INDEX, nbPagesPerIndex, nbPagesPerIndex2);
		D2Win::D2PrintPopup(text, getXNextIndexBtn() + getLNextIndexBtn() / 2, getYNextIndexBtn() - getHNextIndexBtn(), WHITE, 1);

	}
	//else if (active_sharedStash && isOnButtonToggleSharedStash(mx, my)) 
	//{
	//	lpText = PCPY->showSharedStash ? STR_TOGGLE_TO_PERSONAL : STR_TOGGLE_TO_SHARED;
	//	D2Win::D2PrintPopup(lpText, getXSharedBtn() + getLSharedBtn() / 2, getYSharedBtn() - getHSharedBtn(), WHITE, 1);
	//}
	//else if (active_sharedGold && isOnButtonPutGold(mx, my)) {
	//	lpText = STR_PUT_GOLD;
	//	D2Win::D2PrintPopup(lpText, getXPutGoldBtn() + getLPutGoldBtn() / 2, getYPutGoldBtn() - getHPutGoldBtn(), WHITE, 1);

	//}
	//else if (active_sharedGold && isOnButtonTakeGold(mx, my)) {
	//	lpText = STR_TAKE_GOLD;
	//	D2Win::D2PrintPopup(lpText, getXTakeGoldBtn() + getLTakeGoldBtn() / 2, getYTakeGoldBtn() - getHTakeGoldBtn(), WHITE, 1);
	//}
	return D2Client::D2LoadBuySelBtn();
}

DWORD __stdcall manageBtnDown(sWinMessage* msg)
{
	if (isOnButtonPreviousStash(msg->x, msg->y))
		isDownBtn.previous = 1;
	else if (isOnButtonNextStash(msg->x, msg->y))
		isDownBtn.next = 1;
	//else if (active_sharedStash && isOnButtonToggleSharedStash(msg->x, msg->y))
	//	isDownBtn.toggleToSharedStash = 1;
	else if (isOnButtonPreviousIndexStash(msg->x, msg->y))
		isDownBtn.previousIndex = 1;
	else if (isOnButtonNextIndexStash(msg->x, msg->y))
		isDownBtn.nextIndex = 1;
	//else if (active_sharedGold && isOnButtonPutGold(msg->x, msg->y))
	//	isDownBtn.putGold = 1;
	//else if (active_sharedGold && isOnButtonTakeGold(msg->x, msg->y))
	//	isDownBtn.takeGold = 1;
	else return 0;

	D2Client::D2PlaySound(4, 0, 0, 0, 0);
	Storm::D2FreeMessage(msg);
	return 1;
}

DWORD __stdcall manageBtnUp(sWinMessage* msg)
{
	UnitAny* ptChar = *D2Client::ptPlayerClient;

	if (isOnButtonPreviousStash(msg->x, msg->y)) {
		//LogMsg("push up left button previous\n");
		if (isDownBtn.previous)
			if (GetKeyState(VK_SHIFT) < 0)
				updateServer(US_SELECT_PREVIOUS2);
			else
				updateServer(US_SELECT_PREVIOUS);

	}
	else if (isOnButtonNextStash(msg->x, msg->y)) {
		//LogMsg("push up left button next\n");
		if (isDownBtn.next)
			if (GetKeyState(VK_SHIFT) < 0)
				updateServer(US_SELECT_NEXT2);
			else
				updateServer(US_SELECT_NEXT);

	}
	//else if (active_sharedStash && isOnButtonToggleSharedStash(msg->x, msg->y)) {
	//	//LogMsg("push up left button shared\n");
	//	if (isDownBtn.toggleToSharedStash)
	//		if (PCPY->showSharedStash)
	//			updateServer(US_SELECT_SELF);
	//		else
	//			updateServer(US_SELECT_SHARED);

	//}
	else if (isOnButtonPreviousIndexStash(msg->x, msg->y)) {
		//LogMsg("select left button previous index\n");
		if (isDownBtn.previousIndex)
			if (GetKeyState(VK_SHIFT) < 0)
				updateServer(US_SELECT_PREVIOUS_INDEX2);
			else
				updateServer(US_SELECT_PREVIOUS_INDEX);

	}
	else if (isOnButtonNextIndexStash(msg->x, msg->y)) {
		//LogMsg("push up left button next index\n");
		if (isDownBtn.nextIndex)
			if (GetKeyState(VK_SHIFT) < 0)
				updateServer(US_SELECT_NEXT_INDEX2);
			else
				updateServer(US_SELECT_NEXT_INDEX);

	}
	//else if (active_sharedGold && isOnButtonPutGold(msg->x, msg->y)) {
	//	if (isDownBtn.putGold)
	//		updateServer(US_PUTGOLD);

	//}
	//else if (active_sharedGold && isOnButtonTakeGold(msg->x, msg->y)) {
	//	if (isDownBtn.takeGold)
	//		updateServer(US_TAKEGOLD);

	//}
	else return 0;

	return 1;
}

void __fastcall printPageNumber(LPWSTR maxGoldText, DWORD& x, DWORD& y, DWORD color, DWORD bfalse)
{
	int fixx = getXstashGoldTextShow();
	int fixy = getYstashGoldTextShow();
	UnitAny* ptChar = *D2Client::ptPlayerClient;
	WCHAR popupText[100];

	if (PCPY->currentStash)
	{
		bool isShared = PCPY->currentStash->isShared;
		bool isIndex = PCPY->currentStash->isIndex;
		DWORD currentId = PCPY->currentStash->id;

		if (PCPY->currentStash->name && PCPY->currentStash->name[0])
			mbstowcs(popupText, PCPY->currentStash->name, 50);//strlen(PCPY->currentStash->name)+1
		else _snwprintf(popupText, sizeof(popupText), isShared ? STR_SHARED_PAGE_NUMBER : STR_PERSONAL_PAGE_NUMBER, currentId + 1);
		D2Win::D2PrintString(popupText, fixx, fixy, isShared ? (isIndex ? CRYSTAL_RED : RED) : (isIndex ? BRIGHT_WHITE : WHITE), bfalse);
	}
	else 
	{
		_snwprintf(popupText, sizeof(popupText), L"NO_SELECTED_PAGE");
		D2Win::D2PrintString(popupText, fixx, fixy, WHITE, bfalse);
	}

	////printGoldMaxPopup
	//DWORD mx = *D2Client::ptMouseX;
	//DWORD my = *D2Client::ptMouseY;
	//if ((RX(0x5E) < mx) && (mx < RX(0xF8)) && (RY(0x1C8) < my) && (my < RY(0x1B6)))
	//{
	//	if (active_sharedGold)
	//	{
	//		_snwprintf(popupText, sizeof(popupText), L"%s\n%s: %u", maxGoldText, STR_SHARED_GOLD_QUANTITY, PCPY->sharedGold);
	//		DWORD x = D2Win::D2Win::D2GetPixelLen(maxGoldText);
	//		DWORD x2 = D2Win::D2GetPixelLen(popupText) - x;
	//		D2Win::D2PrintPopup(popupText, RX(0xA8 - max(x, x2) / 2), RY(0x1CA), WHITE, 0);
	//	}
	//	else
	//		D2Win::D2PrintPopup(maxGoldText, RX(0xA8), RY(0x1CA), WHITE, 1);
	//}
}


static Stash* curStash = NULL;
static DWORD currentSawStash = 0;
UnitAny* __stdcall getNextItemForSet(UnitAny* ptItem)
{
	UnitAny* item = ptItem ? D2Common::D2GetNextInventoryItem(ptItem) : NULL;
	if (item) return item;

	if (!curStash)
	{
		UnitAny* ptChar = *D2Client::ptPlayerClient;
		switch (currentSawStash)
		{
		case 0: curStash = PCPY->selfStash;
			//currentSawStash = displaySharedSetItemNameInGreen ? 1 : 2;
			currentSawStash = 2;
			break;
		case 1: curStash = PCPY->sharedStash;
			currentSawStash = 2;
			break;
		default:return NULL;
		}
	}
	else {
		curStash = curStash->nextStash;
	}
	if (curStash)
	{
		item = curStash->ptListItem;
		if (item) return item;
	}
	return getNextItemForSet(item);
}

UnitAny* __stdcall initGetNextItemForSet(UnitInventory* ptInventory)
{
	UnitAny* ptChar = *D2Client::ptPlayerClient;
	if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
	if (!PCPY) return NULL;

	curStash = NULL;
	currentSawStash = 0;
	UnitAny* item = D2Common::D2GetFirstInventoryItem(ptInventory);
	if (item) return item;
	return getNextItemForSet(item);
}

__declspec(naked) void caller_manageBtnDown_111()
{
	__asm
	{
		PUSH EBP
		CALL manageBtnDown
		TEST EAX, EAX
		JE IS_NOT_ON_BUTTON
		POP EDX
		MOV EDX, DWORD PTR DS : [EDX + 0x10]
		MOV DWORD PTR DS : [EDX] , 1
		POP EDI
		POP ESI
		POP EBP
		POP EBX
		RETN 4
		IS_NOT_ON_BUTTON :
		JMP D2Client::D2ClickOnStashButton
	}
}

__declspec(naked) void caller_manageBtnUp_111()
{
	__asm
	{
		PUSH EBX
		CALL manageBtnUp
		MOV isDownBtn.all, 0
		TEST EAX, EAX
		JE IS_NOT_ON_BUTTON
		POP EDX
		MOV EDX, DWORD PTR DS : [EDX + 0x1A]
		MOV DWORD PTR DS : [EDX] , 0
		SUB EDX, 8
		MOV DWORD PTR DS : [EDX] , 0
		ADD EDX, 4
		MOV DWORD PTR DS : [EDX] , 0
		ADD EDX, 0x68
		MOV DWORD PTR DS : [EDX] , 0
		POP EDI
		POP ESI
		POP EBP
		POP EBX
		POP ECX
		RETN 4
		IS_NOT_ON_BUTTON:
		JMP D2Client::D2ClickOnStashButton
	}
}

__declspec(naked) void initBtnsStates()
{
	__asm
	{
		MOV isDownBtn.all, 0
		ADD ESP, 0x104
		RETN
	}
}

void Install_InterfaceStash()
{
	DWORD offset = 0;

	//加载图片
	// Print button images
	offset = D2Client::GetAddress(0x99A56);
	Memory::SetCursor(offset);
	Memory::ChangeCallC((DWORD)D2Client::D2LoadBuySelBtn, (DWORD)printBtns);

	// print page number
	offset = D2Client::GetAddress(0x99A33);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Win::D2PrintString, (DWORD)printPageNumber);

	// Manage mouse down (Play sound)
	offset = D2Client::GetAddress(0x9B8A6);
	Memory::SetCursor(offset);
	Memory::ChangeCallC((DWORD)D2Client::D2ClickOnStashButton, (DWORD)caller_manageBtnDown_111);

	// Manage mouse up
	offset = D2Client::GetAddress(0x9B6D9);
	Memory::SetCursor(offset);
	Memory::ChangeCallC((DWORD)D2Client::D2ClickOnStashButton, (DWORD)caller_manageBtnUp_111);

	// init state of button on open stash page
	offset = D2Client::GetAddress(0x8CC3A);
	Memory::SetCursor(offset);
	Memory::ChangeByte(0x81, 0xE9);
	Memory::ChangeCallA(0x000104C4, (DWORD)initBtnsStates);
	Memory::ChangeByte(0x00, 0x90);

	// init the search of print in green the item set name we have in stash
	offset = D2Client::GetAddress(0x8D434);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Common::D2GetFirstInventoryItem, (DWORD)initGetNextItemForSet);

	// Get next item for print in green the item set name we have in stash
	offset = D2Client::GetAddress(0x8D4CB);
	Memory::SetCursor(offset);
	Memory::ChangeCallB((DWORD)D2Common::D2GetNextInventoryItem, (DWORD)getNextItemForSet);

}

void UnInstall_InterfaceStash()
{

}
/*================================= END OF FILE =================================*/
#endif