#include"pch.h"
#ifdef MODULES_MISCFUNCTIONS
//9.修改技能等级无上限:打开D2common.dll搜索(HEX修改器地址)505FE(OD修改器地址)6FDA05FE把后面的代码改成db 90 90

static BOOL m_MiscFunctions_ChangePrColor = FALSE;

static BOOL m_MiscFunctions_DisableAkalaRespec = FALSE;

static BOOL m_MiscFunctions_BloodManaFix = FALSE;

static BOOL m_MiscFunctions_SmiteDamageDisplay = FALSE;

static BOOL m_MiscFunctions_AllCanRuneWordExSet = FALSE;

static BOOL m_MiscFunctions_BankGoldToMax = FALSE;
static BOOL m_MiscFunctions_InvGoldToMax = FALSE;

static BOOL m_MiscFunctions_KickDmgShowOnBootsIsOn = FALSE;

static BOOL m_MiscFunctions_LoadMutiResIsOn = FALSE;
HMODULE pD2MultiRes = NULL;
HMODULE pD2MultiRes2 = NULL;

static BOOL m_MiscFunctions_LoadMapDirIsOn = FALSE;
HMODULE pD2Hackmap = NULL;

static BOOL m_MiscFunctions_MultiD2Window_IsOn = FALSE;

static BOOL m_MiscFunctions_OSkillLimit_IsOn = FALSE;
static BYTE m_MiscFunctions_OSkillLimitValue;


static BOOL m_MiscFunctions_PhysPierce_IsOn = FALSE;
static DWORD m_MiscFunctions_PhysPierceStatID;

static BOOL m_MiscFunctions_MagPierce_IsOn = FALSE;
static DWORD m_MiscFunctions_MagPierceStatID;

static BOOL m_MiscFunctions_BreakPierce_IsOn = FALSE;


static BOOL m_MiscFunctions_PoisonAbsorb_IsOn = FALSE;
static DWORD m_MiscFunctions_PoisonAbsorbStatID;
static DWORD m_MiscFunctions_PoisonAbsorbPercentStatID;

static BOOL m_MiscFunctions_DRPercentCap_IsOn = FALSE;
static DWORD m_MiscFunctions_DRPercentCapValue;

static BOOL m_MiscFunctions_PoisonDmgReducedByMagReduce = FALSE;

static BOOL m_MiscFunctions_NewQuestSkillPoint = FALSE;
static BYTE m_MiscFunctions_NewQuestSkillPoint1;
static BYTE m_MiscFunctions_NewQuestSkillPoint2;
static BYTE m_MiscFunctions_NewQuestSkillPoint3;

static BOOL m_MiscFunctions_UnlimitedMissiles = FALSE;

static BOOL m_MiscFunctions_GambleNumsIsOn = FALSE;
static BYTE m_MiscFunctions_GambleNums;

static BOOL m_MiscFunctions_ExperienceBeyondTwoScreen = FALSE;

static BOOL m_MiscFunctions_EnterAfterCowKingBeKilled = FALSE;
void m_MiscFunctions_LoadCfg()
{
	m_MiscFunctions_ChangePrColor = cfgload::GetModuleCfgBool("Misc", "Change Pr Color IsOn");
	m_MiscFunctions_DisableAkalaRespec= cfgload::GetModuleCfgBool("Misc", "Disable Akala Respec IsOn");
	m_MiscFunctions_BloodManaFix= cfgload::GetModuleCfgBool("Misc", "Blood Mana Fix IsOn");
	m_MiscFunctions_SmiteDamageDisplay= cfgload::GetModuleCfgBool("Misc", "Smite Damage Display IsOn");
	m_MiscFunctions_AllCanRuneWordExSet= cfgload::GetModuleCfgBool("Misc", "All Can Rune Word Ex Set IsOn");
	m_MiscFunctions_BankGoldToMax=cfgload::GetModuleCfgBool("Misc", "Bank Gold To 2000000000 IsOn");
	m_MiscFunctions_InvGoldToMax = cfgload::GetModuleCfgBool("Misc", "Inv Gold To 8000000*lv IsOn");
	m_MiscFunctions_KickDmgShowOnBootsIsOn= cfgload::GetModuleCfgBool("Misc", "Kick Dmg Show On Boots IsOn");
	m_MiscFunctions_LoadMutiResIsOn = cfgload::GetModuleCfgBool("Misc", "Load Muti Res IsOn");
	m_MiscFunctions_LoadMapDirIsOn= cfgload::GetModuleCfgBool("Misc", "Load Map Dir IsOn");
	m_MiscFunctions_MultiD2Window_IsOn= cfgload::GetModuleCfgBool("Misc", "Multi D2Window IsOn");
	m_MiscFunctions_OSkillLimit_IsOn = cfgload::GetModuleCfgBool("Misc", "OSkill Limit IsOn");
	m_MiscFunctions_OSkillLimitValue = cfgload::GetModuleCfgInt("Misc", "OSkill Limit Value");
	m_MiscFunctions_PhysPierce_IsOn = cfgload::GetModuleCfgBool("Misc", "Phys Pierce IsOn");
	m_MiscFunctions_PhysPierceStatID = cfgload::GetModuleCfgInt("Misc", "Phys Pierce Stat");
	m_MiscFunctions_MagPierce_IsOn = cfgload::GetModuleCfgBool("Misc", "Mag Pierce IsOn");
	m_MiscFunctions_MagPierceStatID = cfgload::GetModuleCfgInt("Misc", "Mag Pierce Stat");
	m_MiscFunctions_BreakPierce_IsOn= cfgload::GetModuleCfgBool("Misc", "Break Pierce IsOn");

	m_MiscFunctions_PoisonAbsorb_IsOn= cfgload::GetModuleCfgBool("Misc", "Poison Absorb IsOn");
	m_MiscFunctions_PoisonAbsorbStatID= cfgload::GetModuleCfgBool("Misc", "Poison Absorb StatID");
	m_MiscFunctions_PoisonAbsorbPercentStatID = cfgload::GetModuleCfgBool("Misc", "Poison Absorb Percent StatID");
	m_MiscFunctions_PoisonDmgReducedByMagReduce=cfgload::GetModuleCfgBool("Misc", "Poison Dmg Reduced By MagReduce IsOn");
	m_MiscFunctions_DRPercentCap_IsOn= cfgload::GetModuleCfgBool("Misc", "DR Cap Change IsOn");
	m_MiscFunctions_DRPercentCapValue= cfgload::GetModuleCfgInt("Misc", "DR Cap Change Value");
	m_MiscFunctions_NewQuestSkillPoint= cfgload::GetModuleCfgBool("Misc", "New Quest Skill Point IsOn");
	m_MiscFunctions_NewQuestSkillPoint1= cfgload::GetModuleCfgInt("Misc", "Skill Point:Den of evil");
	m_MiscFunctions_NewQuestSkillPoint2 = cfgload::GetModuleCfgInt("Misc", "Skill Point:Radament");
	m_MiscFunctions_NewQuestSkillPoint3 = cfgload::GetModuleCfgInt("Misc", "Skill Point:Izual");
	m_MiscFunctions_UnlimitedMissiles= cfgload::GetModuleCfgBool("Misc", "Unlimited Missiles");
	m_MiscFunctions_GambleNumsIsOn = cfgload::GetModuleCfgBool("Misc", "Gamble Nums IsOn");
	m_MiscFunctions_GambleNums=cfgload::GetModuleCfgInt("Misc", "Gamble Nums");
	m_MiscFunctions_ExperienceBeyondTwoScreen= cfgload::GetModuleCfgInt("Misc", "Experience Beyond Two Screen IsOn");
	m_MiscFunctions_EnterAfterCowKingBeKilled= cfgload::GetModuleCfgBool("Misc", "Enter After Cow King Be Killed IsOn");
}

void m_MiscFunctions_Install()
{
	DWORD MiscFunctionsOffset;
	if (m_MiscFunctions_ChangePrColor)
	{
		MiscFunctionsOffset = D2Client::GetAddress(0x9425C);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x03, 0x09);
	}

	if (m_MiscFunctions_DisableAkalaRespec)
	{
		MiscFunctionsOffset = D2Client::GetAddress(0x4A3A6);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x04, 0x03);
	}

	if (m_MiscFunctions_BloodManaFix)
	{
		MiscFunctionsOffset = D2Common::GetAddress(0x37D54);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x8B, 0x90);
		Memory::ChangeByte(0x40, 0x90);
		Memory::ChangeByte(0x1C, 0x90);

		MiscFunctionsOffset = D2Game::GetAddress(0xBE7E);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x8B, 0x90);
		Memory::ChangeByte(0x8F, 0x90);
		Memory::ChangeByte(0x58, 0x90);
		Memory::ChangeByte(0x01, 0x90);
		Memory::ChangeByte(0x00, 0x90);
		Memory::ChangeByte(0x00, 0x90);
	}

	if (m_MiscFunctions_SmiteDamageDisplay)
	{
		MiscFunctionsOffset = D2Client::GetAddress(0x93FA0);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x75, 0x90);
		Memory::ChangeByte(0x34, 0x90);
	}

	if (m_MiscFunctions_AllCanRuneWordExSet)
	{
		MiscFunctionsOffset = D2Common::GetAddress(0x26BC1);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(4, 5);
		Memory::ChangeByte(0x7C, 0X75);
	}

	if (m_MiscFunctions_BankGoldToMax)
	{
		MiscFunctionsOffset = D2Common::GetAddress(0x2E9C1);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0x2625A0, 2000000000);
	}

	if (m_MiscFunctions_InvGoldToMax)
	{
		MiscFunctionsOffset = D2Common::GetAddress(0x3194A);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0x2710, 8000000);

		MiscFunctionsOffset = D2Common::GetAddress(0x3195E);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0x2710, 8000000);

		MiscFunctionsOffset = D2Common::GetAddress(0x3198E);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0x2710, 8000000);
	}

	if (m_MiscFunctions_KickDmgShowOnBootsIsOn)
	{
		MiscFunctionsOffset = D2Client::GetAddress(0x94009);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x75, 0x90);
		Memory::ChangeByte(0x13, 0x90);
	}

	if (m_MiscFunctions_LoadMapDirIsOn && GetModuleHandle("D2server") == NULL)
	{
		pD2Hackmap = LoadLibrary("map\\D2hackmap.dll");
	}


	if (m_MiscFunctions_LoadMutiResIsOn && GetModuleHandle("D2server") == NULL)
	{
		if (0)
		{
			pD2MultiRes = LoadLibrary("D2MultiRes");
			pD2MultiRes2 = LoadLibrary("D2MultiResExt");
			class D2MultiRes : public Library<D2MultiRes>
			{
			public:
				static void Init()
				{
					Name = "D2MultiRes.dll";
					Offset = LoadDiabloLibrary();
				}
			};
			D2MultiRes::Init();
			D2MultiRes::HookLibrary();
			MiscFunctionsOffset = D2MultiRes::GetAddress(0x2368);
			Memory::SetCursor(MiscFunctionsOffset);
			Memory::ChangeDword(-0x280, -0x400);

			MiscFunctionsOffset = D2MultiRes::GetAddress(0x2374);
			Memory::SetCursor(MiscFunctionsOffset);
			Memory::ChangeDword(-0x1E0, -0x234);

			MiscFunctionsOffset = D2MultiRes::GetAddress(0x2468);
			Memory::SetCursor(MiscFunctionsOffset);
			Memory::ChangeDword(0x1b0, 0x200);
			//Memory::ChangeDword(0x200, 0x200);

			MiscFunctionsOffset = D2MultiRes::GetAddress(0x2b0a);
			Memory::SetCursor(MiscFunctionsOffset);
			Memory::ChangeDword(0x140, 0x200);
			//Memory::ChangeDword(0x200, 0x325);//右边缘

			MiscFunctionsOffset = D2MultiRes::GetAddress(0x2b10);
			Memory::SetCursor(MiscFunctionsOffset);
			//Memory::ChangeDword(-0x1e0, -0x234);
			Memory::ChangeDword(-0x234, -0x299);//280-295 290是上面多一块 310是下面多一块

			MiscFunctionsOffset = D2MultiRes::GetAddress(0x2bfe);
			Memory::SetCursor(MiscFunctionsOffset);
			//Memory::ChangeDword(0x1b0, 0x200);
			Memory::ChangeDword(0x200,0x299);//下边缘 299最大

			MiscFunctionsOffset = D2MultiRes::GetAddress(0x3301);
			Memory::SetCursor(MiscFunctionsOffset);
			Memory::ChangeDword(-0x280, -0x400);//这个不要动
		}

	}


	if (m_MiscFunctions_MultiD2Window_IsOn)
	{
		MiscFunctionsOffset = D2Gfx::GetAddress(0x85BF);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x74, 0xEB);
	}

	if (m_MiscFunctions_OSkillLimit_IsOn)
	{
		MiscFunctionsOffset = D2Common::GetAddress(0x4FD7B);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x03, m_MiscFunctions_OSkillLimitValue);
		MiscFunctionsOffset = D2Common::GetAddress(0x4FD7F);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x03, m_MiscFunctions_OSkillLimitValue);

		MiscFunctionsOffset = D2Client::GetAddress(0x55986);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x03, m_MiscFunctions_OSkillLimitValue);

		MiscFunctionsOffset = D2Client::GetAddress(0x5598A);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x03, m_MiscFunctions_OSkillLimitValue);
	}

#ifdef D2SERVER
	if (m_MiscFunctions_PhysPierce_IsOn)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0x102B6C);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0xFFFFFFFF, m_MiscFunctions_PhysPierceStatID);
	}

	if (m_MiscFunctions_MagPierce_IsOn)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0x102ABC);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0xFFFFFFFF, m_MiscFunctions_MagPierceStatID);
	}

	if (m_MiscFunctions_BreakPierce_IsOn)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0xDB3E0);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0x7C64FE83, 0xEB909090);
	}

	if (m_MiscFunctions_PoisonAbsorb_IsOn)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0x102C20);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0xFFFFFFFF, m_MiscFunctions_PoisonAbsorbStatID);
		Memory::ChangeDword(0xFFFFFFFF, m_MiscFunctions_PoisonAbsorbPercentStatID);
	}

	if (m_MiscFunctions_PoisonDmgReducedByMagReduce)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0x102C28);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0x00000000, 0x00000002);
	}

	if (m_MiscFunctions_DRPercentCap_IsOn)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0xDB4AF);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeDword(0x00000032, m_MiscFunctions_DRPercentCapValue);
	}

	if (m_MiscFunctions_NewQuestSkillPoint)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0x653D3);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x01, m_MiscFunctions_NewQuestSkillPoint1);

		MiscFunctionsOffset = D2Game::GetAddress(0xD9E9B);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x01, m_MiscFunctions_NewQuestSkillPoint2);

		MiscFunctionsOffset = D2Game::GetAddress(0xBA742);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x02, m_MiscFunctions_NewQuestSkillPoint3);
	}

	if (m_MiscFunctions_UnlimitedMissiles)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0xA16BE);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x4D, 0x90);
	}

	if (m_MiscFunctions_GambleNumsIsOn)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0xBE615);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x0E, m_MiscFunctions_GambleNums);
	}

	if (m_MiscFunctions_ExperienceBeyondTwoScreen)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0xDAFCA);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x3D, 0x90);
		Memory::ChangeByte(0x00, 0x90);
		Memory::ChangeByte(0x19, 0x90);
		Memory::ChangeByte(0x00, 0x90);
		Memory::ChangeByte(0x00, 0x90);
		Memory::ChangeByte(0x77, 0x90);
		Memory::ChangeByte(0x53, 0x90);
	}

	if (m_MiscFunctions_EnterAfterCowKingBeKilled)
	{
		MiscFunctionsOffset = D2Game::GetAddress(0x6750A);
		Memory::SetCursor(MiscFunctionsOffset);
		Memory::ChangeByte(0x0F, 0x90);
		Memory::ChangeByte(0x85, 0x90);
		Memory::ChangeByte(0xC5, 0x90);
		Memory::ChangeByte(0x01, 0x90);
		Memory::ChangeByte(0x00, 0x90);
		Memory::ChangeByte(0x00, 0x90);
	}
#endif
}

void m_MiscFunctions_UnInstall()
{
	if (pD2MultiRes)FreeLibrary(pD2MultiRes);
	if (pD2MultiRes2)FreeLibrary(pD2MultiRes2);
	if (pD2Hackmap)FreeLibrary(pD2Hackmap);
}

#endif // MODULES_MISCFUNCTIONS
