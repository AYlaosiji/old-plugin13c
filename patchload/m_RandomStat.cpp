#include"pch.h"
#ifdef MODULES_RANDOMSTAT

static BOOL m_RamdonStat_RandomStat_IsOn = FALSE;
static DWORD m_RamdonStat_RandomStatID;
static DWORD m_RamdonStat_RandomStatValueMAX;
static DWORD m_RamdonStat_RandomExceptStatID;

void m_RamdonStat_LoadCfg()
{
	m_RamdonStat_RandomStat_IsOn = cfgload::GetModuleCfgBool("Ramdon Stat", "Random Stat IsOn");
	m_RamdonStat_RandomStatID = cfgload::GetModuleCfgInt("Ramdon Stat", "Random Stat ID");
	m_RamdonStat_RandomStatValueMAX = cfgload::GetModuleCfgInt("Ramdon Stat", "Random Stat MAX Value");
	m_RamdonStat_RandomExceptStatID=cfgload::GetModuleCfgInt("Ramdon Stat", "Random Stat Except Stat");
}

void m_RamdonStat_Install()
{

}

void m_RamdonStat_UnInstall()
{

}

#ifdef D2SERVER
DWORD m_RamdonStat_Filter(DWORD unk, DWORD statno, UnitAny* unit)
{
	if (m_RamdonStat_RandomStat_IsOn && m_RamdonStat_RandomStatValueMAX&& unit && statno == m_RamdonStat_RandomStatID && m_RamdonStat_RandomStatValueMAX)
	{
		if (m_RamdonStat_RandomExceptStatID)
		{
			if (D2Common::D2GetUnitStat(unit, m_RamdonStat_RandomExceptStatID, 0))
				return 0;
		}
		srand((int)GetTickCount());
		DWORD ret = rand() % m_RamdonStat_RandomStatValueMAX + 1;
		return ret;
	}
	return 0;
}
#endif

#endif