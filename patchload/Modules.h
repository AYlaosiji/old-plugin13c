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
#include "m_LaunchInfo.h"			//显示版本号
#include "m_HighResolution.h"		//大分辨率★★★★★★★★★★★强制加载★★★★★★★★★★★
#include "m_GameExeDrawModeFix.h"	//修复让他不跳字母★★★★★★★★★★★强制加载★★★★★★★★★★★

#include "m_DrawFunctions.h"		//画图功能★包含了其他模块的函数★//此模块放在第一个，同时也是对整个插件做验证
#include "m_UpdateServerClient.h"	//收发包★包含其他模块的函数★
#include "m_NewStatDesc.h"			//新的属性描述★包含了其他模块的函数★
#include "m_StatItemExtended.h"		//包括物品更新等★★★★★★特殊★★★★★★里面对物品的更新是一个数组储存，而不是ifdef维护
#include "m_LastHitEvent.h"			//击杀怪物最后一击的触发★包含了其他模块的函数★
#include "m_TimerEvent.h"			//各个玩家的时间LOOP★包含了其他模块的函数★
#include "m_StatFilter.h"			//属性过滤器★包含了其他模块的函数★


#include "m_DamageShow.h"			//伤害显示【need:画图功能 & 收发包】
#include "m_MultiPages.h"			//分页箱子【need:画图功能(取消限定，如果没有就空图) & 收发包】
#include "m_32KLifeFix.h"			//法力，耐力的2^32次方上限【need:收发包】
#include "m_DynamicItems.h"			//动态物品
#include "m_DynamicOrbs.h"			//动态血球【need:画图功能】
#include "m_NewStatShow.h"			//额外的属性页【need:画图功能】
#include "m_EquipedPet.h"			//佣兵全装备
#include "m_MagicBag.h"				//魔法口袋【need:新属性显示 & 物品更新】
#include "m_PlayerDeathKillCount.h"	//记录人物的击杀与死亡【need:最后一击触发 & 新属性显示】
#include "m_SoulSkills.h"			//灵魂功能【need:画图功能 & 新属性显示 & 物品更新 & 最后一击触发】
#include "m_KuiLeiCharm.h"			//傀儡小符功能【物品更新 & 最后一击触发】
#include "m_XuKongCharm.h"			//虚空小符功能【时间帧 & 物品更新 & 新属性显示】
#include "m_RedPortal.h"			//红门功能
//#include "m_SaveFileLimit.h"		//对D2Game存档拓展
#include "m_ConvenientGame.h"		//全小站\全任务\一拳满级
#include "m_Drop.h"					//掉落相关
#include "m_LevelExtended.h"		//level拓展-未完成!                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
#include "m_MiscFunctions.h"		//MOD多个直接Patch的小功能 , 强制加载hackmap也在这里面
#include "m_StatFunctions.h"		//A满足B的属性限制与护身符区域【need:新属性显示】
#include "m_RespecNormal.h"			//洗点
#include "m_RandomStat.h"			//产生随机数【need:属性过滤器】
#include "m_MultiFlagStatShow.h"	//使属性多态显示【need:新属性显示】


#endif
