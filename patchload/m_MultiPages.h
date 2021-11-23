#define MODULES_MULTIPAGES

#define MAX_SAVEFILESIZE 0x40000
#define PCPY ((PYPlayerData*)((DWORD)ptChar->ptPlayerData+0x16C)) //PYPlayerData*->ptPYPlayerData

extern char m_UpdateServerClient_ServerSavePath[MAX_PATH];
extern DWORD maxSelfPages;
//extern DWORD maxSharedPages;
extern DWORD nbPagesPerIndex;
extern DWORD nbPagesPerIndex2;
//extern bool active_sharedStash;
//extern bool active_sharedGold;
//extern bool separateHardSoftStash;
//extern char* sharedStashFilename;
//
//extern bool displaySharedSetItemNameInGreen;
extern int posXPreviousBtn, posYPreviousBtn, posXNextBtn, posYNextBtn, /*posXSharedBtn, posYSharedBtn, */posXPreviousIndexBtn, posYPreviousIndexBtn, posXNextIndexBtn, posYNextIndexBtn, posXPutGoldBtn, posYPutGoldBtn, posXTakeGoldBtn, posYTakeGoldBtn;
extern int posXstashGoldTextShow, posYstashGoldTextShow;
//ÄÚ²¿
extern D2DrawCell stashBtnsImages;
//extern D2DrawCell sharedGoldBtnsImages;

#include "m_MultiPages_D2StashFunctions.h"
#include "m_MultiPages_ExtendedSaveFile.h"
#include "m_MultiPages_LoadPlayerData.h"
#include "m_MultiPages_SavePlayerData.h"
#include "m_MultiPages_InterfaceStash.h"
#include "m_MultiPages_PlayerCustomData.h"

void m_MultiPages_LoadCfg();
void m_MultiPages_Install();
void m_MultiPages_UnInstall();

void m_MultiPages_LoadImage();
void m_MultiPages_FreeImage();