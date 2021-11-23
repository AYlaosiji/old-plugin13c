#include"pch.h"

#ifdef MODULES_DYNAMICORBS

BOOL m_DynamicOrbs_OrbIsOn = FALSE;

D2DrawCell orbctrllrImages("Sources\\SJ_PATH\\Orb\\800ctrlpnl7");
D2DrawCell orboverlapImages("Sources\\SJ_PATH\\Orb\\overlap");
D2DrawCell manaorbImages( "Sources\\SJ_PATH\\Orb\\ManaOrb");
D2DrawCell otherorbImages( "Sources\\SJ_PATH\\Orb\\LifeOrb");
D2DrawCell amaorbImages( "Sources\\SJ_PATH\\Orb\\AmaOrb");
D2DrawCell sororbImages( "Sources\\SJ_PATH\\Orb\\SorOrb");
D2DrawCell necorbImages( "Sources\\SJ_PATH\\Orb\\NecOrb");
D2DrawCell barorbImages( "Sources\\SJ_PATH\\Orb\\BarOrb");
D2DrawCell asnorbImages( "Sources\\SJ_PATH\\Orb\\AssOrb");
D2DrawCell druorbImages( "Sources\\SJ_PATH\\Orb\\DruOrb");
D2DrawCell palorbImages( "Sources\\SJ_PATH\\Orb\\PalOrb");
D2DrawCell poiorbImages("Sources\\SJ_PATH\\Orb\\LifeOrbPoi");

void __stdcall m_DynamicOrbs_DrawHpOrb();
void __stdcall m_DynamicOrbs_DrawManaOrb();


void m_DynamicOrbs_LoadCfg()
{
	m_DynamicOrbs_OrbIsOn = cfgload::GetModuleCfgBool("Dynamic Orbs", "IsOn");
}

void m_DynamicOrbs_Install()
{
	if (m_DynamicOrbs_OrbIsOn)
	{
		//¶¯Ì¬ÑªÇòÀ²
		//6fad7340 ÑªÁ¿±³¾°(·Ç800)
		//	6fad73ee À¶Á¿±³¾°(·Ç800)
		//	6fad7459 ÑªÁ¿±³¾°(800)
		//	6fad7536 À¶Á¿±³¾°(800)
		DWORD offset;

		offset = D2Client::GetAddress(0x27340);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xE8, 0x83);
		Memory::ChangeDword(0xFFFE5D51, 0x909018C4);

		offset = D2Client::GetAddress(0x273EE);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xE8, 0x83);
		Memory::ChangeDword(0xFFFE5CA3, 0x909018C4);

		offset = D2Client::GetAddress(0x27459);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xE8, 0x83);
		Memory::ChangeDword(0xFFFE5C38, 0x909018C4);

		offset = D2Client::GetAddress(0x27536);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0xE8, 0x83);
		Memory::ChangeDword(0xFFFE5B5B, 0x909018C4);

		offset = D2Client::GetAddress(0x2929F);
		Memory::SetCursor(offset);
		Memory::ChangeCallA((DWORD)0xFFFFE7ED, (DWORD)m_DynamicOrbs_DrawManaOrb);

		offset = D2Client::GetAddress(0x2929A);
		Memory::SetCursor(offset);
		Memory::ChangeCallA((DWORD)0xFFFFE932, (DWORD)m_DynamicOrbs_DrawHpOrb);
	}
}

void m_DynamicOrbs_UnInstall()
{

}

void __stdcall m_DynamicOrbs_DrawHpOrb()
{
	UnitAny* pPlayer = *D2Client::ptPlayerClient;
	if (!pPlayer)return;

	int nEnergy = D2Common::D2GetUnitStat(pPlayer, STATS_HP, 0);
	int nMaxEnergy = D2Common::D2GetUnitStat(pPlayer, STATS_MAXHP, 0);
	nEnergy = nEnergy / 256;
	nMaxEnergy = nMaxEnergy / 256;

	if (!nMaxEnergy)return;

	int nOrbSize = int(nEnergy * 100 / nMaxEnergy);
	if (nOrbSize > 100)nOrbSize = 100;

	//ÑªÁ¿Çò±³¾°
	orbctrllrImages.setFrame(0);
	orbctrllrImages.draw(32, D2Client::ptScreenSize->y, -1, 5, NULL);

	//ÑªÁ¿Çòoverlap
	orboverlapImages.setFrame(0);
	orboverlapImages.draw(32, D2Client::ptScreenSize->y - 13, -1, 5, NULL);

	//ÑªÁ¿Çò
	int MaxFrames = 68;
	if (D2Common::D2GetUnitState(pPlayer, 2))
	{
		poiorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		poiorbImages.drawVerticalCrop(32, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
	}
	else
	{
		otherorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		otherorbImages.drawVerticalCrop(32, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
	}
}

void __stdcall m_DynamicOrbs_DrawManaOrb()
{
	UnitAny* pPlayer = *D2Client::ptPlayerClient;
	if (!pPlayer)return;

	int nEnergy = D2Common::D2GetUnitStat(pPlayer, STATS_MANA, 0);
	int nMaxEnergy = D2Common::D2GetUnitStat(pPlayer, STATS_MAXMANA, 0);
	if (!nMaxEnergy)return;

	int nOrbSize = nEnergy * 100 / nMaxEnergy;
	if (nOrbSize > 100)nOrbSize = 100;

	sDrawImageInfo data;
	ZeroMemory(&data, sizeof(data));

	//·¨Á¦Çò±³¾°
	orbctrllrImages.setFrame(5);
	orbctrllrImages.draw(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y, -1, 5, NULL);

	//·¨Á¦Çòoverlap
	orboverlapImages.setFrame(1);
	orboverlapImages.draw(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 13, -1, 5, NULL);


	//·¨Á¦Çò
	int MaxFrames = 68;
	switch (pPlayer->dwTxtFileNo)
	{
	case(D2PlayerClass::D2PC_AMAZON):
		amaorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		amaorbImages.drawVerticalCrop(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
		break;
	case(D2PlayerClass::D2PC_SORCERESS):
		sororbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		sororbImages.drawVerticalCrop(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
		break;
	case(D2PlayerClass::D2PC_NECROMANCER):
		necorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		necorbImages.drawVerticalCrop(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
		break;
	case(D2PlayerClass::D2PC_BARBARIAN):
		barorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		barorbImages.drawVerticalCrop(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
		break;
	case(D2PlayerClass::D2PC_ASSASSIN):
		asnorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		asnorbImages.drawVerticalCrop(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
		break;
	case(D2PlayerClass::D2PC_DRUID):
		druorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		druorbImages.drawVerticalCrop(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
		break;
	case(D2PlayerClass::D2PC_PALADIN):
		palorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		palorbImages.drawVerticalCrop(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
		break;
	default:
		manaorbImages.setFrame((GetTickCount() >> 6) % MaxFrames);
		manaorbImages.drawVerticalCrop(D2Client::ptScreenSize->x - 111, D2Client::ptScreenSize->y - 16, 0, nOrbSize, 5);
		break;
	}
}

void m_DynamicOrbs_LoadImage()
{
	if (m_DynamicOrbs_OrbIsOn)
	{
		orbctrllrImages.loadFileSafely();
		orboverlapImages.loadFileSafely();
		manaorbImages.loadFileSafely();
		otherorbImages.loadFileSafely();
		amaorbImages.loadFileSafely();
		sororbImages.loadFileSafely();
		necorbImages.loadFileSafely();
		barorbImages.loadFileSafely();
		asnorbImages.loadFileSafely();
		druorbImages.loadFileSafely();
		palorbImages.loadFileSafely();
		poiorbImages.loadFileSafely();
	}
}

void m_DynamicOrbs_FreeImage()
{
	if (m_DynamicOrbs_OrbIsOn)
	{
		orbctrllrImages.unloadFileSafely();
		orboverlapImages.unloadFileSafely();
		manaorbImages.unloadFileSafely();
		otherorbImages.unloadFileSafely();
		amaorbImages.unloadFileSafely();
		sororbImages.unloadFileSafely();
		necorbImages.unloadFileSafely();
		barorbImages.unloadFileSafely();
		asnorbImages.unloadFileSafely();
		druorbImages.unloadFileSafely();
		palorbImages.unloadFileSafely();
		poiorbImages.unloadFileSafely();
	}
}

#endif