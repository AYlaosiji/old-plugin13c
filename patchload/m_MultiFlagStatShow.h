#define MODULES_MULTIFLAGSTATSHOW
void m_MultiFlagStatShow_LoadCfg();
void m_MultiFlagStatShow_Install();
void m_MultiFlagStatShow_UnInstall();

BOOL m_MultiFlagStatShow_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue);