#define MODULES_RANDOMSTAT
void m_RamdonStat_LoadCfg();
void m_RamdonStat_Install();
void m_RamdonStat_UnInstall();

DWORD m_RamdonStat_Filter(DWORD unk, DWORD statno, UnitAny* unit);