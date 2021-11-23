#include"pch.h"
#ifdef MODULES_REDPORTAL
BOOL m_RedPortal_IsOn = FALSE;
DWORD m_RedPortal_SrvDoFunc = 0;
DWORD m_RedPortal_pSpell = 0;

DWORD __fastcall m_RedPortal_D2SkillSrvDoFunc_t(GameStruct* pGame, UnitAny* pUnit, int nSkill, int nSkillLevel);
BOOL __fastcall m_RedPortal__pSpell(GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem1, UnitAny* pItem2, DWORD it, DWORD flag1, DWORD flag2);

void m_RedPortal_LoadCfg()
{
	m_RedPortal_IsOn = cfgload::GetModuleCfgBool("Red Portal", "Red Portal IsOn");
	m_RedPortal_SrvDoFunc = cfgload::GetModuleCfgInt("Red Portal", "Red Portal SrvDoFunc");
	m_RedPortal_pSpell= cfgload::GetModuleCfgInt("Red Portal", "Red Portal pSpell");
}

void m_RedPortal_Install()
{
	if (m_RedPortal_IsOn == FALSE)return;
#ifdef D2SERVER
	DWORD offSet;
	if (m_RedPortal_SrvDoFunc)
	{
		offSet = D2Game::GetAddress(0x1074A8 + m_RedPortal_SrvDoFunc * 4);
		Memory::SetCursor(offSet);
		Memory::ChangeDword(0, (DWORD)m_RedPortal_D2SkillSrvDoFunc_t);
	}

	if (m_RedPortal_pSpell)
	{
		offSet = D2Game::GetAddress(0x10723C + 8 * m_RedPortal_pSpell);
		Memory::SetCursor(offSet);
		Memory::ChangeDword(0x00000000, (DWORD)m_RedPortal__pSpell);
	}
#endif
}

void m_RedPortal_UnInstall()
{

}

#ifdef D2SERVER

BOOL __fastcall DRLG_GetUnitCoords(UnitAny* pUnit, D2Coord* pCoord)
{
	if (!pUnit || !pCoord)
		return FALSE;

	if (pUnit->nUnitType == UNIT_PLAYER || pUnit->nUnitType == UNIT_MONSTER || pUnit->nUnitType == UNIT_MISSILE)
	{
		DynamicPath* pPath = pUnit->pMonPath;//DynamicPath* pMonPath;
		if (!pPath) return FALSE;

		pCoord->nX = (int)pPath->wPosX;
		pCoord->nY = (int)pPath->wPosY;
		return TRUE;
	}
	else
	{
		StaticPath* pPath = pUnit->pItemPath;
		if (!pPath) return FALSE;

		pCoord->nX = pPath->dwPosX;
		pCoord->nY = pPath->dwPosY;

		return TRUE;
	}
	return FALSE;
}

BOOL __fastcall D2CreateRedPortal(GameStruct* pGame, UnitAny* pUnit, int nLevel)
{
	if (!pGame || !pUnit) return FALSE;

	DrlgRoom1* pRoom = D2Common::D2GetRoomFromUnit(pUnit);
	//–ﬁ∏¥’‚¿Ô
	if (!pRoom || nLevel <= 0)
		return FALSE;
	int RoomLevel = D2Common::D2GetLevelNoFromRoom(pRoom);
	int nAct = D2Common::D2GetActFromLevel(RoomLevel); // this will get removed eventually
	int desAct = D2Common::D2GetActFromLevel(nLevel);
	if (nAct != desAct) return FALSE; // but I haven't fixed the "portal must be created in same act as destination" bug yet

	D2Coord Src, Dest = {};

	if (DRLG_GetUnitCoords(pUnit, &Src))
	{
		DrlgRoom1* newroom = D2Game::D2GetFreeCoords(pRoom, &Src, &Dest, FALSE);
		if (!newroom || !newroom->pRoom2)
			return FALSE;

		int LimitXStart = newroom->pRoom2->dwPosX * 5;
		int LimitYStart = newroom->pRoom2->dwPosY * 5;
		int LimitXEnd = newroom->pRoom2->dwPosX * 5 + newroom->pRoom2->dwSizeX * 5;
		int LimitYEnd = newroom->pRoom2->dwPosY * 5 + newroom->pRoom2->dwSizeY * 5;
		if (
			Src.nX< LimitXStart || Src.nX>LimitXEnd || Src.nY< LimitYStart || Src.nY>LimitYEnd
			|| Dest.nX< LimitXStart || Dest.nX>LimitXEnd || Dest.nY< LimitYStart || Dest.nY>LimitYEnd
			)
		{
			return FALSE;
		}

		UnitAny* pObject = D2Game::D2CreateUnit(pGame, pRoom, 60, UNIT_OBJECT, Dest.nX, Dest.nY, 1, 1, 0);

		if (!pObject || !pObject->ptObjectData) return FALSE;

		pObject->ptObjectData->levelID = nLevel;
		//pObject->pObjectData->nPortalLevelEx = nLevel; // Ignore this part here, this is custom code to get rid of 255 levels limit
#define OBJMODE_OPERATING 1
		D2Common::D2SetAnimMode(pObject, OBJMODE_OPERATING);

		UnitAny* pLinkObject = D2Game::D2CreateLinkedPortalInLevel(pGame, pObject, nLevel, 1);
		if (!pLinkObject) return FALSE;

		DrlgRoom1* pLinkRoom = D2Common::D2GetRoomFromUnit(pLinkObject);
		if (!pLinkRoom) return FALSE;

		D2Common::D2UpdateRoomFlags(pRoom, FALSE);
		D2Common::D2UpdateRoomFlags(pLinkRoom, FALSE);
		return TRUE;
	}
	return FALSE;
}

DWORD __fastcall m_RedPortal_D2SkillSrvDoFunc_t(GameStruct* pGame, UnitAny* pUnit, int nSkill, int nSkillLevel)
{
	SkillsBIN* pSkillbin = D2Common::D2GetSkillsTxt(nSkill);
	if (pSkillbin&& pSkillbin->dwParam1)
	{
		return D2CreateRedPortal(pGame, pUnit, pSkillbin->dwParam1);
	}
	return 0;
}

BOOL __fastcall m_RedPortal__pSpell(GameStruct* pGame, UnitAny* pPlayer, UnitAny* pItem1, UnitAny* pItem2, DWORD it, DWORD flag1, DWORD flag2)
{
	if (pGame && pPlayer && pItem1)
	{
		ItemBIN* pItemTxt = D2Common::D2GetItemTxt(pItem1->dwTxtFileNo);
		if(pItemTxt&& pItemTxt->GambleCost)
		{
			return D2CreateRedPortal(pGame, pPlayer, pItemTxt->GambleCost);
		}
	}
	return FALSE;
}
#endif
#endif // MODULES_REDPORTAL
