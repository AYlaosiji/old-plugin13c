#define MODULES_PLAYERDEATHKILLCOUNT
void m_PlayerDeathKillCount_LoadCfg();
void m_PlayerDeathKillCount_Install();
void m_PlayerDeathKillCount_UnInstall();

void m_PlayerDeathKillCount_AddPlayerDeathLastHit(GameStruct* pDmg, UnitAny* Killed, void* unk, int nDamage, UnitAny* Killer, DamageData* pdmg);
void m_PlayerDeathKillCount_AddPlayerKill(NetClient* pClient, UnitAny* pPlayer, DWORD unkexp);

BOOL m_PlayerDeathKillCount_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue);