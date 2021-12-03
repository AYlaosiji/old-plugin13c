# OldPlugin13c

#### 介绍
该仓库现在公开用于mod制作交流学习

#### 功能包括

1.  #include "m_LaunchInfo.h"			//显示版本号
2.  #include "m_HighResolution.h"		//大分辨率★★★★★★★★★★★强制加载★★★★★★★★★★★
3.  #include "m_GameExeDrawModeFix.h"	//修复让他不跳字母★★★★★★★★★★★强制加载★★★★★★★★★★★
4.  #include "m_DrawFunctions.h"		//画图功能★包含了其他模块的函数★//此模块放在第一个，同时也是对整个插件做验证
5.  #include "m_UpdateServerClient.h"	//收发包★包含其他模块的函数★
6.  #include "m_NewStatDesc.h"			//新的属性描述★包含了其他模块的函数★
7.  #include "m_StatItemExtended.h"		//包括物品更新等★★★★★★特殊★★★★★★里面对物品的更新是一个数组储存，而不是ifdef维护
8.  #include "m_LastHitEvent.h"			//击杀怪物最后一击的触发★包含了其他模块的函数★
9.  #include "m_TimerEvent.h"			//各个玩家的时间LOOP★包含了其他模块的函数★
10.  #include "m_StatFilter.h"			//属性过滤器★包含了其他模块的函数★
11.  #include "m_DamageShow.h"			//伤害显示【need:画图功能 & 收发包】
12.  #include "m_MultiPages.h"			//分页箱子【need:画图功能(取消限定，如果没有就空图) & 收发包】
13.  #include "m_32KLifeFix.h"			//法力，耐力的2^32次方上限【need:收发包】
14.  #include "m_DynamicItems.h"			//动态物品
15.  #include "m_DynamicOrbs.h"			//动态血球【need:画图功能】
16.  #include "m_NewStatShow.h"			//额外的属性页【need:画图功能】
17.  #include "m_EquipedPet.h"			//佣兵全装备
18.  #include "m_MagicBag.h"				//魔法口袋【need:新属性显示 & 物品更新】
19.  #include "m_PlayerDeathKillCount.h"	//记录人物的击杀与死亡【need:最后一击触发 & 新属性显示】
20.  #include "m_SoulSkills.h"			//灵魂功能【need:画图功能 & 新属性显示 & 物品更新 & 最后一击触发】
21.  #include "m_KuiLeiCharm.h"			//傀儡小符功能【物品更新 & 最后一击触发】
22.  #include "m_XuKongCharm.h"			//虚空小符功能【时间帧 & 物品更新 & 新属性显示】
23.  #include "m_RedPortal.h"			//红门功能
24.  #include "m_ConvenientGame.h"		//全小站\全任务\一拳满级
25.  #include "m_Drop.h"					//掉落相关
26.  #include "m_LevelExtended.h"		//level拓展-未完成nctions.h"		//MOD多个直接Patch的小功能 , 强制加载hackmap也在这里面
27.  #include "m_StatFunctions.h"		//A满足B的属性限制与护身符区域【need:新属性显示】
28.  #include "m_RespecNormal.h"			//洗点
29.  #include "m_RandomStat.h"			//产生随机数【need:属性过滤器】
30.  #include "m_MultiFlagStatShow.h"	//使属性多态显示【need:新属性显示】

#### 使用说明

 没有更多的信息 TODO

#### 参与贡献

1.  dapengyou
2.  andersong
3.  mxcen
4.  。。。
5.  plugy
6.  high resolution(did some changes for my mod) from https://github.com/noah-/D2HD 
7.  hackmap



