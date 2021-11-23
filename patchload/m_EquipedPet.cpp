#include"pch.h"
#ifdef MODULES_EQUIPEDPET
static BOOL m_EquipedPet_FullEquipPet = FALSE;
static int m_EquipedPet_FullEquipPethelm = 0;
static int m_EquipedPet_FullEquipPetring = 0;
static int m_EquipedPet_FullEquipPetamul = 0;
static int m_EquipedPet_FullEquipPetboot = 0;
static int m_EquipedPet_FullEquipPetglov= 0;
static int m_EquipedPet_FullEquipPetbelt = 0;

void m_EquipedPet_RingCheck_ASM();
void PetItemCheck_ASM();

void m_EquipedPet_LoadCfg()
{
	m_EquipedPet_FullEquipPet = cfgload::GetModuleCfgBool("Equiped Pet", "Full Equip Pet IsOn");
	m_EquipedPet_FullEquipPethelm = cfgload::GetModuleCfgInt("Equiped Pet", "Full Equip Pet helm");
	m_EquipedPet_FullEquipPetring = cfgload::GetModuleCfgInt("Equiped Pet", "Full Equip Pet ring");
	m_EquipedPet_FullEquipPetamul = cfgload::GetModuleCfgInt("Equiped Pet", "Full Equip Pet amul");
	m_EquipedPet_FullEquipPetboot = cfgload::GetModuleCfgInt("Equiped Pet", "Full Equip Pet boot");
	m_EquipedPet_FullEquipPetglov = cfgload::GetModuleCfgInt("Equiped Pet", "Full Equip Pet glov");
	m_EquipedPet_FullEquipPetbelt = cfgload::GetModuleCfgInt("Equiped Pet", "Full Equip Pet belt");
}

void m_EquipedPet_Install()
{
	DWORD Offset = 0;
	if (m_EquipedPet_FullEquipPet)
	{
#ifdef D2SERVER
		Offset = D2Game::GetAddress(0xD064F);//D2Game对类型的判断
		Memory::SetCursor(Offset);
		Memory::ChangeCallB((DWORD)D2Common::D2CheckItemType, (DWORD)PetItemCheck_ASM);

		Offset = D2Game::GetAddress(0xCFC33);
		Memory::SetCursor(Offset);
		Memory::ChangeByte(0x0F, 0xe8);
		Memory::ChangeCallA(0x13244CB6, (DWORD)m_EquipedPet_RingCheck_ASM);
#endif
		Offset = D2Client::GetAddress(0x8C7C3);//D2Client对类型的判断
		Memory::SetCursor(Offset);
		Memory::ChangeCallB((DWORD)D2Common::D2CheckItemType, (DWORD)PetItemCheck_ASM);
	}
}

void m_EquipedPet_UnInstall()
{

}

#ifdef D2SERVER
__declspec(naked) void m_EquipedPet_RingCheck_ASM()
{
	__asm
	{
		movzx ecx, byte ptr ss : [esp + 0x17]
		cmp ecx, 0x6
		jnz mkrt2
		push 0x7
		push esi
		call D2Common::D2GetItemByBodyLoc
		test eax, eax
		jnz mkrt1
		mov ecx, 0x7
		mov byte ptr ss : [esp + 0x17] , cl
		jmp mkrt2
mkrt1 :
		mov ecx, 0x6
mkrt2 :
		ret
	}
}

#endif

BOOL __fastcall PetItemCheck(UnitAny*  pItem, DWORD type, UnitAny* pet)
{
	if (m_EquipedPet_FullEquipPethelm) { if (D2Common::D2CheckItemType(pItem, m_EquipedPet_FullEquipPethelm))return TRUE; }//头盔
	if (m_EquipedPet_FullEquipPetring) { if (D2Common::D2CheckItemType(pItem, m_EquipedPet_FullEquipPetring))return TRUE; }//戒指
	if (m_EquipedPet_FullEquipPetamul) { if (D2Common::D2CheckItemType(pItem, m_EquipedPet_FullEquipPetamul))return TRUE; }//项链
	if (m_EquipedPet_FullEquipPetboot) { if (D2Common::D2CheckItemType(pItem, m_EquipedPet_FullEquipPetboot))return TRUE; }//鞋子
	if (m_EquipedPet_FullEquipPetglov) { if (D2Common::D2CheckItemType(pItem, m_EquipedPet_FullEquipPetglov))return TRUE; }//手套
	if (m_EquipedPet_FullEquipPetbelt) { if (D2Common::D2CheckItemType(pItem, m_EquipedPet_FullEquipPetbelt))return TRUE; }//腰带
	return FALSE;
}

__declspec(naked) void PetItemCheck_ASM()
{
	__asm
	{
		pushad
		mov ecx, [esp + 0x24]
		mov edx, [esp + 0x28]
		push esi
		call PetItemCheck
		test eax,eax
		jz mrkno
		popad
		mov eax,1
		retn 8
mrkno:
		popad
		JMP D2Common::D2CheckItemType
	}
}

#endif