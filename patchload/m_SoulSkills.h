#define MODULES_SOULSKILLS
void m_SoulSkills_LoadCfg();
void m_SoulSkills_Install();
void m_SoulSkills_UnInstall();

void m_SoulSkills_Draw();

BOOL m_SoulSkills_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue);

void m_SoulSkills_ClearSoulsLastHit(GameStruct* pDmg, UnitAny* Killed, void* unk, int nDamage, UnitAny* Killer, DamageData* pdmg);
void m_SoulSkills_AddPlayerSoul(NetClient* pClient, UnitAny* pPlayer, DWORD unkexp);