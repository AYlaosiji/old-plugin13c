#include "pch.h"
#ifdef MODULES_MULTIFLAGSTATSHOW
#define STR_CANLEARN L"$$9专修球+任意完美宝石+技能符石=学习该技能\n$$;可以学习其他职业技能(被动/变形无法学习)"
static DWORD m_MultiFlagStatShow_StatNegLimit;
static DWORD m_MultiFlagStatShow_UniqueItemUpFlag;
static DWORD m_MultiFlagStatShow_CorpseExplosionFlag;

void m_MultiFlagStatShow_LoadCfg()
{
	m_MultiFlagStatShow_StatNegLimit = cfgload::GetModuleCfgInt("Multi Flag Stat Show", "Item Neg Limit");
	m_MultiFlagStatShow_UniqueItemUpFlag= cfgload::GetModuleCfgInt("Multi Flag Stat Show", "Unique Item Up Flag");
	m_MultiFlagStatShow_CorpseExplosionFlag= cfgload::GetModuleCfgInt("Multi Flag Stat Show", "Corpse Explosion Flag");
}

void m_MultiFlagStatShow_Install()
{

}

void m_MultiFlagStatShow_UnInstall()
{

}

BOOL m_MultiFlagStatShow_NewStatDesc(wchar_t* wszchar, DWORD statID, UnitAny* pItem, DWORD statvalue)
{
	if (m_MultiFlagStatShow_StatNegLimit && statID == m_MultiFlagStatShow_StatNegLimit)
	{
		swprintf(wszchar, L"%s", STR_CANLEARN);
		D2String::ReplaceColorSpecs(wszchar);
		return TRUE;
	}

//为了节省属性，使用属性362，这是黄金的打造的属性
//无孔!!!!!暗金装备现在加2个魔晶可以进行附魔：
//1‰的概率获得邪恶属性->可以转成背包护身符(合成公式待更新)--------------1
//1‰的概率获得崇高属性->可以转成戒指(合成公式待更新)--------------------2
//1‰的概率获得神圣属性->可以转成项链(合成公式待更新)--------------------3
//1‰的概率获得庄重属性->1技能-------------------------------------------4
//7‰的概率获得庄重属性->1各职业技能-------------------------------------4
//9‰的概率获得庄重属性->1 - 20 % MF-------------------------------------4
//80‰的概率获得庄重属性->1 - 20 % 经验获取------------------------------4
//100‰的概率获得庄重属性->1 - 20 % EG-----------------------------------4
//100‰的概率获得贪婪属性->全属性 - 50-----------------------------------5
//100‰的概率获得平淡属性->装备不变，送一个草药--------------------------6
//300‰的概率获得平淡属性->装备不变--------------------------------------6
//100‰的概率获得祝福属性->可以打造(打造公式与属性待更新)----------------10
//200‰的概率装备直接消失

	else if (m_MultiFlagStatShow_UniqueItemUpFlag && statID == m_MultiFlagStatShow_UniqueItemUpFlag)
	{
		DWORD ItemQuality = D2Common::D2GetItemQuality(pItem);
		if (ItemQuality == ITEMQUALITY_UNIQUE)//暗金的
		{
			DWORD statvalue = D2Common::D2GetUnitStat(pItem, m_MultiFlagStatShow_UniqueItemUpFlag, 0);
			switch (statvalue)
			{
			case 1://邪恶的
				swprintf(wszchar, L"$$1邪恶"); break;
			case 2://崇高的
				swprintf(wszchar, L"$$1崇高"); break;
			case 3://神圣的
				swprintf(wszchar, L"$$1神圣"); break;
			case 4://庄重的
				swprintf(wszchar, L"$$9庄重"); break;
			case 5://贪婪的
				swprintf(wszchar, L"$$1贪婪"); break;
			case 6://平淡的
				swprintf(wszchar, L"$$5平淡"); break;
			case 7:
			case 8:
			case 9:
				swprintf(wszchar, L"$$1你TMD开挂了???"); break;
			case 10://祝福
				swprintf(wszchar, L"$$2祝福"); break;
			default://强化暗金
				swprintf(wszchar, L"$$8暗金打造(%d/30)", statvalue-10); break;
			}
			D2String::ReplaceColorSpecs(wszchar);
			return TRUE;
		}
	}
	else if (m_MultiFlagStatShow_CorpseExplosionFlag && statID == m_MultiFlagStatShow_CorpseExplosionFlag)
	{
		DWORD value = D2Common::D2GetUnitStat(pItem, m_MultiFlagStatShow_CorpseExplosionFlag, 0);
		DWORD value2 = value/30;
		swprintf(wszchar, L"$$8触发的尸体爆炸范围等于触发等级 +%d 码\n该尸体爆炸能受到元素穿刺加成\n尸体爆炸强化度： %d", value2, value);
		D2String::ReplaceColorSpecs(wszchar);
		return TRUE;
	}
	return FALSE;
}

#endif
