#include"pch.h"
#ifdef MODULES_DROP
static BOOL m_Drop_IsOn = FALSE;
static BOOL m_Drop_SuperMFSwitch;

void MyDropFunction_ASM();

void m_Drop_LoadCfg()
{
	m_Drop_IsOn = cfgload::GetModuleCfgBool("Drop", "Drop Functions");
	m_Drop_SuperMFSwitch= cfgload::GetModuleCfgBool("Drop", "Super MF Switch");
}

void m_Drop_Install()
{
#ifdef D2SERVER
	if (m_Drop_IsOn)
	{
		DWORD DropOffset = D2Game::GetAddress(0x758C1);
		Memory::SetCursor(DropOffset);
		Memory::ChangeCallC((DWORD)D2Game::VD2DropTreasureClass, (DWORD)MyDropFunction_ASM);//(DWORD)D2Game::D2DropTreasureClass
	}
#endif
}

void m_Drop_UnInstall()
{

}

#ifdef D2SERVER
static void __fastcall MyDropFunction(GameStruct* pGame, UnitAny* pSource, UnitAny* pKiller, DWORD pTC_D2TCExShortStrc, DWORD nQuality, DWORD nIlvl, DWORD dwZero, DWORD dwZero2, DWORD dwZero3, DWORD dwZero4)
{
	//  D2Common::SgptDataTables;
	DWORD ExtraCount = 0;

	UnitAny* pPlayer = D2Game::D2GetPlayerFromPet(pGame, pSource, pKiller);
	if (!pPlayer)
		return;

	if (m_Drop_SuperMFSwitch)
	{
		DWORD mfvalue=D2Common::D2GetUnitStat(pPlayer, STATS_ITEM_MAGICBONUS, 0);
		if (mfvalue)
		{
			//arctan(mf的值/1000/自然对数)/圆周率*2
			double positivevalue =  mfvalue/exp(1)/1000;
			double ret = atan(positivevalue);
			ret = 2000 * ret / 3.1415926;//获得概率，然后放大到0-1000
			srand(GetTickCount());
			int randnum = rand() % 1000;//范围0-999
			if (randnum<int(ret))//几何概型，会额外掉一次
				D2Game::D2DropTreasureClass(pGame, pSource, pKiller, pTC_D2TCExShortStrc, nQuality, nIlvl, dwZero, dwZero2, dwZero3, dwZero4);
		}
	}
	return;
}

__declspec(naked) void MyDropFunction_ASM()
{
	__asm
	{
		pushad
		mov edx, esi
		mov ecx, edi
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		push[esp + 0x40]
		call MyDropFunction
		popad
		JMP D2Game::VD2DropTreasureClass//12D60
	}
}

#endif // D2SERVER
#endif

