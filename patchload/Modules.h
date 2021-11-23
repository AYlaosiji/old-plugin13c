#ifdef MODULES_INSTALL
#define LOAD_MODULE(x) m_##x##_Install();
#endif

#ifdef MODULES_UNINSTALL
#define LOAD_MODULE(x) m_##x##_UnInstall();
#endif

#ifdef MODULES_CONFIGLOAD
#define LOAD_MODULE(x) m_##x##_LoadCfg();
#endif

#ifdef LOAD_MODULE

#ifdef MODULES_LANUNCHINFO
LOAD_MODULE(LaunchInfo)
#endif

#ifdef MODULES_HIGHRESOLUTION
LOAD_MODULE(HighResolution)
#endif

#ifdef MODULES_GAMEEXEDRAWMODEFIX
LOAD_MODULE(GameExeDrawModeFix)
#endif

#ifdef MODULES_DRAWFUNCTIONS
LOAD_MODULE(DrawFunctions)
#endif

#ifdef MODULES_UPDATESERVERCLIENT
LOAD_MODULE(UpdateServerClient)
#endif

#ifdef MODULES_NEWSTATDESC
LOAD_MODULE(NewStatDesc)
#endif 

#ifdef MODULE_STATITEMEXTENDED
LOAD_MODULE(StatItemExtended)
#endif

#ifdef MODULE_LASTHITEVENT
LOAD_MODULE(LastHitEvent)
#endif

#ifdef MODULES_TIMEREVENT
LOAD_MODULE(TimerEvent)
#endif

#ifdef MODULES_NEWCUBEMAINOP
LOAD_MODULE(NewCubemainOP)
#endif

#ifdef MODULES_STATFILTER
LOAD_MODULE(StatFilter)
#endif


#ifdef MODULES_DRAWFUNCTIONS
#ifdef MODULES_UPDATESERVERCLIENT
#ifdef MODULES_DAMAAGESHOW
LOAD_MODULE(DamageShow)
#endif
#endif
#endif

#ifdef MODULES_UPDATESERVERCLIENT
#ifdef MODULES_MULTIPAGES
LOAD_MODULE(MultiPages)
#endif
#endif


#ifdef MODULES_UPDATESERVERCLIENT
#ifdef MODULES_32KLIFEFIX
LOAD_MODULE(32KLifeFix)
#endif
#endif

#ifdef MODULES_DYNAMICITEMS
LOAD_MODULE(DynamicItems)
#endif

#ifdef MODULES_DRAWFUNCTIONS
#ifdef MODULES_DYNAMICORBS
LOAD_MODULE(DynamicOrbs)
#endif
#endif


#ifdef MODULES_DRAWFUNCTIONS
#ifdef MODULES_NEWSTATSHOW
LOAD_MODULE(NewStatShow)
#endif
#endif

#ifdef MODULES_EQUIPEDPET
LOAD_MODULE(EquipedPet)
#endif

#ifdef MODULES_NEWSTATDESC
#ifdef MODULE_STATITEMEXTENDED
#ifdef MODULES_MAGICBAG
LOAD_MODULE(MagicBag)
#endif
#endif
#endif

#ifdef MODULES_NEWSTATDESC
#ifdef MODULE_LASTHITEVENT
#ifdef MODULES_PLAYERDEATHKILLCOUNT
LOAD_MODULE(PlayerDeathKillCount)
#endif
#endif
#endif

#ifdef MODULES_DRAWFUNCTIONS
#ifdef MODULE_LASTHITEVENT
#ifdef MODULES_NEWSTATDESC
#ifdef MODULE_STATITEMEXTENDED
#ifdef MODULES_SOULSKILLS
LOAD_MODULE(SoulSkills)
#endif
#endif
#endif
#endif
#endif

#ifdef MODULE_STATITEMEXTENDED
#ifdef MODULE_LASTHITEVENT
#ifdef MODULES_KUILEICHARM
LOAD_MODULE(KuiLeiCharm)
#endif
#endif
#endif

#ifdef MODULES_TIMEREVENT
#ifdef MODULE_STATITEMEXTENDED
#ifdef MODULES_NEWSTATDESC
#ifdef MODULES_XUKONGCHARM
LOAD_MODULE(XuKongCharm)
#endif
#endif
#endif
#endif

#ifdef MODULES_REDPORTAL
LOAD_MODULE(RedPortal)
#endif

#ifdef MODULES_SAVEFILELIMIT
LOAD_MODULE(SaveFileLimit)
#endif

#ifdef MODULES_CONVENIENTGAME
LOAD_MODULE(ConvenientGame)
#endif

#ifdef MODULES_DROP
LOAD_MODULE(Drop)
#endif

#ifdef MODULES_LEVELEXTEND
LOAD_MODULE(LevelExtended)
#endif


#ifdef MODULES_MISCFUNCTIONS
LOAD_MODULE(MiscFunctions)
#endif

#ifdef MODULES_NEWSTATDESC
#ifdef MODULES_STATFUNCTIONS
LOAD_MODULE(StatFunctions)
#endif
#endif

#ifdef MODULES_RESPECNORMAL
LOAD_MODULE(RespecNormal)
#endif

#ifdef MODULES_STATFILTER
#ifdef MODULES_RANDOMSTAT
LOAD_MODULE(RamdonStat)
#endif
#endif


#ifdef MODULES_NEWSTATDESC
#ifdef MODULES_MULTIFLAGSTATSHOW
LOAD_MODULE(MultiFlagStatShow)
#endif
#endif


#ifdef MODULES_SAVEPATH
LOAD_MODULE(SavePath)
#endif

#undef LOAD_MODULE
#endif

#ifdef MODULES_H
#include "m_LaunchInfo.h"			//��ʾ�汾��
#include "m_HighResolution.h"		//��ֱ��ʡ�����������ǿ�Ƽ��ء�����������
#include "m_GameExeDrawModeFix.h"	//�޸�����������ĸ������������ǿ�Ƽ��ء�����������

#include "m_DrawFunctions.h"		//��ͼ���ܡ����������ģ��ĺ�����//��ģ����ڵ�һ����ͬʱҲ�Ƕ������������֤
#include "m_UpdateServerClient.h"	//�շ������������ģ��ĺ�����
#include "m_NewStatDesc.h"			//�µ��������������������ģ��ĺ�����
#include "m_StatItemExtended.h"		//������Ʒ���µȡ�����������������������Ʒ�ĸ�����һ�����鴢�棬������ifdefά��
#include "m_LastHitEvent.h"			//��ɱ�������һ���Ĵ��������������ģ��ĺ�����
#include "m_TimerEvent.h"			//������ҵ�ʱ��LOOP�����������ģ��ĺ�����
#include "m_StatFilter.h"			//���Թ����������������ģ��ĺ�����


#include "m_DamageShow.h"			//�˺���ʾ��need:��ͼ���� & �շ�����
#include "m_MultiPages.h"			//��ҳ���ӡ�need:��ͼ����(ȡ���޶������û�оͿ�ͼ) & �շ�����
#include "m_32KLifeFix.h"			//������������2^32�η����ޡ�need:�շ�����
#include "m_DynamicItems.h"			//��̬��Ʒ
#include "m_DynamicOrbs.h"			//��̬Ѫ��need:��ͼ���ܡ�
#include "m_NewStatShow.h"			//���������ҳ��need:��ͼ���ܡ�
#include "m_EquipedPet.h"			//Ӷ��ȫװ��
#include "m_MagicBag.h"				//ħ���ڴ���need:��������ʾ & ��Ʒ���¡�
#include "m_PlayerDeathKillCount.h"	//��¼����Ļ�ɱ��������need:���һ������ & ��������ʾ��
#include "m_SoulSkills.h"			//��깦�ܡ�need:��ͼ���� & ��������ʾ & ��Ʒ���� & ���һ��������
#include "m_KuiLeiCharm.h"			//����С�����ܡ���Ʒ���� & ���һ��������
#include "m_XuKongCharm.h"			//���С�����ܡ�ʱ��֡ & ��Ʒ���� & ��������ʾ��
#include "m_RedPortal.h"			//���Ź���
//#include "m_SaveFileLimit.h"		//��D2Game�浵��չ
#include "m_ConvenientGame.h"		//ȫСվ\ȫ����\һȭ����
#include "m_Drop.h"					//�������
#include "m_LevelExtended.h"		//level��չ-δ���!                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
#include "m_MiscFunctions.h"		//MOD���ֱ��Patch��С���� , ǿ�Ƽ���hackmapҲ��������
#include "m_StatFunctions.h"		//A����B�����������뻤�������need:��������ʾ��
#include "m_RespecNormal.h"			//ϴ��
#include "m_RandomStat.h"			//�����������need:���Թ�������
#include "m_MultiFlagStatShow.h"	//ʹ���Զ�̬��ʾ��need:��������ʾ��


#endif
