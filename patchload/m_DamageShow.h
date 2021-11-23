#define MODULES_DAMAAGESHOW


void m_DamageShow_LoadCfg();
void m_DamageShow_Install();
void m_DamageShow_UnInstall();

void m_DamageShow_ShowDamageClient(DWORD pUnitID, DWORD dwdmgmisc, DWORD dmg);
void m_DamageShow_Draw();