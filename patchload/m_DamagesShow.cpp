#include"pch.h"
#ifdef MODULES_DAMAAGESHOW
bool m_DamageShow_ShowDamageIsOn = FALSE;

class DMGShow
{
	typedef struct
	{
		DWORD UnitType;
		DWORD UnitID;
		DWORD dmg;
		BYTE nColour;
		int nTransTbl;
		DWORD Tick;//持续多长时间
	}STDRAW, * LPSTDRAW;
public:
	static std::list<STDRAW> DrawList;

	static void RemoveAll()
	{
		DrawList.clear();
	}

	static void DrawLoop()
	{
		if (*D2Client::ptPlayerClient == NULL)
		{
			RemoveAll();
			return;
		}

		for (std::list<STDRAW>::iterator it = DrawList.begin(); it != DrawList.end(); it++)
		{
			DWORD nowtick = GetTickCount();
			if ((*it).Tick < nowtick)
			{
				DrawList.erase(it);
				return;
			}
		}
		while (DrawList.size() > 7) {
			DrawList.pop_back();
		}
		for (std::list<STDRAW>::iterator it = DrawList.begin(); it != DrawList.end(); it++)
		{
			UnitAny* pUnit = D2Client::D2GetClientUnitFromGUID((*it).UnitID, (*it).UnitType);
			if (pUnit && pUnit->pMonPath && (*D2Client::ptPlayerClient) && (*D2Client::ptPlayerClient)->pMonPath)
			{
				long Targetxoff = D2Common::D2GetUnitPosX(pUnit);
				long Targetyoff = D2Common::D2GetUnitPosY(pUnit);
				long Playerxoff = D2Common::D2GetUnitPosX(*D2Client::ptPlayerClient);
				long Playeryoff = D2Common::D2GetUnitPosY(*D2Client::ptPlayerClient);
				Targetxoff = Targetxoff >> 16;
				Targetyoff = Targetyoff >> 16;
				Playerxoff = Playerxoff >> 16;
				Playeryoff = Playeryoff >> 16;
				D2Common::D2MapToAbsScreen(&Targetxoff, &Targetyoff);
				D2Common::D2MapToAbsScreen(&Playerxoff, &Playeryoff);
				int TargetToCenterX = Targetxoff - Playerxoff;
				int TargetToCenterY = Targetyoff - Playeryoff;
				int ScreenMex = (*D2Client::ptScreenSize).x / 2;
				int ScreenMey = (*D2Client::ptScreenSize).y / 2 - 24;//一半-24
				if (D2Client::D2GetUIToggle(UIVar::UIVAR_STATS))ScreenMex = ScreenMex / 2 * 3;
				else if (D2Client::D2GetUIToggle(UIVar::UIVAR_CUBE)) { RemoveAll(); return; }
				else if (D2Client::D2GetUIToggle(UIVar::UIVAR_INVENTORY))ScreenMex = ScreenMex / 2;
				else if (D2Client::D2GetUIToggle(UIVar::UIVAR_WAYPOINT))ScreenMex = ScreenMex / 2 * 3;
				else if (D2Client::D2GetUIToggle(UIVar::UIVAR_QUEST))ScreenMex = ScreenMex / 2 * 3;
				else if (D2Client::D2GetUIToggle(UIVar::UIVAR_SKILLS))ScreenMex = ScreenMex / 2;

				DWORD a = ((*it).Tick - GetTickCount()) / 10;
				D2Win::D2SetFontSize(1);
				wchar_t info[260] = L"";

				swprintf(info,260, L"%d", (*it).dmg>>8);

				D2Win::D2PrintString(info,
					TargetToCenterX + ScreenMex - 10,
					TargetToCenterY + ScreenMey + a - 85,
					(*it).nColour, (*it).nTransTbl);
			}

		}
	}
	//显示一段时间
	static void ShowUnitDamageForAwhile(DWORD pUnitID, DWORD dwdmgmisc,DWORD dmg)
	{
		Dmgmisc dmgmisc = { 0 };
		//是否显示
		memcpy(&dmgmisc, &dwdmgmisc, sizeof(DWORD));
		//查看单位类型
		DWORD UnitType = dmgmisc.bPlayerFlag != (BYTE)0xFF ? (DWORD)dmgmisc.bPlayerFlag : DWORD(-1);
		if (UnitType == DWORD(-1))return;

		//压入显示的list中
		STDRAW data = { UnitType,pUnitID ,dmg ,dmgmisc.color ,0 ,400 + GetTickCount() };
		DrawList.push_back(data);
	}
};
std::list<DMGShow::STDRAW> DMGShow::DrawList;
void m_DamageShow_ShowDamageClient(DWORD pUnitID, DWORD dmg, DWORD dwdmgmisc)
{
	if (!m_DamageShow_ShowDamageIsOn)return;
	return DMGShow::ShowUnitDamageForAwhile(pUnitID, dwdmgmisc, dmg);
}

void m_Damage_ShowDamage_ASM();

void m_DamageShow_LoadCfg()
{
	cfgJson.GetModuleCfgBool("Damage Show", "IsOn", &m_DamageShow_ShowDamageIsOn);
}

void m_DamageShow_Install()
{
	DWORD offset;

	if (m_DamageShow_ShowDamageIsOn)
	{
#ifdef D2SERVER
		offset = D2Game::GetAddress(0xDE36C);
		Memory::SetCursor(offset);
		Memory::ChangeByte(0x5F, 0xE9);
		Memory::ChangeCallA(0x595B5D5E, (DWORD)m_Damage_ShowDamage_ASM);
#endif 
	}
}

void m_DamageShow_UnInstall()
{
	DMGShow::RemoveAll();
}

void m_DamageShow_Draw()
{
	if (m_DamageShow_ShowDamageIsOn)
		DMGShow::DrawLoop();
}

#ifdef D2SERVER

void __fastcall m_Damage_DamageHook(DamageData* pDmg, UnitAny* pAttacker, UnitAny* pDefender, int nDamage)
{
	if (!m_DamageShow_ShowDamageIsOn||!pDmg || !pDefender)return;

	if (!pAttacker || (int)pDmg->dwDmgTotal <= 0)
		return;

	LONG maxdmg = pDmg->dwPhysDamage;
	BYTE color = D2Color::WHITE;
	if (pDmg->dwMagDamage > maxdmg) { maxdmg = pDmg->dwMagDamage; color = D2Color::ORANGE; }
	if (pDmg->dwFireDamage > maxdmg) { maxdmg = pDmg->dwFireDamage; color = D2Color::RED; }
	if (pDmg->dwColdDamage > maxdmg) { maxdmg = pDmg->dwColdDamage; color = D2Color::BLUE; }
	if (pDmg->dwLtngDamage > maxdmg) { maxdmg = pDmg->dwLtngDamage; color = D2Color::YELLOW; }
	if (pDmg->dwPoisDamage > maxdmg) { maxdmg = pDmg->dwPoisDamage; color = D2Color::GREEN; }

	Dmgmisc dmgmisc =
	{
		color ,
		pDefender->nUnitType == UNIT_PLAYER ? (BYTE)UNIT_PLAYER : pDefender->nUnitType == UNIT_MONSTER ? (BYTE)UNIT_MONSTER : (BYTE)0xFF,
		0
	};
	DmgPack dwmisc = { dmgmisc };
	updateAllClient(pDefender->ptGame, UC_DMG, pDefender->nAllocUnitID, pDmg->dwDmgTotal, dwmisc.dwdmgmisc);
}

__declspec(naked) void m_Damage_ShowDamage_ASM()
{
	__asm
	{
		PUSHAD
		PUSH EDI
		PUSH ESI
		MOV EDX, EBX
		MOV ECX, EBP
		CALL m_Damage_DamageHook
		POPAD
		POP EDI
		POP ESI
		POP EBP
		POP EBX
		POP ECX
		RETN 0x10
	}
}


#endif
#endif // MODULES_DAMAAGESHOW

