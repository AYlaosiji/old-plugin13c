#define MODULES_NEWSTATSHOW
#include"m_NewStatShowPre.h"//����
#include "m_NewStatShow_StatsOld.h"//�������
#include"m_NewStatShow_Stats.h"
#include "m_NewStatShow_StatsPageTwo.h"

extern D2DrawCell newStatsInterfaceImages;
extern D2DrawCell statsBackgroundImages;

void m_NewStatShow_LoadCfg();
void m_NewStatShow_Install();
void m_NewStatShow_UnInstall();

void m_NewStatShow_LoadImage();
void m_NewStatShow_FreeImage();
