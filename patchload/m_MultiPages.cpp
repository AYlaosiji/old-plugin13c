#include"pch.h"
#ifdef MODULES_MULTIPAGES

BOOL m_MultiPages_IsOn = TRUE;
char m_UpdateServerClient_ServerSavePath[MAX_PATH] = "D:\\Server\\D2Server\\PVPGN\\var\\charsave\\";

int posXPreviousBtn = 120;
int posYPreviousBtn = 54;
int posXNextBtn = 165;
int posYNextBtn = 54;
int posXPreviousIndexBtn = 75;
int posYPreviousIndexBtn = 54;
int posXNextIndexBtn = 210;
int posYNextIndexBtn = 54;
int posXstashGoldTextShow = 78;
int posYstashGoldTextShow = 415;

DWORD maxSelfPages = 99;
DWORD nbPagesPerIndex = 10;
DWORD nbPagesPerIndex2 = 100;

//ÄÚ²¿
D2DrawCell stashBtnsImages("Sources\\SJ_PATH\\StashBtns");
//D2DrawCell sharedGoldBtnsImages("Sources\\SJ_PATH\\SharedGoldBtns");

void m_MultiPages_LoadCfg()
{
	m_MultiPages_IsOn = cfgload::GetModuleCfgBool("Multi Pages", "Load New Pages");

	cfgload::GetModuleCfgString("Multi Pages", "Server Save Path", m_UpdateServerClient_ServerSavePath, MAX_PATH);

	maxSelfPages = cfgload::GetModuleCfgInt("Multi Pages", "maxSelfPages");
	nbPagesPerIndex = cfgload::GetModuleCfgInt("Multi Pages", "nbPagesPerIndex");
	nbPagesPerIndex2 = cfgload::GetModuleCfgInt("Multi Pages", "nbPagesPerIndex2");
	posXPreviousBtn = cfgload::GetModuleCfgInt("Multi Pages", "posXPreviousBtn");
	posYPreviousBtn = cfgload::GetModuleCfgInt("Multi Pages", "posYPreviousBtn");
	posXNextBtn = cfgload::GetModuleCfgInt("Multi Pages", "posXNextBtn");
	posYNextBtn = cfgload::GetModuleCfgInt("Multi Pages", "posYNextBtn");
	posXPreviousIndexBtn = cfgload::GetModuleCfgInt("Multi Pages", "posXPreviousIndexBtn");
	posYPreviousIndexBtn = cfgload::GetModuleCfgInt("Multi Pages", "posYPreviousIndexBtn");
	posXNextIndexBtn = cfgload::GetModuleCfgInt("Multi Pages", "posXNextIndexBtn");
	posYNextIndexBtn = cfgload::GetModuleCfgInt("Multi Pages", "posYNextIndexBtn");
	posXstashGoldTextShow = cfgload::GetModuleCfgInt("Multi Pages", "posXstashGoldTextShow");
	posYstashGoldTextShow = cfgload::GetModuleCfgInt("Multi Pages", "posYstashGoldTextShow");
}

void m_MultiPages_Install()
{
	if (m_MultiPages_IsOn)
	{
		Install_LoadPlayerData();
		Install_SavePlayerData();
		Install_InterfaceStash();
		Install_PlayerCustomData();
		Install_MultiPageStash();
	}
}

void m_MultiPages_UnInstall()
{

}

void m_MultiPages_LoadImage()
{
	if (m_MultiPages_IsOn)
	{
		stashBtnsImages.loadFileSafely();
	}
}

void m_MultiPages_FreeImage()
{
	if (m_MultiPages_IsOn)
	{
		stashBtnsImages.unloadFileSafely();
	}
}
#endif // MODULES_MULTIPAGES