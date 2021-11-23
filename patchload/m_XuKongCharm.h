#define MODULES_XUKONGCHARM
void m_XuKongCharm_LoadCfg();
void m_XuKongCharm_Install();
void m_XuKongCharm_UnInstall();

void m_XuKongCharm_XuKongLoop(GameStruct* pGame, UnitAny* pUnit, DWORD Frame, DWORD Type);

BOOL m_XuKongCharm_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue);