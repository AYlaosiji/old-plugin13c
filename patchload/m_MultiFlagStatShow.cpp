#include "pch.h"
#ifdef MODULES_MULTIFLAGSTATSHOW
#define STR_CANLEARN L"$$9ר����+����������ʯ+���ܷ�ʯ=ѧϰ�ü���\n$$;����ѧϰ����ְҵ����(����/�����޷�ѧϰ)"
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

//Ϊ�˽�ʡ���ԣ�ʹ������362�����ǻƽ�Ĵ��������
//�޿�!!!!!����װ�����ڼ�2��ħ�����Խ��и�ħ��
//1��ĸ��ʻ��а������->����ת�ɱ��������(�ϳɹ�ʽ������)--------------1
//1��ĸ��ʻ�ó������->����ת�ɽ�ָ(�ϳɹ�ʽ������)--------------------2
//1��ĸ��ʻ����ʥ����->����ת������(�ϳɹ�ʽ������)--------------------3
//1��ĸ��ʻ��ׯ������->1����-------------------------------------------4
//7��ĸ��ʻ��ׯ������->1��ְҵ����-------------------------------------4
//9��ĸ��ʻ��ׯ������->1 - 20 % MF-------------------------------------4
//80��ĸ��ʻ��ׯ������->1 - 20 % �����ȡ------------------------------4
//100��ĸ��ʻ��ׯ������->1 - 20 % EG-----------------------------------4
//100��ĸ��ʻ��̰������->ȫ���� - 50-----------------------------------5
//100��ĸ��ʻ��ƽ������->װ�����䣬��һ����ҩ--------------------------6
//300��ĸ��ʻ��ƽ������->װ������--------------------------------------6
//100��ĸ��ʻ��ף������->���Դ���(���칫ʽ�����Դ�����)----------------10
//200��ĸ���װ��ֱ����ʧ

	else if (m_MultiFlagStatShow_UniqueItemUpFlag && statID == m_MultiFlagStatShow_UniqueItemUpFlag)
	{
		DWORD ItemQuality = D2Common::D2GetItemQuality(pItem);
		if (ItemQuality == ITEMQUALITY_UNIQUE)//�����
		{
			DWORD statvalue = D2Common::D2GetUnitStat(pItem, m_MultiFlagStatShow_UniqueItemUpFlag, 0);
			switch (statvalue)
			{
			case 1://а���
				swprintf(wszchar, L"$$1а��"); break;
			case 2://��ߵ�
				swprintf(wszchar, L"$$1���"); break;
			case 3://��ʥ��
				swprintf(wszchar, L"$$1��ʥ"); break;
			case 4://ׯ�ص�
				swprintf(wszchar, L"$$9ׯ��"); break;
			case 5://̰����
				swprintf(wszchar, L"$$1̰��"); break;
			case 6://ƽ����
				swprintf(wszchar, L"$$5ƽ��"); break;
			case 7:
			case 8:
			case 9:
				swprintf(wszchar, L"$$1��TMD������???"); break;
			case 10://ף��
				swprintf(wszchar, L"$$2ף��"); break;
			default://ǿ������
				swprintf(wszchar, L"$$8�������(%d/30)", statvalue-10); break;
			}
			D2String::ReplaceColorSpecs(wszchar);
			return TRUE;
		}
	}
	else if (m_MultiFlagStatShow_CorpseExplosionFlag && statID == m_MultiFlagStatShow_CorpseExplosionFlag)
	{
		DWORD value = D2Common::D2GetUnitStat(pItem, m_MultiFlagStatShow_CorpseExplosionFlag, 0);
		DWORD value2 = value/30;
		swprintf(wszchar, L"$$8������ʬ�屬ը��Χ���ڴ����ȼ� +%d ��\n��ʬ�屬ը���ܵ�Ԫ�ش��̼ӳ�\nʬ�屬ըǿ���ȣ� %d", value2, value);
		D2String::ReplaceColorSpecs(wszchar);
		return TRUE;
	}
	return FALSE;
}

#endif
